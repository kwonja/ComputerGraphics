/***********************************************************************/
/*                           HW#7 :   조명                                         */
/*  작성자 : 권성민                              날짜 : 2021년 11월 17일    */
/*                                                                                                 */
/* 문제 정의 :  전신 Can Robot 모델링에 달리는 기능과 조명을 입히시오.                                            */
/*                - - - - - - -                                                                   */
/* 기능 :   	<R 또는 r 키를 누르면> 양팔과 양다리를 적절히 움직여 달리는 모습이 되게하시오.
                 로봇에 조명을 입히시오.
				<달리는 도중(r,R키를 누른후) S 또는 s 키를 누르면> 시점 변환을 통해 물체에 빛을 비추는 위치가 바뀌도록 설정																						*/
			/*                - - - - - - -                                                                   */
			/***********************************************************************/
#include <stdlib.h>
#include <GL/glut.h>
GLUquadricObj *qobj = gluNewQuadric();        //실린더를 구현하기위해서 객체 생성

int check = 0; //물체의 달리는 동작을 실행시키는 변수
int value = 0; //물체의 시점변환여부를 확인하는 변수

//처음에 차렷 자세에서 시작한다.

//오른팔 관련 변수
GLfloat rightarm = 0; //어깨각도
GLfloat rightelbow = 0; //팔꿈치 각도
int rightangle = 0; //오른팔,왼발의 이동 방향

//왼팔 관련 변수
GLfloat leftarm = 0;       //어깨 각도
GLfloat leftelbow = 0;     //팔꿈치 각도
int leftangle = 1;         //왼팔,오른발의 이동방향

//오른다리 관련 변수
GLfloat rightleg = 0;      //골반
GLfloat rightknee = 0;     //무릎

//왼다리 관련 변수
GLfloat leftleg = 0;       //골반
GLfloat leftknee =0;       //무릎

GLfloat leftright = 0;      //몸의 흔들림의 각도
int change = 0;             //몸의 흔들리는 방향

GLfloat lightmove = 0.5;
void MyInit(void) {
	GLfloat MyLightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; // IaR , IaG , IaB 주변반사광은 검은색->그림자를 위해서
	GLfloat MyLightDiffuse[] = { 1.0, 1.0,1.0, 1.0 }; // IdR , IdG , IdB 난반사광은 주로 백색->물체의 색을 그대로 받기 위해서
	GLfloat MyLightSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; // IsR , IsG , IsB 정반사광은 주로 백색->하이라이트를 표시

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };                 //주변반사 계수 
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.0, 1.0 };                 //난반사 계수->물체의 기본이 되는 색
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };                //정반사 계수->물체에 대한 빛의 반사 정도
	GLfloat mat_shininess[] = { 10.0 };                      //정반사의 광택 계수-> 계수가 커질수록 하이라이트 크기가 줄어든다.
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };          //발광체 물체 스스로 빛을 내는데, 수치가 올라가면더 밝아진다.
	GLfloat light_position[] = { 1.0, 0.5, 0.5, 1.0 };       // 광원의 위치
	GLfloat model_ambient[] = { 0.3, 0.0, 0.0, 1.0 };         //0.3,0,0 의 은은한 색을 추가했음(은은한 빨간색)

	glLightfv(GL_LIGHT0, GL_AMBIENT, MyLightAmbient);  //주변반사
	glLightfv(GL_LIGHT0, GL_DIFFUSE, MyLightDiffuse);  //난반사
	glLightfv(GL_LIGHT0, GL_SPECULAR, MyLightSpecular); //정반사
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//물체의 표면에 따른 특성
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  //표면에 대한 주변반사
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //표면에 대한 정반사
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);     //표면에 대한 난반사
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);       //표면에 대한 광택계수
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);        //발광체
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);        //광원의 위치
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);  //전역주변 광원 색 설정-> 광원에 대해서 영향을 받지 않음
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);    //관찰자의 시점 위치->각각의 시점벡터를 계산

	//은면 제거
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);         //광원 활성화
	glEnable(GL_LIGHT0);           //0번 광원 활성화
	//glEnable(GL_COLOR_MATERIAL);    //물체의 색 활성화

}
//display callback 함수 선언
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          //깊이 버퍼 기능 사용
	glShadeModel(GL_SMOOTH);              //물체의 음영을 부드럽게 설정
	gluQuadricDrawStyle(qobj, GLU_FILL); //객체를 그림으로 채운다.
	gluQuadricNormals(qobj, GLU_SMOOTH);    //객체면을 부드럽게 그린다.법선벡터 제어
	gluQuadricOrientation(qobj, GLU_OUTSIDE);  //바깥쪽을 가리키는 법선벡터를 그린다.
	gluQuadricTexture(qobj, GL_FALSE);          //텍스트 좌표를 사용하지 않는다.

	glMatrixMode(GL_MODELVIEW); //모델뷰 행렬 을 받기 위해 선언
	glLoadIdentity();             //항등행렬로 초기화
	glPushMatrix();
	gluLookAt(0, 0, 0, lightmove, 1, 0.1, 0, 0, 1);
	glRotatef(leftright,0.0, 1.0, 0.0); //실린더를 잘 보이게하기위해서 선언
	//객체관련 설정 지정

	glTranslatef(0.0, 0.0, 1.2); //머리와 목의 연결부분
		//머리만 따로 회전해야되기때문에 이동후 물체 생성부분에 push pop을 해줌
	glPushMatrix();
	glRotatef(0, 0, 1, 0);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.5, 0.3, 0.6, 20, 8); //머리

	//오른쪽 눈
	glPushMatrix();
	glColor3f(1,1, 1);
	glTranslatef(0.15, -0.35, 0.4);
	glRotatef(90, 1.0, 0.0, 0.0); //디스크를 잘 보이게하기위해서 선언
	gluSphere(qobj, 0.1, 20, 20);
	glPopMatrix();

	//왼쪽 눈
	glPushMatrix();
	glTranslatef(-0.15, -0.35, 0.4);
	glColor3f(1, 1, 1);
	glRotatef(90, 1.0, 0.0, 0.0); //디스크를 잘 보이게하기위해서 선언
	gluSphere(qobj, 0.1, 20, 20);
	glPopMatrix();

	glPopMatrix(); //머리에 대해 이어진 행렬을 pop -> 그래야 목으로 돌아온다.
				  //눈 부분이 머리행렬 안에 있는 이유는 머리가 움직이면 눈도 같이 움직이기때문


	glTranslatef(0.0, 0.0, -0.2); //목과 몸의 연결부분
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(qobj, 0.2, 0.2, 0.2, 20, 8); //목 생성

	glTranslatef(0.0, 0.0, -1.2); //목아래 몸통이랑 이어져 있는 부분으로 이동
	glColor3f(1.0, 1.0, 1.0);
	gluCylinder(qobj, 0.8, 0.8, 1.2, 20, 8); //몸통 생성 현재 msd는 몸통 제일 아래쪽 중심에 위치해있다.


	//오른쪽 팔
	glPushMatrix();
	glTranslatef(0.8, 0.0, 1.1);
	glRotatef(rightarm, 1.0, 0.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(0, 1, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	glRotatef(rightelbow, 1.0, 0.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(1, 1, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	//손
	glTranslatef(0.0, 0.0, -0.1);
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//몸통 좌표로 다시 돌아옴

	//왼쪽 팔
	glPushMatrix();
	glTranslatef(-0.8, 0.0, 1.1);
	glRotatef(leftarm, 1.0, 0.0, 0.0); //어깨 각도
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(0, 0.8, 0.2);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	glRotatef(leftelbow, 1.0, 0.0, 0.0); //팔꿈치 각도
	glTranslatef(0.0, 0.0, -0.6);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.6, 20, 8);
	//손
	glTranslatef(0.0, 0.0, -0.1);
	gluSphere(qobj, 0.2, 15, 15);
	glPopMatrix();
	//몸통 좌표로 다시 돌아옴

	//왼쪽 다리
	glPushMatrix();
	glTranslatef(-0.4, 0.0, 0.0);
	glRotatef(leftleg, 1.0, 0.0, 0.0); //왼쪽 다리 각도
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1, 0, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glRotatef(leftknee, 1.0, 0.0, 0.0); //왼쪽 다리 무릎 각도
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(-0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 1.0);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();


	//오른쪽 다리 생성
	glPushMatrix();
	glTranslatef(0.4, 0.0, 0.0);
	glRotatef(rightleg, 1.0, 0.0, 0.0);  //오른쪽 다리 각도
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1, 0, 1);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glRotatef(rightknee, 1.0, 0.0, 0.0);  //오른쪽 다리 무릎 각도
	glTranslatef(0.0, 0.0, -0.5);
	glColor3f(1.0, 1.0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 20, 8);
	glTranslatef(0.1, 0.0, -0.1);
	glColor3f(0.0, 0.0, 1.0);
	gluCylinder(qobj, 0.3, 0.3, 0.1, 20, 8);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers(); //스왑버퍼를 통해 front frame와 back frame을 바꿔준다(더블 버퍼링을 통한 유령현상 예방)
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//키보드 콜백함수 선언
void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)  //r,R를 누르게되면 물체가 달리게 된다. s,S를 누르게되면 시점이 변한다.
	{
	case 'r':
	case 'R':
		check = 1;           //물체가 달린다.
		break;
	case 's':
	case 'S':
		value = 2;             //시점이 변화한다.
		break;
	}
}
//idle 콜백함수 선언 
void MyIdle()
{

	if (check == 1) //달리기 시작
					//몸앞에서 60도 일때 5도씩 움직이면 12번 움직이고, 몸뒤에서 36도 일때 3도씩 움직이면 12번 움직인다.
					//이렇게 앞뒤 횟수를 맞춰 같은시간때에 왼팔과 오른팔, 왼다리 오른다리가  몸 중앙(0도)에서 만나도록 설정
	{
			//오른팔 움직이기
			if (rightarm < -60 || rightarm>36)   //앞으로 60도까지 가고 뒤로 36도 까지간다.
			{
				rightangle += 1;                 //-60이하,36이상가면 방향 바꾸기
				rightangle = rightangle % 2;
			}
			if (rightangle == 0)      //오른팔이 앞으로 간다
			{
				if (rightarm < 0)                      //몸앞
				{
					rightarm = rightarm - 0.05;        //어깨가 앞으로 나오면서
					rightelbow = rightelbow - 0.06;    //팔꿈치도 굽혀 손이 위로 올라간다.
				}
				if (rightarm >= 0)                    //몸뒤
				{
					rightarm = rightarm - 0.03;       //어깨가 뒤로감
					rightelbow = 0;                   //뒤로갈때는 팔꿈치를 편다
				}
			}
			if (rightangle == 1)  //오른팔이 뒤로간다
			{
				if (rightarm < 0)                          //몸앞
				{
					rightarm = rightarm + 0.05;            //앞으로 나간 어깨를 뒤로 되돌린다.
					rightelbow = rightelbow + 0.06;         //팔꿈치도 접는다.
				}
				if (rightarm >= 0)                         //몸뒤
				{
					rightarm = rightarm + 0.03;             //몸 중앙 기준 36도까지 뒤로간다.
					rightelbow = 0;                        //팔꿈치가 몸 중앙에 오고난뒤는 편상태로 뒤로 이동
				}
			}
			
			//왼팔 움직이기
			if (leftarm < -60 || leftarm>36)  //앞으로 60도까지 가고 뒤로 36도 까지간다.
			{
				leftangle += 1;                    //-60이하,36이상가면 방향 바꾸기
				leftangle = leftangle % 2;
			}
			if (leftangle == 0) //왼팔이 앞으로 나갈때
			{
				if (leftarm < 0)                     //몸앞
				{
					leftarm = leftarm - 0.05;      //어깨 앞으로 보내기
					leftelbow = leftelbow - 0.06; //팔 구부리기
				}
				if (leftarm >= 0)                 //몸뒤
				{
					leftarm = leftarm - 0.03;         //어깨 앞으로 보내기
					leftelbow = 0;                   //팔을 편상태로 고정
				}
			}
			if (leftangle == 1) //왼팔이 뒤로 갈때
			{
				if (leftarm < 0)              //몸앞
				{
					leftarm = leftarm + 0.05;     //앞으로 나간 어깨를 뒤로 되돌리기
					leftelbow = leftelbow + 0.06; //팔 펴기
				}
				if (leftarm >= 0)
				{
					leftarm = leftarm + 0.03;     //어깨 뒤로 보내기
					leftelbow = 0;     //팔을 편상태로 고정
				}
			}

			//오른쪽 다리 움직이기
			//앞으로 나갈때는 약 48도 만큼 뒤로는 약 36도 만큼 움직이도록 설정

			if (leftangle == 0)     //왼팔이랑 같이 앞으로 나간다.
			{
				if (rightleg >= 0) // 몸뒤
				{
					rightleg = rightleg - 0.03;       //달릴때 다리가 몸뒤로도 가기때문에 약 36도 까지 뒤로감
					rightknee = 0;                   //제자리에 오면 무릎 세우기
				}
				if (rightleg < 0) //몸앞
				{
					rightleg = rightleg - 0.04;    //골반을 굽혀 앞으로 가는거 처럼 만든다(약 48도까지)
					rightknee = rightknee + 0.06; //앞에서는 무릎이 굽혀진다. 약 72도 까지 올라가도록 설정
				}
			}
			if (leftangle == 1) //오른쪽 다리가 뒤로 돌아올때
			{
				if (rightleg >= 0) //몸 뒤
				{
					rightleg = rightleg + 0.03;  //몸 뒤에 있을때 다리 뒤로가기
					rightknee = 0;  //제자리에 오면 무릎세우기
				}
				if (rightleg < 0) //몸 앞
				{
					rightleg = rightleg + 0.04;   //몸 앞에 있을때 다리 뒤로가기
					rightknee = rightknee - 0.06;  //다 달리고 나서 돌아올때 무릎이 펴진다.
				}
			}
			//왼쪽 다리 움직이기
			if (rightangle == 0)   //왼쪽다리가 앞으로 나갈때(오른팔이 앞으로 나갈때)
			{
				if (leftleg >= 0)      //몸뒤
				{
					leftleg = leftleg - 0.03; //몸뒤에서 앞으로 다리가 나온다
					leftknee = 0;  //제자리에 오면 무릎세우기
				}
				if (leftleg < 0)
				{
					leftleg = leftleg - 0.04;    //몸 중앙에서 몸앞으로 다리가 나온다
					leftknee = leftknee + 0.06; //앞에서는 무릎이 굽혀진다. 약 72도 까지 올라가도록 설정(0.06도씩 12000번)
				}
			}
			if (rightangle == 1) //왼쪽다리가 앞으로 갔다가 뒤로 돌아올때
			{
				if (leftleg >= 0) //몸 뒤
				{
					leftknee = 0;  //제자리에 오면 무릎세우기
					leftleg = leftleg + 0.03;  //몸중앙에서  다리가 뒤로간다.
				}
				if (leftleg < 0)  //몸 앞
				{
					leftleg = leftleg + 0.04;       //몸 앞에서 중앙까지 다리가 뒤로간다.
					leftknee = leftknee - 0.06; //다 달리고 나서 돌아올때 무릎이 펴진다.
				}
			}
			//몸통 흔들기
			//중앙 기준 0.005도 씩 12000번 이동하도록 만들어 팔이 움직였다가 차렷 자세로 돌아오면 다시 정면을 바라보도록 맞춰줌
			if (leftright > 6 || leftright < -6) //-6~6도 까지 몸을 흔든다.
			{
				change += 1;                      //각도를 넘으면 방향전환
				change = change % 2;
			}
			if (change==0)   //오른쪽으로 갈때
			{
				leftright = leftright + 0.005;
				if (value == 2)
				{
					lightmove = lightmove + 0.0005;               //시점 변환
				}
			}
			else
			if (change==1)  //왼쪽으로 갈때
			{
				leftright = leftright - 0.005;
				if (value == 2)
				{
					lightmove = lightmove - 0.0005;               //시점 변환
				}
			}
	
	}
	glutPostRedisplay(); //위에 변경사항을 바로 화면에 띄우게한다.
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //깊이 버퍼 기능 사용
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Primitives");
	MyInit();
	glutDisplayFunc(MyDisplay); //display 콜백함수 등록
	glutReshapeFunc(Reshape);  //reshape 콜백함수 등록
	glutIdleFunc(MyIdle);       //idle 콜백함수 등록
	glutKeyboardFunc(MyKeyboard);  //keyboard 콜백함수 등록
	glutMainLoop();
	return 0;
}