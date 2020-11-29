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

#include <gmock/gmock.h>
#include <aasdk/Transport/ITransport.hpp>


namespace aasdk
{
namespace transport
{
namespace ut
{

class TransportMock: public ITransport
{
public:
    MOCK_METHOD2(receive, void(size_t size, ReceivePromise::Pointer promise));
    MOCK_METHOD2(send, void(common::Data data, SendPromise::Pointer promise));
    MOCK_METHOD0(stop, void());
};

}
}
}
