//
//  const.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <sstream>

#include "strop.h"

namespace streamulus
{    
        
    template<typename T>
    class Const : public Strop<T()> 
    {
    public:
        
        Const(const T& v)
		: mValue(v)
        {
        }
        
        virtual ~Const()
        {
        }
                
        bool Compute(T& result)
        {
            result = mValue;
            return true;
        }
        
        virtual std::string DisplayName() const
        {
            std::stringstream ss;
            ss << "Const" << mValue;
            return ss.str();
        }
        
        

    private:
        T mValue;
    };
    
} // ns streamulus
