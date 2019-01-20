//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

#include "POS320.pb.h"

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    Pos_msg::pos320 msg;

    //int BUFFSIZE = 256;
    //char buff[BUFFSIZE];

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        //memcpy(testString.c_str(), &(request.data()),strlen(request.data()));
        //testString = request.data();
        //testString.data() = request.data();
        std::string testString(static_cast<char*>(request.data()), request.size());
        msg.ParseFromString(testString.c_str());
        std::cout << "Received: " << msg.lat() <<  std::endl;

        //  Do some 'work'
    	sleep(1);

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply);
    }
    return 0;
}
