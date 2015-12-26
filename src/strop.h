//
//  strop.h
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

#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/proto/proto.hpp>


#include "strop_stream_producer.h" 

namespace streamulus
{
    
    template<typename F> // F = function signature
    class Strop 
        : public StropStreamProducer<typename boost::function_types::result_type<F>::type>
    {
    public:
        
        virtual ~Strop() 
        {
        }
        
        template<typename Inputs> // a fusion sequence of the inputs
        void SetInputs(const Inputs& inputs)
        {
            mInputs=inputs;
        }
        
        template<typename Tinput, int I>
        Stream<Tinput>* const Input()
        {
            return boost::fusion::at_c<I>(mInputs).get();
        }
        
                        
    private:
        template<typename T>
        struct MakeStreamPtrType 
        {
            using type = std::shared_ptr<Stream<T>>;
        };
        using param_types =  boost::function_types::parameter_types<F>;
        using input_types = typename boost::mpl::transform<param_types,MakeStreamPtrType<boost::mpl::_1> >::type;
        typename boost::fusion::result_of::as_vector<typename input_types::type>::type mInputs;
    };
    
    
} // ns streamulus