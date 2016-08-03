
set(SRC_LIST Acceptor.cc InetAddress.cc TcpStream.cc Socket.cc)

add_executable(echo ${SRC_LIST} echo.cc)
add_executable(echo_client ${SRC_LIST} echo_client.cc)
