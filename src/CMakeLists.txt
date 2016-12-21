
set(PRODUCT_SRC_LIST config.cpp log.cpp procmon.cpp plot.cpp fastcgi/fastcgi.cpp fastcgi/fastcgi_resource.cpp mysql_connect.cpp server_prod.cpp)
add_executable(ming ${PRODUCT_SRC_LIST})

set(MAIN_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)
target_link_libraries(ming ${MAIN_LIB_LIST})

set_target_properties(ming PROPERTIES COMPILE_FLAGS "-std=c++14")
add_definitions(-DMING_DEBUG)
if(TCMALLOC_INCLUDE_DIR AND TCMALLOC_LIBRARY)
  set_target_properties(ming PROPERTIES COMPILE_FLAGS "-DHAVE_TCMALLOC")
  target_link_libraries(ming tcmalloc_and_profiler)
endif()