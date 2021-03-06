add_subdirectory(glew-cmake-2.1.0 EXCLUDE_FROM_ALL)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")
set(GLFW_DOCUMENT_INTERNALS OFF CACHE BOOL "Include internals in documentation")
add_subdirectory(glfw-3.0 EXCLUDE_FROM_ALL)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build package with shared libraries.")
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "If the supplementary tools for Assimp are built in addition to the library.")
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp's export functionality.")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "If the test suite for Assimp is built in addition to the library.")
add_subdirectory(assimp-5.0.1 EXCLUDE_FROM_ALL)

if (MSVC)
	target_compile_options(assimp PUBLIC /W0)
else()
	target_compile_options(assimp PUBLIC -w)
endif()
