set(SRC_LIST test_loop.cpp)
set(LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

#add_executable(test_loop ${SRC_LIST})
#target_link_libraries(test_loop ${LIB_LIST})

#add_executable(test_timer test_timer.cpp)
#target_link_libraries(test_timer ${LIB_LIST})

#add_executable(test_multiport test_multiport.cpp)
#target_link_libraries(test_multiport ${LIB_LIST})

#add_executable(test_connect test_connect.cpp)
#target_link_libraries(test_connect ${LIB_LIST})

add_executable(trace_string trace_string.cpp)
target_link_libraries(trace_string ${LIB_LIST})