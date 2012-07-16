//
//  strop_base.h
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

#include "engine_api.h" 

namespace streamulus
{
    
    class StropBase 
    {
    public:
        
        StropBase()
        : mEngine(NULL)
        , mVertexDescriptor(0)
        , mIsActive(false)
        , mDisplayName("unnamed")
        {    
        }
        
        StropBase(const std::string& display_name)
        : mEngine(NULL)
        , mVertexDescriptor(0)
        , mIsActive(false)
        , mDisplayName(display_name)
        {    
        }
        
        virtual ~StropBase()
        {
        }
        
        Graph::vertex_descriptor GetDescriptor() const
        {
            return mVertexDescriptor;
        }
        
        size_t GetTopSortIndex() const
        {
            return mTopSortIndex;
        }
        
        EngineApi* GetEngine()
        {
            return mEngine;
        }
        
        void SetGraph(EngineApi* engine, const Graph::vertex_descriptor& desc, size_t top_sort_index)
        {
            assert(mEngine==NULL || engine==NULL || engine == mEngine);
            mEngine = engine; 
            mVertexDescriptor = desc;
            mTopSortIndex = top_sort_index;
        }
        
        inline bool IsActive()
        {
            return mIsActive;
        }
        
        void SetIsActive(bool isActive)
        {
            mIsActive = isActive;
        }
        
        virtual std::string DisplayName() const=0;
        
        virtual void Work()=0;
        
        friend std::ostream& operator<<(std::ostream& os, const StropBase& strop)
        {
            return os << strop.mDisplayName;    
        }

    protected:
        
        EngineApi* mEngine; // no ownership. Do not delete. 
        Graph::vertex_descriptor mVertexDescriptor;
        size_t mTopSortIndex;
        bool mIsActive;
        
        std::string mDisplayName;
    };
    
} // ns streamulus