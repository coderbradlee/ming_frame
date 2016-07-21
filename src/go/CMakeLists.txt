set(LINK_ARGS libgo libgo_main boost_coroutine boost_context boost_system boost_thread pthread dl)

add_executable(hredis sample12_hiredis.cpp)
target_link_libraries(hredis ${LINK_ARGS})

