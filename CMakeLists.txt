cmake_minimum_required(VERSION 3.5.0)

project(SandPandaAnalytics VERSION 1.0.0)

set(SOURCES_FILES
        Sources/Model/cone.cpp
        Sources/Model/disk.cpp
        Sources/Model/elbow.cpp
        Sources/Model/plan.cpp
        Sources/Model/solid.cpp
        Sources/Model/sphere.cpp
        Sources/Model/velocity.cpp
        
        Sources/Repository/containerrepository.cpp
        Sources/Repository/sphererepository.cpp

        Sources/main.cpp
)

set(INCLUDES_FILES
        Includes/Model/cone.h
        Includes/Model/disk.h
        Includes/Model/elbow.h
        Includes/Model/plan.h
        Includes/Model/solid.h
        Includes/Model/sphere.h
        Includes/Model/velocity.h
        
        Includes/Repository/containerrepository.h
        Includes/Repository/sphererepository.h
)

set(SandPandaAnalytics_FILES
        ${INCLUDES_FILES}
        ${SOURCES_FILES}
)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(
        SandPandaAnalytics
        ${SandPandaAnalytics_FILES}
)

target_link_libraries(
        SandPandaAnalytics
        ${GTEST_LIBRARIES}
        ${OpenMP_}
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-O0 -g -pg -fno-omit-frame-pointer -DNOMP")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "-O3 -flto -march=native -DNOMP")
else (CMAKE_BUILD_TYPE STREQUAL "OpenMP")
    set(CMAKE_CXX_FLAGS "-O3 -flto -march=native")
endif ()

if (OPENMP_FOUND AND CMAKE_BUILD_TYPE STREQUAL "OpenMP")
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()


enable_testing()

#add_subdirectory("Tests")
