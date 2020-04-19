set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
file(
	GLOB_RECURSE SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Add header files
file(
	GLOB_RECURSE HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_executable(engine ${HEADER_FILES} ${SOURCE_FILES})

if (MSVC)
	# warning level 3 and all warnings as errors
	target_compile_options(engine PUBLIC /W3 /WX /EHsc)
else()
	# lots of warnings and all warnings as errors
	target_compile_options(
		engine PUBLIC
		-g
		-Wall
		-Werror
		-Wextra
		-Wpedantic
		-Wshadow
		-Wnon-virtual-dtor
		-Wcast-align
		-Wunused
		-Wconversion
		-Wold-style-cast
	)
endif()

message(STATUS "Checking dependencies")
find_package(OpenGL 3 REQUIRED COMPONENTS OpenGL)

message(STATUS "Linking dependencies")
target_link_libraries(engine OpenGL::GL libglew_static glfw assimp)
