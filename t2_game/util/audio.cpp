#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include <stdlib.h>
#include <assert.h>
#include <ao/ao.h>
#include "audio.hpp"

using namespace std;

void audio::loadFile(string fileName){
    std::ifstream file;
    file.open(fileName.c_str(), std::ios::binary | std::ios::in);

    file.read(this->header.id, sizeof(this->header.id));
    assert(!std::memcmp(this->header.id, "RIFF", 4)); //is it a WAV file?
    file.read((char*)&this->header.totalLength, sizeof(this->header.totalLength));
    file.read(this->header.wavefmt, sizeof(this->header.wavefmt)); //is it the right format?
    assert(!std::memcmp(this->header.wavefmt, "WAVEfmt ", 8));
    file.read((char*)&this->header.format, sizeof(this->header.format));
    file.read((char*)&this->header.pcm, sizeof(this->header.pcm));
    file.read((char*)&this->header.channels, sizeof(this->header.channels));
    file.read((char*)&this->header.frequency, sizeof(this->header.frequency));
    file.read((char*)&this->header.bytesPerSecond, sizeof(this->header.bytesPerSecond));
    file.read((char*)&this->header.bytesByCapture, sizeof(this->header.bytesByCapture));
    file.read((char*)&this->header.bitsPerSample, sizeof(this->header.bitsPerSample));
    file.read(this->header.data, sizeof(this->header.data));
    file.read((char*)&this->header.bytesInData, sizeof(this->header.bytesInData));

    // determine how many AUDIO_BUF_SIZE chunks are in file
    int fSize = this->header.bytesInData;
    int bCount = fSize / AUDIO_BUF_SIZE;

    for (int i = 0; i < bCount; ++i) {
        char* buffer = (char*)malloc(AUDIO_BUF_SIZE * sizeof(char));
        file.read(buffer, AUDIO_BUF_SIZE);
        this->buffers.push_back(buffer);
    }
    char* leftOverBuffer = (char*)malloc(AUDIO_BUF_SIZE * sizeof(char));
    int leftoverBytes = fSize % AUDIO_BUF_SIZE;
    // std::cout << leftoverBytes << endl;
    file.read(leftOverBuffer, leftoverBytes);
    memset(leftOverBuffer + leftoverBytes, 0, AUDIO_BUF_SIZE - leftoverBytes);
    this->buffers.push_back(leftOverBuffer);
}

int audio::playSound() {
    ao_device* device;
    ao_sample_format format;
    int defaultDriver;

    ao_initialize();

    defaultDriver = ao_default_driver_id();

    memset(&format, 0, sizeof(format));
    format.bits = this->header.format;
    format.channels = this->header.channels;
    format.rate = this->header.frequency;
    format.byte_format = AO_FMT_LITTLE;

    device = ao_open_live(defaultDriver, &format, NULL);
    if (device == NULL) {
        std::cout << "Unable to open driver" << std::endl;
        return 1;
    }

    vector<char*>::iterator ib;
    for (ib = this->buffers.begin(); ib != this->buffers.end(); ++ib) {
        ao_play(device, (*ib), AUDIO_BUF_SIZE);
    }

    ao_close(device);
    ao_shutdown();
}
