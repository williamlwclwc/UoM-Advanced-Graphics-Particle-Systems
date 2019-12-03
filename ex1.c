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
#include "ex1.h"

void setView()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch (current_view)
  {
  case 1:
    // oblique view
    gluLookAt(1000.0, 1000.0, 1000.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    break;
  case 2:
    // front view
    gluLookAt(0.0, 100.0, 1200.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    break;
  case 3:
    // top view
    gluLookAt(1.0, 1200.0, 1.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    break;
  case 4:
    // ship view
    dir_x = 100 * cos(DEG_TO_RAD * lat) * sin(DEG_TO_RAD * lon);
    dir_y = 100 * sin(DEG_TO_RAD * lat);
    dir_z = 100 * cos(DEG_TO_RAD * lat) * cos(DEG_TO_RAD * lon);
    gluLookAt(eyex, eyey, eyez,
              dir_x + eyex, dir_y + eyey, dir_z + eyez,
              0.0, 1.0, 0.0);
    break;
  default:
    // oblique view
    gluLookAt(600.0, 600.0, 600.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
    break;
  }
}

void display()
{
  setView();
  // Clear the screen
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  frameStart();
  
  // If enabled, draw coordinate axis
  if(axisEnabled) glCallList(axisList);

  // display ground
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glEnable(GL_TEXTURE_2D);
  glNormal3f(0.0f,1.0f,0.0f);
  float g_size = 800;
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-g_size, -1, g_size);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(g_size, -1, g_size);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(g_size, -1, -g_size);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-g_size, -1, -g_size);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  int num_active = 0;

  // display particles
  for (int i = 0; i < set_num_particles; i++)
  {
    // render active particles
    if (particles[i].active == 1)
    {
      num_active++;
      
      draw_particles(i);

      if(low_efficiency == 1)
      {
        // auto emission, wrong place, not efficient
        if (num_active < set_num_particles / 2)
        {
          emit();
        }
      }
    }
    
    // display explosion particles
    // render active particles
    if (sm_particles[i].active == 1)
    {
      draw_sm_particles(i);
    }
  }

  if(low_efficiency == 0)
  {
    // auto emission
    if (num_active < set_num_particles / 2)
    {
      emit();
    }
  }

  float cur_fps = frameEnd(GLUT_BITMAP_HELVETICA_10, 1.0, 1.0, 1.0, 0.05, 0.95);
  fps[fps_index] = cur_fps;
  num_of_particles[fps_index] = cnt_particles;
  fps_index++;
  fps_length++;
  if (fps_index > 10000)
  {
    fps_index = 0;
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
      // save fps & num of particles to file
      fp = fopen("data/fps_data.txt", "w+");
      for(int i = 0; i < fps_length; i++)
      {
        fprintf(fp, "%.2f, %d\n", fps[i], num_of_particles[i]);
      }
      printf("%d\n", fps_length);
      fclose(fp);
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
  // activate alpha value
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  // makeAxes();
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
