cmake_minimum_required(VERSION 3.31)
project(tc_itk_util)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
        include
        $ENV{TC2412_ROOT}/include
        $ENV{TC2412_ROOT}/include_cpp
)

function(configure_target_common target_name)
    target_compile_definitions(${target_name} PRIVATE
            NT40
            POMDLL
            CRTAPI1=_cdecl
            CRTAPI2=cdecl
            _WIN32
            WIN64
            WIN32_LEAN_AND_MEAN
            WNT
            BYPASS_FLEX
            _INTEL=1
            IPLIB=none
    )

    if (MSVC)
        target_compile_options(${target_name} PRIVATE /W3 /MD /wd4099 /wd4199 /wd4819 /wd4267)

        set_target_properties(${target_name} PROPERTIES
                LINK_FLAGS "/SUBSYSTEM:CONSOLE /MACHINE:X64"
        )

        target_link_options(${target_name} PRIVATE
                "/DELAYLOAD:libtcsso.dll"
                "/DELAYLOAD:libict.dll"
        )

        target_link_options(${target_name} PRIVATE $ENV{TC2412_ROOT}/lib/itk_main.obj)
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target_name} PRIVATE DEBUG)
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${target_name} PRIVATE NDEBUG)
    endif ()

    target_link_directories(${target_name} PRIVATE "$ENV{TC2412_ROOT}/lib")

    file(GLOB LIB_FILES "$ENV{TC2412_ROOT}/lib/*.lib")
    target_link_libraries(${target_name} PRIVATE ${LIB_FILES} gtest)
endfunction()

include(GoogleTest)

add_executable(tc_itk_util tests/test.cpp
        tests/item_util_test.cpp src/item_util.cpp
        tests/session_util_test.cpp src/session_util.cpp
        tests/qry_util_test.cpp src/qry_util.cpp)
configure_target_common(tc_itk_util)

add_executable(item_util_test tests/test.cpp
        tests/item_util_test.cpp src/item_util.cpp)
configure_target_common(item_util_test)

add_executable(session_util_test tests/test.cpp
        tests/session_util_test.cpp src/session_util.cpp)
configure_target_common(session_util_test)
