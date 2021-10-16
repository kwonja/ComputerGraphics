/***********************************************************************/
/*                           HW#2 :   GLU Modeling – 3D Primitives 구현                                       */
/*  작성자 : 권성민                              날짜 : 2021년 9월 24일    */
/*                                                                                                 */
/* 문제 정의 :  코드4-5와 코드4-7을 참고하여 다음과 같은 3D Primitive 구현 : Sphere, Cylinder, Disk, PartialDisk                                                                        */
/*                - - - - - - -                                                                   */
/* 기능 :  Diskplay List 를 사용해서 Sphere, Cylinder, Disk, PartialDisk 구현																				  */
/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
GLUquadricObj *qobj = gluNewQuadric();          // 새로운 Quadric Object 생성
int MyListID[4];                                 //display list를 사용하기위해서 선언 4가지를 저장하기위해 4크기로 지정함
int number;                                      //각각의 숫자를 저장하기위해 선언

//반복적으로 실행되어야 할 요소를 디스플레이 리스트 내부에 포함,display list를 생성
void MyCreateList() {
	MyListID[0] = glGenLists(4);   //아이디 할당,DisplayList는 정수 ID에 의해 식별
	MyListID[1] = MyListID[0] + 1; 
	MyListID[2] = MyListID[1] + 1;
	MyListID[3] = MyListID[2] + 1;
	//각각 1씩 더해주어 총 4개의 아이디를 할당해줌
	glNewList(MyListID[0], GL_COMPILE);            //MyListID[0]에 대한 리스트 생성

	//리스트를 구성하는 함수 나열
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);                //조명
	glShadeModel(GL_SMOOTH);              //부드럽게 칠하기
	gluQuadricDrawStyle(qobj, GLU_FILL);            //solid 형태로 반시계방향으로 그려진다.
	gluQuadricNormals(qobj, GLU_SMOOTH);           //객체의 모서리가 부드럽게 보이도록 법선벡터를 생성
	gluQuadricOrientation(qobj, GLU_OUTSIDE);      //바깥 쪽을 가리키는 벡터를 가진 Quadric을 그린다
	gluQuadricTexture(qobj, GL_FALSE);             //텍스트좌표를 사용하지 않는다.
	gluSphere(qobj, 1.0, 50, 50);                  //원 모양의 객체
	glEndList();                                 //생성한 리스트의 끝을 표기

	glNewList(MyListID[1], GL_COMPILE);          //MyListID[1]에 대한 리스트 생성
	//리스트를 구성하는 함수 나열
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	gluQuadricDrawStyle(qobj, GLU_LINE);       //Wire-frame 형태로 모델링->선으로 표시된다.
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluCylinder(qobj, 1.0, 1.0, 2.0, 20, 8);      //원기둥 모양의 객체
	glEndList();                                 //생성한 리스트의 끝을 표기

	glNewList(MyListID[2], GL_COMPILE);        //MyListID[2]에 대한 리스트 생성
	//리스트를 구성하는 함수 나열
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);       //선으로 표시되는데, 외부 모서리만 선으로 표시
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluDisk(qobj, 0.5, 1.5, 20, 3);         //디스크 모양의 객체
	glEndList();                           //생성한 리스트의 끝을 표기

	glNewList(MyListID[3], GL_COMPILE);      //MyListID[3]에 대한 리스트 생성
	//리스트를 구성하는 함수 나열
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	gluQuadricDrawStyle(qobj, GLU_POINT);           //객체를 점으로 표시
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluPartialDisk(qobj, 0.5, 1.5, 26, 13, 180,180);        //디스크의 부분을 나타낼수 있는 객체->현재 반쪽을 구현
	glEndList();                                            //생성한 리스트의 끝을 표기
}
//질문
void MyInit(void) {
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void MyDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //윈도우창에 있는 그림버퍼를 지우는것
	//디스크에 4개를 저장했기때문에 각각의 그림을 보기위해서 따로 만들었다.
	cout << "1,2,3,4중 원하시는 모델의 숫자를 선택하세요 " << endl;
	cout << "숫자를 입력하세요 : ";
	cin >> number;
	glCallList(MyListID[number-1]);           //디스크 리스트 내부에 컴파일된 내용들을 실행시킨다
	glutSwapBuffers();                        //현 프레임 버퍼 변경
	glFlush();                               //밀린 작업들을 한번에 실행시킨다.
}

//원도우창 크기에 대해서 왜곡현상이 일어나지 않도록 방지하기위해 Reshape 함수 선언
void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glRotatef(290, 0, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutInitWindowPosition(0, 0);
		//사이즈가 800,600 이고 0,0을 시작으로하는 윈도우 초기화
		glutCreateWindow("Graphics Primitives");
		//타이틀이 Graphics Primitives인 원도우 생성
		MyInit();
		MyCreateList();               //display list를 생성하는 함수
		glutDisplayFunc(MyDisplay); //display callback함수 등록
		glutReshapeFunc(Reshape);   //Reshape calloback함수 등록
		glutMainLoop();    //사용자나 시스템에 의해 발생한 메시지를 받아 메시지 처리 함수를 호출하는 중요한 역할을 한다
	return 0;
}