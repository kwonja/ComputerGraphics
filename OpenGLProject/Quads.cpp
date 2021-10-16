/***********************************************************************/
/*                           HW#2 :   GL Modeling - 2D Primitive들을 구현                                         */
/*  작성자 : 권성민                              날짜 : 2021년 9월 24일    */
/*                                                                                                 */
/* 문제 정의 :  코드4-2를 참조하여 다음과 같은 2D Primitive들을 구현                                                                        */
/*                - - - - - - -                                                                   */
/* 기능 :   Quadsp에 대한 2D Primitive을 구현													  */
/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <GL/glut.h>
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

	glutMainLoop(); //사용자나 시스템에 의해 발생한 메시지를 받아 메시지 처리 함수를 호출하는 중요한 역할을 한다
	return 0;
}