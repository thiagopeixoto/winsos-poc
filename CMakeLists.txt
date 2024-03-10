cmake_minimum_required(VERSION 3.5)

project(winsos LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

add_definitions(-DUNICODE -D_UNICODE)

add_executable(
    winsos
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/net.cpp
    ${PROJECT_SOURCE_DIR}/src/fs.cpp
    ${PROJECT_SOURCE_DIR}/src/winsos.cpp
)

target_include_directories(winsos PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(
    winsos
    wininet.lib
)
