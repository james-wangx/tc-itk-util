cmake_minimum_required(VERSION 4.0.2)
project(tc_itk_util LANGUAGES CXX)

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

find_package(CURL REQUIRED)

include_directories(
        include
        $ENV{TC2412_ROOT}/include
        $ENV{TC2412_ROOT}/include_cpp
)

file(GLOB SOURCES src/*.cxx)

function(configure_library target_name)
    target_compile_definitions(${target_name} PRIVATE
            IPLIB=none
    )

    if (MSVC)
        target_compile_options(${target_name} PRIVATE /W3 /MD /wd4819 /wd4251)
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(${target_name} PRIVATE DEBUG)
    endif ()

    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_definitions(${target_name} PRIVATE NDEBUG)
    endif ()

    target_link_directories(${target_name} PRIVATE "$ENV{TC2412_ROOT}/lib")

    file(GLOB LIB_FILES "$ENV{TC2412_ROOT}/lib/*.lib")
    target_link_libraries(${target_name} PRIVATE ${LIB_FILES} CURL::libcurl)
endfunction()

function(configure_executable target_name)
    target_compile_definitions(${target_name} PRIVATE
            IPLIB=none
    )

    if (MSVC)
        target_compile_options(${target_name} PRIVATE /W3 /MD /wd4819)
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
    target_link_libraries(${target_name} PRIVATE ${LIB_FILES} gtest libtcitkutil CURL::libcurl)
endfunction()

add_library(libtcitkutil STATIC ${SOURCES})
configure_library(libtcitkutil)

include(GoogleTest)
