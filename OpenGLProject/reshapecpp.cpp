/***********************************************************************/
/*                           HW#1 : 3D Sierpinski Gasket ����                                     */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 9�� 18��    */
/*                                                                                                 */
/* ���� ���� :  OpenGL�� ���� 3D Sierpinski Gasket ����                                                                           */
/*                - - - - - - -                                                                   */
/* ��� :  p���� �����鼭 3D �����ü�� �����.                                                                                   */
/*                - - - - - - -                                                                   */
/***********************************************************************/

#include <GL/glut.h>   //glut�� ����ϱ����� ����
#include <stdlib.h>  //rand() �Լ� ��� �뵵

/*void MyInit()  //���� �� ȸ���� ����� ���� ����� ���� �Լ�
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // �Ͼ������� ����
	glColor3f(3.0, 0.0, 0.0); // ���������� ����
	glMatrixMode(GL_PROJECTION);  //��������� ����ϱ����� ����
	glLoadIdentity();             //������� �ʱ�ȭ
	glOrtho(0.0, 500.0, 0.0, 500.0, 0, -500);     //��ĺ�ȯ
	//���ú��ǿ� �����ü�� ������ؼ� 500�� �������� ������
	glRotatef(20.0, 1.0, 1.0, 0.0);  //1,1,0 ���� �������� 20����ŭ ��ü�� ȸ����Ų��.

}
*/
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);                   //os�� �����ִ� ȭ�� ũ�⿡ �°� ������ ���ش�.
	glClearColor(1.0, 1.0, 1.0, 1.0); // �Ͼ������� ����
	glColor3f(3.0, 0.0, 0.0); // ���������� ����
	GLfloat Widthfactor = (GLfloat)NewWidth / (GLfloat)500;     //�����ü�� �������� 500���� �����߱� ������ 500���� ������ ������ �����ش�.
	GLfloat Heightfactor = (GLfloat)NewHeight / (GLfloat)500;   //�����ü�� �������� 500���� �����߱� ������ 500���� ������ ������ �����ش�.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//������ ������ 500�� ���ؼ� ���ú��Ǿȿ� ���� ���ü�� ������ �����ش� -> �� ������ ���� �ְ������� ���´�.
	glOrtho(0.0*Widthfactor, 500.0*Widthfactor, 0.0*
		Heightfactor, 500.0*Heightfactor, 0.0, -500.0);
	//near, far�� 0,-500 ���� ������Ų ������ ȭ�鿡 ���̴°� 2D �̱⶧���� �յڴ� �ְ����� �ش���� �ʴ´�.
	glRotatef(20.0, 1.0, 1.0, 0.0);      //1,1,0 ���� �������� 20����ŭ ��ü�� ȸ����Ų��.         
}

void MyDisplay(void)
{
	float vertices[4][3] = { { 0.0,0.0,0.0 },{ 250.0,500.0,0.0 },{ 500.0,0.0,0.0 },{250.0,0.0,500.0} };
	//�ʱ� ���𿡼� 3�������� ���̰� �Ϸ��� �� �Ѱ��� �� �� ���ü ������� ���������Ѵ�.
	int i, j;
	float p[3] = { 250.0, 250.0,250.0 };  // ���� ����Ʈ
	//3���� ��ǥ�� ����ϱ� ������ z��ǥ�� �߰��ߴ�.

	glClear(GL_COLOR_BUFFER_BIT);   //Clear�� ���� �����ʱ�ȭ(������ȭ�鿡 �ִ� �׸��� �����.)
	for (j = 0; j < 100000; j++)
	{
		i = rand() % 4; // ������ ���� -> ���� 4���� �����ؼ� 3->4�� �ٲ���Ѵ�.
		// ���� ���õ� ���� ���� ���� �������� ���ο� �� ��ġ ��� 
		p[0] = (p[0] + vertices[i][0]) / 2.0; //���ο� ���� x��
		p[1] = (p[1] + vertices[i][1]) / 2.0; //���ο� ���� y��
		p[2] = (p[2] + vertices[i][2]) / 2.0; //���ο� ���� z��

		glBegin(GL_POINTS);  //begin����  �������� ���� ��� Ÿ���� ����
		glVertex3fv(p); // ���� ��ġ�� �� ���  �� ��ǥ�� �þ�� ������ 2fv->3fv ���� ����������Ѵ�.
		glEnd();
	}
	//�������� ���� ���� �����鼭 �����ü�� ȭ�鿡 ����Ѵ�.

	glFlush();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	//����� 500,500 �̰� 0,0�� ���������ϴ� ������ �ʱ�ȭ
	glutCreateWindow("Sierpinski Gasket");   //Ÿ��Ʋ�� Sierpinski Gasket�� ������ ����
	glutDisplayFunc(MyDisplay);               //display callback�Լ� ���
	glutReshapeFunc(MyReshape);
	glutMainLoop(); //����ڳ� �ý��ۿ� ���� �߻��� �޽����� �޾� �޽��� ó�� �Լ��� ȣ���ϴ� �߿��� ������ �Ѵ�
}