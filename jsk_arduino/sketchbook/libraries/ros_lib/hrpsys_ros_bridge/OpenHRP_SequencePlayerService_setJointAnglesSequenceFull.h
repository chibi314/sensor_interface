#ifndef _ROS_SERVICE_OpenHRP_SequencePlayerService_setJointAnglesSequenceFull_h
#define _ROS_SERVICE_OpenHRP_SequencePlayerService_setJointAnglesSequenceFull_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Float64MultiArray.h"

namespace hrpsys_ros_bridge
{

static const char OPENHRP_SEQUENCEPLAYERSERVICE_SETJOINTANGLESSEQUENCEFULL[] = "hrpsys_ros_bridge/OpenHRP_SequencePlayerService_setJointAnglesSequenceFull";

  class OpenHRP_SequencePlayerService_setJointAnglesSequenceFullRequest : public ros::Msg
  {
    public:
      std_msgs::Float64MultiArray jvss;
      std_msgs::Float64MultiArray vels;
      std_msgs::Float64MultiArray torques;
      std_msgs::Float64MultiArray poss;
      std_msgs::Float64MultiArray rpys;
      std_msgs::Float64MultiArray accs;
      std_msgs::Float64MultiArray zmps;
      std_msgs::Float64MultiArray wrenchs;
      std_msgs::Float64MultiArray optionals;
      uint8_t tms_length;
      float st_tms;
      float * tms;

    OpenHRP_SequencePlayerService_setJointAnglesSequenceFullRequest():
      jvss(),
      vels(),
      torques(),
      poss(),
      rpys(),
      accs(),
      zmps(),
      wrenchs(),
      optionals(),
      tms_length(0), tms(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->jvss.serialize(outbuffer + offset);
      offset += this->vels.serialize(outbuffer + offset);
      offset += this->torques.serialize(outbuffer + offset);
      offset += this->poss.serialize(outbuffer + offset);
      offset += this->rpys.serialize(outbuffer + offset);
      offset += this->accs.serialize(outbuffer + offset);
      offset += this->zmps.serialize(outbuffer + offset);
      offset += this->wrenchs.serialize(outbuffer + offset);
      offset += this->optionals.serialize(outbuffer + offset);
      *(outbuffer + offset++) = tms_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < tms_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->tms[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->jvss.deserialize(inbuffer + offset);
      offset += this->vels.deserialize(inbuffer + offset);
      offset += this->torques.deserialize(inbuffer + offset);
      offset += this->poss.deserialize(inbuffer + offset);
      offset += this->rpys.deserialize(inbuffer + offset);
      offset += this->accs.deserialize(inbuffer + offset);
      offset += this->zmps.deserialize(inbuffer + offset);
      offset += this->wrenchs.deserialize(inbuffer + offset);
      offset += this->optionals.deserialize(inbuffer + offset);
      uint8_t tms_lengthT = *(inbuffer + offset++);
      if(tms_lengthT > tms_length)
        this->tms = (float*)realloc(this->tms, tms_lengthT * sizeof(float));
      offset += 3;
      tms_length = tms_lengthT;
      for( uint8_t i = 0; i < tms_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_tms));
        memcpy( &(this->tms[i]), &(this->st_tms), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return OPENHRP_SEQUENCEPLAYERSERVICE_SETJOINTANGLESSEQUENCEFULL; };
    const char * getMD5(){ return "27969734fb24cec0718f6a9e8c7b6b72"; };

  };

  class OpenHRP_SequencePlayerService_setJointAnglesSequenceFullResponse : public ros::Msg
  {
    public:
      bool operation_return;

    OpenHRP_SequencePlayerService_setJointAnglesSequenceFullResponse():
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

    const char * getType(){ return OPENHRP_SEQUENCEPLAYERSERVICE_SETJOINTANGLESSEQUENCEFULL; };
    const char * getMD5(){ return "8dd59ee39c15084c92106411b8c3e8fc"; };

  };

  class OpenHRP_SequencePlayerService_setJointAnglesSequenceFull {
    public:
    typedef OpenHRP_SequencePlayerService_setJointAnglesSequenceFullRequest Request;
    typedef OpenHRP_SequencePlayerService_setJointAnglesSequenceFullResponse Response;
  };

}
#endif
