#include <GL/glut.h>  //�������
void MyDisplay() {
	glClearColor(0.259, 0.259, 0.453, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//����ǥ
	glBegin(GL_POLYGON); // GL_POINTS, GL_POLYGON ��

	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.8, 0.5);
	glEnd();
	glFlush();
	//gl (�׷��� ���̺귯��)
}
int main(int argc, char** argv) {
	//glut
	glutInit(&argc, argv);  //�ʱ�ȭ
	glutInitDisplayMode(GLUT_RGB); //������(rgb���)
	glutInitWindowSize(500, 500);   //������ũ��
	glutCreateWindow("My First OpenGL Code"); //�ʱ�ȭ �� ������ ����
	glutDisplayFunc(MyDisplay); //callback�Լ�
	glutMainLoop();//���ѷ����� ��� �ѳ��� ����
	return 0;
}