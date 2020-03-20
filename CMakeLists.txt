cmake_minimum_required(VERSION 3.8.2)

project(apparator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
	# warning level 4 and all warnings as errors
	add_compile_options(/W4 /WX)
else()
	# lots of warnings and all warnings as errors
	add_compile_options(
		-Wall
		-Werror
		-Wextra
		-Wpedantic
		-Wshadow
		-Wnon-virtual-dtor
		-Wcast-align
		-Wunused
	)
endif()

include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(apparator ${HEADER_FILES} ${SOURCE_FILES})

message(STATUS "Checking dependencies")
find_package(OpenGL 3 REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if(HAS_FS)
	message(STATUS "Compiler has std::filesystem capabilities")
else()
	message(FATAL_ERROR "Compiler is missing std::filesystem capabilities")
endif(HAS_FS)

message(STATUS "Linking dependencies")
target_link_libraries(apparator OpenGL::GL)
target_link_libraries(apparator GLEW::GLEW)
target_link_libraries(apparator glfw)

# Copy assets to build dir
message(STATUS "Copying assets to build directory")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
