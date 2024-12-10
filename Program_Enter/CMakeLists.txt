cmake_minimum_required(VERSION 3.20)
project(LauncherApk VERSION 1.0 LANGUAGES CXX)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка полного пути к ADB
set(ADB_EXECUTABLE "C:/ADB_Programm/platform-tools/adb.exe")

if(NOT EXISTS ${ADB_EXECUTABLE})
    message(FATAL_ERROR "ADB not found at specified path: ${ADB_EXECUTABLE}")
else()
    message(STATUS "ADB found: ${ADB_EXECUTABLE}")
endif()

# Добавление исполняемого файла
add_executable(LauncherApk main.cpp)

# Проверка ADB
add_custom_target(RunADB
    COMMAND ${ADB_EXECUTABLE} devices
    COMMENT "Running ADB to check connected devices"
)

# Добавление зависимости
add_dependencies(LauncherApk RunADB)
