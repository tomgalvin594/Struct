#################################################################################
##
## BOX2D C++ Library
## Copyright (c) 2011-2014 Jan Haller
##                    2015 Thomas Galvin
## 
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the auBOX2Ds be held liable for any damages
## arising from the use of this software.
## 
## Permission is granted to anyone to use this software for any purpose,
## including commercial applications, and to alter it and redistribute it
## freely, subject to the following restrictions:
## 
## 1. The origin of this software must not be misrepresented; you must not
##    claim that you wrote the original software. If you use this software
##    in a product, an acknowledgment in the product documentation would be
##    appreciated but is not required.
## 
## 2. Altered source versions must be plainly marked as such, and must not be
##    misrepresented as being the original software.
## 
## 3. This notice may not be removed or altered from any source distribution.
##
#################################################################################

# This script locates the Box2D C++ Library
# It is basically an exact copy of FindThor.cmake,
# which is itself based on FindSFML.cmake
# ========================================
#
# Usage
# -----
#
# Box2D's libraries use the same configuration (static/dynamic linking) as SFML's.
# If the variable SFML_STATIC_LIBRARIES is set to TRUE before calling find_package(Box2D),
# the static libraries of Box2D are found. Otherwise, the dynamic ones are found.
#
# If Box2D is not installed in a standard path, you can use the BOX2D_ROOT CMake (or environment) variable
# to tell CMake where Box2D is.
#
# Output
# ------
#
# This script defines the following variables:
# - BOX2D_LIBRARY_DEBUG:   Name of the debug library (set to BOX2D_LIBRARY_RELEASE if no debug version is found)
# - BOX2D_LIBRARY_RELEASE: Name of the release library (set to BOX2D_LIBRARY_DEBUG if no release version is found)
# - BOX2D_LIBRARY:		  Name of the library to link to (includes both debug and release names if necessary)
# - BOX2D_INCLUDE_DIR:	  The path where BOX2D headers are located (the directory containing the BOX2D/Config.hpp file)
# - BOX2D_FOUND:		      Is TRUE if at least one of the debug or release library is found
#
# Usage example:
# 
#   find_package(Box2D 2 REQUIRED)
#   include_directories(${BOX2D_INCLUDE_DIR})
#   target_link_libraries(MyProject ${BOX2D_LIBRARY})


# Deduce the libraries suffix from the options
set(FINDBOX2D_LIB_SUFFIX "")
if(SFML_STATIC_LIBRARIES)
	set(FINDBOX2D_LIB_SUFFIX "-s")
endif()

# Find the SFML include directory
find_path(BOX2D_INCLUDE_DIR Box2D/Box2D.h
		  PATH_SUFFIXES include
		  PATHS
		  ${BOX2D_ROOT}
		  $ENV{BOX2D_ROOT}
		  /usr/local/
		  /usr/
		  /sw          # Fink
		  /opt/local/  # DarwinPorts
		  /opt/csw/    # Blastwave
		  /opt/)

# Find the requested modules
set(BOX2D_FOUND TRUE) # will be set to false if one of the required modules is not found
set(FINDBOX2D_LIB_PATHS
	${BOX2D_ROOT}
	$ENV{BOX2D_ROOT}
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt)

# Debug library
find_library(BOX2D_LIBRARY_DEBUG
			 NAMES Box2D${FINDBOX2D_LIB_SUFFIX}-d
			 PATH_SUFFIXES lib64 lib
			 PATHS ${FINDBOX2D_LIB_PATHS})

# Release library
find_library(BOX2D_LIBRARY_RELEASE
			 NAMES Box2D${FINDBOX2D_LIB_SUFFIX}
			 PATH_SUFFIXES lib64 lib
			 PATHS ${FINDBOX2D_LIB_PATHS})

if(BOX2D_LIBRARY_DEBUG OR BOX2D_LIBRARY_RELEASE)
	# Library found
	set(BOX2D_FOUND TRUE)

	# If both are found, set BOX2D_LIBRARY to contain both
	if(BOX2D_LIBRARY_DEBUG AND BOX2D_LIBRARY_RELEASE)
		set(BOX2D_LIBRARY debug	 ${BOX2D_LIBRARY_DEBUG}
						 optimized ${BOX2D_LIBRARY_RELEASE})
	endif()

	# If only one debug/release variant is found, set the other to be equal to the found one
	if(BOX2D_LIBRARY_DEBUG AND NOT BOX2D_LIBRARY_RELEASE)
		# debug and not release
		set(BOX2D_LIBRARY_RELEASE ${BOX2D_LIBRARY_DEBUG})
		set(BOX2D_LIBRARY		 ${BOX2D_LIBRARY_DEBUG})
	endif()
	if(BOX2D_LIBRARY_RELEASE AND NOT BOX2D_LIBRARY_DEBUG)
		# release and not debug
		set(BOX2D_LIBRARY_DEBUG ${BOX2D_LIBRARY_RELEASE})
		set(BOX2D_LIBRARY	   ${BOX2D_LIBRARY_RELEASE})
	endif()
else()
	# Library not found
	set(BOX2D_FOUND FALSE)
	set(BOX2D_LIBRARY "")
	set(FINDBOX2D_MISSING "${FINDBOX2D_MISSING} BOX2D_LIBRARY")
endif()

# Mark variables as advanced
mark_as_advanced(BOX2D_INCLUDE_DIR
				 BOX2D_LIBRARY
				 BOX2D_LIBRARY_RELEASE
				 BOX2D_LIBRARY_DEBUG)

# Result
if(BOX2D_FOUND)
	# Success
	message("-- Found Box2D in ${BOX2D_INCLUDE_DIR}")
else()
	# include directory or library not found
	set(FINDBOX2D_ERROR "Could NOT find Box2D (missing: ${FINDBOX2D_MISSING})")

	if(BOX2D_FIND_REQUIRED)
		# Fatal error
		message(FATAL_ERROR ${FINDBOX2D_ERROR})
	elseif(NOT BOX2D_FIND_QUIETLY)
		# Error, but continue
		message("${FINDBOX2D_ERROR}")
	endif()
endif()
