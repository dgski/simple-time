#include <string>
#include <iomanip>
#include <sstream>

#define DEFAULT_DATETIME_FORMAT "%Y/%m/%d %H:%M:%S"
#define DEFAULT_DATE_FORMAT "%Y/%m/%d"

class SimpleTime
{
    tm t;
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

    time_t toTimeT() const
    {
        tm _t = t;
        return mktime(&_t);
    }

    bool isEqual(const SimpleTime& other) const
    {
        return toTimeT() == other.toTimeT();
    }

    bool isBefore(const SimpleTime& other) const
    {
        return toTimeT() < other.toTimeT();
    }

    bool isAfter(const SimpleTime& other) const
    {
        return toTimeT() > other.toTimeT();
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