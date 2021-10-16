#include <stdlib.h>
#include <GL/glut.h>

GLUquadricObj *qobj = gluNewQuadric();
int headcount = 0;
int rightarmcount = 0;
int leftarmcount = 0;
int rightlegcount = 0;
int leftlegcount = 0;

int headstart = 0;
int rightarmstart = 0;
int leftarmstart = 0;
int rightlegstart = 0;
int leftlegstart = 0;


int check = 0;
float head = 0;
int headangle = 1;
float rightarm = -30; //디폴트값
int rightarmangle = -1;
float leftarm = 30;
int leftarmangle = 1;
float rightleg = 0.0;
int rightlegangle = -1;
float leftleg = 0.0;
int leftlegangle = 1;
void MyInit(void) {
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
// 2. 1번 실습 손가락이 1번움직일때 2번을 누르게하면 1번은 계속 진행되야 하나요?


void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-90, 1.0, 0.0, 0.0); //실린더를 잘 보이게하기위해서 선언
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	glTranslatef(0.0, 0.0, 1.2); //머리와 목의 연결부분
	glPushMatrix();
	glRotatef((GLfloat)head, 0, 1, 0);
	gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //머리
	glPopMatrix();
	glTranslatef(0.0, 0.0, -0.2); //목과 몸의 연결부분
	gluCylinder(qobj, 0.2, 0.2, 0.2, 20, 8); //목 생성
	glTranslatef(0.0, 0.0, -1.2); //목아래 몸통이랑 이어져 있는 부분으로 이동
	gluCylinder(qobj, 0.8, 0.8, 1.2, 20, 8); //몸통 생성 현재 msd는 몸통 제일 아래쪽 중심에 위치해있다.
	//오른쪽 팔
	glPushMatrix();
	glTranslatef(0.8, 0.0, 1.1);
	glRotatef(rightarm, 0.0, 1.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.8);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(60, 0.0, 1.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.8);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glPopMatrix();
	//몸통 좌표로 다시 돌아옴
	//왼쪽 팔
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 1.1);
	glRotatef(leftarm, 0.0, 1.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.8);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(-60, 0.0, 1.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.8);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glPopMatrix();
	//왼쪽 다리 생성
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(leftleg, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -0.5);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.0, 0.0, -0.5);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(-0.1, 0.0, -0.1);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();
	//오른쪽 다리 생성
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef(rightleg, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -0.5);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.0, 0.0, -0.5);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.1, 0.0, -0.1);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void MyMainMenu(int value)
{
	if (value == 1) //머리 회전
	{
		check = 1;
	}
	if (value == 2) //오른팔 움직이기
	{
		check = 2;
	}
	if (value == 3)
	{
		check = 3;
	}
	if (value == 4)
	{
		check = 4;
	}
	if (value == 5)
	{
		check = 5;
	}
	if (value == 6)
	{
		exit(0);
	}
	glutPostRedisplay();
}
void MyKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		check = 0;
		break;
	case 'S':
		check = 0;
		break;
	}
}
void HeadTimer(int value)
{
	if (headcount == 2 && head > 0)
	{
		headcount = 0;
		headstart = 0;
	}
	else
	{
		if (head < -40)
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
			head = head + 0.01;
		}
		else
			head = head - 0.01;

		glutPostRedisplay();     //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
		glutTimerFunc(40, HeadTimer, 1); //40후에 타이머콜백함수가 실행되도록 등록
	}
}
void MyTimer(int value)
{

	if (check == 1)
	{
		headstart = 1;
	}
	else if (check == 2)
	{
		rightarmstart = 1;
	}
	else if (check == 3)
	{
		leftarmstart = 1;
	}
	else if (check == 4)
	{
		rightlegstart = 1;
	}
	if (check == 5)
	{
		leftlegstart = 1;
	}
	if (headstart == 1)
	{
		glutTimerFunc(40, HeadTimer, 1);
	}
	if (rightarmstart == 1)
	{
		if (rightarmcount == 2 && rightarm < -30)
		{
			rightarmcount = 0;
			rightarmstart = 0;
			check = 0;
		}
		else if (rightarm > -10)
		{
			rightarmangle = -1;
			rightarmcount++;
		}
		else if (rightarm < -75)
		{
			rightarmangle = 1;
			rightarmcount++;
		}
		if (rightarmangle == 1)
		{
			rightarm = rightarm + 0.01;
		}
		else
			rightarm = rightarm - 0.01;
	}
	if (leftarmstart == 1)
	{
		if (leftarmcount == 2 && leftarm > 30)
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
			leftarm = leftarm + 0.01;
		}
		else
			leftarm = leftarm - 0.01;
	}
	if (rightlegstart == 1)
	{
		if (rightleg > 0)
		{
			rightlegangle = -1;
			rightlegcount++;
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
			rightleg = rightleg + 0.01;
		}
		else
			rightleg = rightleg - 0.01;
	}
	if (leftlegstart == 1)
	{
		if (leftleg < 0)
		{
			leftlegangle = 1;
			leftlegcount++;
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
			leftleg = leftleg + 0.01;
		}
		else
			leftleg = leftleg - 0.01;
	}
	glutPostRedisplay();     //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
	glutTimerFunc(40, MyTimer, 1); //40후에 타이머콜백함수가 실행되도록 등록
}

void MyMenu()
{
	//주메뉴에 대한 메뉴 콜백함수 등록
	//주메뉴가 5개이므로 5개를 순서대로 나열
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	//주메뉴에대한 하부메뉴를 만들고 싶으면 Addsubmenu함수를 통해 라벨값과 id값을 넣어줘야한다.
	glutAddMenuEntry("Head Move", 1);
	glutAddMenuEntry("RightArm Move", 2);
	glutAddMenuEntry("LeftArm Move", 3);
	glutAddMenuEntry("RightLeg Move", 4);
	glutAddMenuEntry("LeftLeg Move", 5);
	glutAddMenuEntry("Exit", 6);                   //Exit를 클릭하면 value값 1을 주메뉴콜백함수로 보낸다
	glutAttachMenu(GLUT_RIGHT_BUTTON);              //마우스 오른쪽을 클릭하면 팝업창이 뜨게한다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	MyMenu();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(Reshape);
	glutTimerFunc(40,MyTimer,1);
	glutKeyboardFunc(MyKeyBoard);
	glutMainLoop();
	return 0;
}