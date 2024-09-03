LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsbhelper

LOCAL_MODULE_FILENAME := libjsbhelper

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := ../src/JSListenerBase.cpp

LOCAL_CFLAGS    += -DIS_ANDROID
LOCAL_CPPFLAGS    += -DIS_ANDROID

LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)

$(call import-module, cocos)
