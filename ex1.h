#define MAX_PARTICLES 1001
#define TICK_OF_TIME 0.2

#define MILLION 1000000
#define DEG_TO_RAD 0.01745329
#define RUN_SPEED  1.6 * 10
#define TURN_ANGLE 4.0

typedef struct
{
    short active; // show particle on screen?
    float life; // last time
    float fade; // how fast a particle dies
    float r, g, b; // color of particle
    float x, y, z; // position of particle
    float v_x, v_y, v_z; // speed of each particle
    float a_x, a_y, a_z; // acceleration of particle
    float g_x, g_y, g_z; // direction of gravity
} Particle;

