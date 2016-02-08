#ifndef _ROS_jsk_footstep_msgs_Footstep_h
#define _ROS_jsk_footstep_msgs_Footstep_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "ros/duration.h"
#include "geometry_msgs/Vector3.h"

namespace jsk_footstep_msgs
{

  class Footstep : public ros::Msg
  {
    public:
      uint8_t leg;
      geometry_msgs::Pose pose;
      ros::Duration duration;
      uint32_t footstep_group;
      geometry_msgs::Vector3 dimensions;
      float swing_height;
      float cost;
      enum { RIGHT = 2 };
      enum { LEFT = 1 };
      enum { REJECTED = 3 };
      enum { APPROVED = 4 };

    Footstep():
      leg(0),
      pose(),
      duration(),
      footstep_group(0),
      dimensions(),
      swing_height(0),
      cost(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->leg >> (8 * 0)) & 0xFF;
      offset += sizeof(this->leg);
      offset += this->pose.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->duration.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration.sec);
      *(outbuffer + offset + 0) = (this->duration.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration.nsec);
      *(outbuffer + offset + 0) = (this->footstep_group >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->footstep_group >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->footstep_group >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->footstep_group >> (8 * 3)) & 0xFF;
      offset += sizeof(this->footstep_group);
      offset += this->dimensions.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_swing_height;
      u_swing_height.real = this->swing_height;
      *(outbuffer + offset + 0) = (u_swing_height.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_swing_height.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_swing_height.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_swing_height.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->swing_height);
      union {
        float real;
        uint32_t base;
      } u_cost;
      u_cost.real = this->cost;
      *(outbuffer + offset + 0) = (u_cost.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cost.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cost.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cost.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cost);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->leg =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->leg);
      offset += this->pose.deserialize(inbuffer + offset);
      this->duration.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration.sec);
      this->duration.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration.nsec);
      this->footstep_group =  ((uint32_t) (*(inbuffer + offset)));
      this->footstep_group |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->footstep_group |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->footstep_group |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->footstep_group);
      offset += this->dimensions.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_swing_height;
      u_swing_height.base = 0;
      u_swing_height.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_swing_height.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_swing_height.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_swing_height.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->swing_height = u_swing_height.real;
      offset += sizeof(this->swing_height);
      union {
        float real;
        uint32_t base;
      } u_cost;
      u_cost.base = 0;
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cost = u_cost.real;
      offset += sizeof(this->cost);
     return offset;
    }

    const char * getType(){ return "jsk_footstep_msgs/Footstep"; };
    const char * getMD5(){ return "e9cf5aea8acd6e0d8c6251192b89a665"; };

  };

}
#endif