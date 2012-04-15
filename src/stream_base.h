//
//  stream_base.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include "graph.h"

namespace streamulus
{
    class StreamBase 
    {
    public:
        StreamBase()
        : mGraph(NULL)
        {
        }
        
        virtual ~StreamBase()
        {
        }
        
        const Graph::edge_descriptor& Descriptor() const
        {
            return mEdgeDescriptor;
        }
        
        void SetGraph(const Graph::edge_descriptor& desc, Graph* g) 
        {
            mGraph = g;
            mEdgeDescriptor = desc;
        }
        
    private:
        Graph* mGraph;  // no ownership. do not delete.
        Graph::edge_descriptor mEdgeDescriptor;
    };
    
} // ns streamulus