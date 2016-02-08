#ifndef _ROS_pr2_controllers_msgs_Pr2GripperCommandResult_h
#define _ROS_pr2_controllers_msgs_Pr2GripperCommandResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pr2_controllers_msgs
{

  class Pr2GripperCommandResult : public ros::Msg
  {
    public:
      float position;
      float effort;
      bool stalled;
      bool reached_goal;

    Pr2GripperCommandResult():
      position(0),
      effort(0),
      stalled(0),
      reached_goal(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->position);
      offset += serializeAvrFloat64(outbuffer + offset, this->effort);
      union {
        bool real;
        uint8_t base;
      } u_stalled;
      u_stalled.real = this->stalled;
      *(outbuffer + offset + 0) = (u_stalled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->stalled);
      union {
        bool real;
        uint8_t base;
      } u_reached_goal;
      u_reached_goal.real = this->reached_goal;
      *(outbuffer + offset + 0) = (u_reached_goal.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->reached_goal);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->effort));
      union {
        bool real;
        uint8_t base;
      } u_stalled;
      u_stalled.base = 0;
      u_stalled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->stalled = u_stalled.real;
      offset += sizeof(this->stalled);
      union {
        bool real;
        uint8_t base;
      } u_reached_goal;
      u_reached_goal.base = 0;
      u_reached_goal.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->reached_goal = u_reached_goal.real;
      offset += sizeof(this->reached_goal);
     return offset;
    }

    const char * getType(){ return "pr2_controllers_msgs/Pr2GripperCommandResult"; };
    const char * getMD5(){ return "e4cbff56d3562bcf113da5a5adeef91f"; };

  };

}
#endif