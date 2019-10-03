# *******************************************************************************************
#/ <summary>
#/ 
#/ </summary>
#/ <created>ʆϒʅ,03.10.2019</created>
#/ <changed>ʆϒʅ,04.10.2019</changed>
# *******************************************************************************************


cmake_minimum_required(VERSION 3.5)

set(RELEASE_FLAG OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(TARGET_NAME entity)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
  VERSION 0.1.0.0
  DESCRIPTION "Entity Game"
  HOMEPAGE_URL "https://github.com/BirdSofts/Entity"
  LANGUAGES CXX
  )

include(CTest)

if(MSVC)
  find_package(GTest CONFIG REQUIRED)
  include(GoogleTest)
endif(MSVC)

enable_testing()

if(NOT CMAKE_MODULE_PATH)
  if(MSVC)
    set(QT_BINARIES "C:/Qt/5.13.1/msvc2017_64/bin")
    set(Qt5_DIR "C:/Qt/5.13.1/msvc2017_64/lib/cmake/Qt5")
  else(MSVC)
    set(QT_BINARIES "C:/Qt/5.13.1/mingw73_64/bin")
  endif(MSVC)
endif()

find_package(Qt5 COMPONENTS
  Core
  Gui
  Qml
  Quick
  QuickControls2
  REQUIRED)

add_subdirectory(libSettings)

if(MSVC)
  add_subdirectory(gtests)
endif(MSVC)

if(MSVC)
  list(APPEND RESOURCES
    ${TARGET_NAME}.rc
    resource.h
    )
endif(MSVC)

list(APPEND HEADER_FILES
  )

list(APPEND SOURCE_FILES
  main.cpp
  )

list(APPEND QRC_FILES
  ${TARGET_NAME}.qrc
  )

if(WIN32)
  list(APPEND SOURCE_FILES ${HEADER_FILES})
  list(APPEND SOURCE_FILES ${QRC_FILES})
endif(WIN32)

if(ANDROID)
  add_library(${TARGET_NAME} SHARED ${SOURCE_FILES} ${RESOURCES})
elseif(WIN32)
  add_executable(${TARGET_NAME} WIN32 ${SOURCE_FILES} ${RESOURCES})
else(WIN32)
  add_executable(${TARGET_NAME} ${SOURCE_FILES} ${RESOURCES})
endif(ANDROID)

#target_compile_definitions(${TARGET_NAME}
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${TARGET_NAME}
  PUBLIC Qt5::Core
  PUBLIC Qt5::Gui
  PUBLIC Qt5::Qml
  PUBLIC Qt5::Quick
  PUBLIC Qt5::QuickControls2
  PUBLIC libSettings
  )

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# These variables must use CACHE, otherwise QtCreator won't see them.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android" CACHE INTERNAL "")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so CACHE INTERNAL "")
#    endif()
#endif()

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
  COMMAND cmake -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/libSettings/settings.xml
  $<TARGET_FILE_DIR:${TARGET_NAME}>
  )

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
  COMMAND cmake -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/libSettings/settings.xml
  $<TARGET_FILE_DIR:${TARGET_NAME}>/gtests
  )

if(MSVC)
  add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
    COMMAND cmake -E copy_if_different
    ${QT_BINARIES}/Qt5Core.dll
    ${QT_BINARIES}/Qt5Cored.dll
    ${QT_BINARIES}/Qt5Gui.dll
    ${QT_BINARIES}/Qt5Guid.dll
    ${QT_BINARIES}/Qt5Network.dll
    ${QT_BINARIES}/Qt5Networkd.dll
    ${QT_BINARIES}/Qt5Qml.dll
    ${QT_BINARIES}/Qt5Qmld.dll
    ${QT_BINARIES}/Qt5Quick.dll
    ${QT_BINARIES}/Qt5Quickd.dll
    ${QT_BINARIES}/Qt5QuickControls2.dll
    ${QT_BINARIES}/Qt5QuickControls2d.dll
    ${QT_BINARIES}/Qt5QuickTemplates2.dll
    ${QT_BINARIES}/Qt5QuickTemplates2d.dll
    ${QT_BINARIES}/Qt5QuickWidgets.dll
    ${QT_BINARIES}/Qt5QuickWidgetsd.dll
    ${QT_BINARIES}/Qt5Widgets.dll
    ${QT_BINARIES}/Qt5Widgetsd.dll
    $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
    COMMAND cmake -E copy_if_different
    ${QT_BINARIES}/Qt5Core.dll
    ${QT_BINARIES}/Qt5Cored.dll
    ${QT_BINARIES}/Qt5Gui.dll
    ${QT_BINARIES}/Qt5Guid.dll
    ${QT_BINARIES}/Qt5Network.dll
    ${QT_BINARIES}/Qt5Networkd.dll
    ${QT_BINARIES}/Qt5Qml.dll
    ${QT_BINARIES}/Qt5Qmld.dll
    ${QT_BINARIES}/Qt5Quick.dll
    ${QT_BINARIES}/Qt5Quickd.dll
    ${QT_BINARIES}/Qt5QuickControls2.dll
    ${QT_BINARIES}/Qt5QuickControls2d.dll
    ${QT_BINARIES}/Qt5QuickTemplates2.dll
    ${QT_BINARIES}/Qt5QuickTemplates2d.dll
    ${QT_BINARIES}/Qt5QuickWidgets.dll
    ${QT_BINARIES}/Qt5QuickWidgetsd.dll
    ${QT_BINARIES}/Qt5Widgets.dll
    ${QT_BINARIES}/Qt5Widgetsd.dll
    $<TARGET_FILE_DIR:${TARGET_NAME}>/gtests
    )
endif(MSVC)

if(RELEASE_FLAG)
  if(MINGW)
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
      COMMAND cmake -E copy_if_different
      ${QT_BINARIES}/libgcc_s_seh-1.dll
      ${QT_BINARIES}/libstdc++-6.dll
      ${QT_BINARIES}/libwinpthread-1.dll
      ${QT_BINARIES}/Qt5Core.dll
      ${QT_BINARIES}/Qt5Cored.dll
      ${QT_BINARIES}/Qt5Gui.dll
      ${QT_BINARIES}/Qt5Guid.dll
      ${QT_BINARIES}/Qt5Network.dll
      ${QT_BINARIES}/Qt5Networkd.dll
      ${QT_BINARIES}/Qt5Qml.dll
      ${QT_BINARIES}/Qt5Qmld.dll
      ${QT_BINARIES}/Qt5Quick.dll
      ${QT_BINARIES}/Qt5Quickd.dll
      ${QT_BINARIES}/Qt5QuickControls2.dll
      ${QT_BINARIES}/Qt5QuickControls2d.dll
      ${QT_BINARIES}/Qt5QuickTemplates2.dll
      ${QT_BINARIES}/Qt5QuickTemplates2d.dll
      ${QT_BINARIES}/Qt5QuickWidgets.dll
      ${QT_BINARIES}/Qt5QuickWidgetsd.dll
      ${QT_BINARIES}/Qt5Widgets.dll
      ${QT_BINARIES}/Qt5Widgetsd.dll
      $<TARGET_FILE_DIR:${TARGET_NAME}>
      )
  endif(MINGW)
endif(RELEASE_FLAG)

#if(GNUCXX)
#
#endif(GNUCXX)
