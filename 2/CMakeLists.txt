cmake_minimum_required (VERSION 3.20)

set(TARGET_NAME "day3")
project ("Day3" VERSION 0.0.1)

add_executable(${TARGET_NAME} main.cpp)


find_package(fmt CONFIG REQUIRED)
target_link_libraries(${TARGET_NAME} PUBLIC fmt::fmt-header-only)


target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)
