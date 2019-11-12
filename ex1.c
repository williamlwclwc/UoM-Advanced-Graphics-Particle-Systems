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
GLfloat eyex = 0.0, eyey = 0.0, eyez = -1000.0;

// particle parameters
GLfloat init_vx = 10;
GLfloat init_vy = 20;
GLfloat init_vz = 10;
GLfloat init_r = 1.0;
GLfloat init_g = 1.0;
GLfloat init_b = 0;
GLfloat gravity = -0.9;
GLfloat fade = 0.005;
GLfloat set_num_particles = 250;

unsigned char *data;

// create menu to control parameters
void processMainMenu() {}

void processVelocityMenu(int menuentry)
{
  switch(menuentry)
  {
    case 1:
      init_vx = 20;
      init_vy = 40;
      init_vz = 20;
      break;
    case 2:
      init_vx = 10;
      init_vy = 20;
      init_vz = 10;
      break;
    case 3:
      init_vx = 5;
      init_vy = 10;
      init_vz = 5;
      break;
    default:
      init_vx = 10;
      init_vy = 20;
      init_vz = 10;
  }
}

void processColorMenu(int menuentry)
{
  switch(menuentry)
  {
    case 1:
      // red
      init_r = 1.0;
      init_g = 0;
      init_b = 0;
      break;
    case 2:
      // orange
      init_r = 1.0;
      init_g = 0.5;
      init_b = 0;
      break;
    case 3:
      // yellow
      init_r = 1.0;
      init_g = 1.0;
      init_b = 0;
      break;
    default:
      // yellow
      init_r = 1.0;
      init_g = 1.0;
      init_b = 0;
  }
}

void processGravityMenu(int menuentry)
{
  switch(menuentry)
  {
    case 1:
      gravity = -5.0;
      break;
    case 2:
      gravity = -0.98;
      break;
    case 3:
      gravity = -0.2;
      break;
    default:
      gravity = -0.98;
  }
}

void processLifetimeMenu(int menuentry)
{
  switch(menuentry)
  {
    case 1:
      fade = 0;
      break;
    case 2:
      fade = 0.005;
      break;
    case 3:
      fade = 0.1;
      break;
    default:
      fade = 0.005;
  }
}

void processNumberMenu(int menuentry)
{
  switch(menuentry)
  {
    case 1:
      set_num_particles = 25;
      break;
    case 2:
      set_num_particles = 250;
      break;
    case 3:
      set_num_particles = 2500;
      break;
    case 4:
      set_num_particles = 25000;
      break;
    case 5:
      set_num_particles = 250000;
      break;
    default:
      set_num_particles = 250;
  }
}

void init_menu()
{
  int velocityMenu = glutCreateMenu(processVelocityMenu);
  glutAddMenuEntry("high", 1);
  glutAddMenuEntry("normal", 2);
  glutAddMenuEntry("low", 3);

  int colorMenu = glutCreateMenu(processColorMenu);
  glutAddMenuEntry("Red", 1);
  glutAddMenuEntry("Orange", 2);
  glutAddMenuEntry("Yellow", 3);

  int gravityMenu = glutCreateMenu(processGravityMenu);
  glutAddMenuEntry("intense", 1);
  glutAddMenuEntry("normal", 2);
  glutAddMenuEntry("low", 3);

  int lifetimeMenu = glutCreateMenu(processLifetimeMenu);
  glutAddMenuEntry("long", 1);
  glutAddMenuEntry("normal", 2);
  glutAddMenuEntry("short", 3);

  int numberMenu = glutCreateMenu(processNumberMenu);
  glutAddMenuEntry("100", 1);
  glutAddMenuEntry("1000", 2);
  glutAddMenuEntry("10,000", 3);
  glutAddMenuEntry("100,000", 4);
  glutAddMenuEntry("1,000,000", 5);

  glutCreateMenu(processMainMenu);
  glutAddSubMenu("Initial velocity of particles", velocityMenu);
  glutAddSubMenu("Initial color of particles", colorMenu);
  glutAddSubMenu("Gravity intensity", gravityMenu);
  glutAddSubMenu("Lifetime of particles", lifetimeMenu);
  glutAddSubMenu("Maximum number of particles", numberMenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setView()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // SHIP_VIEW
  dir_x = 100 * cos(DEG_TO_RAD * lat) * sin(DEG_TO_RAD * lon);
  dir_y = 100 * sin(DEG_TO_RAD * lat);
  dir_z = 100 * cos(DEG_TO_RAD * lat) * cos(DEG_TO_RAD * lon);
  gluLookAt(eyex, eyey, eyez,
            dir_x + eyex, dir_y + eyey, dir_z + eyez,
            0.0, 1.0, 0.0);

  // gluLookAt(0.0, 100.0, 1000.0,
  //           0.0, 0.0, 0.0,
  //           0.0, 1.0, 0.0);
}

// load texture images
// according to tutorials: https://learnopengl.com/Getting-started/Textures
// referencing image loading library stb_image.h: https://github.com/nothings/stb/blob/master/stb_image.h
unsigned int lava_rock;
void loadtextures()
{
  int width, height, nrChannels;
  data = stbi_load("lava-rock.jpg", &width, &height, &nrChannels, 0);
  if(data == NULL) 
  {
    printf("failed to load texture image\n");
  } 
  else
  {
    printf("texture loaded\n");
  }

  glGenTextures(1,&lava_rock);
  glBindTexture(GL_TEXTURE_2D, lava_rock);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width,
            height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  if(data!=NULL)
  {
    stbi_image_free(data);
  }
}

void set_particle(Particle *particle, float x, float y, float z)
{
  particle->active = 1;
  particle->life = 1.0f;
  particle->fade = fade;
  particle->x = x;
  particle->y = y;
  particle->z = z;
  particle->x1 = 0;
  particle->y1 = 0;
  particle->z1 = 0;
  particle->x2 = 0;
  particle->y2 = 0;
  particle->z2 = 0;
  particle->x3 = 0;
  particle->y3 = 0;
  particle->z3 = 0;
  particle->r = init_r;
  particle->g = init_g;
  particle->b = init_b;
  particle->v_x = (myRandom() - myRandom()) * init_vx;
  particle->v_y = init_vy + myRandom() * init_vy;
  particle->v_z = (myRandom() - myRandom()) * init_vz;
  particle->a_x = 0;
  particle->a_y = 0;
  particle->a_z = 0;
}

// initialize new particles
void init()
{ 
  int init_emit_num = myRandom() * set_num_particles;
  for (int i = 0; i < init_emit_num; i++)
  {
    set_particle(particles+i, 0, 0, 0);
  }
}

// consequtive emission
void emit()
{
  float x = 0, y = 0, z = 0;
  float rd = myRandom();
  if (rd < 0.2) 
  {
    x = -50;
    z = -50;
  }
  else if (rd > 0.2 && rd < 0.4)
  {
    x = 50;
    z = 50;
  }
  else if (rd > 0.4 && rd < 0.6)
  {
    x = 0;
    z = 0;
  }
  else if (rd > 0.6 && rd < 0.8)
  {
    x = 50;
    z = -50;
  }
  else
  {
    x = -50;
    z = 50;
  }
  
  for (int i = 0; i < set_num_particles; i++)
  {
    if (particles[i].active == 0)
    {
      if (myRandom() > 0.5)
      {
        set_particle(particles+i, x, y, z);
      }
    }
  }
}

void display()
{
  setView();
  // Clear the screen
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  // If enabled, draw coordinate axis
  if(axisEnabled) glCallList(axisList);

  // display particles
  for (int i = 0; i < set_num_particles; i++)
  {
    int num_active = 0;
    // render active particles
    if (particles[i].active == 1)
    {
      num_active++;
      // current position of particle i
      float x = particles[i].x;
      float y = particles[i].y;
      float z = particles[i].z;

      float x1 = particles[i].x1;
      float y1 = particles[i].y1;
      float z1 = particles[i].z1;
      float x2 = particles[i].x2;
      float y2 = particles[i].y2;
      float z2 = particles[i].z2;
      float x3 = particles[i].x3;
      float y3 = particles[i].y3;
      float z3 = particles[i].z3;
    
      // set particles' color
      glColor4f(
        particles[i].r,
        particles[i].g,
        particles[i].b,
        particles[i].life
      );
      
      // draw particles

      // simple render particles as points

      // glPointSize(8.0f);
      // glBegin(GL_POINTS);
      // glVertex3f(x, y, z);
      // glEnd();

      // glPointSize(6.0f);
      // glBegin(GL_POINTS);
      // glVertex3f(x1, y1, z1);
      // glEnd();

      // glPointSize(4.0f);
      // glBegin(GL_POINTS);
      // glVertex3f(x2, y2, z2);
      // glEnd();

      // glPointSize(2.0f);
      // glBegin(GL_POINTS);
      // glVertex3f(x3, y3, z3);
      // glEnd();

      // render squares: assume length of a side is 'size', center is position (x, y, z)
      // then top left corner coordinate is (x-size, y+size, z)
      // then top right corner coordinate is (x+size, y+size, z)
      // then buttom right corner coordinate is (x+size, y-size, z)
      // then buttom left corner coordinate is (x-size, y-size, z)

      int size = 6;
      glBegin(GL_QUADS);
      glVertex3f(x1 - size, y1 + size, z1);
      glVertex3f(x1 + size, y1 + size, z1);
      glVertex3f(x1 + size, y1 - size, z1);
      glVertex3f(x1 - size, y1 - size, z1);
      glEnd();

      size = 4;
      glBegin(GL_QUADS);
      glVertex3f(x2 - size, y2 + size, z2);
      glVertex3f(x2 + size, y2 + size, z2);
      glVertex3f(x2 + size, y2 - size, z2);
      glVertex3f(x2 - size, y2 - size, z2);
      glEnd();

      size = 2;
      glBegin(GL_QUADS);
      glVertex3f(x3 - size, y3 + size, z3);
      glVertex3f(x3 + size, y3 + size, z3);
      glVertex3f(x3 + size, y3 - size, z3);
      glVertex3f(x3 - size, y3 - size, z3);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, lava_rock);
      glEnable(GL_TEXTURE_2D);
      glNormal3f(0.0f, 0.0f, 1.0f);

      size = 8;
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x - size, y + size, z);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x + size, y + size, z);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x + size, y - size, z);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x - size, y - size, z);
      glEnd();

      glDisable(GL_TEXTURE_2D);

      // update position
      particles[i].x3 = particles[i].x2;
      particles[i].y3 = particles[i].y2;
      particles[i].z3 = particles[i].z2;

      particles[i].x2 = particles[i].x1;
      particles[i].y2 = particles[i].y1;
      particles[i].z2 = particles[i].z1;

      particles[i].x1 = particles[i].x;
      particles[i].y1 = particles[i].y;
      particles[i].z1 = particles[i].z;

      particles[i].x += particles[i].v_x * TICK_OF_TIME + 0.5 * particles[i].a_x * TICK_OF_TIME * TICK_OF_TIME;
      particles[i].y += particles[i].v_y * TICK_OF_TIME + 0.5 * (particles[i].a_y + gravity) * TICK_OF_TIME * TICK_OF_TIME;
      particles[i].z += particles[i].v_z * TICK_OF_TIME + 0.5 * particles[i].a_z * TICK_OF_TIME * TICK_OF_TIME;

      // update speed
      particles[i].v_x += particles[i].a_x * TICK_OF_TIME;
      particles[i].v_y += (particles[i].a_y + gravity) * TICK_OF_TIME;
      particles[i].v_z += particles[i].a_z * TICK_OF_TIME;

      // update lifetime
      particles[i].life -= particles[i].fade;

      // if a particle die
      if (particles[i].y < -1 || particles[i].life < 0)
      {
        particles[i].x = 0;
        particles[i].y = 0;
        particles[i].z = 0;
        particles[i].active = 0;
      }

      // auto emission
      if (num_active < set_num_particles / 4)
      {
        emit();
      }
    }
  }

  glutSwapBuffers();
  glutPostRedisplay();
}

///////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y)
{
  GLdouble heading = 0;
  switch(key)
  {
    // a
    case 97:
      axisEnabled = !axisEnabled;
      break;
    
    // enter
    case 13:
      emit();
      break;

    // space
    case 32:
      emit();
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
  loadtextures();
  init_menu();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  makeAxes();
  init();
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
