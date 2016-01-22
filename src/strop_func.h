//
//  strop_func.h
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


#include <sstream>

#include <boost/optional.hpp>

#include "strop.h"

namespace streamulus {
    template<typename R, typename...Args>
    class FuncBase : public Strop<R(Args...)> {
    public:

        FuncBase(const std::function<R(Args...)>& f)
                : mFunction(f), mInputExists(false) {
            std::stringstream ss;
            ss << "Func_" << "F";
            Strop<R(Args...)>::SetDisplayName(ss.str());
        }

        R Apply(Args...args) {
            return mFunction(args...);
        }

    protected:
        bool mInputExists;

    private:
        std::function<R(Args...)> mFunction;
    };


    template<class F,
            typename R = typename std::result_of<F(void)>::type>
    class Func0 : public FuncBase<R> {
    public:

        using BaseType = FuncBase<R>;

        Func0(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {
            StropStreamProducer<R>::Output(BaseType::Apply());
        }
    };


    template<class F,
            typename A1,
            typename R = typename std::result_of<F(A1)>::type>
    class Func1 : public FuncBase<R, A1> {
    public:

        using BaseType = FuncBase<R, A1>;
        using StropType = Strop<R(A1)>;

        Func1(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {
            BaseType::mInputExists |= StropType::IsValid();

            if (BaseType::mInputExists) {
                while (StropType::HasMore()) {
                    Stream<A1> *const input1 = StropType::template Input<0>();
                    StropStreamProducer<R>::Output(BaseType::Apply(input1->Current()));
                }
            }
        }
    };

    template<class F,
            typename A1,
            typename A2,
            typename R =typename std::result_of<F(A1, A2)>::type>
    class Func2 : public FuncBase<R, A1, A2> {
    public:

        using BaseType = FuncBase<R, A1, A2>;
        using StropType = Strop<R(A1, A2)>;

        Func2(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {
            BaseType::mInputExists |= StropType::IsValid();

            if (BaseType::mInputExists) {
                while (StropType::HasMore()) {
                    Stream<A1> *const input1 = StropType::template Input<0>();
                    Stream<A2> *const input2 = StropType::template Input<1>();

                    StropStreamProducer<R>::Output(BaseType::Apply(
                            input1->Current(),
                            input2->Current()
                    ));
                }
            }
        }
    };

    template<class F,
            typename A1,
            typename A2,
            typename A3,
            typename R =typename std::result_of<F(A1, A2, A3)>::type>
    class Func3 : public FuncBase<R, A1, A2, A3> {
    public:

        using BaseType = FuncBase<R, A1, A2, A3>;
        using StropType = Strop<R(A1, A2, A3)>;

        Func3(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {
            BaseType::mInputExists |= StropType::IsValid();

            if (BaseType::mInputExists) {
                while (StropType::HasMore()) {
                    Stream<A1> *const input1 = StropType::template Input<0>();
                    Stream<A2> *const input2 = StropType::template Input<1>();
                    Stream<A3> *const input3 = StropType::template Input<2>();

                    StropStreamProducer<R>::Output(BaseType::Apply(
                            input1->Current(),
                            input2->Current(),
                            input3->Current()
                    ));
                }
            }
        }
    };

    template<class F,
            typename A1,
            typename A2,
            typename A3,
            typename A4,
            typename R = typename std::result_of<F(A1, A2, A3, A4)>::type>
    class Func4 : public FuncBase<R, A1, A2, A3, A4> {
    public:

        using BaseType = FuncBase<R, A1, A2, A3, A4>;
        using StropType = Strop<R(A1, A2, A3, A4)>;

        Func4(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {
            BaseType::mInputExists |= StropType::IsValid();

            if (BaseType::mInputExists) {
                while (StropType::HasMore()) {
                    Stream<A1> *const input1 = StropType::template Input<0>();
                    Stream<A2> *const input2 = StropType::template Input<1>();
                    Stream<A3> *const input3 = StropType::template Input<2>();
                    Stream<A4> *const input4 = StropType::template Input<3>();

                    StropStreamProducer<R>::Output(BaseType::Apply(
                            input1->Current(),
                            input2->Current(),
                            input3->Current(),
                            input4->Current()
                    ));
                }
            }
        }
    };

    template<class F,
            typename A1,
            typename A2,
            typename A3,
            typename A4,
            typename A5,
            typename R = typename std::result_of<F(A1, A2, A3, A4, A5)>::type>
    class Func5 : public FuncBase<R, A1, A2, A3, A4, A5> {
    public:

        using BaseType = FuncBase<R, A1, A2, A3, A4, A5>;
        using StropType = Strop<R(A1, A2, A3, A4, A5)>;

        Func5(const F &f)
                : BaseType(f) {
        }

        virtual void Work() {

            BaseType::mInputExists |= StropType::IsValid();

            if (BaseType::mInputExists) {
                while (StropType::HasMore()) {
                    Stream<A1> *const input1 = StropType::template Input<0>();
                    Stream<A2> *const input2 = StropType::template Input<1>();
                    Stream<A3> *const input3 = StropType::template Input<2>();
                    Stream<A4> *const input4 = StropType::template Input<3>();
                    Stream<A5> *const input5 = StropType::template Input<4>();

                    StropStreamProducer<R>::Output(BaseType::Apply(
                            input1->Current(),
                            input2->Current(),
                            input3->Current(),
                            input4->Current(),
                            input5->Current()
                    ));
                }
            }
        }
    };


} // ns streamulus
