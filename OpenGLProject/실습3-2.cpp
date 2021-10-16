/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  스페셜 키보드인 특수문자를 받는 키보드콜백을 사용하여 사각형 움직이기                     */
/*                - - - - - - -                                                                   */
/* 기능 :    ← 를 누르면 왼쪽으로 이동, → 를 누르면 오른쪽으로 이동, ↑ 을 누르면 아래로 이동, ↓를 누르면 위쪽으로 이동
             pageup 을 누르면 4개의 좌표가 확대, pagedown을 누르면 4개의 좌표를 축소,
			 확대/축소 과정에서 가시적으로 최대/최소일경우 확대/축소가 일어나지 않도록 설정
			 이때,만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.                              */

			 /*                - - - - - - -                                                                   */
			 /***********************************************************************/
#include <GL/glut.h>
//사각형의 처음 좌표를 전역변수로 선언
double x1 = -0.5;
double x2 = 0.5;
double y1 = -0.5;
double y2 = 0.5;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();
	glFlush();
}
//스페셜키보드 콜백함수 정의
//키보드를 눌렀을때의 EVENT를 받는다
void MySpecial(int key, int x, int y) {
	//스페셜키보드(특수문자)는 정수형으로 정의되어있어서 int형 key 변수를 받는다
	switch (key) {
	case GLUT_KEY_LEFT:
		//경계선에 닿으면 이동x
		if (x1 < -0.9)
		{
			break;
		}
		//왼쪽 화살표일때 사각형 왼쪽으로 이동
		x1 += -0.1;
		x2 += -0.1;
		break;
	case GLUT_KEY_UP:
		//경계선에 닿으면 이동x
		if (y2 > 0.9)
		{
			break;
		}
		//위 화살표일때 사각형 위쪽으로 이동
		y1 += 0.1;
		y2 += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		//경계선에 닿으면 이동x
		if (x2 > 0.9)
		{
			break;
		}
		//오른쪽 화살표일때 오른쪽으로 이동
		x1 += 0.1;
		x2 += 0.1;
		break;
	case GLUT_KEY_DOWN:
		//경계선에 닿으면 이동x
		if (y1 < -0.9)
		{
			break;
		}
		//아래쪽 화살표일때 아래쪽으로 이동
		y1 += -0.1;
		y2 += -0.1;
		break;
	case GLUT_KEY_PAGE_UP:
		//사각형이 확대될때 화면 경계선에 닿는경우 더이상 커지지않는다. 4개의 좌표중에 하나라도 경계선에 도달하면
		// 아래 조건문을 들어가지 않는다.->이때가 최대확대지점
		if ((x1 > -0.9) && (x2 < 0.9) && (y1 > -0.9) && (y2 < 0.9))
		{
			x1 += -0.1;
			x2 += 0.1;
			y1 += -0.1;
			y2 += 0.1;
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		//사각형이 축소될때, 계속 x2와x1을 일정비율 줄이게되면 사각형이 작아지다가 보면 안보이는경우가 생기는데,
		//안보이는경우가 아닌, 안보이기전 사각형을 축소의 최소지점으로 보았다.
		//아래 조건문은 축소되기전, 다음 축소될 좌표를 미리 검증하고, 조건을 만족하면 실행이된다.
		//0.1이 아닌 0.11을 더해준 이유는 x1,x2이 같아진다고 생각되는 부분에서 미세하게 x1이 x2보다 작게 측정됬다. 그래서
		//이 오차를 줄이고자 0.01을 더해준 값으로 비교해보니 그부분에서 x1>x2가 되었고, 사각형이 안보이는경우를 제외할수있었다.
		if ((x1 + 0.11) < (x2 - 0.11))
		{
			x1 += 0.1;
			x2 += -0.1;
			y1 += +0.1;
			y2 += -0.1;
			break;
		}
		break;
	}
	glutPostRedisplay();          //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Keyboard Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);  //display 콜백함수 등록
	glutSpecialFunc(MySpecial);  //keyboard 콜백함수 등록

	glutMainLoop();
	return 0;
}