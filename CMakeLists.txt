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
include ( ${CMAKE_CURRENT_LIST_DIR}/resources/macros.cmake )

# project
project ( staticlib_utils CXX )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 1.3.0 )
set ( ${PROJECT_NAME}_DESCRIPTION "Staticlibs common utilities library" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/staticlib_utils )

# docs
option ( ${PROJECT_NAME}_ENABLE_DOCS "Generate doxyfile and exit build" OFF )
if ( ${PROJECT_NAME}_ENABLE_DOCS )
    configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )
    return ( )
endif ( )

# library
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include )

# pkg-config
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${CMAKE_CURRENT_LIST_DIR}/include" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -l${PROJECT_NAME}" )
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} )
endif ( )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/${PROJECT_NAME}.pc )
