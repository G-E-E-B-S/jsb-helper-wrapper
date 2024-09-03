cmake_minimum_required(VERSION 3.8)

set(JSB_HELPER_BINDING_SRC
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/JSListenerBase.cpp)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/../bindings PREFIX "js-bindings/jsb-helper" FILES ${JSB_HELPER_BINDING_SRC})

list(APPEND CC_ALL_SOURCES ${JSB_HELPER_BINDING_SRC})