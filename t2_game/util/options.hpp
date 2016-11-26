#ifndef optionsH
#define optionsH
#include <string>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <queue>
#include <GLee.h>

using namespace std;

class options {
private:
    string path = "options.ini";
    bool saved;
    bool fullscreen,fullscreenMaxSize;
	bool useAmbient;
	bool audioSuccess;
    int fullscreenWidth,fullscreenHeight;
    int windowedWidth,windowedHeight;
    GLfloat sensitivity,cameraSpeed;
	GLfloat shootSpeed[2];
	queue<string> levelQueue;
public:
    options(){
        this->saved = false;
    }
    void defaults(){
        std::cout << "Loading default options..." << std::endl;
        this->sensitivity = 10;
        this->cameraSpeed = 2;
        this->fullscreen = false;
        this->fullscreenMaxSize = false;
        this->fullscreenWidth = 1080;
        this->fullscreenHeight = 1920;
        this->windowedWidth = 600;
        this->windowedHeight = 800;
		this->useAmbient = false;
        this->saved = false;
        this->shootSpeed[0] = 5;
        this->shootSpeed[1] = 10;
		this->audioSuccess = false;
    }
    bool save(){
        std::cout << "Saving options to " << this->path << std::endl;
        this->saved = true;
        std::cout << "Saved options" << std::endl;
        return saved;
    }
    bool load(){
        FILE * file = fopen(this->path.c_str(), "r");
    	if( file == NULL ){
    		this->defaults();
    		return true;
    	}
        std::cout << "Loading options from " << this->path << std::endl;
        char optName[1024];
        int res = fscanf(file, "%s", optName);
        int shootNext = 0;
        while(res != EOF){
            if (strcmp(optName, "level") == 0 ){
                char level[1024];
                fscanf(file, "%s\n", level);
                levelQueue.push("data/levels/"+string(level));
    		}
            else{
                GLfloat value;
                fscanf(file, "%f\n", &value);
                std::cout << "option " << optName << "\t= " << value<< std::endl;
                if (strcmp(optName, "sensitivity") == 0 ){
                    this->sensitivity = value;
                }else if (strcmp(optName, "speed.camera") == 0 ){
                    this->cameraSpeed = value;
                }else if (strcmp(optName, "speed.shoot") == 0 ){
                    this->shootSpeed[shootNext++] = value;
                }else if (strcmp(optName, "fullscreen") == 0 ){
                    this->fullscreen = value;
                }else if (strcmp(optName, "fullscreen.maxSize") == 0 ){
                    this->fullscreenMaxSize = value;
                }else if (strcmp(optName, "fullscreen.width") == 0 ){
                    this->fullscreenWidth = value;
                }else if (strcmp(optName, "fullscreen.height") == 0 ){
                    this->fullscreenHeight = value;
        		}else if (strcmp(optName, "windowed.width") == 0 ){
                    this->windowedWidth = value;
        		}else if (strcmp(optName, "windowed.height") == 0 ){
                    this->windowedHeight = value;
        		}else if (strcmp(optName, "ambient") == 0 ){
                    this->useAmbient = value;
        		}else if (strcmp(optName, "audio.success") == 0 ){
                    this->audioSuccess = value;
                }
            }
            res = fscanf(file, "%s", optName);
        }
        this->saved = true;
        std::cout << "Loaded options" << std::endl;
        return saved;
    }
    void setFullscreen(bool value){ this->fullscreen = value; this->saved=false;}
    void setFullscreenMaxSize(bool value){ this->fullscreenMaxSize = value; this->saved=false;}
    void setFullscreenWidth(bool value){ this->fullscreenWidth = value; this->saved=false;}
    void setFullscreenHeight(bool value){ this->fullscreenHeight = value; this->saved=false;}
    void setWindowedWidth(bool value){ this->windowedWidth = value; this->saved=false;}
    void setWindowedHeight(bool value){ this->windowedHeight = value; this->saved=false;}
    void setUseAmbientLight(bool value){ this->useAmbient = value; this->saved=false;}
    bool isSaved(){ return this->saved;}
    bool isFullscreen(){ return this->fullscreen;}
    bool isFullscreenMaxSize(){ return this->fullscreenMaxSize;}
    bool useAmbientLight(){ return this->useAmbient;}
    int getMouseSensitivity(){ return this->sensitivity;}
    int getCameraSpeed(){ return this->cameraSpeed;}
    int getShootSpeed(int idx=0){ return this->shootSpeed[idx];}
    int getFullscreenWidth(){ return this->fullscreenWidth;}
    int getFullscreenHeight(){ return this->fullscreenHeight;}
    int getWindowedWidth(){ return this->windowedWidth;}
    int getWindowedHeight(){ return this->windowedHeight;}
    bool playSuccessAudio(){ return this->audioSuccess;}
    bool hasNextLevel(){ return levelQueue.size() > 0;}
    string nextLevel(){
        string level = levelQueue.front();
        levelQueue.pop();
        return level;
    }
};
#endif
