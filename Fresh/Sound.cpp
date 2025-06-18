#include "Sound.h"

Sound::Sound(const char* path)
    : isPlaying(false), isLooping(false) // Initialize flags
{
    // Open the audio device
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open audio device" << std::endl;
        return;
    }

    // Create an OpenAL context and set it as current
    context = alcCreateContext(device, nullptr);
    if (!alcMakeContextCurrent(context)) {
        std::cerr << "Failed to set audio context" << std::endl;
        return;
    }

    // Load the WAV file
    ALenum format;
    ALsizei freq;
    std::vector<char> data;
    if (!loadWAV(path, data, format, freq)) {
        std::cerr << "Failed to load WAV file: " << path << std::endl;
        return;
    }

    // Create OpenAL buffer and load the data
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data.data(), data.size(), freq);

    // Create OpenAL source
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    // Initially set to play the sound
    alSourcePlay(source);
    isPlaying = true;
}

Sound::~Sound()
{
    // Delete OpenAL resources
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    // Close the OpenAL context and device
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool Sound::loadWAV(const char* filename, std::vector<char>& buffer, ALenum& format, ALsizei& freq)
{
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "rb");  // Use fopen_s for safe file opening
    if (err != 0 || file == nullptr) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read WAV header and extract relevant data
    char chunkID[4];
    fread(chunkID, 1, 4, file);
    if (std::string(chunkID, 4) != "RIFF") {
        std::cerr << "Not m_a valid WAV file" << std::endl;
        fclose(file);
        return false;
    }

    fseek(file, 20, SEEK_SET);
    short audioFormat;
    fread(&audioFormat, sizeof(short), 1, file);
    if (audioFormat != 1) { // PCM format
        std::cerr << "Not PCM format" << std::endl;
        fclose(file);
        return false;
    }

    short numChannels;
    fread(&numChannels, sizeof(short), 1, file);
    fread(&freq, sizeof(ALsizei), 1, file);

    fseek(file, 34, SEEK_SET);
    short bitsPerSample;
    fread(&bitsPerSample, sizeof(short), 1, file);

    if (numChannels == 1) {
        format = (bitsPerSample == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    }
    else {
        format = (bitsPerSample == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }

    fseek(file, 40, SEEK_SET);
    int dataSize;
    fread(&dataSize, sizeof(int), 1, file);

    buffer.resize(dataSize);
    fread(buffer.data(), 1, dataSize, file);

    fclose(file);
    return true;
}

void Sound::Update()
{
    // Check if sound should be playing and if it's not playing yet
    if (isPlaying) {
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);

        // If sound is finished playing, reset the flag
        if (state != AL_PLAYING) {
            if (isLooping) {
                // If looping is enabled, restart the sound
                alSourcePlay(source);
            }
            else {
                // Stop the sound if not looping
                isPlaying = false;
                alSourceStop(source);
            }
        }
    }
}

void Sound::Stop() {
    if (isPlaying) {
        alSourceStop(source);
        isPlaying = false;
    }
}
