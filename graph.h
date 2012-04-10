//
//  graph.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <boost/graph/adjacency_list.hpp>

namespace streamulus
{
    
    struct StropTag { typedef boost::vertex_property_tag kind; };
    struct StreamTag { typedef boost::edge_property_tag kind; };
    
    class StropBase;
    class StreamBase;
    
    typedef boost::shared_ptr<StropBase> StropPtr;
    typedef boost::shared_ptr<StreamBase> StreamPtr;
    
    
    typedef boost::adjacency_list<boost::vecS 
    , boost::vecS
    , boost::bidirectionalS 
    , boost::property<StropTag, StropPtr>
    , boost::property<StreamTag, StreamPtr>
    > BoostGraph;
    
    class Graph : public BoostGraph 
    {
    public:
        typedef BoostGraph type;
        StropPtr operator[](const BoostGraph::vertex_descriptor& d) const;
        StreamPtr operator[](const BoostGraph::edge_descriptor& d) const;
    };
    
    
} // ns streamulus
