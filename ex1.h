#define DEG_TO_RAD 0.01745329
#define RUN_SPEED  1.6 * 10
#define TURN_ANGLE 4.0

#define OBLIQUE_VIEW 1
#define FRONT_VIEW 2
#define TOP_VIEW 3
#define SHIP_VIEW 4

// according to tutorials: https://learnopengl.com/Getting-started/Textures
// referencing image loading library stb_image.h: https://github.com/nothings/stb/blob/master/stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "referenced_utils/stb_image.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifdef MACOSX
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

// referenced from UoM OpenGL Wiki
#include "referenced_utils/frames.h"

// Global parameters

// Display list for coordinate axis 
GLuint axisList;

int AXIS_SIZE= 200;
int axisEnabled= 1;

GLdouble lat = 0, lon = 0;
GLfloat dir_x, dir_y, dir_z;
GLfloat eyex = 0.0, eyey = 0.0, eyez = 0.0;

int current_view = OBLIQUE_VIEW;
int low_efficiency = 0;

// particle parameters
GLfloat init_vx = 10;
GLfloat init_vy = 20;
GLfloat init_r = 1.0;
GLfloat init_g = 1.0;
GLfloat init_vz = 10;
GLfloat init_b = 0;
GLfloat gravity = -0.9;
GLfloat fade = 0.005;
GLfloat set_num_particles = 250;

GLuint textures[2];

#include "utils/menu.c"
#include "utils/textures.c"
#include "utils/particles.c"