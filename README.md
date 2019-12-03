# COMP37111 Advanced Computer Graphics Lab - Particle Systems

## Task by Task

1. Design Simulation
    * data structure that represents an individual particle
        * how to represent in code?
        * what properties does a particle have and how to represent these efficiently?
    * how to represent a collection of particles
        * time or space complexity?
        * how to access this data structure? random or iterate?
        * more than one 'emitter'?
    * when a particle dies
        * what to do? recycle or throw away and make new ones?
    * how to represent the physics of simulation
        * how to represent physics?
        * how does it interact with the data structure?
    * interaction with simulation and test different effects
        * via GUI, key-presses, command line or both?
        * how changes interact with the data structures and physics?
    * explore performance
        * how to explore performance?
        * what are the different things to measure?
        * how to demonstrate the measurement?
2. Draw One Particle
   * [x] Render a particle (e.g. using GL_POINT) and scale it up with glPointSize()
   * [x] Give the particle an initial position, velocity and acceleration
   * [x] A loop that implements 'ticks' of time, at each tick, work out a new position of the particle (movement should conform to the equation of motion under gravity) and draw it
   * [x] Use the space key to reset time to 0 and trigger the system to start emit particles
3. Draw A System of Particles
   * [x] build an emitter (single-point or geometry)
     [x] single-point emitter: all particles are emitted from one point in space
     [x] geometry emiiter: particles are emited from multiple sources arranged in some geometrical pattern
   * [x] apply the data structure to each of the particles produced by the emitter in turn
   * [x] add randomness for the particles
4. Control of Particle Parameters
   * [x] initial velocity
   * [x] initial color
   * [x] intensity of gravity
   * [x] lifetime of particle
   * [x] number of particles in system
5. Improved/Alternative Redering
   * [x] draw particles beyond GL_Point
     * faster or slower? I think it's a little faster
   * Implement at least one of the following:
     * [x] Particle trails
     * [x] Render as a little billboarded sprite using GL_QUADS
     * [x] alpha value to show transparency
     * [x] textured quads
     * ~~[ ] Others~~
6. Conduct Experiments to Explore Performance
   * [x] experiment with number of particles: 100->1000->10000->100000->1000000, what's the effect?
     * 100 and 1000 are completely smooth.
     * 10,000 become slower but acceptable.
     * 100,000 are becoming really slow, but you can see them moving.
     * 1,000,000 are kind of "dangerous" for my computer, my computer is getting stuck.
     * Opengl uses only 1 core of my CPU, which kind of limit the performance.
   * [x] enable and disable different parts of the system and understand how they contribute to the overall performance
     * measure performance of the "physics" vs. "rendering"
       * obviously, rendering costs much more than physical calculations.
7. Sophistication and Flair
   * [x] Multiple particle sources
   * [x] Support different viewpoints of the world, or being able to fly around the scene
   * [x] Textured particles
   * ~~[ ] Interactions between particles~~
   * ~~[ ] Animated "fly-throughs" of the scene~~
   * [x] Interactions between particles and other objects in the world
   * ~~[ ] GPU-based particle rendering~~

## Marking Scheme

1. Multiple particles
   * [x] multiple particles appearing on-screen (1 mark)
   * [x] moving in 3 dimensions (1 mark)
2. Rendering beyond GL_POINT
   * [x] rendering beyond GL_POINTS (2 marks)
3. Interactively control the system to change properties and see appropriate effects
   * [x] 2+ different particles properties(e.g. life, velocity) (1 mark)
   * [x] 1+ world property(e.g. gravity or wind) (1 mark)
4. Analysis of the fidelity of chosen laws of motion
   * [x] describe what the laws of motion are intended to be and demonstrate that the particles roughly follow those (1 mark)
     * projectile motion, each particle has a initial speed, and affect by gravity
   * [x] describe informally how accurate the laws of motion are simulated (1 mark)
     * accurately calculated with law of motion, but does not consider wind or air resistance
   * [ ] describe with specific data how accurate the laws of the motions are simulated (1 mark)
5. Efficiency of your approach to implement chosen laws of motion
   * [x] any evidence that efficiently has been thought of (1 mark)
   * [x] evidence of thinking about efficiency and what measures could be taken to improve it, or a solid argument as to why there is no possible way of improving it (1 mark)
   * [x] demonstrating that specific measures to improve or maximise efficiency have been implemented (1 mark)
6. Analysis of overall performance / rendering speed and discussion of efficiencies implemented
   * [x] sensible discussion of how performance is bound by the limitations of data structures/CPU/use of GPU/transfer of data between CPU-GPU (1 mark)
     * when there are a large number of particles, there is only a CPU core working 100% and the other 3 are idle, if openGL can use multi-thread rendering, the performance can increase
     * using a decent GPU can make the rendering process parallel
   * [x] evidence of exploring performance/rendering bounds by performing experiments (1 mark)
     * we can see CPU core reached 100% by setting number of particles to 10,000
   * [x] analysis/discussion supported by some data (1 mark)
   * [ ] rigorous performance analysis supported by graphs or other data visulisations (e.g. paricle number vs. framerates) (1 mark)
7. Sophistication and flair
   * [x] demonstrating 2 different things from the list in Task 7 (2 mark)
   * ~~[ ] or one super-thing that is impressive~~

## How to run

* use './run' to compile and run with bash
