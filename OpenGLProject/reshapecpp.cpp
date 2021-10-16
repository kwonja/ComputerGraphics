/***********************************************************************/
/*                           HW#1 : 3D Sierpinski Gasket 구현                                     */
/*  작성자 : 권성민                              날짜 : 2021년 9월 18일    */
/*                                                                                                 */
/* 문제 정의 :  OpenGL을 통해 3D Sierpinski Gasket 구현                                                                           */
/*                - - - - - - -                                                                   */
/* 기능 :  p점을 찍으면서 3D 정사면체를 만든다.                                                                                   */
/*                - - - - - - -                                                                   */
/***********************************************************************/

#include <GL/glut.h>   //glut를 사용하기위해 선언
#include <stdlib.h>  //rand() 함수 사용 용도

/*void MyInit()  //투영 후 회전의 기능을 가진 사용자 지정 함수
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // 하얀배경으로 세팅
	glColor3f(3.0, 0.0, 0.0); // 빨간점으로 세팅
	glMatrixMode(GL_PROJECTION);  //투영행렬을 사용하기위해 선언
	glLoadIdentity();             //투영행렬 초기화
	glOrtho(0.0, 500.0, 0.0, 500.0, 0, -500);     //행렬변환
	//가시부피에 정사면체를 담기위해서 500을 기준으로 투영함
	glRotatef(20.0, 1.0, 1.0, 0.0);  //1,1,0 축을 기준으로 20도만큼 물체를 회전시킨다.

}
*/
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);                   //os가 구해주는 화면 크기에 맞게 뷰폿을 해준다.
	glClearColor(1.0, 1.0, 1.0, 1.0); // 하얀배경으로 세팅
	glColor3f(3.0, 0.0, 0.0); // 빨간점으로 세팅
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;     //정사면체의 기준으로 500으로 지정했기 때문에 500으로 나눠서 비율을 정해준다.
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;   //정사면체의 기준으로 500으로 지정했기 때문에 500으로 나눠서 비율을 정해준다.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//정해진 비율을 500에 곱해서 가시부피안에 들어가는 사면체의 비율을 정해준다 -> 이 과정을 통해 왜곡현상을 막는다.
	glOrtho(0.0*Widthfactor, 500.0*Widthfactor, 0.0*
		Heightfactor, 500.0*Heightfactor, 0.0, -500.0);
	//near, far를 0,-500 으로 고정시킨 이유는 화면에 보이는건 2D 이기때문에 앞뒤는 왜곡현상에 해당되지 않는다.
	glRotatef(20.0, 1.0, 1.0, 0.0);      //1,1,0 축을 기준으로 20도만큼 물체를 회전시킨다.         
}

void MyDisplay(void)
{
	float vertices[4][3] = { { 0.0,0.0,0.0 },{ 250.0,500.0,0.0 },{ 500.0,0.0,0.0 },{250.0,0.0,500.0} };
	//초기 세모에서 3차원으로 보이게 하려면 점 한개를 더 찍어서 사면체 모양으로 만들어줘야한다.
	int i, j;
	float p[3] = { 250.0, 250.0,250.0 };  // 찍힐 포인트
	//3차원 좌표를 사용하기 때문에 z좌표를 추가했다.

	glClear(GL_COLOR_BUFFER_BIT);   //Clear를 통해 버퍼초기화(원도우화면에 있는 그림을 지운다.)
	for (j = 0; j < 100000; j++)
	{
		i = rand() % 4; // 임의점 선택 -> 점이 4개로 증가해서 3->4로 바꿔야한다.
		// 새로 선택된 점과 현재 점을 기준으로 새로운 점 위치 계산 
		p[0] = (p[0] + vertices[i][0]) / 2.0; //새로운 점의 x축
		p[1] = (p[1] + vertices[i][1]) / 2.0; //새로운 점의 y축
		p[2] = (p[2] + vertices[i][2]) / 2.0; //새로운 점의 z축

		glBegin(GL_POINTS);  //begin으로  독립적인 점을 찍는 타입을 선택
		glVertex3fv(p); // 찍힐 위치에 점 찍기  점 좌표가 늘어갔기 때문에 2fv->3fv 으로 변경해줘야한다.
		glEnd();
	}
	//랜덤으로 많은 점을 찍으면서 정사면체를 화면에 출력한다.

	glFlush();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	//사이즈가 500,500 이고 0,0을 시작으로하는 윈도우 초기화
	glutCreateWindow("Sierpinski Gasket");   //타이틀이 Sierpinski Gasket인 원도우 생성
	glutDisplayFunc(MyDisplay);               //display callback함수 등록
	glutReshapeFunc(MyReshape);
	glutMainLoop(); //사용자나 시스템에 의해 발생한 메시지를 받아 메시지 처리 함수를 호출하는 중요한 역할을 한다
}