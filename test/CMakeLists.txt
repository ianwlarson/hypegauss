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

add_executable(hpgs_tests hpgs_tests.c ${lib_srcs})

target_link_libraries(hpgs_tests PUBLIC Unity)
#add_library(seatuna.dll SHARED IMPORTED)
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY LINK_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "ldir='${dir}'")
endforeach()
add_library(seatuna SHARED IMPORTED)
SET_PROPERTY(TARGET seatuna PROPERTY IMPORTED_LOCATION ${SEATUNA_ROOT_DIR}/bin/libseatuna.dll)
SET_PROPERTY(TARGET seatuna PROPERTY IMPORTED_IMPLIB ${SEATUNA_ROOT_DIR}/lib/libseatuna.dll.a)
target_link_libraries(hpgs_tests PUBLIC seatuna)

add_test(hpgs_tests hpgs_tests)
