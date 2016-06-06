# Copyright by Krzysztof Taperek, 2016
# Licensed under the MIT license:
# http://www.opensource.org/licenses/mit-license.php
#
# Author: Krzysztof Taperek <krzysztof.taperek@gmail.com>

cmake_minimum_required (VERSION 3.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

##########################################
## Project info
##########################################

set( PROJECT_NAME psoc-charts )
set( TARGET_NAME "${PROJECT_NAME}.out" )

if( WIN32 )
	set( TARGET_NAME "${PROJECT_NAME}" )
endif( WIN32 ) 

project( ${PROJECT_NAME} )

##########################################
## Compilation mode
##########################################

option( DEBUG_MODE "Add debug symbols to executive file" OFF)


##########################################
## EXE info
##########################################

file(GLOB_RECURSE TARGET_SRC src/*.cpp)
file(GLOB_RECURSE TARGET_HEADERS src/*.h src/*.hpp )

include_directories( src/ )

# compiler specific flags
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    # using clang
	add_definitions( -Wall  -Wextra )
	add_definitions( -std=c++14 )
	
	if( DEBUG_MODE )
		add_definitions( -g )
	else( DEBUG_MODE)
		add_definitions( -O2 )
	endif( DEBUG_MODE )
	
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
    # using gcc
	add_definitions( -Wall  -Wextra )
	add_definitions( -std=c++14 )
	
	if( DEBUG_MODE )
		add_definitions( -g )
	else( DEBUG_MODE)
		add_definitions( -O2 )
	endif( DEBUG_MODE )
	
elseif( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    # using msvc
	#add_definitions( -std=c++14 )
endif()

##########################################
## Linking libraries
##########################################

# Find LIBUSB
find_package(LIBUSB REQUIRED)
if( LIBUSB_FOUND )
  include_directories( ${LIBUSB_INCLUDE_DIR} )
  set( LIBRARIES ${LIBRARIES} ${LIBUSB_LIBRARY} )
endif( LIBUSB_FOUND )

###########################################
add_executable(${TARGET_NAME} ${TARGET_SRC} ${TARGET_HEADERS} )
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
###########################################


# Find wxWidgets
SET(wxWidgets_USE_STATIC ON)
SET(wxWidgets_WXCONFIG_OPTS "--static=yes")


   FIND_PACKAGE(wxWidgets COMPONENTS base core gl net aui)
   IF(wxWidgets_FOUND)
     INCLUDE(${wxWidgets_USE_FILE})
     # and for each of your dependant executable/library targets:
     TARGET_LINK_LIBRARIES(${TARGET_NAME} ${wxWidgets_LIBRARIES})
   ENDIF(wxWidgets_FOUND)


#find_package(wxWidgets REQUIRED net gl core base)
#find_package(wxWidgets REQUIRED core base)
#include(${wxWidgets_USE_FILE})

#if( WXWIDGETS_FOUND )

#  include_directories( ${WXWIDGETS_INCLUDE_DIR} )
#  set( LIBRARIES ${LIBRARIES} ${WXWIDGETS_LIBRARY} )
#endif( WXWIDGETS_FOUND )


