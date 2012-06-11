//
//  operator_subscribe_tests.hpp
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

#include "operators.h"
#include "unit_test_api.h"

//
// operator subscribe test
//
// Subscribe an expression for each operator and check that it computes 
// something reasonable.
//

#include "../include/streamulus.h"

namespace streamulus
{   
    namespace bp = boost::proto;
    
    struct assert_eq
    {
        static int tests_passed;
        
        template<class Sig> struct result;
        
        template<class This,typename T1, typename T2>
        struct result<This(T1, T2)>
        {
            typedef bool type; 
        };
        
        template<typename T1, typename T2>
        typename result<assert_eq(T1,T2)>::type
        operator()(const T1& v1, const T2& v2) const
        { 
            bool result = (v1 == v2);
            if (! result)
                std::cout << "********* Test Failed! " << v1 << "!=" << v2 << " *********" << std::endl;
            
            if(result)
                tests_passed++;
            return result;
        }
    };
        
    struct operator_subscribe_unit_tests : unit_test_api
    {
    public:
        
        operator_subscribe_unit_tests()
        {
            tests_run = 0;
        }

        void Run();

    private:
        template<typename Expr, typename ExpectedValueType>
        void RunTest(Expr& expr, ExpectedValueType expected)
        {
            tests_run++;
            Streamulus engine;
            engine.Subscribe(Streamify<assert_eq>(expr, expected));
        }
        
        void OpsBetweenTerminals();
        
        void OpsBetweenTerminalAndConst();

        int tests_run;
    };
    
} // ns streamulus