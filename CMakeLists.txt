
# *******************************************************************************************
#/ <summary>
#/ CMakeLists.txt
#/ Entity
#/ created by Mehrdad Solimanimajd on 03.10.2019
#/ </summary>
#/ <created>ʆϒʅ, 03.10.2019</created>
#/ <changed>ʆϒʅ, 01.03.2023</changed>
# *******************************************************************************************

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(RELEASE_FLAG OFF)

set(TARGET_NAME Entity)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
  VERSION 0.1.0.0
  DESCRIPTION "Entity Game"
  HOMEPAGE_URL "https://github.com/s-mehrdad/Entity"
  LANGUAGES CXX
)

include(CTest)

if(MSVC)
  find_package(GTest CONFIG REQUIRED)
  include(GoogleTest)
endif(MSVC)

enable_testing()

find_package(Qt6 COMPONENTS
  Core
  Gui
  Qml
  Quick
  QuickControls2
  REQUIRED)

add_subdirectory(libTale)
add_subdirectory(libSettings)
add_subdirectory(libLogic)

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
endif(WIN32)

if(ANDROID)
  add_library(${TARGET_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${QRC_FILES}
    ${RESOURCES}
  )

elseif(WIN32)
  add_executable(${TARGET_NAME} WIN32
    ${SOURCE_FILES}
    ${QRC_FILES}
    ${RESOURCES}
  )

else(WIN32)
  add_executable(${TARGET_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${QRC_FILES}
    ${RESOURCES})
endif(ANDROID)

#target_compile_definitions(${TARGET_NAME}
#  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${TARGET_NAME}
  PUBLIC Qt6::Core
  PUBLIC Qt6::Gui
  PUBLIC Qt6::Qml
  PUBLIC Qt6::Quick
  PUBLIC Qt6::QuickControls2
  PUBLIC libTale
  PUBLIC libSettings
  PUBLIC libLogic
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
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/libSettings/settings.xml
  $<TARGET_FILE_DIR:${TARGET_NAME}>
  VERBATIM)

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/libSettings/settings.xml
  $<TARGET_FILE_DIR:${TARGET_NAME}>/gtests
  VERBATIM)

install(FILES libSettings/settings.xml
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(FILES libSettings/settings.xml
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/gtests)

if(RELEASE_FLAG)
  if(MINGW)
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
      COMMAND cmake -E copy_if_different
      ${QT_BINARIES}/libgcc_s_seh-1.dll
      ${QT_BINARIES}/libstdc++-6.dll
      ${QT_BINARIES}/libwinpthread-1.dll
      ${QT_BINARIES}/Qt6Core.dll
      ${QT_BINARIES}/Qt6Cored.dll
      ${QT_BINARIES}/Qt6Gui.dll
      ${QT_BINARIES}/Qt6Guid.dll
      ${QT_BINARIES}/Qt6Network.dll
      ${QT_BINARIES}/Qt6Networkd.dll
      ${QT_BINARIES}/Qt6Qml.dll
      ${QT_BINARIES}/Qt6Qmld.dll
      ${QT_BINARIES}/Qt6Quick.dll
      ${QT_BINARIES}/Qt6Quickd.dll
      ${QT_BINARIES}/Qt6QuickControls2.dll
      ${QT_BINARIES}/Qt6QuickControls2d.dll
      ${QT_BINARIES}/Qt6QuickTemplates2.dll
      ${QT_BINARIES}/Qt6QuickTemplates2d.dll
      ${QT_BINARIES}/Qt6QuickWidgets.dll
      ${QT_BINARIES}/Qt6QuickWidgetsd.dll
      ${QT_BINARIES}/Qt6Widgets.dll
      ${QT_BINARIES}/Qt6Widgetsd.dll
      $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endif(MINGW)
endif(RELEASE_FLAG)

#if(GNUCXX)
#
#endif(GNUCXX)
