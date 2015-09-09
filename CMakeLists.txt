# Copyright 2015, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

# project
project ( staticlib_utils CXX )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 1.3.0 )

# pkg-config
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
endif ( )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/pkgconfig/${PROJECT_NAME}.pc.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/${PROJECT_NAME}.pc )

# library
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include )

# docs
if ( DEFINED STATICLIB_CMAKE )
    configure_file ( ${STATICLIB_CMAKE}/doxygen/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )
endif ( )
