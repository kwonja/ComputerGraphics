#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(10.0, 0.0, -30.0);
	glVertex3f(10.0, 10.0, -30.0);
	glVertex3f(0.0, 10.0, -30.0);
	glEnd();
	glFlush();
}
//��������� ����ϰ� �Ǹ� ������ â�� ������ŭ �׸��� ���󰡼� ���ϴ� �׸��� �ְ������� ����� �ִµ�,
//ex) ������� ������ 1:1 �ε� ������â(����)������ 2:1�϶� �ְ������� �߻�
//�װ��� �����ֱ����ؼ� Reshape �Լ��� ���
void MyReshape(int NewWidth, int NewHeight) {
	//�Ű��������� os�� �˾Ƽ� �����ؼ� �־��ش�.
	glViewport(0, 0, NewWidth/2, NewHeight/2);   //�����ؼ� �־��� ũ�⸸ŭ �������� â�� ����
	//������ ũ�⿡ 1/2�� ���� �������� ���ú��ǿ� ������ ������ŭ �簢���� ��µ�
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)300;               //ó�� ũ�Ⱑ 300�̱⶧���� ������ 300���� ������ ���� ����
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)300;              //ó�� ũ�Ⱑ 300�̱⶧���� ������ 300���� ������ ���� ����
	//GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)200;   
	//GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)200;
	//200���� �� ��� ���ú��ǰ� �� Ŀ���� ȭ�鿡 ������ �簢���� �� ���� ������� �׷�����.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0*Widthfactor, 20.0*Widthfactor, 0.0* Heightfactor, 20.0*Heightfactor, 10.0, 50.0);
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	/*glMatrixMode(GL_PROJECTION);   // ������� ����
	glLoadIdentity( );  // ���� ��������� �׵���ķ� �ʱ�ȭ
	glOrtho(0.0, 20.0, 0.0, 20.0, 10.0, 50.0); // ��ĺ�ȯ

	glMatrixMode(GL_MODELVIEW);  // �𵨺���� ����
	glLoadIdentity( ); // ���� �𵨺� ����� �׵���ķ� �ʱ�ȭ*/
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Reshape");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}