//
//  input_stream.h
//  streamulus
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

#include "strop_data_source.h"

namespace streamulus
{
    
    // A convenience utility for defining input streams    
    
    template<typename T>
    struct InputStream
    {
        typedef const boost::shared_ptr<DataSource<T> > stream_type;
        typedef const boost::proto::literal<stream_type> expr_type;
        
        InputStream(const std::string& name)
        : stream(new DataSource<T>(name))
        , literal(boost::proto::lit(stream))
        {
        }
        
        void Put(const T& value)
        {
            stream->Tick(value);
        }
        
        expr_type expr()
        {
            return literal;
        }
        
    private:
        stream_type stream;
        expr_type literal;
    };
    
} // ns streamulus