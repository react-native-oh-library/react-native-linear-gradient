
cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB rnoh_linear_gradient_SRC CONFIGURE_DEPENDS *.cpp)
add_library(rnoh_linear_gradient SHARED ${rnoh_linear_gradient_SRC})
target_include_directories(rnoh_linear_gradient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rnoh_linear_gradient PUBLIC rnoh)