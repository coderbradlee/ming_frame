set(QUOTATION_SRC_LIST ../config.cpp ../log.cpp italy_quotation_report.cpp italy_quotation_report_main.cpp)
set(QUOTATION_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

add_executable(italy_quotation_report ${QUOTATION_SRC_LIST})

target_link_libraries(italy_quotation_report ${QUOTATION_LIB_LIST})

if(TCMALLOC_INCLUDE_DIR AND TCMALLOC_LIBRARY)
  set_target_properties(italy_quotation_report PROPERTIES COMPILE_FLAGS "-DHAVE_TCMALLOC")
  target_link_libraries(italy_quotation_report tcmalloc_and_profiler)
endif()

set(LEAD_SRC_LIST ../config.cpp ../log.cpp italy_lead_report.cpp italy_lead_report_main.cpp)
set(LEAD_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale muduo_inspect gd)

add_executable(italy_lead_report ${LEAD_SRC_LIST})

target_link_libraries(italy_lead_report ${LEAD_LIB_LIST})

if(TCMALLOC_INCLUDE_DIR AND TCMALLOC_LIBRARY)
  set_target_properties(italy_lead_report PROPERTIES COMPILE_FLAGS "-DHAVE_TCMALLOC")
  target_link_libraries(italy_lead_report tcmalloc_and_profiler)
endif()




set(PRODUCT_SRC_LIST ../config.cpp ../log.cpp italy_account_report.cpp italy_account_report_main.cpp)
add_executable(italy_account_report ${PRODUCT_SRC_LIST})

set(main_name italy_account_report)

target_link_libraries(${main_name} muduo_net_cpp11)
target_link_libraries(${main_name} muduo_base_cpp11)
target_link_libraries(${main_name} muduo_http)
target_link_libraries(${main_name}  boost_system )
target_link_libraries(${main_name} ssl)
target_link_libraries(${main_name} mysqlcppconn)
target_link_libraries(${main_name} boost_program_options) 
target_link_libraries(${main_name} boost_filesystem) 
target_link_libraries(${main_name} boost_coroutine) 
target_link_libraries(${main_name} boost_thread) 
target_link_libraries(${main_name} pthread) 
target_link_libraries(${main_name} boost_context) 
target_link_libraries(${main_name} boost_date_time) 
target_link_libraries(${main_name} crypto) 
target_link_libraries(${main_name} boost_regex) 
target_link_libraries(${main_name} boost_timer) 
target_link_libraries(${main_name} boost_signals) 
target_link_libraries(${main_name} boost_locale)

target_link_libraries(${main_name} muduo_inspect)
target_link_libraries(${main_name} gd)
set_target_properties(${main_name} PROPERTIES COMPILE_FLAGS "-std=c++14")
add_definitions(-DMING_DEBUG)
if(TCMALLOC_INCLUDE_DIR AND TCMALLOC_LIBRARY)
  set_target_properties(${main_name} PROPERTIES COMPILE_FLAGS "-DHAVE_TCMALLOC")
  target_link_libraries(${main_name} tcmalloc_and_profiler)
endif()