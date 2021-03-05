#ifndef _ROS_rosserial_Servo_msg_h
#define _ROS_rosserial_Servo_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_arduino
{

  class Servo_msg : public ros::Msg
  {
    public:
      typedef uint16_t _x_type;
      _x_type x;
      typedef uint16_t _y_type;
      _y_type y;
      

    Servo_msg():
      x(0),
      y(0),
     
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->x >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->x >> (8 * 1)) & 0xFF;
      offset += sizeof(this->x);
      *(outbuffer + offset + 0) = (this->y >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y >> (8 * 1)) & 0xFF;
      offset += sizeof(this->y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->x =  ((uint16_t) (*(inbuffer + offset)));
      this->x |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->x);
      this->y =  ((uint16_t) (*(inbuffer + offset)));
      this->y |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->y);
     return offset;
    }

    const char * getType(){ return "rosserial_arduino/Adc"; };
    const char * getMD5(){ return "6d7853a614e2e821319068311f2af25b"; };

  };

}
#endif