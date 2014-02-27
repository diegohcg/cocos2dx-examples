LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SpriteMove_shared

LOCAL_MODULE_FILENAME := libSpriteMove

LOCAL_SRC_FILES := SpriteMove/main.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/SpriteLayer.cpp \
				../../Classes/Sprite.cpp

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../Classes \
		$(COCOS2DX_ROOT)/extensions/CCGestureRecognizer

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos2dx)
$(call import-module,extensions)
