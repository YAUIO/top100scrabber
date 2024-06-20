cmake_minimum_required(VERSION 3.28)
project(top100scrabber)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
set(BUILD_SHARED_LIBS FALSE)

FETCHCONTENT_DECLARE(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

FETCHCONTENT_MAKEAVAILABLE(SFML)

add_executable(top100scrabber main.cpp)

target_link_libraries(top100scrabber sfml-graphics)

