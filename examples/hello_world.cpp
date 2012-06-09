//
//  hello_world.cpp
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

#include "../include/streamulus.h"


// Functor that prints whatever it gets. 
// Stremify<print> is a stream function that prints every
// element of a stream.
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
    
    // Construct a streamulus instance
    Streamulus streamulus_engine;            
    
    // Define some constants
    std::string hello("Hello ");
    std::string exc("!");

    // For each element of the stream: 
    //     compute a greeting
    //     print it 
    //     emit it into the output stream
    // 
    // the output is assined to the 'greeting' variable, 
    // which can be used in other streamulus expressions. 
    // 
    Subscription<std::string>::type greeting = 
        streamulus_engine.Subscribe<std::string>(Streamify<print>(hello + s + exc));
    
    // Use the 'greeting' variable in other streamulus expressions. 
    streamulus_engine.Subscribe(Streamify<print>(std::string("Well, ") + greeting ));
    streamulus_engine.Subscribe(Streamify<print>(std::string("I said: ") + greeting  + exc));
    
    // Insert data to the input stream
    InputStreamPut<std::string>(s, "World");
    InputStreamPut<std::string>(s, "London");
    InputStreamPut<std::string>(s, "Streamulus");    
}

