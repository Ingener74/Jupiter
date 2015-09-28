/*
 * Test-7.cpp
 *
 *  Created on: Sep 25, 2015
 *      Author: pavel
 */

#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>

#include <unistd.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <ogg/ogg.h>
#include <vorbis/codec.h>

using namespace std;

/*
 * Получить данные из файла
 */
vector<uint8_t> getFileData(string const& filename){
    FILE* df = fopen(filename.c_str(), "rb");
    if(!df)
        throw runtime_error("can't open file " + filename);

    fseek(df, 0, SEEK_END);
    auto size = ftell(df);
    rewind(df);

    vector<uint8_t> buffer;
    buffer.resize(size);

    auto res = fread(buffer.data(), sizeof(char), size, df);
    if (res != size)
        throw runtime_error("read error");

    fclose(df);
    return move(buffer);
}

class InputStreamBuffer: public streambuf{
public:
    InputStreamBuffer(vector<uint8_t> const& buffer) :
        _buffer(buffer) {
        setg(reinterpret_cast<char*>(_buffer.data()), reinterpret_cast<char*>(_buffer.data()),
            reinterpret_cast<char*>(_buffer.data()) + _buffer.size());
    }
    virtual ~InputStreamBuffer(){}
private:
    vector<uint8_t> _buffer;
};

class OutputStreamBuffer: public streambuf{
public:
//    const size_t StartSize = 1<<13; // 8 Килобайт
//    const size_t StartSize = 1<<24; // 16 Мегабайт
    const size_t startSize = 1<<26; // 67 Мегабайт
    OutputStreamBuffer() :
        _buffer(startSize) {
        setp(reinterpret_cast<char*>(_buffer.data()), reinterpret_cast<char*>(_buffer.data()) + _buffer.size());
    }
    virtual ~OutputStreamBuffer(){}

    vector<uint8_t> getBuffer() {
        return vector<uint8_t>{pbase(), pptr()};
    }

private:
    vector<uint8_t> _buffer;
};

/**
 * Данные Ogg файла в PCM данные
 */
ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */
int convsize=4096;

vector<uint8_t> getPCMFromOGG(vector<uint8_t> const& data){
    ogg_sync_state   oy; /* sync and verify incoming physical bitstream */
    ogg_stream_state os; /* take physical pages, weld into a logical
                            stream of packets */
    ogg_page         og; /* one Ogg bitstream page. Vorbis packets are inside */
    ogg_packet       op; /* one raw packet of data for decode */

    vorbis_info      vi; /* struct that stores all the static vorbis bitstream
                            settings */
    vorbis_comment   vc; /* struct that stores all the bitstream user comments */
    vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
    vorbis_block     vb; /* local working space for packet->PCM decode */

    const size_t BUFFER_SIZE = 4096;

    InputStreamBuffer inStreamBuffer{data};
    istream inStream{&inStreamBuffer};

    OutputStreamBuffer outStreamBuffer;
    ostream outStream{&outStreamBuffer};

    char *buffer;
    int  bytes;

    /********** Decode setup ************/

    ogg_sync_init(&oy); /* Now we can read pages */

    while(1){ /* we repeat if the bitstream is chained */
      int eos=0;
      int i;

      /* grab some data at the head of the stream. We want the first page
         (which is guaranteed to be small and only contain the Vorbis
         stream initial header) We need the first page to get the stream
         serialno. */

      /* submit a 4k block to libvorbis' Ogg layer */
      buffer=ogg_sync_buffer(&oy,BUFFER_SIZE);

//      bytes=fread(buffer,1,BUFFER_SIZE,some_input_stream);
      inStream.read(buffer, BUFFER_SIZE); // Читаем из моего буфер
      bytes = inStream.gcount();

      ogg_sync_wrote(&oy,bytes);

      /* Get the first page. */
      if(ogg_sync_pageout(&oy,&og)!=1){
        /* have we simply run out of data?  If so, we're done. */
        if(bytes<BUFFER_SIZE)break;

        /* error case.  Must not be Vorbis data */
        throw runtime_error("Input does not appear to be an Ogg bitstream.");
      }

      /* Get the serial number and set up the rest of decode. */
      /* serialno first; use it to set up a logical stream */
      ogg_stream_init(&os,ogg_page_serialno(&og));

      /* extract the initial header from the first page and verify that the
         Ogg bitstream is in fact Vorbis data */

      /* I handle the initial header first instead of just having the code
         read all three Vorbis headers at once because reading the initial
         header is an easy way to identify a Vorbis bitstream and it's
         useful to see that functionality seperated out. */

      vorbis_info_init(&vi);
      vorbis_comment_init(&vc);
      if(ogg_stream_pagein(&os,&og)<0){
    	  throw runtime_error("Error reading first page of Ogg bitstream data.");
      }

      if(ogg_stream_packetout(&os,&op)!=1){
    	  throw runtime_error("Error reading initial header packet.");
      }

      if(vorbis_synthesis_headerin(&vi,&vc,&op)<0){
    	  throw runtime_error("This Ogg bitstream does not contain Vorbis audio data.");
      }

      /* At this point, we're sure we're Vorbis. We've set up the logical
         (Ogg) bitstream decoder. Get the comment and codebook headers and
         set up the Vorbis decoder */

      /* The next two packets in order are the comment and codebook headers.
         They're likely large and may span multiple pages. Thus we read
         and submit data until we get our two packets, watching that no
         pages are missing. If a page is missing, error out; losing a
         header page is the only place where missing data is fatal. */

      i=0;
      while(i<2){
        while(i<2){
          int result=ogg_sync_pageout(&oy,&og);
          if(result==0)break; /* Need more data */
          /* Don't complain about missing or corrupt data yet. We'll
             catch it at the packet output phase */
          if(result==1){
            ogg_stream_pagein(&os,&og); /* we can ignore any errors here
                                           as they'll also become apparent
                                           at packetout */
            while(i<2){
              result=ogg_stream_packetout(&os,&op);
              if(result==0)break;
              if(result<0){
            	  throw runtime_error("Corrupt secondary header.  Exiting.");
              }
              result=vorbis_synthesis_headerin(&vi,&vc,&op);
              if(result<0){
            	  throw runtime_error("Corrupt secondary header.  Exiting.");
              }
              i++;
            }
          }
        }
        /* no harm in not checking before adding more */
        buffer=ogg_sync_buffer(&oy,BUFFER_SIZE);

//        bytes=fread(buffer,1,BUFFER_SIZE,some_input_stream);
        inStream.read(buffer, BUFFER_SIZE); // Читаем из моего буфер
        bytes = inStream.gcount();

        if(bytes==0 && i<2){
        	throw runtime_error("End of file before finding all Vorbis headers!");
        }
        ogg_sync_wrote(&oy,bytes);
      }

      /* Throw the comments plus a few lines about the bitstream we're
         decoding */
      {
        char **ptr=vc.user_comments;
        while(*ptr){
          cout << *ptr << endl;
          ++ptr;
        }
        cout << "Bitstream is " << vi.channels << " channel, " << vi.rate << endl;
        cout << "Encoded by: " << vc.vendor << endl;
      }

      convsize=BUFFER_SIZE/vi.channels;

      /* OK, got and parsed all three headers. Initialize the Vorbis
         packet->PCM decoder. */
      if(vorbis_synthesis_init(&vd,&vi)==0){ /* central decode state */
        vorbis_block_init(&vd,&vb);          /* local state for most of the decode
                                                so multiple block decodes can
                                                proceed in parallel. We could init
                                                multiple vorbis_block structures
                                                for vd here */

        /* The rest is just a straight decode loop until end of stream */
        while(!eos){
          while(!eos){
            int result=ogg_sync_pageout(&oy,&og);
            if(result==0)break; /* need more data */
            if(result<0){ /* missing or corrupt data at this page position */
                stringstream s;
                s << "Corrupt or missing data in bitstream; continuing...\n";
                throw runtime_error(s.str());
            }else{
              ogg_stream_pagein(&os,&og); /* can safely ignore errors at
                                             this point */
              while(1){
                result=ogg_stream_packetout(&os,&op);

                if(result==0)break; /* need more data */
                if(result<0){ /* missing or corrupt data at this page position */
                  /* no reason to complain; already complained above */
                }else{
                  /* we have a packet.  Decode it */
                  float **pcm;
                  int samples;

                  if(vorbis_synthesis(&vb,&op)==0) /* test for success! */
                    vorbis_synthesis_blockin(&vd,&vb);
                  /*

                  **pcm is a multichannel float vector.  In stereo, for
                  example, pcm[0] is left, and pcm[1] is right.  samples is
                  the size of each channel.  Convert the float values
                  (-1.<=range<=1.) to whatever PCM format and write it out */

                  while((samples=vorbis_synthesis_pcmout(&vd,&pcm))>0){
                    int j;
                    int clipflag=0;
                    int bout=(samples<convsize?samples:convsize);

                    /* convert floats to 16 bit signed ints (host order) and
                       interleave */
                    for(i=0;i<vi.channels;i++){
                      ogg_int16_t *ptr=convbuffer+i;
                      float  *mono=pcm[i];
                      for(j=0;j<bout;j++){
  #if 1
                        int val=floor(mono[j]*32767.f+.5f);
  #else /* optional dither */
                        int val=mono[j]*32767.f+drand48()-0.5f;
  #endif
                        /* might as well guard against clipping */
                        if(val>32767){
                          val=32767;
                          clipflag=1;
                        }
                        if(val<-32768){
                          val=-32768;
                          clipflag=1;
                        }
                        *ptr=val;
                        ptr+=vi.channels;
                      }
                    }

                                    if (clipflag)
                                        cerr << "warning: clipping in frame " << (long) (vd.sequence) << endl;


//                    fwrite(convbuffer,2*vi.channels,bout,some_output_stream);
                    outStream.write(reinterpret_cast<char*>(convbuffer), 2*vi.channels * bout);

                    vorbis_synthesis_read(&vd,bout); /* tell libvorbis how
                                                        many samples we
                                                        actually consumed */
                  }
                }
              }
              if(ogg_page_eos(&og))eos=1;
            }
          }
          if(!eos){
            buffer=ogg_sync_buffer(&oy,BUFFER_SIZE);

//            bytes=fread(buffer,1,BUFFER_SIZE,some_input_stream);
            inStream.read(buffer, BUFFER_SIZE); // Читаем из моего буфер
            bytes = inStream.gcount();

            ogg_sync_wrote(&oy,bytes);
            if(bytes==0)eos=1;
          }
        }

        /* ogg_page and ogg_packet structs always point to storage in
           libvorbis.  They're never freed or manipulated directly */

        vorbis_block_clear(&vb);
        vorbis_dsp_clear(&vd);
      }else{
//        fprintf(stderr,"Error: Corrupt header during playback initialization.\n");
          throw runtime_error("Error: Corrupt header during playback initialization.");
      }

      /* clean up this logical bitstream; before exit we see if we're
         followed by another [chained] */

      ogg_stream_clear(&os);
      vorbis_comment_clear(&vc);
      vorbis_info_clear(&vi);  /* must be called last */
    }

    /* OK, clean up the framer */
    ogg_sync_clear(&oy);

    return outStreamBuffer.getBuffer();
}

class Listener {
public:
    Listener() {
        ALfloat position[] = { 0.f, 0.f, 0.f };
        ALfloat velocity[] = { 0.f, 0.f, 0.f };
        ALfloat orientation[] = {
            0.f, 0.f, -1.f, // target
            0.f, 1.f,  0.f  // up
        };

        _device = alcOpenDevice(nullptr);
        if (!_device)
            throw runtime_error("can't open device");

        vector<pair<string, int>> exts{
            {"ALC_DEFAULT_DEVICE_SPECIFIER          ", ALC_DEFAULT_DEVICE_SPECIFIER        },
            {"ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER  ", ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER},
            {"ALC_DEVICE_SPECIFIER                  ", ALC_DEVICE_SPECIFIER                },
            {"ALC_CAPTURE_DEVICE_SPECIFIER          ", ALC_CAPTURE_DEVICE_SPECIFIER        },
            {"ALC_EXTENSIONS                        ", ALC_EXTENSIONS                      },
        };
        for_each(exts.begin(), exts.end(), [=](pair<string, int> const& i){
            cout << i.first << " " << alcGetString(_device, i.second) << endl;
        });

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
    virtual ~Listener() {
        if (_context)
            alcMakeContextCurrent(nullptr);
        if (_context)
            alcDestroyContext(_context);
        if (_device)
            alcCloseDevice(_device);
    }

    static void checkErrors(){
        ALenum error = AL_NO_ERROR;
        if ((error = alGetError()) != AL_NO_ERROR) {
            stringstream s;
            s << "OpenAL error: 0x" << hex << error;
            throw runtime_error(s.str());
        }
    }

private:
    ALCdevice* _device = nullptr;
    ALCcontext* _context = nullptr;
};

/**
 * Класс источника звука(пока что вместе с буфером)
 */
class Speaker {
public:
    Speaker(string const& filename, bool loop = false) {
        Listener::checkErrors();

        alGenBuffers(1, &_buffer);
        Listener::checkErrors();

        const ALvoid* data = nullptr;
        ALsizei size = 0;
        ALsizei freq = 0;

        auto pcmData = getPCMFromOGG(getFileData(filename));

        data = pcmData.data();
        size = pcmData.size();
//        freq = 48000;
        freq = 44100;

        cout << "buffer data" << endl;

        alBufferData(_buffer, AL_FORMAT_STEREO16, data, size, freq);

        cout << "buffer data end" << endl;

        alGenSources(1, &_source);
        Listener::checkErrors();

        alSourcei(_source, AL_BUFFER, _buffer);
        alSourcef(_source, AL_PITCH, 1.f);
        alSourcef(_source, AL_GAIN, 1.f);
        alSourcefv(_source, AL_POSITION, _position);
        alSourcefv(_source, AL_VELOCITY, _velocity);
    }
    virtual ~Speaker() {
        alDeleteSources(1, &_source);
        alDeleteBuffers(1, &_buffer);
    }

    void play(){
        alSourcePlay(_source);
    }

    void stop(){
        alSourceStop(_source);
    }

private:
    ALfloat _position[3] = {0.f, 0.f, 0.f};
    ALfloat _velocity[3] = {0.f, 0.f, 0.f};
    ALuint _buffer;
    ALuint _source;
};

int main(int argc, char **argv) {
    try {
        cout << "OpenAL test" << endl;

        if (argc < 2)
            throw runtime_error("Usage: ./Test-7 </path/to/ogg/file>");

        Listener oap;

        Speaker sound(argv[1]);

        cout << "Enter command: " << endl
            << "p for play" << endl
            << "s for stop" << endl
            << "q for quit" << endl;

        char command = ' ';
        while(command != 'q'){
            cin >> command;
            switch(command){
            case 'p':
                sound.play();
                break;
            case 's':
                sound.stop();
                break;
            }
        }

        cout << "Good bye" << endl;

    } catch (exception const& e) {
        cerr << e.what() << endl;
    }
}

