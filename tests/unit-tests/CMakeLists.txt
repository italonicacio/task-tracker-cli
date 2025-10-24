set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilita o modo quiet to FetchContent" FORCE)

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        v1.15.0
)

FetchContent_MakeAvailable(googletest)

set(TEST_DATA_DIR "${CMAKE_BINARY_DIR}/test_data")

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/Environment.hpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/Environment.hpp"
	@ONLY
)

file(MAKE_DIRECTORY ${TEST_DATA_DIR})

include(GoogleTest)

add_executable(
    TaskTrackerTests
    RunTests.cpp
    TaskOperationsTest.cpp
	TaskRepositoryFileSystemTest.cpp
)

target_link_libraries(TaskTrackerTests PRIVATE TaskTrackerCore GTest::gtest )

target_include_directories(
    TaskTrackerTests
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include 
		${CMAKE_CURRENT_BINARY_DIR}
)


gtest_discover_tests(TaskTrackerTests)

