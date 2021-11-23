/***********************************************************************/
/*                           HW#3 :   ������ȯ                                        */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 11�� 6��    */
/*                                                                                                 */
/* ���� ���� :  �ڵ�7-2�� �����Ͽ� ������ ���� ����� �� �� �ִ� ���α׷�����                                            */
/*                - - - - - - -                                                                   */
/* ��� :    �ϳ��� �����츦 4���� �������� ����
             ������ ������ gluPerspective()�� �̿��� ��������, �������� glOrtho()�� �̿��� ������������ ����

			 (Ű����� ���콺�ݹ��� ����ؼ� ���� ���)
			 ���콺 ���� Ŭ���� ���� 4���� ���ҵ� ������ ȭ�鿡 ���� ������ȯ�� �����ϵ��� ����
		     �ȴ�������(ó��) : ���ϴ�->���� : ����
			 �ѹ� �������� : ���ϴ�->���� : ��(����)
			 �ι� �������� : �»��->���� : ��
			 ���� �������� : ����->���� : (5,5,5)���� ��������
			 ���� �߰������� ������ �Ǹ� �ٽ� ���ϴ� ȭ������ ���ư���.
			 ���콺 ��Ŭ�� : ���ϴ����� �̵�

			 ������ ȭ�� ���� ������ȯ�� �����ϴ�.
			 ���ϴ�,���ϴ�,�»���� w,a,s,d�� �̵��� ����
			 w: ������ ���� 0.1��ŭ �̵�
			 a: ������ �������� 0.1��ŭ �̵�
			 s: ������ �Ʒ��� 0.1��ŭ �̵�
			 d: ������ ���������� 0.1��ŭ �̵�
			 ������ Ȯ��/��Ұ� �����ϴ�
			 w : ��� ī�޶� ������ 0.1��ŭ ����(Ȯ��)
			 s : ��� ī�޶� ������ 0.1��ŭ ����(���)

			 ��� �������� ��ü�� �⺻������ ������ �߽ɺο� ��ġ�ϵ��� �ϰ�.
			Keyboard�� Mouse�� ������ ��쿡�� �׻� �߽ɺο� ��ġ�ϵ��� ��.
			�������� ũ�⸦ ���Ƿ� �����ϰų� Full Screen���� �����Ͽ��� ��쿡�� 
			�������� ũ�⿡ ������� ��ü�� ���°� �ְ���� �ʵ��� ��.
			 */

			 /*                - - - - - - -                                                                   */
			 /***********************************************************************/
#include <GL/glut.h>

int Width, Height;
GLfloat Widthfactor;
GLfloat Heightfactor;
//reshape�� ���� ��Ⱦ�� �����ϱ����� ������ ����

int screen = 0; //4���� ������ ���� ���� -> �ʱ⿡�� ���ϴ�
//���ϴ� ī�޶���� ����
float fcamerax = 0.3;
float fcameray =0.0;
float fcameraz = 1;
//���ϴ� ī�޶���� ����
float scamerax = -1;
float scameray = 0.5;
float scameraz = 0.0;
//�»�� ī�޶� ���� ����
float tcamerax = 0;
float tcameray = 1;
float tcameraz = 0;
//���� ī�޶� ���� ����
float rcamerax = 5;
float rcameray = 5;
float rcameraz = 5;
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//ȭ�鿡 ��� �׸������� ����
void DrawScene() {
	glColor3f(255, 0, 0);
	glPushMatrix();
	glutWireTorus(0.2, 0.5, 20, 20);
	glPopMatrix();

	glColor3f(0.3, 0.3, 0.7);
	glPushMatrix();
	glutWireTeapot(0.5);
	glPopMatrix();
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glViewport(0, 0, Width / 2, Height / 2); //���ϴ� ����
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(fcamerax, fcameray, fcameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //���ϴ� ������ ���� ����->�ʱⰪ�� ����
	DrawScene();
	glPopMatrix();

	glViewport(Width / 2, 0, Width / 2, Height / 2); //���ϴ� ����
	glPushMatrix();
	gluLookAt(scamerax, scameray, scameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //���ϴ� ������ ���� ����->�ʱⰪ�� ��(����)
	DrawScene();
	glPopMatrix();

	glViewport(0, Height / 2, Width / 2, Height / 2); //�»�� ����
	glPushMatrix();
	gluLookAt(tcamerax, tcameray, tcameraz, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0); //�»�� ������ ���� ����->�ʱⰪ�� ��
	DrawScene();
	glPopMatrix();

	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);             //���� ����
	glMatrixMode(GL_PROJECTION); //������ļ���
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(20,(Widthfactor/Heightfactor), 3.0, 50.0); //������ĵ� ��Ⱦ�� ����

	//������ ��������� �����ϰ�, �ٽ� �𵨺� ��ķ� ���ƿ����� ������ ������Ѵ�
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(rcamerax, rcameray, rcameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //���� ������ ���� ����->�ʱⰪ��(5,5,5)���� �ٶ󺻴�
	DrawScene();
	glPopMatrix();

	glMatrixMode(GL_PROJECTION); //��������� ���� pop�ϱ����ؼ� ����
	glPopMatrix();

	glutSwapBuffers(); //���������� �������ؼ� ������ۼ���
}
//�ְ������� �������� reshape�ݹ��Լ� ����
void MyReshape(int w, int h) {

	Width = w;
	Height = h;
	Widthfactor = (GLfloat)Width / (GLfloat)500; //���� ȭ�鿡 ���� ���� ����
	Heightfactor = (GLfloat)Height / (GLfloat)500; //���� ȭ�鿡 ���� ���� ����
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0*Widthfactor, 1.0*Widthfactor, -1.0*Heightfactor, 1.0*Heightfactor, 0.5, 5.0); //��Ⱦ�� ��ġ��Ų��.
}
//Ű�����ݹ��Լ� ����
void MyKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//������ ���ϴ�,���ϴ�,�»���� ��쿡�� ������ �������� �̵�
	case 'a':
	case 'A':
		if (screen == 0)
		{
			fcamerax = fcamerax - 0.1;
		}
		if (screen == 1)
		{
			scameraz = scameraz - 0.1;
		}
		if (screen == 2)
		{
			tcameraz = tcameraz - 0.1;
		}
		break;
		//������ ���ϴ�,���ϴ�,�»���� ��쿡�� ������ ���� �̵�
		//������ ������ ���� ��ü���� ī�޶� ������ Ȯ��
	case 'w':
	case 'W':
		if (screen == 0)
		{
			fcameray = fcameray + 0.1;
		}
		if (screen == 1)
		{
			scameray = scameray + 0.1;
		}
		if (screen == 2)
		{
			tcamerax = tcamerax + 0.1;
		}
		if (screen == 3)
		{
			rcamerax = rcamerax - 0.1;
			rcameray = rcameray - 0.1;
			rcameraz = rcameraz - 0.1;
		}
		break;
		//������ ���ϴ�,���ϴ�,�»���� ��쿡�� ������ �Ʒ��� �̵�
		//������ ������ ���� ��ü���� ī�޶� ������ ���
	case 's':
	case 'S':
		if (screen == 0)
		{
			fcameray = fcameray - 0.1;
		}
		if (screen == 1)
		{
			scameray = scameray - 0.1;
		}
		if (screen == 2)
		{
			tcamerax = tcamerax - 0.1;
		}
		if (screen == 3)
		{
			rcamerax = rcamerax + 0.1;
			rcameray = rcameray + 0.1;
			rcameraz = rcameraz + 0.1;
		}
		break;
		//������ ���ϴ�,���ϴ�,�»���� ��쿡�� ������ ���������� �̵�
	case 'd':
	case 'D':
		if (screen == 0)
		{
			fcamerax = fcamerax + 0.1;
		}
		if (screen == 1)
		{
			scameraz = scameraz + 0.1;
		}
		if (screen == 2)
		{
			tcameraz = tcameraz + 0.1;
		}
		break;
	}
	glutPostRedisplay(); //������ȯ�� ���� ��ȭ�� �ٷ� �����ֱ����ؼ� display�� ������ ����
}
//���콺 �ݹ��Լ� ����
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //���콺 ���� Ŭ���� �����ٸ�
	{
		screen++;  //������ġ�� ����
		screen = screen % 4; //�� 4���� �����̶� 0,1,2,3���� ǥ��
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //���콺 ������ Ŭ���� �����ٸ�
	{
		screen = 0; //������ȯ�� �Ҽ� �ִ� ����� ���ϴ� �������� �̵�
	}
}
int main(int argc, char** argv) {
	Width = 500;
	Height = 500;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Viewpory Partition");
	MyInit();
	glutDisplayFunc(MyDisplay); //���÷��� �ݹ��Լ� ���
	glutReshapeFunc(MyReshape);  //reshape �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyBoard);  //Ű���� �ݹ��Լ� ���
	glutMouseFunc(MyMouseClick);  //���콺 �ݹ��Լ� ���
	glutMainLoop();
	return 0;
}