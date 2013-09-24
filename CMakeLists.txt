cmake_minimum_required (VERSION 2.6)
project (Eigenlicht)

set (CMAKE_BUILD_TYPE "Debug")

set (IRRLICHT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../ThirdParty/irrlicht-1.8/include/")
set (EIGENLICHT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/")
set (EIGENLICHT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/source/")
set (CMAKE_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/lib/")

include_directories (
  ${IRRLICHT_INCLUDE_DIR}
  ${EIGENLICHT_INCLUDE_DIR}
)

add_library (
  Eigenlicht
  STATIC
  ${EIGENLICHT_SOURCE_DIR}/Manager.cpp
  ${EIGENLICHT_SOURCE_DIR}/Event.cpp
  ${EIGENLICHT_SOURCE_DIR}/EventDispatcher.cpp
  ${EIGENLICHT_SOURCE_DIR}/ComponentContainer.cpp
  ${EIGENLICHT_SOURCE_DIR}/Plane.cpp
)

install (
  TARGETS Eigenlicht
  DESTINATION ${CMAKE_LIBRARY_DIR}
)
