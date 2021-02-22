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

#include <aasdk_proto/ControlMessageIdsEnum.pb.h>
#include <aasdk_proto/BluetoothChannelMessageIdsEnum.pb.h>
#include <aasdk_proto/BluetoothPairingRequestMessage.pb.h>
#include <aasdk/Channel/Bluetooth/IBluetoothServiceChannelEventHandler.hpp>
#include <aasdk/Channel/Bluetooth/BluetoothServiceChannel.hpp>
#include <aasdk/Common/Log.hpp>


namespace aasdk
{
namespace channel
{
namespace bluetooth
{

BluetoothServiceChannel::BluetoothServiceChannel(asio::io_service::strand& strand, messenger::IMessenger::Pointer messenger)
    : ServiceChannel(strand, std::move(messenger), messenger::ChannelId::BLUETOOTH)
{

}

void BluetoothServiceChannel::receive(IBluetoothServiceChannelEventHandler::Pointer eventHandler)
{
        AASDK_LOG(info) << "[BluetoothServiceChannel] receive ";

    auto receivePromise = messenger::ReceivePromise::defer(strand_);
    receivePromise->then([this, self = this->shared_from_this(), eventHandler](messenger::Message::Pointer message) {
                           this->messageHandler(std::move(message), eventHandler);},
                         [&](const error::Error &e) { AASDK_LOG(ERROR) << "channel error: " << e.what()
                                                                       << ", channel: " << static_cast<int>(this->getId()) << "\n"; });

    messenger_->enqueueReceive(channelId_, std::move(receivePromise));
}

messenger::ChannelId BluetoothServiceChannel::getId() const
{
    return channelId_;
}

void BluetoothServiceChannel::sendChannelOpenResponse(const proto::messages::ChannelOpenResponse& response, SendPromise::Pointer promise)
{
    AASDK_LOG(info) << "[BluetoothServiceChannel] channel open response ";

    auto message(std::make_shared<messenger::Message>(channelId_, messenger::EncryptionType::ENCRYPTED, messenger::MessageType::CONTROL));
    message->insertPayload(messenger::MessageId(proto::ids::ControlMessage::CHANNEL_OPEN_RESPONSE).getData());
    message->insertPayload(response);

    this->send(std::move(message), std::move(promise));
}

void BluetoothServiceChannel::sendBluetoothPairingResponse(const proto::messages::BluetoothPairingResponse& response, SendPromise::Pointer promise)
{
        AASDK_LOG(info) << "[BluetoothServiceChannel] pairing response ";

    auto message(std::make_shared<messenger::Message>(channelId_, messenger::EncryptionType::ENCRYPTED, messenger::MessageType::SPECIFIC));
    message->insertPayload(messenger::MessageId(proto::ids::BluetoothChannelMessage::PAIRING_RESPONSE).getData());
    message->insertPayload(response);

    this->send(std::move(message), std::move(promise));
}

void BluetoothServiceChannel::messageHandler(messenger::Message::Pointer message, IBluetoothServiceChannelEventHandler::Pointer eventHandler)
{
        AASDK_LOG(info) << "[BluetoothServiceChannel] message handler ";

    messenger::MessageId messageId(message->getPayload());
    common::DataConstBuffer payload(message->getPayload(), messageId.getSizeOf());

    switch(messageId.getId())
    {
    case proto::ids::ControlMessage::CHANNEL_OPEN_REQUEST:
        this->handleChannelOpenRequest(payload, std::move(eventHandler));
        break;
    case proto::ids::BluetoothChannelMessage::PAIRING_REQUEST:
        this->handleBluetoothPairingRequest(payload, std::move(eventHandler));
        break;
    default:
        AASDK_LOG(error) << "[BluetoothServiceChannel] message not handled: " << messageId.getId();
        this->receive(std::move(eventHandler));
        break;
    }
}

void BluetoothServiceChannel::handleChannelOpenRequest(const common::DataConstBuffer& payload, IBluetoothServiceChannelEventHandler::Pointer eventHandler)
{
        AASDK_LOG(info) << "[BluetoothServiceChannel] channel open request ";

    proto::messages::ChannelOpenRequest request;
    if(request.ParseFromArray(payload.cdata, payload.size))
    {
        eventHandler->onChannelOpenRequest(request);
    }
    else
    {
        eventHandler->onChannelError(error::Error(error::ErrorCode::PARSE_PAYLOAD));
    }
}

void BluetoothServiceChannel::handleBluetoothPairingRequest(const common::DataConstBuffer& payload, IBluetoothServiceChannelEventHandler::Pointer eventHandler)
{
        AASDK_LOG(info) << "[BluetoothServiceChannel] pairing request ";

    proto::messages::BluetoothPairingRequest request;
    if(request.ParseFromArray(payload.cdata, payload.size))
    {
        eventHandler->onBluetoothPairingRequest(request);
    }
    else
    {
        eventHandler->onChannelError(error::Error(error::ErrorCode::PARSE_PAYLOAD));
    }
}

}
}
}
