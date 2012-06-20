//
//  operator_subscribe_tests.cpp
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

#include "operator_subscribe_test.hpp"

namespace streamulus
{
    int assert_eq::tests_passed = 0;
    
    void operator_subscribe_unit_tests::Run()
    {
        OpsBetweenTerminals();
        OpsBetweenTerminalAndConst();
        std::cout << "operator_subscribe_unit_tests completed. " << 
        assert_eq::tests_passed << "/" << tests_run << " tests passed" << std::endl;
        
        Check(assert_eq::tests_passed == tests_run);
    }

    
    void operator_subscribe_unit_tests::OpsBetweenTerminals()
    {        
        int v1_=7;
        int v2_=2;
        int v1=v1_;
        int v2=v2_;
        proto::terminal<int>::type t1 = {v1};
        proto::terminal<int>::type t2 = {v2};
        proto::terminal<int*>::type p1 = {&v1};
        proto::terminal<int*>::type p2 = {&v2};
        
        v1=v1_; v2=v2_; RunTest(-t1, -v1);
        v1=v1_; v2=v2_; RunTest(-t2, -v2);
        
        v1=v1_; v2=v2_; RunTest(*p1, v1);
        v1=v1_; v2=v2_; RunTest(*p2, v2);
        
        v1=v1_; v2=v2_; RunTest(~t1, ~v1);
        v1=v1_; v2=v2_; RunTest(~t2, ~v2);
        
        v1=v1_; v2=v2_; RunTest(!t1, !v1);
        v1=v1_; v2=v2_; RunTest(!t2, !v2);
        
        v1=v1_; v2=v2_; RunTest(++t1, ++v1);
        v1=v1_; v2=v2_; RunTest(++t2, ++v2);
        
        v1=v1_; v2=v2_; RunTest(--t1, --v1);
        v1=v1_; v2=v2_; RunTest(--t2, --v2);
        
        v1=v1_; v2=v2_; RunTest(t1++, v1++);
        v1=v1_; v2=v2_; RunTest(t2++, v2++);
        
        v1=v1_; v2=v2_; RunTest(t1--, v1--);
        v1=v1_; v2=v2_; RunTest(t2--, v2--);
        
        v1=v1_; v2=v2_; RunTest(t1 << t2, v1 << v2);
        v1=v1_; v2=v2_; RunTest(t2 << t1, v2 << v1);
        
        v1=v1_; v2=v2_; RunTest(t1 >> t2, v1 >> v2);
        v1=v1_; v2=v2_; RunTest(t2 >> t1, v2 >> v1);
        
        v1=v1_; v2=v2_; RunTest(t1 * t2, v1 * v2);
        v1=v1_; v2=v2_; RunTest(t2 * t1, v2 * v1);
        
        v1=v1_; v2=v2_; RunTest(t1 / t2, v1 / v2);
        v1=v1_; v2=v2_; RunTest(t2 / t1, v2 / v1);
        
        v1=v1_; v2=v2_; RunTest(t1 % t2, v1 % v2);
        v1=v1_; v2=v2_; RunTest(t2 % t1, v2 % v1);
        
        v1=v1_; v2=v2_; RunTest(t1 + t2, v1 + v2);
        v1=v1_; v2=v2_; RunTest(t2 + t1, v2 + v1);
        
        v1=v1_; v2=v2_; RunTest(t1 - t2, v1 - v2);
        v1=v1_; v2=v2_; RunTest(t2 - t1, v2 - v1);
        
        v1=v1_; v2=v2_; RunTest(t1 < t2, v1 < v2);
        v1=v1_; v2=v2_; RunTest(t2 < t1, v2 < v1);
        
        v1=v1_; v2=v2_; RunTest(t1 > t2, v1 > v2);
        v1=v1_; v2=v2_; RunTest(t2 > t1, v2 > v1);
        
        v1=v1_; v2=v2_; RunTest(t1 <= t2, v1 <= v2);
        v1=v1_; v2=v2_; RunTest(t2 <= t1, v2 <= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 >= t2, v1 >= v2);
        v1=v1_; v2=v2_; RunTest(t2 >= t1, v2 >= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 == t2, v1 == v2);
        v1=v1_; v2=v2_; RunTest(t2 == t1, v2 == v1);
        
        v1=v1_; v2=v2_; RunTest(t1 != t2, v1 != v2);
        v1=v1_; v2=v2_; RunTest(t2 != t1, v2 != v1);
        
        v1=v1_; v2=v2_; RunTest(t1 || t2, v1 || v2);
        v1=v1_; v2=v2_; RunTest(t2 || t1, v2 || v1);
        
        v1=v1_; v2=v2_; RunTest(t1 && t2, v1 && v2);
        v1=v1_; v2=v2_; RunTest(t2 && t1, v2 && v1);
        
        v1=v1_; v2=v2_; RunTest(t1 | t2, v1 | v2);
        v1=v1_; v2=v2_; RunTest(t2 | t1, v2 | v1);
        
        v1=v1_; v2=v2_; RunTest(t1 & t2, v1 & v2);
        v1=v1_; v2=v2_; RunTest(t2 & t1, v2 & v1);
        
        v1=v1_; v2=v2_; RunTest(t1 ^ t2, v1 ^ v2);
        v1=v1_; v2=v2_; RunTest(t2 ^ t1, v2 ^ v1);
                
        v1=v1_; v2=v2_; RunTest((t1 = t2), (v1 = v2));
        v1=v1_; v2=v2_; RunTest((t2 = t1), (v2 = v1));
        
        v1=v1_; v2=v2_; RunTest(t1 <<= t2, v1 <<= v2);
        v1=v1_; v2=v2_; RunTest(t2 <<= t1, v2 <<= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 >>= t2, v1 >>= v2);
        v1=v1_; v2=v2_; RunTest(t2 >>= t1, v2 >>= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 *= t2, v1 *= v2);
        v1=v1_; v2=v2_; RunTest(t2 *= t1, v2 *= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 /= t2, v1 /= v2);
        v1=v1_; v2=v2_; RunTest(t2 /= t1, v2 /= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 %= t2, v1 %= v2);
        v1=v1_; v2=v2_; RunTest(t2 %= t1, v2 %= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 += t2, v1 += v2);
        v1=v1_; v2=v2_; RunTest(t2 += t1, v2 += v1);
        
        v1=v1_; v2=v2_; RunTest(t1 -= t2, v1 -= v2);
        v1=v1_; v2=v2_; RunTest(t2 -= t1, v2 -= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 &= t2, v1 &= v2);
        v1=v1_; v2=v2_; RunTest(t2 &= t1, v2 &= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 |= t2, v1 |= v2);
        v1=v1_; v2=v2_; RunTest(t2 |= t1, v2 |= v1);
        
        v1=v1_; v2=v2_; RunTest(t1 ^= t2, v1 ^= v2);
        v1=v1_; v2=v2_; RunTest(t2 ^= t1, v2 ^= v1);
        
        
        // TODO:: make these work
        v1=v1_; v2=v2_; RunTest(true ? t1 : t2, true ? v1 : v2);
        v1=v1_; v2=v2_; RunTest(true ? t2 : t1, true ? v2 : v1);
        
        v1=v1_; v2=v2_; RunTest(false ? t1 : t2, false ? v1 : v2);
        v1=v1_; v2=v2_; RunTest(false ? t2 : t1, false ? v2 : v1);
        
    }
    
    void operator_subscribe_unit_tests::OpsBetweenTerminalAndConst()
    {
        int v1_=7;
        int v1=v1_;
        proto::terminal<int>::type t1 = {v1};
        
        v1=v1_; RunTest(t1 << 2, v1 << 2);
        v1=v1_; RunTest(2 << t1, 2 << v1);
        
        v1=v1_; RunTest(t1 >> 2, v1 >> 2);
        v1=v1_; RunTest(2 >> t1, 2 >> v1);
        
        v1=v1_; RunTest(t1 * 2, v1 * 2);
        v1=v1_; RunTest(2 * t1, 2 * v1);
        
        v1=v1_; RunTest(t1 / 2, v1 / 2);
        v1=v1_; RunTest(2 / t1, 2 / v1);
        
        v1=v1_; RunTest(t1 % 2, v1 % 2);
        v1=v1_; RunTest(2 % t1, 2 % v1);
        
        v1=v1_; RunTest(t1 + 2, v1 + 2);
        v1=v1_; RunTest(2 + t1, 2 + v1);
        
        v1=v1_; RunTest(t1 - 2, v1 - 2);
        v1=v1_; RunTest(2 - t1, 2 - v1);
        
        v1=v1_; RunTest(t1 < 2, v1 < 2);
        v1=v1_; RunTest(2 < t1, 2 < v1);
        
        v1=v1_; RunTest(t1 > 2, v1 > 2);
        v1=v1_; RunTest(2 > t1, 2 > v1);
        
        v1=v1_; RunTest(t1 <= 2, v1 <= 2);
        v1=v1_; RunTest(2 <= t1, 2 <= v1);
        
        v1=v1_; RunTest(t1 >= 2, v1 >= 2);
        v1=v1_; RunTest(2 >= t1, 2 >= v1);
        
        v1=v1_; RunTest(t1 == 2, v1 == 2);
        v1=v1_; RunTest(2 == t1, 2 == v1);
        
        v1=v1_; RunTest(t1 != 2, v1 != 2);
        v1=v1_; RunTest(2 != t1, 2 != v1);
                
        v1=v1_; RunTest(t1 | 2, v1 | 2);
        v1=v1_; RunTest(2 | t1, 2 | v1);
        
        v1=v1_; RunTest(t1 & 2, v1 & 2);
        v1=v1_; RunTest(2 & t1, 2 & v1);
        
        v1=v1_; RunTest(t1 ^ 2, v1 ^ 2);
        v1=v1_; RunTest(2 ^ t1, 2 ^ v1);
                
        v1=v1_; RunTest((t1 = 2), (v1 = 2));
        
        v1=v1_; RunTest(t1 <<= 2, v1 <<= 2);
        
        v1=v1_; RunTest(t1 >>= 2, v1 >>= 2);
        
        v1=v1_; RunTest(t1 *= 2, v1 *= 2);
        
        v1=v1_; RunTest(t1 /= 2, v1 /= 2);
        
        v1=v1_; RunTest(t1 %= 2, v1 %= 2);
        
        v1=v1_; RunTest(t1 += 2, v1 += 2);
        
        v1=v1_; RunTest(t1 -= 2, v1 -= 2);
        
        v1=v1_; RunTest(t1 &= 2, v1 &= 2);
        
        v1=v1_; RunTest(t1 |= 2, v1 |= 2);
        
        v1=v1_; RunTest(t1 ^= 2, v1 ^= 2);
        
        /*            
         // TODO:: make these work
         v1=v1_; RunTest(proto::if_else<true,t1,2>, true ? v1 : 2);
         v1=v1_; RunTest(proto::if_else<true,2,t1>, true ? 2 : v1);
         
         v1=v1_; RunTest(proto::if_else<false,t1,2>, false ? v1 : 2);
         v1=v1_; RunTest(proto::if_else<false,2,t1>, false ? 2 : v1); 
         */
    }

    
} // ns streamulus