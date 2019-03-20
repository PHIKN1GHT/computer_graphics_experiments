#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

int winWidth = 900, winHeight = 450;
int tetrahedron;
float roanglesX = 1;
unsigned char mask[8 * 16];
int maskSize = 16;
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
	glVertex3f(3.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 3.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 3.0);
	glColor3f(1.0, 1.0, 1.0);
	glEnd();


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

	glEndList();
}

double dis = 4.0;
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, winWidth / 2, winHeight);
	glPushMatrix();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(tetrahedron);
	glPopMatrix();
	
	
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	glPushMatrix();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(roanglesX, roanglesX, roanglesX);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(mask);
	glCallList(tetrahedron);
	glDisable(GL_POLYGON_STIPPLE);
	glPopMatrix();

	glFlush();
}
 
void Reshape(int width, int height)
{
	winWidth = width; winHeight = height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint vp[4]; glGetIntegerv(GL_VIEWPORT ,vp); 
	glOrtho(-3, 3, -3, 3, 0.01, 255);
	//gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 30.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpecialKeyFunction(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP : roanglesX += 0.1; break;
		case GLUT_KEY_DOWN : roanglesX -= 0.1; break;
	}
	glutPostRedisplay();
}
 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutSpecialFunc(SpecialKeyFunction);
	Initial();
	glutMainLoop();
	return 0;
}
