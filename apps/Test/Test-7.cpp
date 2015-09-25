/*
 * Test-7.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: pavel
 */

#include <iostream>
#include <stdexcept>

#include <AL/al.h>
#include <AL/alc.h>

using namespace std;

class OpenALPlayer {
public:
    OpenALPlayer() {
        ALfloat position[] = { 0.f, 0.f, 0.f };
        ALfloat velocity[] = { 0.f, 0.f, 0.f };
        ALfloat orientation[] = {
            0.f, 0.f, -1.f, // target
            0.f, 1.f,  0.f  // up
        };

        _device = alcOpenDevice(nullptr);
        if (!_device)
            throw runtime_error("can't open device");

        _context = alcCreateContext(_device, nullptr);
        if (!_context)
            throw runtime_error("can't create context");

        auto result = alcMakeContextCurrent(_context);
        if (!result)
            throw runtime_error("can't make context current");

        alListenerfv(AL_POSITION, position);
        alListenerfv(AL_VELOCITY, velocity);
        alListenerfv(AL_ORIENTATION, orientation);
    }
    virtual ~OpenALPlayer() {
        if (_context)
            alcMakeContextCurrent(nullptr);
        if (_context)
            alcDestroyContext(_context);
        if (_device)
            alcCloseDevice(_device);
    }
private:
    ALCdevice* _device = nullptr;
    ALCcontext* _context = nullptr;
};

int main(int argc, char **argv) {
    try {
        cout << "OpenAL test" << endl;
        OpenALPlayer oap;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}

