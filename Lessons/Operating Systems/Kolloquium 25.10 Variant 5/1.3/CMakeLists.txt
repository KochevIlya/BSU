cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_executable(MyApp main.cpp)
set(BOOST_ROOT "C:/Repo/boost_1_66_0")


find_package(Boost REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы

add_executable(MyTests MyTest.cpp)

target_link_libraries(MyTests ${Boost_LIBRARIES})
