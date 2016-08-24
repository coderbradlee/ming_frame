add_subdirectory(rpcbench)
add_subdirectory(codec)
add_subdirectory(rpc)
add_subdirectory(rpcbalancer)


#if(CARES_INCLUDE_DIR AND CARES_LIBRARY)
#  add_subdirectory(resolver)
#else()
#  add_subdirectory(resolver EXCLUDE_FROM_ALL)
#endif()
