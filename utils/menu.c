// particle parameters
extern GLfloat init_vx;
extern GLfloat init_vy;
extern GLfloat init_r;
extern GLfloat init_g;
extern GLfloat init_vz;
extern GLfloat init_b;
extern GLfloat gravity;
extern GLfloat fade;
extern GLfloat set_num_particles;

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
      set_num_particles = 100;
      break;
    case 2:
      set_num_particles = 1000;
      break;
    case 3:
      set_num_particles = 10000;
      break;
    case 4:
      set_num_particles = 100000;
      break;
    case 5:
      set_num_particles = 1000000;
      break;
    default:
      set_num_particles = 1000;
  }
}

void processViewMenu(int menuentry)
{
  switch(menuentry)
  {
    case OBLIQUE_VIEW:
      current_view = OBLIQUE_VIEW;
      break;
    case FRONT_VIEW:
      current_view = FRONT_VIEW;
      break;
    case TOP_VIEW:
      current_view = TOP_VIEW;
      break;
    case SHIP_VIEW:
      current_view = SHIP_VIEW;
      break;
    default:
      current_view = OBLIQUE_VIEW;
  }
}

void processEffMenu(int menuentry)
{
  switch(menuentry)
  {
    case 0:
      low_efficiency = 0;
      break;
    case 1:
      low_efficiency = 1;
      break;
    default:
      low_efficiency = 0;
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

  int viewMenu = glutCreateMenu(processViewMenu);
  glutAddMenuEntry("Oblique View", OBLIQUE_VIEW);
  glutAddMenuEntry("Front View", FRONT_VIEW);
  glutAddMenuEntry("Top View", TOP_VIEW);
  glutAddMenuEntry("Ship View", SHIP_VIEW);

  int effMenu = glutCreateMenu(processEffMenu);
  glutAddMenuEntry("High Efficiency Mode", 0);
  glutAddMenuEntry("Low Efficiency Mode", 1);

  glutCreateMenu(processMainMenu);
  glutAddSubMenu("Initial velocity of particles", velocityMenu);
  glutAddSubMenu("Initial color of particles", colorMenu);
  glutAddSubMenu("Gravity intensity", gravityMenu);
  glutAddSubMenu("Lifetime of particles", lifetimeMenu);
  glutAddSubMenu("Maximum number of particles", numberMenu);
  glutAddSubMenu("Change View", viewMenu);
  glutAddSubMenu("Check Efficiency Improvement", effMenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}