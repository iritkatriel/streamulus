//
//  stream.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
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
        
        virtual ~Stream()
        {
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
        
        bool Current(T& value)
        {
            if (!mBuffer.empty())
            {
                value = Top();
                Pop();
                return true;
            }
            // No new data - return last (if exists)
            if (mHistory.empty())
                return false;
            
            value = mHistory.back();
            return true;
        }
        
        const T& Top()
        {
            assert(!Empty());
            return mBuffer.front();
        }
        
        void Pop()
        {
            assert(!Empty());
            mHistory.push_back(Top());
            mBuffer.pop_front();
        }
        
    private:
        std::deque<T> mBuffer;
        boost::circular_buffer<T> mHistory;
    };
    
} // ns streamulus