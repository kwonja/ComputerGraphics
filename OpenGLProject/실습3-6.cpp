/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 1��    */
/*                                                                                                 */
/* ���� ���� :  Timer Callback �� ����Ͽ� �簢�� �����̱�                 */
/*                - - - - - - -                                                                   */
/* ��� :     ���α׷��� ����Ǹ� �簢���� ���������� �̵��ϴٰ� ���� �ε����� ������ ������ ���������� ���ϰ�,
              �������� ���ٰ� ���� ���� �ε����� ���������� ���ƿ���, �ٽ� ���������� �̵��� �ݺ��Ѵ�.
			  �׸��� ������ Ŭ���ϸ� �����̴� ������ �����. ��Ŭ���� �ϸ� �ٽ� �����̵��� �߰��� �������־���.
			 
			   �̶�, ��������� �簢���� ������â �ٱ����� �ȳ������� �������־���.      
			   �簢���� �����̴°��� �� �� Ȯ���ϱ����� 0.01�� �����̵��� �������־���         * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>

int check = 0;             // ���콺 Ŭ�������� ������ �������ִ� ����
int move = 1;               //���� �ε��������� �������ִ� ����
//�簢���� ó�� ��ǥ�� ���������� ����
double x1 = -0.5;
double x2 = 0.5;
double y1 = -0.5;
double y2 = 0.5;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	//
	if (move == 1)        //���ʺ��� �ε����� ���������� ����
	{
		glColor3f(0.0, 0.5, 0.8);  //�������� �簢��
	}
	else if (move == 0)   //�����ʺ��� �ε����� �������� ����
	{
		glColor3f(255.0, 0.0, 0.0);   //�������� �簢��
	}
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();

	glutSwapBuffers();   //���ҹ��۸� ���� front frame�� back frame�� �ٲ��ش�(���� ���۸��� ���� �������� ����)
}
//����Ŭ�� �ݹ��Լ� ���
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)       //����Ŭ���� ������
	{
		check = 1;                                          //check=1 �������� ����
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)   //������ Ŭ��������
	{
		check = 0;                                          //check=0  �ٽÿ����̰��ϱ�
	}
}
//Ÿ�̸� �ݹ��Լ� ����
//Ÿ�̸� �ݹ��Լ��� �ѹ�����ǰ��� �ٽ� ������ �ȵǱ⶧���� ��������� ����ؾ��Ѵ�.
void MyTimer(int Value) {
	//check==0 �� �������ʰ� �۵��Ҷ�
	if (check == 0)
	{
		if (move == 0) //�������� ����������
		{
			if (x1 < -1.0) //��輱�� ������
			{
				move = 1; //���������� �̵��ϵ��� 1 ����
			}
			x1 += -0.01;
			x2 += -0.01;
		}
		if (move == 1) //���������� ����������
		{
			if (x2 > 1.0)  //��輱�� ������
			{
				move = 0; //�������� �̵��ϵ��� 0 ����
			}
			x1 += 0.01;
			x2 += 0.01;
		}
		glutPostRedisplay();     //���� ������׵��� �ٷ� ���÷��̿� ����ǵ��� ������������ش�.
		glutTimerFunc(40, MyTimer, 1); //40�Ŀ� Ÿ�̸��ݹ��Լ��� ����ǵ��� ���
	}
	else if(check==1) //�۵�����������
	{   //���������ʴ��� ��Ŭ���� �ٽ� �����̰� �Ϸ��� Ÿ�̸��ݹ��Լ��� ��� ��Ͻ��������.
		//�׷��� �ʰ�, �������� �������� Ÿ�̸� �ݹ��Լ������ ������, �ٽ� Ÿ�̸� �ݹ��Լ��� �����ų���� ����.
		//Ÿ�̸� �ݹ��Լ��� ����ϸ� �ѹ������ϰ� ����ȴ�.
		glutPostRedisplay();
		glutTimerFunc(40, MyTimer, 1);
	}
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //������۸��� ����ϱ����� ����->���۸� 2���� �ø���.
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);         //display �ݹ��Լ� ���
	glutMouseFunc(MyMouseClick);         //���콺 �ݹ��Լ� ���
	glutTimerFunc(40, MyTimer, 1);        //Ÿ�̸� �ݹ��Լ� ���

	glutMainLoop();
	return 0;
}