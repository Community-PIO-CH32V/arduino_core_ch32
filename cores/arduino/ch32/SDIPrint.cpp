#include <SDIPrint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

#define DEBUG_DATA0_ADDRESS  ((volatile uint32_t*)0xE00000F4)
#define DEBUG_DATA1_ADDRESS  ((volatile uint32_t*)0xE00000F8)

SDIPrint::SDIPrint() {}

SDIPrint::~SDIPrint() {}

void SDIPrint::enable()
{
    *(DEBUG_DATA0_ADDRESS) = 0;
    Delay_Init();
    Delay_Ms(1);
}


bool SDIPrint::is_busy()
{
    return *(DEBUG_DATA0_ADDRESS) != 0;
}


size_t SDIPrint::write_str(const uint8_t *buf, size_t size)
{
    size_t i = 0;
    while (i < size) {
        while (is_busy()) {}
        if (size - i > 7) {
            *(DEBUG_DATA1_ADDRESS) = (*(buf+i+3)) | (*(buf+i+4)<<8) | (*(buf+i+5)<<16) | (*(buf+i+6)<<24);
            *(DEBUG_DATA0_ADDRESS) = (7u) | (*(buf+i)<<8) | (*(buf+i+1)<<16) | (*(buf+i+2)<<24);
            i = i + 7;
        } else {
            *(DEBUG_DATA1_ADDRESS) = (*(buf+i+3)) | (*(buf+i+4)<<8) | (*(buf+i+5)<<16) | (*(buf+i+6)<<24);
            *(DEBUG_DATA0_ADDRESS) = (size - i) | (*(buf+i)<<8) | (*(buf+i+1)<<16) | (*(buf+i+2)<<24);
            i = size;
        }
    }
    while (is_busy()) {}
    return i;
}

size_t SDIPrint::println(const char* str)
{
    return write_str((const uint8_t *)str, strlen(str)) + write_str("\n", 1);
}

size_t SDIPrint::println(const String &s)
{
    return write_str((const uint8_t *)(s + '\n').c_str(), s.length() + 1);
}

size_t SDIPrint::print(const String &s)
{
    return write_str((const uint8_t *)s.c_str(), s.length());
}

size_t SDIPrint::print(const char* str)
{
    return write_str((const uint8_t *)str, strlen(str));
}

size_t SDIPrint::print(const char* str, u_int len)
{
    return write_str((const uint8_t *)str, len);
}

SDIPrint SDIprint = SDIPrint();