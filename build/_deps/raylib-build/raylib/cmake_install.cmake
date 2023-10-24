<<<<<<< Updated upstream
# Install script for directory: D:/ComOrg/MeowXMonster/build/_deps/raylib-src/src
=======
# Install script for directory: /home/pi/Desktop/MeowXMonster/build/_deps/raylib-src/src
>>>>>>> Stashed changes

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/MeowXMonster")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/TDM-GCC-64/bin/objdump.exe")
endif()

<<<<<<< Updated upstream
if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/ComOrg/MeowXMonster/build/_deps/raylib-build/raylib/libraylib.a")
=======
if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/arm-linux-gnueabihf" TYPE STATIC_LIBRARY FILES "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-build/raylib/libraylib.a")
>>>>>>> Stashed changes
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
<<<<<<< Updated upstream
    "D:/ComOrg/MeowXMonster/build/_deps/raylib-src/src/raylib.h"
    "D:/ComOrg/MeowXMonster/build/_deps/raylib-src/src/rlgl.h"
    "D:/ComOrg/MeowXMonster/build/_deps/raylib-src/src/raymath.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/ComOrg/MeowXMonster/build/_deps/raylib-build/raylib/raylib.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/raylib" TYPE FILE FILES "D:/ComOrg/MeowXMonster/build/_deps/raylib-build/raylib/raylib-config-version.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/raylib" TYPE FILE FILES "D:/ComOrg/MeowXMonster/build/_deps/raylib-src/src/../cmake/raylib-config.cmake")
=======
    "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src/src/raylib.h"
    "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src/src/rlgl.h"
    "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src/src/raymath.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/arm-linux-gnueabihf/pkgconfig" TYPE FILE FILES "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-build/raylib/raylib.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/arm-linux-gnueabihf/cmake/raylib" TYPE FILE FILES "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-build/raylib/raylib-config-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/arm-linux-gnueabihf/cmake/raylib" TYPE FILE FILES "/home/pi/Desktop/MeowXMonster/build/_deps/raylib-src/src/../cmake/raylib-config.cmake")
>>>>>>> Stashed changes
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< Updated upstream
  include("D:/ComOrg/MeowXMonster/build/_deps/raylib-build/raylib/external/glfw/cmake_install.cmake")
=======
  include("/home/pi/Desktop/MeowXMonster/build/_deps/raylib-build/raylib/external/glfw/cmake_install.cmake")
>>>>>>> Stashed changes

endif()

