// START IMU.ino
void computeIMU () {
  uint8_t axis;
  static int16_t gyroADCprevious[3] = {
    0,0,0  };
  int16_t gyroADCp[3];
  int16_t gyroADCinter[3];
  static uint32_t timeInterleave = 0;
  //we separate the 2 situations because reading gyro values with a gyro only setup can be acchieved at a higher rate
  //gyro+nunchuk: we must wait for a quite high delay betwwen 2 reads to get both WM+ and Nunchuk data. It works with 3ms
  //gyro only: the delay to read 2 consecutive values can be reduced to only 0.65ms
  ACC_getADC();
  getEstimatedAttitude();
  Gyro_getADC();
  for (axis = 0; axis < 3; axis++)
    gyroADCp[axis] = imu.gyroADC[axis];
  timeInterleave=micros();
  annexCode();
  if ((micros()-timeInterleave)>650) {
    annex650_overrun_count++;
  } 
  else {
    while((micros()-timeInterleave)<650) ; //empirical, interleaving delay between 2 consecutive reads
  }
  Gyro_getADC();
  for (axis = 0; axis < 3; axis++) {
    gyroADCinter[axis] = imu.gyroADC[axis]+gyroADCp[axis];
    // empirical, we take a weighted value of the current and the previous values
    imu.gyroData[axis] = (gyroADCinter[axis]+gyroADCprevious[axis])/3;
    gyroADCprevious[axis] = gyroADCinter[axis]>>1;
    if (!ACC) imu.accADC[axis]=0;
  }
}
// **************************************************
// Simplified IMU based on "Complementary Filter"
// Inspired by http://starlino.com/imu_guide.html
//
// adapted by ziss_dm : http://www.multiwii.com/forum/viewtopic.php?f=8&t=198
//
// The following ideas was used in this project:
// 1) Rotation matrix: http://en.wikipedia.org/wiki/Rotation_matrix
// 2) Small-angle approximation: http://en.wikipedia.org/wiki/Small-angle_approximation
// 3) C. Hastings approximation for atan2()
// 4) Optimization tricks: http://www.hackersdelight.org/
//
// Currently Magnetometer uses separate CF which is used only
// for heading approximation.
//
// **************************************************
//******  advanced users settings *******************
/* Set the Low Pass Filter factor for ACC
 Increasing this value would reduce ACC noise (visible in GUI), but would increase ACC lag time
 Comment this if  you do not want filter at all.
 unit = n power of 2 */
// this one is also used for ALT HOLD calculation, should not be changed
#ifndef ACC_LPF_FACTOR
#define ACC_LPF_FACTOR 4 // that means a LPF of 16
#endif

/* Set the Gyro Weight for Gyro/Acc complementary filter
 Increasing this value would reduce and delay Acc influence on the output of the filter*/
#ifndef GYR_CMPF_FACTOR
#define GYR_CMPF_FACTOR 600
#endif

/* Set the Gyro Weight for Gyro/Magnetometer complementary filter
 Increasing this value would reduce and delay Magnetometer influence on the output of the filter*/
#define GYR_CMPFM_FACTOR 250

//****** end of advanced users settings *************
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))

#define GYRO_SCALE ((2279 * PI)/((32767.0f / 4.0f ) * 180.0f * 1000000.0f)) //(ITG3200 and MPU6050)
// +-2000/sec deg scale
// for WMP, empirical value should be #define GYRO_SCALE (1.0f/200e6f)
// !!!!should be adjusted to the rad/sec and be part defined in each gyro sensor
typedef struct fp_vector {
  float X,Y,Z;
} 
t_fp_vector_def;
typedef union {
  float A[3];
  t_fp_vector_def V;
} 
t_fp_vector;
typedef struct int32_t_vector {
  int32_t X,Y,Z;
} 
t_int32_t_vector_def;
typedef union {
  int32_t A[3];
  t_int32_t_vector_def V;
} 
t_int32_t_vector;
int16_t _atan2(int32_t y, int32_t x){
  float z = (float)y / x;
  int16_t a;
  if ( abs(y) < abs(x) ){
    a = 573 * z / (1.0f + 0.28f * z * z);
    if (x<0) {
      if (y<0) a -= 1800;
      else a += 1800;
    }
  } 
  else {
    a = 900 - 573 * z / (z * z + 0.28f);
    if (y<0) a -= 1800;
  }
  return a;
}
float InvSqrt (float x){
  union{
    int32_t i;
    float f;
  } 
  conv;
  conv.f = x;
  conv.i = 0x5f3759df - (conv.i >> 1);
  return 0.5f * conv.f * (3.0f - x * conv.f * conv.f);
}
// Rotate Estimated vector(s) with small angle approximation, according to the gyro data
void rotateV(struct fp_vector *v,float* delta) {
  fp_vector v_tmp = *v;
  v->Z -= delta[ROLL] * v_tmp.X + delta[PITCH] * v_tmp.Y;
  v->X += delta[ROLL] * v_tmp.Z - delta[YAW] * v_tmp.Y;
  v->Y += delta[PITCH] * v_tmp.Z + delta[YAW] * v_tmp.X;
}
static int32_t accLPF32[3] = {
  0, 0, 1};
static float invG; // 1/|G|
static t_fp_vector EstG;
static t_int32_t_vector EstG32;
static t_int32_t_vector EstM32;
static t_fp_vector EstM;
void getEstimatedAttitude(){
  uint8_t axis;
  int32_t accMag = 0;
  float scale, deltaGyroAngle[3];
  uint8_t validAcc;
  static uint16_t previousT;
  uint16_t currentT = micros();
  scale = (currentT - previousT) * GYRO_SCALE;
  previousT = currentT;
  // Initialization
  for (axis = 0; axis < 3; axis++) {
    deltaGyroAngle[axis] = imu.gyroADC[axis] * scale;

    accLPF32[axis]    -= accLPF32[axis]>>ACC_LPF_FACTOR;
    accLPF32[axis] += imu.accADC[axis];
    imu.accSmooth[axis]    = accLPF32[axis]>>ACC_LPF_FACTOR;
    accMag += (int32_t)imu.accSmooth[axis]*imu.accSmooth[axis] ;
  }
  rotateV(&EstG.V,deltaGyroAngle);
  rotateV(&EstM.V,deltaGyroAngle);
  if ( abs(imu.accSmooth[ROLL])<ACC_25deg && abs(imu.accSmooth[PITCH])<ACC_25deg && imu.accSmooth[YAW]>0) {
    f.SMALL_ANGLES_25 = 1;
  } 
  else {
    f.SMALL_ANGLES_25 = 0;
  }
  accMag = accMag*100/((int32_t)ACC_1G*ACC_1G);
  validAcc = 72 < accMag && accMag < 133;
  // Apply complimentary filter (Gyro drift correction)
  // If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
    // To do that, we just skip filter, as EstV already rotated by Gyro
  for (axis = 0; axis < 3; axis++) {
    if ( validAcc )
      EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + imu.accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
    EstG32.A[axis] = EstG.A[axis]; //int32_t cross calculation is a little bit faster than float	
    EstM.A[axis] = (EstM.A[axis] * GYR_CMPFM_FACTOR  + imu.magADC[axis]) * INV_GYR_CMPFM_FACTOR;
    EstM32.A[axis] = EstM.A[axis];
  }

#if 1
  // before calibrate acc end, reset EstG
  if (calibratingA==1) {
    for (axis = 0; axis < 3; axis++) {
      EstG.A[axis] = imu.accSmooth[axis];
    }
  }
#endif

  // Attitude of the estimated vector
  int32_t sqGX_sqGZ = sq(EstG32.V.X) + sq(EstG32.V.Z);
  invG = InvSqrt(sqGX_sqGZ + sq(EstG32.V.Y));
  att.angle[ROLL] = _atan2(EstG32.V.X , EstG32.V.Z);
  att.angle[PITCH] = _atan2(EstG32.V.Y , InvSqrt(sqGX_sqGZ)*sqGX_sqGZ);
  att.heading = _atan2(
  EstM32.V.Z * EstG32.V.X - EstM32.V.X * EstG32.V.Z,
  EstM32.V.Y * invG * sqGX_sqGZ - (EstM32.V.X * EstG32.V.X + EstM32.V.Z * EstG32.V.Z) * invG * EstG32.V.Y );
  att.heading += MAG_DECLINIATION * 10; //add declination
  att.heading /= 10;
}

#define UPDATE_INTERVAL 25000    // 40hz update rate (20hz LPF on acc)
#define BARO_TAB_SIZE   21

#define ACC_Z_DEADBAND (ACC_1G>>5) // was 40 instead of 32 now


#define applyDeadband(value, deadband)  \
if(abs(value) < deadband) {    \
    value = 0;                 \
  } else if(value > 0){                   \
    value -= deadband;                    \
  } else if(value < 0){                   \
    value += deadband;                    \
  }

uint8_t getEstimatedAltitude(){
  static uint32_t deadLine;
  static int32_t baroGroundPressure;
  static uint16_t previousT;
  uint16_t currentT = micros();
  uint16_t dTime;
  dTime = currentT - previousT;
  if (dTime < UPDATE_INTERVAL) return 0;
  previousT = currentT;
  if(calibratingB > 0) {
    baroGroundPressure = baroPressureSum/(BARO_TAB_SIZE - 1);
    calibratingB--;
  }
  // pressure relative to ground pressure with temperature compensation (fast!)
  // baroGroundPressure is not supposed to be 0 here
  // see: https://code.google.com/p/ardupilot-mega/source/browse/libraries/AP_Baro/AP_Baro.cpp
  BaroAlt = log( baroGroundPressure * (BARO_TAB_SIZE - 1)/ (float)baroPressureSum ) * (baroTemperature+27315) * 29.271267f; // in cemtimeter 
  alt.EstAlt = (alt.EstAlt * 6 + BaroAlt * 2) >> 3; // additional LPF to reduce baro noise (faster by 30 µs)

  // projection of ACC vector to global Z, with 1G subtructed
  // Math: accZ = A * G / |G| - 1G
  int16_t accZ = (imu.accSmooth[ROLL] * EstG32.V.X + imu.accSmooth[PITCH] * EstG32.V.Y + imu.accSmooth[YAW] * EstG32.V.Z) * invG;
  static int16_t accZoffset = 0;
  if (!f.ARMED) {
    accZoffset -= accZoffset>>3;
    accZoffset += accZ;
  }
  accZ -= accZoffset>>3;
  applyDeadband(accZ, ACC_Z_DEADBAND);
  static float vel = 0.0f;

  // Integrator - velocity, cm/sec
  vel += accZ * ACC_VelScale * dTime;
  static int32_t lastBaroAlt;
  int16_t baroVel = (alt.EstAlt - lastBaroAlt) * 1000000.0f / dTime;
  lastBaroAlt = alt.EstAlt;
  baroVel = constrain(baroVel, -300, 300); // constrain baro velocity +/- 300cm/s
  applyDeadband(baroVel, 10); // to reduce noise near zero

  // apply Complimentary Filter to keep the calculated velocity based on baro velocity (i.e. near real velocity). 
  // By using CF it's possible to correct the drift of integrated accZ (velocity) without loosing the phase, i.e without delay
  vel = vel * 0.985f + baroVel * 0.015f;
  //D
  int16_t vel_tmp = vel;
  applyDeadband(vel_tmp, 5);
  alt.vario = vel_tmp;
  return 1;
}
// END IMU.ino
