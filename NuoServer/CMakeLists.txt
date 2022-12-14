cmake_minimum_required(VERSION 3.5)

project(NuoServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
find_package(sqlite3 PATHS C:/Users/User/Desktop/QTPliki/NuoProject/NuoServer/lib)
find_package(Qt6 REQUIRED COMPONENTS Sql)
#include_directories(/usr/include)
#link_directories(/usr/lib)
#target_link_libraries(tutorial sqlite3)

set(PROJECT_SOURCES
        main.cpp
        ekran.cpp
        ekran.h
        ekran.ui
        nuoserver.cpp
        nuoserver.h
        gra.cpp
        gra.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NuoServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NuoServer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NuoServer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NuoServer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NuoServer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(NuoServer PRIVATE Qt6::Sql)

set_target_properties(NuoServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS NuoServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NuoServer)
endif()

target_link_libraries(NuoServer
    PRIVATE Qt${QT_VERSION_MAJOR}::Network)

add_library(essa
        C:/Users/User/Desktop/QTPliki/NuoProject/Nuo2/gracz.h
        C:/Users/User/Desktop/QTPliki/NuoProject/Nuo2/gracz.cpp)

target_include_directories(essa PUBLIC "C:/Users/User/Desktop/QTPliki/NuoProject/Nuo2")

target_link_libraries(NuoServer PRIVATE essa)
