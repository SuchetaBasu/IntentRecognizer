cmake_minimum_required(VERSION 3.19)

project(IntentRecognizerLib CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS "header/*.h")
file(GLOB_RECURSE Sources CONFIGURE_DEPENDS "src/*.cpp")

include_directories(header)
add_library(IntentRecognizerLib STATIC ${Headers} ${Sources})
