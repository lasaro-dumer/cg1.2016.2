#include <stdio.h>
#include <GLee.h>
#include <GL/glut.h>
#include <SOIL.h>

GLuint loadTex() {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	//...
	// Load and generate the texture
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

int main(int argc, char *argv[]) {

    //create GL context
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("windowname");

    GLfloat zoom = 1.5f;
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    gluOrtho2D(-zoom * (800/600), zoom * (800/600), -zoom, zoom);

	GLuint tex = loadTex();
    //clear and draw quad with texture (could be in display callback)
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2i(0, 0);
    glTexCoord2f(0, 1); glVertex2i(0, 1);
    glTexCoord2f(1, 1); glVertex2i(1, 1);
    glTexCoord2f(1, 0); glVertex2i(1, 0);


    glTexCoord2f(0, 0); glVertex2i(0, 0);
    glTexCoord2f(0, 0.5f); glVertex2i(0, -1);
    glTexCoord2f(0.5f, 0.5f); glVertex2i(-1, -1);
    glTexCoord2f(0.5f, 0); glVertex2i(-1, 0);

    glTexCoord2f(0, 0); glVertex2i(0, 0);
    glTexCoord2f(0, 0.25f); glVertex2i(0, 1);
    glTexCoord2f(0.25f, 0.25f); glVertex2i(-1, 1);
    glTexCoord2f(0.25f, 0); glVertex2i(-1, 0);

    glTexCoord2f(0, 0); glVertex2i(0, 0);
    glTexCoord2f(0, 0.125f); glVertex2i(0, -1);
    glTexCoord2f(0.125f, 0.125f); glVertex2i(1, -1);
    glTexCoord2f(0.125f, 0); glVertex2i(1, 0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFlush(); //don't need this with GLUT_DOUBLE and glutSwapBuffers

    getchar(); //pause so you can see what just happened
	return 0;
}
