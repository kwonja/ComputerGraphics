/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  마우스콜백을 사용하여 사각형 움직이기                     */
/*                - - - - - - -                                                                   */
/* 기능 :    마우스 왼쪽을 클릭하면 사각형이 오른쪽으로 움직이고, 우클릭을하면 멈춘다.
               이때, 만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.
			     움직이는것을 더 잘보기위해서 0.00001만큼 움직이도록 변경해주었다.                * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//마우스 좌/우 클릭을 저장하기위한 변수
int check = 0;
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
//Idle 콜백함수 정의
//아무 EVENT도 발생하지 않으면 실행된다.
void MyIdle()
{
	//왼쪽 클릭을 했을때만 MyIdle 안에 내용이  실행되도록 구현(움직이도록)
	if (check == 1) //왼쪽 클릭을 했다면
	{
		//경계선에 닿으면 멈춘다
		if (x2 > 1.0)
		{
			return;
		}
		//경계선에 닿은게 아니라면 오른쪽으로 이동한다.
		x1 += 0.00001;
		x2 += 0.00001;
		glutPostRedisplay(); //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
	}
}
//마우스 콜백함수 정의
//마우스 클릭에대한 EVENT를 받는다
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //마우스 왼쪽 클릭이 눌린다면
	{
		check = 1;                                         //이동할수 있도록 1대입
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //마우스 오른쪽 클릭이 눌린다면
	{
		check = 0;                                        //멈춘다면 0대입
	}
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
	glutDisplayFunc(MyDisplay);   //display 콜백함수 등록
	glutMouseFunc(MyMouseClick);  //마우스 클릭 콜백함수 등록
	glutIdleFunc(MyIdle);   //idle콜백함수 등록
	glutMainLoop();
	return 0;
}