EXECUTABLE = spritemove

COCOS_ROOT = $(COCOS2DX_ROOT)
CLASS_ROOT = ../Classes

INCLUDES += \
	-I$(CLASS_ROOT) \
	-I$(CLASS_ROOT)/CCGestureRecognizer/ \
	-I$(COCOS_ROOT)/external/ \

SOURCES = main.cpp \
		  $(CLASS_ROOT)/AppDelegate.cpp \
		  $(CLASS_ROOT)/SpriteLayer.cpp \
		  $(CLASS_ROOT)/Sprite.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCLongPressGestureRecognizer.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCGestureRecognizer.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCPanGestureRecognizer.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCPinchGestureRecognizer.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCSwipeGestureRecognizer.cpp \
		  $(CLASS_ROOT)/CCGestureRecognizer/CCTapGestureRecognizer.cpp \

include ./cocos2dx.mk

SHAREDLIBS += -lcocos2d -lGL
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

#STATICLIBS += \
    #$(LIB_DIR)/libextension.a \

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
