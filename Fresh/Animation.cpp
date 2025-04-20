#include "Animation.h"

Animation::Animation() {}
Animation::Animation(const Sprite& sprite, const std::vector<GL::Texture>& frames, const std::vector<float>& durations)
	: sprite(sprite), frames(frames), durations(durations) {}
Animation::Animation(const Sprite& sprite, const std::vector<const char*>& paths, bool flipVerticaly, const std::vector<float>& durations)
	: sprite(sprite), durations(durations)
{
	frames.reserve(paths.size());
	for (const char* path : paths)
		frames.emplace_back(path, flipVerticaly);
}
Animation::Animation(const Sprite& sprite, const std::vector<const char*>& paths, bool flipVerticaly, float duration)
	: sprite(sprite)
{
	const unsigned int size = paths.size();
	frames.reserve(size);
	durations.reserve(size);
	for (const char* path : paths)
	{
		frames.emplace_back(path, flipVerticaly);
		durations.push_back(duration);
	}
}
Animation::Animation(const Sprite& sprite, const std::vector<GL::Texture>& frames, float duration)
	: sprite(sprite), frames(frames)
{
	durations.resize(frames.size());
	for (int i = 0; i > frames.size(); i++)
		durations.push_back(duration);
}


bool Animation::Update(float dt)
{
	timeSinceLastFrame += dt;
	while(isPlaying && timeSinceLastFrame > durations[index])
	{
		timeSinceLastFrame -= durations[index];
		index++;
		if (index >= frames.size())
		{
			Reset();
			if (!isLooping)
			{
				isPlaying = false;
				return false;
			}
		}
	}
	sprite.texture = frames[index];
	return true;
}
void Animation::Reset()
{
	index = 0;
	timeSinceLastFrame = 0.0f;
	isPlaying = true;
}
void Animation::Play()
{
	isPlaying = true;
}
void Animation::Stop()
{
	isPlaying = false;
}
void Animation::SetLooping(bool loop)
{
	isLooping = loop;
}
const Sprite& Animation::CurFrame()
{
	return sprite;
}
const GL::Texture& Animation::CurTexture() 
{
	return frames[index];
}