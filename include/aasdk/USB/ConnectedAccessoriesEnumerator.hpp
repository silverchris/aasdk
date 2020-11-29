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
#include <aasdk/USB/IUSBWrapper.hpp>
#include <aasdk/USB/IAccessoryModeQueryChainFactory.hpp>
#include <aasdk/USB/IConnectedAccessoriesEnumerator.hpp>

namespace aasdk
{
namespace usb
{

class ConnectedAccessoriesEnumerator: public IConnectedAccessoriesEnumerator, public std::enable_shared_from_this<ConnectedAccessoriesEnumerator>
{
public:
    ConnectedAccessoriesEnumerator(IUSBWrapper& usbWrapper, asio::io_service& ioService, IAccessoryModeQueryChainFactory& queryChainFactory);

    void enumerate(Promise::Pointer promise) override;
    void cancel() override;

private:
    using std::enable_shared_from_this<ConnectedAccessoriesEnumerator>::shared_from_this;
    void queryNextDevice();
    DeviceHandle getNextDeviceHandle();
    void reset();

    IUSBWrapper& usbWrapper_;
    asio::io_service::strand strand_;
    IAccessoryModeQueryChainFactory& queryChainFactory_;
    IAccessoryModeQueryChain::Pointer queryChain_;
    Promise::Pointer promise_;
    DeviceListHandle deviceListHandle_;
    DeviceList::iterator actualDeviceIter_;
};

}
}
