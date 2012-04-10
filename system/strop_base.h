//
//  strop_base.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

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
        
        Graph::vertex_descriptor Descriptor() const
        {
            return mVertexDescriptor;
        }
        
        size_t GetTopSortIndex() const
        {
            return mTopSortIndex;
        }
        
        bool GraphIsSet() const
        {
            return mEngine != NULL;
        }
        
        void SetGraph(EngineApi* engine, const Graph::vertex_descriptor& desc, size_t top_sort_index)
        {
            assert(mEngine==NULL || engine == mEngine);
            mEngine = engine; 
            mVertexDescriptor = desc;
            mTopSortIndex = top_sort_index;
        }
        
        bool IsActive()
        {
            return mIsActive;
        }
        
        void SetIsActive(bool isActive)
        {
            mIsActive = isActive;
        }
        
        virtual std::string DisplayName() const=0;
        
        virtual bool Work()=0;
        
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