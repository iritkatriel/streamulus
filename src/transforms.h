//
//  transforms.h
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

// Transforms for streamulus grammar

#include "stream.h"
#include "strop.h"
#include "strop_const.h"
#include "strop_func.h"
#include "input_stream.h"
#include "strop_return_type.h"

#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits.hpp>


namespace streamulus
{
    
    using namespace boost;
        
    template<typename SharedPtrType>
    struct BaseType;
    
    template<typename Type>
    struct BaseType<boost::shared_ptr<Type> >
    {
        typedef Type type;
    };
    
    
    template<typename Sig>
    struct MakeStropPtrType
    {  
        typedef boost::shared_ptr<Strop<Sig> > type;    
    };
    
    struct AddStropToGraph : proto::callable  
    {
        template<class Sig> struct result;
        
        template<class This, class StropType, class State>
        struct result<This(StropType,State)>
        {
            typedef StropType type;
        };
        
        template<typename StropType, class State>
        const StropType operator()(StropType strop, State engine)
        {
            if (engine->IsVerbose())
                std::cout << "AddStropToGraph: strop=" << strop << std::endl;
            if (!strop->GetEngine())
            {
                if (engine->IsVerbose())
                    std::cout << "AddStropToGraph::operator()" << std::endl;
                engine->AddVertexToGraph(strop);
                engine->AddSource(strop);
            }
            if (engine->IsVerbose())
                std::cout << "returning " << strop->GetDescriptor() << std::endl;
            return strop;
        }
    };
    
    struct AddConstToGraph : proto::callable  
    {
        template<class Sig> struct result;
        
        template<class This, typename T, class State>
        struct result<This(T,State)>
        {
            typedef typename boost::remove_const<typename boost::remove_reference<T>::type>::type ConstType;
            typedef const boost::shared_ptr<StropStreamProducer<ConstType> > type;
        };
        
        template<typename T, class State>
        typename result<AddConstToGraph(T,State)>::type operator()(T& value, State engine)
        {
            typedef typename result<AddConstToGraph(T,State)>::ConstType ConstType;
            if (engine->IsVerbose())
                std::cout << "Add const to graph " << value <<std::endl;
            boost::shared_ptr<Const<ConstType> > strop(new Const<ConstType>(value));
            return AddStropToGraph()(strop,engine);
        }
    };

    struct generic_func : proto::callable
    {
        template<typename Sig> struct result;
        
        // Arity = 1
        template<typename F, 
        typename Arg1Strop, 
        typename State>
        struct result<generic_func(F&,Arg1Strop,State)>
        {
            typedef typename StropReturnType<const Arg1Strop>::type Arg1Type;
            typedef typename F::template result<F(Arg1Type)>::type R; 
            typedef const boost::shared_ptr<Strop<R(Arg1Type)> > type;         
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename State>
        typename result<generic_func(F&,Arg1Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   State engine)
        {  
            if (engine->IsVerbose())             
                std::cout << "generic_func" << std::endl;
            typedef result<generic_func(F&,Arg1Strop,State)> Result;        
            typedef Func1<F
            ,typename Result::Arg1Type
            > FuncStropType; 
            
            boost::shared_ptr<FuncStropType> funcStropPtr(new FuncStropType(f)); 
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1->GetDescriptor(), funcStropPtr->GetDescriptor(), arg1Stream);
            return funcStropPtr;
        }

        // Arity = 2
        template<typename F, typename Arg1Strop, typename Arg2Strop, typename State>
        struct result<generic_func(F&,Arg1Strop,Arg2Strop,State)>
        {
            typedef typename StropReturnType<const Arg1Strop>::type Arg1Type;
            typedef typename StropReturnType<const Arg2Strop>::type Arg2Type;
            typedef typename F::template result<F(Arg1Type,Arg2Type)>::type R; 
            typedef const boost::shared_ptr<Strop<R(Arg1Type,Arg2Type)> > type;         
        };
        
        template<typename F, typename Arg1Strop, typename Arg2Strop, typename State>
        typename result<generic_func(F&,Arg1Strop,Arg2Strop, State)>::type
        operator()(const F& f,const Arg1Strop arg1, const Arg2Strop arg2, State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            typedef result<generic_func(F&,Arg1Strop,Arg2Strop, State)> Result;        
            typedef Func2<F, typename Result::Arg1Type, typename Result::Arg2Type> FuncStropType; 
            boost::shared_ptr<FuncStropType> funcStropPtr(new FuncStropType(f)); 
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1->GetDescriptor(), funcStropPtr->GetDescriptor(), arg1Stream);
            engine->AddEdgeToGraph(arg2->GetDescriptor(), funcStropPtr->GetDescriptor(), arg2Stream);
            return funcStropPtr;
        }

        // Arity = 3
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename State>
        struct result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,State)>
        {
            typedef typename StropReturnType<const Arg1Strop>::type Arg1Type;
            typedef typename StropReturnType<const Arg2Strop>::type Arg2Type;
            typedef typename StropReturnType<const Arg3Strop>::type Arg3Type;
            typedef typename F::template result<F(Arg1Type,Arg2Type,Arg3Type)>::type R; 
            typedef const boost::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type)> > type;         
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename State>
        typename result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   const Arg2Strop arg2, 
                   const Arg3Strop arg3, 
                   State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            typedef result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,State)> Result;        
            typedef Func3<F
            ,typename Result::Arg1Type
            ,typename Result::Arg2Type
            ,typename Result::Arg3Type
            > FuncStropType; 
            
            boost::shared_ptr<FuncStropType> funcStropPtr(new FuncStropType(f)); 
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1->GetDescriptor(), funcStropPtr->GetDescriptor(), arg1Stream);
            engine->AddEdgeToGraph(arg2->GetDescriptor(), funcStropPtr->GetDescriptor(), arg2Stream);
            engine->AddEdgeToGraph(arg3->GetDescriptor(), funcStropPtr->GetDescriptor(), arg3Stream);
            return funcStropPtr;
        }
        
        // Arity = 4
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename Arg4Strop, 
        typename State>
        struct result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)>
        {
            typedef typename StropReturnType<const Arg1Strop>::type Arg1Type;
            typedef typename StropReturnType<const Arg2Strop>::type Arg2Type;
            typedef typename StropReturnType<const Arg3Strop>::type Arg3Type;
            typedef typename StropReturnType<const Arg4Strop>::type Arg4Type;
            typedef typename F::template result<F(Arg1Type,Arg2Type,Arg3Type,Arg4Type)>::type R; 
            typedef const boost::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type,Arg4Type)> > type;         
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename Arg4Strop, 
        typename State>
        typename result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   const Arg2Strop arg2, 
                   const Arg3Strop arg3, 
                   const Arg4Strop arg4, 
                   State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            typedef result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)> Result;        
            typedef Func4<F
            ,typename Result::Arg1Type
            ,typename Result::Arg2Type
            ,typename Result::Arg3Type
            ,typename Result::Arg4Type
            > FuncStropType; 
            
            boost::shared_ptr<FuncStropType> funcStropPtr(new FuncStropType(f)); 
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg4Stream(arg4->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream, arg4Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1->GetDescriptor(), funcStropPtr->GetDescriptor(), arg1Stream);
            engine->AddEdgeToGraph(arg2->GetDescriptor(), funcStropPtr->GetDescriptor(), arg2Stream);
            engine->AddEdgeToGraph(arg3->GetDescriptor(), funcStropPtr->GetDescriptor(), arg3Stream);
            engine->AddEdgeToGraph(arg4->GetDescriptor(), funcStropPtr->GetDescriptor(), arg4Stream);
            return funcStropPtr;
        }
        
        // Arity = 5
        template<typename F, 
                 typename Arg1Strop, 
                 typename Arg2Strop, 
                 typename Arg3Strop, 
                 typename Arg4Strop, 
                 typename Arg5Strop, 
                 typename State>
        struct result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,Arg5Strop,State)>
        {
            typedef typename StropReturnType<const Arg1Strop>::type Arg1Type;
            typedef typename StropReturnType<const Arg2Strop>::type Arg2Type;
            typedef typename StropReturnType<const Arg3Strop>::type Arg3Type;
            typedef typename StropReturnType<const Arg4Strop>::type Arg4Type;
            typedef typename StropReturnType<const Arg5Strop>::type Arg5Type;
            typedef typename F::template result<F(Arg1Type,Arg2Type,Arg3Type,Arg4Type,Arg5Type)>::type R; 
            typedef const boost::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type,Arg4Type,Arg5Type)> > type;         
        };
        
        template<typename F, 
                 typename Arg1Strop, 
                 typename Arg2Strop, 
                 typename Arg3Strop, 
                 typename Arg4Strop, 
                 typename Arg5Strop, 
                 typename State>
        typename result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,Arg5Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   const Arg2Strop arg2, 
                   const Arg3Strop arg3, 
                   const Arg4Strop arg4, 
                   const Arg5Strop arg5, 
                   State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            typedef result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,Arg5Strop,State)> Result;        
            typedef Func5<F
                        ,typename Result::Arg1Type
                        ,typename Result::Arg2Type
                        ,typename Result::Arg3Type
                        ,typename Result::Arg4Type
                        ,typename Result::Arg5Type
                        > FuncStropType; 
            
            boost::shared_ptr<FuncStropType> funcStropPtr(new FuncStropType(f)); 
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg3Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            typename BaseType<Arg4Strop>::type::OutputStreamPtr arg4Stream(arg4->MakeOutputStream());
            typename BaseType<Arg5Strop>::type::OutputStreamPtr arg5Stream(arg5->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream, arg4Stream, arg5Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1->GetDescriptor(), funcStropPtr->GetDescriptor(), arg1Stream);
            engine->AddEdgeToGraph(arg2->GetDescriptor(), funcStropPtr->GetDescriptor(), arg2Stream);
            engine->AddEdgeToGraph(arg3->GetDescriptor(), funcStropPtr->GetDescriptor(), arg3Stream);
            engine->AddEdgeToGraph(arg4->GetDescriptor(), funcStropPtr->GetDescriptor(), arg4Stream);
            engine->AddEdgeToGraph(arg5->GetDescriptor(), funcStropPtr->GetDescriptor(), arg5Stream);
            return funcStropPtr;
        }

    };
    
    template<typename F, typename CallableDummy = proto::callable>
    struct lib_unary_func : proto::callable
    {
        template<typename Sig> struct result;
        
        template<typename ArgStrop, typename State>
        struct result<lib_unary_func(ArgStrop,State)> 
        : generic_func::result<generic_func(F&,ArgStrop,State)> 
        {};    
        
        template<typename ArgStrop, typename State>
        typename result<lib_unary_func(ArgStrop,State)>::type
        operator()(const ArgStrop arg, State engine)
        {
            generic_func gf;
            F func;
            if (engine->IsVerbose())            
                std::cout << "builtin func: " << typeid(func).name() << std::endl;
            return gf(func,arg,engine);
        }
    };

    template<typename F, typename CallableDummy = proto::callable>
    struct lib_binary_func : proto::callable
    {
        template<typename Sig> struct result;
        
        template<typename LhsStrop, typename RhsStrop, typename State>
        struct result<lib_binary_func(LhsStrop,RhsStrop,State)> 
        : generic_func::result<generic_func(F&,LhsStrop,RhsStrop,State)> 
        {};    
        
        template<typename LhsStrop, typename RhsStrop, typename State>
        typename result<lib_binary_func(LhsStrop,RhsStrop,State)>::type
        operator()(const LhsStrop left, const RhsStrop right, State engine)
        {
            generic_func gf;
            F func;
            if (engine->IsVerbose())
                std::cout << "builtin func: " << typeid(func).name() << std::endl;
            return gf(func,left,right,engine);
        }
    };
        
} // ns streamulus
