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

if (UNITY_ROOT_DIR)
    message(STATUS "Unity testing suite located.")
    add_library(Unity STATIC ${UNITY_ROOT_DIR}/src/unity.c)
    target_include_directories(Unity PUBLIC ${UNITY_ROOT_DIR}/src)
endif()

if (SEATUNA_ROOT_DIR)
    message(STATUS "Seatuna RNG located.")
    set(external_includes "${external_includes};${SEATUNA_ROOT_DIR}/include")
    set(external_libs "${external_libs};${SEATUNA_ROOT_DIR}/lib")
endif()

set(external_includes ${external_includes} PARENT_SCOPE)
set(external_libs ${external_libs} PARENT_SCOPE)
