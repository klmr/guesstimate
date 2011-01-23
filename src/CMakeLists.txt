cmake_minimum_required (VERSION 2.6) 

project (guesstimate)

find_package (Threads)

add_executable (guesstimate main.cpp measure_pthreads.cpp wall_clock.cpp)
target_link_libraries (guesstimate ${CMAKE_THREAD_LIBS_INIT})

# Link against librt on Linux for time measurement.
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  target_link_libraries (guesstimate rt)
endif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
