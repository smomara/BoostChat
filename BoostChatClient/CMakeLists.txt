cmake_minimum_required(VERSION 3.26)
project(BoostChatClient)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        BoostChatNetwork
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        BoostChatNetwork
)