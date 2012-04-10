//
//  data_source.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <iostream>

#include "strop.h"

namespace streamulus
{    
    
    template<typename R>
    class DataSource : public Strop<R()>  
    {
    public:
        DataSource(const std::string& name)
        : mName(name)
        , mIsValid(false)
        {
        }
                
        bool Compute(R& result)
        {
            if (mIsValid)
                result = mLastValue;
            std::cout << mName << "  Compute():  result =" << result << " valid=" << mIsValid << std::endl;
            return mIsValid;
        }
        
        void Tick(const R& value)
        {
            std::cout << "Tick(" << mName << "," << value << ")" << std::endl;
            Strop<R()>::Output(value); 
            mLastValue = value;
            mIsValid = true;
        }
        
        virtual std::string DisplayName() const
        {
            return mName;
        }
        
        
    private:
        std::string mName; 
        R           mLastValue;
        bool        mIsValid;
    };
    
} // ns streamulus