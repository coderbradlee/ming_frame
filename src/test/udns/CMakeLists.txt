
set(SRC_LIST udns-0.2/udns_dn.c udns-0.2/udns_dntosp.c udns-0.2/udns_parse.c udns-0.2/udns_XtoX.c udns-0.2/udns_resolver.c udns-0.2/udns_init.c udns-0.2/udns_misc.c  udns-0.2/udns_rr_a.c udns-0.2/udns_rr_ptr.c udns-0.2/udns_rr_mx.c udns-0.2/udns_rr_txt.c udns-0.2/udns_bl.c udns-0.2/udns_rr_srv.c udns-0.2/udns_rr_naptr.c udns-0.2/udns_codes.c udns-0.2/udns_jran.c dns.cc Resolver.cc)
set(LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

add_executable(udns ${SRC_LIST})

target_link_libraries(udns ${LIB_LIST})
