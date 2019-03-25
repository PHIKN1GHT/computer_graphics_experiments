#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> > pointList;

int ww, wh;
void Initial() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(4.0);
	glEnable(GL_MAP1_VERTEX_3);
	pointList.clear();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	if (pointList.size() > 0) {
		GLfloat ControlP[4][3]; memset(ControlP, 0, sizeof(ControlP));
		for (int i = 0; i < pointList.size(); i++)
			ControlP[i][0] = pointList[i].first,
			ControlP[i][1] = pointList[i].second,
			ControlP[i][2] = 0;
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, pointList.size(), *ControlP);
		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);
	}
	glFlush();
}

void Reshape(GLint w, GLint h) {
	ww = w, wh = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}

void MousePlot(GLint button, GLint action,GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		if (pointList.size() == 4) pointList.clear();
			else pointList.push_back(pair<int, int> {xMouse, wh - yMouse});
		glutPostRedisplay();
	}
}

int main (int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("COMPUTER GRAPHICS 10170940");
	Initial();
	glutMouseFunc(MousePlot);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}































