/*
 * Engine.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Jupiter/JupiterError.h"
#include "Jupiter/Tools.h"
#include "Jupiter/Game.h"
#include "Jupiter/Node.h"
#include "Jupiter/Sprite.h"
#include "Jupiter/Controller.h"
#include "Jupiter/Image.h"
#include "Jupiter/Texture.h"
#include "Jupiter/File.h"

#include "Jupiter/FileFactory.h"

#include "Jupiter/PngImage.h"

#include "Jupiter/ImageTexture.h"

#include "Jupiter/Shader.h"
#include "Jupiter/FileShader.h"

#include "Jupiter/Shape.h"
#include "Jupiter/ImageShape.h"

//#include "Jupiter/JsonGame.h"

#include "Jupiter/Camera.h"

#include "Jupiter/NodeVisitor.h"
#include "Jupiter/RenderVisitor.h"
#include "Jupiter/PrintVisitor.h"

namespace jupiter {

void initJupiter() throw (JupiterError);

}  // namespace jupiter

#endif /* ENGINE_H_ */
