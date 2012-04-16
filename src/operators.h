//
//  operators.h
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

#include <boost/type_traits.hpp> 

namespace streamulus
{       
    struct unary_plus_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<unary_plus_func(A)>::type
        operator()(const A& value) const
        { 
            return +value; 
        }
    };

    struct negate_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<negate_func(A)>::type
        operator()(const A& value) const
        { 
            return -value; 
        }
    };
    
    struct dereference_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef typename boost::remove_pointer<A>::type type; 
        };
        
        template<typename A>
        typename result<dereference_func(A)>::type
        operator()(const A& value) const 
        { 
            return *value; 
        }
    };
    
    
    struct complement_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<complement_func(A)>::type
        operator()(const A& value) const 
        { 
            return ~value; 
        }
    };
    
    struct address_of_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef typename boost::add_pointer<A>::type type; 
        };
        
        template<typename A>
        typename result<address_of_func(A)>::type
        operator()(A& value) const
        { 
            return &value; 
        }
    };
    
    struct logical_not_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef bool type; 
        };
        
        template<typename A>
        typename result<logical_not_func(A)>::type
        operator()(const A& value) const
        { 
            return !value; 
        }
    };
    
    struct prefix_inc_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<prefix_inc_func(A)>::type
        operator()(A& value) const
        { 
            return ++value; 
        }
    };
    
    struct prefix_dec_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<prefix_dec_func(A)>::type
        operator()(A& value) const
        { 
            return --value; 
        }
    };
    
    struct postfix_inc_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<postfix_inc_func(A)>::type
        operator()(A& value) const 
        { 
            return value++; 
        }
    };
    
    struct postfix_dec_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            typedef A type; 
        };
        
        template<typename A>
        typename result<postfix_dec_func(A)>::type
        operator()(A& value) const
        { 
            return value--; 
        }
    };
    
    
    struct shift_left_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<shift_left_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<<rhs; 
        }
    };
    
    struct shift_right_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type;
        };
        
        template<typename A, typename B>
        typename result<shift_right_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            return lhs>>rhs; 
        }
    };
    
    struct multiplies_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<multiplies_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs*rhs; 
        }
    };
    
    
    struct divides_func
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<divides_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs/rhs; 
        }
    };
    
    struct modulus_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<modulus_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs%rhs; 
        }
    };
    
    struct plus_func 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<plus_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs+rhs; 
        }
    };
    
    struct minus_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<minus_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs-rhs; 
        }
    };
    
    struct less_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<less_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<rhs; 
        }
    };
    
    struct greater_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<greater_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs>rhs; 
        }
    };
    
    struct less_eq_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<less_eq_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<=rhs; 
        }
    };
    
    struct greater_eq_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<greater_eq_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs>=rhs; 
        }
    };
    
    struct equal_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<equal_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs==rhs; 
        }
    };
    
    struct not_equal_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<not_equal_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs!=rhs; 
        }
    };
    
    struct logical_or_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<logical_or_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs||rhs; 
        }
    };
    
    struct logical_and_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef bool type; 
        };
        
        template<typename A, typename B>
        typename result<logical_and_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs&&rhs; 
        }
    };
    
    struct bitwise_or_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<bitwise_or_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs|rhs; 
        }
    };
    
    struct bitwise_and_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<bitwise_and_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs&rhs; 
        }
    };
    
    struct bitwise_xor_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B>
        typename result<bitwise_xor_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs^rhs; 
        }
    };
    
    struct comma_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef B type; 
        };
        
        template<typename A, typename B>
        typename result<comma_func(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs,rhs; 
        }
    };
    
    
    struct assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs=rhs; 
        }
    };
    
    struct lshift_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<lshift_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs <<= rhs; 
        }
    };
    
    struct rshift_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<rshift_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs >>= rhs; 
        }
    };
    
    struct mult_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<mult_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs*=rhs; 
        }
    };
    
    struct div_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<div_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs/=rhs; 
        }
    };
    
    struct mod_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<mod_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs%=rhs; 
        }
    };
    
    struct plus_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<plus_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs+=rhs; 
        }
    };
    
    struct minus_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<minus_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs-=rhs; 
        }
    };
    
    struct bitand_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<bitand_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs&=rhs; 
        }
    };
    
    struct bitor_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<bitor_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs|=rhs; 
        }
    };
    
    
    struct bitxor_assign_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            typedef A type; 
        };
        
        template<typename A, typename B>
        typename result<bitxor_assign_func(A,B)>::type
        operator()(A& lhs, const B& rhs) const
        { 
            return lhs^=rhs; 
        }
    };
    
    
    struct subscript_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            // TODO: this will work for arrays but not in general. fix or remove.
            typedef typename boost::remove_pointer<A>::type type; 
        };
        
        template<typename A, typename B>
        typename result<subscript_func(A,B)>::type
        operator()(const A& array, const B& index) const
        { 
            return array[index]; 
        }
    };
    
    
    struct if_else_func 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B, typename C> 
        struct result<This(A,B,C)>
        {
            typedef typename boost::common_type<A,B>::type type; 
        };
        
        template<typename A, typename B, typename C>
        typename result<if_else_func(A,B,C)>::type
        operator()(const A& condition, const B& yes, const C& no) 
        { 
            return condition ? yes : no; 
        }
    };
    
} // ns streamulus