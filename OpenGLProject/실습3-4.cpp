/***********************************************************************/
/*                           HW#3 :   Callback Programming                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 10�� 1��    */
/*                                                                                                 */
/* ���� ���� :  �޴� �ݹ� �Լ��� �̿��Ͽ� �޴� �����                     */
/*                - - - - - - -                                                                   */
/* ��� :    .�� �޴��� �ָ޴� : Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit �� 5���� �����,
              ������ �� �޴��� �Ʒ��� ���� �Ϻθ޴��� �����.
            Draw Sphere �Ϻ� �޴� : Small Sphere, Large Sphere   Draw Torus �Ϻ� �޴� : Small Torus , Large Torus			Draw Teapot �Ϻ� �޴� : Small Teapot , Large Teapot   Change Color �Ϻ� �޴� : Red, Green, Blue
			   �̶�, ��������� �簢���� ������â �ٱ����� �ȳ������� �������־���.      * /
			 /*                - - - - - - -                                                     */
			 /***********************************************************************/
#include <GL/glut.h>
//ũ�⿡ ���� ������ �����ϴ� ����
GLboolean IsSmall = true;
//���������� ������ �����ϴ� ����
GLint Object = 1;
//�������� ������ �����ϴ� ����
GLint COLOR = 0;
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	//���� ���� ������ �޴��ݹ��Լ��� ���� �����ϸ�,���������� ����ǰ�, ���÷��̿��� ����ȴ�.
	if(COLOR==0) //���� ������ �ִ� ���� color=0�̶�� ����
	glColor3f(0.0, 0.5, 0.5);
	else if(COLOR==1) glColor3f(255.0, 0.0, 0.0);   //������ color=1
	else if (COLOR == 2) glColor3f(0.0, 255.0, 0.0);  //�ʷ��� color=2.
	else glColor3f(0.0, 0.0, 255.0);                  //�Ķ��� color=3 �׷����� ���̻� ����̾��⶧���� else�� ǥ��

	//�Ϻθ޴��� �����ϸ� ������ �Ϻθ޴����� ��ü������ ������ �����ϴ� ������ �ִ�.
	//�׸��� �������� �����Ұ���,ū���� �����Ұ����� ���� �޴����� ���� ũ�⿡���� ������ �����ϴ� ������ �ִ�.
	switch (Object)
	{
	case 1:          //sphere
		if (IsSmall)                          //small�� ������ ���
			glutWireSphere(0.5, 30, 30);
		else                                   //large�� ������ ���
			glutWireSphere(0.7, 30, 30);
		break;
	case 2:             //tour
		if (IsSmall)                           //small�� ������ ���
			glutWireTorus(0.1, 0.3, 10, 10);
		else                                       //large�� ������ ���
			glutWireTorus(0.3, 0.5, 10, 10);
		break;
	case 3:             //teapot
		if (IsSmall)                    //small�� ������ ���
			glutWireTeapot(0.3);
		else                            //large�� ������ ���
			glutWireTeapot(0.5);
		break;
	}
	glFlush();
}
//�ָ޴� �ݹ��Լ� ���
void MyMainMenu(int entryID) {

	if (entryID == 1)       exit(0);
	//value���� 1�� ������ ȭ�� ����

	glutPostRedisplay();  //���� ������׵��� �ٷ� ���÷��̿� ����ǵ��� ������������ش�.
} 
//sphere������ �Ϻθ޴� �ݹ��Լ� ����
//�Ϻθ޴��� ���� ����� �����ϸ� �ش� value���� �ݹ��Լ��� ���´�.
//�׸��� �ش��ϴ� �ɼǿ� ���� ���÷��̰� �ٲ�� ���������� ���� �ٲ��ش�.
void MySphereMenu(int entryID) {
	Object = 1;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//torus�� ���� �Ϻθ޴� �ݹ��Լ� ����
//�Ϻθ޴��� ���� ����� �����ϸ� �ش� value���� �ݹ��Լ��� ���´�.
//�׸��� �ش��ϴ� �ɼǿ� ���� ���÷��̰� �ٲ�� ���������� ���� �ٲ��ش�.
void MyTorusMenu(int entryID) {
	Object = 2;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//teapot�� ���� �Ϻθ޴� �ݹ��Լ� ����
//�Ϻθ޴��� ���� ����� �����ϸ� �ش� value���� �ݹ��Լ��� ���´�.
//�׸��� �ش��ϴ� �ɼǿ� ���� ���÷��̰� �ٲ�� ���������� ���� �ٲ��ش�.
void MyTeapotMenu(int entryID) {
	Object = 3;
	if (entryID == 1)            IsSmall = true;
	else if (entryID == 2)      IsSmall = false;

	glutPostRedisplay();
}
//�������� �Ϻθ޴� �ݹ��Լ� ����
//�Ϻθ޴��� ���� ����� �����ϸ� �ش� value���� �ݹ��Լ��� ���´�.
//�׸��� �ش��ϴ� �ɼǿ� ���� ���÷��̰� �ٲ�� ���������� ���� �ٲ��ش�.
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
	//�Ϻθ޴����� �ش� ��ü�� small,large�� ǥ���ǵ��� ����
	//AddMenuEntry�� ���� �޴������ �߰��Ҽ��ִ�.
	//����� �Լ��� ���� ����� �����ϸ� �ݹ��Լ��� value���� �����ش�.

	//sphere�� ���� �Ϻθ޴� �޴� �ݹ��Լ� ���
	GLint MySphereMenuID = glutCreateMenu(MySphereMenu);
	glutAddMenuEntry("Small Sphere", 1);
	glutAddMenuEntry("Large Sphere", 2);

	//torus�� ���� �Ϻθ޴� �޴� �ݹ��Լ� ���
	GLint MyTorusMenuID = glutCreateMenu(MyTorusMenu);
	glutAddMenuEntry("Small Torus", 1);
	glutAddMenuEntry("Large Torus", 2);

	//teapot�� ���� �Ϻθ޴� �޴� �ݹ��Լ� ���
	GLint MyTeapotMenuID = glutCreateMenu(MyTeapotMenu);
	glutAddMenuEntry("Small Teapot", 1);
	glutAddMenuEntry("Large Teapot", 2);

	//color�� ���� �Ϻθ޴� �޴� �ݹ��Լ� ���
	GLint MyColorMenuID = glutCreateMenu(MyColorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	//�ָ޴��� ���� �޴� �ݹ��Լ� ���
	//�ָ޴��� 5���̹Ƿ� 5���� ������� ����
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	//�ָ޴������� �Ϻθ޴��� ����� ������ Addsubmenu�Լ��� ���� �󺧰��� id���� �־�����Ѵ�.
	glutAddSubMenu("Draw Sphere", MySphereMenuID);
	glutAddSubMenu("Draw Torus", MyTorusMenuID);
	glutAddSubMenu("Draw Teapot", MyTeapotMenuID);
	glutAddSubMenu("Change Color", MyColorMenuID);
	glutAddMenuEntry("Exit", 1);                   //Exit�� Ŭ���ϸ� value�� 1�� �ָ޴��ݹ��Լ��� ������
	glutAttachMenu(GLUT_RIGHT_BUTTON);              //���콺 �������� Ŭ���ϸ� �˾�â�� �߰��Ѵ�.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Menu Callback");
	MyInit();
	glutDisplayFunc(MyDisplay);         //display �ݹ��Լ� ���

	glutMainLoop();
	return 0;
}