#define MAX_PARTICLES 250001
#define TICK_OF_TIME 0.3
#include<stdlib.h>
#include<math.h>

typedef struct
{
    short active; // show particle on screen?
    float life; // last time
    float fade; // how fast a particle dies
    float r, g, b; // color of particle
    float x, y, z; // position of particle
    float x1, y1, z1; // previous position 1
    float x2, y2, z2; // previous position 2
    float x3, y3, z3; // previous position 3
    float v_x, v_y, v_z; // speed of each particle
    float a_x, a_y, a_z; // acceleration of particle
} Particle;

Particle particles[MAX_PARTICLES];
Particle sm_particles[MAX_PARTICLES];

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

///////////////////////////////////////////////

double myRandom()
//Return random double within range [0,1]
{
  return (rand()/(double)RAND_MAX);
}
///////////////////////////////////////////////

void set_particle(Particle *particle, float x, float y, float z, int type)
{
  particle->active = 1;
  particle->life = 1.0f;
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
  if (type == 0) 
  {
    // main particle
    particle->fade = fade;
    particle->r = init_r;
    particle->g = init_g;
    particle->b = init_b;
    particle->v_x = (myRandom() - myRandom()) * init_vx;
    particle->v_y = init_vy + myRandom() * init_vy;
    particle->v_z = (myRandom() - myRandom()) * init_vz;
  }
  else 
  {
    // small particles
    particle->fade = fade*2;
    particle->r = 1;
    particle->g = 0.5;
    particle->b = 0;
    particle->v_x = (myRandom() - myRandom()) * init_vx * 0.8;
    particle->v_y = myRandom() * init_vy * 0.8;
    particle->v_z = (myRandom() - myRandom()) * init_vz * 0.8;
  }
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
    set_particle(particles+i, 0, 0, 0, 0);
  }
}

// consequtive emission (multi-source)
void emit()
{
  float x = 0, y = 0, z = 0;
  int p_or_n;
  
  for (int i = 0; i < set_num_particles; i++)
  {
    if (particles[i].active == 0)
    {
      if (myRandom() > 0.9)
      {
        if (myRandom() > 0.5)
        {
          p_or_n = 1;
        }
        else
        {
          p_or_n = -1;
        }
        x = p_or_n * myRandom() * 100;

        if (myRandom() > 0.5)
        {
          p_or_n = 1;
        }
        else
        {
          p_or_n = -1;
        }
        z = p_or_n * myRandom() * 100;
        set_particle(particles+i, x, y, z, 0);
      }
    }
  }
}

// if particle reach the ground
void explode_ground(float x, float y, float z)
{
  // emit again near x, y, z
  int cnt = 0, limit = 4;
  for (int i = 0; i < set_num_particles; i++)
  {
    if (sm_particles[i].active == 0)
    {
      set_particle(sm_particles+i, x, y, z, 1);
      cnt++;
    }
    if (cnt == limit)
    {
      break;
    }
  }
}

void draw_particles(int i)
{
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
  
  // draw particles
  int size;

  // particle trails
  glColor4f(
  particles[i].r,
  particles[i].g,
  particles[i].b,
  particles[i].life+0.2
  );

  glPointSize(6.0f);
  glBegin(GL_POINTS);
  glVertex3f(x1, y1, z1);
  glEnd();

  glPointSize(4.0f);
  glBegin(GL_POINTS);
  glVertex3f(x2, y2, z2);
  glEnd();

  glPointSize(2.0f);
  glBegin(GL_POINTS);
  glVertex3f(x3, y3, z3);
  glEnd();

  if(current_view == SHIP_VIEW)
  {
    // simple render particles as points
    glColor4f(
    1,
    0.5,
    particles[i].b,
    particles[i].life+0.2
    );

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
  }
  else
  {
    // render squares: assume length of a side is 'size', center is position (x, y, z)
    // then top left corner coordinate is (x-size, y+size, z)
    // then top right corner coordinate is (x+size, y+size, z)
    // then buttom right corner coordinate is (x+size, y-size, z)
    // then buttom left corner coordinate is (x-size, y-size, z)

    // set particles' color
    // glColor4f(
    // particles[i].r,
    // particles[i].g,
    // particles[i].b,
    // particles[i].life+0.2
    // );
    
    // size = 6;
    // glBegin(GL_QUADS);
    // glVertex3f(x1 - size, y1 + size, z1);
    // glVertex3f(x1 + size, y1 + size, z1);
    // glVertex3f(x1 + size, y1 - size, z1);
    // glVertex3f(x1 - size, y1 - size, z1);
    // glEnd();

    // size = 4;
    // glBegin(GL_QUADS);
    // glVertex3f(x2 - size, y2 + size, z2);
    // glVertex3f(x2 + size, y2 + size, z2);
    // glVertex3f(x2 + size, y2 - size, z2);
    // glVertex3f(x2 - size, y2 - size, z2);
    // glEnd();

    // size = 2;
    // glBegin(GL_QUADS);
    // glVertex3f(x3 - size, y3 + size, z3);
    // glVertex3f(x3 + size, y3 + size, z3);
    // glVertex3f(x3 + size, y3 - size, z3);
    // glVertex3f(x3 - size, y3 - size, z3);
    // glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glNormal3f(0.0f, 1.0f, 0.0f);

    size = 8;
    if (current_view == TOP_VIEW)
    {
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x - size, y, z+size);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x + size, y, z+size);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x + size, y, z-size);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x - size, y, z-size);
      glEnd();
    }
    else if(current_view == OBLIQUE_VIEW)
    {
      glPushMatrix();
      glTranslatef(x, y, z);
      glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
      glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
      glTranslatef(-x, -y, -z);
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
      glPopMatrix();
    }
    else
    {
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
    }

    glDisable(GL_TEXTURE_2D);
  }

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

  if(low_efficiency == 1)
  {
    particles[i].x += particles[i].v_x * TICK_OF_TIME + 0.5 * particles[i].a_x * TICK_OF_TIME * TICK_OF_TIME;
    particles[i].y += particles[i].v_y * TICK_OF_TIME + 0.5 * (particles[i].a_y + gravity) * TICK_OF_TIME * TICK_OF_TIME;
    particles[i].z += particles[i].v_z * TICK_OF_TIME + 0.5 * particles[i].a_z * TICK_OF_TIME * TICK_OF_TIME;
  }
  else
  {
    particles[i].x += (particles[i].v_x + 0.5 * particles[i].a_x * TICK_OF_TIME) * TICK_OF_TIME;
    particles[i].y += (particles[i].v_y + 0.5 * (particles[i].a_y + gravity) * TICK_OF_TIME) * TICK_OF_TIME;
    particles[i].z += (particles[i].v_z + 0.5 * particles[i].a_z * TICK_OF_TIME) * TICK_OF_TIME;
  }

  // update speed
  particles[i].v_x += particles[i].a_x * TICK_OF_TIME;
  particles[i].v_y += (particles[i].a_y + gravity) * TICK_OF_TIME;
  particles[i].v_z += particles[i].a_z * TICK_OF_TIME;

  // update lifetime
  particles[i].life -= particles[i].fade;

  // if a particle die
  if (y < 0 || particles[i].life < 0)
  {
    if (y < 0)
    {
      y = 0;
    }
    explode_ground(x, y, z);
    particles[i].x = 0;
    particles[i].y = 0;
    particles[i].z = 0;
    particles[i].active = 0;
  }
}

void draw_sm_particles(int i)
{
  // current position of particle i
  float x = sm_particles[i].x;
  float y = sm_particles[i].y;
  float z = sm_particles[i].z;

  // set particles' color
  glColor4f(
    sm_particles[i].r,
    sm_particles[i].g,
    sm_particles[i].b,
    sm_particles[i].life
  );
  
  // draw particles

  // simple render particles as points

  glPointSize(3.0f);
  glBegin(GL_POINTS);
  glVertex3f(x, y, z);
  glEnd();

  if(low_efficiency == 1)
  {
    sm_particles[i].x += sm_particles[i].v_x * TICK_OF_TIME + 0.5 * sm_particles[i].a_x * TICK_OF_TIME * TICK_OF_TIME;
    sm_particles[i].y += sm_particles[i].v_y * TICK_OF_TIME + 0.5 * (sm_particles[i].a_y + gravity) * TICK_OF_TIME * TICK_OF_TIME;
    sm_particles[i].z += sm_particles[i].v_z * TICK_OF_TIME + 0.5 * sm_particles[i].a_z * TICK_OF_TIME * TICK_OF_TIME;
  }
  else
  {
    sm_particles[i].x += (sm_particles[i].v_x + 0.5 * sm_particles[i].a_x * TICK_OF_TIME) * TICK_OF_TIME;
    sm_particles[i].y += (sm_particles[i].v_y + 0.5 * (sm_particles[i].a_y + gravity) * TICK_OF_TIME) * TICK_OF_TIME;
    sm_particles[i].z += (sm_particles[i].v_z + 0.5 * sm_particles[i].a_z * TICK_OF_TIME) * TICK_OF_TIME;
  }

  // update speed
  sm_particles[i].v_x += sm_particles[i].a_x * TICK_OF_TIME;
  sm_particles[i].v_y += (sm_particles[i].a_y + gravity) * TICK_OF_TIME;
  sm_particles[i].v_z += sm_particles[i].a_z * TICK_OF_TIME;

  // update lifetime
  sm_particles[i].life -= sm_particles[i].fade;

  // if a particle die
  if (y < 0 || sm_particles[i].life < 0)
  {
    sm_particles[i].x = 0;
    sm_particles[i].y = 0;
    sm_particles[i].z = 0;
    sm_particles[i].active = 0;
  }
}