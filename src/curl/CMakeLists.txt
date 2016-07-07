add_library(ming_curl Curl.cc)
target_link_libraries(ming_curl muduo_net)
target_link_libraries(ming_curl curl)

install(TARGETS ming_curl DESTINATION lib)
install(FILES Curl.h DESTINATION include/muduo/curl)

#add_executable(ming_mcurl mcurl.cc)
#target_link_libraries(ming_mcurl ming_curl)

add_executable(ming_curl_download download.cc)
target_link_libraries(ming_curl_download ming_curl)

add_executable(rest_request rest_request.cpp)
target_link_libraries(rest_request ming_curl)
