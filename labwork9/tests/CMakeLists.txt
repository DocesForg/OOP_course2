include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        adapter_tests
        test_adapters.cpp
)

target_link_libraries(
        adapter_tests
        adapters
        GTest::gtest_main
)

target_include_directories(adapter_tests PUBLIC ${PROJECT_SOURCE_DIR})
add_test(NAME adapter_tests COMMAND adapter_tests)

include(GoogleTest)

gtest_discover_tests(adapter_tests)