cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

project(Tekgin
	VERSION 0.0.1
	DESCRIPTION "Basic text adventure game engine"
	LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
set(CMAKE_CXX_MODULE_STD ON)

option(FORMAT "Enable clang-format run" OFF)

if(FORMAT)
	message(STATUS "Formatting files...")
	file(GLOB_RECURSE FORMAT_SOURCES CONFIGURE_DEPENDS
		"${CMAKE_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_SOURCE_DIR}/src/*.cppm"
	)

	foreach(FILE ${FORMAT_SOURCES})
		execute_process(COMMAND clang-format -i ${FILE})
	endforeach()
endif()

foreach(OUTPUTCONFIG RUNTIME LIBRARY ARCHIVE)
	foreach(CONFIG Debug Release RelWithDebInfo MinSizeRel)
		set(CMAKE_${OUTPUTCONFIG}_OUTPUT_DIRECTORY_${CONFIG}
			"${CMAKE_BINARY_DIR}/${CONFIG}/$<TARGET_NAME:tekgin>")
	endforeach()
endforeach()

# foreach(OUTPUTCONFIG RUNTIME LIBRARY ARCHIVE)
# 	set(CMAKE_${OUTPUTCONFIG}_OUTPUT_DIRECTORY
# 		"${CMAKE_BINARY_DIR}/$<TARGET_NAME:tekgin>")
# endforeach()

file(GLOB_RECURSE MODULE_INTERFACES CONFIGURE_DEPENDS "src/*.cppm")
file(GLOB_RECURSE MODULE_IMPLEMENTATIONS CONFIGURE_DEPENDS "src/*.cpp")

add_library(tekgin STATIC)

add_executable(tekgin_exec main.cpp)
target_link_libraries(tekgin_exec PUBLIC tekgin)

target_sources(tekgin
	PUBLIC
		FILE_SET CXX_MODULES
		BASE_DIRS "src"
		FILES ${MODULE_INTERFACES}
	PRIVATE
		${MODULE_IMPLEMENTATIONS})

target_compile_features(tekgin PUBLIC cxx_std_23)

add_compile_options(
	PRIVATE
	$<$<CXX_COMPILER_ID:Clang>:
		-stdlib=libc++ -unwindlib=libunwind -rtlib=compiler-rt -lc++abi>
	PUBLIC
		-Wall -Wextra -Wpedantic )

add_compile_options(
	PRIVATE
	$<$<CXX_COMPILER_ID:Clang>:
		-stdlib=libc++ -unwindlib=libunwind -rtlib=compiler-rt -lc++abi>
	PUBLIC
		-Wall -Wextra -Wpedantic )
