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

#include "cpp14_utils.h"

#include <boost/type_traits.hpp> 
#include <boost/proto/proto.hpp>

namespace streamulus
{       
    template<typename TAG>
    struct functor_of;
    
    template<>
    struct functor_of<boost::proto::tag::unary_plus> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::unary_plus>(A)>::type
        operator()(const A& value) const
        { 
            return +value; 
        }
    };
     
    template<>
    struct functor_of<boost::proto::tag::negate> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::negate>(A)>::type
        operator()(const A& value) const
        { 
            return -value; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::dereference> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = remove_pointer_t<A>;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::dereference> (A)>::type
        operator()(const A& value) const 
        { 
            return *value; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::complement> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;

        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::complement>(A)>::type
        operator()(const A& value) const 
        { 
            return ~value; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::address_of>  
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = typename boost::add_pointer<A>::type;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::address_of>(A)>::type
        operator()(A& value) const
        { 
            return &value; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::logical_not> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = bool;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::logical_not>(A)>::type
        operator()(const A& value) const
        { 
            return !value; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::pre_inc> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::pre_inc>(A)>::type
        operator()(const A& value) const
        {
            remove_const_t<A> res(value);
            return ++res; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::pre_dec> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::pre_dec>(A)>::type
        operator()(const A& value) const
        { 
            remove_const_t<A> res(value);
            return --res; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::post_inc> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::post_inc>(A)>::type
        operator()(const A& value) const
        {
            remove_const_t<A> res(value);
            return res++; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::post_dec> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A> 
        struct result<This(A)>
        {
            using type = A;
        };
        
        template<typename A>
        typename result<functor_of<boost::proto::tag::post_dec>(A)>::type
        operator()(const A& value) const
        {
            remove_const_t<A> res(value);
            return res--; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::shift_left> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::shift_left>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<<rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::shift_right> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::shift_right>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            return lhs>>rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::multiplies> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::multiplies>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs*rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::divides> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::divides>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs/rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::modulus> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::modulus>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs%rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::plus> 
    {
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::plus>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs+rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::minus> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::minus>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs-rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::less> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::less>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::greater> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::greater>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs>rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::less_equal> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::less_equal>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs<=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::greater_equal> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::greater_equal>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs>=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::equal_to> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::equal_to>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs==rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::not_equal_to> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::not_equal_to>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs!=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::logical_or> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::logical_or>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs||rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::logical_and> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = bool;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::logical_and>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs&&rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_or> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_or>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs|rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_and> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_and>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs&rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_xor> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_xor>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs^rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::comma> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = B;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::comma>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        { 
            return lhs,rhs; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::shift_left_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::shift_left_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy <<= rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::shift_right_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::shift_right_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy >>= rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::multiplies_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::multiplies_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy*=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::divides_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::divides_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy/=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::modulus_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::modulus_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy%=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::plus_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::plus_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy+=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::minus_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::minus_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy-=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_and_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_and_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy&=rhs; 
        }
    };
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_or_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_or_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy|=rhs; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::bitwise_xor_assign> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            using type = A;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::bitwise_xor_assign>(A,B)>::type
        operator()(const A& lhs, const B& rhs) const
        {
            remove_const_t<A> dummy(lhs);
            return dummy^=rhs; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::subscript> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B> 
        struct result<This(A,B)>
        {
            // TODO: this will work for arrays but not in general. fix or remove.
            using type = remove_pointer_t<A>;
        };
        
        template<typename A, typename B>
        typename result<functor_of<boost::proto::tag::subscript>(A,B)>::type
        operator()(const A& array, const B& index) const
        { 
            return array[index]; 
        }
    };
    
    
    template<>
    struct functor_of<boost::proto::tag::if_else_> 
    {    
        template<class Sig> struct result;
        
        template<class This,typename A, typename B, typename C> 
        struct result<This(A,B,C)>
        {
            using type = typename boost::common_type<A,B>::type;
        };
        
        template<typename A, typename B, typename C>
        typename result<functor_of<boost::proto::tag::if_else_>(A,B,C)>::type
        operator()(const A& condition, const B& yes, const C& no) 
        { 
            return condition ? yes : no; 
        }
    };
    
} // ns streamulus
