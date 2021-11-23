#include <stdlib.h>
#include <GL/glut.h>

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(1.0, 1.5, 5.0);
	glutWireTeapot(1.0);
	glPopMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, -1.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glutWireTorus(0.5, 2.0, 20, 20);
	glPopMatrix();

	glutSwapBuffers();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2, 9, -2, 7, -20, 20);
	//gluPerspective(70.0, (GLfloat) w/(GLfloat) h, 0, 20);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Projection");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}