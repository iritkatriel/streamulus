//
//  graph.h
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
