//
//  stream.h
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

#pragma once

#include <deque>
#include <boost/circular_buffer.hpp>

#include "stream_base.h"

namespace streamulus
{
    
    template<typename T>
    class Stream : public StreamBase
    {
    public:	
        
        
        Stream()
		: mHistory(1)
        {
        }
        
        Stream(size_t history)
		: mHistory(history)
        {
            assert(history>0);
        }
                
        void Append(const T& item)
        {
            mBuffer.push_back(item);
        }
        
        bool Empty()
        {
            return mBuffer.empty();
        }
        
        bool IsValid()
        {
            return !(mBuffer.empty() && mHistory.empty());
        }
        
        const T& Current()
        {
            if (!mBuffer.empty())
                return Top();

            assert(! mHistory.empty());
            
            // No new data - return last
            return mHistory.back();
        }
        
        const T& Top()
        {
            assert(!Empty());
            return mBuffer.front();
        }
        
        void Pop(bool check_not_empty = false)
        {
            assert(!(check_not_empty && Empty()));
            if (Empty())
                return;
            mHistory.push_back(Top());
            mBuffer.pop_front();
        }
        
    private:
        std::deque<T> mBuffer;
        boost::circular_buffer<T> mHistory;
    };
    
} // ns streamulus