////////////////////////////////////////////////////////////////
// Department of Computer Science
// The University of Manchester
//
// This code is licensed under the terms of the Creative Commons 
// Attribution 2.0 Generic (CC BY 3.0) License.
//
// Skeleton code for COMP37111 coursework, 2019-20
//
// Authors: Toby Howard and Arturs Bekasovs
//
/////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "ex1.h"

#ifdef MACOSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

Particle particles[MAX_PARTICLES];

// Display list for coordinate axis 
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;

///////////////////////////////////////////////

double myRandom()
//Return random double within range [0,1]
{
  return (rand()/(double)RAND_MAX);
}

///////////////////////////////////////////////

GLdouble lat = 0, lon = 0;
GLfloat dir_x, dir_y, dir_z;
GLfloat eyex = 0.0, eyey = 100.0, eyez = 1000.0;

void setView()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // SHIP_VIEW
  dir_x = 100 * cos(DEG_TO_RAD * lat) * sin(DEG_TO_RAD * lon);
  dir_y = 100 * sin(DEG_TO_RAD * lat) - 100;
  dir_z = 100 * cos(DEG_TO_RAD * lat) * cos(DEG_TO_RAD * lon) - 1100;
  gluLookAt(eyex, eyey, eyez,
            dir_x + eyex, dir_y + eyey, dir_z + eyez,
            0.0, 1.0, 0.0);

  // gluLookAt(0.0, 100.0, 1000.0,
  //           0.0, 0.0, 0.0,
  //           0.0, 1.0, 0.0);
}

// initialize new particles
void emit()
{
  // glShadeModel(GL_SMOOTH);
  for (int i = 0; i < MAX_PARTICLES; i++)
  {
    particles[i].active = 1;
    particles[i].life = 1.0f;
    particles[i].fade = myRandom() / 10.0f;
    particles[i].x = 0;
    particles[i].y = 0;
    particles[i].z = 0;
    particles[i].r = 1.0;
    particles[i].g = 0.0;
    particles[i].b = 0.0;
    particles[i].d_x = myRandom() * 10.0;
    particles[i].d_y = myRandom() * 10.0;
    particles[i].d_z = 10.0;
    particles[i].g_x = 0;
    particles[i].g_y = 0;
    particles[i].g_z = 0.9;
  }
}

void display()
{
  setView();
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
  // If enabled, draw coordinate axis
  if(axisEnabled) glCallList(axisList);

  // display particles
  for (int i = 0; i < MAX_PARTICLES; i++)
  {
    // render active particles
    if (particles[i].active == 1)
    {
      // current position of particle i
      float x = particles[i].x;
      float y = particles[i].y;
      float z = particles[i].z;

      // set particles' color
      glColor4f(
        particles[i].r,
        particles[i].g,
        particles[i].b,
        particles[i].life
      );
      
      // draw particles
      glPointSize(10.0f);
      glBegin(GL_POINTS);
      glVertex3f(x, y, z);
      glEnd();
    }
  }

  glutSwapBuffers();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
  GLdouble heading = 0;
  switch(key)
  {
    case 97:
      axisEnabled = !axisEnabled;
      break;

    case 87: // W
      // move to left
      heading = 90;
      eyey += RUN_SPEED * sin(DEG_TO_RAD*heading);
      break;
    case 83: // S
      // move to right
      heading = -90;
      eyey += RUN_SPEED * sin(DEG_TO_RAD*heading);
      break;
    case 65: // A
      // move to left
      heading = lon + 90;
      eyex += RUN_SPEED * sin(DEG_TO_RAD*heading);
      eyez += RUN_SPEED * cos(DEG_TO_RAD*heading);
      break;
    case 68: // D
      // move to right
      heading = lon - 90;
      eyex += RUN_SPEED * sin(DEG_TO_RAD*heading);
      eyez += RUN_SPEED * cos(DEG_TO_RAD*heading);
      break;
    case 27:  /* Escape key */
      exit(0);
  }
  glutPostRedisplay();
}

void cursor_keys(int key, int x, int y) 
{
  GLdouble temp = 0;
  GLdouble heading = 0;
  switch (key) 
  {
    /* To be completed */
    case GLUT_KEY_LEFT:
      // rotate to the left
      temp = lon + TURN_ANGLE;
      lon = temp;
      break;
    case GLUT_KEY_RIGHT:
      // rotate to the right
      temp = lon - TURN_ANGLE;
      lon = temp;
      break;
    case GLUT_KEY_PAGE_UP:
      // tilt up
      temp = lat + TURN_ANGLE;
      if(temp < 90 && temp > -90)
      {
        lat = temp;
      }
      break;
    case GLUT_KEY_PAGE_DOWN:
      // tilt down
      temp = lat - TURN_ANGLE;
      if(temp < 90 && temp > -90)
      {
        lat = temp;
      }
      break;
    case GLUT_KEY_HOME:
      // re-center lat
      lat = 0;
      break;
    case GLUT_KEY_UP:
      // step forwards 
      heading = lon;
      eyex += RUN_SPEED * sin(DEG_TO_RAD*heading);
      eyez += RUN_SPEED * cos(DEG_TO_RAD*heading);
      break;
    case GLUT_KEY_DOWN:
      // step backwards
      heading = lon;
      eyex -= RUN_SPEED * sin(DEG_TO_RAD*heading);
      eyez -= RUN_SPEED * cos(DEG_TO_RAD*heading);
      break;
  }
  glutPostRedisplay();
} 

///////////////////////////////////////////////

void reshape(int width, int height)
{
  glClearColor(0.9, 0.9, 0.9, 1.0);
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 10000.0);
  glMatrixMode(GL_MODELVIEW);
}

///////////////////////////////////////////////

void makeAxes() {
// Create a display list for drawing coord axis
  axisList = glGenLists(1);
  glNewList(axisList, GL_COMPILE);
      glLineWidth(2.0);
      glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);       // X axis - red
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(AXIS_SIZE, 0.0, 0.0);
      glColor3f(0.0, 1.0, 0.0);       // Y axis - green
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, AXIS_SIZE, 0.0);
      glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, AXIS_SIZE);
    glEnd();
  glEndList();
}

///////////////////////////////////////////////
void initGraphics(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutCreateWindow("COMP37111 Particles");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(cursor_keys);
  glutReshapeFunc(reshape);
  makeAxes();
  emit();
}

/////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  double f;
  srand(time(NULL));
  initGraphics(argc, argv);
  glEnable(GL_POINT_SMOOTH);
  glutMainLoop();
}
