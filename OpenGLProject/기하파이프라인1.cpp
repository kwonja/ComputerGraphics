#include <GL/glut.h>

void MyDisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	//glRotatef(30.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(1.0, 1.5, 1.0);
	//������ �� �������� ����.
	//glScalef(1.0, 1.5, 1.0);
	glutSolidTeapot(0.5);
	glPopMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(1.0, 1.5, 1.0);
	glTranslatef(0.0, 1.0, 0.0);
	//glRotatef(30.0, 0.0, 0.0, 1.0);
	glutSolidTeapot(0.5);

	//��ȯ��Ģ�� ������ ���ϴ°��� �˼� �ִ�.
	//->��� �޶����µ� ���� �˾ƾ� �ϳ�?
	glFlush();
}

void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)500;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)500;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.5 * WidthFactor, 2.5 * WidthFactor, -2.5 * HeightFactor, 2.5 * HeightFactor, -10.0, 10.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Modleing Transform");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}