
#include "Jupiter/Tools.h"
#include "Jupiter/Texture.h"

namespace jupiter
{

using namespace std;

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    Tools::glError();
}

} /* namespace ndk_game */

