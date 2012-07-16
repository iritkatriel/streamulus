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

#include "graph.h"
#include "strop.h"
#include "grammar.h"
#include "strop_stream_generator.h"
#include "subscription.h"

#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/utility.hpp>

#include <iostream>

namespace streamulus
{
    
    class Engine 
        : public EngineApi
        , public boost::noncopyable
    {
    public:
        
        Engine()
            : mWorking(false)
            , mCurrentTime(0)
            , mVerbose(false)
        {
        };
        
        
        void AddVertexToGraph(const StropPtr& strop)
        {
            boost::add_vertex(strop, mGraph);
            GraphChanged();
        }
        
        void AddSource(const StropPtr& strop)
        {
            mSources.push_back(strop);
        }
        
        bool ReplaceStrop(const StropPtr& strop, const StropPtr& new_strop)
        {
            if (strop->GetEngine() != this)
                return false;
            
            new_strop->SetGraph(strop->GetEngine(), 
                                strop->GetDescriptor(), 
                                strop->GetTopSortIndex());
            
            mGraph[strop->GetDescriptor()] = new_strop;
            
            strop->SetGraph(NULL, 0, 0); 
            return true;
        }
        
        void AddEdgeToGraph(const BoostGraph::vertex_descriptor& source, 
                                    const BoostGraph::vertex_descriptor& target,
                                    const StreamPtr& stream)
        {
            Graph::edge_descriptor desc = boost::add_edge(source, target, stream, mGraph).first;
            GraphChanged();
        }
        
        
        void Work()
        {
            if (mWorking)
                return;
            mWorking = true;
            
            
            // std::cout << "Work called. mQueue.size() = " << mQueue.size() << std::endl;
            while (!mQueue.empty())
            {
                std::set<QueueEntry>::iterator it = mQueue.begin();
                mCurrentTime = std::max(mCurrentTime,it->mTime);
                
                StropPtr strop(mGraph[it->mVertexDescriptor]);
                strop->Work();
                strop->SetIsActive(false);
                mQueue.erase(it);
            }
            mWorking = false;
        }
        
        inline bool IsVerbose()
        {
            return mVerbose;
        }

        template<typename Expr>
        struct ExpressionResultType
        {
            // Get the type of the strop created by the expression
            typedef typename boost::result_of<smls_grammar(const Expr&, Engine*)>::type result_strop_type;
            // Extract the output type
            typedef typename StropReturnType<result_strop_type>::type type;            
        };

        template<typename Expr>
        const typename Subscription<typename ExpressionResultType<Expr>::type>::type
        Subscribe(const Expr &expr)
        {
            typedef typename ExpressionResultType<Expr>::type R;
                        
            if (IsVerbose())
                boost::proto::display_expr(expr);
            
            // Make sure the expression conforms to our grammar
            BOOST_MPL_ASSERT(( boost::proto::matches<Expr, smls_grammar> ));
            
            // add the expression to the graph
            typedef typename Subscription<R>::strop_type ResultStropType;
            ResultStropType result = smls_grammar()(expr, this);
                     
            StartEngine();
            return proto::lit(result);
        }
        
    private:
        
        void StartEngine()
        {
            WriteGraph("TsGraph.vis");
            ActivateSources();
            Work();            
        }
        
        void ActivateVertex(const BoostGraph::vertex_descriptor& vertex)
        {
            ActivateVertex(mGraph[vertex]);
        }
        
        void ActivateVertex(const StropPtr& strop)
        {
            assert(strop->GetEngine());
            if (!strop->GetEngine())
                return;
            
            if (strop->IsActive())
                return;
            mQueue.insert(QueueEntry(mCurrentTime++, strop->GetTopSortIndex(), strop->GetDescriptor()));
            strop->SetIsActive(true);
        }
        
        void ActivateSources()
        {
            if (IsVerbose())
                std::cout << "Activate sources: mSources.size() = " << mSources.size() << std::endl;
            for (std::vector<StropPtr>::iterator it = mSources.begin(); it != mSources.end(); ++it)
                ActivateVertex(*it);
        }        

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
                
                if (mEngine->IsVerbose())
                {
                    std::cout << "Finish vertex " << u << "  " //  << mGraph[u]->GetName()
                              << "  TO=" << mGraph[u]->GetTopSortIndex() << std::endl;
                }
            }
        private:
            size_t mIndex;
            Graph& mGraph;
            EngineApi* mEngine;
        };
        
        void GraphChanged()
        {
            TopologicalSortVisitor vis(mGraph, this);
            boost::depth_first_search(mGraph, boost::visitor(vis));
        }
        
        
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
        
        void WriteGraph(const std::string& filename)
        {
            if (IsVerbose())
                std::cout << "Writing graph to " << filename << std::endl;
            std::ofstream file;
            file.open (filename.c_str());
            boost::write_graphviz(file, mGraph, VertexPropertyWriter(mGraph));
            file.close();
        }

        std::set<QueueEntry> mQueue;
        TimestampT mCurrentTime;
        bool mWorking;    
        std::vector<StropPtr> mSources;
        bool mVerbose;

    };
    
} // ns streamulus
