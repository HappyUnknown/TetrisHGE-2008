# Install script for directory: E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/HGE")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/zlib-1.2.5/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/libPNG/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/helpers/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/core/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/fontconv/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/fonted/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/particleed/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/pngopt/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/src/texasm/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial01/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial02/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial03/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial04/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial05/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial06/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial07/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial08/cmake_install.cmake")
  include("E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/tutorials/tutorial05_shaders/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/FILES/WORK/IOneGames/Tetris/Ye-e-e oldschool/hge-porting/_build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
