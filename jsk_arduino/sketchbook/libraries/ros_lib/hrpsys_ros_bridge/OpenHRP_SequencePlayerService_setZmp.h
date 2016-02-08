#ifndef _ROS_SERVICE_OpenHRP_SequencePlayerService_setZmp_h
#define _ROS_SERVICE_OpenHRP_SequencePlayerService_setZmp_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hrpsys_ros_bridge
{

static const char OPENHRP_SEQUENCEPLAYERSERVICE_SETZMP[] = "hrpsys_ros_bridge/OpenHRP_SequencePlayerService_setZmp";

  class OpenHRP_SequencePlayerService_setZmpRequest : public ros::Msg
  {
    public:
      uint8_t zmp_length;
      float st_zmp;
      float * zmp;
      float tm;

    OpenHRP_SequencePlayerService_setZmpRequest():
      zmp_length(0), zmp(NULL),
      tm(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = zmp_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < zmp_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->zmp[i]);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->tm);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t zmp_lengthT = *(inbuffer + offset++);
      if(zmp_lengthT > zmp_length)
        this->zmp = (float*)realloc(this->zmp, zmp_lengthT * sizeof(float));
      offset += 3;
      zmp_length = zmp_lengthT;
      for( uint8_t i = 0; i < zmp_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_zmp));
        memcpy( &(this->zmp[i]), &(this->st_zmp), sizeof(float));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->tm));
     return offset;
    }

    const char * getType(){ return OPENHRP_SEQUENCEPLAYERSERVICE_SETZMP; };
    const char * getMD5(){ return "ccc8d359d012f5f55e6be510fbec1781"; };

  };

  class OpenHRP_SequencePlayerService_setZmpResponse : public ros::Msg
  {
    public:
      bool operation_return;

    OpenHRP_SequencePlayerService_setZmpResponse():
      operation_return(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_operation_return;
      u_operation_return.real = this->operation_return;
      *(outbuffer + offset + 0) = (u_operation_return.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->operation_return);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_operation_return;
      u_operation_return.base = 0;
      u_operation_return.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->operation_return = u_operation_return.real;
      offset += sizeof(this->operation_return);
     return offset;
    }

    const char * getType(){ return OPENHRP_SEQUENCEPLAYERSERVICE_SETZMP; };
    const char * getMD5(){ return "8dd59ee39c15084c92106411b8c3e8fc"; };

  };

  class OpenHRP_SequencePlayerService_setZmp {
    public:
    typedef OpenHRP_SequencePlayerService_setZmpRequest Request;
    typedef OpenHRP_SequencePlayerService_setZmpResponse Response;
  };

}
#endif
