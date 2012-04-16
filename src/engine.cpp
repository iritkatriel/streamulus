//
//  engine.cpp
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

#include <iostream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>

#include "engine.h"


namespace streamulus
{
    
    Engine::Engine()
    : mWorking(false)
    , mCurrentTime(0)
    {
    };
    
    
    void Engine::AddVertexToGraph(StropPtr strop)
    {
        boost::add_vertex(strop, mGraph);
        GraphChanged();
    }
    
    void Engine::AddSource(StropPtr strop)
    {
        mSources.push_back(strop);
    }
    
    
    void Engine::AddEdgeToGraph(BoostGraph::vertex_descriptor source, 
                                BoostGraph::vertex_descriptor target,
                                const StreamPtr& stream)
    {
        Graph::edge_descriptor desc = boost::add_edge(source, target, stream, mGraph).first;
        GraphChanged();
    }
    
    
    void Engine::Work()
    {
        if (mWorking)
            return;
        mWorking = true;
        
        
        std::cout << "Work called. mQueue.size() = " << mQueue.size() << std::endl;
        while (!mQueue.empty())
        {
            std::set<QueueEntry>::iterator it = mQueue.begin();
            mCurrentTime = std::max(mCurrentTime,it->mTime);
            
            StropPtr strop(mGraph[it->mVertexDescriptor]);
            if (strop->Work())
            {
                // activate successors
                BoostGraph::out_edge_iterator out_it, out_it_end;
                for (boost::tie(out_it, out_it_end) = boost::out_edges(it->mVertexDescriptor, mGraph); 
                     out_it != out_it_end; 
                     ++out_it )
                {
                    BoostGraph::edge_descriptor edge(*out_it);
                    BoostGraph::vertex_descriptor target(boost::target(edge,mGraph));
                    ActivateVertex(mGraph[target]);
                }
            }
            strop->SetIsActive(false);
            mQueue.erase(it);
        }
        mWorking = false;
    }
    
    
    void Engine::ActivateVertex(BoostGraph::vertex_descriptor vertex)
    {
        ActivateVertex(mGraph[vertex]);
    }
    
    void Engine::ActivateVertex(StropPtr strop)
    {
        if (strop->IsActive())
            return;
        mQueue.insert(QueueEntry(mCurrentTime++, strop->GetTopSortIndex(), strop->Descriptor()));
        strop->SetIsActive(true);
    }
    
    void Engine::ActivateSources()
    {
        std::cout << "Activate sources: mSources.size() = " << mSources.size() << std::endl;
        for (std::vector<StropPtr>::iterator it = mSources.begin(); it != mSources.end(); ++it)
            ActivateVertex(*it);
    }
    
    
    void Engine::GraphChanged()
    {
        TopologicalSortVisitor vis(mGraph, this);
        boost::depth_first_search(mGraph, boost::visitor(vis));
    }
    
    void Engine::WriteGraph(const std::string& filename)
    {
        std::cout << "Writing graph to " << filename << std::endl;
        std::ofstream file;
        file.open (filename.c_str());
        boost::write_graphviz(file, mGraph, VertexPropertyWriter(mGraph));
        file.close();
    }
    
} // ns streamulus