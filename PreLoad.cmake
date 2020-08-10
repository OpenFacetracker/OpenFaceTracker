if (WIN32)
	# set generator to NMake
	set (CMAKE_GENERATOR "NMake Makefiles" CACHE INTERNAL "" FORCE)
	
	# set vcpkg toolchain file
	if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
			CACHE STRING "")
	endif()
endif (WIN32)