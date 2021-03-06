//
// Created by awbrenn on 10/16/16.
//

//
// Created by Austin Brennan on 9/12/16
// See readme.md for more details
//
#define GL_GLEXT_PROTOTYPES 1

#include "Camera.h"
#include "Object.h"
#include "SpringyObject.h"
#include "Solver.h"

#ifdef __APPLE__
  #pragma clang diagnostic ignored "-Wdeprecated-declarations"
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
#else
  #include <GL/glut.h>
  #include <GL/gl.h>
#endif

int WIDTH = 1280;
int HEIGHT = 720;

Camera *camera;
SpringyObject *springy_object;
Solver *solver;
unsigned int INTEGRATOR;
Vector3d user_acceleration;
double user_accel_magnitude;

bool showReferenceGrid = true;

// draws a simple grid
void drawReferenceGrid() {
  glUseProgram(0);
  glColor3f(0.0f, 0.0f, 0.0f);

  glLineWidth(1.0f);

  for (double i=-12; i<12; i++) {
    for (double j=-12; j<12; j++) {
      glBegin(GL_LINES);
      glVertex3f(i, (GLfloat) solver->ground_level, j);
      glVertex3f(i, (GLfloat) solver->ground_level, j+1);
      glEnd();
      glBegin(GL_LINES);
      glVertex3f(i, (GLfloat) solver->ground_level, j);
      glVertex3f(i+1, (GLfloat) solver->ground_level, j);
      glEnd();

      if (j == 11){
        glBegin(GL_LINES);
        glVertex3f(i, (GLfloat) solver->ground_level, j+1);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j+1);
        glEnd();
      }
      if (i == 11){
        glBegin(GL_LINES);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j);
        glVertex3f(i+1, (GLfloat) solver->ground_level, j+1);
        glEnd();
      }
    }
  }

  glLineWidth(2.0f);
  glBegin(GL_LINES);
  glVertex3f(-12, (GLfloat) solver->ground_level, 0);
  glVertex3f(12, (GLfloat) solver->ground_level, 0);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0, (GLfloat) solver->ground_level, -12);
  glVertex3f(0, (GLfloat) solver->ground_level, 12);
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

void drawMesh() {
//  glUseProgram(springy_object->shader->program);
  glPolygonMode(GL_FRONT, GL_LINE);
  glPolygonMode(GL_BACK, GL_LINE);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < springy_object->mesh.GLfaces.size(); ++i) {
    GLface face = springy_object->mesh.GLfaces[i];
    for (int j = 0; j < 3; ++j) {
      glNormal3fv((GLfloat*)&face.vn[j]);
      glVertex3fv((GLfloat*)&face.v[j]);
    }
  }
  glEnd();
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
}

void perspDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw the camera created in perspective
  camera->PerspectiveDisplay(WIDTH, HEIGHT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (showReferenceGrid)
    drawReferenceGrid();

  drawMesh();

  glFlush();
  glutSwapBuffers();
}

void stepSimulation() {
  solver->update(INTEGRATOR, &springy_object->mesh, user_acceleration);
  user_acceleration = Vector3d(0.0, 0.0, 0.0);
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
//    case 'r': case 'R':
//      // render the particles
//      showReferenceGrid = false;
//      initCameraRender();
//      ;
//      break;
//
//    case 'd': case 'D':
//      // render the particles
//      showReferenceGrid = true;
//      initCameraDebug();
//      ;
//      break;

    case 'w': case 'W':
      user_acceleration = Vector3d(0.0, 0.0, -1.0 * user_accel_magnitude);
      break;

    case 'a':
      user_acceleration = Vector3d(-1.0 * user_accel_magnitude, 0.0, 0.0);
      break;

    case 's':
      user_acceleration = Vector3d(0.0, 0.0, user_accel_magnitude);
      break;

    case 'd':
      user_acceleration = Vector3d(user_accel_magnitude, 0.0, 0.0);
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

bool readParameters(char *paramfile_name) {
  bool succeeded = true;
  std::ifstream paramfile_stream(paramfile_name);
  std::string line;

  if (paramfile_stream.is_open()) {
    // read through the file
    while (getline(paramfile_stream, line)) {

      if (line.compare("SPRINGY OBJECT:") == 0) {
        double mass,                       // mass of the object
               spring_constant,            // spring time constant
               damping_constant,           // damper time constant
               torsional_spring_constant,  // spring constant of the torsional springs
               torsional_damping_constant; // damping constant of the torsional springs
        std::string obj_filename;
        std::string frag_shader_filename;
        std::string vert_shader_filename;
        // skip a line
        getline(paramfile_stream, line);

        // stream the line with object information
        getline(paramfile_stream, line);
        std::stringstream object_stream(line);

        object_stream >> obj_filename;

        // skip a few lines
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        object_stream.str(line);
        object_stream.clear();

        object_stream >> frag_shader_filename >> vert_shader_filename;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        object_stream.str(line);
        object_stream.clear();

        object_stream >> mass >> spring_constant >> damping_constant;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        object_stream.str(line);
        object_stream.clear();

        object_stream >> torsional_spring_constant >> torsional_damping_constant;

//        std::cout << "mass: " << mass << " k: " << spring_constant << " d: " << damping_constant << std::endl;

        springy_object = new SpringyObject(obj_filename, frag_shader_filename, vert_shader_filename, mass,
                                           spring_constant, damping_constant, torsional_spring_constant,
                                           torsional_damping_constant);
      }

      else if (line.compare("SOLVER:") == 0) {
        double time_step,
               ground_plane,
               coefficient_of_restitution,
               coefficient_of_friction;
        // skip a line
        getline(paramfile_stream, line);

        getline(paramfile_stream, line);
        std::stringstream solver_stream(line);
        solver_stream >> time_step;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();
        std::string integration_type;

        solver_stream >> integration_type;
        if (integration_type.compare("LEAPFROG") == 0) {
          INTEGRATOR = LEAPFROG;
        }
        else if (integration_type.compare("SIXTH") == 0) {
          INTEGRATOR = SIXTH;
        }
        else {
          INTEGRATOR = SIXTH;
        }

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();

        solver_stream >> ground_plane >> coefficient_of_restitution >> coefficient_of_friction;

        // skip a line
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);
        getline(paramfile_stream, line);

        solver_stream.str(line);
        solver_stream.clear();

        solver_stream >> user_accel_magnitude;

        solver = new Solver(&springy_object->spring_mesh, time_step, ground_plane,
                            coefficient_of_restitution, coefficient_of_friction);
      }
    }
  }
  else {
    succeeded = false;
  }

  return succeeded;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Proper Usage: $> SquishyMesh parameters" << std::endl;
    exit(EXIT_FAILURE);
  }

  // set up opengl window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50, 50);
  int persp_win = glutCreateWindow("Simulating A Squishy Mesh");

  // read the parameters
  readParameters(argv[1]);

  // initialize the camera and such
  initCameraDebug();

  // set up opengl callback functions
  glutDisplayFunc(perspDisplay);
  glutIdleFunc(stepSimulation);
  glutMouseFunc(mouseEventHandler);
  glutMotionFunc(motionEventHandler);
  glutKeyboardFunc(keyboardEventHandler);

  glutMainLoop();
  return(0);
}

