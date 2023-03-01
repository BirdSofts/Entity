
# *******************************************************************************************
#/ <summary>
#/ CMakeLists.txt
#/ Entity - libSettings
#/ created by Mehrdad Solimanimajd on 04.10.2019
#/ </summary>
#/ <created>ʆϒʅ, 04.10.2019</created>
#/ <changed>ʆϒʅ, 01.03.2023</changed>
# *******************************************************************************************

cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME libSettings)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
  VERSION 0.1.0.0
  DESCRIPTION "Entity settings library"
  HOMEPAGE_URL "https://github.com/s-mehrdad/Entity"
  LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND HEADER_FILES
  settings.h
)

list(APPEND SOURCE_FILES
  settings.cpp
)

list(APPEND UI_FILES
  settings.xml
)

if(WIN32)
  #  list(APPEND SOURCE_FILES ${HEADER_FILES})
endif(WIN32)

add_library(${TARGET_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
  ${UI_FILES}
)

target_link_libraries(${TARGET_NAME}
  PUBLIC Qt6::Core
  PUBLIC Qt6::Gui
  PUBLIC Qt6::Qml
  PUBLIC Qt6::Quick
  PUBLIC Qt6::QuickControls2
)

#target_include_directories(${TARGET_NAME} BEFORE
#    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
#  )
