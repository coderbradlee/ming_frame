set(webSocket_SRCS
  webSocketServer.cc
  webSocketResponse.cc
  webSocketContext.cc
  )

add_library(webSocket ${webSocket_SRCS})
#target_link_libraries(webSocket muduo_net)
target_link_libraries(webSocket muduo_net_cpp11)
install(TARGETS webSocket DESTINATION lib)
set(HEADERS
  webSocketRequest.h
  webSocketResponse.h
  webSocketServer.h
  )
#install(FILES ${HEADERS} DESTINATION include/muduo/net/http)

#if(NOT CMAKE_BUILD_NO_EXAMPLES)
#add_executable(httpserver_test tests/HttpServer_test.cc)
#target_link_libraries(httpserver_test webSocket)

#if(BOOSTTEST_LIBRARY)
#add_executable(httprequest_unittest tests/HttpRequest_unittest.cc)
#target_link_libraries(httprequest_unittest webSocket #boost_unit_test_framework)
#endif()

#endif()

# add_subdirectory(tests)
