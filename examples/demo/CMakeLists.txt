cmake_minimum_required (VERSION 2.6)
project (demo)

set (CMAKE_BUILD_TYPE "Debug")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  if (MSVC)
    set (IRRLICHT_SYSTEM_NAME "Win32-VisualStudio")
  else ()
    set (IRRLICHT_SYSTEM_NAME "Win32-gcc")
  endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set (IRRLICHT_SYSTEM_NAME "Linux")
endif ()

set (IRRLICHT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../../../ThirdParty/irrlicht-1.8/include/")
set (IRRLICHT_LIB_DIR "${CMAKE_SOURCE_DIR}/../../../ThirdParty/irrlicht-1.8/lib/${IRRLICHT_SYSTEM_NAME}/")
set (EIGENLICHT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../../include/")
set (EIGENLICHT_LIB_DIR "${CMAKE_SOURCE_DIR}/../../lib/")
set (CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/")

message ("Irrlicht lib path: ${IRRLICHT_LIB_DIR}")
message ("Eigenlicht lib path: ${EIGENLICHT_LIB_DIR}")

# Platform detection:
# http://www.openguru.com/2009/04/cmake-detecting-platformoperating.html
find_library (
  IRRLICHT_LIB
  NAMES Irrlicht
  HINTS ${IRRLICHT_LIB_DIR}
)

find_library (
  EIGENLICHT_LIB
  NAMES Eigenlicht
  HINTS ${EIGENLICHT_LIB_DIR}
)

include_directories (
  ${IRRLICHT_INCLUDE_DIR}
  ${EIGENLICHT_INCLUDE_DIR}
)

link_directories (
  ${IRRLICHT_LIB_DIR}
  ${EIGENLICHT_LIB_DIR}
)

add_executable (
  demo
  ${CMAKE_SOURCE_DIR}/source/main.cpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries (demo Irrlicht Winmm Eigenlicht)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  target_link_libraries (demo Irrlicht GL X11 Xxf86vm Eigenlicht)
endif ()

set_target_properties (
  demo
  PROPERTIES
  INSTALL_RPATH "./"
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  install (
    FILES
      "${CMAKE_SOURCE_DIR}/ThirdParty/irrlicht-1.8/bin/${IRRLICHT_SYSTEM_NAME}/Irrlicht.dll"
    DESTINATION ${CMAKE_BINARY_DIR}
  )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
endif ()

install (
  TARGETS demo
  DESTINATION ${CMAKE_BINARY_DIR}
)

