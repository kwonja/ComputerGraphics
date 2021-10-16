#include <GL/glut.h>

void MyDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	glTranslatef(3.5, 0.0, 0.0);
	glutSolidTeapot(1.0);

	glColor3f(1.0, 0.0, 1.0);
	glLoadIdentity();
	glTranslatef(6.0, 3.0, 1.0);
	glScalef(2.0, 2.0, 2.0);
	glutSolidTorus(0.3, 0.5, 20, 20);

	glColor3f(0.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(0.0, 6.0, 1.0);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	glScalef(1.0, 1.0, -1.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glutSolidTorus(0.5, 2.0, 20, 20);


	glFlush();
	//push pop이 아닌 항등행렬로 바꿔주어도 괜찮다.
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.5 * WidthFactor, 10.0 * WidthFactor, -2.5 * HeightFactor, 10.0 * HeightFactor, -10.0, 10.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Matrix Stack");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}