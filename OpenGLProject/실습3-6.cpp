/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  Timer Callback 을 사용하여 사각형 움직이기                 */
/*                - - - - - - -                                                                   */
/* 기능 :     프로그램이 실행되면 사각형은 오른쪽으로 이동하다가 벽에 부딪히면 도형의 색깔이 빨강색으로 변하고,
              왼쪽으로 가다가 왼쪽 벽에 부딪히면 원래색으로 돌아온후, 다시 오른쪽으로 이동을 반복한다.
			  그리고 왼쪽을 클릭하면 움직이는 도형이 멈춘다. 우클릭을 하면 다시 움직이도록 추가로 설정해주었다.
			 
			   이때, 만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.      
			   사각형이 움직이는것을 더 잘 확인하기위해 0.01씩 움직이도록 변경해주었다         * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>

int check = 0;             // 마우스 클릭에대한 정보를 저장해주는 변수
int move = 1;               //벽에 부딪혓을때를 저장해주는 변수
//사각형의 처음 좌표를 전역변수로 선언
double x1 = -0.5;
double x2 = 0.5;
double y1 = -0.5;
double y2 = 0.5;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	//
	if (move == 1)        //왼쪽벽에 부딪히고 오른쪽으로 갈때
	{
		glColor3f(0.0, 0.5, 0.8);  //원래색의 사각형
	}
	else if (move == 0)   //오른쪽벽에 부딪히고 왼쪽으로 갈때
	{
		glColor3f(255.0, 0.0, 0.0);   //빨강색의 사각형
	}
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();

	glutSwapBuffers();   //스왑버퍼를 통해 front frame와 back frame을 바꿔준다(더블 버퍼링을 통한 유령현상 예방)
}
//마우클릭 콜백함수 등록
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)       //왼쪽클릭을 했을때
	{
		check = 1;                                          //check=1 움직임을 멈춤
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)   //오른쪽 클릭했을때
	{
		check = 0;                                          //check=0  다시움직이게하기
	}
}
//타이머 콜백함수 정의
//타이머 콜백함수는 한번실행되고나면 다시 실행이 안되기때문에 재귀적으로 사용해야한다.
void MyTimer(int Value) {
	//check==0 은 멈추지않고 작동할때
	if (check == 0)
	{
		if (move == 0) //왼쪽으로 가고있을때
		{
			if (x1 < -1.0) //경계선에 닿으면
			{
				move = 1; //오른쪽으로 이동하도록 1 대입
			}
			x1 += -0.01;
			x2 += -0.01;
		}
		if (move == 1) //오른쪽으로 가고있을때
		{
			if (x2 > 1.0)  //경계선에 닿으면
			{
				move = 0; //왼쪽으로 이동하도록 0 대입
			}
			x1 += 0.01;
			x2 += 0.01;
		}
		glutPostRedisplay();     //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
		glutTimerFunc(40, MyTimer, 1); //40후에 타이머콜백함수가 실행되도록 등록
	}
	else if(check==1) //작동하지않을때
	{   //움직이지않더라도 우클릭후 다시 움직이게 하려면 타이머콜백함수를 계속 등록시켜줘야함.
		//그렇지 않고, 움직임이 멈췄을때 타이머 콜백함수등록을 끝내면, 다시 타이머 콜백함수를 실행시킬수가 없음.
		//타이머 콜백함수를 등록하면 한번실행하고 종료된다.
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //더블버퍼링을 사용하기위해 선언->버퍼를 2개로 늘린다.
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Timer Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);         //display 콜백함수 등록
	glutMouseFunc(MyMouseClick);         //마우스 콜백함수 등록
	glutTimerFunc(40, MyTimer, 1);        //타이머 콜백함수 등록

	glutMainLoop();
	return 0;
}