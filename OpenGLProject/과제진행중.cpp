/***********************************************************************/
/*                           HW#7 :   ����                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 11�� 17��    */
/*                                                                                                 */
/* ���� ���� :  ���� Can Robot �𵨸��� �޸��� ��ɰ� ������ �����ÿ�.                                            */
/*                - - - - - - -                                                                   */
/* ��� :   	<R �Ǵ� r Ű�� ������> ���Ȱ� ��ٸ��� ������ ������ �޸��� ����� �ǰ��Ͻÿ�.
                 �κ��� ������ �����ÿ�.
				<�޸��� ����(r,RŰ�� ������) S �Ǵ� s Ű�� ������> ���� ��ȯ�� ���� ��ü�� ���� ���ߴ� ��ġ�� �ٲ�� ����																						*/
			/*                - - - - - - -                                                                   */
			/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
GLUquadricObj *qobj = gluNewQuadric();        //�Ǹ����� �����ϱ����ؼ� ��ü ����

int check = 0; //��ü�� �޸��� ������ �����Ű�� ����
int value = 0; //��ü�� ������ȯ���θ� Ȯ���ϴ� ����

//ó���� ���� �ڼ����� �����Ѵ�.

//������ ���� ����
GLfloat rightarm = 0; //�������
GLfloat rightelbow = 0; //�Ȳ�ġ ����
int rightangle = 0; //������,�޹��� �̵� ����

//���� ���� ����
GLfloat leftarm = 0;       //��� ����
GLfloat leftelbow = 0;     //�Ȳ�ġ ����
int leftangle = 1;         //����,�������� �̵�����

//�����ٸ� ���� ����
GLfloat rightleg = 0;      //���
GLfloat rightknee = 0;     //����

//�޴ٸ� ���� ����
GLfloat leftleg = 0;       //���
GLfloat leftknee =0;       //����

GLfloat leftright = 0;      //���� ��鸲�� ����
int change = 0;             //���� ��鸮�� ����

GLfloat lightmove = 0.5;
void MyInit(void) {
	GLfloat MyLightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // IaR , IaG , IaB �ֺ��ݻ籤�� ������->�׸��ڸ� ���ؼ�
	GLfloat MyLightDiffuse[] = { 1.0, 1.0,1.0, 1.0 }; // IdR , IdG , IdB ���ݻ籤�� �ַ� ���->��ü�� ���� �״�� �ޱ� ���ؼ�
	GLfloat MyLightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // IsR , IsG , IsB ���ݻ籤�� �ַ� ���->���̶���Ʈ�� ǥ��

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };                 //�ֺ��ݻ� ��� 
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.0, 1.0 };                 //���ݻ� ���->��ü�� �⺻�� �Ǵ� ��
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };                //���ݻ� ���->��ü�� ���� ���� �ݻ� ����
	GLfloat mat_shininess[] = { 10.0 };                      //���ݻ��� ���� ���-> ����� Ŀ������ ���̶���Ʈ ũ�Ⱑ �پ���.
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };          //�߱�ü ��ü ������ ���� ���µ�, ��ġ�� �ö󰡸�� �������.
	GLfloat light_position[] = { 1.0, 0.5, 0.5, 1.0 };       // ������ ��ġ
	GLfloat model_ambient[] = { 0.3, 0.0, 0.0, 1.0 };         //0.3,0,0 �� ������ ���� �߰�����(������ ������)

	glLightfv(GL_LIGHT0, GL_AMBIENT, MyLightAmbient);  //�ֺ��ݻ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, MyLightDiffuse);  //���ݻ�
	glLightfv(GL_LIGHT0, GL_SPECULAR, MyLightSpecular); //���ݻ�
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//��ü�� ǥ�鿡 ���� Ư��
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  //ǥ�鿡 ���� �ֺ��ݻ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //ǥ�鿡 ���� ���ݻ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);     //ǥ�鿡 ���� ���ݻ�
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);       //ǥ�鿡 ���� ���ð��
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);        //�߱�ü
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);        //������ ��ġ
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);  //�����ֺ� ���� �� ����-> ������ ���ؼ� ������ ���� ����
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //�������� ���� ��ġ->������ �������͸� ���

	//���� ����
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);         //���� Ȱ��ȭ
	glEnable(GL_LIGHT0);           //0�� ���� Ȱ��ȭ
	//glEnable(GL_COLOR_MATERIAL);    //��ü�� �� Ȱ��ȭ

}
//display callback �Լ� ����
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          //���� ���� ��� ���
	glShadeModel(GL_SMOOTH);              //��ü�� ������ �ε巴�� ����
	gluQuadricDrawStyle(qobj, GLU_FILL); //��ü�� �׸����� ä���.
	gluQuadricNormals(qobj, GLU_SMOOTH);    //��ü���� �ε巴�� �׸���.�������� ����
	gluQuadricOrientation(qobj, GLU_OUTSIDE);  //�ٱ����� ����Ű�� �������͸� �׸���.
	gluQuadricTexture(qobj, GL_FALSE);          //�ؽ�Ʈ ��ǥ�� ������� �ʴ´�.

	glMatrixMode(GL_MODELVIEW); //�𵨺� ��� �� �ޱ� ���� ����
	glLoadIdentity();             //�׵���ķ� �ʱ�ȭ
	glPushMatrix();
	gluLookAt(0, 0, 0, lightmove, 1, 0.1, 0, 0, 1);
	glRotatef(leftright,0.0, 1.0, 0.0); //�Ǹ����� �� ���̰��ϱ����ؼ� ����
	//��ü���� ���� ����

	glTranslatef(0.0, 0.0, 1.2); //�Ӹ��� ���� ����κ�
		//�Ӹ��� ���� ȸ���ؾߵǱ⶧���� �̵��� ��ü �����κп� push pop�� ����
	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //�Ӹ�

	//������ ��
	glPushMatrix();
	glColor3f(1,1, 1);
	glTranslatef(0.15, -0.35, 0.4);
	glRotatef(90, 1.0, 0.0, 0.0); //��ũ�� �� ���̰��ϱ����ؼ� ����
	gluSphere(qobj, 0.1, 20, 20);
	glPopMatrix();

	//���� ��
	glPushMatrix();
	glTranslatef(-0.15, -0.35, 0.4);
	glColor3f(1, 1, 1);
	glRotatef(90, 1.0, 0.0, 0.0); //��ũ�� �� ���̰��ϱ����ؼ� ����
	gluSphere(qobj, 0.1, 20, 20);
	glPopMatrix();

	glPopMatrix(); //�Ӹ��� ���� �̾��� ����� pop -> �׷��� ������ ���ƿ´�.
				  //�� �κ��� �Ӹ���� �ȿ� �ִ� ������ �Ӹ��� �����̸� ���� ���� �����̱⶧��


	glTranslatef(0.0, 0.0, -0.2); //��� ���� ����κ�
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(qobj, 0.2, 0.2, 0.2, 20, 8); //�� ����

	glTranslatef(0.0, 0.0, -1.2); //��Ʒ� �����̶� �̾��� �ִ� �κ����� �̵�
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(qobj, 0.8, 0.8, 1.2, 20, 8); //���� ���� ���� msd�� ���� ���� �Ʒ��� �߽ɿ� ��ġ���ִ�.


	//������ ��
	glPushMatrix();
	glTranslatef(0.8, 0.0, 1.1);
	glRotatef(rightarm, 1.0, 0.0, 0.0); //��� ����
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(0, 1, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	glRotatef(rightelbow, 1.0, 0.0, 0.0); //�Ȳ�ġ ����
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	//��
	glTranslatef(0.0, 0.0, -0.1);
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//���� ��ǥ�� �ٽ� ���ƿ�

	//���� ��
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 1.1);
	glRotatef(leftarm, 1.0, 0.0, 0.0); //��� ����
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(0, 0.8, 0.2);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	glRotatef(leftelbow, 1.0, 0.0, 0.0); //�Ȳ�ġ ����
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	//��
	glTranslatef(0.0, 0.0, -0.1);
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//���� ��ǥ�� �ٽ� ���ƿ�

	//���� �ٸ�
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(leftleg, 1.0, 0.0, 0.0); //���� �ٸ� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1, 0, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glRotatef(leftknee, 1.0, 0.0, 0.0); //���� �ٸ� ���� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(-0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 1.0);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();


	//������ �ٸ� ����
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef(rightleg, 1.0, 0.0, 0.0);  //������ �ٸ� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1, 0, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glRotatef(rightknee, 1.0, 0.0, 0.0);  //������ �ٸ� ���� ����
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 1.0);
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
//Ű���� �ݹ��Լ� ����
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)  //r,R�� �����ԵǸ� ��ü�� �޸��� �ȴ�. s,S�� �����ԵǸ� ������ ���Ѵ�.
	{
	case 'r':
	case 'R':
		check = 1;           //��ü�� �޸���.
		break;
	case 's':
	case 'S':
		value = 2;             //������ ��ȭ�Ѵ�.
		break;
	}
}
//idle �ݹ��Լ� ���� 
void MyIdle()
{

	if (check == 1) //�޸��� ����
					//���տ��� 60�� �϶� 5���� �����̸� 12�� �����̰�, ���ڿ��� 36�� �϶� 3���� �����̸� 12�� �����δ�.
					//�̷��� �յ� Ƚ���� ���� �����ð����� ���Ȱ� ������, �޴ٸ� �����ٸ���  �� �߾�(0��)���� �������� ����
	{
			//������ �����̱�
			if (rightarm < -60 || rightarm>36)   //������ 60������ ���� �ڷ� 36�� ��������.
			{
				rightangle += 1;                 //-60����,36�̻󰡸� ���� �ٲٱ�
				rightangle = rightangle % 2;
			}
			if (rightangle == 0)      //�������� ������ ����
			{
				if (rightarm < 0)                      //����
				{
					rightarm = rightarm - 0.05;        //����� ������ �����鼭
					rightelbow = rightelbow - 0.06;    //�Ȳ�ġ�� ���� ���� ���� �ö󰣴�.
				}
				if (rightarm >= 0)                    //����
				{
					rightarm = rightarm - 0.03;       //����� �ڷΰ�
					rightelbow = 0;                   //�ڷΰ����� �Ȳ�ġ�� ���
				}
			}
			if (rightangle == 1)  //�������� �ڷΰ���
			{
				if (rightarm < 0)                          //����
				{
					rightarm = rightarm + 0.05;            //������ ���� ����� �ڷ� �ǵ�����.
					rightelbow = rightelbow + 0.06;         //�Ȳ�ġ�� ���´�.
				}
				if (rightarm >= 0)                         //����
				{
					rightarm = rightarm + 0.03;             //�� �߾� ���� 36������ �ڷΰ���.
					rightelbow = 0;                        //�Ȳ�ġ�� �� �߾ӿ� �����ڴ� ����·� �ڷ� �̵�
				}
			}
			
			//���� �����̱�
			if (leftarm < -60 || leftarm>36)  //������ 60������ ���� �ڷ� 36�� ��������.
			{
				leftangle += 1;                    //-60����,36�̻󰡸� ���� �ٲٱ�
				leftangle = leftangle % 2;
			}
			if (leftangle == 0) //������ ������ ������
			{
				if (leftarm < 0)                     //����
				{
					leftarm = leftarm - 0.05;      //��� ������ ������
					leftelbow = leftelbow - 0.06; //�� ���θ���
				}
				if (leftarm >= 0)                 //����
				{
					leftarm = leftarm - 0.03;         //��� ������ ������
					leftelbow = 0;                   //���� ����·� ����
				}
			}
			if (leftangle == 1) //������ �ڷ� ����
			{
				if (leftarm < 0)              //����
				{
					leftarm = leftarm + 0.05;     //������ ���� ����� �ڷ� �ǵ�����
					leftelbow = leftelbow + 0.06; //�� ���
				}
				if (leftarm >= 0)
				{
					leftarm = leftarm + 0.03;     //��� �ڷ� ������
					leftelbow = 0;     //���� ����·� ����
				}
			}

			//������ �ٸ� �����̱�
			//������ �������� �� 48�� ��ŭ �ڷδ� �� 36�� ��ŭ �����̵��� ����

			if (leftangle == 0)     //�����̶� ���� ������ ������.
			{
				if (rightleg >= 0) // ����
				{
					rightleg = rightleg - 0.03;       //�޸��� �ٸ��� ���ڷε� ���⶧���� �� 36�� ���� �ڷΰ�
					rightknee = 0;                   //���ڸ��� ���� ���� �����
				}
				if (rightleg < 0) //����
				{
					rightleg = rightleg - 0.04;    //����� ���� ������ ���°� ó�� �����(�� 48������)
					rightknee = rightknee + 0.06; //�տ����� ������ ��������. �� 72�� ���� �ö󰡵��� ����
				}
			}
			if (leftangle == 1) //������ �ٸ��� �ڷ� ���ƿö�
			{
				if (rightleg >= 0) //�� ��
				{
					rightleg = rightleg + 0.03;  //�� �ڿ� ������ �ٸ� �ڷΰ���
					rightknee = 0;  //���ڸ��� ���� ���������
				}
				if (rightleg < 0) //�� ��
				{
					rightleg = rightleg + 0.04;   //�� �տ� ������ �ٸ� �ڷΰ���
					rightknee = rightknee - 0.06;  //�� �޸��� ���� ���ƿö� ������ ������.
				}
			}
			//���� �ٸ� �����̱�
			if (rightangle == 0)   //���ʴٸ��� ������ ������(�������� ������ ������)
			{
				if (leftleg >= 0)      //����
				{
					leftleg = leftleg - 0.03; //���ڿ��� ������ �ٸ��� ���´�
					leftknee = 0;  //���ڸ��� ���� ���������
				}
				if (leftleg < 0)
				{
					leftleg = leftleg - 0.04;    //�� �߾ӿ��� �������� �ٸ��� ���´�
					leftknee = leftknee + 0.06; //�տ����� ������ ��������. �� 72�� ���� �ö󰡵��� ����(0.06���� 12000��)
				}
			}
			if (rightangle == 1) //���ʴٸ��� ������ ���ٰ� �ڷ� ���ƿö�
			{
				if (leftleg >= 0) //�� ��
				{
					leftknee = 0;  //���ڸ��� ���� ���������
					leftleg = leftleg + 0.03;  //���߾ӿ���  �ٸ��� �ڷΰ���.
				}
				if (leftleg < 0)  //�� ��
				{
					leftleg = leftleg + 0.04;       //�� �տ��� �߾ӱ��� �ٸ��� �ڷΰ���.
					leftknee = leftknee - 0.06; //�� �޸��� ���� ���ƿö� ������ ������.
				}
			}
			//���� ����
			//�߾� ���� 0.005�� �� 12000�� �̵��ϵ��� ����� ���� �������ٰ� ���� �ڼ��� ���ƿ��� �ٽ� ������ �ٶ󺸵��� ������
			if (leftright > 6 || leftright < -6) //-6~6�� ���� ���� ����.
			{
				change += 1;                      //������ ������ ������ȯ
				change = change % 2;
			}
			if (change==0)   //���������� ����
			{
				leftright = leftright + 0.005;
				if (value == 2)
				{
					lightmove = lightmove + 0.0005;               //���� ��ȯ
				}
			}
			else
			if (change==1)  //�������� ����
			{
				leftright = leftright - 0.005;
				if (value == 2)
				{
					lightmove = lightmove - 0.0005;               //���� ��ȯ
				}
			}
	
	}
	glutPostRedisplay(); //���� ��������� �ٷ� ȭ�鿡 �����Ѵ�.
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���� ���� ��� ���
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	glutDisplayFunc(MyDisplay); //display �ݹ��Լ� ���
	glutReshapeFunc(Reshape);  //reshape �ݹ��Լ� ���
	glutIdleFunc(MyIdle);       //idle �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyboard);  //keyboard �ݹ��Լ� ���
	glutMainLoop();
	return 0;
}