//
//  engine.h
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

#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/utility.hpp>

#include "graph.h"
#include "strop.h"
#include "grammar.h"
#include "strop_stream_generator.h"

namespace streamulus
{
    
    class Engine 
        : public EngineApi
        , public boost::noncopyable
    {
    public:
        
        Engine();
        
        
        void AddVertexToGraph(StropPtr strop);
        
        void AddSource(StropPtr strop);        

        bool ReplaceStrop(StropPtr strop, StropPtr new_strop);
        
        void AddEdgeToGraph(BoostGraph::vertex_descriptor source, 
                            BoostGraph::vertex_descriptor target,
                            const StreamPtr& stream);        
        

        void Work();
        
        
        template<typename R, typename Expr>
        const boost::shared_ptr<StropStreamGenerator<R> > Subscribe(Expr const &expr)
        {
            typedef boost::shared_ptr<StropStreamGenerator<R> > ResultType;

            std::cout << "Engine::Parse()" << std::endl;
            boost::proto::display_expr(expr);
            
            // Make sure the expression conforms to our grammar
            BOOST_MPL_ASSERT(( boost::proto::matches<Expr, smls_grammar> ));
            
            // add the expression to the graph
          
            ResultType result = smls_grammar()(expr, this);
            
            StartEngine();
            return result;
        }

        template<typename Expr>
        void Subscribe(Expr const &expr)
        {
            
            std::cout << "Engine::Parse()" << std::endl;
            boost::proto::display_expr(expr);
            
            // Make sure the expression conforms to our grammar
            BOOST_MPL_ASSERT(( boost::proto::matches<Expr, smls_grammar> ));
            
            // add the expression to the graph
            smls_grammar()(expr, this);
            
            StartEngine();
        }

    private:
        
        void StartEngine()
        {
            WriteGraph("/Users/iritkatriel/data/TsGraph.vis");
            ActivateSources();
            Work();            
        }
        
        void ActivateVertex(BoostGraph::vertex_descriptor vertex);
        
        void ActivateVertex(StropPtr strop);
        
        void ActivateSources();        
        

        struct TopologicalSortVisitor : public boost::default_dfs_visitor
        {  // Reset descriptors and recompute topological order labels in the graph:
        public:
            TopologicalSortVisitor(Graph & g, EngineApi* engine)
            : mIndex(boost::num_vertices(g))
            , mGraph(g)
            , mEngine(engine)
            {
            }
            
            void finish_vertex(BoostGraph::vertex_descriptor u, const BoostGraph & g) 
            {
                assert( mIndex > 0);
                mGraph[u]->SetGraph(mEngine, u, mIndex--);
                
                std::cout << "Finish vertex " << u << "  " //  << mGraph[u]->GetName()
                << "  TO=" << mGraph[u]->GetTopSortIndex() << std::endl;
            }
        private:
            size_t mIndex;
            Graph& mGraph;
            EngineApi* mEngine;
        };
        
        void GraphChanged();
        
        typedef long TimestampT;

        struct QueueEntry
        {
            QueueEntry(TimestampT time,
                       size_t top_sort_index, 
                       BoostGraph::vertex_descriptor desc)
            : mTime(time)
            , mTopSortIndex(top_sort_index)
            , mVertexDescriptor(desc)
            {
            }
            
            bool operator<(const QueueEntry& rhs ) const
            {
                // sort by (time, topological order)
                return (this->mTime<rhs.mTime) || 
                    (this->mTime==rhs.mTime && this->mTopSortIndex<rhs.mTopSortIndex);
            }
            
            TimestampT       mTime;
            size_t           mTopSortIndex;
            BoostGraph::vertex_descriptor mVertexDescriptor;
        };
        
        
        
        class VertexPropertyWriter
        {
        public:
            VertexPropertyWriter(Graph& g) : mGraph(g) {}
            
            void operator()(std::ostream& out, const Graph::vertex_descriptor& v) const
            {
                out << "[label=" << mGraph[v]->DisplayName() 
                    << "_Desc" << mGraph[v]->GetDescriptor() 
                    << "_TO" << mGraph[v]->GetTopSortIndex() << "]";
            }
            
        private:
            Graph& mGraph;
        };
        
        void WriteGraph(const std::string& filename);

        std::set<QueueEntry> mQueue;
        TimestampT mCurrentTime;
        bool mWorking;    
        std::vector<StropPtr> mSources;
        
    };
    
} // ns streamulus