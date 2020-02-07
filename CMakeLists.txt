cmake_minimum_required(VERSION 3.5)

project(ThGuard LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_subdirectory(thread_guard)
#add_subdirectory(Data)

add_executable(ThGuard
  main.cpp
)

target_include_directories(${PROJECT_NAME}
                    PUBLIC ${PROJECT_SOURCE_DIR}/thread_guard
                    )

target_link_libraries(ThGuard Qt5::Core)
