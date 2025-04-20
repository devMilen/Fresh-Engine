#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

class Sound
{
public:
    unsigned int buffer;
    unsigned int source;
    ALCdevice* device;
    ALCcontext* context;

    bool isPlaying, isLooping;

    Sound(const char* path);
    ~Sound(); 
    bool loadWAV(const char* filename, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
    void Update(); 
    void Stop();
};
