#include <GL/glut.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //������â�� �ִ� �׸����۸� ����°�
	glViewport(100, 100, 300, 300);
	glColor3f(0.5, 0.5, 0.5); //�簢�� ����
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(10.0, 0.0, -30.0);
	glVertex3f(10.0, 10.0, -30.0);
	glVertex3f(0.0, 10.0, -30.0);
	glEnd();
	//glBegin ~ glEnd ��� ���̿� �پ��� �Լ����� ȣ��Ǵµ� �ַ� ������ ��ġ�ϰų� �Ӽ��� �ٲٴ� ��ɵ��̴�. ������ ���� �Լ��� �����Ѵ�. 
	//�տ��� �����Ѵ�� ��ǥ ���� �μ��� 4������ ���� �� �ְ� �μ��� Ÿ�Ե� �پ��ϴ�. 
	//���⼭�� 3���� ����Ѵ�.
	glFlush(); //�и� �۾����� �ѹ��� �����Ų��.
}
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);  //������ ����� �Ͼ������ �����
	glMatrixMode(GL_PROJECTION);        //������� ���� �ٲ۴�.
	// ������� ����
	glLoadIdentity();                    // ���� ��������� �׵���ķ� �ʱ�ȭ
	glOrtho(0.0, 40.0, 0.0, 40.0, 10.0, 50.0); //(-1,-1),(-1,-0.5),(-0.5,-0.5),(-0.5,-1)->����ȭ�� ���ú��� ������ ������ viewport�� ����.
	//->����� (0.0)�� �������� viewport ũ�⿡ ���� ������ �簢���� ��µȴ�.
	//glOrtho(0.0, 20.0, 0.0, 20.0, 10.0, 50.0);//(-1,-1),(-1,0),(0,0),(0,-1) ->����ȭ�� ���ú��� ������ ������ viewport�� ����. 
	//��ǥ ��ġ�� ���� ������ ���ؼ� �簢���� ä������.
	//glOrtho(0.0, 10.0, 0.0, 10.0, 10.0, 50.0);//(-1,-1) (-1,1), (1,1),(1,-1)->����ȭ�� ���ú��� ������ ������ viewport�� ����. 
	//�� ��� ȭ�鿡 �� ä������.
	// ��ĺ�ȯ
	//���߿� �𵨺並 �����̶�� �����ϰ� �̸� �ʱ�ȭ �صа�
	glMatrixMode(GL_MODELVIEW); 
	// �𵨺���� ����   -> viewport�� �����Ű ���ؼ� �𵨺������ �����Ѵ�.
	glLoadIdentity();
	// ���� �𵨺� ����� �׵���ķ� �ʱ�ȭ
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);

	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
