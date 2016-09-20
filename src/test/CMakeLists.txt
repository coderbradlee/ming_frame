#add_definitions(-Wno-error=unused-variable)

#set(CMAKE_CXX_FLAGS "-Wno-unused-variable ${CMAKE_CXX_FLAGS}")
add_subdirectory(muduo_bench)
add_subdirectory(tpc)
add_subdirectory(socks4a)

set(TEST_MAIN_SRC_LIST ../config.cpp ../log.cpp test2.cpp test_main.cpp)
set(TEST_MAIN_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

add_executable(test_main ${TEST_MAIN_SRC_LIST})

target_link_libraries(test_main ${TEST_MAIN_LIB_LIST})

set_target_properties (test_main PROPERTIES COMPILE_FLAGS "-DCHECK_PTHREAD_RETURN_VALUE -D_FILE_OFFSET_BITS=64 -Wall
 -Wextra -Wno-unused-parameter -Woverloaded-virtual -Wpointer-arith -Wshadow -Wwrite-strings -march=native
 -std=c++11 -rdynamic -O2 -finline-limit=1000 -DNDEBUG")