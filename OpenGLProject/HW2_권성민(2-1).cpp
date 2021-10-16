/***********************************************************************/
/*                           HW#2 :   GL Modeling - 2D Primitive���� ����                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 9�� 24��    */
/*                                                                                                 */
/* ���� ���� :  �ڵ�4-2�� �����Ͽ� ������ ���� 2D Primitive���� ����                                                                        */
/*                - - - - - - -                                                                   */
/* ��� :   Points, Lines, LineStrip, LineLoop,TrangleFan, Triangles, TriangleStrip,Polygons, Quads, QuadStrip�� ���� 2D Primitive�� ����                                                                                   */
/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <GL/glut.h>

//GL_POINTS �� ���� MyDisplay
//6���� ���� ��´�.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.5, 0.4, 0.3);
	glPointSize(10.0);  //���������� Ȯ���ϱ����ؼ� ũ�⸦ �÷���
	glBegin(GL_POINTS);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();


	glFlush();
}
/*
//GL_LINES �� ���� MyDisplay
//������� 2���� ������ ���� �����ȴ�.
void MyDisplay( ) {
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0.5, 0.4, 0.3);
		 glBegin(GL_LINES);
		 glVertex3f(-0.5, -1.0, 0.0);
		 glVertex3f(0.5, -1.0, 0.0);
		 glVertex3f(1.0, 0.0, 0.0);
		 glVertex3f(0.5, 1.0, 0.0);
		 glVertex3f(-0.5, 1.0, 0.0);
		 glVertex3f(-1.0, 0.0, 0.0);
		 glEnd();

     glFlush();
}
*/

/*
//GL_LINE_STRIP �� ���� MyDisplay
//ó�� ������ �ݽð� �������� �������� ������ ���� ���. ��, �Ǹ����� ���� ���� �������� �ʴ´�. 
	void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	//glBegin(GL_LINES);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
//GL_LINE_LOOP �� ���� MyDisplay
//���� ���� �ݽð�������� ������ ���� ���
	void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	//glBegin(GL_LINES);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_POLYGON �� ���� MyDisplay
//���� ���� ������� ��翡 ���� ĥ��ä�� ����->�ٰ����� �����.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
void MyDisplay() {
	//GL_TRIANGLES �� ���� MyDisplay
	//������� 3���� ���� �̿��� �ﰢ�� ������ �����.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5, -1.0, 0.0);
	glVertex3f(0.5, -1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glVertex3f(-0.5, 1.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/

/*
//GL_TRIANGLE_STRIP �� ���� MyDisplay
//�� 3���� ���� �ﰢ������ ��� �����Ѵ�.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1, -0.3, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(-0.5, 0.7, 0.0);
	glVertex3f(-1.0, -0.1, 0.0);
	glVertex3f(-1.5, 0.4, 0.0);
	glVertex3f(-2.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_TRIANGLE_FAN �� ���� MyDisplay
//�ﰢ������ ��ä������� �����Ѵ�
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(0.6, -1.0, 0.0);
	glVertex3f(0.7, -0.3, 0.0);
	glVertex3f(0.4, 0.5, 0.0);
	glVertex3f(0.1, 0.8, 0.0);
	glVertex3f(-0.3, 1.0, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_QUADS �� ���� MyDisplay
//���� 4���� ��� 4���� �������� ���� POLYGON�� �����.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_QUADS);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.0);
	glEnd();

	glFlush();
}
*/
/*
//GL_QUAD_STRIP �� ���� MyDisplay
//�簢������ ��� �����Ѵ�.
//�簢���� �̾���̱� ���� V2,V3�� �ٲٰ�, V6,V7�� �ٲ��־���.
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.4, 0.3);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(-0.5, 0.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glEnd();

	glFlush();
}
*/
int main(int argc, char** argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGBA);
     glutInitWindowSize(500, 500);
     glutInitWindowPosition(0, 0);
	 //����� 500,500 �̰� 0,0�� ���������ϴ� ������ �ʱ�ȭ
     glutCreateWindow("Graphics Primitives");  //Ÿ��Ʋ�� Graphics Primitives�� ������ ����
     glClearColor(1.0, 1.0, 1.0, 1.0);
     glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
     glutDisplayFunc(MyDisplay);           //display callback�Լ� ���

     glutMainLoop( ); //����ڳ� �ý��ۿ� ���� �߻��� �޽����� �޾� �޽��� ó�� �Լ��� ȣ���ϴ� �߿��� ������ �Ѵ�
     return 0;
}