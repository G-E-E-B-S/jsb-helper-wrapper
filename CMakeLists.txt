set(PROJ_NAME jsb-helper)
set (PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/JSListenerBase.cpp)
set(JSB_HELPER_INCLUDE_DIR
    ${CMAKE_CURRENT_LIST_DIR})

add_library(${PROJ_NAME} STATIC ${PROJ_SOURCES})

target_include_directories(${PROJ_NAME} PUBLIC
    ${COCOS_X_PATH}
    ${COCOS_X_PATH}/cocos
    ${COCOS_X_PATH}/cocos/renderer
if (COCOS_3_7_PLUS)
    ${COCOS_X_PATH}/cocos/bindings/jswrapper
endif()
    ${platform_spec_path}/include/v8
    ${CMAKE_CURRENT_LIST_DIR})