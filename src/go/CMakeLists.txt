set(LINK_ARGS libgo libgo_main boost_coroutine boost_context boost_system boost_thread pthread dl hiredis curl)

#add_executable(hredis sample12_hiredis.cpp)
#target_link_libraries(hredis ${LINK_ARGS})

#add_executable(myasio sample5_asio.cpp)
#target_link_libraries(myasio ${LINK_ARGS})

#add_executable(multithread sample8_multithread.cpp)
#target_link_libraries(multithread ${LINK_ARGS})

#add_executable(sample9_curl sample9_curl.cpp)
#target_link_libraries(sample9_curl ${LINK_ARGS})
