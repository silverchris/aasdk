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

#include <list>
#include <queue>
#include <asio.hpp>
#include <aasdk/Transport/ITransport.hpp>
#include <aasdk/Transport/DataSink.hpp>

namespace aasdk
{
namespace transport
{

class Transport: public ITransport, public std::enable_shared_from_this<Transport>
{
public:
    explicit Transport(asio::io_service& ioService);

    void receive(size_t size, ReceivePromise::Pointer promise) override;
    void send(common::Data data, SendPromise::Pointer promise) override;

private:
    Transport(const Transport&) = delete;

protected:
    typedef std::list<std::pair<size_t, ReceivePromise::Pointer>> ReceiveQueue;
    typedef std::list<std::pair<common::Data, SendPromise::Pointer>> SendQueue;

    using std::enable_shared_from_this<Transport>::shared_from_this;
    void receiveHandler(size_t bytesTransferred);
    void distributeReceivedData();
    void rejectReceivePromises(const error::Error& e);

    virtual void enqueueReceive(common::DataBuffer buffer) = 0;
    virtual void enqueueSend(SendQueue::iterator queueElement) = 0;

    DataSink receivedDataSink_;

    asio::io_service::strand receiveStrand_;
    ReceiveQueue receiveQueue_;

    asio::io_service::strand sendStrand_;
    SendQueue sendQueue_;
};

}
}
