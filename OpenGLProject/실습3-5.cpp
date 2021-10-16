/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 1��    */
/*                                                                                                 */
/* ���� ���� :  Idle Callback �� ����Ͽ� �簢�� �����̱�                 */
/*                - - - - - - -                                                                   */
/* ��� :    ��,��,��,�� Ű���带 ������ �� �������� �簢���� �����̵��� �Ѵ�.
             Ű���带 ������������, ���� Ű���带 ������������ ��� �����δ�.
			   �̶�, ��������� �簢���� ������â �ٱ����� �ȳ������� �������־���.      
			   �簢���� �����̴°��� �� �� Ȯ���ϱ����� 0.0001�� �����̵��� �������־���             * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//�簢���� ������ �����ִ� ����
int check = 0;
//�簢���� ó�� ��ǥ�� ���������� ����
double x1 = -0.5;
double x2 = 0.5;
double y1 = -0.5;
double y2 = 0.5;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.8);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();
	glutSwapBuffers();  //���ҹ��۸� ���� front frame�� back frame�� �ٲ��ش�(���� ���۸��� ���� �������� ����)
}
//idle �ݹ��Լ� ����
//��� event�� ������ �����Ѵ�.->�̺�Ʈ�����ٸ� �ݺ�����ȴ�->���������� �����δ�.
void MyIdle() {

	//check�� 1�̸� �������� �̵��ϴµ�,
	if (check == 1)
	{
		if (x1 >= -1.0) //x1��ǥ�� ��輱�� �Ѿ�ԵǸ� if�� ������ �������ʴ´�.
		{
			x1 += -0.0001;
			x2 += -0.0001;
		}
	}
	//check�� 2�̸� �������� �̵��ϴµ�,
	else if (check == 2)
	{
		if (y2 <= 1.0) //y2��ǥ�� ��輱�� �Ѿ�ԵǸ� if�� ������ �������ʴ´�.
		{
			y1 += 0.0001;
			y2 += 0.0001;
		}
	}
	//check�� 3�̸� ���������� �̵��ϴµ�,
	else if (check == 3)
	{
		if (x2 <= 1.0) //x2��ǥ�� ��輱�� �Ѿ�ԵǸ� if�� ������ �������ʴ´�.
		{
			x1 += 0.0001;
			x2 += 0.0001;
		}
	}
	//check�� 4�̸� �Ʒ������� �̵��ϴµ�,
	else if(check==4)
	{
		if (y1 >= -1.0) //y1��ǥ�� ��輱�� �Ѿ�ԵǸ� if�� ������ �������ʴ´�.
		{
			y1 += -0.0001;
			y2 += -0.0001;
		}
	}
	glutPostRedisplay(); //���� ������׵��� �ٷ� ���÷��̿� ����ǵ��� ������������ش�.
}
//��,��,��,�츦 �Է¹��� �����Ű���� �ݹ� �Լ� ����
//��,��,��,��� int �� ���ǵǾ��־ ������ key���� �Ű������� �޴´�.
void MySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		check = 1;         //�����϶� �������� ���� ���÷��̿��� ���ȴ�.
		break;
	case GLUT_KEY_UP:
		check = 2;         //�����϶� �������� ����
		break;
	case GLUT_KEY_RIGHT:
		check = 3;           //�������϶� ���������� ����
		break;
	case GLUT_KEY_DOWN:        
		check = 4;              //�Ʒ����϶� �Ʒ������� ����
		break;
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);        //������۸��� ����ϱ����� ����->���۸� 2���� �ø���.
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Idle Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutSpecialFunc(MySpecial); //�����Ű���� �ݹ��Լ� ���
	glutIdleFunc(MyIdle);         //idle �ݹ��Լ� ���

	glutMainLoop();
	return 0;
}