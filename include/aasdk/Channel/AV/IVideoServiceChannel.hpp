/*
*  This file is part of aasdk library project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  aasdk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  aasdk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with aasdk. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>
#include <aasdk_proto/AVChannelSetupResponseMessage.pb.h>
#include <aasdk_proto/VideoFocusIndicationMessage.pb.h>
#include <aasdk_proto/AVMediaAckIndicationMessage.pb.h>
#include <aasdk_proto/ChannelOpenResponseMessage.pb.h>
#include <aasdk/Messenger/ChannelId.hpp>
#include <aasdk/Channel/Promise.hpp>
#include <aasdk/Channel/AV/IVideoServiceChannelEventHandler.hpp>


namespace aasdk::channel::av {

class IVideoServiceChannel {
 public:
  typedef std::shared_ptr<IVideoServiceChannel> Pointer;

  IVideoServiceChannel() = default;
  virtual ~IVideoServiceChannel() = default;

    virtual void receive(IVideoServiceChannelEventHandler::Pointer eventHandler) = 0;
    virtual void sendChannelOpenResponse(const proto::messages::ChannelOpenResponse& response, SendPromise::Pointer promise) = 0;
    virtual void sendAVChannelSetupResponse(const proto::messages::AVChannelSetupResponse& response, SendPromise::Pointer promise) = 0;
    virtual void sendVideoFocusIndication(const proto::messages::VideoFocusIndication& indication, SendPromise::Pointer promise) = 0;
    virtual void sendAVMediaAckIndication(const proto::messages::AVMediaAckIndication& indication, SendPromise::Pointer promise) = 0;
    virtual messenger::ChannelId getId() const = 0;
};

}
