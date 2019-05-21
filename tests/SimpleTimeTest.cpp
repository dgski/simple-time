#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "../SimpleTime.h"
#include <string>

TEST_CASE("Read datetime from const char*")
{
    SimpleTime t{"2012/01/01 18:21:33", DEFAULT_DATETIME_FORMAT};
    const tm& tt = t.getTimeStruct();

    REQUIRE(tt.tm_year == 112);
    REQUIRE(tt.tm_mon == 0);
    REQUIRE(tt.tm_mday == 1);
    REQUIRE(tt.tm_hour == 18);
    REQUIRE(tt.tm_min == 21);
    REQUIRE(tt.tm_sec == 33);
}

TEST_CASE("Read datetime from string")
{
    std::string s{"2005/05/10 12:10:10"};
    SimpleTime t{s,DEFAULT_DATETIME_FORMAT};
    const tm& tt = t.getTimeStruct();

    REQUIRE(tt.tm_year == 105);
    REQUIRE(tt.tm_mon == 4);
    REQUIRE(tt.tm_mday == 10);
    REQUIRE(tt.tm_hour == 12);
    REQUIRE(tt.tm_min == 10);
    REQUIRE(tt.tm_sec == 10);   
}

TEST_CASE("Format output to string object properly")
{
    SimpleTime t{"2018/02/01 15:01:03", DEFAULT_DATETIME_FORMAT};
    std::string s = t.toString(DEFAULT_DATETIME_FORMAT);

    REQUIRE(s == "2018/02/01 15:01:03");
}

TEST_CASE("< operator")
{
    SimpleTime t1{"2010/08/03", DEFAULT_DATE_FORMAT};
    SimpleTime t2{"2020/08/04", DEFAULT_DATE_FORMAT};

    REQUIRE(t1 < t2);
}

TEST_CASE("== operator")
{
    SimpleTime t1{"2018/04/01 00:03:01", DEFAULT_DATETIME_FORMAT};
    SimpleTime t2{"2018/04/01 00:03:01", DEFAULT_DATETIME_FORMAT};

    REQUIRE(t1 == t2);
}

TEST_CASE("> operator")
{
    SimpleTime t1{"2022/07/03 00:00:01", DEFAULT_DATETIME_FORMAT};
    SimpleTime t2{"2022/07/03 00:00:00", DEFAULT_DATETIME_FORMAT};

    REQUIRE(t1 > t2);
}