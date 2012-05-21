//
//  apply_filter.h
//  streamulus
//
//  Created by Irit Katriel on 16/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <boost/utility.hpp>
#include <boost/type_traits.hpp> 

namespace streamulus {

template <typename Type>
class HasFilter
{
    // SFINAE test for a bool Filter(...) function
    
    class yes { char m;};
    class no { yes m[2];};
        
    struct BaseMixin
    {
        bool Filter(){}
    };
        
    struct Base : public Type, public BaseMixin {};
        
    template <typename T, T t>    class Helper{};
        
    template <typename U>
    static no deduce(U*, Helper<bool (BaseMixin::*)(), &U::Filter>* = 0);
    static yes deduce(...);
        
public:
    static const bool value = (sizeof(yes) == sizeof(deduce((Base*)(0))));
};


template<typename F, typename A1>
typename boost::enable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1)
{
    return f.Filter(a1);
}
    
template<typename F, typename A1, typename A2>
typename boost::enable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2)
{
    return f.Filter(a1,a2);
}

template<typename F, typename A1, typename A2, typename A3>
typename boost::enable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3)
{
    return f.Filter(a1,a2,a3);
}

template<typename F, typename A1, typename A2, typename A3, typename A4>
typename boost::enable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
    return f.Filter(a1,a2,a3,a4);
}

template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5>
typename boost::enable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
    return f.Filter(a1,a2,a3,a4,a5);
}    

template<typename F, typename A1>
typename boost::disable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1)
{
    return true;
}
    
template<typename F, typename A1, typename A2>
typename boost::disable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2)
{
    return true;
}
    
template<typename F, typename A1, typename A2, typename A3>
typename boost::disable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3)
{
    return true;
}

template<typename F, typename A1, typename A2, typename A3, typename A4>
typename boost::disable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
    return true;
}
    
template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5>
typename boost::disable_if_c<HasFilter<F>::value, bool>::type
ApplyFilter(F& f, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
    return true;
}


} // ns streamulus
 