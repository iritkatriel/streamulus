//
//  grammar.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include "transforms.h"
#include "operators.h"

#include <boost/proto/proto.hpp>

namespace streamulus
{
    
    
    struct smls_grammar;
    
    // ************************************** RULES **************************************
    
    // terminals
    struct strop_terminal_rule     : proto::terminal<boost::shared_ptr<proto::_> > {};
    struct function_terminal_rule  : proto::terminal<proto::_>                     {};
    
    //operators
    struct unary_plus_rule         : proto::unary_plus         <smls_grammar>              {};
    struct negate_rule             : proto::negate             <smls_grammar>              {};
    struct dereference_rule        : proto::dereference        <smls_grammar>              {};
    struct complement_rule         : proto::complement         <smls_grammar>              {};
    struct address_of_rule         : proto::address_of         <smls_grammar>              {};
    struct logical_not_rule        : proto::logical_not        <smls_grammar>              {};
    struct prefix_inc_rule         : proto::pre_inc            <smls_grammar>              {};
    struct prefix_dec_rule         : proto::pre_dec            <smls_grammar>              {};
    struct postfix_inc_rule        : proto::post_inc           <smls_grammar>              {};
    struct postfix_dec_rule        : proto::post_dec           <smls_grammar>              {};
    struct shift_left_rule         : proto::shift_left         <smls_grammar,smls_grammar> {};
    struct shift_right_rule        : proto::shift_right        <smls_grammar,smls_grammar> {};
    struct multiplies_rule         : proto::multiplies         <smls_grammar,smls_grammar> {};
    struct divides_rule            : proto::divides            <smls_grammar,smls_grammar> {};
    struct modulus_rule            : proto::modulus            <smls_grammar,smls_grammar> {};
    struct plus_rule               : proto::plus               <smls_grammar,smls_grammar> {};
    struct minus_rule              : proto::minus              <smls_grammar,smls_grammar> {};
    struct less_rule               : proto::less               <smls_grammar,smls_grammar> {};
    struct greater_rule            : proto::greater            <smls_grammar,smls_grammar> {};
    struct less_eq_rule            : proto::less_equal         <smls_grammar,smls_grammar> {};
    struct greater_eq_rule         : proto::greater_equal      <smls_grammar,smls_grammar> {};
    struct equal_rule              : proto::equal_to           <smls_grammar,smls_grammar> {};
    struct not_equal_rule          : proto::not_equal_to       <smls_grammar,smls_grammar> {};
    struct logical_or_rule         : proto::logical_or         <smls_grammar,smls_grammar> {};
    struct logical_and_rule        : proto::logical_and        <smls_grammar,smls_grammar> {};
    struct bitwise_or_rule         : proto::bitwise_or         <smls_grammar,smls_grammar> {};
    struct bitwise_and_rule        : proto::bitwise_and        <smls_grammar,smls_grammar> {};
    struct bitwise_xor_rule        : proto::bitwise_xor        <smls_grammar,smls_grammar> {};
    struct comma_rule              : proto::comma              <smls_grammar,smls_grammar> {};
    struct mem_ptr_rule            : proto::mem_ptr            <smls_grammar,smls_grammar> {};
    struct assign_rule             : proto::assign             <smls_grammar,smls_grammar> {};
    struct lshift_assign_rule      : proto::shift_left_assign  <smls_grammar,smls_grammar> {};
    struct rshift_assign_rule      : proto::shift_right_assign <smls_grammar,smls_grammar> {};
    struct mult_assign_rule        : proto::multiplies_assign  <smls_grammar,smls_grammar> {};
    struct div_assign_rule         : proto::divides_assign     <smls_grammar,smls_grammar> {};
    struct mod_assign_rule         : proto::modulus_assign     <smls_grammar,smls_grammar> {};
    struct plus_assign_rule        : proto::plus_assign        <smls_grammar,smls_grammar> {};
    struct minus_assign_rule       : proto::minus_assign       <smls_grammar,smls_grammar> {};
    struct bitand_assign_rule      : proto::bitwise_and_assign <smls_grammar,smls_grammar> {};
    struct bitor_assign_rule       : proto::bitwise_or_assign  <smls_grammar,smls_grammar> {};
    struct bitxor_assign_rule      : proto::bitwise_xor_assign <smls_grammar,smls_grammar> {};
    struct subscript_rule          : proto::subscript          <smls_grammar,smls_grammar> {};
    struct if_else_rule            : proto::if_else_           <smls_grammar,smls_grammar,smls_grammar> {};
    
    
    // TODO: make the generic version
    // struct function_rule         : proto::function<proto::terminal<proto::_>,proto::vararg<smls_grammar> > {};
    
    struct function_0_rule : proto::function<proto::terminal<proto::_> > {};
    struct function_1_rule : proto::function<proto::terminal<proto::_>,smls_grammar> {};
    struct function_2_rule : proto::function<proto::terminal<proto::_>,smls_grammar,smls_grammar> {};
    struct function_3_rule : proto::function<proto::terminal<proto::_>,smls_grammar,smls_grammar,smls_grammar> {};
    struct function_4_rule : proto::function<proto::terminal<proto::_>,smls_grammar,smls_grammar,smls_grammar,smls_grammar> {};
    struct function_5_rule : proto::function<proto::terminal<proto::_>,smls_grammar,smls_grammar,smls_grammar,smls_grammar,smls_grammar> {};
    
    
    
    // ************************************** GRAMMAR **************************************
    
    struct smls_grammar;
    
    struct smls_grammar_cases
    {
        // The primary template matches nothing:
        template<typename Tag>
        struct case_
        : proto::not_<proto::_>
        {};
    };
    
    // Terminal expressions 
    template<>
    struct smls_grammar_cases::case_<proto::tag::terminal>
    : proto::or_<
    proto::when<
    strop_terminal_rule, 
    AddStropToGraph(proto::_value,proto::_state)
    >  
    , proto::when<
    function_terminal_rule,
    proto::_value
    >
    >
    {};
    
    // Operator expressions 
    template<>
    struct smls_grammar_cases::case_<proto::tag::unary_plus>
    : proto::or_<
    proto::when<
    unary_plus_rule, 
    proto::_value 
    >
    >
    {};
    
    template<>
    struct smls_grammar_cases::case_<proto::tag::plus>
    : proto::or_<
    proto::when<
    plus_rule, 
    lib_func<plus_func>(smls_grammar(proto::_left),smls_grammar(proto::_right) ,proto::_state) 
    >
    >
    {};
    
    template<>
    struct smls_grammar_cases::case_<proto::tag::minus>
    : proto::or_<
    proto::when<
    minus_rule, 
    lib_func<minus_func>(smls_grammar(proto::_left),smls_grammar(proto::_right) ,proto::_state) 
    > 
    >
    {};
    
    
    template<>
    struct smls_grammar_cases::case_<proto::tag::function>
    : proto::or_< 
    proto::when<
    function_0_rule, 
    generic_func(smls_grammar(proto::_child0),
                 proto::_state)
    >
    , proto::when<
    function_1_rule, 
    generic_func(smls_grammar(proto::_child0),
                 smls_grammar(proto::_child1),
                 proto::_state)
    >
    , proto::when<
    function_2_rule, 
    generic_func(smls_grammar(proto::_child0),
                 smls_grammar(proto::_child1),
                 smls_grammar(proto::_child2),
                 proto::_state)
    >
    , proto::when<
    function_3_rule, 
    generic_func(smls_grammar(proto::_child0), 
                 smls_grammar(proto::_child1), 
                 smls_grammar(proto::_child2), 
                 smls_grammar(proto::_child3), 
                 proto::_state) 
    >
    , proto::when<
    function_4_rule, 
    generic_func(smls_grammar(proto::_child0),
                 smls_grammar(proto::_child1),
                 smls_grammar(proto::_child2),
                 smls_grammar(proto::_child3),
                 smls_grammar(proto::_child4),
                 proto::_state)
    >
    , proto::when<
    function_5_rule,
    generic_func(smls_grammar(proto::_child0),
                 smls_grammar(proto::_child1),
                 smls_grammar(proto::_child2),
                 smls_grammar(proto::_child3),
                 smls_grammar(proto::_child4),
                 smls_grammar(proto::_child5),
                 proto::_state)
    >
    >
    {};
    
    
    // The grammar
    struct smls_grammar
    : proto::switch_<smls_grammar_cases>
    {};
    
    
} // ns streamulus