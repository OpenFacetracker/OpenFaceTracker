# Define minimum CMAKE version required
cmake_minimum_required(VERSION 3.4)

# Set Compilation mode
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

# Set program and library names
set(LIB_NAME oft)

# Fix cmake try compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set project name
project(${LIB_NAME} VERSION 6.0.0 LANGUAGES CXX)

message("Library build started")

#----------------------------------------------------------------------------------
#                                   BUILD LIBRARY
#----------------------------------------------------------------------------------

# Treat all warnings as error
if (UNIX)
    if (CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    endif (CMAKE_COMPILER_IS_GNUCC)
elseif (WIN32)
	if (MSVC14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4251")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    endif (MSVC14)
endif (UNIX)

# Set library output path
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Configure library sources depends
file(GLOB LIB_SRCS CMAKE_CONFIGURE_DEPENDS 
    ./src/*.cpp
    )

# Configure library headers depends
file(GLOB LIB_HEADERS CMAKE_CONFIGURE_DEPENDS
    ./include/oft/*.hpp
	)

# Add a library to the project using the specified source files
add_library(${LIB_NAME} SHARED ${LIB_SRCS} ${LIB_HEADERS})

# Set include directory
set(INCLUDEDIR ${PROJECT_SOURCE_DIR}/include)

if (UNIX)
    # Include pkg-config
	include(FindPkgConfig)

	# Check OPENCV_LIBRARIES and OPENCV_INCLUDE_DIRS
	pkg_check_modules(OPENCV REQUIRED opencv)

	# Check JSON-C_LIBRARIES
	pkg_check_modules(JSON-C REQUIRED json-c)

	# Include directories of headers
	target_include_directories(${LIB_NAME} PUBLIC ${CPPDB_INCLUDE_DIR})
	target_include_directories(${LIB_NAME} PUBLIC ${INCLUDEDIR})
	target_include_directories(${LIB_NAME} PUBLIC ${OPENCV_INCLUDE_DIRS})
	target_include_directories(${LIB_NAME} PUBLIC ${X11_INCLUDE_DIR})

	# Add additional libraries
	find_package(Boost REQUIRED COMPONENTS filesystem)
	find_package(X11)
	find_package(Threads)
elseif (WIN32)
	
	# linking vcpkg library directory
	target_link_directories(${LIB_NAME} PUBLIC $ENV{VCPKG_LIB_X64})

	# Check OPENCV_LIBRARIES and OPENCV_INCLUDE_DIRS
	find_package(opencv REQUIRED)

	# Check nlohmann-json package
	find_package(nlohmann_json CONFIG REQUIRED)

	# Include directories of headers
	target_include_directories(${LIB_NAME} PUBLIC ${INCLUDEDIR})

	find_package(Boost CONFIG)

	#include CPPDB library
	find_path(CPPDB_INCLUDE_DIR cppdb/backend.h)
	find_library(CPPDB_LIBRARY cppdb)
	target_include_directories(${LIB_NAME} PUBLIC ${CPPDB_INCLUDE_DIR})

endif (UNIX)

# Check libcurl
find_package(CURL)
if (CURL_FOUND)
    # Include directories of headers
    target_include_directories(${LIB_NAME} PUBLIC ${CURL_INCLUDE_DIR})

	# Export Header
	include(GenerateExportHeader)
	generate_export_header(${LIB_NAME})

	# Move file generated export header to lib include dir as defs.hpp
	file(RENAME ${PROJECT_BINARY_DIR}/${LIB_NAME}_export.h ${INCLUDEDIR}/oft/defs.hpp)

    # Link a target to given libraries
    if (UNIX)
        if (CMAKE_COMPILER_IS_GNUCC)
            #target_link_libraries(${LIB_NAME} PUBLIC nlohmann-json ${OPENCV_LIBRARIES} ${CURL_LIBRARIES} ${X11_LIBRARIES} cppdb ${Boost_LIBRARIES})
        endif (CMAKE_COMPILER_IS_GNUCC)
    elseif (WIN32)
		if (MSVC14)
            target_link_libraries(${LIB_NAME} PUBLIC ${OpenCV_LIBS} libcurl cppdb boost_filesystem-vc140-mt)
        endif (MSVC14)
    endif (UNIX)
else (CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files")
endif (CURL_FOUND)

#-----------------------------------------------------------------------------------
#                                BUILD DOCUMENTATION
#-----------------------------------------------------------------------------------

# Check doxygen
#find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
    message("Doxygen not found, I will not generate/install the documentation")
elseif (DOXYGEN_FOUND)
    # Copies a doxygen <input> file to a doxygen <output> file
    configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_SOURCE_DIR}/doc/Doxyfile)

    # Set doxygen <input> and <output> file
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_SOURCE_DIR}/doc/Doxyfile)

    # Substitutes variable values referenced @ONLY
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Adds a target with the given name that executes the given commands
    add_custom_target( doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} > /dev/null
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating OpenFaceTracker-Lib6 documentation with Doxygen"
        VERBATIM )
endif (NOT DOXYGEN_FOUND)