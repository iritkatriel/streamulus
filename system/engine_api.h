//
//  engine_api.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include "graph.h"

namespace streamulus
{
    
    class EngineApi
    {
    public:
        
        virtual ~EngineApi()
        {
        }
        
        virtual void AddVertexToGraph(StropPtr strop)=0;
        virtual void AddSource(StropPtr strop)=0;
        
        template<typename T>
        void Output(BoostGraph::vertex_descriptor source, const T& value)
        {
            BoostGraph::out_edge_iterator it, it_end;
            
            for (boost::tie(it,it_end) = boost::out_edges(source, mGraph); it != it_end; ++it)
            {
                BoostGraph::edge_descriptor edge(*it);
                
                // Put the data on the edge's stream 
                StreamPtr stream(mGraph[edge]);
                dynamic_cast<Stream<T>*>(stream.get())->Append(value);
                
                ActivateVertex(boost::target(edge, mGraph));
            }
            Work();
        }
        
        virtual void ActivateVertex(BoostGraph::vertex_descriptor vertex)=0;
        
        virtual void Work()=0;
        
    protected:
        
        Graph mGraph;
        
    };
    
} // ns streamulus