cmake_minimum_required(VERSION 3.26)
project(BoostChatNetwork)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost 1.83.0 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            ${Boost_INCLUDE_DIRS}
        PRIVATE
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ws2_32
            wsock32
        PRIVATE
            ${Boost_LIBRARIES}
)