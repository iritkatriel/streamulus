//
//  operators.cpp
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

#include "operators.h"
#include "unit_test_api.h"

namespace streamulus
{   
    struct operator_strops_unit_tests : unit_test_api
    {
        void Run()
        {    
            int i0 = 7, j0 = 2;
            int i, j;
            int iexp, jexp;
            int *pi = &i;
            
            i=iexp=i0; j=jexp=j0; Check(negate_func()(i) == -iexp); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(negate_func()(-i) == iexp); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(dereference_func()(pi) == iexp); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(complement_func()(i) == ~iexp); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(address_of_func()(i) == pi); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(logical_not_func()(i) == !iexp); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(prefix_inc_func()(i) == ++iexp); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(prefix_dec_func()(i) == --iexp); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(postfix_inc_func()(i) == iexp++); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(postfix_dec_func()(i) == iexp--); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(shift_left_func()(i,j) == (iexp<<jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(shift_left_func()(j,i) == (jexp<<iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(shift_right_func()(i,j) == (iexp>>jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(shift_right_func()(j,i) == (jexp>>iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(multiplies_func()(i,j) == (iexp*jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(multiplies_func()(j,i) == (jexp*iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(divides_func()(i,j) == (iexp/jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(divides_func()(j,i) == (jexp/iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(modulus_func()(i,j) == (iexp%jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(modulus_func()(j,i) == (jexp%iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(plus_func()(i,j) == (iexp+jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(plus_func()(j,i) == (jexp+iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(minus_func()(i,j) == (iexp-jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(minus_func()(j,i) == (jexp-iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(less_func()(i,j) == (iexp<jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(less_func()(j,i) == (jexp<iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(greater_func()(i,j) == (iexp>jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(greater_func()(j,i) == (jexp>iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(less_eq_func()(i,j) == (iexp<=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(less_eq_func()(j,i) == (jexp<=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(greater_eq_func()(i,j) == (iexp>=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(greater_eq_func()(j,i) == (jexp>=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(equal_func()(i,j) == (iexp==jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(equal_func()(j,i) == (jexp==iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(not_equal_func()(i,j) == (iexp!=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(not_equal_func()(j,i) == (jexp!=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(logical_or_func()(i,j) == (iexp||jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(logical_or_func()(j,i) == (jexp||iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(logical_and_func()(i,j) == (iexp&&jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(logical_and_func()(j,i) == (jexp&&iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitwise_or_func()(i,j) == (iexp|jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitwise_or_func()(j,i) == (jexp|iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitwise_and_func()(i,j) == (iexp&jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitwise_and_func()(j,i) == (jexp&iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitwise_xor_func()(i,j) == (iexp^jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitwise_xor_func()(j,i) == (jexp^iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(comma_func()(i,j) == (iexp,jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(comma_func()(j,i) == (jexp,iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(assign_func()(i,j) == (iexp=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(assign_func()(j,i) == (jexp=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(lshift_assign_func()(i,j) == (iexp<<=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(lshift_assign_func()(j,i) == (jexp<<=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(rshift_assign_func()(i,j) == (iexp>>=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(rshift_assign_func()(j,i) == (jexp>>=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(mult_assign_func()(i,j) == (iexp*=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(mult_assign_func()(j,i) == (jexp*=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(div_assign_func()(i,j) == (iexp/=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(div_assign_func()(j,i) == (jexp/=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(mod_assign_func()(i,j) == (iexp%=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(mod_assign_func()(j,i) == (jexp%=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(plus_assign_func()(i,j) == (iexp+=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(plus_assign_func()(j,i) == (jexp+=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(minus_assign_func()(i,j) == (iexp-=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(minus_assign_func()(j,i) == (jexp-=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitand_assign_func()(i,j) == (iexp&=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitand_assign_func()(j,i) == (jexp&=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitor_assign_func()(i,j) == (iexp|=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitor_assign_func()(j,i) == (jexp|=iexp)); Check(i==iexp); Check(j==jexp);
            
            i=iexp=i0; j=jexp=j0; Check(bitxor_assign_func()(i,j) == (iexp^=jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(bitxor_assign_func()(j,i) == (jexp^=iexp)); Check(i==iexp); Check(j==jexp);
            
            // subscript_func
            
            i=iexp=i0; j=jexp=j0; Check(if_else_func()(true,i,j)  == (true ? iexp : jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(if_else_func()(true,j,i)  == (true ? jexp : iexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(if_else_func()(false,i,j) == (false ? iexp : jexp)); Check(i==iexp); Check(j==jexp);
            i=iexp=i0; j=jexp=j0; Check(if_else_func()(false,j,i) == (false ? jexp : iexp)); Check(i==iexp); Check(j==jexp);
            
        }
    };
    
} // ns streamulus