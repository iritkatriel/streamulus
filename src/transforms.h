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
#include "strop_func.h"
#include "strop_sliding_window.h"
#include "input_stream.h"
#include "strop_return_type.h"
#include "funcs.h"
#include "cpp14_utils.h"

#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits.hpp>


namespace streamulus
{
    
    using namespace boost;
        
    //////////////////////////// Utilities ////////////////////////////
    template<typename T>
    struct BaseType
    {
        static const bool value = false;
    };
    
    template<typename Type>
    struct BaseType<std::shared_ptr<Type> >
    {
        static const bool value = true;
        using type = Type;
    };
    
    template<typename Sig>
    struct MakeStropPtrType
    {  
        using type = std::shared_ptr<Strop<Sig> >;
    };
         
    //////////////////////////// Transforms ////////////////////////////
    
    struct AddStropToGraph : proto::callable  
    {
        template<typename StropType, class State>
        const StropType operator()(StropType strop, State engine)
        {
            if (!strop->GetEngine())
            {
                engine->AddVertexToGraph(strop);
                engine->AddSource(strop);
            }
            if (engine->IsVerbose())
                std::cout << "AddStropToGraph: " << strop << " returning " << strop->GetDescriptor() << std::endl; 
            return strop;
        }
    };

    
    struct generic_func : proto::callable
    {
        template<typename Sig> struct result;
        
        // Arity = 0
        template<typename FArg, typename State>
        struct result<generic_func(FArg,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using R = typename F::template result<F()>::type;
            using type = const std::shared_ptr<Strop<R()>>;
        };
        
        template<typename F, typename State>
        typename result<generic_func(const F&,State)>::type
        operator()(const F& f, State engine)
        {  
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            using FuncStropType = Func0<F>;

            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddSource(funcStropPtr);
            return funcStropPtr;
        }        
        
        // Arity = 1
        template<typename FArg, 
        typename Arg1Strop, 
        typename State>
        struct result<generic_func(FArg,Arg1Strop,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using Arg1Type = typename StropReturnType<const Arg1Strop>::type;
            using  R = typename std::result_of<F(Arg1Type)>::type;
            using type = const std::shared_ptr<Strop<R(Arg1Type)>>;
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename State>
        typename result<generic_func(const F&,Arg1Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   State engine)
        {  
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            using Result = result<generic_func(F&,Arg1Strop,State)>;
            using FuncStropType = Func1<F,typename Result::Arg1Type>;

            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1, funcStropPtr, arg1Stream);
            return funcStropPtr;
        }

        // Arity = 2
        template<typename FArg, typename Arg1Strop, typename Arg2Strop, typename State>
        struct result<generic_func(FArg,Arg1Strop,Arg2Strop,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using Arg1Type = typename StropReturnType<const Arg1Strop>::type;
            using Arg2Type = typename StropReturnType<const Arg2Strop>::type;
            using R = typename std::result_of<F(Arg1Type,Arg2Type)>::type;
            using type = const std::shared_ptr<Strop<R(Arg1Type,Arg2Type)>>;
        };
        
        template<typename F, typename Arg1Strop, typename Arg2Strop, typename State>
        typename result<generic_func(const F&,Arg1Strop,Arg2Strop, State)>::type
        operator()(const F& f,const Arg1Strop arg1, const Arg2Strop arg2, State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            using Result = result<generic_func(F&,Arg1Strop,Arg2Strop, State)>;
            using FuncStropType = Func2<F, typename Result::Arg1Type, typename Result::Arg2Type>;
            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1, funcStropPtr, arg1Stream);
            engine->AddEdgeToGraph(arg2, funcStropPtr, arg2Stream);
            return funcStropPtr;
        }

        // Arity = 3
        template<typename FArg, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename State>
        struct result<generic_func(FArg,Arg1Strop,Arg2Strop,Arg3Strop,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using Arg1Type = typename StropReturnType<const Arg1Strop>::type;
            using Arg2Type = typename StropReturnType<const Arg2Strop>::type;
            using Arg3Type = typename StropReturnType<const Arg3Strop>::type;
            using R = typename std::result_of<F(Arg1Type,Arg2Type,Arg3Type)>::type;
            using type = const std::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type)> >;
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename State>
        typename result<generic_func(const F&,Arg1Strop,Arg2Strop,Arg3Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   const Arg2Strop arg2, 
                   const Arg3Strop arg3, 
                   State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            using Result = result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,State)>;
            using FuncStropType = Func3<F
            ,typename Result::Arg1Type
            ,typename Result::Arg2Type
            ,typename Result::Arg3Type
            >;

            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg3Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1, funcStropPtr, arg1Stream);
            engine->AddEdgeToGraph(arg2, funcStropPtr, arg2Stream);
            engine->AddEdgeToGraph(arg3, funcStropPtr, arg3Stream);
            return funcStropPtr;
        }
        
        // Arity = 4
        template<typename FArg, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename Arg4Strop, 
        typename State>
        struct result<generic_func(FArg,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using Arg1Type = typename StropReturnType<const Arg1Strop>::type;
            using Arg2Type = typename StropReturnType<const Arg2Strop>::type;
            using Arg3Type = typename StropReturnType<const Arg3Strop>::type;
            using Arg4Type = typename StropReturnType<const Arg4Strop>::type;
            using R = typename std::result_of<F(Arg1Type,Arg2Type,Arg3Type,Arg4Type)>::type;
            using type = const std::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type,Arg4Type)> >;
        };
        
        template<typename F, 
        typename Arg1Strop, 
        typename Arg2Strop, 
        typename Arg3Strop, 
        typename Arg4Strop, 
        typename State>
        typename result<generic_func(const F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)>::type
        operator()(const F& f,
                   const Arg1Strop arg1, 
                   const Arg2Strop arg2, 
                   const Arg3Strop arg3, 
                   const Arg4Strop arg4, 
                   State engine)
        {   
            if (engine->IsVerbose())
                std::cout << "generic_func" << std::endl;
            using Result = result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,State)>;
            using FuncStropType = Func4<F
            ,typename Result::Arg1Type
            ,typename Result::Arg2Type
            ,typename Result::Arg3Type
            ,typename Result::Arg4Type
            >;

            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg3Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            typename BaseType<Arg4Strop>::type::OutputStreamPtr arg4Stream(arg4->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream, arg4Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1, funcStropPtr, arg1Stream);
            engine->AddEdgeToGraph(arg2, funcStropPtr, arg2Stream);
            engine->AddEdgeToGraph(arg3, funcStropPtr, arg3Stream);
            engine->AddEdgeToGraph(arg4, funcStropPtr, arg4Stream);
            return funcStropPtr;
        }
        
        // Arity = 5
        template<typename FArg, 
                 typename Arg1Strop, 
                 typename Arg2Strop, 
                 typename Arg3Strop, 
                 typename Arg4Strop, 
                 typename Arg5Strop, 
                 typename State>
        struct result<generic_func(FArg,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,Arg5Strop,State)>
        {
            using F = remove_const_t<remove_reference_t<FArg>>;
            using Arg1Type = typename StropReturnType<const Arg1Strop>::type;
            using Arg2Type = typename StropReturnType<const Arg2Strop>::type;
            using Arg3Type = typename StropReturnType<const Arg3Strop>::type ;
            using Arg4Type = typename StropReturnType<const Arg4Strop>::type ;
            using Arg5Type = typename StropReturnType<const Arg5Strop>::type;
            using R = typename std::result_of<F(Arg1Type,Arg2Type,Arg3Type,Arg4Type,Arg5Type)>::type;

            using type = const std::shared_ptr<Strop<R(Arg1Type,Arg2Type,Arg3Type,Arg4Type,Arg5Type)>>;
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
            using Result = result<generic_func(F&,Arg1Strop,Arg2Strop,Arg3Strop,Arg4Strop,Arg5Strop,State)>;
            using FuncStropType = Func5<F
                        ,typename Result::Arg1Type
                        ,typename Result::Arg2Type
                        ,typename Result::Arg3Type
                        ,typename Result::Arg4Type
                        ,typename Result::Arg5Type
                        >;

            std::shared_ptr<FuncStropType> funcStropPtr = std::make_shared<FuncStropType>(f);
            
            typename BaseType<Arg1Strop>::type::OutputStreamPtr arg1Stream(arg1->MakeOutputStream());
            typename BaseType<Arg2Strop>::type::OutputStreamPtr arg2Stream(arg2->MakeOutputStream());
            typename BaseType<Arg3Strop>::type::OutputStreamPtr arg3Stream(arg3->MakeOutputStream());
            typename BaseType<Arg4Strop>::type::OutputStreamPtr arg4Stream(arg4->MakeOutputStream());
            typename BaseType<Arg5Strop>::type::OutputStreamPtr arg5Stream(arg5->MakeOutputStream());
            funcStropPtr->SetInputs(boost::fusion::make_vector(arg1Stream, arg2Stream, arg3Stream, arg4Stream, arg5Stream));
            
            engine->AddVertexToGraph(funcStropPtr);
            engine->AddEdgeToGraph(arg1, funcStropPtr, arg1Stream);
            engine->AddEdgeToGraph(arg2, funcStropPtr, arg2Stream);
            engine->AddEdgeToGraph(arg3, funcStropPtr, arg3Stream);
            engine->AddEdgeToGraph(arg4, funcStropPtr, arg4Stream);
            engine->AddEdgeToGraph(arg5, funcStropPtr, arg5Stream);
            return funcStropPtr;
        }

    };
      

    struct HandleTerminal : proto::callable  
    {
        template<class Sig> struct result;
        
        // Case 1: terminal is a shared_ptr to a strop 
        template<class This, class StropType, class State>
        struct result<This(const std::shared_ptr<StropType>&,State)>
        {
            using StropPtrType = const std::shared_ptr<StropType>&;
            using type = typename std::result_of<AddStropToGraph(StropPtrType,State)>::type;
        };
        
        template<class This, class StropType, class State>
        struct result<This(std::shared_ptr<StropType>,State)>
        : result<This(const std::shared_ptr<StropType>&,State)>
        {};
        
        template<typename StropType, class State>
        typename boost::enable_if<BaseType<StropType>, typename result<HandleTerminal(StropType ,State)>::type>::type
        operator()(StropType strop, State engine)
        {
            return AddStropToGraph()(strop, engine);
        }
        
        // Final case: Terminal is any other constant
        template<class This, class ConstType, class State>
        struct result<This(ConstType,State)>
        {
            using ConstFuncResultType = typename ConstFunc<ConstType>::template result<ConstFunc<ConstType>(ConstType)>::type;
            using type = const std::shared_ptr<Strop<ConstFuncResultType()>>;
        };
        
        template<typename ConstType, class State>
        typename boost::disable_if<BaseType<ConstType>, typename result<HandleTerminal(ConstType ,State)>::type>::type
        operator()(ConstType const_value, State engine)
        {
            using T = typename result<HandleTerminal(ConstType ,State)>::ConstFuncResultType;
            return generic_func()(ConstFunc<T>(const_value),engine);
        }
         
    };

    
    struct SlidingWindow : proto::callable
    {
        template<typename Sig> struct result;
        
        template<typename ArgStrop, typename State>
        struct result<SlidingWindow(const int&,ArgStrop,State)>
        {
            using input_type = typename StropReturnType<const ArgStrop>::type;
            using result_type = WindowUpdateType<input_type>;
            using type = const std::shared_ptr<StropStreamProducer<result_type> >;
        };
        
        template<typename ArgStrop, typename State>
        typename result<SlidingWindow(const int&,ArgStrop,State)>::type
        operator()(const int& size, const ArgStrop arg, State engine)
        {
            using WindowStropType = Window<typename StropReturnType<const ArgStrop>::type>;
            std::shared_ptr<WindowStropType> strop = std::make_shared<WindowStropType>(size);

            typename BaseType<ArgStrop>::type::OutputStreamPtr argStream(arg->MakeOutputStream());
            strop->SetInputs(boost::fusion::make_vector(argStream));
            
            engine->AddVertexToGraph(strop);
            engine->AddEdgeToGraph(arg, strop, argStream);
            return strop;
        }        
    };
    
        
    
    
} // ns streamulus
