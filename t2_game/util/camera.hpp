#ifndef cameraH
#define cameraH
#include <GLee.h>
#include "../elements/point3D.hpp"

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
    GLfloat sensitivity;
    // Camera moving directions. to use on .move()
    bool moveForward;
    bool moveBackward;
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    // Speed
    GLfloat speedFactor;
    void calculateCameraMovement();
public:
    camera (){
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

        this->sensitivity = 10.0f;

        this->moveForward = false;
        this->moveBackward = false;
        this->moveLeft = false;
        this->moveRight = false;
        this->moveUp = false;
        this->moveDown = false;

        this->speedFactor = 3;
    }
    virtual ~camera ();
    void setMouseSensitivity(GLfloat value){ this->sensitivity = value;}
    void setSpeed(GLfloat value){ this->speedFactor = value;}
    void setPerspective(GLint windowHeight,GLint windowWidth);
    void rotate(double vertMovement,double horizMovement);
    void move();
    void draw();
    point3D* getCurrentPosition();
    void updateMovements(bool forward,bool backward,bool left, bool right);
    void setMoveForward(bool mForward){ this->moveForward = mForward; }
    void setMoveBackward(bool mBackward){ this->moveBackward = mBackward; }
    void setMoveLeft(bool mLeft){ this->moveLeft = mLeft; }
    void setMoveRight(bool mRight){ this->moveRight = mRight; }
    void setMoveUp(bool mUp){ this->moveUp = mUp; }
    void setMoveDown(bool mDown){ this->moveDown = mDown; }
};

#endif
