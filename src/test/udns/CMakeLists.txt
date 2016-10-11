target_include_directories(udns-0.2)
set(SRC_LIST udns_dn.c udns_dntosp.c udns_parse.c udns_resolver.c udns_init.c udns_misc.c udns_XtoX.c udns_rr_a.c udns_rr_ptr.c udns_rr_mx.c udns_rr_txt.c udns_bl.c udns_rr_srv.c udns_rr_naptr.c udns_codes.c udns_jran.c dns.cc Resolver.cc)
set(LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

add_executable(udns ${SRC_LIST})

target_link_libraries(udns ${LIB_LIST})
