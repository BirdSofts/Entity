# *******************************************************************************************
#/ <summary>
#/ 
#/ </summary>
#/ <created>ʆϒʅ,21.10.2019</created>
#/ <changed>ʆϒʅ,24.10.2019</changed>
# *******************************************************************************************

cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME libTale)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
  VERSION 0.1.0.0
  DESCRIPTION "Entity tale library"
  HOMEPAGE_URL "https://github.com/BirdSofts/Entity"
  LANGUAGES CXX
  )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND HEADER_FILES
  tale.h
  )

list(APPEND SOURCE_FILES
  tale.cpp
  )

if(WIN32)
  list(APPEND SOURCE_FILES ${HEADER_FILES})
endif(WIN32)

add_library(${TARGET_NAME} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
  PUBLIC Qt5::Core
  PUBLIC Qt5::Gui
  PUBLIC Qt5::Qml
  PUBLIC Qt5::Quick
  )
