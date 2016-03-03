project(stl_examples)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wpedantic -Werror")
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.5.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnull-dereference")
    endif()
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-prototypes")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic")
endif()

include_directories(include/)
find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

add_executable(all_of src/all_of.cxx)
add_executable(any_of src/any_of.cxx)
target_link_libraries(any_of
    ${Boost_SYSTEM_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARIES}
)
add_executable(none_of src/none_of.cxx)
add_executable(for_each src/for_each.cxx)
add_executable(count src/count.cxx)
add_executable(mismatch src/mismatch.cxx src/color.h)
add_executable(equal src/equal.cxx)
add_executable(find src/find.cxx src/color.h)
target_link_libraries(find pthread)
add_executable(find_if_not src/find_if_not.cxx)
add_executable(find_end src/find_end.cxx)
add_executable(find_first_of src/find_first_of.cxx)
add_executable(adjacent_find src/adjacent_find.cxx)
add_executable(search src/search.cxx)
add_executable(search_n src/search_n.cxx)
add_executable(copy include/print_container.h src/copy.cxx)
add_executable(copy_n include/print_container.h src/copy_n.cxx)
add_executable(copy_backward src/copy_backward.cxx)
add_executable(move src/move.cxx)
add_executable(fill src/fill.cxx)
add_executable(fill_n include/print_container.h src/fill_n.cxx)
add_executable(transform include/print_container.h src/transform.cxx)
add_executable(generate src/generate.cxx)
add_executable(generate_n include/generate_n.h src/generate_n.cxx src/generate_n_main.cxx)
add_executable(remove src/remove.cxx)

# Testing - it should be under some 'ifdef'
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(all_tests
    tests/tests_main.cxx
    include/generate_n.h
    src/generate_n.cxx
    tests/test_generate_n.cxx
)
target_link_libraries(all_tests ${GTEST_BOTH_LIBRARIES})

GTEST_ADD_TESTS(all_tests "" AUTO)
