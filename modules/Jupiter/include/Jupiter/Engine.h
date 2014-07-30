/*
 * Engine.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <Engine/IDrawEngine.h>
#include <Engine/GLES20Engine.h>
#include <Engine/IGameObject.h>

#include <Engine/IShaderLoader.h>
#include <Engine/SimpleShaderLoader.h>

#include <Engine/Texture.h>
#include <Engine/TextureLoader.h>
#include <Engine/AssetTextureLoader.h>
#include <Engine/DummyTextureLoader.h>

#include <Engine/Sprite.h>
#include <Engine/ISpriteLoader.h>
#include <Engine/SimpleSpriteLoader.h>
#include <Engine/RectSpriteLoader.h>

#include <Engine/ISoundEngine.h>
#include <Engine/SLESSoundEngine.h>
#include <Engine/DummySoundEngine.h>

#include <Engine/ISound.h>
#include <Engine/SLESSound.h>
#include <Engine/DummySound.h>

#include <Engine/Tools.h>
#include <Engine/Log.h>
#include <Engine/Rect.h>
#include <Engine/Scene.h>
#include <Engine/Image.h>

#endif /* ENGINE_H_ */
