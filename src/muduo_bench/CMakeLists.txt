#add_executable(server pingpong_server.cc)
#target_link_libraries(server muduo_net_cpp11)
#target_link_libraries(server muduo_base_cpp11)


#add_executable(client pingpong_client.cc)
#target_link_libraries(client muduo_net_cpp11)
#target_link_libraries(client muduo_base_cpp11)

#add_executable(pingpong_bench pingpong_bench.cc)
#target_link_libraries(pingpong_bench muduo_net_cpp11)
#target_link_libraries(pingpong_bench muduo_base_cpp11)

#add_executable(test_server test_server.cpp)
#target_link_libraries(test_server muduo_net_cpp11)
#target_link_libraries(test_server muduo_base_cpp11)

#add_executable(file_transfer file_transfer.cpp)
#target_link_libraries(file_transfer muduo_net_cpp11)
#target_link_libraries(file_transfer muduo_base_cpp11)

add_executable(hub hub.cpp)
target_link_libraries(hub muduo_net_cpp11)
target_link_libraries(hub muduo_base_cpp11)

add_library(muduo_pubsub pubsubclient.cpp)
target_link_libraries(muduo_pubsub muduo_net)

add_executable(pub pub.cpp)
target_link_libraries(pub muduo_pubsub)

add_executable(sub sub.cpp)
target_link_libraries(sub muduo_pubsub)