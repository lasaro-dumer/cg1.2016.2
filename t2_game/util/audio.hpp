#ifndef audioH
#define audioH
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <ao/ao.h>
#include <semaphore.h>

static const int AUDIO_BUF_SIZE = 4096;

using namespace std;

struct WavHeader {
	char id[4]; //should contain RIFF
	int32_t totalLength;
	char wavefmt[8];
	int32_t format; // 16 for PCM
	int16_t pcm; // 1 for PCM
	int16_t channels;
	int32_t frequency;
	int32_t bytesPerSecond;
	int16_t bytesByCapture;
	int16_t bitsPerSample;
	char data[4]; // "data"
	int32_t bytesInData;
};

static sem_t semAudio;
static bool semAudioInit;

class audio{
private:
	WavHeader header;
	vector<char*> buffers;
public:
	audio(string fileName){
	    this->loadFile(fileName);
	}
	void loadFile(string fileName);
	int playSound();
	static void * tryPlaySoundAsync(void * context){
		if(!semAudioInit){
			sem_init(&semAudio,0,1);
			semAudioInit = true;
		}
		int canRun;
		sem_getvalue(&semAudio, &canRun);
		if(canRun){
	        sem_wait(&semAudio);
			((audio*)context)->playSound();
	        sem_post(&semAudio);
		}
		return NULL;
	}
	static void * playSoundAsync(void * context){
		if(!semAudioInit){
			sem_init(&semAudio,0,1);
			semAudioInit = true;
		}
		int canRun;
		bool played = false;
		do {
			sem_getvalue(&semAudio, &canRun);
			if(canRun){
		        sem_wait(&semAudio);
				((audio*)context)->playSound();
		        sem_post(&semAudio);
				played = true;
			}
		}while(!played);
		
		return NULL;
	}
};
#endif
