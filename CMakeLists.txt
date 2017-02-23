cmake_minimum_required (VERSION 3.6)

project(fub_constrained CXX)

add_definitions('-g')
add_definitions('-Wall')
add_definitions('-Wextra')
add_definitions('-Wfatal-errors')
add_definitions('-std=c++1z')
add_definitions('-fconcepts')
add_definitions('-g')
add_definitions('-pedantic')

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/third-party/cmcstl2/include")
include_directories("${PROJECT_SOURCE_DIR}/third-party/Catch/include")

add_executable(constrained "test/constrained.t.cpp")
