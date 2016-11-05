# Install script for directory: /root/ming_frame/src/test

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/root/ming_frame/build/release/release-testinstall")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/root/ming_frame/build/release/src/test/muduo_bench/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/tpc/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/socks4a/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/ttcp/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/websocket/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/chat/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/multiplexer/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/shorturl/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/udns/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/curl/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/muduo_net/cmake_install.cmake")
  INCLUDE("/root/ming_frame/build/release/src/test/nbody/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

