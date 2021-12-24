/***********************************************************************/
/*                           HW#4 :   계층적 모델링                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 15일    */
/*                                                                                                 */
/* 문제 정의 :  전신 Can Robot 모델링                                            */
/*                - - - - - - -                                                                   */
/* 기능 :   <머리 움직이기>
			<오른팔 움직이기>			<왼쪽팔 움직이기>			<오른다리 움직이기>
			<왼쪽다리 움직이기>
			이에 대한 메뉴 구현->해당 메뉴에 맞는 신체가 한번 움직였다가 원래 자세로 돌아옴
			추가적으로 s를 누르면 움직이는 신체가 멈춤
			색은 예시와 비슷하게 하려고 했으나, 같은색이 반영이안되서 비슷한 색으로 구현																			*/
								  /*                - - - - - - -                                                                   */
								  /***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
GLUquadricObj *qobj = gluNewQuadric();        //실린더를 구현하기위해서 객체 생성





int headcount = 0;
int rightarmcount = 0;
int leftarmcount = 0;
int rightlegcount = 0;
int leftlegcount = 0;
//각각의 동작에서, 동작을 수행하고 원래 자리로 돌아오는것을 체크하기위한 카운트

int headstart = 0;
int rightarmstart = 0;
int leftarmstart = 0;
int rightlegstart = 0;
int leftlegstart = 0;
//물체가 진행하고있음을 기억하는 변수 선언->머리가 움직일때 팔,다리가 움직여도 계속 움직일수있게 설정

int stop = 0;
//물체가 멈추는 행동을 저장하는 변수, 1이면 물체가 멈춘다.

int check = 0;
//각 모드를 체크하는 변수

//머리 관련 변수 
float head = 0;  //각도
int headangle = 1;   //방향을 결정해주는 변수

//오른팔 관련 변수
float rightarm = -30; //디폴트값
int rightarmangle = -1;

//왼팔 관련 변수
float leftarm = 30;
int leftarmangle = 1;

//오른다리 관련 변수
float rightleg = 0;
int rightlegangle = -1;

//왼다리 관련 변수
float leftleg = 0.0;
int leftlegangle = 1;

void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}

//display callback 함수 선언
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	gluQuadricDrawStyle(qobj, GLU_LINE); //객체를 선으로 그린다.
	glMatrixMode(GL_MODELVIEW); //모델뷰 행렬 을 받기 위해 선언
	glLoadIdentity();             //항등행렬로 초기화
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0); //실린더를 잘 보이게하기위해서 선언
	//객체관련 설정 지정

	glTranslatef(0.0, 0.0, 1.2); //머리와 목의 연결부분
		//머리만 따로 회전해야되기때문에 이동후 물체 생성부분에 push pop을 해줌
		glPushMatrix();
		glRotatef((GLfloat)head,0,1,0);
		glColor3f(255.0, 255.0, 0);
		gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //머리
		gluQuadricDrawStyle(qobj, GLU_FILL); //눈은 선이 아닌 색을 채워줘야하기때문에 선언

		//오른쪽 눈
		glPushMatrix();
		glTranslatef(0.15, 0.0, 0.4);
		glColor3f(255, 255, 255);
		glRotatef(90, 1.0, 0.0, 0.0); //디스크를 잘 보이게하기위해서 선언
		gluDisk(qobj, 0.05, 0.1, 20, 3);
		glPopMatrix();

		//왼쪽 눈
		glPushMatrix();
		glTranslatef(-0.15, 0.0, 0.4);
		glColor3f(255, 255, 255);
		glRotatef(90, 1.0, 0.0, 0.0); //디스크를 잘 보이게하기위해서 선언
		gluDisk(qobj, 0.05, 0.1, 20, 3);
		glPopMatrix();
		gluQuadricDrawStyle(qobj, GLU_LINE); //눈이 끝나면 다시 선으로 바꾼다.

		glPopMatrix(); //머리에 대해 이어진 행렬을 pop -> 그래야 목으로 돌아온다.
					  //눈 부분이 머리행렬 안에 있는 이유는 머리가 움직이면 눈도 같이 움직이기때문


	glTranslatef(0.0, 0.0,-0.2); //목과 몸의 연결부분
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.2, 0.2, 0.2, 20, 8); //목 생성

	glTranslatef(0.0, 0.0, -1.2); //목아래 몸통이랑 이어져 있는 부분으로 이동
	glColor3f(0.0, 0.0, 255.0);
	gluCylinder(qobj, 0.8, 0.8, 1.2, 20, 8); //몸통 생성 현재 msd는 몸통 제일 아래쪽 중심에 위치해있다.


	//오른쪽 팔
	glPushMatrix();
	glTranslatef(0.8, 0.0, 1.1);
	glRotatef(rightarm, 0.0, 1.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(0, 255, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(60, 0.0, 1.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(255, 255, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	//손
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//몸통 좌표로 다시 돌아옴

	//왼쪽 팔
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 1.1);
	glRotatef(leftarm, 0.0, 1.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(0, 255, 255);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	glRotatef(-60, 0.0, 1.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.8);
	glColor3f(255.0, 255.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.8, 20, 8);
	//손
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//몸통 좌표로 다시 돌아옴

	//왼쪽 다리
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(leftleg, 0.0, 1.0, 0.0); //왼쪽 다리 각도
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


	//오른쪽 다리 생성
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef(rightleg, 0.0, 1.0, 0.0);  //오른쪽 다리 각도
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

	glutSwapBuffers(); //스왑버퍼를 통해 front frame와 back frame을 바꿔준다(더블 버퍼링을 통한 유령현상 예방)
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//주 메뉴 콜백 함수 선언
void MyMainMenu(int value)
{
	if (stop == 1)     //물체를 멈추게 되면 stop=1 상태가 되는데 메뉴를 클릭하면 다시 동작하게 하기 위함
	{
		stop = 0;    //다시 동작할때 멈춤기능을 푼다
	}
	if (value == 1) //머리 회전
	{
		check = 1;
	}
	if (value == 2) //오른팔 움직이기
	{
		check = 2;
	}
	if (value == 3) //왼팔 움직이기
	{
		check = 3;
	}
	if (value == 4)  //오른다리 움직이기
	{
		check = 4;
	}
	if (value == 5)  //왼다리 움직이기
	{
		check = 5;
	}
	if (value == 6)   //종료
	{
		exit(0);
	}
	glutPostRedisplay();  //위의 변동사항을 바로 수정
}
//키보드 콜백 함수 선언
void MyKeyBoard(unsigned char key, int x, int y)
{
	switch (key)  //s를 누르게되면 물체가 하던 일을 멈춤
	{
	case 's':
		stop = 1;  //멈춘다는 의미에서 stop=1
		break;
	case 'S':
		stop = 1;
		break;
	}
}
//idle 콜백함수 선언 
void MyIdle()
{
	if (stop == 1) //물체를 멈출때
	{
		//모든 기능을 제어
		headstart = 0;
		rightarmstart = 0;
		leftarmstart = 0;
		rightlegstart = 0;
		leftlegstart = 0;
	}
	else if (check == 1) //첫번째 메뉴를 클릭하면
	{
		headstart = 1;  //머리회전이 시작
	}
	else if (check == 2) //두번째 메뉴를 클릭하면
	{
		rightarmstart = 1; //오른팔 회전 시작
	}
	else if (check == 3)  //세번째 메뉴를 클릭하면
	{
		leftarmstart = 1; //왼팔 회전 시작
	}
	else if (check == 4)  //네번째 메뉴를 클릭하면
	{
		rightlegstart = 1; //오른다리 회전 시작
	}
	else if (check == 5)  //다섯번째 메뉴를 클릭하면
	{
		leftlegstart = 1;  //왼쪽 다리 회전 시작
	}

	if (headstart == 1) //머리회전 시작
	{
		//머리가 좌우로 회전하고 다시 원상태로 돌아와야하는데,
		//count는 좌,우를 한번씩 세주고, 돌아오면서 head가 0이상이면 멈춰준다.
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
	if (rightarmstart == 1) //오른팔 회전 시작
	{
		//count는 좌,우를 한번씩 세주고, 돌아오면서 제자리에서 멈춰준다.
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
	if (leftarmstart == 1) //왼팔 회전 시작
	{
		//count는 좌,우를 한번씩 세주고, 돌아오면서 제자리에서 멈춰준다.
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
	if (rightlegstart == 1) //오른다리 회전
	{
		if (rightleg > 0)
		{
			rightlegangle = -1;
			rightlegcount++;
			//다리같은 경우는 갔다가 오면 끝이라서 방향이 바뀌고 바로 멈춰준다.
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
	if (leftlegstart == 1)  //왼쪽다리 회전
	{
		if (leftleg < 0)
		{
			leftlegangle = 1;
			leftlegcount++;
			//다리같은 경우는 갔다가 오면 끝이라서 방향이 바뀌고 바로 멈춰준다.
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
	glutPostRedisplay(); //위에 변경사항을 바로 화면에 띄우게한다.
}
//주메뉴에 대한 내용이 너무 많아서 MyMenu()함수에 따로 저장
void MyMenu()
{
	//주메뉴에 대한 메뉴 콜백함수 등록
	//주메뉴가 5개이므로 5개를 순서대로 나열 ,추가적으로 종료버튼 추가
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	//주메뉴에대한 메뉴 설정
	glutAddMenuEntry("Head Move", 1);
	glutAddMenuEntry("RightArm Move", 2);
	glutAddMenuEntry("LeftArm Move", 3);
	glutAddMenuEntry("RightLeg Move", 4);
	glutAddMenuEntry("LeftLeg Move", 5);
	glutAddMenuEntry("Exit", 6);                   //Exit를 클릭하면 value값 6을 주메뉴콜백함수로 보낸다
	glutAttachMenu(GLUT_RIGHT_BUTTON);              //마우스 오른쪽을 클릭하면 팝업창이 뜨게한다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	MyMenu();
	glutDisplayFunc(MyDisplay); //display 콜백함수 등록
	glutReshapeFunc(Reshape);  //reshape 콜백함수 등록
	glutIdleFunc(MyIdle);       //idle 콜백함수 등록
	glutKeyboardFunc(MyKeyBoard);  //keyboard 콜백함수 등록
	glutMainLoop();
	return 0;
}