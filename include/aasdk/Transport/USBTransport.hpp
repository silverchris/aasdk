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

#include <asio.hpp>
#include <aasdk/Transport/Transport.hpp>
#include <aasdk/USB/IAOAPDevice.hpp>

namespace aasdk
{
namespace transport
{

class USBTransport: public Transport
{
public:
    USBTransport(asio::io_service& ioService, usb::IAOAPDevice::Pointer aoapDevice);

    void stop() override;

private:
    void enqueueReceive(common::DataBuffer buffer) override;
    void enqueueSend(SendQueue::iterator queueElement) override;
    void doSend(SendQueue::iterator queueElement, common::Data::size_type offset);
    void sendHandler(SendQueue::iterator queueElement, common::Data::size_type offset, size_t bytesTransferred);

    usb::IAOAPDevice::Pointer aoapDevice_;

    static constexpr uint32_t cSendTimeoutMs = 10000;
    static constexpr uint32_t cReceiveTimeoutMs = 0;
};

}
}
