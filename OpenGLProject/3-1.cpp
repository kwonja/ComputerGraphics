#include <GL/glut.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); //윈도우창에 있는 그림버퍼를 지우는것
	glViewport(100, 100, 300, 300);
	glColor3f(0.5, 0.5, 0.5); //사각형 색상
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(10.0, 0.0, -30.0);
	glVertex3f(10.0, 10.0, -30.0);
	glVertex3f(0.0, 10.0, -30.0);
	glEnd();
	//glBegin ~ glEnd 블록 사이에 다양한 함수들이 호출되는데 주로 정점을 배치하거나 속성을 바꾸는 명령들이다. 정점은 다음 함수로 지정한다. 
	//앞에서 설명한대로 좌표 지정 인수를 4개까지 취할 수 있고 인수의 타입도 다양하다. 
	//여기서는 3개를 사용한다.
	glFlush(); //밀린 작업들을 한번에 실행시킨다.
}
void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);  //윈도우 배경을 하얀색으로 만들기
	glMatrixMode(GL_PROJECTION);        //투영행렬 모드로 바꾼다.
	// 투영행렬 선택
	glLoadIdentity();                    // 현재 투영행렬을 항등행렬로 초기화
	glOrtho(0.0, 40.0, 0.0, 40.0, 10.0, 50.0); //(-1,-1),(-1,-0.5),(-0.5,-0.5),(-0.5,-1)->정규화된 가시부피 비율을 가지고 viewport에 들어간다.
	//->가운데가 (0.0)을 기준으로 viewport 크기에 대한 비율로 사각형이 출력된다.
	//glOrtho(0.0, 20.0, 0.0, 20.0, 10.0, 50.0);//(-1,-1),(-1,0),(0,0),(0,-1) ->정규화된 가시부피 비율을 가지고 viewport에 들어간다. 
	//좌표 위치에 대한 비율에 대해서 사각형이 채워진다.
	//glOrtho(0.0, 10.0, 0.0, 10.0, 10.0, 50.0);//(-1,-1) (-1,1), (1,1),(1,-1)->정규화된 가시부피 비율을 가지고 viewport에 들어간다. 
	//이 경우 화면에 꽉 채워진다.
	// 행렬변환
	//나중에 모델뷰를 쓸것이라고 예상하고 미리 초기화 해둔것
	glMatrixMode(GL_MODELVIEW); 
	// 모델뷰행렬 선택   -> viewport에 적용시키 위해서 모델뷰행렬을 선택한다.
	glLoadIdentity();
	// 현재 모델뷰 행렬을 항등행렬로 초기화
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);

	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
