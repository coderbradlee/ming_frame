# Install script for directory: /root/ming_frame/muduo/base

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/root/ming_frame/build/release/lib/libmuduo_base_cpp11.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/root/ming_frame/muduo/base/AsyncLogging.h"
    "/root/ming_frame/muduo/base/Atomic.h"
    "/root/ming_frame/muduo/base/BlockingQueue.h"
    "/root/ming_frame/muduo/base/BoundedBlockingQueue.h"
    "/root/ming_frame/muduo/base/Condition.h"
    "/root/ming_frame/muduo/base/CountDownLatch.h"
    "/root/ming_frame/muduo/base/CurrentThread.h"
    "/root/ming_frame/muduo/base/Date.h"
    "/root/ming_frame/muduo/base/Exception.h"
    "/root/ming_frame/muduo/base/FileUtil.h"
    "/root/ming_frame/muduo/base/GzipFile.h"
    "/root/ming_frame/muduo/base/LogFile.h"
    "/root/ming_frame/muduo/base/LogStream.h"
    "/root/ming_frame/muduo/base/Logging.h"
    "/root/ming_frame/muduo/base/Mutex.h"
    "/root/ming_frame/muduo/base/ProcessInfo.h"
    "/root/ming_frame/muduo/base/Singleton.h"
    "/root/ming_frame/muduo/base/StringPiece.h"
    "/root/ming_frame/muduo/base/Thread.h"
    "/root/ming_frame/muduo/base/ThreadLocal.h"
    "/root/ming_frame/muduo/base/ThreadLocalSingleton.h"
    "/root/ming_frame/muduo/base/ThreadPool.h"
    "/root/ming_frame/muduo/base/TimeZone.h"
    "/root/ming_frame/muduo/base/Timestamp.h"
    "/root/ming_frame/muduo/base/Types.h"
    "/root/ming_frame/muduo/base/WeakCallback.h"
    "/root/ming_frame/muduo/base/copyable.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/root/ming_frame/build/release/muduo/base/tests/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

