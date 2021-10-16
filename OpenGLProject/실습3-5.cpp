/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  Idle Callback 을 사용하여 사각형 움직이기                 */
/*                - - - - - - -                                                                   */
/* 기능 :    상,하,좌,우 키보드를 누르면 그 방향으로 사각형이 움직이도록 한다.
             키보드를 누르기전까지, 이전 키보드를 누른방향으로 계속 움직인다.
			   이때, 만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.      
			   사각형이 움직이는것을 더 잘 확인하기위해 0.0001씩 움직이도록 변경해주었다             * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//사각형의 방향을 정해주는 변수
int check = 0;
//사각형의 처음 좌표를 전역변수로 선언
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
	glutSwapBuffers();  //스왑버퍼를 통해 front frame와 back frame을 바꿔준다(더블 버퍼링을 통한 유령현상 예방)
}
//idle 콜백함수 정의
//어떠한 event도 없을때 실행한다.->이벤트가없다면 반복실행된다->연속적으로 움직인다.
void MyIdle() {

	//check가 1이면 왼쪽으로 이동하는데,
	if (check == 1)
	{
		if (x1 >= -1.0) //x1좌표가 경계선을 넘어가게되면 if문 안으로 들어오지않는다.
		{
			x1 += -0.0001;
			x2 += -0.0001;
		}
	}
	//check가 2이면 위쪽으로 이동하는데,
	else if (check == 2)
	{
		if (y2 <= 1.0) //y2좌표가 경계선을 넘어가게되면 if문 안으로 들어오지않는다.
		{
			y1 += 0.0001;
			y2 += 0.0001;
		}
	}
	//check가 3이면 오른쪽으로 이동하는데,
	else if (check == 3)
	{
		if (x2 <= 1.0) //x2좌표가 경계선을 넘어가게되면 if문 안으로 들어오지않는다.
		{
			x1 += 0.0001;
			x2 += 0.0001;
		}
	}
	//check가 4이면 아래쪽으로 이동하는데,
	else if(check==4)
	{
		if (y1 >= -1.0) //y1좌표가 경계선을 넘어가게되면 if문 안으로 들어오지않는다.
		{
			y1 += -0.0001;
			y2 += -0.0001;
		}
	}
	glutPostRedisplay(); //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
}
//상,하,좌,우를 입력받을 스페셜키보드 콜백 함수 정의
//상,하,좌,우는 int 로 정의되어있어서 정수형 key값을 매개변수로 받는다.
void MySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		check = 1;         //왼쪽일때 왼쪽임을 저장 디스플레이에서 사용된다.
		break;
	case GLUT_KEY_UP:
		check = 2;         //위쪽일때 위쪽임을 저장
		break;
	case GLUT_KEY_RIGHT:
		check = 3;           //오른쪽일때 오른쪽임을 저장
		break;
	case GLUT_KEY_DOWN:        
		check = 4;              //아래쪽일때 아래쪽임을 저장
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);        //더블버퍼링을 사용하기위해 선언->버퍼를 2개로 늘린다.
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Idle Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutSpecialFunc(MySpecial); //스페셜키보드 콜백함수 등록
	glutIdleFunc(MyIdle);         //idle 콜백함수 등록

	glutMainLoop();
	return 0;
}