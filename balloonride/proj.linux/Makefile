EXECUTABLE = ballonride

COCOS_ROOT = $(COCOS2DX_ROOT)
CLASS_ROOT = ../Classes

INCLUDES += \
	-I$(CLASS_ROOT) \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/external/

SOURCES = main.cpp \
	$(CLASS_ROOT)/GameObjects/AnimatedObject.cpp \
	$(CLASS_ROOT)/GameObjects/Enemy.cpp \
	$(CLASS_ROOT)/GameObjects/Balloon.cpp \
	$(CLASS_ROOT)/Scenes/StartScene.cpp \
	$(CLASS_ROOT)/Scenes/MainScene.cpp \
	$(CLASS_ROOT)/Scenes/EndScene.cpp \
	$(CLASS_ROOT)/AppDelegate.cpp \
	$(CLASS_ROOT)/EnemyGenerator.cpp

include ./cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion -lGL
COCOS_LIBS = \
	$(LIB_DIR)/libcocosdenshion.so \
	$(LIB_DIR)/libcocos2d.so

STATICLIBS += \
    $(LIB_DIR)/libbox2d.a \

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
