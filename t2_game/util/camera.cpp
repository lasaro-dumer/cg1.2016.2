#include <GLee.h>
#include <math.h>
#include "camera.hpp"
#include "smmath.hpp"
#include "../elements/point3D.hpp"

void camera::setPerspective(GLint windowHeight,GLint windowWidth){
    // Change to the projection matrix, reset the matrix and set up our projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspectRatio = (windowWidth > windowHeight)? float(windowWidth)/float(windowHeight) : float(windowHeight)/float(windowWidth);
    GLfloat fH = tan( float(fieldOfView / 360.0f * 3.14159f) ) * near;
    GLfloat fW = fH * aspectRatio;
    glFrustum(-fW, fW, -fH, fH, near, far);
}

point3D* camera::getCurrentPosition(){
    return new point3D(this->camXPos,this->camYPos,this->camZPos,this->camXRot,this->camYRot,this->camZRot);
}

void camera::rotate(double vertMovement,double horizMovement){
    this->camXRot += vertMovement / this->sensitivity;
    this->camYRot += horizMovement / this->sensitivity;

    // Control looking up and down with the mouse forward/back movement
    // Limit loking up to vertically up
    if (this->camXRot < -90.0f)
        this->camXRot = -90.0f;
    // Limit looking down to vertically down
    if (this->camXRot > 90.0f)
        this->camXRot = 90.0f;
    // Looking left and right. Keep the angles in the range -180.0f (anticlockwise turn looking behind) to 180.0f (clockwise turn looking behind)
    if (this->camYRot < -180.0f)
        this->camYRot += 360.0f;
    if (this->camYRot > 180.0f)
        this->camYRot -= 360.0f;
}

void camera::draw() {
    // Move the camera to our location in space
    glRotatef(this->camXRot, 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glRotatef(this->camYRot, 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    glTranslatef(-this->camXPos,-this->camYPos,-this->camZPos);    // Translate the modelviewm matrix to the position of our camera
}
void camera::updateMovements(bool forward,bool backward,bool left, bool right){
    this->moveForward = forward;
    this->moveBackward = backward;
    this->moveLeft = left;
    this->moveRight = right;
}
// Function to calculate which direction we need to move the camera and by what amount
void camera::calculateCameraMovement()
{
    // Break up our movement into components along the X, Y and Z axis
    float camMovementXComponent = 0.0f;
    float camMovementYComponent = 0.0f;
    float camMovementZComponent = 0.0f;

    if (this->moveForward)
    {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(this->camXRot));
        camMovementXComponent += ( this->speedFactor * float(sin(toRads(this->camYRot))) ) * pitchFactor;
        // Control Y-Axis movement
        camMovementYComponent += this->speedFactor * float(sin(toRads(this->camXRot))) * -1.0f;
        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(this->camXRot)));
        camMovementZComponent += ( this->speedFactor * float(cos(toRads(this->camYRot))) * -1.0f ) * yawFactor;
    }

    if (this->moveBackward)
    {
        // Control X-Axis movement
        float pitchFactor = cos(toRads(this->camXRot));
        camMovementXComponent += ( this->speedFactor * float(sin(toRads(this->camYRot))) * -1.0f) * pitchFactor;
        // Control Y-Axis movement
        camMovementYComponent += this->speedFactor * float(sin(toRads(this->camXRot)));
        // Control Z-Axis movement
        float yawFactor = float(cos(toRads(this->camXRot)));
        camMovementZComponent += ( this->speedFactor * float(cos(toRads(this->camYRot))) ) * yawFactor;
    }

    if (this->moveLeft)
    {
        // Calculate our Y-Axis rotation in radians once here because we use it twice
        float yRotRad = toRads(this->camYRot);
        camMovementXComponent += -this->speedFactor * float(cos(yRotRad));
        camMovementZComponent += -this->speedFactor * float(sin(yRotRad));
    }

    if (this->moveRight)
    {
        // Calculate our Y-Axis rotation in radians once here because we use it twice
        float yRotRad = toRads(this->camYRot);
        camMovementXComponent += this->speedFactor * float(cos(yRotRad));
        camMovementZComponent += this->speedFactor * float(sin(yRotRad));
    }

    if(this->moveUp)
    {
        float zRotRad = toRads(this->camZRot);
        camMovementYComponent += this->speedFactor * float(cos(zRotRad));
    }

    if(this->moveDown)
    {
        float zRotRad = toRads(this->camZRot);
        camMovementYComponent += this->speedFactor * float(cos(zRotRad)) * -1.0f;
    }
    // After combining our movements for any & all keys pressed, assign them to our camera speed along the given axis
    this->camXSpeed = camMovementXComponent;
    this->camYSpeed = camMovementYComponent;
    this->camZSpeed = camMovementZComponent;
    // Cap the speeds to our movementSpeedFactor (otherwise going forward and strafing at an angle is twice as fast as just going forward!)
    // X Speed cap
    if (this->camXSpeed > this->speedFactor)
        this->camXSpeed = this->speedFactor;
    if (this->camXSpeed < -this->speedFactor)
        this->camXSpeed = -this->speedFactor;
    // Y Speed cap
    if (this->camYSpeed > this->speedFactor)
        this->camYSpeed = this->speedFactor;
    if (this->camYSpeed < -this->speedFactor)
        this->camYSpeed = -this->speedFactor;
    // Z Speed cap
    if (this->camZSpeed > this->speedFactor)
        this->camZSpeed = this->speedFactor;
    if (this->camZSpeed < -this->speedFactor)
        this->camZSpeed = -this->speedFactor;
}

bool camera::collide(asteroid* a){
    point3D* ac = a->getPosition();//getModel()->center;
    // point3D* c = this->position;//oModel->center;
    GLfloat xd = pow((this->camXPos+this->camXSpeed) - ac->getX(),2);
    GLfloat yd = pow((this->camYPos+this->camYSpeed) - ac->getY(),2);
    GLfloat zd = pow((this->camZPos+this->camZSpeed) - ac->getZ(),2);
    //d = sq (xb-xa)^2 + (yb-ya)^2
    GLfloat d = sqrt(xd+yd+zd);
    GLfloat hitD = a->getRadius();
    //std::cout << "d: " << d << " hitD: " << hitD << std::endl;
    return (d < hitD);
}

// Function to move the camera the amount we've calculated in the calculateCameraMovement function
void camera::move(list<asteroid*> asteroids)
{
    bool canMove = true;
    // list<asteroid*>::iterator ia;
    // for (ia = asteroids.begin(); (ia != asteroids.end() && canMove); ++ia)
    //     if((*ia)->isAlive())
    //         if(this->collide((*ia)))
    //             canMove = false;

    if(canMove){
        // Calculate our camera movement
        this->calculateCameraMovement();
        this->camXPos += this->camXSpeed;
        this->camYPos += this->camYSpeed;
        this->camZPos += this->camZSpeed;
    }
}

camera::~camera(){

}
