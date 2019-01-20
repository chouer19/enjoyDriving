PROJECT(zmq_examples)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

find_package(cppzmq)
find_package(libzmq)

# proto msgs
include_directories(${PROTOINCLUDEDIR})

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
target_link_libraries(hwclient cppzmq proto ${PROTOBUF_LIBRARIES})

# simple server demo
add_executable(hwserver hwserver.cpp)
target_link_libraries(hwserver cppzmq proto ${PROTOBUF_LIBRARIES})

# psenvpub, publish example
add_executable(
    psenvpub
    psenvpub.cpp
    zhelpers.hpp
)
target_link_libraries(psenvpub cppzmq proto ${PROTOBUF_LIBRARIES})

# psenvsub, subscribe example
add_executable(
    psenvsub
    psenvsub.cpp
    zhelpers.hpp
)
target_link_libraries(psenvsub cppzmq proto ${PROTOBUF_LIBRARIES})

# pubProto, publish protobuf msg example
add_executable(
    pubProto
    pubProto.cpp
    zhelpers.hpp
)
target_link_libraries(pubProto cppzmq proto ${PROTOBUF_LIBRARIES})

# subProto, sublish protobuf msg example
add_executable(
    subProto
    subProto.cpp
    zhelpers.hpp
)
target_link_libraries(subProto cppzmq proto ${PROTOBUF_LIBRARIES})

