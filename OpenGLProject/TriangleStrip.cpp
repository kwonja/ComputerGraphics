/***********************************************************************/
/*                           HW#2 :   GL Modeling - 2D Primitive���� ����                                         */
/*  �ۼ��� : �Ǽ���                              ��¥ : 2021�� 9�� 24��    */
/*                                                                                                 */
/* ���� ���� :  �ڵ�4-2�� �����Ͽ� ������ ���� 2D Primitive���� ����                                                           */
/*                - - - - - - -                                                                   */
/* ��� : TriangleStrip�� ���� 2D Primitive�� ����                                                 */
/*                - - - - - - -                                                                   */
/***********************************************************************/
#include <GL/glut.h>
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

	glutMainLoop(); //����ڳ� �ý��ۿ� ���� �߻��� �޽����� �޾� �޽��� ó�� �Լ��� ȣ���ϴ� �߿��� ������ �Ѵ�
	return 0;
}