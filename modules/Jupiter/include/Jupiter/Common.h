/*
 * Common.h
 *
 *  Created on: 25 ��� 2014 �.
 *      Author: Admin
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifndef ANDROID
	#include <execinfo.h>
#endif

#include <list>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

#include <png.h>

#include <selene.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef ANDROID
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
	#include <GLES2/gl2platform.h>

	#include <android/log.h>
	#include <android/asset_manager.h>
	#include <android_native_app_glue.h>

	#include <SLES/OpenSLES.h>
	#include <SLES/OpenSLES_Android.h>
	#include <SLES/OpenSLES_AndroidConfiguration.h>
#else
	#include <GL/glew.h>
	#include <GL/gl.h>
#endif


#endif /* COMMON_H_ */
