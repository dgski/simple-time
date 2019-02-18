# SimpleTime
SimpleTime provides the basic essential datetime functionality:
- Reading from time_t unix time.
- Reading from string using specified format.
- Outputting time_t unix time.
- Outputting a string representation using specified format.
- Sortability.

Fundamentally it is a convenient wrapper class for the various time utilies provided by **time.h**. Format string is specified with the same characters as the [get_time function](https://en.cppreference.com/w/cpp/io/manip/get_time).

## Examples
``` c++
// Get and Output Current Local Date
SimpleTime t;
t.setNowLocal();
output << t.toString("%Y/%m/%d");

// Set UTC using time_t
time_t example;
t.setUTC(example);

// Read datetime From String
string sample {"1994 10:10:00"};
t.set(sample,"%Y %H:%M:%S");

```

## Provided Public Methods
| Method | Description |
|------------|-------------|
| void **set**(T timeString, const char* fmt) | Set value of object given the following input and format strings.|
| void **setNowLocal**() | Set value of object to the current datetime using local timezone.|
| void **setNowUTC**() | Set value of object to the current datetime using UTC.|
| void **setLocal**(time_t input) | Set value of the object using local timezone and the provided time_t.|
| void **setUTC**(time_t input) | Set value of the object using UTC and the provided time_t.|
| const tm& **getTimeStruct**() const | Get the internal time struct from time.h.|
| string **toString**(const char* fmt) const | Provided a desired format, returns the string representation of it's current value.|
| time_t **toTimeT**() | Get the time_t unix time current value of the object.|
| bool **isEqual**(const SimpleTime& other) const | Object is equal in value to the provided argument.|
| bool **isBefore**(const SimpleTime& other) const | Object's time value comes before the provided argument.|
| bool **isAfter**(const SimpleTime& other) const | Object's time value comes after the provided argument.|

## Provided Operators
| Operator | Description |
|----------|-------------|
| static bool **operator<** (const SimpleTime& a, const SimpleTime& b)  | Calls **isBefore** method of first object with second object as argument.|
| static bool **operator==** (const SimpleTime& a, const SimpleTime& b) | Calls **isEqual** method of first object with second object as argument.|
| static bool **operator>** (const SimpleTime& a, const SimpleTime& b)  | Calls **isAfter** method of first object with second object as argument.|


