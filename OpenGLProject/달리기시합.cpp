/***********************************************************************/
/*                           HW#8 : ����                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 12�� 01��    */
/*                                                                                                 */
/* ���� ���� :  �� �κ��� �޸��� ����                                            */
/*                - - - - - - -                                                                   */
/* ��� :   	 R �Ǵ� r Ű�� ������ �޸��� ������ ���۵ȴ�.
				 ������ ���۵Ǹ� �Լ� �Ҹ��� �鸰��.

                 ���콺 ��Ŭ���� �ϸ� �޸��� ���� �� ���·� ���ƿ´�.  

				 w �Ǵ� W Ű Ŭ�� �ϸ� ī�޶� ������ z������ 0.1����   ->������ ����
				 s �Ǵ� S Ű Ŭ�� �ϸ� ī�޶� ������ z������ 0.1����   ->�ڷΰ���
				 a �Ǵ� A Ű Ŭ�� �ϸ� ī�޶� ������ x������ 0.1����    ->�������� ����
				 d �Ǵ� D Ű Ŭ�� �ϸ� ī�޶� ������ x������ 0.1����    ->���������� ����
				 z �Ǵ� Z Ű Ŭ�� �ϸ� ī�޶� ������ y������ 0.1����    ->���� ����
				 x �Ǵ� X Ű Ŭ�� �ϸ� ī�޶� ������ y������ 0.1����    ->�Ʒ��� ����

				 ������ ������ ���ʵڿ� ����ڸ� Ȯ�� �Ѵ�.
*/
				/*                - - - - - - -                                                                   */
				/***********************************************************************/
#include <windows.h>
#include <stdlib.h>

#include <GL/glut.h>
#include <GL/glaux.h>

#include <mmsystem.h>                     //�Լ� �Ҹ��� �ֱ� ���ؼ� ����
#pragma comment(lib,"winmm.lib")          //�Լ� �Ҹ��� �ֱ� ���ؼ� ����

#pragma comment(lib, "glaux.lib")                         //�ؽ��� ������ ����ϱ� ���� ����
#pragma comment (lib,"legacy_stdio_definitions.lib")      //�ؽ��� ������ ����ϱ� ���� ����

struct Vertex {
	// GL_T2F_V3F
	float tu, tv;
	float x, y, z;
};

//s,t�� �̷���� �ؼ� ��ǥ�� x,y,z ����� ��ü ��ǥ->������� �ٴ��� �ǹ��Ѵ�.
Vertex g_quadVertices[] = {
	{ 0.0f,0.0f, -20.0f, -1.5f, -20.0f },
	{ 1.0f,0.0f,  20.0f, -1.5f, -20.0f },
	{ 1.0f,1.0f,  20.0f, -1.5f, 20.0f },
	{ 0.0f,1.0f, -20.0f, -1.5f, 20.0f }
};
GLUquadricObj *qobj = gluNewQuadric();        //�Ǹ����� �����ϱ����ؼ� ��ü ����

int check = 0; //��ü�� �޸��� ������ �����Ű�� ����

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
GLfloat leftknee = 0;       //����

GLfloat leftright = 0;      //���� ��鸲�� ����
int change = 0;             //���� ��鸮�� ����

GLfloat running1 = -16.0;   // ù��° ���� ��ġ
GLfloat running2 = -16.0;   // �ι�° ���� ��ġ
GLfloat door = 0;           //��������� �������� ���� ������.

//ī�޶� ��ġ ����
GLfloat camx = 1.0;
GLfloat camy = 1.0;
GLfloat camz = 1.0;

//ī�޶� �ٶ󺸴� ��ġ����
GLfloat camLx = 0.0;
GLfloat camLy = 0.0;
GLfloat camLz = 0.0;

float seewinner = 0; //����ڰ� �������� ����� Ȯ�� ����
int viewchange = 0;  //����� Ȯ���Ҷ� ī�޶� ��ġ�� �ü��� �ٲ��ִµ� ����ϴ� ����

int weight, height;  //ȭ�鿡 ���� ũ�⸦ ���������� ����ϱ� ���ؼ� ����


void loadTexture(void) {
	AUX_RGBImageRec *pTextureImage = auxDIBImageLoad(L"jandi.bmp"); // �׸��� ���� �Ŀ� ȭ�Ұ��� �迭 ���·� �����´�.

	if (pTextureImage != NULL) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  //��Ұ���ν� ����� ���� ������ ����
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Ȯ�����ν� ����� ���� ������ ����

		//�迭�� ǥ�õ� 2D Image�� ���� Texture Image�� ��ȯ
		//�ؽ��� �޸𸮿� �÷��� ����� �����ϴ�
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTextureImage->sizeX, pTextureImage->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, pTextureImage->data);
	}

	if (pTextureImage) {          //�ؽ��� ���� �޸� �迭�� �����ϸ�
		if (pTextureImage->data)          // �ؽ��� ���� �޸� �迭 �ȿ� ���� ������ �����ϸ�
			free(pTextureImage->data);     // �ؽ��� ���� ���� �ݳ�

		free(pTextureImage);         // �ؽ��� ��ü �ݳ�
	}
}
void MyInit(void) {
	GLfloat MyLightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // IaR , IaG , IaB �ֺ��ݻ籤�� ������->�׸��ڸ� ���ؼ�
	GLfloat MyLightDiffuse[] = { 1.0, 1.0,1.0, 1.0 }; // IdR , IdG , IdB ���ݻ籤�� �ַ� ���->��ü�� ���� �״�� �ޱ� ���ؼ�
	GLfloat MyLightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // IsR , IsG , IsB ���ݻ籤�� �ַ� ���->���̶���Ʈ�� ǥ��

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };                 //�ֺ��ݻ� ��� 
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };                 //���ݻ� ���->��ü�� �⺻�� �Ǵ� ��
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };                //���ݻ� ���->��ü�� ���� ���� �ݻ� ����
	GLfloat mat_shininess[] = { 10.0 };                      //���ݻ��� ���� ���-> ����� Ŀ������ ���̶���Ʈ ũ�Ⱑ �پ���.
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };          //�߱�ü ��ü ������ ���� ���µ�, ��ġ�� �ö󰡸�� �������.
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 1.0 };       // ������ ��ġ

	glLightfv(GL_LIGHT0, GL_AMBIENT, MyLightAmbient);  //�ֺ��ݻ�
	glLightfv(GL_LIGHT0, GL_DIFFUSE, MyLightDiffuse);  //���ݻ�
	glLightfv(GL_LIGHT0, GL_SPECULAR, MyLightSpecular); //���ݻ�
	glClearColor(0.5, 0.4, 0.3, 0.0);

	//��ü�� ǥ�鿡 ���� Ư��
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  //ǥ�鿡 ���� �ֺ��ݻ�
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //ǥ�鿡 ���� ���ݻ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);     //ǥ�鿡 ���� ���ݻ�
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);       //ǥ�鿡 ���� ���ð��
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);        //�߱�ü
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);        //������ ��ġ

	glEnable(GL_LIGHTING);         //���� Ȱ��ȭ
	glEnable(GL_LIGHT0);           //0�� ���� Ȱ��ȭ

	//���� ����
	glEnable(GL_DEPTH_TEST);            //�ٴ��� ������� ��������� z���۰� �� ���Ƽ� ������ ������ ����������
	                                    //�������� ������ �ʴ´�.

	glEnable(GL_COLOR_MATERIAL);    //��ü�� �� Ȱ��ȭ
	glShadeModel(GL_SMOOTH);              //��ü�� ������ �ε巴�� ����
	gluQuadricDrawStyle(qobj, GLU_FILL); //��ü�� �׸����� ä���.
	gluQuadricNormals(qobj, GLU_SMOOTH);    //��ü���� �ε巴�� �׸���.�������� ����
	gluQuadricOrientation(qobj, GLU_OUTSIDE);  //�ٱ����� ����Ű�� �������͸� �׸���.
	gluQuadricTexture(qobj, GL_FALSE);          //�ؽ�Ʈ ��ǥ�� ������� �ʴ´�.
}
//ù��° ����
void player1()
{
	glPushMatrix();
	gluLookAt(0, 0, 0, 0, 2, 0, 0, 0, 1); //����
	glRotatef(leftright, 0.0, 1.0, 0.0); //�Ǹ����� �� ���̰��ϱ����ؼ� ����
	//��ü���� ���� ����

	glTranslatef(0.0, 0.0, 1.2); //�Ӹ��� ���� ����κ�
		//�Ӹ��� ���� ȸ���ؾߵǱ⶧���� �̵��� ��ü �����κп� push pop�� ����
	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //�Ӹ�

	//������ ��
	glPushMatrix();
	glColor3f(1, 1, 1);
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
	glColor3f(1.0, 0.0, 0.0);
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

}
//�ι�° ����
void player2()
{
	glPushMatrix();
	gluLookAt(0, 0, 0, 0, 2, 0, 0, 0, 1); //����
	glRotatef(leftright, 0.0, 1.0, 0.0); //�Ǹ����� �� ���̰��ϱ����ؼ� ����
	//��ü���� ���� ����

	glTranslatef(0.0, 0.0, 1.2); //�Ӹ��� ���� ����κ�
		//�Ӹ��� ���� ȸ���ؾߵǱ⶧���� �̵��� ��ü �����κп� push pop�� ����
	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //�Ӹ�

	//������ ��
	glPushMatrix();
	glColor3f(1, 1, 1);
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
	glColor3f(0.0, 0.0, 1.0);
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

}
//�����
void background()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);              //�ؽ��� ��� Ȱ��ȭ
	loadTexture();                        //�迭�� ǥ�õ� 2D Image�� ���� Texture Image�� ��ȯ
	glInterleavedArrays(GL_T2F_V3F, 0, g_quadVertices); //���ϴ� �迭�� Ȱ��ȭ��
	glDrawArrays(GL_QUADS, 0, 4);                       //������� �׸���.
	glDisable(GL_TEXTURE_2D);                          //�ؽ��� ��� ��Ȱ��ȭ

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);                     //��߼�
	glVertex3f(-20.0, -1.3, -10.0);
	glVertex3f(20.0, -1.3, -10.0);
	glVertex3f(20.0, -1.3, -12.0);
	glVertex3f(-20.0, -1.3, -12.0);
	glEnd();
	glPopMatrix();
}
//��������� �ش��ϴ� ��
void endline()
{
	//���ʹ�
	glPushMatrix();
	glTranslatef(-20, 0, 16);
	glRotatef(-door, 0, 1, 0);                       //���� ������ ����
	glTranslatef(10, 0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(20.0, 1.0, 1.0);
	glutSolidCube(1.0);                             
	glPopMatrix();

	//�����ʹ�
	glPushMatrix();
	glTranslatef(20, 0, 16);
	glRotatef(door, 0, 1, 0);                     //���� ������ ����
	glTranslatef(-10, 0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glScalef(20.0, 1.0, 1.0);
	glutSolidCube(1.0);                          
	glPopMatrix();
}
//display callback �Լ� ����
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          //���� ���� ��� ���
	glShadeModel(GL_SMOOTH);              //��ü�� ������ �ε巴�� ����
	glMatrixMode(GL_MODELVIEW); //�𵨺� ��� �� �ޱ� ���� ����
	glLoadIdentity();             //�׵���ķ� �ʱ�ȭ
	gluLookAt(camx, camy, camz, camLx, camLy, camLz, 0.0, 1.0, 0.0);       //������ȯ
	
	//ù��° ������ġ
	glPushMatrix();
	glTranslatef(-5,0.2,running1);
	player1();
	glPopMatrix();

	//�ι�° ������ġ
	glPushMatrix();
	glTranslatef(5, 0.2, running2);
	player2();
	glPopMatrix();
	endline();               //�������
	background();            //�����
	glFlush();
	glutSwapBuffers(); //���ҹ��۸� ���� front frame�� back frame�� �ٲ��ش�(���� ���۸��� ���� �������� ����)
}
//reshape �ݹ��Լ� ����
void Reshape(int w, int h) {
	weight = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);               //������ȯ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20.0, -20*(GLfloat)w / (GLfloat)h, 20*(GLfloat)w / (GLfloat)h, -20.0, 20.0); //��������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//mouse �ݹ��Լ� ����
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //���콺 ������ Ŭ���� �����ٸ�
	{
		//�޸��� ������ ���·� ���ư�

		seewinner = 0;                               //����� ���·� ���ư�
		glMatrixMode(GL_PROJECTION);                 //����� ���¸� �������������̱⶧���� ������ĵ� �ٲ���
		glLoadIdentity();
		glOrtho(-20, 20.0, -20 * (GLfloat)weight / (GLfloat)height, 20 * (GLfloat)weight / (GLfloat)height, -20.0, 20.0);
		check = 0;                                   //�޸�����

		//ó�� ������ ī�޶� ��ġ�� �ü�
		camx = 1.0;
		camy = 1.0;
		camz = 1.0;
		camLx = 0.0;
		camLy = 0.0;
		camLz = 0.0;

		//ó�� ������ ��ġ
		running1 = -16.0;
		running2 = -16.0;

		//��������� ���� ����
		door = 0;

		//����� �����ڼ��� ���ư�

		rightarm = 0; //�������
		rightelbow = 0; //�Ȳ�ġ ����
		rightangle = 0; //������,�޹��� �̵� ����

		//���� ���� ����
		leftarm = 0;       //��� ����
		leftelbow = 0;     //�Ȳ�ġ ����
		leftangle = 1;         //����,�������� �̵�����

		//�����ٸ� ���� ����
		rightleg = 0;      //���
		rightknee = 0;     //����

		//�޴ٸ� ���� ����
		leftleg = 0;       //���
		leftknee = 0;       //����

		leftright = 0;      //���� ��鸲�� ����
		change = 0;             //���� ��鸮�� ����

	}
}

//Ű���� �ݹ��Լ� ����
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//��� ����
	case 'r':
	case 'R':
		check = 1;
		PlaySound(TEXT("hamsung.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT); //������ ���������� �Լ� bgm �߰�
		break;
	//ī�޶� ���� ��ȯ
	case 'a':
	case 'A':
		camx = camx - 0.1;				//����
		break;
	case 'd':
	case 'D':
		camx = camx + 0.1;				//������
	case 'w':
	case 'W':
		camz = camz - 0.1;				//��
		break;
	case 's':
	case 'S':
		camz = camz + 0.1;				//��
		break;
	case 'z':
	case 'Z':
		camy = camy + 0.1;				//��
		break;
	case 'x':
	case 'X':
		camy = camy - 0.1;               //�Ʒ�
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
				rightarm = rightarm - 0.5;        //����� ������ �����鼭
				rightelbow = rightelbow - 0.6;    //�Ȳ�ġ�� ���� ���� ���� �ö󰣴�.
			}
			if (rightarm >= 0)                    //����
			{
				rightarm = rightarm - 0.3;       //����� �ڷΰ�
				rightelbow = 0;                   //�ڷΰ����� �Ȳ�ġ�� ���
			}
		}
		if (rightangle == 1)  //�������� �ڷΰ���
		{
			if (rightarm < 0)                          //����
			{
				rightarm = rightarm + 0.5;            //������ ���� ����� �ڷ� �ǵ�����.
				rightelbow = rightelbow + 0.6;         //�Ȳ�ġ�� ���´�.
			}
			if (rightarm >= 0)                         //����
			{
				rightarm = rightarm + 0.3;             //�� �߾� ���� 36������ �ڷΰ���.
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
				leftarm = leftarm - 0.5;      //��� ������ ������
				leftelbow = leftelbow - 0.6; //�� ���θ���
			}
			if (leftarm >= 0)                 //����
			{
				leftarm = leftarm - 0.3;         //��� ������ ������
				leftelbow = 0;                   //���� ����·� ����
			}
		}
		if (leftangle == 1) //������ �ڷ� ����
		{
			if (leftarm < 0)              //����
			{
				leftarm = leftarm + 0.5;     //������ ���� ����� �ڷ� �ǵ�����
				leftelbow = leftelbow + 0.6; //�� ���
			}
			if (leftarm >= 0)
			{
				leftarm = leftarm + 0.3;     //��� �ڷ� ������
				leftelbow = 0;     //���� ����·� ����
			}
		}

		//������ �ٸ� �����̱�
		//������ �������� �� 48�� ��ŭ �ڷδ� �� 36�� ��ŭ �����̵��� ����

		if (leftangle == 0)     //�����̶� ���� ������ ������.
		{
			if (rightleg >= 0) // ����
			{
				rightleg = rightleg - 0.3;       //�޸��� �ٸ��� ���ڷε� ���⶧���� �� 36�� ���� �ڷΰ�
				rightknee = 0;                   //���ڸ��� ���� ���� �����
			}
			if (rightleg < 0) //����
			{
				rightleg = rightleg - 0.4;    //����� ���� ������ ���°� ó�� �����(�� 48������)
				rightknee = rightknee + 0.6; //�տ����� ������ ��������. �� 72�� ���� �ö󰡵��� ����
			}
		}
		if (leftangle == 1) //������ �ٸ��� �ڷ� ���ƿö�
		{
			if (rightleg >= 0) //�� ��
			{
				rightleg = rightleg + 0.3;  //�� �ڿ� ������ �ٸ� �ڷΰ���
				rightknee = 0;  //���ڸ��� ���� ���������
			}
			if (rightleg < 0) //�� ��
			{
				rightleg = rightleg + 0.4;   //�� �տ� ������ �ٸ� �ڷΰ���
				rightknee = rightknee - 0.6;  //�� �޸��� ���� ���ƿö� ������ ������.
			}
		}
		//���� �ٸ� �����̱�
		if (rightangle == 0)   //���ʴٸ��� ������ ������(�������� ������ ������)
		{
			if (leftleg >= 0)      //����
			{
				leftleg = leftleg - 0.3; //���ڿ��� ������ �ٸ��� ���´�
				leftknee = 0;  //���ڸ��� ���� ���������
			}
			if (leftleg < 0)
			{
				leftleg = leftleg - 0.4;    //�� �߾ӿ��� �������� �ٸ��� ���´�
				leftknee = leftknee + 0.6; //�տ����� ������ ��������. �� 72�� ���� �ö󰡵��� ����(0.06���� 12000��)
			}
		}
		if (rightangle == 1) //���ʴٸ��� ������ ���ٰ� �ڷ� ���ƿö�
		{
			if (leftleg >= 0) //�� ��
			{
				leftknee = 0;  //���ڸ��� ���� ���������
				leftleg = leftleg + 0.3;  //���߾ӿ���  �ٸ��� �ڷΰ���.
			}
			if (leftleg < 0)  //�� ��
			{
				leftleg = leftleg + 0.4;       //�� �տ��� �߾ӱ��� �ٸ��� �ڷΰ���.
				leftknee = leftknee - 0.6; //�� �޸��� ���� ���ƿö� ������ ������.
			}
		}
		//���� ����
		//�߾� ���� 0.005�� �� 12000�� �̵��ϵ��� ����� ���� �������ٰ� ���� �ڼ��� ���ƿ��� �ٽ� ������ �ٶ󺸵��� ������
		if (leftright > 6 || leftright < -6) //-6~6�� ���� ���� ����.
		{
			change += 1;                      //������ ������ ������ȯ
			change = change % 2;
		}
		if (change == 0)   //���������� ����
		{
			leftright = leftright + 0.05;
		}
		else
			if (change == 1)  //�������� ����
			{
				leftright = leftright - 0.05;
			}
		//ù��° ������ �޸���
		if (running1 < 16.0)
		{
			//ó���ӷ�
			if (running1 < -1)
			{
				running1 = running1 + 0.03;
			}
			//���߿�  �ӷ��� �����Ѵ�.
			else
			{
				running1 = running1 + 0.05;
			}
		}
		//�ι�° ������ �޸���.
		if (running2 < 16.0)
		{
			//ó�� �ӷ�
			if (running2 < 0)
			{
				running2 = running2 + 0.04;
			}
			//���߿� �ӷ��� �����Ѵ�.
			else
			{
				running2 = running2 + 0.03;
			}
		}
		//���߿� ������� ����ϸ�
		if(running1 >16.0 || running2>16.0)
		{
			//���� ������.
			check = 2;
			viewchange = 1; //���� �����鼭 ������ȯ�� �ϵ��� üũ
		}
	}
	if (check == 2)           //�޸��°��� ���߰� ���� ������.
	{
		if (door < 40.0)        /// ��� ���� ������ ���� (�� 40��)
		{
			door = door + 0.1;
		}
		if (door > 40.0) //���� ������ ����ڰ� �ٷ� ������ �ʰ� �ϱ� ���ؼ� ���� �д�
		{
			seewinner=seewinner+ 0.01;
		}

		if (seewinner > 1.0 )   //����ڰ� �������� �ü�
		{
				if (viewchange == 1)
				{
					camx = -4;
					camy = 1.0; 
					camz = 16.5;
					camLx = -5.0;
					camLy = 0.0;
					camLz = 16.0;
				}
				viewchange = 0;  //������ȯ�� ���ְ�      ������ȯ üũ�� Ǯ���ش�.
				glMatrixMode(GL_PROJECTION);             // �������
				glLoadIdentity();
				gluPerspective(50, weight / height, 0.1, 20);       //���� �������� ��¼����� Ȯ�����ش�.
				if (camz < 20.9)                          //Ȯ���� �־����鼭 ����ȿ��ó�� ��Ÿ����.
				{
					camz = camz + 0.01;
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
	glutCreateWindow("running");
	MyInit();
	glutDisplayFunc(MyDisplay); //display �ݹ��Լ� ���
	glutReshapeFunc(Reshape);  //reshape �ݹ��Լ� ���
	glutIdleFunc(MyIdle);       //idle �ݹ��Լ� ���
	glutKeyboardFunc(MyKeyboard);  //keyboard �ݹ��Լ� ���
	glutMouseFunc(MyMouseClick);   //mouse �ݹ��Լ� ���
	glutMainLoop();
	return 0;
}