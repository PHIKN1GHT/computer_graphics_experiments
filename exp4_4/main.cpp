#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>

int winWidth = 450, winHeight = 450;
int tetrahedron;
float roangles;

void Initial()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	tetrahedron = glGenLists(1);
	glNewList(tetrahedron, GL_COMPILE);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(3.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 3.0);
	glColor3f(1.0, 1.0, 1.0);
	glEnd();

	glLineWidth(4.0);
	glBegin(GL_TRIANGLES);
	double k = 7;
	glColor3f(1.0 * k, 1.0 * k, 1.0 * k);
	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);

	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	
	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);

	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);
	glEnd();
	glLineWidth(1.0);
	glEndList();
}

double dis = 4.0;
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 0.0, dis, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	glCallList(tetrahedron);
	glPopMatrix();

	glViewport(0, winHeight / 2, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glCallList(tetrahedron);
	glPopMatrix();

	glViewport(winWidth / 2, winHeight / 2, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glCallList(tetrahedron);
	glPopMatrix();
	
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(roangles, 0.0, 1.0, 0.0);
	glCallList(tetrahedron);
	glPopMatrix();

	glFlush();
}
 
void Reshape(int width, int height)
{
	winWidth = width; winHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 30.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IdleFunction()
{
	roangles += 0.03f;
	glutPostRedisplay();
}
 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(450, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutIdleFunc(IdleFunction);
	Initial();
	glutMainLoop();
	return 0;
}
