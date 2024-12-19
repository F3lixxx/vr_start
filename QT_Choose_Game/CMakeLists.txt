cmake_minimum_required(VERSION 3.16)

project(Choose_Game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ADB_EXECUTABLE "C:\\platform-tools\\adb.exe")

if (NOT EXISTS ${ADB_EXECUTABLE})
    message (FATAL_ERROR "ADB not found at specified path: ${ADB_EXECUTABLE}")
else()
    message(STATUS "ADB found: ${ADB_EXECUTABLE}")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Choose_Game
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        second_window.h second_window.cpp second_window.ui
        apkfile.h apkfile.cpp apkfile.ui
    )

else()
    if(ANDROID)
        add_library(Choose_Game SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(Choose_Game
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Choose_Game PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Choose_Game)
endif()
set_target_properties(Choose_Game PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Choose_Game
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Choose_Game)
endif()

add_custom_target(RunADB
    COMMAND ${ADB_EXECUTABLE} devices
    COMMENT "Running ADB To check connected devices"
)
add_dependencies(Choose_Game RunADB)
