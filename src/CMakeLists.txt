add_executable(ming_log log.cpp)
target_link_libraries(ming_log muduo_base)

if(CURL_FOUND)
  add_subdirectory(curl)
else()
  add_subdirectory(curl EXCLUDE_FROM_ALL)
endif()
