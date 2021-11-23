/***********************************************************************/
/*                           HW#3 :   뷰폿변환                                        */
/*  작성자 : 권성민                              날짜 : 2021년 11월 6일    */
/*                                                                                                 */
/* 문제 정의 :  코드7-2를 참조하여 다음과 같은 결과를 낼 수 있는 프로그램구현                                            */
/*                - - - - - - -                                                                   */
/* 기능 :    하나의 윈도우를 4개의 뷰폿으로 분할
             우상단의 뷰폿은 gluPerspective()을 이용한 원근투영, 나머지는 glOrtho()을 이용한 평행투영으로 설정

			 (키보드와 마우스콜백을 사용해서 만든 기능)
			 마우스 왼쪽 클릭을 통해 4개로 분할된 각각의 화면에 대한 시점변환이 가능하도록 설정
		     안눌렀을때(처음) : 좌하단->시점 : 정면
			 한번 눌렀을때 : 우하단->시점 : 옆(왼쪽)
			 두번 눌렀을때 : 좌상단->시점 : 위
			 세번 눌렀을때 : 우상단->시점 : (5,5,5)에서 원근투영
			 이후 추가적으로 누르게 되면 다시 좌하단 화면으로 돌아간다.
			 마우스 우클릭 : 좌하단으로 이동

			 각각의 화면 마다 시점변환이 가능하다.
			 좌하단,우하단,좌상단은 w,a,s,d로 이동이 가능
			 w: 시점이 위로 0.1만큼 이동
			 a: 시점이 왼쪽으로 0.1만큼 이동
			 s: 시점이 아래로 0.1만큼 이동
			 d: 시점이 오른쪽으로 0.1만큼 이동
			 우상단은 확대/축소가 가능하다
			 w : 모든 카메라 시점이 0.1만큼 감소(확대)
			 s : 모든 카메라 시점이 0.1만큼 증가(축소)

			 모든 뷰폿들은 객체를 기본적으로 뷰폿의 중심부에 위치하도록 하고.
			Keyboard나 Mouse로 제어할 경우에도 항상 중심부에 위치하도록 함.
			윈도우의 크기를 임의로 변경하거나 Full Screen으로 변경하였을 경우에는 
			윈도우의 크기에 상관없이 객체의 형태가 왜곡되지 않도록 함.
			 */

			 /*                - - - - - - -                                                                   */
			 /***********************************************************************/
#include <GL/glut.h>

int Width, Height;
GLfloat Widthfactor;
GLfloat Heightfactor;
//reshape을 통해 종횡비를 유지하기위해 선언한 변수

int screen = 0; //4개의 뷰폿에 대한 변수 -> 초기에는 좌하단
//좌하단 카메라시점 변수
float fcamerax = 0.3;
float fcameray =0.0;
float fcameraz = 1;
//우하단 카메라시점 변수
float scamerax = -1;
float scameray = 0.5;
float scameraz = 0.0;
//좌상단 카메라 시점 변수
float tcamerax = 0;
float tcameray = 1;
float tcameraz = 0;
//우상단 카메라 시점 변수
float rcamerax = 5;
float rcameray = 5;
float rcameraz = 5;
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//화면에 띄울 그림에대한 정보
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
	glViewport(0, 0, Width / 2, Height / 2); //좌하단 뷰폿
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(fcamerax, fcameray, fcameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //좌하단 뷰폿에 대한 시점->초기값은 정면
	DrawScene();
	glPopMatrix();

	glViewport(Width / 2, 0, Width / 2, Height / 2); //우하단 뷰폿
	glPushMatrix();
	gluLookAt(scamerax, scameray, scameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //우하단 뷰폿에 대한 시점->초기값은 옆(왼쪽)
	DrawScene();
	glPopMatrix();

	glViewport(0, Height / 2, Width / 2, Height / 2); //좌상단 뷰폿
	glPushMatrix();
	gluLookAt(tcamerax, tcameray, tcameraz, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0); //좌상단 뷰폿에 대한 시점->초기값은 위
	DrawScene();
	glPopMatrix();

	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);             //우상단 뷰폿
	glMatrixMode(GL_PROJECTION); //투영행렬선언
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(20,(Widthfactor/Heightfactor), 3.0, 50.0); //원근행렬도 종횡비를 유지

	//위에서 투영행렬을 선언하고, 다시 모델뷰 행렬로 돌아오려면 선언을 해줘야한다
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(rcamerax, rcameray, rcameraz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //우상단 뷰폿에 대한 시점->초기값은(5,5,5)에서 바라본다
	DrawScene();
	glPopMatrix();

	glMatrixMode(GL_PROJECTION); //투영행렬을 마저 pop하기위해서 선언
	glPopMatrix();

	glutSwapBuffers(); //유령현상을 막기위해서 더블버퍼선언
}
//왜곡현상을 막기위해 reshape콜백함수 선언
void MyReshape(int w, int h) {

	Width = w;
	Height = h;
	Widthfactor = (GLfloat)Width / (GLfloat)500; //기존 화면에 대한 가로 비율
	Heightfactor = (GLfloat)Height / (GLfloat)500; //기존 화면에 대한 세로 비율
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0*Widthfactor, 1.0*Widthfactor, -1.0*Heightfactor, 1.0*Heightfactor, 0.5, 5.0); //종횡비를 일치시킨다.
}
//키보드콜백함수 선언
void MyKeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//뷰폿이 좌하단,우하단,좌상단의 경우에는 시점이 왼쪽으로 이동
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
		//뷰폿이 좌하단,우하단,좌상단의 경우에는 시점이 위로 이동
		//뷰폿이 우상단인 경우는 전체적인 카메라 시점이 확대
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
		//뷰폿이 좌하단,우하단,좌상단의 경우에는 시점이 아래로 이동
		//뷰폿이 우상단인 경우는 전체적인 카메라 시점이 축소
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
		//뷰폿이 좌하단,우하단,좌상단의 경우에는 시점이 오른쪽으로 이동
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
	glutPostRedisplay(); //시점변환에 대한 변화를 바로 보여주기위해서 display를 강제로 실행
}
//마우스 콜백함수 선언
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //마우스 왼쪽 클릭이 눌린다면
	{
		screen++;  //뷰폿위치를 변경
		screen = screen % 4; //총 4개의 뷰폿이라서 0,1,2,3으로 표현
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //마우스 오른쪽 클릭이 눌린다면
	{
		screen = 0; //시점변환을 할수 있는 기능이 좌하단 뷰폿으로 이동
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
	glutDisplayFunc(MyDisplay); //디스플레이 콜백함수 등록
	glutReshapeFunc(MyReshape);  //reshape 콜백함수 등록
	glutKeyboardFunc(MyKeyBoard);  //키보드 콜백함수 등록
	glutMouseFunc(MyMouseClick);  //마우스 콜백함수 등록
	glutMainLoop();
	return 0;
}