cmake_minimum_required (VERSION 2.6) 

project (guesstimate)

find_package (Threads)
find_package (OpenMP)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

add_executable (guesstimate main.cpp measure_pthreads.cpp measure_omp.cpp wall_clock.cpp)
target_link_libraries (guesstimate ${CMAKE_THREAD_LIBS_INIT})

# Link against librt on Linux for time measurement.
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  target_link_libraries (guesstimate rt)
endif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
