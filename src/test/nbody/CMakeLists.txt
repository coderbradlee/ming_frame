
set(LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)
add_executable(nbodyc nbody.c)
target_link_libraries(nbodyc ${LIB_LIST})

add_executable(nbodycc nbody.cc)
target_link_libraries(nbodycc ${LIB_LIST})
