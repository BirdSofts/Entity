
# *******************************************************************************************
#/ <summary>
#/ CMekaLists.txt
#/ Entity - libTale
#/ created by Mehrdad Soleimanimajd on 21.10.2019
#/ </summary>
#/ <created>ʆϒʅ, 21.10.2019</created>
#/ <changed>ʆϒʅ, 25.06.2023</changed>
# *******************************************************************************************

cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME libTale)

set(PROJECT_NAME ${TARGET_NAME})

project(${PROJECT_NAME}
    VERSION 0.1.0.0
    DESCRIPTION "Entity tale library"
    HOMEPAGE_URL "https://github.com/s-mehrdad/Entity"
    LANGUAGES CXX
    )

set(CMAKE_INCLUDE_CURRENT_SOURCE_DIR ON)

list(APPEND HEADER_FILES
    tale.h
    )

list(APPEND SOURCE_FILES
    tale.cpp
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
    )
