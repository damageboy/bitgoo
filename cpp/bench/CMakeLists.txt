set(TARGET_NAME ${CMAKE_PROJECT_NAME}_bench)


find_package(Threads REQUIRED)

file(GLOB bench_sources *.cpp)
file(GLOB bench_headers *.h)
add_executable(bitgoo_bench ${bench_sources} ${bench_headers})

target_link_libraries(${TARGET_NAME}
        bitgoo_lib
        benchmark
        ${CMAKE_THREAD_LIBS_INIT})

add_test(${TARGET_NAME} bitgoo_bench)