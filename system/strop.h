//
//  strop.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/proto/proto.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "stream.h" 
#include "engine_api.h" 
#include "strop_base.h" 

namespace streamulus
{
    
    
    template<typename F> // F = function signature
    class Strop 
        : public StropBase
        , public boost::enable_shared_from_this<Strop<F> >
    {
    public:
        
        virtual ~Strop() 
        {
        }
        
        typedef typename boost::function_types::result_type<F>::type result_type;
        typedef boost::function_types::parameter_types<F> param_types;
        
        typedef boost::shared_ptr<Strop<F> > StropPtrType;
        typedef typename boost::proto::terminal<const StropPtrType>::type ProtoTerminalType;
        
        virtual bool Compute(result_type& result)=0;
        
        // return true if you put any data on output streams, false otherwise
        virtual bool Work()
        {            
            result_type res;
            if (! Compute(res))
                return false;
            
            std::cout << "Compute[" << mTopSortIndex << "]: " << res << std::endl;
            
            Output(res);
            return true;
        }
        
        void Output(const result_type& value)
        {
            mEngine->Output<result_type>(mVertexDescriptor,value);
        }
        
        template<typename Inputs> // a fusion sequence of the inputs
        void SetInputs(const Inputs& inputs)
        {
            mInputs=inputs;
        }
        
        template<typename Tinput, int I>
        boost::shared_ptr<Stream<Tinput> > Input()
        {
            return boost::fusion::at_c<I>(mInputs);
        }
        
        typedef boost::shared_ptr<Stream<result_type> > OutputStreamPtr;
        
        OutputStreamPtr MakeOutputStream() const
        {
            return OutputStreamPtr(new Stream<result_type>());
        }
        
#if 0        
        ProtoTerminalType ProtoTerminal() const
        {
            StropPtrType strop(shared_from_this());
            ProtoTerminalType strop_term = {strop};
            return strop_term;
        }
#endif 
        
    private:
        template<typename T>
        struct MakeStreamPtrType 
        {
            typedef boost::shared_ptr<Stream<T>  > type;
        };
        typedef typename boost::mpl::transform<param_types,MakeStreamPtrType<boost::mpl::_1> >::type input_types;
        typename boost::fusion::result_of::as_vector<typename input_types::type>::type mInputs;
    };
    
    
} // ns streamulus