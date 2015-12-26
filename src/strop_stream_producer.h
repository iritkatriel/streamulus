//
//  strop_stream_generator.h
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

#include "engine.h" 
#include "stream.h" 
#include "strop_base.h" 

#include <boost/make_shared.hpp>
#include <boost/optional.hpp>

namespace streamulus
{
    
    template<typename R> 
    class StropStreamProducer
    : public StropBase
    {
    public:

        using result_type = R;
        
        virtual ~StropStreamProducer() 
        {
        }
        
        void Output(const boost::optional<R>& value)
        {
            if (!GetEngine())
                return;

            if(value) {
                GetEngine()->template Output<R>(mVertexDescriptor, *value);
            }
            mCurrentValue = value;
        }

        using OutputStreamPtr = boost::shared_ptr<Stream<R>>;
        
        OutputStreamPtr MakeOutputStream()
        {
            OutputStreamPtr stream = boost::make_shared< Stream<R> >();
            if (mCurrentValue)
                stream->Append(*mCurrentValue);
            return stream;
        }
        
    private:
        boost::optional<R> mCurrentValue;
    };
    
    
} // ns streamulus