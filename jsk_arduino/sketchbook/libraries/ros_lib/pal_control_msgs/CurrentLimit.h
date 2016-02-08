#ifndef _ROS_SERVICE_CurrentLimit_h
#define _ROS_SERVICE_CurrentLimit_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pal_control_msgs
{

static const char CURRENTLIMIT[] = "pal_control_msgs/CurrentLimit";

  class CurrentLimitRequest : public ros::Msg
  {
    public:
      const char* actuator_name;
      float current_limit;

    CurrentLimitRequest():
      actuator_name(""),
      current_limit(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_actuator_name = strlen(this->actuator_name);
      memcpy(outbuffer + offset, &length_actuator_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->actuator_name, length_actuator_name);
      offset += length_actuator_name;
      offset += serializeAvrFloat64(outbuffer + offset, this->current_limit);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_actuator_name;
      memcpy(&length_actuator_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_actuator_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_actuator_name-1]=0;
      this->actuator_name = (char *)(inbuffer + offset-1);
      offset += length_actuator_name;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->current_limit));
     return offset;
    }

    const char * getType(){ return CURRENTLIMIT; };
    const char * getMD5(){ return "6d1326759cec3fceb10a88d2834f6fba"; };

  };

  class CurrentLimitResponse : public ros::Msg
  {
    public:
      const char* status;

    CurrentLimitResponse():
      status("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_status = strlen(this->status);
      memcpy(outbuffer + offset, &length_status, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_status;
      memcpy(&length_status, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
     return offset;
    }

    const char * getType(){ return CURRENTLIMIT; };
    const char * getMD5(){ return "4fe5af303955c287688e7347e9b00278"; };

  };

  class CurrentLimit {
    public:
    typedef CurrentLimitRequest Request;
    typedef CurrentLimitResponse Response;
  };

}
#endif
