//=================================================================================================
// Copyright (c) 2016, Stefan Kohlbrecher, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Simulation, Systems Optimization and Robotics
//       group, TU Darmstadt nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef FRAMEIDCHANGER_H__
#define FRAMEIDCHANGER_H__

#include <ros/ros.h>


namespace topic_field_tools{

template <typename MessageType>
class FrameIdChanger{
public:

  FrameIdChanger()
  {
    int queue_size = 1;

    nh_ = ros::NodeHandle();
    pnh_ = ros::NodeHandle("~");

    pnh_.param("new_frame_id", new_frame_id_, std::string("INVALID"));


    message_pub_ = nh_.advertise<MessageType>("topic_out", queue_size, false);
    message_sub_ = nh_.subscribe("topic_in", queue_size, &FrameIdChanger::messageCallback, this);
  }

  void messageCallback(const boost::shared_ptr<MessageType>& msg_in)
  {
    MessageType msg_out;
    msg_out = *msg_in;
    msg_out.header.frame_id = new_frame_id_;
    message_pub_.publish(msg_out);
  }


protected:

  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;

  std::string new_frame_id_;

  ros::Subscriber message_sub_;
  ros::Publisher  message_pub_;

};

}

#endif
