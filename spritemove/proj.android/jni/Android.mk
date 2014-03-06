LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SpriteMove_shared

LOCAL_MODULE_FILENAME := libSpriteMove

LOCAL_SRC_FILES := \
				SpriteMove/main.cpp \
				../../Classes/CCGestureRecognizer/CCLongPressGestureRecognizer.cpp \
				../../Classes/CCGestureRecognizer/CCGestureRecognizer.cpp \
				../../Classes/CCGestureRecognizer/CCPanGestureRecognizer.cpp \
				../../Classes/CCGestureRecognizer/CCPinchGestureRecognizer.cpp \
				../../Classes/CCGestureRecognizer/CCSwipeGestureRecognizer.cpp \
				../../Classes/CCGestureRecognizer/CCTapGestureRecognizer.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/SpriteLayer.cpp \
				../../Classes/Sprite.cpp \

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../Classes \
		$(LOCAL_PATH)/../../Classes/CCGestureRecognizer

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos2dx)
