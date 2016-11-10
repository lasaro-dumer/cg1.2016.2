#include <GLee.h>
#include "guides.hpp"

// Function to draw a grid of lines
void drawGround()
{
    GLfloat extent      = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
    GLfloat stepSize    = 20.0f;  // The size of the separation between points
    GLfloat groundLevel = -100.0f;   // Where on the Y-Axis the ground is drawn
    // Set colour to white
    glColor3ub(255, 255, 255);
    // Draw our ground grid
    glBegin(GL_LINES);
    for (GLint loop = -extent; loop < extent; loop += stepSize)
    {
        // Draw lines along Z-Axis
        glVertex3f(loop, groundLevel,  extent);
        glVertex3f(loop, groundLevel, -extent);
        // Draw lines across X-Axis
        glVertex3f(-extent, groundLevel, loop);
        glVertex3f(extent,  groundLevel, loop);
    }
    glEnd();
}

void draw2DAxis(GLfloat lineLength) {
    glBegin(GL_LINES);
        //Red positive X-Axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0,0);
        glVertex2f(lineLength,0);
        for (GLfloat i = 0; i > -lineLength; i=i-0.20f) {
            glVertex2f(i,0);
            glVertex2f(i-0.10f,0);
        }
        //Blue positive Y-Axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0,0);
        glVertex2f(0,lineLength);
		for (GLfloat i = 0; i > -lineLength; i=i-0.20f) {
            glVertex2f(0,i);
            glVertex2f(0,i-0.10f);
        }
    glEnd();
}

void draw3DAxis(GLfloat lineLength) {
    glBegin(GL_LINES);
        //Red positive X-Axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0,0,0);
        glVertex3f(lineLength,0,0);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(i,0,0);
            glVertex3f(i-2.5f,0,0);
        }
        //Blue positive Y-Axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0,0,0);
        glVertex3f(0,lineLength,0);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(0,i,0);
            glVertex3f(0,i-2.5f,0);
        }
        //Green positive Z-Axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0,0,0);
        glVertex3f(0,0,lineLength);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(0,0,i);
            glVertex3f(0,0,i-2.5f);
        }
    glEnd();
}

void drawCheesGrid(GLfloat TAM,GLfloat D,GLfloat Y)
{
	bool flagx, flagz;
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	flagx = false;
	for(float x=-TAM; x<TAM; x+=D)
	{
		if(flagx) flagz = false;
		else flagz = true;
		for (float z=-TAM;z<TAM;z+=D)
		{
			if(flagz)
				glColor3f(0.4,0.4,0.4);
			else
				glColor3f(1,1,1);
			glVertex3f(x,Y,z+D);
            glVertex3f(x+D,Y,z+D);
            glVertex3f(x+D,Y,z);
            glVertex3f(x,Y,z);
			flagz = !flagz;
		}
		flagx = !flagx;
	}
	glEnd();
}
