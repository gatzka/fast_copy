cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(GatzkaToolchainFiles
    GIT_REPOSITORY https://github.com/gatzka/cmake-toolchain-files.git
    SOURCE_DIR ${CMAKE_BINARY_DIR}/toolchains
)
FetchContent_GetProperties(GatzkaToolchainFiles)
if(NOT GatzkaToolchainFiles_POPULATED)
    FetchContent_Populate(GatzkaToolchainFiles)
endif()

project(fast_copy VERSION 0.0.1 LANGUAGES C)

if(CMAKE_CONFIGURATION_TYPES)
    if(NOT "MemorySanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES MemorySanitizer)
    endif()
    if(NOT "AddressSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES AddressSanitizer)
    endif()
    if(NOT "LeakSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES LeakSanitizer)
    endif()
    if(NOT "UndefinedBehaviorSanitizer" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES UndefinedBehaviorSanitizer)
    endif()
    if(NOT "Coverage" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Coverage)
    endif()
    if(NOT "Profile" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Profile)
    endif()
else()
    set(allowableBuildTypes Debug Release RelWithDebInfo MemorySanitizer AddressSanitizer LeakSanitizer UndefinedBehaviorSanitizer Coverage Profile)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
    STRINGS "${allowableBuildTypes}")
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
    elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
        message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_C_FLAGS_ADDRESSSANITIZER "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${ASAN_FLAGS}" CACHE STRING "Flags used by the C compiler during address sanitizer builds." FORCE)
set(CMAKE_CXX_FLAGS_ADDRESSSANITIZER "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${ASAN_FLAGS}" CACHE STRING "Flags used by the C++ compiler during address sanitizer builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_ADDRESSSANITIZER "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${ASAN_FLAGS}" CACHE STRING "Flags used for linking executables during address sanitizer builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_ADDRESSSANITIZER "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${ASAN_FLAGS}" CACHE STRING "Flags used for shared library linking during address sanitizer builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_ADDRESSSANITIZER "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Flags used for static library linking during address sanitizer builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_ADDRESSSANITIZER "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} ${ASAN_FLAGS}" CACHE STRING "Flags used module linking during address sanitizer builds." FORCE)

set(CMAKE_C_FLAGS_MEMORYSANITIZER "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${MSAN_FLAGS}" CACHE STRING "Flags used by the C compiler during memory sanitizer builds." FORCE)
set(CMAKE_CXX_FLAGS_MEMORYSANITIZER "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${MSAN_FLAGS}" CACHE STRING "Flags used by the C++ compiler during memory sanitizer builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_MEMORYSANITIZER "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${MSAN_FLAGS}" CACHE STRING "Flags used for linking executables during memory sanitizer builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_MEMORYSANITIZER "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${MSAN_FLAGS}" CACHE STRING "Flags used for shared library linking during memory sanitizer builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_MEMORYSANITIZER "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Flags used for static library linking during memory sanitizer builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_MEMORYSANITIZER "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} ${MSAN_FLAGS}" CACHE STRING "Flags used module linking during memory sanitizer builds." FORCE)

set(CMAKE_C_FLAGS_LEAKSANITIZER "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${LSAN_FLAGS}" CACHE STRING "Flags used by the C compiler during leak sanitizer builds." FORCE)
set(CMAKE_CXX_FLAGS_LEAKSANITIZER "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${LSAN_FLAGS}" CACHE STRING "Flags used by the C++ compiler during leak sanitizer builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_LEAKSANITIZER "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${LSAN_FLAGS}" CACHE STRING "Flags used for linking executables during leak sanitizer builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_LEAKSANITIZER "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${LSAN_FLAGS}" CACHE STRING "Flags used for shared library linking during leak sanitizer builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_LEAKSANITIZER "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Flags used for static library linking during leak sanitizer builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_LEAKSANITIZER "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} ${LSAN_FLAGS}" CACHE STRING "Flags used module linking during leak sanitizer builds." FORCE)

set(CMAKE_C_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${UBSAN_FLAGS}" CACHE STRING "Flags used by the C compiler during undefined behavior sanitizer builds." FORCE)
set(CMAKE_CXX_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${UBSAN_FLAGS}" CACHE STRING "Flags used by the C++ compiler during undefined behavior sanitizer builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${UBSAN_FLAGS}" CACHE STRING "Flags used for linking executables during undefined behavior sanitizer builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${UBSAN_FLAGS}" CACHE STRING "Flags used for shared library linking during undefined behavior sanitizer builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Flags used for static library linking during undefined behavior sanitizer builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_UNDEFINEDBEHAVIORSANITIZER "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} ${UBSAN_FLAGS}" CACHE STRING "Flags used module linking during undefined behavior sanitizer builds." FORCE)

set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} ${COVERAGE_FLAGS}" CACHE STRING "Flags used by the C compiler during coverage builds." FORCE)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} ${COVERAGE_FLAGS}" CACHE STRING "Flags used by the C++ compiler during coverage builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${COVERAGE_FLAGS}" CACHE STRING "Flags used for linking executables during coverage builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} ${COVERAGE_FLAGS}" CACHE STRING "Flags used for shared library linking during coverage builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_COVERAGE "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}" CACHE STRING "Flags used for static library linking during coverage builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_COVERAGE "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} ${COVERAGE_FLAGS}" CACHE STRING "Flags used module linking during coverage builds." FORCE)

set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELWITHDEBINFO} ${PROFILE_FLAGS}" CACHE STRING "Flags used by the C compiler during profiling builds." FORCE)
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${PROFILE_FLAGS}" CACHE STRING "Flags used by the C++ compiler during profiling builds." FORCE)
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} ${PROFILE_FLAGS}" CACHE STRING "Flags used for linking executables during profiling builds." FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${PROFILE_FLAGS}" CACHE STRING "Flags used for shared library linking during profiling builds." FORCE)
set(CMAKE_STATIC_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO}" CACHE STRING "Flags used for static library linking during profiling builds." FORCE)
set(CMAKE_MODULE_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} ${PROFILE_FLAGS}" CACHE STRING "Flags used module linking during profiling builds." FORCE)

include(CTest)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT output)
if(ipo_supported)
    option(FAST_COPY_ENABLE_LTO "Build everithing with link time optization" OFF)
endif()


add_library(${PROJECT_NAME}
    fast_copy.c
    fast_copy.h
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if(NOT CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
        SOVERSION ${PROJECT_VERSION_MAJOR}
        C_STANDARD 99
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
        C_VISIBILITY_PRESET hidden
    )
endif()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY PUBLIC_HEADER
    fast_copy.h
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}/export.h)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated/>
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}/export.h"
    DESTINATION include/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Config.cmake
)

add_subdirectory(tests)
