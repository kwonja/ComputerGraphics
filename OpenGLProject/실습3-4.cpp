/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 1일    */
/*                                                                                                 */
/* 문제 정의 :  메뉴 콜백 함수를 이용하여 메뉴 만들기                     */
/*                - - - - - - -                                                                   */
/* 기능 :    .주 메뉴로 주메뉴 : Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit 총 5개를 만들고,
              각각의 주 메뉴에 아래와 같은 하부메뉴를 만든다.
            Draw Sphere 하부 메뉴 : Small Sphere, Large Sphere   Draw Torus 하부 메뉴 : Small Torus , Large Torus			Draw Teapot 하부 메뉴 : Small Teapot , Large Teapot   Change Color 하부 메뉴 : Red, Green, Blue
			   이때, 만들어지는 사각형은 윈도우창 바깥으로 안나가도록 설정해주었다.      * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//크기에 대한 정보를 저장하는 변수
GLboolean IsSmall = true;
//도형에대한 정보를 저장하는 변수
GLint Object = 1;
//색에대한 정보를 저장하는 변수
GLint COLOR = 0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//색에 대한 변경을 메뉴콜백함수로 부터 실행하면,전역변수로 저장되고, 디스플레이에서 실행된다.
	if(COLOR==0) //원래 가지고 있던 색을 color=0이라고 지정
	glColor3f(0.0, 0.5, 0.5);
	else if(COLOR==1) glColor3f(255.0, 0.0, 0.0);   //빨강은 color=1
	else if (COLOR == 2) glColor3f(0.0, 255.0, 0.0);  //초록은 color=2.
	else glColor3f(0.0, 0.0, 255.0);                  //파랑은 color=3 그렇지만 더이상 목록이없기때문에 else로 표현

	//하부메뉴를 선택하면 각각의 하부메뉴마다 물체에대한 정보를 저장하는 변수가 있다.
	//그리고 작은것을 선택할건지,큰것을 선택할건지에 대한 메뉴에도 역시 크기에대한 정보를 저장하는 변수가 있다.
	switch (Object)
	{
	case 1:          //sphere
		if (IsSmall)                          //small을 선택한 경우
			glutWireSphere(0.5, 30, 30);
		else                                   //large를 선택한 경우
			glutWireSphere(0.7, 30, 30);
		break;
	case 2:             //tour
		if (IsSmall)                           //small을 선택한 경우
			glutWireTorus(0.1, 0.3, 10, 10);
		else                                       //large를 선택한 경우
			glutWireTorus(0.3, 0.5, 10, 10);
		break;
	case 3:             //teapot
		if (IsSmall)                    //small을 선택한 경우
			glutWireTeapot(0.3);
		else                            //large를 선택한 경우
			glutWireTeapot(0.5);
		break;
	}
	glFlush();
}
//주메뉴 콜백함수 등록
void MyMainMenu(int entryID) {

	if (entryID == 1)       exit(0);
	//value값이 1이 들어오면 화면 종료

	glutPostRedisplay();  //위에 변경사항들이 바로 디스플레이에 적용되도록 강제실행시켜준다.
} 
//sphere에대한 하부메뉴 콜백함수 정의
//하부메뉴에 대한 목록을 선택하면 해당 value값이 콜백함수로 들어온다.
//그리고 해당하는 옵션에 따라 디스플레이가 바뀌도록 전역변수에 값을 바꿔준다.
void MySphereMenu(int entryID) {
	Object = 1;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//torus에 대한 하부메뉴 콜백함수 정의
//하부메뉴에 대한 목록을 선택하면 해당 value값이 콜백함수로 들어온다.
//그리고 해당하는 옵션에 따라 디스플레이가 바뀌도록 전역변수에 값을 바꿔준다.
void MyTorusMenu(int entryID) {
	Object = 2;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//teapot에 대한 하부메뉴 콜백함수 정의
//하부메뉴에 대한 목록을 선택하면 해당 value값이 콜백함수로 들어온다.
//그리고 해당하는 옵션에 따라 디스플레이가 바뀌도록 전역변수에 값을 바꿔준다.
void MyTeapotMenu(int entryID) {
	Object = 3;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//색에대한 하부메뉴 콜백함수 정의
//하부메뉴에 대한 목록을 선택하면 해당 value값이 콜백함수로 들어온다.
//그리고 해당하는 옵션에 따라 디스플레이가 바뀌도록 전역변수에 값을 바꿔준다.
void MyColorMenu(int entryID) {
	if (entryID == 1)            COLOR = 1;
	else if (entryID == 2)      COLOR = 2;
	else if (entryID == 3)   COLOR = 3;

	glutPostRedisplay();
}

void MyInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//하부메뉴에는 해당 물체의 small,large만 표현되도록 설정
	//AddMenuEntry를 통해 메뉴목록을 추가할수있다.
	//등록한 함수에 대한 목록을 선택하면 콜백함수로 value값을 보내준다.

	//sphere에 대한 하부메뉴 메뉴 콜백함수 등록
	GLint MySphereMenuID = glutCreateMenu(MySphereMenu);
	glutAddMenuEntry("Small Sphere", 1);
	glutAddMenuEntry("Large Sphere", 2);

	//torus에 대한 하부메뉴 메뉴 콜백함수 등록
	GLint MyTorusMenuID = glutCreateMenu(MyTorusMenu);
	glutAddMenuEntry("Small Torus", 1);
	glutAddMenuEntry("Large Torus", 2);

	//teapot에 대한 하부메뉴 메뉴 콜백함수 등록
	GLint MyTeapotMenuID = glutCreateMenu(MyTeapotMenu);
	glutAddMenuEntry("Small Teapot", 1);
	glutAddMenuEntry("Large Teapot", 2);

	//color에 대한 하부메뉴 메뉴 콜백함수 등록
	GLint MyColorMenuID = glutCreateMenu(MyColorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	//주메뉴에 대한 메뉴 콜백함수 등록
	//주메뉴가 5개이므로 5개를 순서대로 나열
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	//주메뉴에대한 하부메뉴를 만들고 싶으면 Addsubmenu함수를 통해 라벨값과 id값을 넣어줘야한다.
	glutAddSubMenu("Draw Sphere", MySphereMenuID);
	glutAddSubMenu("Draw Torus", MyTorusMenuID);
	glutAddSubMenu("Draw Teapot", MyTeapotMenuID);
	glutAddSubMenu("Change Color", MyColorMenuID);
	glutAddMenuEntry("Exit", 1);                   //Exit를 클릭하면 value값 1을 주메뉴콜백함수로 보낸다
	glutAttachMenu(GLUT_RIGHT_BUTTON);              //마우스 오른쪽을 클릭하면 팝업창이 뜨게한다.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Menu Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);         //display 콜백함수 등록

	glutMainLoop();
	return 0;
}