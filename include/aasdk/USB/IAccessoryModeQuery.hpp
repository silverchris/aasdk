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
#include <asio.hpp>
#include <libusb.h>
#include <aasdk/IO/Promise.hpp>
#include <aasdk/USB/IUSBEndpoint.hpp>


namespace aasdk
{
namespace usb
{

class IAccessoryModeQuery
{
public:
    typedef std::shared_ptr<IAccessoryModeQuery> Pointer;
    typedef io::Promise<IUSBEndpoint::Pointer> Promise;

    IAccessoryModeQuery() = default;
    virtual ~IAccessoryModeQuery() = default;

    virtual void start(Promise::Pointer promise) = 0;
    virtual void cancel() = 0;
};

}
}
