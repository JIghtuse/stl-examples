project(stl_examples)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wpedantic -Werror")
if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
endif()

find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

add_executable(all_of src/all_of.cxx)
add_executable(any_of src/any_of.cxx)
target_link_libraries(any_of
	${Boost_SYSTEM_LIBRARIES}
	${Boost_FILESYSTEM_LIBRARIES}
)

add_executable(none_of src/none_of.cxx)
