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
    
    // ////////////////////////////// Operator expressions //////////////////////////////
    
#define STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(TAG, RULE, FUNCTOR) \
template<> \
struct smls_grammar_cases::case_<TAG> \
: proto::or_<proto::when<RULE, lib_func<FUNCTOR>(smls_grammar(proto::_child), proto::_state)> >{}; 

    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::unary_plus, unary_plus_rule, unary_plus_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::negate, negate_rule, negate_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::dereference, dereference_rule, dereference_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::complement, complement_rule, complement_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::address_of, address_of_rule, address_of_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::logical_not, logical_not_rule, logical_not_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::pre_inc, prefix_inc_rule, prefix_inc_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::pre_dec, prefix_dec_rule, prefix_dec_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::post_inc, postfix_inc_rule, postfix_inc_func);
    STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE(proto::tag::post_dec, postfix_dec_rule, postfix_dec_func);

#undef STREAMULUS_GRAMMAR_UNARY_OPERATOR_CASE
    
    
#define STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(TAG, RULE, FUNCTOR) \
    template<> \
    struct smls_grammar_cases::case_<TAG> \
    : proto::or_<proto::when<RULE, \
        lib_func<FUNCTOR>(smls_grammar(proto::_left),smls_grammar(proto::_right), proto::_state)  \
    > > {}; 

    
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::shift_left, shift_left_rule, shift_left_func);                                       
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::shift_right, shift_right_rule, shift_right_func);                                       
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::multiplies, multiplies_rule, multiplies_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::divides, divides_rule, divides_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::modulus, modulus_rule, modulus_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::plus, plus_rule, plus_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::minus, minus_rule, minus_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::less, less_rule, less_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::greater, greater_rule, greater_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::less_equal, less_eq_rule, less_eq_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::greater_equal, greater_eq_rule, greater_eq_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::equal_to, equal_rule, equal_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::not_equal_to, not_equal_rule, not_equal_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::logical_or, logical_or_rule, logical_or_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::logical_and, logical_and_rule, logical_and_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_or, bitwise_or_rule, bitwise_or_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_and, bitwise_and_rule, bitwise_and_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_xor, bitwise_xor_rule, bitwise_xor_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::comma, comma_rule, comma_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::assign, assign_rule, assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::shift_left_assign, lshift_assign_rule, lshift_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::shift_right_assign, rshift_assign_rule, rshift_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::multiplies_assign, mult_assign_rule, mult_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::divides_assign, div_assign_rule, div_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::modulus_assign, mod_assign_rule, mod_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::plus_assign, plus_assign_rule, plus_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::minus_assign, minus_assign_rule, minus_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_and_assign, bitand_assign_rule, bitand_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_or_assign, bitor_assign_rule, bitor_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::bitwise_xor_assign, bitxor_assign_rule, bitxor_assign_func);
    STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE(proto::tag::subscript, subscript_rule, subscript_func);

#undef STREAMULUS_GRAMMAR_BINARY_OPERATOR_CASE
    
    template<>
    struct smls_grammar_cases::case_<proto::tag::function>
    : proto::or_< 
        proto::when<function_0_rule, 
                    generic_func(smls_grammar(proto::_child0), proto::_state)
        >
        , proto::when<function_1_rule, 
                    generic_func(smls_grammar(proto::_child0), 
                                 smls_grammar(proto::_child1), 
                                 proto::_state)
        >
        , proto::when<function_2_rule, 
                      generic_func(smls_grammar(proto::_child0), 
                                   smls_grammar(proto::_child1),
                                   smls_grammar(proto::_child2),
                                   proto::_state)
        >
        , proto::when<function_3_rule, 
                      generic_func(smls_grammar(proto::_child0), 
                                   smls_grammar(proto::_child1), 
                                   smls_grammar(proto::_child2), 
                                   smls_grammar(proto::_child3), 
                                   proto::_state) 
        >
        , proto::when<function_4_rule, 
                      generic_func(smls_grammar(proto::_child0),
                                   smls_grammar(proto::_child1),
                                   smls_grammar(proto::_child2),
                                   smls_grammar(proto::_child3),
                                   smls_grammar(proto::_child4),
                                   proto::_state)
        >
        , proto::when<function_5_rule,
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