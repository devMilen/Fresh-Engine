#pragma once
#include "Sprite.h"
#include <vector>

class Animation {
public:
    std::vector<GL::Texture> frames;
    std::vector<float> durations;

    Sprite sprite;

    unsigned int index = 0;
    float timeSinceLastFrame = 0.0f;
    bool isPlaying = true;
    bool isLooping = false;

    Animation();
    Animation(const Sprite& sprite, const std::vector<GL::Texture>& frames, const std::vector<float>& durations);
    Animation(const Sprite& sprite, const std::vector<const char*>& paths, bool flipVerticaly, const std::vector<float>& durations);
    Animation(const Sprite& sprite, const std::vector<const char*>& paths, bool flipVerticaly, float duration);
    Animation(const Sprite& sprite, const std::vector<GL::Texture>& frames, float duration);


    bool Update(float dt);
    void Reset();
    void Play();
    void Stop();
    void SetLooping(bool loop);
    const Sprite& CurFrame();
    const GL::Texture& CurTexture();
};

