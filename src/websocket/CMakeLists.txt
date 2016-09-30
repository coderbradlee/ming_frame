set(webSocket_SRCS
  webSocketServer.cc
  webSocketResponse.cc
  webSocketContext.cc
  base64.cc
  )

add_library(webSocket ${webSocket_SRCS})
#target_link_libraries(webSocket muduo_net)
target_link_libraries(webSocket muduo_net_cpp11 muduo_base_cpp11 muduo_http boost_system ssl mysqlcppconn boost_program_options boost_filesystem boost_coroutine boost_thread pthread boost_context boost_date_time crypto boost_regex boost_timer boost_signals boost_locale libgo libgo_main muduo_inspect gd)
install(TARGETS webSocket DESTINATION lib)
set(HEADERS
  webSocketRequest.h
  webSocketResponse.h
  webSocketServer.h
  )
#install(FILES ${HEADERS} DESTINATION include/muduo/net/http)

#if(NOT CMAKE_BUILD_NO_EXAMPLES)
add_executable(webSockets tests/webSocketServer_test.cc)
target_link_libraries(webSockets webSocket)

#if(BOOSTTEST_LIBRARY)
#add_executable(httprequest_unittest tests/HttpRequest_unittest.cc)
#target_link_libraries(httprequest_unittest webSocket #boost_unit_test_framework)
#endif()

#endif()

# add_subdirectory(tests)
