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

#include <aasdk/TCP/TCPEndpoint.hpp>
#include <utility>


namespace aasdk
{
namespace tcp
{

TCPEndpoint::TCPEndpoint(ITCPWrapper& tcpWrapper, SocketPointer socket)
    : tcpWrapper_(tcpWrapper)
    , socket_(std::move(socket))
{

}

void TCPEndpoint::send(common::DataConstBuffer buffer, Promise::Pointer promise)
{
    tcpWrapper_.asyncWrite(*socket_, std::move(buffer),
                           [this, self = this->shared_from_this(), promise](const asio::error_code& ec, size_t bytesTransferred){asyncOperationHandler(ec, bytesTransferred, std::move(promise));});
}

void TCPEndpoint::receive(common::DataBuffer buffer, Promise::Pointer promise)
{
    tcpWrapper_.asyncRead(*socket_, std::move(buffer),
                          [this, self = this->shared_from_this(), promise](const asio::error_code& ec, size_t bytesTransferred){asyncOperationHandler(ec, bytesTransferred, std::move(promise));});
}

void TCPEndpoint::stop()
{
    tcpWrapper_.close(*socket_);
}

void TCPEndpoint::asyncOperationHandler(const asio::error_code& ec, size_t bytesTransferred, Promise::Pointer promise)
{
    if(!ec)
    {
        promise->resolve(bytesTransferred);
    }
    else
    {
        auto error = ec == asio::error::basic_errors::operation_aborted ? error::Error(error::ErrorCode::OPERATION_ABORTED) : error::Error(error::ErrorCode::TCP_TRANSFER, static_cast<uint32_t>(ec.value()));
        promise->reject(error);
    }
}

}
}
