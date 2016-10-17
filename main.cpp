//
// Created by awbrenn on 10/16/16.
//

//
// Created by Austin Brennan on 9/12/16
// See readme.md for more details
//
#include "Camera.h"
#include "Mesh.h"

#ifdef __APPLE__
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

int WIDTH = 1280;
int HEIGHT = 720;

Camera *camera;

bool showReferenceGrid = true;

// draws a simple grid
void drawReferenceGrid() {
  glColor3f(0.0f, 0.0f, 0.0f);

  glLineWidth(1.0f);

  for (double i=-12; i<12; i++) {
    for (double j=-12; j<12; j++) {
      glBegin(GL_LINES);
      glVertex3f(i, 0, j);
      glVertex3f(i, 0, j+1);
      glEnd();
      glBegin(GL_LINES);
      glVertex3f(i, 0, j);
      glVertex3f(i+1, 0, j);
      glEnd();

      if (j == 11){
        glBegin(GL_LINES);
        glVertex3f(i, 0, j+1);
        glVertex3f(i+1, 0, j+1);
        glEnd();
      }
      if (i == 11){
        glBegin(GL_LINES);
        glVertex3f(i+1, 0, j);
        glVertex3f(i+1, 0, j+1);
        glEnd();
      }
    }
  }

  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(-12, 0, 0);
  glVertex3f(12, 0, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, 0, -12);
  glVertex3f(0, 0, 12);
  glEnd();
  glLineWidth(1.0f);
}

void initCameraDebug() {
  // set up camera
  // parameters are eye point, aim point, up vector
  camera = new Camera(Vector3d(0, 5, 5), Vector3d(0, 0, 0),
                      Vector3d(0, 1, 0));

  // grey background for window
  glClearColor(0.62, 0.62, 0.62, 0.0f);
  glShadeModel(GL_SMOOTH);
  glDepthRange(0.0f, 1.0f);

  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initCameraRender() {
  // set up camera
  // parameters are eye point, aim point, up vector
  camera = new Camera(Vector3d(0, 5, 5), Vector3d(0, 0, 0),
                      Vector3d(0, 1, 0));

  // black background for window
  glClearColor(0.0, 0.0, 0.0, 0.0f);
  glShadeModel(GL_SMOOTH);
  glDepthRange(0.0f, 1.0f);

  glEnable(GL_NORMALIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void perspDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw the camera created in perspective
  camera->PerspectiveDisplay(WIDTH, HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (showReferenceGrid)
    drawReferenceGrid();

  glFlush();
  glutSwapBuffers();
}

void simulateParticles() {
  glutPostRedisplay();
}

void mouseEventHandler(int button, int state, int x, int y) {
  // let the camera handle some specific mouse events (similar to maya)
  camera->HandleMouseEvent(button, state, x, y);
  glutPostRedisplay();
}

void motionEventHandler(int x, int y) {
  // let the camera handle some mouse motions if the camera is to be moved
  camera->HandleMouseMotion(x, y);
  glutPostRedisplay();
}

void keyboardEventHandler(unsigned char key, int x, int y) {
  switch (key) {
    case 'r': case 'R':
      // render the particles
      showReferenceGrid = false;
      initCameraRender();
      ;
      break;

    case 'd': case 'D':
      // render the particles
      showReferenceGrid = true;
      initCameraDebug();
      ;
      break;

    case 'p': case 'P':
      // render the particles as points
      ;
      break;

    case 'l': case 'L':
      // render the particles as lines
      ;
      break;

    case 'v': case 'V':
      ;
      break;

    case 'g': case 'G':
      showReferenceGrid = !showReferenceGrid;
      break;

    case 'f': case 'F':
      camera->SetCenterOfFocus(Vector3d(0, 0, 0));
      break;

    case 'q': case 'Q':	// q or esc - quit
    case 27:		// esc
      exit(0);
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  // set up opengl window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);
  int persp_win = glutCreateWindow("Simulating A Squishy Mesh");

  // initialize the camera and such
  initCameraDebug();

  // set up opengl callback functions
  glutDisplayFunc(perspDisplay);
  glutIdleFunc(simulateParticles);
  glutMouseFunc(mouseEventHandler);
  glutMotionFunc(motionEventHandler);
  glutKeyboardFunc(keyboardEventHandler);

  Mesh mesh = Mesh();
  mesh.loadObj((char *) "hello");

  glutMainLoop();
  return(0);
}

