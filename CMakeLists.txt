cmake_minimum_required(VERSION 3.19)

project(IntentRecognizer CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "main.cpp")

include_directories(source/header)
include_directories(/usr/local/include)

add_subdirectory(googletest)
add_subdirectory(utest)
add_subdirectory(source)

add_executable(IntentRecognizer ${Sources})
target_link_libraries(IntentRecognizer PUBLIC
	IntentRecognizerLib
)
