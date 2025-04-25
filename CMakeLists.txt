cmake_minimum_required(VERSION 3.31)
project(tc_itk_util)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
        $ENV{TC13.3_ROOT}/include
        $ENV{TC13.3_ROOT}/include_cpp
)

set(SOURCES
        src/dispatcher_util.cpp
        src/ics_util.cpp
        src/nr_util.cpp
        src/main.cpp
)

add_definitions(
        -DNT40
        -DPOMDLL
        -DCRTAPI1=_cdecl
        -DCRTAPI2=cdecl
        -D_WIN32
        -DWIN64
        -DWIN32_LEAN_AND_MEAN
        -DWNT
        -DBYPASS_FLEX
        -D_INTEL=1
        -DIPLIB=none
)

set(LIB_DIR "$ENV{TC13.3_ROOT}/lib")

file(GLOB LIB_FILES "${LIB_DIR}/*.lib")

link_directories(${LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_FILES})

if(MSVC)
    add_compile_options(/wd4819)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /MD)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd4099 /wd4199)

    set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:CONSOLE /MACHINE:X64"
    )

    target_link_options(${PROJECT_NAME} PRIVATE
            "/DELAYLOAD:libtcsso.dll"
            "/DELAYLOAD:libict.dll"
    )

    target_link_options(${PROJECT_NAME} PRIVATE $ENV{TC13.3_ROOT}/lib/itk_main.obj)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
endif()
