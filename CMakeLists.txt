# Copyright 2016 Ian W. Larson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project("libhpgs" C)
cmake_minimum_required(VERSION 3.0)

enable_testing()

add_compile_options(-std=c99)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(external)
include_directories(${external_includes})
link_directories(${external_libs})

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

add_subdirectory(test)

add_library(libhpgs SHARED ${lib_srcs})

install(TARGETS libhpgs
        LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib
        RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
        ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)

if (UNITY_ROOT_DIR AND SEATUNA_ROOT_DIR)
    message(STATUS "Testing enabled.")
else()
    message(WARNING "Tests cannot be compiled without Unity. Set UNITY_ROOT_DIR.")
endif()

message(STATUS "${PROJECT_SOURCE_DIR}")
