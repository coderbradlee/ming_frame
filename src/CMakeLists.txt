#add_executable(ming_log config.cpp)
#target_link_libraries(ming_log muduo_base)

#if(CURL_FOUND)
#  add_subdirectory(curl)
#else()
#  add_subdirectory(curl EXCLUDE_FROM_ALL)
#endif()
#add_library(ming_config config.cpp)
#target_link_libraries(ming_config muduo_net)

#add_subdirectory(fastcgi)
add_subdirectory(test)
#add_subdirectory(sudoku)
#add_subdirectory(memcached/client)
#add_subdirectory(memcached/server)
#add_subdirectory(month_report)
#add_subdirectory(us_report)
#add_subdirectory(jp_report)
#add_subdirectory(mexico_report)
#add_subdirectory(italy_report)
#add_subdirectory(thailand_report)
#add_subdirectory(special_sales_report)
if(PROTOBUF_FOUND)
  #add_subdirectory(ace/logging)
  add_subdirectory(protobuf)
else()
  #add_subdirectory(ace/logging EXCLUDE_FROM_ALL)
  add_subdirectory(protobuf EXCLUDE_FROM_ALL)
endif()

#set(SRC_LIST log.cpp fastcgi/fastcgi.cc fastcgi/fastcgi_resource.cc  config.cpp main.cpp)
#set(SRC_LIST config.cpp log.cpp sudoku/sudoku.cc mysql_connect.cpp fastcgi/fastcgi.cc fastcgi/fastcgi_resource.cc test/test.cpp test/test1.cpp shorturl.cpp main.cpp)


#set(SRC_LIST config.cpp log.cpp test/test2.cpp procmon.cpp plot.cpp inspector.cpp main.cpp)
#add_executable(ming ${SRC_LIST})

set(PRODUCT_SRC_LIST config.cpp log.cpp test/test2.cpp procmon.cpp plot.cpp sudoku/sudoku.cc server_prod.cpp)
add_executable(ming ${PRODUCT_SRC_LIST})

#file(WRITE ${PROJECT_SOURCE_DIR}/config.ini "${PROJECT_BIN_DIR}/bin")



#install(FILES ${PROJECT_SOURCE_DIR}/config.ini DESTINATION "/etc/ld.so.conf.d")
#install(TARGETS ${TARGET} LIBRARY DESTINATION "lib" ARCHIVE DESTINATION "lib")
#install(DIRECTORY libgonet/ DESTINATION "include/libgonet" FILES_MATCHING PATTERN "*.h")

set(MAIN_LIB_LIST muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale libgo libgo_main muduo_inspect gd)

target_link_libraries(ming ${MAIN_LIB_LIST})

set_target_properties(ming PROPERTIES COMPILE_FLAGS "-std=c++14")
add_definitions(-DMING_DEBUG)
if(TCMALLOC_INCLUDE_DIR AND TCMALLOC_LIBRARY)
  set_target_properties(ming PROPERTIES COMPILE_FLAGS "-DHAVE_TCMALLOC")
  target_link_libraries(ming tcmalloc_and_profiler)
endif()