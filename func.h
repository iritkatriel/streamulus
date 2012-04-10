//
//  func.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <sstream>

#include "strop.h"

namespace streamulus
{    
    
    template<typename Sig>
    class FuncBase : public Strop<Sig>
    {
    public:
        virtual std::string DisplayName() const
        {
            std::stringstream ss;
            ss << "Func_" << "F";
            return ss.str();
        }
    };
    
    template<class F, 
    typename A1, 
    typename R =typename F::template result<F(A1)>::type>
    class Func1 : public FuncBase<R(A1)>
    {
    public:
        
        bool Compute(R& result)
        {
            A1 a1;
            bool valid = true;        
            valid &= Strop<R(A1)>::template Input<A1,0>()->Current(a1);
            result = mFunction(a1);
            std::cout << FuncBase<R(A1)>::DisplayName() << "(" << a1 << ")=" << result <<std::endl;
            return valid;
        }
        
    private:
        F* mFunction;
    };
    
    template<class F, 
    typename A1, 
    typename A2, 
    typename R =typename F::template result<F(A1,A2)>::type>
    class Func2 : public FuncBase<R(A1,A2)>
    {
    public:
        
        bool Compute(R& result)
        {
            A1 a1;
            A2 a2;
            bool valid = true;        
            valid &= Strop<R(A1,A2)>::template Input<A1,0>()->Current(a1);
            valid &= Strop<R(A1,A2)>::template Input<A2,1>()->Current(a2);
            result = mFunction(a1,a2);
            std::cout << FuncBase<R(A1,A2)>::DisplayName() << "(" << a1 << "," << a2 << ")=" << result <<std::endl;
            return valid;
        }
                
    private:
        F mFunction;
    };
    
    template<class F, 
    typename A1, 
    typename A2, 
    typename A3, 
    typename R =typename F::template result<F(A1,A2,A3)>::type>
    class Func3 : public FuncBase<R(A1,A2,A3)>
    {
    public:        
        bool Compute(R& result)
        {
            A1 a1;
            A2 a2;
            A3 a3;
            bool valid = true;        
            valid &= Strop<R(A1,A2,A3)>::template Input<A1,0>()->Current(a1);
            valid &= Strop<R(A1,A2,A3)>::template Input<A2,1>()->Current(a2);
            valid &= Strop<R(A1,A2,A3)>::template Input<A3,2>()->Current(a3);
            
            if (valid)
                result = mFunction(a1,a2,a3);
            std::cout << FuncBase<R(A1,A2,A3)>::DisplayName() << "(" << a1 << "," << a2 << "," << a3 << ")=" << result <<std::endl;
            return valid;
        }
        
    private:
        F mFunction;
    };
    
    template<class F, 
    typename A1, 
    typename A2, 
    typename A3, 
    typename A4, 
    typename R =typename F::template result<F(A1,A2,A3,A4)>::type>
    class Func4 : public FuncBase<R(A1,A2,A3,A4)>
    {
    public:        
        bool Compute(R& result)
        {
            A1 a1;
            A2 a2;
            A3 a3;
            A4 a4;
            bool valid = true;        
            valid &= Strop<R(A1,A2,A3,A4)>::template Input<A1,0>()->Current(a1);
            valid &= Strop<R(A1,A2,A3,A4)>::template Input<A2,1>()->Current(a2);
            valid &= Strop<R(A1,A2,A3,A4)>::template Input<A3,2>()->Current(a3);
            valid &= Strop<R(A1,A2,A3,A4)>::template Input<A4,3>()->Current(a4);
            
            if (valid)
                result = mFunction(a1,a2,a3,a4);
            std::cout << FuncBase<R(A1,A2,A3,A4)>::DisplayName() << "(" << a1 << "," << a2 << "," << a3 << "," << a4 << ")=" << result <<std::endl;
            return valid;
        }
        
    private:
        F mFunction;
    };

    template<class F, 
    typename A1, 
    typename A2, 
    typename A3, 
    typename A4, 
    typename A5, 
    typename R =typename F::template result<F(A1,A2,A3,A4,A5)>::type>
    class Func5 : public FuncBase<R(A1,A2,A3,A4,A5)>
    {
    public:        
        bool Compute(R& result)
        {
            A1 a1;
            A2 a2;
            A3 a3;
            A4 a4;
            A5 a5;
            bool valid = true;        
            valid &= Strop<R(A1,A2,A3,A4,A5)>::template Input<A1,0>()->Current(a1);
            valid &= Strop<R(A1,A2,A3,A4,A5)>::template Input<A2,1>()->Current(a2);
            valid &= Strop<R(A1,A2,A3,A4,A5)>::template Input<A3,2>()->Current(a3);
            valid &= Strop<R(A1,A2,A3,A4,A5)>::template Input<A4,3>()->Current(a4);
            valid &= Strop<R(A1,A2,A3,A4,A5)>::template Input<A5,4>()->Current(a5);
            
            if (valid)
                result = mFunction(a1,a2,a3,a4,a5);
            std::cout << FuncBase<R(A1,A2,A3,A4,A5)>::DisplayName() << "(" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << ")=" << result <<std::endl;
            return valid;
        }
                
    private:
        F mFunction;
    };
    
    
} // ns streamulus
