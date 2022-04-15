cmake_minimum_required(VERSION 3.0)

project(managing_threads)

set (CMAKE_CXX_STANDARD_REQUIRED 17)

add_executable(callable_obj callable_obj.cpp)
add_executable(lambda lambda.cpp)
add_executable(thread_guard_ex thread_guard.cpp)
add_executable(joining_thread joining_thread.cpp)