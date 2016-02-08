#ifndef _ROS_SERVICE_OpenHRP_ServoControllerService_getJointAngle_h
#define _ROS_SERVICE_OpenHRP_ServoControllerService_getJointAngle_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace hrpsys_ros_bridge
{

static const char OPENHRP_SERVOCONTROLLERSERVICE_GETJOINTANGLE[] = "hrpsys_ros_bridge/OpenHRP_ServoControllerService_getJointAngle";

  class OpenHRP_ServoControllerService_getJointAngleRequest : public ros::Msg
  {
    public:
      int16_t id;

    OpenHRP_ServoControllerService_getJointAngleRequest():
      id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->id = u_id.real;
      offset += sizeof(this->id);
     return offset;
    }

    const char * getType(){ return OPENHRP_SERVOCONTROLLERSERVICE_GETJOINTANGLE; };
    const char * getMD5(){ return "83303829ff5167a112112db2bf7b7905"; };

  };

  class OpenHRP_ServoControllerService_getJointAngleResponse : public ros::Msg
  {
    public:
      bool operation_return;
      float jv;

    OpenHRP_ServoControllerService_getJointAngleResponse():
      operation_return(0),
      jv(0)
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
      offset += serializeAvrFloat64(outbuffer + offset, this->jv);
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
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->jv));
     return offset;
    }

    const char * getType(){ return OPENHRP_SERVOCONTROLLERSERVICE_GETJOINTANGLE; };
    const char * getMD5(){ return "d7490a2e887a3ee0e8b08e935c1c3a96"; };

  };

  class OpenHRP_ServoControllerService_getJointAngle {
    public:
    typedef OpenHRP_ServoControllerService_getJointAngleRequest Request;
    typedef OpenHRP_ServoControllerService_getJointAngleResponse Response;
  };

}
#endif
