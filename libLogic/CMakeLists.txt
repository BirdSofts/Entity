
# *******************************************************************************************
#/ <summary>
#/ CMakeLists.txt
#/ Entity - libLogic
#/ created by Mehrdad Soleimanimajd on 04.10.2019
#/ </summary>
#/ <created>ʆϒʅ, 04.10.2019</created>
#/ <changed>ʆϒʅ, 25.06.2023</changed>
# *******************************************************************************************

cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME libLogic)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
    VERSION 0.1.0.0
    DESCRIPTION "Entity logic library"
    HOMEPAGE_URL "https://github.com/s-mehrdad/Entity"
    LANGUAGES CXX
    )

set(CMAKE_INCLUDE_CURRENT_SOURCE_DIR ON)

list(APPEND HEADER_FILES
    logic.h
    )

list(APPEND SOURCE_FILES
    logic.cpp
    )

#if(WIN32)
list(APPEND SOURCE_FILES ${HEADER_FILES})
#endif(WIN32)

add_library(${TARGET_NAME} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
    PUBLIC Qt6::Core
    PUBLIC Qt6::Gui
    PUBLIC Qt6::Qml
    PUBLIC Qt6::Quick
    PUBLIC Qt6::QuickControls2
    )
