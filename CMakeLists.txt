# Define minimum CMAKE version required
cmake_minimum_required(VERSION 3.4)

# Set Compilation mode
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

# Set program and library names
set(PROG_NAME oftapp)
set(LIB_NAME oft)

# Fix cmake try compilation
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set project name
project(${PROG_NAME})

#----------------------------------------------------------------------------------
#                                   BUILD BINARY
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
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
        set(CMAKE_CXX_STANDARD 11)
        set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
    endif (MSVC14)
endif (UNIX)

add_subdirectory(${CMAKE_SOURCE_DIR}/libsrc)

# Configure sources depends
file(GLOB SRCS CMAKE_CONFIGURE_DEPENDS 
	${CMAKE_SOURCE_DIR}/appsrc/*
)

include_directories(${CMAKE_SOURCE_DIR}/appsrc ${CMAKE_SOURCE_DIR}/libsrc/include)

# Set executable output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Add executable
add_executable(${PROG_NAME} ${SRCS})

# Link executable to library
target_link_libraries(${PROG_NAME} ${LIB_NAME})

# Move lib dll from /lib to /bin POST_BUILD
add_custom_command(TARGET ${PROG_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/${LIB_NAME}.dll ${CMAKE_SOURCE_DIR}/bin/${LIB_NAME}.dll
)