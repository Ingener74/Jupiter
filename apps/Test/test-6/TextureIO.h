/*
 * TextureIO.h
 *
 *  Created on: Aug 27, 2015
 *      Author: pavel
 */

#ifndef APPS_TEST_TEST_6_TEXTUREIO_H_
#define APPS_TEST_TEST_6_TEXTUREIO_H_

class In;

class TextureIO {
public:
    TextureIO();
    TextureIO(In* image);
    virtual ~TextureIO();

    In* getImage();
    void setImage(In* image);

private:
    In* _image = nullptr;
};
#endif /* APPS_TEST_TEST_6_TEXTUREIO_H_ */
