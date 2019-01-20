//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include "POS320.pb.h"

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("tcp://localhost:5555");

    Pos_msg::pos320 msg;
    msg.set_num(100);
    msg.set_lat(39.88);
    std::string buff;
    msg.SerializeToString(&buff);
    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        zmq::message_t request(buff.length()+1);
        memcpy (request.data() , buff.c_str(), buff.length());
        std::cout << buff <<"\t" <<request_nbr << "..." << std::endl;
        socket.send (request);
        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        //std::cout << "Received World " << request_nbr << std::endl;
    }
    return 0;
}
