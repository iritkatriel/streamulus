//
//  streamulus.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include "engine.h"
#include "strop_data_source.h"
#include "operators.h"
#include "streamify.h"
#include "strop_const.h"


namespace streamulus
{
    typedef Engine Streamulus;

    // A convenience utility for defining input streams    
    
    template<typename T>
    struct InputStream
    {
        typedef const boost::shared_ptr<DataSource<T> > stream_type;
        typedef const boost::proto::literal<stream_type> literal_type;
        
        InputStream(const std::string& name)
        : stream(new DataSource<T>(name))
        , literal(boost::proto::lit(stream))
        {
        }
        
        stream_type stream;
        literal_type literal;
    };
    
} // ns streamulus
