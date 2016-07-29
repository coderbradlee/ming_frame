include_directories("include")
include_directories("details")
include_directories("httpserver")
include_directories("httpserver/details")
set(net_SRCS string_utilities.cpp webserver.cpp http_utils.cpp http_request.cpp http_response.cpp http_resource.cpp details/comet_manager.cpp details/http_endpoint.cpp)

add_library(microhttpserver ${net_SRCS})
target_link_libraries(microhttpserver microhttpd)
set_target_properties(microhttpserver PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS microhttpserver DESTINATION lib)

set(HEADERS
  autoinit_funcs.h
  microhttpd.h
  platform.h
  platform_interface.h
  w32functions.h
  httpserver.hpp
  )
install(FILES ${HEADERS} DESTINATION include/microhttpserver)


