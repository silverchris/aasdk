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

#include <aasdk/USB/AccessoryModeQuery.hpp>


namespace aasdk
{
namespace usb
{

class AccessoryModeStartQuery: public AccessoryModeQuery, public std::enable_shared_from_this<AccessoryModeStartQuery>
{
public:
    AccessoryModeStartQuery(asio::io_service& ioService, IUSBWrapper& usbWrapper, IUSBEndpoint::Pointer usbEndpoint);
    void start(Promise::Pointer promise) override;

private:
    using std::enable_shared_from_this<AccessoryModeStartQuery>::shared_from_this;

    static constexpr uint32_t ACC_REQ_START = 53;
};

}
}
