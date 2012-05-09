//
//  input_stream.h
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
        typedef const boost::shared_ptr<DataSource<T> > strop_type;
        typedef const boost::proto::literal<strop_type> expr_type;
        
        InputStream(const std::string& name)
        : mStrop(new DataSource<T>(name))
        , mLiteral(boost::proto::lit(mStrop))
        {
        }
        
        void Put(const T& value)
        {
            mStrop->Tick(value);
        }
        
        expr_type expr()
        {
            return mLiteral;
        }
        
        strop_type strop()
        {
            return mStrop;
        }
        
    private:
        strop_type mStrop;
        expr_type mLiteral;
    };
    
} // ns streamulus