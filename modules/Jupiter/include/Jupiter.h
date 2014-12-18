/*
 * Engine.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <Jupiter/facade/Game.h>
#include <Jupiter/facade/Sprite.h>
#include <Jupiter/facade/Node.h>
#include <Jupiter/facade/Controller.h>
#include <Jupiter/Image.h>
#include <Jupiter/JupiterError.h>
#include <Jupiter/Texture.h>

#include <Jupiter/DrawEngine.h>
#include <Jupiter/IGameObject.h>

#include <Jupiter/ResourceManager.h>
#include <Jupiter/FStreamResource.h>
#include <Jupiter/FileResource.h>

#include <Jupiter/IShaderLoader.h>
#include <Jupiter/SimpleShaderLoader.h>
#include <Jupiter/ResourceShaderLoader.h>

#include <Jupiter/TextureLoader.h>
#include <Jupiter/DummyTextureLoader.h>
#include <Jupiter/FileTextureLoader.h>

#include <Jupiter/ISpriteLoader.h>
#include <Jupiter/SimpleSpriteLoader.h>
#include <Jupiter/RectSpriteLoader.h>

#include <Jupiter/ISoundEngine.h>
#include <Jupiter/DummySoundEngine.h>

#include <Jupiter/ISound.h>
#include <Jupiter/DummySound.h>

#include <Jupiter/Tools.h>
#include <Jupiter/Rect.h>
#include <Jupiter/Scene.h>
#include <Jupiter/detail/SpriteBuilder.h>
#include <Jupiter/detail/FileSpriteFactory.h>

#include <Jupiter/detail/ImageBuilder.h>
#include <Jupiter/detail/PNGImageFactory.h>

#ifdef ANDROID
	#include <Jupiter/SLESSound.h>
	#include <Jupiter/SLESSoundEngine.h>
	#include <Jupiter/AssetTextureLoader.h>
	#include <Jupiter/GLES20Engine.h>
#else
#endif

#endif /* ENGINE_H_ */
