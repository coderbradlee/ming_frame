include_directories(${PROJECT_SOURCE_DIR}/base)
set(SRC_LIST Acceptor.cc InetAddress.cc TcpStream.cc Socket.cc)

add_executable(echo ${SRC_LIST} echo.cc)
target_link_libraries(echo pthread)

add_executable(echo_client ${SRC_LIST} echo_client.cc)

add_executable(sudoku_stress ${SRC_LIST} sudoku_stress.cc Timestamp.cc)
target_link_libraries(sudoku_stress pthread)