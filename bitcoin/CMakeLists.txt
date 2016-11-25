
set(PRODUCT_SRC_LIST addr.cpp)
add_executable(bitcoin_test ${PRODUCT_SRC_LIST})


#set(MAIN_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

set(MAIN_LIB_LIST bitcoin)

target_link_libraries(bitcoin_test ${MAIN_LIB_LIST})

