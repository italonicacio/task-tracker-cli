cmake_minimum_required(VERSION 3.22)

project(TaskTracker CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_VERBOSE_MAKEFILE True)

file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIBRARY_SOURCES "src/main.cpp")

add_library (
    TaskTrackerCore
    STATIC
        ${LIBRARY_SOURCES}
)

target_include_directories(
    TaskTrackerCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)


# target_link_libraries(
#     MyLibrary
#     PUBLIC
#         <ADD_EXTERN_LIBRARIES>
# )

set_target_properties( 
    TaskTrackerCore
    PROPERTIES
        ENABLE_EXPORTS ON
        POSITION_INDEPENDENT_CODE ON
)

install (
    TARGETS TaskTrackerCore
    DESTINATION ${CMAKE_BINARY_DIR}/lib
)

add_executable(
    TaskTracker
        "src/main.cpp"
)



target_include_directories(
    TaskTracker
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include

)

target_link_libraries(
    TaskTracker
    PRIVATE
        TaskTrackerCore
)

if (CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR enable_tests)
	enable_testing()
	add_subdirectory(tests/unit-tests)
endif()

