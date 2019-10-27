#define MAX_PARTICLES 1

typedef struct
{
    short active; // show particle on screen?
    float life; // last time
    float fade; // how fast a particle dies
    float r, g, b; // color of particle
    float x, y, z; // position of particle
    float d_x, d_y, d_z; // direction of particle
    float g_x, g_y, g_z; // direction of gravity
} Particle;

