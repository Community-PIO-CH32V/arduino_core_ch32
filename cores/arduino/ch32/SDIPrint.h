#ifndef __SDI_PRINT_H_
#define __SDI_PRINT_H
#include <stdio.h>
#include "WString.h"

// usage
// #include <Arduino.h>
// #include <SDIPrint.h>
// 
// void setup()
// {	
//     SDIprint.enable();
//     SDIprint.print(String("log ") + "test");
//     SDIprint.println("log test", 9);
//     SDIprint.println("log test");
// }

class SDIPrint
{
    public:
    SDIPrint();
    ~SDIPrint();

    void enable();
    size_t write_str(const uint8_t *buf, size_t size);
    size_t SDIPrint::print(const char* str, u_int len);
    size_t SDIPrint::print(const char* str);
    size_t SDIPrint::print(const String &s);
    size_t SDIPrint::println(const String &s);
    size_t SDIPrint::println(const char* str);

    private:
    bool is_busy();
};

extern SDIPrint SDIprint;

#endif