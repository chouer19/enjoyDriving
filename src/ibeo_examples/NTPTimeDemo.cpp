#include "ibeosdk/Time.hpp"
#include <iostream>

using namespace ibeosdk;

int main(const int argc, const char** argv){
    //beosdk::NTPTime ptime ibeosdk::NTPTime.getInvalidTime();
    //NTPTime nptTime = NTPTime::getInvalidTime();
    NTPTime nptTime = NTPTime();
    nptTime.setFromPTime(Time::localTime());
    std::cout<< "ptime.getSeconds(): " << nptTime.getSeconds() << std::endl;
    std::cout<< "ptime.getMilliseconds(): " << nptTime.getMilliseconds() << std::endl;

    return 0;
}
