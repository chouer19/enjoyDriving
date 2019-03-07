//======================================================================
/*! \file RuichengDriver.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date January 28, 2019
 * \date January 29, 2019
 * \date Febirary 02, 2019
 *///-------------------------------------------------------------------
//======================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "zhelpers.hpp"
#include "Vehicle.pb.h"

class VehiclePort {
public:
    VehiclePort() {};
    VehiclePort(const string portName, const unsigned int baudRate ):m_portName(portName), m_portBaudRate(baudRate) {
    };
    bool Clear(){
        if(this.isOpen()){return false;}
        this.m_portBaudRate = 0;
        return true;
    };
    bool Open(){
        if(this.m_portBaudRate == 0){
            return false;
        }
        return false;
    };
    bool Open(const string portName, const unsigned int baudRate){
        this.m_portName = portName;
        this.m_portBaudRate = baudRate;

        boost::asio::serial_port pos320_sp(this.m_io);
        pos320_sp.set_option(boost::asio::serial_port_base::baud_rate(this.m_portBaudRate));
        pos320_sp.set_option(boost::asio::serial_port_base::character_size(8));
        pos320_sp.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        pos320_sp.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
        pos320_sp.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

        this.m_port = pos320_sp;

        this.m_port.open(this.m_portName, this.m_ec);
        this.m_opened = this.m_port.is_open();
        if( !this.m_port.is_open()){
            std::cout << "port not opened" << std::endl;
        }else{
            std::cout << "port opened" << std::endl;
        }
        return this.m_opened;
    };
    bool Close(){
        if(!this.isOpen()){
            std::cout << "port of " <<this.m_portName << "was not opened yet!\n";
            return false;
        }
        this.m_port.close();
        this.m_opened = false;
        return true;
    };
    bool Write(const Car_msg::Ruicheng_control &command){
        return false;
    };
    bool Read(Car_msg::Ruicheng_feedback &feedback){
        return false;
    };
    bool isOpen(){
        return this.m_opened;
    }

private:
    boost::asio::serial_port m_port;
    boost::asio::io_service m_io;
    bool m_opened = false;
    boost::system::error_code m_ec;

pretected:
    string m_portName = "";
    unsigned int m_portBaudRate = 0;
}

class Bus {
public:
    Bus() {};
    Bus(const string portName, const unsigned int baudRate ):m_portName(portName), m_portBaudRate(baudRate) {};
    bool Open(){
        
        return false;
    };
    bool Open(const string portName, const unsigned int baudRate){
        return false;
    };
    bool Close(){
    };
    bool Write(Car_msg::Ruicheng_control command){
        return false;
    };
    bool Read(Car_msg::Ruicheng_feedback &feedback){
        return false;
    };

private:

pretected:
    string m_portName = "";
    unsigned int m_portBaudRate = 0;

}

int main(){
   return 0;
}
