#ifndef cameraH
#define cameraH
#include <GLee.h>

class camera {
private:
    GLfloat fieldOfView; // Define our field of view (i.e. how quickly foreshortening occurs)
    GLfloat near;        // The near (Z Axis) point of our viewing frustrum (default 1.0f)
    GLfloat far;         // The far  (Z Axis) point of our viewing frustrum (default 1500.0f)
    // Camera rotation
    GLfloat camXRot,camYRot,camZRot;
    // Camera position
    GLfloat camXPos,camYPos,camZPos;
    // Camera movement speed
    GLfloat camXSpeed,camYSpeed,camZSpeed;
    // Mouse sensitivity
    GLfloat vertMouseSensitivity;
    GLfloat horizMouseSensitivity;
    // Camera moving directions. to use on .move()
    bool moveForward;
    bool moveBackward;
    bool moveLeft;
    bool moveRight;
    // Speed
    GLfloat speedFactor;
    void calculateCameraMovement();
public:
    camera (GLfloat vertSensitivity, GLfloat horizSensitivity, GLfloat speed){
        this->fieldOfView = 45.0f;
        this->near        = 1.0f;
        this->far         = 1500.0f;

        this->camXRot = 0.0f;
        this->camYRot = 0.0f;
        this->camZRot = 0.0f;

        this->camXPos = 0.0f;
        this->camYPos = 0.0f;
        this->camZPos = 0.0f;

        this->camXSpeed = 0.0f;
        this->camYSpeed = 0.0f;
        this->camZSpeed = 0.0f;

        this->vertMouseSensitivity = vertSensitivity;
        this->horizMouseSensitivity = horizSensitivity;

        this->moveForward = false;
        this->moveBackward = false;
        this->moveLeft = false;
        this->moveRight = false;

        this->speedFactor = speed;
    }
    virtual ~camera ();
    void setPerspective(GLint windowHeight,GLint windowWidth);
    void rotate(int vertMovement,int horizMovement);
    void move();
    void draw();
    void updateMovements(bool forward,bool backward,bool left, bool right);
    void setMoveForward(bool mForward){ this->moveForward = mForward; }
    void setMoveBackward(bool mBackward){ this->moveBackward = mBackward; }
    void setMoveLeft(bool mLeft){ this->moveLeft = mLeft; }
    void setMoveRight(bool mRight){ this->moveRight = mRight; }
};

#endif
