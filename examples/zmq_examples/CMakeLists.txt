PROJECT(zmq_examples)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

find_package(cppzmq)
#find_package(libzmq)

# proto msgs
#include_directories(${PROTOINCLUDEDIR})

# zmq_test
add_executable(
    zmq_test
    zmq_test.cpp
    )
target_link_libraries(
    zmq_test
    cppzmq
    )


# simple client demo
add_executable(hwclient hwclient.cpp)
target_link_libraries(hwclient cppzmq msgs ${PROTOBUF_LIBRARIES})

# simple server demo
add_executable(hwserver hwserver.cpp)
target_link_libraries(hwserver cppzmq msgs ${PROTOBUF_LIBRARIES})

# psenvpub, publish example
add_executable(
    psenvpub
    psenvpub.cpp
)
target_link_libraries(psenvpub cppzmq msgs ${PROTOBUF_LIBRARIES})

# psenvsub, subscribe example
add_executable(
    psenvsub
    psenvsub.cpp
)
target_link_libraries(psenvsub cppzmq msgs ${PROTOBUF_LIBRARIES})

# pubProto, publish protobuf msg example
add_executable(
    pubProto
    pubProto.cpp
)
target_link_libraries(pubProto cppzmq msgs ${PROTOBUF_LIBRARIES})

# subProto, sublish protobuf msg example
add_executable(
    subProto
    subProto.cpp
)
target_link_libraries(subProto cppzmq msgs ${PROTOBUF_LIBRARIES})

