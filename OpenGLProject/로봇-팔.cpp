/***********************************************************************/
/*                           HW#5 :   시점변환                                         */
/*  작성자 : 권성민                              날짜 : 2021년 10월 28일    */
/*                                                                                                 */
/* 문제 정의 :  <로봇손-팔>을 선택하여 다양한 시점에서 모델링된 객체 를 관찰할 수 있도록 수정                                            */
/*                - - - - - - -                                                                   */
/* 기능 :      아래는 기존 로봇손-팔의 기능
			<1 키를 누르면> 첫번째 손가락을 접었다 펼쳤다 반복
			<2 키를 누르면> 두번째 손가락을 접었다 펼쳤다 반복
			<3 키를 누르면> 세번째 손가락을 접었다 펼쳤다 반복
			<4 키를 누르면> 모든 손가락이 접었다 펼쳤다 반복
			<S 키를 누르면> 움직이던 손가락이 움직임을 멈춤
			추가 선택 기능
			<마우스 왼쪽 버튼을 클릭하면> 어깨, 팔꿈치 및 모든 손가락을 움직여서 Robot Arm이 특정 물건을 잡는 것처럼 회전
			여기서 한번더 클릭하면 잡는도중 멈추하는 기능을 추가하였음. 다시 클릭하면 잡는 회전을 이어서 실행
			잡는 행동은 한번만 실행하도록 설정
			<마우스 오른쪽 버튼을 클릭하면> 팔꿈치 및 모든 손가락을 움직여서 Robot Arm의 원래위치와 자세로 되돌아가도록 함.
			원래위치로 돌아간후 기존의 다른기능들을 수행가능
			손가락의 각도는 0~90도로 설정해주었다.
			팔꿈치의 각도는 0~40도로 설정해주었다.

			여기부터 시점변환

			↑ 키를 누르면 카메라의 시점이 위로간다.
			↓ 키를 누르면 카메라의 시점이 아래로간다.
			← 키를 누르면 카메라의 시점이 왼쪽으로 간다.
			→ 키를 누르면 카메라의 시점이 오른쪽으로 간다.

			기존에 마우스 왼쪽을 클릭하면 손가락을 접는 행동을 취하는데, 그때 카메라 시점이 왼쪽으로 움직이다가 접는행동을
			마쳤을때 카메라 이동을 멈춘다.
			기존에 마우스 오른쪽을 클릭하면 손가락을 펴는 행동을 취하는데, 그때 카메라 시점이 오른쪽으로 움직이다가
			(원래 자리로 이동) 손이 다 펴지면 카메라 이동을 멈춘다.
		
			위 아래를 확인할때 마우스 왼쪽 클릭을 통해 손가락이 접히는 방향을 보면 쉽게 확인할수 있다.																								*/

			 /*                - - - - - - -                                                                   */
			 /***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
//카메라 시점에 대한 변수

GLfloat focusx = 0;
GLfloat focusy = 0;
GLfloat focusz = 0;
//초점에 대한 변수

GLfloat camerax = 0;
GLfloat cameray = 1.5;
GLfloat cameraz = 1.5;
//카메라 위치에 대한 변수

int cameramoving = 0; //접고 펼때 카메라 움직을 나타내는 변수
int cameradir = 1;   //접고 펼때 카메라의 움직이는 방향을 나타내는 변수

int firstangle = 1;
int secondangle = 1;
int thirdangle = 1;
//손가락 관절의 각도 증가/감소을 알리는 변수

float first = 0.0;
float second = 0.0;
float third=0.0;
//각 손가락의 각도를 나타내는 변수, 기본값은 0.0으로 설정

int check = 0;
//손가락들의 기능을 나타내는 변수, 움직이지 않을때는 0이다.

int all = 0;
//손가락이 모두 움직일때를 나타내는 변수, 움직이지 않을때는 0이다.

int firststart = 0;
int secondstart = 0;
int thirdstart = 0;
//손가락이 한번 움직이게되면, 멈추기 전까지 계속 움직여야하는데, 이를 만족시켜주기 위해서 선언

int jobgi = 0;
//물건을 잡는 기능을 할때 그 값을 저장해주는 변수, 움직이지 않을때는 0이다.

int back = 0;
//원래 위치로 돌아가는 기능을 할때 그 값을 저장해주는 변수, 움직이지 않을때는 0이다.
float elbow = 0;
//잡는 기능을 할때, 팔꿈치를 움직여야되는데, 그 각도를 저장해주는 변수
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}
//display callback 함수 선언
void MyDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();   //기존의 위치를 저장하기 위해서 푸시 -> 여기를 기준으로 시작
	//모델뷰행렬에서 물체기준 제일 마지막에 곱해줘야하기때문에 제일 먼저 선언
	gluLookAt(camerax, cameray, cameraz, focusx, focusy, focusz, 0.0, 1.0, 0.0); //시점변환
	glTranslatef(-1.5, 1.5, 0.0); // 팔을 왼쪽부터 시작하기위해서 이동
	glTranslatef(-1.0, 0.0, 0.0); //객체 좌표이동
	glRotatef(-45, 0.0, 0.0, 1.0); //객체 회전
	glTranslatef(1.0, 0.0, 0.0);	//객체 좌표이동

	//위팔
	glPushMatrix();  //모델뷰행렬 푸시
	glColor3f(1.0, 1.0, 1.0);
	glScalef(2.0, 0.4, 1.0);    //객체 크기 변환
	glutWireCube(1.0);
	glPopMatrix(); //모델뷰행렬 팝

	//아래팔을 만들기위해서 좌표이동
	glTranslatef(1.0, 0.0, 0.0);  
	glRotatef(45, 0.0, 0.0, 1.0); // 위팔을 올리기 위해서 -45도를 해줬기때문에 0을 만들기 위해서 +45도 돌려줌
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0); //팔꿈치 관절 최대 40도 까지로 설정
	glTranslatef(1.0, 0.0, 0.0);

	//아래팔
	glPushMatrix();	//모델뷰 행렬 푸시
	glColor3f(1.0, 1.0, 1.0);
	glScalef(2.0, 0.4, 1.0); //객체 크기 변환
	glutWireCube(1.0);  //전완
	glPopMatrix(); //모델뷰 행렬 팝


	//아래팔과 연결되는 손가락 구현

	//가운데 손가락
		glPushMatrix(); //여기서 푸시를 해야 가운데 손가락을 만들고 다시 아래팔로 돌아옴
			glTranslatef(1.0, 0.0, 0.0);
			glRotatef((GLfloat)second,0.0, 0.0, 1.0); //1번째 마디
			glTranslatef(0.3 ,0.0, 0.0);
			glColor3f(1.0, 1.0, 1.0);

				//손가락마디
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)second, 0.0, 0.0, 1.0); //2번째 마디
			glTranslatef(0.3, 0.0, 0.0);
				
			    //손가락마디
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)second, 0.0, 0.0, 1.0); //3번째마디
			glTranslatef(0.3, 0.0, 0.0);
				
				//손가락마디
				glPushMatrix();
				glScalef(0.6, 0.4, 0.3);
				glutWireCube(1.0);
				glPopMatrix();

		glPopMatrix(); //가운데 손가락에 대한 행렬 삭제->아래팔로 돌아간다.

		//첫번째 손가락
		glPushMatrix(); //여기서 푸시를 해야 가운데 손가락을 만들고 다시 아래팔로 돌아옴
		glTranslatef(1.0, 0.0, -0.3);
		glRotatef(60, 0.0, 1.0, 0.0); //첫번째 손가락이 가운데 손가락과 겹치지 않게 하기위해서 회전
		glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //첫번째 마디
		glTranslatef(0.3, 0.0, 0.0);
			
			//손가락마디
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //2번째 마디
			glTranslatef(0.3, 0.0, 0.0);

			//손가락마디
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

			glTranslatef(0.3, 0.0, 0.0);
			glRotatef((GLfloat)first, 0.0, 0.0, 1.0); //3번째 마디
			glTranslatef(0.3, 0.0, 0.0);

			//손가락마디
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();

		glPopMatrix(); //첫번째 손가락에 대한 행렬 삭제->아래팔로 돌아간다.

	//세번째 손가락
		glPushMatrix(); //여기서 푸시를 해야 세번째 손가락을 만들고 다시 아래팔로 돌아옴
			glTranslatef(1.0, 0.0, 0.3);
			glRotatef(-50, 0.0, 1.0, 0.0); //세번째 손가락이 가운데 손가락과 겹치지 않도록 하기 위해서 회전
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //1번째 마디
			glTranslatef(0.3, 0.0, 0.0);

			//손가락마디
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();
			
			glTranslatef(0.3, 0.0, 0.0);
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //2번째 마디
			glTranslatef(0.3, 0.0, 0.0);

			//손가락마디
			glPushMatrix();
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();


			glTranslatef(0.3, 0.0, 0.0);
			glRotated((GLfloat)third, 0.0, 0.0, 1.0); //3번째 마디
			glTranslatef(0.3, 0.0, 0.0);

			//손가락마디
			glPushMatrix(); //크기에 대한 것
			glScalef(0.6, 0.4, 0.3);
			glutWireCube(1.0);
			glPopMatrix();


		glPopMatrix(); //세번째 손가락에 대한 행렬 삭제->아래팔로 돌아간다.

	glPopMatrix(); //맨 처음에 푸시해줫던 항등행렬로 돌아감

	glutSwapBuffers(); //스왑버퍼를 통해 front frame와 back frame을 바꿔준다(더블 버퍼링을 통한 유령현상 예방)
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);        //모델뷰 행렬 선언
	glLoadIdentity();                  //항등행렬로 초기화
	glTranslatef(0.0, 0.0, -5.0);
}
//keyboard callback 함수 선언
void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':               //첫번째 손가락 움직이기
		check = 1;
		break;
	case '2':              //가운데 손가락 움직이기
		check = 2;
		break;
	case '3':              //세번째 손가락 움직이기
		check = 3;
		break;
	case '4':              //모든 손가락 움직이기
		all = 1;
		break;
	case 's':             //모든 손가락 멈추기
		check = 0;
		all = 0;
		break;
	case 'S':              //모든 손가락 멈추기
		check = 0;
		all = 0;
		break;
	}
}
//스페셜키보드 콜백함수 선언
//방향키를 통해 카메라 시점을 바꾼다.
void MySpecial(int key, int x, int y) {
	//스페셜키보드(특수문자)는 정수형으로 정의되어있어서 int형 key 변수를 받는다
	switch (key) {
		//초점은 건드리지 않는다
	case GLUT_KEY_UP: //위에서 바라보기
		cameradir = 1;
		cameraz = 1.5;
		camerax = 0.0;
		cameray = 3;
		break;
	case GLUT_KEY_DOWN: //아래에서 바라보기
		cameradir = 1;
		cameraz = 1.5;
		camerax = 0;
		cameray = -2;
		break;
	case GLUT_KEY_LEFT:  //왼쪽에서 바라보기
		cameradir = 3;
		cameraz = 0;
		camerax = -1.5;
		cameray = 1;
		break;
	case GLUT_KEY_RIGHT: //오른쪽에서 바라보기
		cameradir = 2;
		cameraz = 0;
		camerax = 3.5;
		cameray = 3.5;
		break;
	//손이 접힐때는 카메라의 위치를 왼쪽으로, 손이 펴칠때(원상태로 돌아갈때는 카메라의 위치를 오른쪽으로 이동)
	}
}
//idle callback 함수 선언
void MyIdle()
{
	if (jobgi == 0)  //접기 기능을 실행하지 않았을때
	{
		if (check == 0)  //정지-> 모든손가락을 멈추게 하기위해서 0으로 초기화
		{
			firststart = 0;
			secondstart = 0;
			thirdstart = 0;
		}
		if (check == 1 || all)  //1또는 all일때 첫번째 손가락을 움직이게 하는 변수를 1로 만듬
		{
			firststart = 1;
		}
		if (firststart == 1)  //1을 받으면 첫번째 손가락이 계속 움직인다.
		{
			if (first >= 90)
			{
				firstangle = -1;
			}
			else if (first <= 0)
			{
				firstangle = 1;
			}

			if (firstangle == 1)
			{
				first = first + 0.1;
			}
			else
				first = first - 0.1;
		}
		if (check == 2 || all) //2 또는 all일때 가운데 손가락을 움직이게 하는 변수를 1로 만듬
		{
			secondstart = 1;
		}
		if (secondstart == 1)   //1이 되면 가운데 손가락을 계속 움직인다.
		{
			if (second >= 90)
			{
				secondangle = -1;
			}
			else if (second <= 10)
			{
				secondangle = 1;
			}

			if (secondangle == 1)
			{
				second = second + 0.1;
			}
			else
				second = second - 0.1;
		}
		if (check == 3 || all)  //3또는 all 일때 세번째 손가락을 움직이게 하는 변수를 1로 만듬
		{
			thirdstart = 1;
		}
		if (thirdstart == 1)  //변수가 1이 됬을때 세번째 손가락이 움직이는것을 반복
		{
			if (third >= 90)
			{
				thirdangle = -1;
			}
			else if (third <= 0)
			{
				thirdangle = 1;
			}

			if (thirdangle == 1)
			{
				third = third + 0.1;
			}
			else
				third = third - 0.1;
		}
		if (back == 1)  //우클릭을 했을때 손가락이 원래 위치로 돌아가야한다
		{
			//돌아가기전에 기존에 하던 기능을 정지
			check = 0;
			all = 0;
			//정지 시킨후 돌아가게한다.
			if (first > 0)
			{
				first = first - 0.03;
			}
			if (second > 0)
			{
				second = second - 0.03;
			}
			if (third > 0)
			{
				third = third - 0.03;
			}
			if (elbow > 0)
			{
				elbow = elbow - 0.015;
			}
			if (first < 0 && second < 0 && third < 0 && elbow<0) //모든 손가락이 돌아가면 돌아가는 상태를 멈춤
			{
				back = 0; //백을 하기전 0 상태로 돌아감
				cameramoving = 0; //손움직이 멈출때 카메라 움직임도 멈춘다.
			}
			if (cameramoving == 1) //손이 제자리로 돌아갈때 카메라 시점 변환
			{
				if (cameradir == 1)  //위,아래에 볼때
				{
					camerax = camerax + 0.001;  //손이 제자리로 돌아갈때 카메라 시점 변환
				}
				if (cameradir == 2) //오른쪽에서 볼때
				{
					cameraz = cameraz - 0.001;
				}
				if (cameradir == 3) //왼쪽에서 볼때
				{
					cameraz = cameraz + 0.001;
				}
			}
		}
	}
	//잡는 도중에는 다른 기능이 먹히지 않도록 설정
	else if (jobgi == 1)
	{
		if (cameramoving) //손이 접힐때 카메라 시점 변환
		{
			if (cameradir == 1)  //위,아래에 볼때
			{
				camerax = camerax - 0.001; 
			}
			if (cameradir == 2) //오른쪽에서 볼때
			{
				cameraz = cameraz + 0.001;
			}
			if (cameradir == 3) //왼쪽에서 볼때
			{
				cameraz = cameraz - 0.001;
			}

		}
		//잡기는 손가락은 90도 까지 팔꿈치는 40도 까지 잡는것으로 설정
		if (first < 90)
		{
			first = first + 0.03;
		}
		if (second < 90)
		{
			second = second + 0.03;
		}
		if (third < 90)
		{
			third = third + 0.03;
		}
		if (elbow < 40)
		{
			elbow = elbow + 0.015;
		}
		if (first >90 && second > 90 && third > 90 && elbow>40) //잡기가 다 끝나면
		{
			jobgi = 0; //잡기가 끝난다
			//잡기가 끝나고 기존에 눌렀던 버튼을 초기화
			check = 0;
			all = 0;
		}
		if (back == 1) //접는중에 원래위치로 가는 입력을 받으면
		{
			jobgi = 0; //접던중에 돌아가야된다면 접던것을 멈춘다.
		}

	}
	glutPostRedisplay(); //화면에 변화값이 생겼을때 바로 화면에 띄우기 위해서 선언
}
//mousce callback 함수 선언
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) //마우스 왼쪽 클릭이 눌린다면
	{
		jobgi += 1;                                        //잡기
		jobgi = jobgi % 2;
		cameramoving = 1;                                  //잡기도중에 카메라가 움직이는것을 확인하기위한 변수
	}
	if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)  //마우스 오른쪽 클릭이 눌린다면
	{
		back = 1;                             //원래 위치로 되돌린다.
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Robot Arm");
	MyInit();
	glutDisplayFunc(MyDisplay);    //display 콜백함수 등록
	glutReshapeFunc(MyReshape);     //reshape 콜백함수 등록
	glutKeyboardFunc(MyKeyboard);  //keyboard 콜백함수 등록
	glutMouseFunc(MyMouseClick);  //mouse 콜백함수 등록
	glutIdleFunc(MyIdle);         //idle 콜백함수 등록
	glutSpecialFunc(MySpecial);  //specialkeyboard 콜백함수 등록
	glutMainLoop();
	return 0;
}