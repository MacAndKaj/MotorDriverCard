set(LIBS_INSTALL_PATH ${CMAKE_BINARY_DIR}/libs)
set(LIBS_SOURCE_PATH ${CMAKE_SOURCE_DIR}/libs)

include(ExternalProject)

ExternalProject_Add(Unity
	GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LIBS_INSTALL_PATH}
)


include_directories(${LIBS_INSTALL_PATH}/include/unity)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(platform)
add_subdirectory(msg)

link_directories(${LIBS_PATH}/lib)
