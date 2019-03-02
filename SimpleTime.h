#include <string>
#include <iomanip>
#include <sstream>
#include <functional>
#include <iostream>

#define DEFAULT_DATETIME_FORMAT "%Y/%m/%d %H:%M:%S"
#define DEFAULT_DATE_FORMAT "%Y/%m/%d"

class SimpleTime
{
    tm t;

    bool compare(const SimpleTime& other, std::function<bool(int,int)> func) const
    {
        const tm& o = other.getTimeStruct();

        if(func(t.tm_year, o.tm_year))      return false;
        if(func(t.tm_mon, o.tm_mon))        return false;
        if(func(t.tm_mday, o.tm_mday))      return false;
        if(func(t.tm_hour, o.tm_hour))      return false;
        if(func(t.tm_min, o.tm_min))        return false;
        if(func(t.tm_sec, o.tm_sec))        return false;

        return true;
    }

public:
    SimpleTime() : t()
    {}

    template <class T>
    SimpleTime(T timeString, const char* fmt)
    {
        set(timeString, fmt);
    }

    template <class T>
    void set(T timeString, const char* fmt)
    {
        std::stringstream ss {timeString};
        ss >> std::get_time(&t, fmt);
    }

    void setNowLocal()
    {
        setLocal(time(nullptr));
    }

    void setNowUTC()
    {
        setUTC(time(nullptr));
    }

    void setLocal(time_t input)
    {
        const tm * _t = localtime(&input);
        t = *_t;
    }

    void setUTC(time_t input)
    {
        const tm * _t = localtime(&input);
        t = *_t;
    }

    const tm& getTimeStruct() const
    {
        return t;
    }

    std::string toString(const char* fmt) const
    {
        std::stringstream ss;
        ss << std::put_time(&t, fmt);
        return ss.str();
    }

    time_t toTimeT()
    {
        return mktime(&t);
    }

    bool isEqual(const SimpleTime& other) const
    {
        return compare(other, [](auto a, auto b)
        {
            return a != b;
        });
    }

    bool isBefore(const SimpleTime& other) const
    {
        return compare(other, [](const auto a, const auto b)
        {
            return a > b;
        });
    }

    bool isAfter(const SimpleTime& other) const
    {
        return compare(other, [](const auto a, const auto b)
        {
            return a < b;
        });
    }
};

static bool operator< (const SimpleTime& a, const SimpleTime& b)
{
    return a.isBefore(b);
}

static bool operator== (const SimpleTime& a, const SimpleTime& b)
{
    return a.isEqual(b);
}

static bool operator> (const SimpleTime& a, const SimpleTime& b)
{
    return a.isAfter(b);
}

#pragma once