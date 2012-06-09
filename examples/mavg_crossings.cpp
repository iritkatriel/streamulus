//
//  mavg_crossings.cpp
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

#include <iostream>

// -------------------------------------------------------------------
// This example implements and algorithm to detect crossings of two 
// moving averages of a time series.
// The input is given as {time, value} pairs.
// We have a slow-decaying moving average and a fast-decaying one.
// When they cross we issue an alert (in this case print to the 
// screen). We distinguish between Death Crosses (where the slow
// mavg crosses the fast one from below, so the time series is 
// decreasing) and Golden Crosses (where it crosses from above, 
// so the time series is increasing). 
// --------------------------------------------------------------------

// time-value pair
struct TimeValue
{
    TimeValue()
        : time(0)
        , value(0)
    {
    }
    
    TimeValue(clock_t t, double v)
        : time(t)
        , value(v)
    {
    }
    
    friend std::ostream& operator<<(std::ostream& os, const TimeValue& tv)
    {
        return os << "{" << tv.time << "," << tv.value << "}";
    }
    
    clock_t time;
    double value;
};

// Exponentially decaying moving average
template<int DecayFactor>
class Mavg
{
public:
    
    Mavg()
    : mMavg(0)
    , mFirst(true)
    {
    }
    
    template<class Sig> 
    struct result 
    {
        typedef double type; 
    };
    
    double operator()(const TimeValue& tick) 
    {
        if (! mFirst)
        {
            double alpha = 1-1/exp(DecayFactor*(tick.time-mPrevTime));
            mMavg += alpha*(tick.value - mMavg);
            mPrevTime = tick.time;
        }
        else
        {
            mMavg = tick.value;
            mPrevTime = tick.time;
            mFirst = false;
        }
        return mMavg;
    }
    
private:
    double mMavg;  
    clock_t mPrevTime;    
    bool mFirst;
};

// Remove consecutive repetitions from a stream. 
template<typename T>
class unique
{
public:
    
    unique()  
        : mFirst(true) 
    {
    }
    
    template<class Sig> 
    struct result 
    {
        typedef T type; 
    };
    
    bool Filter(const T& value) 
    {
        bool have_output(mFirst || (value != mPrev));
        mFirst = false;
        mPrev = value;
        return have_output;
    }
    
    T operator()(const T& value) const 
    { 
        return mPrev;
    }
    
private:
    bool mFirst; 
    T mPrev;
};


// Print an alert when a cross comes. Value indicates 
// the type of the cross.
struct cross_alert
{
    template<class Sig> 
    struct result 
    {
        typedef bool type; 
    };
    
    
    bool operator()(const bool is_golden_cross) 
    {
        if (is_golden_cross)
            std::cout << "Golden cross detected!" << std::endl;
        else
            std::cout << "Death cross detected!" << std::endl;
        
        return is_golden_cross;
    }
    
};

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


// Return whatever you got as a string. This is useful 
// for printing sub-expression results within a string
// (converting to string allows + with other strings).
struct as_string 
{    
    template<class Sig> struct result;
    
    template<class This,typename T>
    struct result<This(T)>
    {
        typedef std::string type; 
    };
    
    template<typename T>
    typename result<print(T)>::type
    operator()(const T& value) const
    { 
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
};


void cross_alert_example()
{
    using namespace streamulus;
    
    InputStream<TimeValue>::type ts = NewInputStream<TimeValue>("TS");
    Streamulus engine;

    // The moving averages:
    Subscription<double>::type slow = engine.Subscribe<double>(Streamify<Mavg<1> >(ts));
    Subscription<double>::type fast = engine.Subscribe<double>(Streamify<Mavg<10> >(ts));

    // Print the moving averages:
    engine.Subscribe(Streamify<print>(std::string("Slow Mavg = ") + Streamify<as_string>(slow)));
    engine.Subscribe(Streamify<print>(std::string("Fast Mavg = ") + Streamify<as_string>(fast)));

    // The cross detection expression:
    engine.Subscribe(Streamify<cross_alert>( Streamify<unique<bool> >(slow < fast)));

    for (int i=0; i<15; i++)
        InputStreamPut(ts, TimeValue(i, i % 5));
}
