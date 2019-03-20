#include <GL/glut.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

int winWidth = 450, winHeight = 450;
int tetrahedron;
float roangles;
unsigned char mask[8 * 16];
int maskSize = 8;
int maskType = 0;

void Initial()
{
	memset(mask, 0, sizeof(mask));
	for (int i = 0; i < 32; i++)
		for (int j = 0; j < 32; j++)
			mask[i*4+j/8] |= (((i%maskSize^(j%maskSize))<(maskSize>>1)) << (j%8));

	tetrahedron = glGenLists(1);
	glNewList(tetrahedron, GL_COMPILE);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(233.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 233, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 233);
	glColor3f(1.0, 1.0, 1.0);
	glEnd();

	double k = 233;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	glVertex3f(0.2 * k, 0.1 * k, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.1 * k, 0.1 * k, 0.1 * k);
	glVertex3f(0.2 * k, 0.0, 0.0);
	glVertex3f(0.0, 0.1 * k, 0.0);
	glEnd();


	glEndList();
}

double dis = 120.0;
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (!maskType) {
		glEnable(GL_POLYGON_STIPPLE);
		glPolygonStipple(mask);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	

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
	gluLookAt(40, 40, 40, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(roangles, 0.0, 1.0, 0.0);
	glCallList(tetrahedron);
	glPopMatrix();
	if (!maskType) {
		glDisable(GL_POLYGON_STIPPLE);
	}
	glFlush();
}
 
void Reshape(int width, int height)
{
	winWidth = width; winHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.0f, 255.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IdleFunction()
{
	roangles += 0.03f;
	glutPostRedisplay();
}

void ProcessMenu(int value) {
	maskType = value - 1;
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
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Mask", 1);
	glutAddMenuEntry("NoMask", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutIdleFunc(IdleFunction);
	Initial();
	glutMainLoop();
	return 0;
}
