LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := BalloonRide_shared

LOCAL_MODULE_FILENAME := libBalloonRide

LOCAL_SRC_FILES := \
				BalloonRide/main.cpp \
				../../Classes/GameObjects/AnimatedObject.cpp \
				../../Classes/GameObjects/Enemy.cpp \
				../../Classes/GameObjects/Balloon.cpp \
				../../Classes/Scenes/StartScene.cpp \
				../../Classes/Scenes/MainScene.cpp \
				../../Classes/Scenes/EndScene.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/EnemyGenerator.cpp

LOCAL_C_INCLUDES := \
		$(COCOS2DX_ROOT)/CocosDenshion/include \
		$(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos2dx)
$(call import-module,CocosDenshion/android)
