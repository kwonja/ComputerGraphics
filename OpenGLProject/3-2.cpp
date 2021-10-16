#include <GL/glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, -30.0);
	glVertex3f(10.0, 0.0, -30.0);
	glVertex3f(10.0, 10.0, -30.0);
	glVertex3f(0.0, 10.0, -30.0);
	glEnd();
	glFlush();
}
//투영행렬을 사용하게 되면 원도우 창의 비율만큼 그림이 따라가서 원하던 그림에 왜곡현상이 생길수 있는데,
//ex) 투영행렬 비율이 1:1 인데 윈도우창(뷰폿)비율이 2:1일때 왜곡현상이 발생
//그것을 막아주기위해서 Reshape 함수를 사용
void MyReshape(int NewWidth, int NewHeight) {
	//매개변수값은 os가 알아서 측정해서 넣어준다.
	glViewport(0, 0, NewWidth/2, NewHeight/2);   //측정해서 넣어준 크기만큼 뷰폿으로 창을 설정
	//원도우 크기에 1/2한 곳을 기준으로 가시부피에 측정된 비율만큼 사각형이 출력됨
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)300;               //처음 크기가 300이기때문에 가로을 300으로 나눠서 비율 측정
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)300;              //처음 크기가 300이기때문에 세로을 300으로 나눠서 비율 측정
	//GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)200;   
	//GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)200;
	//200으로 할 경우 가시부피가 더 커져서 화면에 나오는 사각형이 더 작은 모양으로 그려진다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0*Widthfactor, 20.0*Widthfactor, 0.0* Heightfactor, 20.0*Heightfactor, 10.0, 50.0);
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	/*glMatrixMode(GL_PROJECTION);   // 투영행렬 선택
	glLoadIdentity( );  // 현재 투영행렬을 항등행렬로 초기화
	glOrtho(0.0, 20.0, 0.0, 20.0, 10.0, 50.0); // 행렬변환

	glMatrixMode(GL_MODELVIEW);  // 모델뷰행렬 선택
	glLoadIdentity( ); // 현재 모델뷰 행렬을 항등행렬로 초기화*/
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Reshape");
	MyInit();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);

	glutMainLoop();
	return 0;
}