/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 1��    */
/*                                                                                                 */
/* ���� ���� :  ���콺�ݹ��� ����Ͽ� �簢�� �����̱�                     */
/*                - - - - - - -                                                                   */
/* ��� :    ���콺 ������ Ŭ���ϸ� �簢���� ���������� �����̰�, ��Ŭ�����ϸ� �����.
               �̶�, ��������� �簢���� ������â �ٱ����� �ȳ������� �������־���.
			     �����̴°��� �� �ߺ������ؼ� 0.00001��ŭ �����̵��� �������־���.                * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//���콺 ��/�� Ŭ���� �����ϱ����� ����
int check = 0;
//�簢���� ó�� ��ǥ�� ���������� ����
double x1 = -0.5;
double x2 = 0.5;
double y1 = -0.5;
double y2 = 0.5;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();
	glFlush();
}
//Idle �ݹ��Լ� ����
//�ƹ� EVENT�� �߻����� ������ ����ȴ�.
void MyIdle()
{
	//���� Ŭ���� �������� MyIdle �ȿ� ������  ����ǵ��� ����(�����̵���)
	if (check == 1) //���� Ŭ���� �ߴٸ�
	{
		//��輱�� ������ �����
		if (x2 > 1.0)
		{
			return;
		}
		//��輱�� ������ �ƴ϶�� ���������� �̵��Ѵ�.
		x1 += 0.00001;
		x2 += 0.00001;
		glutPostRedisplay(); //���� ������׵��� �ٷ� ���÷��̿� ����ǵ��� ������������ش�.
	}
}
//���콺 �ݹ��Լ� ����
//���콺 Ŭ�������� EVENT�� �޴´�
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //���콺 ���� Ŭ���� �����ٸ�
	{
		check = 1;                                         //�̵��Ҽ� �ֵ��� 1����
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //���콺 ������ Ŭ���� �����ٸ�
	{
		check = 0;                                        //����ٸ� 0����
	}
}
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Keyboard Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);   //display �ݹ��Լ� ���
	glutMouseFunc(MyMouseClick);  //���콺 Ŭ�� �ݹ��Լ� ���
	glutIdleFunc(MyIdle);   //idle�ݹ��Լ� ���
	glutMainLoop();
	return 0;
}