cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(BOOST_ROOT "C:/Repo/boost_1_66_0")
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_LIBRARYDIR "C:/Repo/boost_1_66_0/libs")

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


find_package(Boost REQUIRED)

if (Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы

    # Создайте исполняемый файл для основного проекта
    add_executable(MyApp main.cpp)

    add_executable(MyTests MyTest.cpp)	

    # Свяжите основной проект с библиотекой Boost
    target_link_libraries(MyApp ${Boost_LIBRARIES})
	
    target_link_libraries(MyTests ${Boost_LIBRARIES})

endif ()