#include <GL/glut.h>  //헤더파일
void MyDisplay() {
	glClearColor(0.259, 0.259, 0.453, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//선좌표
	glBegin(GL_POLYGON); // GL_POINTS, GL_POLYGON 등

	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(0.0, 0.0);
	glVertex2f(-0.8, 0.5);
	glEnd();
	glFlush();
	//gl (그래픽 라이브러리)
}
int main(int argc, char** argv) {
	//glut
	glutInit(&argc, argv);  //초기화
	glutInitDisplayMode(GLUT_RGB); //배경삽입(rgb사용)
	glutInitWindowSize(500, 500);   //윈도우크기
	glutCreateWindow("My First OpenGL Code"); //초기화 후 윈도우 생성
	glutDisplayFunc(MyDisplay); //callback함수
	glutMainLoop();//무한루프로 계속 켜놓게 만듬
	return 0;
}