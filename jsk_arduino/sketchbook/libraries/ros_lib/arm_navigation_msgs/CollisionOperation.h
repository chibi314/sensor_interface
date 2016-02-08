#ifndef _ROS_arm_navigation_msgs_CollisionOperation_h
#define _ROS_arm_navigation_msgs_CollisionOperation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arm_navigation_msgs
{

  class CollisionOperation : public ros::Msg
  {
    public:
      const char* object1;
      const char* object2;
      float penetration_distance;
      int32_t operation;
      enum { COLLISION_SET_ALL = "all" };
      enum { COLLISION_SET_OBJECTS = "objects" };
      enum { COLLISION_SET_ATTACHED_OBJECTS = "attached" };
      enum { DISABLE = 0 };
      enum { ENABLE = 1 };

    CollisionOperation():
      object1(""),
      object2(""),
      penetration_distance(0),
      operation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_object1 = strlen(this->object1);
      memcpy(outbuffer + offset, &length_object1, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object1, length_object1);
      offset += length_object1;
      uint32_t length_object2 = strlen(this->object2);
      memcpy(outbuffer + offset, &length_object2, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object2, length_object2);
      offset += length_object2;
      offset += serializeAvrFloat64(outbuffer + offset, this->penetration_distance);
      union {
        int32_t real;
        uint32_t base;
      } u_operation;
      u_operation.real = this->operation;
      *(outbuffer + offset + 0) = (u_operation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_operation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_operation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_operation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->operation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_object1;
      memcpy(&length_object1, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object1; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object1-1]=0;
      this->object1 = (char *)(inbuffer + offset-1);
      offset += length_object1;
      uint32_t length_object2;
      memcpy(&length_object2, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object2; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object2-1]=0;
      this->object2 = (char *)(inbuffer + offset-1);
      offset += length_object2;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->penetration_distance));
      union {
        int32_t real;
        uint32_t base;
      } u_operation;
      u_operation.base = 0;
      u_operation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_operation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_operation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_operation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->operation = u_operation.real;
      offset += sizeof(this->operation);
     return offset;
    }

    const char * getType(){ return "arm_navigation_msgs/CollisionOperation"; };
    const char * getMD5(){ return "e0cf3073b26bd86266c918a0c779f8a2"; };

  };

}
#endif