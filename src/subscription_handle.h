//
//  subscription_handle.h
//
// Streamulus Copyright (c) 2012 Irit Katriel. All rights reserved.
//
// This file is part of Streamulus.
// 
// Streamulus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Streamulus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Streamulus.  If not, see <http://www.gnu.org/licenses/>.
//

namespace streamulus {
    
template<typename T>
struct SubscriptionHandle
{
    typedef T type;    
    typedef const boost::shared_ptr<StropStreamGenerator<T> > StropType;
    typedef const boost::proto::literal<StropType> expr_type;
    
    SubscriptionHandle(StropType s)
    : strop(s)
    {
        std::cout << "TYPE OF s: " << typeid(s).name() << std::endl;
    }
    
    expr_type expr()
    {
        return proto::lit(strop);        
    }
    
    StropType strop;
};

} // ns streamulus