# *******************************************************************************************
#/ <summary>
#/ 
#/ </summary>
#/ <created>ʆϒʅ,04.10.2019</created>
#/ <changed>ʆϒʅ,11.10.2019</changed>
# *******************************************************************************************


cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME EntityGTests)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
  VERSION 0.1.0.0
  DESCRIPTION "Google Tests of Entity Game."
  HOMEPAGE_URL "https://github.com/BirdSofts/Entity"
  LANGUAGES CXX
  )

list(APPEND HEADER_FILES
#  gTestsClass.h
  )
list(APPEND SOURCE_FILES
#  main.cpp
#  gTestsClass.cpp
  gTestsFeatures.cpp
  )
if(WIN32)
  list(APPEND SOURCE_FILES ${HEADER_FILES})
endif(WIN32)

add_executable(${TARGET_NAME} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
  PUBLIC GTest::gtest GTest::gtest_main
  PUBLIC Qt5::Core
  PUBLIC Qt5::Gui
  PUBLIC Qt5::Qml
  PUBLIC Qt5::Quick
  PUBLIC Qt5::QuickControls2
  PUBLIC libLogic
  PUBLIC libSettings
  )

gtest_discover_tests(${TARGET_NAME} NO_PRETTY_TYPES NO_PRETTY_VALUES)
