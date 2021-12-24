/***********************************************************************/
/*                           HW#4 :   ������ �𵨸�                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 15��    */
/*                                                                                                 */
/* ���� ���� :  ���� Can Robot �𵨸�                                            */
/*                - - - - - - -                                                                   */
/* ��� :   <�Ӹ� �����̱�>
			<������ �����̱�>			<������ �����̱�>			<�����ٸ� �����̱�>
			<���ʴٸ� �����̱�>
			�̿� ���� �޴� ����->�ش� �޴��� �´� ��ü�� �ѹ� �������ٰ� ���� �ڼ��� ���ƿ�
			�߰������� s�� ������ �����̴� ��ü�� ����
			���� ���ÿ� ����ϰ� �Ϸ��� ������, �������� �ݿ��̾ȵǼ� ����� ������ ����																			*/
								  /*                - - - - - - -                                                                   */
								  /***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
GLUquadricObj *qobj = gluNewQuadric();        //�Ǹ����� �����ϱ����ؼ� ��ü ����





int headcount = 0;
int rightarmcount = 0;
int leftarmcount = 0;
int rightlegcount = 0;
int leftlegcount = 0;
//������ ���ۿ���, ������ �����ϰ� ���� �ڸ��� ���ƿ��°��� üũ�ϱ����� ī��Ʈ

int headstart = 0;
int rightarmstart = 0;
int leftarmstart = 0;
int rightlegstart = 0;
int leftlegstart = 0;
//��ü�� �����ϰ������� ����ϴ� ���� ����->�Ӹ��� �����϶� ��,�ٸ��� �������� ��� �����ϼ��ְ� ����

int stop = 0;
//��ü�� ���ߴ� �ൿ�� �����ϴ� ����, 1�̸� ��ü�� �����.

int check = 0;
//�� ��带 üũ�ϴ� ����

//�Ӹ� ���� ���� 
float head = 0;  //����
int headangle = 1;   //������ �������ִ� ����

//������ ���� ����
float rightarm = -30; //����Ʈ��
int rightarmangle = -1;

//���� ���� ����
float leftarm = 30;
int leftarmangle = 1;

//�����ٸ� ���� ����
float rightleg = 0;
int rightlegangle = -1;

//�޴ٸ� ���� ����
float leftleg = 0.0;
int leftlegangle = 1;

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}

//display callback �Լ� ����
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluQuadricDrawStyle(qobj, GLU_LINE); //��ü�� ������ �׸���.
	glMatrixMode(GL_MODELVIEW); //�𵨺� ��� �� �ޱ� ���� ����
	glLoadIdentity();             //�׵���ķ� �ʱ�ȭ
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0); //�Ǹ����� �� ���̰��ϱ����ؼ� ����
	//��ü���� ���� ����

	glTranslatef(0.0, 0.0, 1.2); //�Ӹ��� ���� ����κ�
		//�Ӹ��� ���� ȸ���ؾߵǱ⶧���� �̵��� ��ü �����κп� push pop�� ����
		glPushMatrix();
		glRotatef((GLfloat)head,0,1,0);
		glColor3f(255.0, 255.0, 0);
		gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //�Ӹ�
		gluQuadricDrawStyle(qobj, GLU_FILL); //���� ���� �ƴ� ���� ä������ϱ⶧���� ����

		//������ ��
		glPushMatrix();
		glTranslatef(0.15, 0.0, 0.4);
		glColor3f(255, 255, 255);
		glRotatef(90, 1.0, 0.0, 0.0); //��ũ�� �� ���̰��ϱ����ؼ� ����
		gluDisk(qobj, 0.05, 0.1, 20, 3);
		glPopMatrix();

		//���� ��
		glPushMatrix();
		glTranslatef(-0.15, 0.0, 0.4);
		glColor3f(255, 255, 255);
		glRotatef(90, 1.0, 0.0, 0.0); //��ũ�� �� ���̰��ϱ����ؼ� ����
		gluDisk(qobj, 0.05, 0.1, 20, 3);
		glPopMatrix();
		gluQuadricDrawStyle(qobj, GLU_LINE); //���� ������ �ٽ� ������ �ٲ۴�.

		glPopMatrix(); //�Ӹ��� ���� �̾��� ����� pop -> �׷��� ������ ���ƿ´�.
					  //�� �κ��� �Ӹ���� �ȿ� �ִ� ������ �Ӹ��� �����̸� ���� ���� �����̱⶧��


	glTranslatef(0.0, 0.0,-0.2); //��� ���� ����κ�
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.2, 0.2, 0.2, 20, 8); //�� ����

	glTranslatef(0.0, 0.0, -1.2); //��Ʒ� �����̶� �̾��� �ִ� �κ����� �̵�
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.8, 0.8, 1.2, 20, 8); //���� ���� ���� msd�� ���� ���� �Ʒ��� �߽ɿ� ��ġ���ִ�.


	//������ ��
	glPushMatrix();
	glTranslatef(0.8, 0.0, 1.1);
	glRotatef(rightarm, 0.0, 1.0, 0.0); //��� ����
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(0, 255, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(60, 0.0, 1.0, 0.0); //�Ȳ�ġ ����
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(255, 255, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	//��
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//���� ��ǥ�� �ٽ� ���ƿ�

	//���� ��
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 1.1);
	glRotatef(leftarm, 0.0, 1.0, 0.0); //��� ����
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(0, 255, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(-60, 0.0, 1.0, 0.0); //�Ȳ�ġ ����
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(255.0, 255.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	//��
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//���� ��ǥ�� �ٽ� ���ƿ�

	//���� �ٸ�
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(leftleg, 0.0, 1.0, 0.0); //���� �ٸ� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(255, 0, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(255.0, 255.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(-0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();


	//������ �ٸ� ����
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef(rightleg, 0.0, 1.0, 0.0);  //������ �ٸ� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(255, 0, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(255.0, 255.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers(); //���ҹ��۸� ���� front frame�� back frame�� �ٲ��ش�(���� ���۸��� ���� �������� ����)
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//�� �޴� �ݹ� �Լ� ����
void MyMainMenu(int value)
{
	if (stop == 1)     //��ü�� ���߰� �Ǹ� stop=1 ���°� �Ǵµ� �޴��� Ŭ���ϸ� �ٽ� �����ϰ� �ϱ� ����
	{
		stop = 0;    //�ٽ� �����Ҷ� �������� Ǭ��
	}
	if (value == 1) //�Ӹ� ȸ��
	{
		check = 1;
	}
	if (value == 2) //������ �����̱�
	{
		check = 2;
	}
	if (value == 3) //���� �����̱�
	{
		check = 3;
	}
	if (value == 4)  //�����ٸ� �����̱�
	{
		check = 4;
	}
	if (value == 5)  //�޴ٸ� �����̱�
	{
		check = 5;
	}
	if (value == 6)   //����
	{
		exit(0);
	}
	glutPostRedisplay();  //���� ���������� �ٷ� ����
}
//Ű���� �ݹ� �Լ� ����
void MyKeyBoard(unsigned char key, int x, int y)
{
	switch (key)  //s�� �����ԵǸ� ��ü�� �ϴ� ���� ����
	{
	case 's':
		stop = 1;  //����ٴ� �ǹ̿��� stop=1
		break;
	case 'S':
		stop = 1;
		break;
	}
}
//idle �ݹ��Լ� ���� 
void MyIdle()
{
	if (stop == 1) //��ü�� ���⶧
	{
		//��� ����� ����
		headstart = 0;
		rightarmstart = 0;
		leftarmstart = 0;
		rightlegstart = 0;
		leftlegstart = 0;
	}
	else if (check == 1) //ù��° �޴��� Ŭ���ϸ�
	{
		headstart = 1;  //�Ӹ�ȸ���� ����
	}
	else if (check == 2) //�ι�° �޴��� Ŭ���ϸ�
	{
		rightarmstart = 1; //������ ȸ�� ����
	}
	else if (check == 3)  //����° �޴��� Ŭ���ϸ�
	{
		leftarmstart = 1; //���� ȸ�� ����
	}
	else if (check == 4)  //�׹�° �޴��� Ŭ���ϸ�
	{
		rightlegstart = 1; //�����ٸ� ȸ�� ����
	}
	else if (check == 5)  //�ټ���° �޴��� Ŭ���ϸ�
	{
		leftlegstart = 1;  //���� �ٸ� ȸ�� ����
	}

	if (headstart == 1) //�Ӹ�ȸ�� ����
	{
		//�Ӹ��� �¿�� ȸ���ϰ� �ٽ� �����·� ���ƿ;��ϴµ�,
		//count�� ��,�츦 �ѹ��� ���ְ�, ���ƿ��鼭 head�� 0�̻��̸� �����ش�.
		if (headcount == 2 && head>0)
		{
			check = 0;
			headstart = 0;
			headcount = 0;
		}
		else if (head < -40)
		{
			headangle = 1;
			headcount++;
		}
		else if (head > 40)
		{
			headangle = -1;
			headcount++;
		}
		if (headangle == 1)
		{
			head = head + 0.1;
		}
		else
			head = head - 0.1;
	}
	if (rightarmstart == 1) //������ ȸ�� ����
	{
		//count�� ��,�츦 �ѹ��� ���ְ�, ���ƿ��鼭 ���ڸ����� �����ش�.
		if(rightarmcount==2 && rightarm<-30)
		{
			rightarmcount = 0;
			rightarmstart = 0;
			check = 0;
		}
		else if (rightarm > -10)
		{
			rightarmangle= -1;
			rightarmcount++;
		}
		else if(rightarm < -75)
		{
			rightarmangle = 1;
			rightarmcount++;
		}
		if (rightarmangle == 1)
		{
			rightarm = rightarm + 0.1;
		}
		else
			rightarm =rightarm - 0.1;
	}
	if (leftarmstart == 1) //���� ȸ�� ����
	{
		//count�� ��,�츦 �ѹ��� ���ְ�, ���ƿ��鼭 ���ڸ����� �����ش�.
		if(leftarmcount==2 && leftarm>30)
		{
			leftarmcount = 0;
			leftarmstart = 0;
			check = 0;
		}
		else if (leftarm < 10)
		{
			leftarmangle = 1;
			leftarmcount++;
		}
		else if (leftarm > 75)
		{
			leftarmangle = -1;
			leftarmcount++;
		}
		if (leftarmangle == 1)
		{
			leftarm = leftarm + 0.1;
		}
		else
			leftarm = leftarm - 0.1;
	}
	if (rightlegstart == 1) //�����ٸ� ȸ��
	{
		if (rightleg > 0)
		{
			rightlegangle = -1;
			rightlegcount++;
			//�ٸ����� ���� ���ٰ� ���� ���̶� ������ �ٲ�� �ٷ� �����ش�.
			if (rightlegcount == 2)
			{
				rightlegcount = 0;
				rightlegstart = 0;
				check = 0;
			}
		}
		else if (rightleg < -30)
		{
			rightlegangle = 1;
			rightlegcount++;
		}
		if (rightlegangle == 1)
		{
			rightleg = rightleg + 0.1;
		}
		else
			rightleg = rightleg - 0.1;
	}
	if (leftlegstart == 1)  //���ʴٸ� ȸ��
	{
		if (leftleg < 0)
		{
			leftlegangle = 1;
			leftlegcount++;
			//�ٸ����� ���� ���ٰ� ���� ���̶� ������ �ٲ�� �ٷ� �����ش�.
			if (leftlegcount == 2)
			{
				leftlegcount = 0;
				leftlegstart = 0;
				check = 0;
			}
		}
		else if (leftleg > 30)
		{
			leftlegangle = -1;
			leftlegcount++;
		}
		if (leftlegangle == 1)
		{
			leftleg = leftleg + 0.1;
		}
		else
			leftleg = leftleg - 0.1;
	}
	glutPostRedisplay(); //���� ��������� �ٷ� ȭ�鿡 �����Ѵ�.
}
//�ָ޴��� ���� ������ �ʹ� ���Ƽ� MyMenu()�Լ��� ���� ����
void MyMenu()
{
	//�ָ޴��� ���� �޴� �ݹ��Լ� ���
	//�ָ޴��� 5���̹Ƿ� 5���� ������� ���� ,�߰������� �����ư �߰�
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	//�ָ޴������� �޴� ����
	glutAddMenuEntry("Head Move", 1);
	glutAddMenuEntry("RightArm Move", 2);
	glutAddMenuEntry("LeftArm Move", 3);
	glutAddMenuEntry("RightLeg Move", 4);
	glutAddMenuEntry("LeftLeg Move", 5);
	glutAddMenuEntry("Exit", 6);                   //Exit�� Ŭ���ϸ� value�� 6�� �ָ޴��ݹ��Լ��� ������
	glutAttachMenu(GLUT_RIGHT_BUTTON);              //���콺 �������� Ŭ���ϸ� �˾�â�� �߰��Ѵ�.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	MyMenu();
	glutDisplayFunc(MyDisplay); //display �ݹ��Լ� ���
	glutReshapeFunc(Reshape);  //reshape �ݹ��Լ� ���
	glutIdleFunc(MyIdle);       //idle �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyBoard);  //keyboard �ݹ��Լ� ���
	glutMainLoop();
	return 0;
}