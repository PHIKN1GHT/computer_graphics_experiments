#include <GL/freeglut.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

int winWidth = 900, winHeight = 450; int leftType = 0;
float roanglesX, roanglesY;
int tetrahedron;
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3, 3, -3, 3, 0.01, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glPushMatrix();
	switch (leftType) {
		case 0 : gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); break;
		case 1 : gluLookAt(0, 4.0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); break;
		case 2 : gluLookAt(4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); break;
		case 3 : gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); break;
	}


	

	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(tetrahedron);

	glColor3f(0.0f, 0.0f, 1.0f );
	const char* textx = "X Axis";
    glRasterPos3f(0, 0, 3);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)textx );

    glColor3f(1.0f, 0.0f, 0.0f );
	const char* texty = "Y Axis";
    glRasterPos3f(3, 0, 0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)texty );

    glColor3f(0.0f, 1.0f, 0.0f );
	const char* textz = "Z Axis";
    glRasterPos3f(0, 2.7, 0);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)textz );

	glPopMatrix();
	





	glViewport(winWidth / 2, 0, winWidth / 2, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)winWidth / (GLfloat)winHeight, 0.01, 255);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();





	glPushMatrix();
	gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(roanglesX, 1.0, 0.0, 0.0);
	glRotatef(roanglesY, 0.0, 0.0, 1.0);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(mask);
	glCallList(tetrahedron);
	glPopMatrix();





	glFlush();
}
 
void Reshape(int width, int height)
{
	winWidth = width; winHeight = height;
	glViewport(0, 0, width, height);
}

void ProcessMenu(int value) {
	leftType = value;
}

void SpecialKeyFunction(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP : roanglesX += 1; break;
		case GLUT_KEY_DOWN : roanglesX -= 1; break;
		case GLUT_KEY_LEFT : roanglesY += 1; break;
		case GLUT_KEY_RIGHT : roanglesY -= 1; break;
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
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Original", 0);
	glutAddMenuEntry("XOZ(V)", 1);
	glutAddMenuEntry("YOZ(W)", 2);
	glutAddMenuEntry("XOY(H)", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutSpecialFunc(SpecialKeyFunction);
	Initial();
	glutMainLoop();
	return 0;
}
