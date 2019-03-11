//======================================================================
/*! \file testIbeoLux.cpp
 * \copydoc Copyright
 * \author Xue Chong(xc)
 * \date March 11, 2019
 *
 * project for receiving msg from ibeo node.
 *///-------------------------------------------------------------------

// ibeo headers
#include "ibeosdk/Time.hpp"

// protobuf headers
#include "msgs/Ibeo.pb.h"
#include "msgs/Geometry.pb.h"

// zmq headers
#include "zmq/zhelpers.hpp"

//
#include <iostream>
#include <cstdlib>

int main(const int argc, const char** argv){

    //  Prepare our context and subscriber
    zmq::context_t context(1);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://127.0.0.1:5563");
    std::cout << "debug 0" << std::endl;
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "ibeoLuxObjList", 1);
    Ibeo_msg::ObjectLuxList objLuxList;

    while (1) {


                //  Read envelope with address
                std::string address = s_recv (subscriber);
                std::cout << "[  address ] :" << address << std::endl;

                //  Read message contents
                std::string contents = s_recv (subscriber);
                objLuxList.ParseFromString(contents.c_str());

                for(int i=0; i < objLuxList.objects_size(); i++){
                    std::cout << objLuxList.objects(i).objectid() << std::endl;
                }

                //std::cout<<"objectID is "<< objLuxList.objectid() << std::endl;
                //std::cout<<"targetSpeed is "<<control.targetspeed() << std::endl;
    }

    return 0;
}
