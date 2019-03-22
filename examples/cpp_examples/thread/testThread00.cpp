//Create a C++11 thread from the main program

#include <iostream>
#include <thread>

//This function will be called from a thread

void call_from_thread() {
    for(int i=0;i<10;i++){
        std::cout << "1st Hello, World!" << std::endl;
    }
}

void call_from_thread2() {
    for(int i=0;i<10;i++){
        std::cout << "2st Hello, World!" << std::endl;
    }
}

int main() {
    //Launch a thread
    std::thread t1(call_from_thread);

    //Launch a thread
    std::thread t2(call_from_thread2);

    for(int i=0;i<10;i++){
        std::cout << "main Hello, World!" << std::endl;
    }

    //Join the thread with the main thread
    t1.join();
    t2.join();
    

    for(int i=0;i<10;i++){
        std::cout << "last Hello, World!" << std::endl;
    }

    return 0;
}
