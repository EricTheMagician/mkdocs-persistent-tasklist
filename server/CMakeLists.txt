cmake_minimum_required(VERSION 3.6.0)
set(CMAKE_CXX_STANDARD 17)

Project(mkdocs-persistent-tasklist LANGUAGES CXX)

# generate the protobuf source
find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS src/protobuf/tasks.proto)

include(./src/dependencies.cmake)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/services/tasks.cpp
    src/server.hpp src/server.cpp
    src/database/database.hpp src/database/database.cpp
    src/detail/database/database.hpp src/detail/database/database.cpp
    src/config.hpp
    ${PROTO_SRCS} ${PROTO_HDRS}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    httplib
    sqlite_orm
    protobuf::libprotobuf
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    src
)
