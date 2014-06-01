
LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/libpng/Android.mk

include $(CLEAR_VARS)

LOCAL_MODULE    := native-activity

LOCAL_CPPFLAGS := -DNDK_GAME_DEBUG

LOCAL_SRC_FILES :=                      \
    Engine/Sprite.cpp                   \
    Engine/Texture.cpp                  \
    Engine/TextureLoader.cpp            \
    Engine/Tools.cpp                    \
    Engine/AssetTextureLoader.cpp       \
    Engine/Image.cpp                    \
    Engine/GLES20Engine.cpp             \
    Engine/Scene.cpp                    \
    Engine/SimpleShaderLoader.cpp       \
    Engine/DummyTextureLoader.cpp       \
    Engine/SimpleSpriteLoader.cpp       \
    Engine/RectSpriteLoader.cpp         \
    Engine/Rect.cpp                     \
                                        \
    Game/GameBuilder.cpp                \
    Game/AssetShaderLoader.cpp          \
    Game/BackGround.cpp                 \
    Game/StartButton.cpp                \
    Game/BattleShip.cpp                 \
    Game/FireButton.cpp                 \
    Game/RightButton.cpp                \
    Game/LeftButton.cpp                 \
    Game/GasButton.cpp                  \
    Game/Bullet.cpp                     \
    Game/Rock.cpp                       \
                                        \
    main.cpp                            \

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lz
LOCAL_STATIC_LIBRARIES := android_native_app_glue png

include $(BUILD_SHARED_LIBRARY)

# import modules from <path-to-android-ndk>/sources/android/native_app_glue
$(call import-module,android/native_app_glue) 
