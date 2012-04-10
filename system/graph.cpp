//
//  graph.cpp
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#include "graph.h"

namespace streamulus
{
    
    StropPtr Graph::operator[](const BoostGraph::vertex_descriptor& d) const
    {
        return boost::get(StropTag(), *this)[d];
    }
    
    StreamPtr Graph::operator[](const BoostGraph::edge_descriptor& d) const
    {
        return boost::get(StreamTag(), *this)[d];
    }	
    
    
} // ns streamulus