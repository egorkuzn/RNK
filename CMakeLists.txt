cmake_minimum_required(VERSION 3.12) #пусть будет

project(RNK) #имя проекта на свой вкус

enable_testing() #какая-то штука вроде нужна

add_subdirectory(unit_tests)

set(HEADERS #собираем все заголовки в кучу под именем HEADERS
    RNK.h
    DNK.h
)

set(SOURCES_MAIN #собираем все сишники с main.cpp чтобы запускать программу как обычно
    RNK.cpp
    main.cpp
    DNK.cpp
)

set(SOURCES_FOR_TEST #собираем все сишники без main.cpp чтобы запихнуть в библиотеку
    RNK.cpp
    DNK.cpp
)

add_library(RNK STATIC ${HEADERS} ${SOURCES_FOR_TEST}) #делаем библиотеку, чтобы наши тесты видели все объявления и определения

add_executable(MAIN ${SOURCES_MAIN}) #шаманим exe`шник чтобы можно было собирать программу и сразу запускать (как обычно)
#MAIN это будет наша конфигурация сборки, он соберёт в кучу сишники с мейном и можно снизу возле треугольника выбирать что запускать
