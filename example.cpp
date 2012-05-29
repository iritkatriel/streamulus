//
//  example.cpp
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

// #include <iostream>

#include "include/streamulus.h"

struct print 
{    
    template<class Sig> struct result;
    
    template<class This,typename T>
    struct result<This(T)>
    {
        typedef T type; 
    };
    
    template<typename T>
    typename result<print(T)>::type
    operator()(const T& value) const
    { 
        std::cout << value << std::endl;
        return value;
    }
};


void hello_stream()
{
    using namespace streamulus;

    InputStream<std::string>::type s = NewInputStream<std::string>("Input Stream");
    
    Engine streamulus;            
    
    std::string hello("Hello ");
    std::string exc("!");
    
    Subscription<std::string>::type greeting = 
        streamulus.Subscribe<std::string>(Streamify<print>(hello + s + exc));
    
    streamulus.Subscribe(Streamify<print>(std::string("Well, ") + greeting ));
    streamulus.Subscribe(Streamify<print>(std::string("I said: ") + greeting  + exc));
    
    InputStreamPut<std::string>(s, "World");
    InputStreamPut<std::string>(s, "London");
    InputStreamPut<std::string>(s, "Streamulus");    
}

