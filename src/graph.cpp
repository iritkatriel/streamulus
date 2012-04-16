//
//  graph.cpp
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