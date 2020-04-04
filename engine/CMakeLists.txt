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
		-Wno-unused-variable
	)
endif()

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

message(STATUS "Checking dependencies")
find_package(OpenGL 3 REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)

message(STATUS "Linking dependencies")
target_link_libraries(engine OpenGL::GL)
target_link_libraries(engine GLEW::GLEW)
target_link_libraries(engine glfw)

add_custom_target(
	copy-runtime-files ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_CURRENT_SOURCE_DIR}/resources
					${CMAKE_CURRENT_BINARY_DIR}/resources
)