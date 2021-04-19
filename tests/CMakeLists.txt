cmake_minimum_required(VERSION 3.9)
project(fast_copy_unit_test C)
enable_testing()

add_library(fff INTERFACE)
target_include_directories(fff INTERFACE fff)

add_library(unity OBJECT
    unity/unity.c
)
set_target_properties(unity PROPERTIES
    COMPILE_OPTIONS "$<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:-Wno-strict-overflow>"
    C_CLANG_TIDY ""
)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_LIST_DIR}/unity/)

add_executable(test_fast_copy
    test_fast_copy.c
    ../fast_copy.c
)

get_property(includes TARGET fast_copy::fast_copy PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(targets DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt ${targets})
    get_target_property(target_type ${tgt} TYPE)
    if (target_type STREQUAL "EXECUTABLE")
        target_link_libraries(${tgt} fff unity)
        set_target_properties(${tgt} PROPERTIES
            C_STANDARD 11
            C_STANDARD_REQUIRED ON
            C_EXTENSIONS OFF
            C_CLANG_TIDY ""
        )
        target_include_directories(${tgt} PUBLIC ${includes})
        add_test(NAME common.${tgt} COMMAND ${tgt})
    endif()

    if(FAST_COPY_ENABLE_LTO AND NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
        set_property(TARGET ${tgt} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endforeach()

