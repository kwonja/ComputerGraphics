/***********************************************************************/
/*                           HW#2 :   GL Modeling - 2D Primitive들을 구현                                         */
/*  작성자 : 권성민                              날짜 : 2021년 9월 24일    */
/*                                                                                                 */
/* 문제 정의 :  코드4-2를 참조하여 다음과 같은 2D Primitive들을 구현                                                                        */
/*                - - - - - - -                                                                   */
/* 기능 :   Points, Lines, LineStrip, LineLoop,TrangleFan, Triangles, TriangleStrip,Polygons, Quads, QuadStrip에 대한 2D Primitive을 구현                                                                                   */
/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <GL/glut.h>

//GL_POINTS 에 대한 MyDisplay
//6개의 점을 찍는다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.5, 0.4, 0.3);
	glPointSize(10.0);  //점찍힌것을 확인하기위해서 크기를 늘려줌
	glBegin(GL_POINTS);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();


	glFlush();
}
/*
//GL_LINES 에 대한 MyDisplay
//순서대로 2개의 점으로 선이 생성된다.
void MyDisplay( ) {
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.5, 0.4, 0.3);
		 glBegin(GL_LINES);
		 glVertex3f(-0.5, -1.0, 0.0);
		 glVertex3f(0.5, -1.0, 0.0);
		 glVertex3f(1.0, 0.0, 0.0);
		 glVertex3f(0.5, 1.0, 0.0);
		 glVertex3f(-0.5, 1.0, 0.0);
		 glVertex3f(-1.0, 0.0, 0.0);
		 glEnd();

     glFlush();
}
*/

/*
//GL_LINE_STRIP 에 대한 MyDisplay
//처음 점부터 반시계 방향으로 점과점을 연결한 선을 출력. 단, 맨마지막 점과 점은 연결하지 않는다. 
	void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	//glBegin(GL_LINES);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
//GL_LINE_LOOP 에 대한 MyDisplay
//점과 점을 반시계방향으로 연결한 선을 출력
	void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	//glBegin(GL_LINES);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_POLYGON 에 대한 MyDisplay
//점을 통해 만들어진 모양에 색을 칠한채로 생성->다각형을 만든다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
void MyDisplay() {
	//GL_TRIANGLES 에 대한 MyDisplay
	//순서대로 3개의 점을 이용해 삼각형 도형을 만든다.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
//GL_TRIANGLE_STRIP 에 대한 MyDisplay
//점 3개로 만든 삼각형들을 길게 연결한다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1, -0.3, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(-0.5, 0.7, 0.0);
	glVertex3f(-1.0, -0.1, 0.0);
	glVertex3f(-1.5, 0.4, 0.0);
	glVertex3f(-2.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_TRIANGLE_FAN 에 대한 MyDisplay
//삼각형들을 부채모양으로 연결한다
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(0.6, -1.0, 0.0);
	glVertex3f(0.7, -0.3, 0.0);
	glVertex3f(0.4, 0.5, 0.0);
	glVertex3f(0.1, 0.8, 0.0);
	glVertex3f(-0.3, 1.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_QUADS 에 대한 MyDisplay
//점을 4개씩 묶어서 4개의 꼭짓점을 가진 POLYGON을 만든다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_QUAD_STRIP 에 대한 MyDisplay
//사각형들을 길게 연결한다.
//사각형을 이어붙이기 위해 V2,V3를 바꾸고, V6,V7을 바꿔주었다.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA);
     glutInitWindowSize(500, 500);
     glutInitWindowPosition(0, 0);
	 //사이즈가 500,500 이고 0,0을 시작으로하는 윈도우 초기화
     glutCreateWindow("Graphics Primitives");  //타이틀이 Graphics Primitives인 원도우 생성
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
     glutDisplayFunc(MyDisplay);           //display callback함수 등록

     glutMainLoop( ); //사용자나 시스템에 의해 발생한 메시지를 받아 메시지 처리 함수를 호출하는 중요한 역할을 한다
     return 0;
}