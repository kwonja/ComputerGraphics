/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  키보드 콜백함수를 이용한 도형 움직이기                                            */
/*                - - - - - - -                                                                   */
/* 기능 :    a또는A 를 누르면 왼쪽으로 이동, f또는F 를 누르면 오른쪽으로 이동, r또는R 을 누르면 아래로 이동, v또는V를 누르면 위쪽으로 이동
             이때,만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.
             b또는 B를 누르면 파란색으로 변경, 또한번 누르면 원래색으로 돌아가도록 기능을 추가                      */

/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <GL/glut.h>

//사각형의 처음 좌표를 전역변수로 선언
float x1 = -0.5;
float x2 = 0.5;
float y1 = -0.5;
float y2 = 0.5;

int check = 0;         //사각형의 색 변경을 저장하기위한 변수 -> 0이면 원래색, 1이면 파란색

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//0이면 기존색
	if (check == 0)
	{
		glColor3f(0.5, 0.5, 0.5);
	}
	//1이면 파란색
	else
	{
		glColor3f(0.0, 0.0, 255);

	}
	glBegin(GL_POLYGON);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);
	glVertex3f(x1, y1, 0.0);
	glEnd();
	glFlush();
}
//키보드 콜백함수 정의
//키보드를 눌렀을때의 EVENT를 받는다
void MyKeyboard(unsigned char key, int x, int y) {
	//키보드로 눌렀을때 key 값에 들어가게된다.
	switch (key) {
		//a 또는 A는 왼쪽으로 이동 이기때문에 x축에 -0.1씩 더해준다.
	case 'a':
	case 'A':
		//-1.0까지가 윈도우창 크기의 끝이기때문에 x1이가 -1.0보다 더 작아지면 윈도우 밖으로 나가게된다 -> 그것을 방지
		if (x1 < -1.0)
		{
			break;
		}
		x1 += -0.1;
		x2 += -0.1;
		break;
		//f또는 F는 오른쪽으로 이동 이기때문에 x축에 0.1씩 더해준다.
	case 'f':
	case 'F':
		//1.0까지가 윈도우창 크기의 끝이기때문에 x2이 1.0보다 더 커지면 윈도우 밖으로 나가게된다 -> 그것을 방지
		if (x2 > 1.0)
		{
			break;
		}
		x1 += 0.1;
		x2 += 0.1;
		break;
		//r또는 R는 아래쪽으로 이동 이기때문에 y축에 -0.1씩 더해준다.
	case 'r':
	case 'R':
		//-1.0까지가 윈도우창 크기의 끝이기때문에 y1이가 -1.0보다 더 작아지면 윈도우 밖으로 나가게된다 -> 그것을 방지
		if (y1 < -1.0)
		{
			break;
		}
		y1 += -0.1;
		y2 += -0.1;
		break;
		//v또는 V는 위쪽으로 이동 이기때문에 y축에 0.1씩 더해준다.
	case 'v':
	case 'V':
		//1.0까지가 윈도우창 크기의 끝이기때문에 y2이 1.0보다 더 커지면 윈도우 밖으로 나가게된다 -> 그것을 방지
		if (y2 > 1.0)
		{
			break;
		}
		y1 += 0.1;
		y2 += 0.1;
		break;
		//b또는B를 누르면 파란색 또한번 누르면 원래색이 된다 ->껏다켰다할수 있는 기능
	case 'b':
	case 'B':
		check++;                     //check를 더해주고
		check = check % 2;           //2로 나누면 0 또는 1의 값만 가질수있다. 1이면 파란색, 0이면 원래색을 디스플레이에 띄운다.
		break;
	}
	glutPostRedisplay();             //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
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
	glutDisplayFunc(MyDisplay); //display 콜백함수 등록
	glutKeyboardFunc(MyKeyboard); //keyboard 콜백함수 등록

	glutMainLoop();
	return 0;
}