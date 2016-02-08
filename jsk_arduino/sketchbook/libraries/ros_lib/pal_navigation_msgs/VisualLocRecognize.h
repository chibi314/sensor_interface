#ifndef _ROS_SERVICE_VisualLocRecognize_h
#define _ROS_SERVICE_VisualLocRecognize_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

namespace pal_navigation_msgs
{

static const char VISUALLOCRECOGNIZE[] = "pal_navigation_msgs/VisualLocRecognize";

  class VisualLocRecognizeRequest : public ros::Msg
  {
    public:

    VisualLocRecognizeRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return VISUALLOCRECOGNIZE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class VisualLocRecognizeResponse : public ros::Msg
  {
    public:
      bool success;
      float confidence;
      geometry_msgs::PoseWithCovarianceStamped estimatedPose;

    VisualLocRecognizeResponse():
      success(0),
      confidence(0),
      estimatedPose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      offset += serializeAvrFloat64(outbuffer + offset, this->confidence);
      offset += this->estimatedPose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->confidence));
      offset += this->estimatedPose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return VISUALLOCRECOGNIZE; };
    const char * getMD5(){ return "af944bb003989194ffe33120c472f3ed"; };

  };

  class VisualLocRecognize {
    public:
    typedef VisualLocRecognizeRequest Request;
    typedef VisualLocRecognizeResponse Response;
  };

}
#endif
