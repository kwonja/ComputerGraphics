/***********************************************************************/
/*                           HW#5 :   ������ȯ                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 28��    */
/*                                                                                                 */
/* ���� ���� :  <�κ���-��>�� �����Ͽ� �پ��� �������� �𵨸��� ��ü �� ������ �� �ֵ��� ����                                            */
/*                - - - - - - -                                                                   */
/* ��� :      �Ʒ��� ���� �κ���-���� ���
			<1 Ű�� ������> ù��° �հ����� ������ ���ƴ� �ݺ�
			<2 Ű�� ������> �ι�° �հ����� ������ ���ƴ� �ݺ�
			<3 Ű�� ������> ����° �հ����� ������ ���ƴ� �ݺ�
			<4 Ű�� ������> ��� �հ����� ������ ���ƴ� �ݺ�
			<S Ű�� ������> �����̴� �հ����� �������� ����
			�߰� ���� ���
			<���콺 ���� ��ư�� Ŭ���ϸ�> ���, �Ȳ�ġ �� ��� �հ����� �������� Robot Arm�� Ư�� ������ ��� ��ó�� ȸ��
			���⼭ �ѹ��� Ŭ���ϸ� ��µ��� �����ϴ� ����� �߰��Ͽ���. �ٽ� Ŭ���ϸ� ��� ȸ���� �̾ ����
			��� �ൿ�� �ѹ��� �����ϵ��� ����
			<���콺 ������ ��ư�� Ŭ���ϸ�> �Ȳ�ġ �� ��� �հ����� �������� Robot Arm�� ������ġ�� �ڼ��� �ǵ��ư����� ��.
			������ġ�� ���ư��� ������ �ٸ���ɵ��� ���డ��
			�հ����� ������ 0~90���� �������־���.
			�Ȳ�ġ�� ������ 0~40���� �������־���.

			������� ������ȯ

			�� Ű�� ������ ī�޶��� ������ ���ΰ���.
			�� Ű�� ������ ī�޶��� ������ �Ʒ��ΰ���.
			�� Ű�� ������ ī�޶��� ������ �������� ����.
			�� Ű�� ������ ī�޶��� ������ ���������� ����.

			������ ���콺 ������ Ŭ���ϸ� �հ����� ���� �ൿ�� ���ϴµ�, �׶� ī�޶� ������ �������� �����̴ٰ� �����ൿ��
			�������� ī�޶� �̵��� �����.
			������ ���콺 �������� Ŭ���ϸ� �հ����� ��� �ൿ�� ���ϴµ�, �׶� ī�޶� ������ ���������� �����̴ٰ�
			(���� �ڸ��� �̵�) ���� �� ������ ī�޶� �̵��� �����.
		
			�� �Ʒ��� Ȯ���Ҷ� ���콺 ���� Ŭ���� ���� �հ����� ������ ������ ���� ���� Ȯ���Ҽ� �ִ�.																								*/

			 /*                - - - - - - -                                                                   */
			 /***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
//ī�޶� ������ ���� ����

GLfloat focusx = 0;
GLfloat focusy = 0;
GLfloat focusz = 0;
//������ ���� ����

GLfloat camerax = 0;
GLfloat cameray = 1.5;
GLfloat cameraz = 1.5;
//ī�޶� ��ġ�� ���� ����

int cameramoving = 0; //���� � ī�޶� ������ ��Ÿ���� ����
int cameradir = 1;   //���� � ī�޶��� �����̴� ������ ��Ÿ���� ����

int firstangle = 1;
int secondangle = 1;
int thirdangle = 1;
//�հ��� ������ ���� ����/������ �˸��� ����

float first = 0.0;
float second = 0.0;
float third=0.0;
//�� �հ����� ������ ��Ÿ���� ����, �⺻���� 0.0���� ����

int check = 0;
//�հ������� ����� ��Ÿ���� ����, �������� �������� 0�̴�.

int all = 0;
//�հ����� ��� �����϶��� ��Ÿ���� ����, �������� �������� 0�̴�.

int firststart = 0;
int secondstart = 0;
int thirdstart = 0;
//�հ����� �ѹ� �����̰ԵǸ�, ���߱� ������ ��� ���������ϴµ�, �̸� ���������ֱ� ���ؼ� ����

int jobgi = 0;
//������ ��� ����� �Ҷ� �� ���� �������ִ� ����, �������� �������� 0�̴�.

int back = 0;
//���� ��ġ�� ���ư��� ����� �Ҷ� �� ���� �������ִ� ����, �������� �������� 0�̴�.
float elbow = 0;
//��� ����� �Ҷ�, �Ȳ�ġ�� �������ߵǴµ�, �� ������ �������ִ� ����
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}
//display callback �Լ� ����
void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();   //������ ��ġ�� �����ϱ� ���ؼ� Ǫ�� -> ���⸦ �������� ����
	//�𵨺���Ŀ��� ��ü���� ���� �������� ��������ϱ⶧���� ���� ���� ����
	gluLookAt(camerax, cameray, cameraz, focusx, focusy, focusz, 0.0, 1.0, 0.0); //������ȯ
	glTranslatef(-1.5, 1.5, 0.0); // ���� ���ʺ��� �����ϱ����ؼ� �̵�
	glTranslatef(-1.0, 0.0, 0.0); //��ü ��ǥ�̵�
	glRotatef(-45, 0.0, 0.0, 1.0); //��ü ȸ��
	glTranslatef(1.0, 0.0, 0.0);	//��ü ��ǥ�̵�

	//����
	glPushMatrix();  //�𵨺���� Ǫ��
	glColor3f(1.0, 1.0, 1.0);
	glScalef(2.0, 0.4, 1.0);    //��ü ũ�� ��ȯ
	glutWireCube(1.0);
	glPopMatrix(); //�𵨺���� ��

	//�Ʒ����� ��������ؼ� ��ǥ�̵�
	glTranslatef(1.0, 0.0, 0.0);  
	glRotatef(45, 0.0, 0.0, 1.0); // ������ �ø��� ���ؼ� -45���� ����⶧���� 0�� ����� ���ؼ� +45�� ������
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); //�Ȳ�ġ ���� �ִ� 40�� ������ ����
	glTranslatef(1.0, 0.0, 0.0);

	//�Ʒ���
	glPushMatrix();	//�𵨺� ��� Ǫ��
	glColor3f(1.0, 1.0, 1.0);
	glScalef(2.0, 0.4, 1.0); //��ü ũ�� ��ȯ
	glutWireCube(1.0);  //����
	glPopMatrix(); //�𵨺� ��� ��


	//�Ʒ��Ȱ� ����Ǵ� �հ��� ����

	//��� �հ���
		glPushMatrix(); //���⼭ Ǫ�ø� �ؾ� ��� �հ����� ����� �ٽ� �Ʒ��ȷ� ���ƿ�
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)second,0.0, 0.0, 1.0); //1��° ����
			glTranslatef(0.3 ,0.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);

				//�հ�������
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)second, 0.0, 0.0, 1.0); //2��° ����
			glTranslatef(0.3, 0.0, 0.0);
				
			    //�հ�������
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)second, 0.0, 0.0, 1.0); //3��°����
			glTranslatef(0.3, 0.0, 0.0);
				
				//�հ�������
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

		glPopMatrix(); //��� �հ����� ���� ��� ����->�Ʒ��ȷ� ���ư���.

		//ù��° �հ���
		glPushMatrix(); //���⼭ Ǫ�ø� �ؾ� ��� �հ����� ����� �ٽ� �Ʒ��ȷ� ���ƿ�
		glTranslatef(1.0, 0.0, -0.3);
		glRotatef(60, 0.0, 1.0, 0.0); //ù��° �հ����� ��� �հ����� ��ġ�� �ʰ� �ϱ����ؼ� ȸ��
		glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //ù��° ����
		glTranslatef(0.3, 0.0, 0.0);
			
			//�հ�������
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //2��° ����
			glTranslatef(0.3, 0.0, 0.0);

			//�հ�������
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //3��° ����
			glTranslatef(0.3, 0.0, 0.0);

			//�հ�������
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

		glPopMatrix(); //ù��° �հ����� ���� ��� ����->�Ʒ��ȷ� ���ư���.

	//����° �հ���
		glPushMatrix(); //���⼭ Ǫ�ø� �ؾ� ����° �հ����� ����� �ٽ� �Ʒ��ȷ� ���ƿ�
			glTranslatef(1.0, 0.0, 0.3);
			glRotatef(-50, 0.0, 1.0, 0.0); //����° �հ����� ��� �հ����� ��ġ�� �ʵ��� �ϱ� ���ؼ� ȸ��
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //1��° ����
			glTranslatef(0.3, 0.0, 0.0);

			//�հ�������
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.3, 0.0, 0.0);
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //2��° ����
			glTranslatef(0.3, 0.0, 0.0);

			//�հ�������
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();


			glTranslatef(0.3, 0.0, 0.0);
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //3��° ����
			glTranslatef(0.3, 0.0, 0.0);

			//�հ�������
			glPushMatrix(); //ũ�⿡ ���� ��
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();


		glPopMatrix(); //����° �հ����� ���� ��� ����->�Ʒ��ȷ� ���ư���.

	glPopMatrix(); //�� ó���� Ǫ���آZ�� �׵���ķ� ���ư�

	glutSwapBuffers(); //���ҹ��۸� ���� front frame�� back frame�� �ٲ��ش�(���� ���۸��� ���� �������� ����)
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);        //�𵨺� ��� ����
	glLoadIdentity();                  //�׵���ķ� �ʱ�ȭ
	glTranslatef(0.0, 0.0, -5.0);
}
//keyboard callback �Լ� ����
void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':               //ù��° �հ��� �����̱�
		check = 1;
		break;
	case '2':              //��� �հ��� �����̱�
		check = 2;
		break;
	case '3':              //����° �հ��� �����̱�
		check = 3;
		break;
	case '4':              //��� �հ��� �����̱�
		all = 1;
		break;
	case 's':             //��� �հ��� ���߱�
		check = 0;
		all = 0;
		break;
	case 'S':              //��� �հ��� ���߱�
		check = 0;
		all = 0;
		break;
	}
}
//�����Ű���� �ݹ��Լ� ����
//����Ű�� ���� ī�޶� ������ �ٲ۴�.
void MySpecial(int key, int x, int y) {
	//�����Ű����(Ư������)�� ���������� ���ǵǾ��־ int�� key ������ �޴´�
	switch (key) {
		//������ �ǵ帮�� �ʴ´�
	case GLUT_KEY_UP: //������ �ٶ󺸱�
		cameradir = 1;
		cameraz = 1.5;
		camerax = 0.0;
		cameray = 3;
		break;
	case GLUT_KEY_DOWN: //�Ʒ����� �ٶ󺸱�
		cameradir = 1;
		cameraz = 1.5;
		camerax = 0;
		cameray = -2;
		break;
	case GLUT_KEY_LEFT:  //���ʿ��� �ٶ󺸱�
		cameradir = 3;
		cameraz = 0;
		camerax = -1.5;
		cameray = 1;
		break;
	case GLUT_KEY_RIGHT: //�����ʿ��� �ٶ󺸱�
		cameradir = 2;
		cameraz = 0;
		camerax = 3.5;
		cameray = 3.5;
		break;
	//���� �������� ī�޶��� ��ġ�� ��������, ���� ��ĥ��(�����·� ���ư����� ī�޶��� ��ġ�� ���������� �̵�)
	}
}
//idle callback �Լ� ����
void MyIdle()
{
	if (jobgi == 0)  //���� ����� �������� �ʾ�����
	{
		if (check == 0)  //����-> ���հ����� ���߰� �ϱ����ؼ� 0���� �ʱ�ȭ
		{
			firststart = 0;
			secondstart = 0;
			thirdstart = 0;
		}
		if (check == 1 || all)  //1�Ǵ� all�϶� ù��° �հ����� �����̰� �ϴ� ������ 1�� ����
		{
			firststart = 1;
		}
		if (firststart == 1)  //1�� ������ ù��° �հ����� ��� �����δ�.
		{
			if (first >= 90)
			{
				firstangle = -1;
			}
			else if (first <= 0)
			{
				firstangle = 1;
			}

			if (firstangle == 1)
			{
				first = first + 0.1;
			}
			else
				first = first - 0.1;
		}
		if (check == 2 || all) //2 �Ǵ� all�϶� ��� �հ����� �����̰� �ϴ� ������ 1�� ����
		{
			secondstart = 1;
		}
		if (secondstart == 1)   //1�� �Ǹ� ��� �հ����� ��� �����δ�.
		{
			if (second >= 90)
			{
				secondangle = -1;
			}
			else if (second <= 10)
			{
				secondangle = 1;
			}

			if (secondangle == 1)
			{
				second = second + 0.1;
			}
			else
				second = second - 0.1;
		}
		if (check == 3 || all)  //3�Ǵ� all �϶� ����° �հ����� �����̰� �ϴ� ������ 1�� ����
		{
			thirdstart = 1;
		}
		if (thirdstart == 1)  //������ 1�� ������ ����° �հ����� �����̴°��� �ݺ�
		{
			if (third >= 90)
			{
				thirdangle = -1;
			}
			else if (third <= 0)
			{
				thirdangle = 1;
			}

			if (thirdangle == 1)
			{
				third = third + 0.1;
			}
			else
				third = third - 0.1;
		}
		if (back == 1)  //��Ŭ���� ������ �հ����� ���� ��ġ�� ���ư����Ѵ�
		{
			//���ư������� ������ �ϴ� ����� ����
			check = 0;
			all = 0;
			//���� ��Ų�� ���ư����Ѵ�.
			if (first > 0)
			{
				first = first - 0.03;
			}
			if (second > 0)
			{
				second = second - 0.03;
			}
			if (third > 0)
			{
				third = third - 0.03;
			}
			if (elbow > 0)
			{
				elbow = elbow - 0.015;
			}
			if (first < 0 && second < 0 && third < 0 && elbow<0) //��� �հ����� ���ư��� ���ư��� ���¸� ����
			{
				back = 0; //���� �ϱ��� 0 ���·� ���ư�
				cameramoving = 0; //�տ����� ���⶧ ī�޶� �����ӵ� �����.
			}
			if (cameramoving == 1) //���� ���ڸ��� ���ư��� ī�޶� ���� ��ȯ
			{
				if (cameradir == 1)  //��,�Ʒ��� ����
				{
					camerax = camerax + 0.001;  //���� ���ڸ��� ���ư��� ī�޶� ���� ��ȯ
				}
				if (cameradir == 2) //�����ʿ��� ����
				{
					cameraz = cameraz - 0.001;
				}
				if (cameradir == 3) //���ʿ��� ����
				{
					cameraz = cameraz + 0.001;
				}
			}
		}
	}
	//��� ���߿��� �ٸ� ����� ������ �ʵ��� ����
	else if (jobgi == 1)
	{
		if (cameramoving) //���� ������ ī�޶� ���� ��ȯ
		{
			if (cameradir == 1)  //��,�Ʒ��� ����
			{
				camerax = camerax - 0.001; 
			}
			if (cameradir == 2) //�����ʿ��� ����
			{
				cameraz = cameraz + 0.001;
			}
			if (cameradir == 3) //���ʿ��� ����
			{
				cameraz = cameraz - 0.001;
			}

		}
		//���� �հ����� 90�� ���� �Ȳ�ġ�� 40�� ���� ��°����� ����
		if (first < 90)
		{
			first = first + 0.03;
		}
		if (second < 90)
		{
			second = second + 0.03;
		}
		if (third < 90)
		{
			third = third + 0.03;
		}
		if (elbow < 40)
		{
			elbow = elbow + 0.015;
		}
		if (first >90 && second > 90 && third > 90 && elbow>40) //��Ⱑ �� ������
		{
			jobgi = 0; //��Ⱑ ������
			//��Ⱑ ������ ������ ������ ��ư�� �ʱ�ȭ
			check = 0;
			all = 0;
		}
		if (back == 1) //�����߿� ������ġ�� ���� �Է��� ������
		{
			jobgi = 0; //�����߿� ���ư��ߵȴٸ� �������� �����.
		}

	}
	glutPostRedisplay(); //ȭ�鿡 ��ȭ���� �������� �ٷ� ȭ�鿡 ���� ���ؼ� ����
}
//mousce callback �Լ� ����
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //���콺 ���� Ŭ���� �����ٸ�
	{
		jobgi += 1;                                        //���
		jobgi = jobgi % 2;
		cameramoving = 1;                                  //��⵵�߿� ī�޶� �����̴°��� Ȯ���ϱ����� ����
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //���콺 ������ Ŭ���� �����ٸ�
	{
		back = 1;                             //���� ��ġ�� �ǵ�����.
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();
	glutDisplayFunc(MyDisplay);    //display �ݹ��Լ� ���
	glutReshapeFunc(MyReshape);     //reshape �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyboard);  //keyboard �ݹ��Լ� ���
	glutMouseFunc(MyMouseClick);  //mouse �ݹ��Լ� ���
	glutIdleFunc(MyIdle);         //idle �ݹ��Լ� ���
	glutSpecialFunc(MySpecial);  //specialkeyboard �ݹ��Լ� ���
	glutMainLoop();
	return 0;
}