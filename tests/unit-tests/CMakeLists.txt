set(FETCHCONTENT_QUIET OFF CACHE BOOL "Desabilita o modo quiet to FetchContent" FORCE)

include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        v1.15.0
)

FetchContent_MakeAvailable(googletest)



include(GoogleTest)

add_executable(
    TaskTrackerTests
    RunTests.cpp
    TaskOperationsTest.cpp
)

target_link_libraries(TaskTrackerTests PRIVATE TaskTrackerCore GTest::gtest )

target_include_directories(
    TaskTrackerTests
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/include 
)


gtest_discover_tests(TaskTrackerTests)

