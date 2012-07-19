//
// strop_sliding_window.h
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

#include <boost/circular_buffer.hpp>

namespace streamulus 
{

    enum WindowInOut { DATA_IN, DATA_OUT };
    
    template<typename T>
    struct WindowUpdateType
    {
        typedef std::pair<WindowInOut,T> type;
    };

    template<typename T>
    struct WindowBaseType;
    
    template<typename T>
    struct WindowBaseType<std::pair<WindowInOut,T> >
    {
        typedef T type;
    };
    
    template<typename T>
    class Window : public Strop<typename WindowUpdateType<T>::type(T)>
    {
    public:
        typedef typename WindowUpdateType<T>::type R;
        
        Window(size_t size)
            : mBuffer(size)
        {
        }
        
        virtual void Work()
        {
            Stream<T>* const input(Strop<R(T)>::template Input<T,0>());
            
            assert(input->IsValid());
            
            while (input->HasMore())
            {
                if (mBuffer.reserve() == 0)
                    StropStreamProducer<R>::Output(std::make_pair(DATA_OUT,mBuffer.front()));                       

                const T& value(input->Current());
                mBuffer.push_back(value);
                StropStreamProducer<R>::Output(std::make_pair(DATA_IN,value));   
            }
        }
        
    private:
        boost::circular_buffer<T> mBuffer;  
    };
    
} // ns streamulus