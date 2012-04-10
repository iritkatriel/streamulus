//
//  unit_test_api.h
//
//  Copyright (c) 2012 Irit Katriel. All rights reserved.
//

#pragma once

#include <exception>

namespace streamulus
{
    struct unit_test_api
    {
        struct unit_test_failed : public std::exception
        {};

        virtual void Check(bool condition) throw(unit_test_failed)
        {
            if (!condition)
            {
                throw unit_test_failed();
            }
        }

        virtual void Run()=0;

    };

} // ns streamulus