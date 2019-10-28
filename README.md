# COMP37111 Advanced Computer Graphics Lab - Particle Systems

## Task by Task

1. Design Simulation
    * [ ] data structure that represents an individual particle
        * how to represent in code?
        * what properties does a particle have and how to represent these efficiently?
    * [ ] how to represent a collection of particles
        * time or space complexity?
        * how to access this data structure? random or iterate?
        * more than one 'emitter'?
    * [ ] when a particle dies
        * what to do? recycle or throw away and make new ones?
    * [ ] how to represent the physics of simulation
        * how to represent physics?
        * how does it interact with the data structure?
    * [ ] interaction with simulation and test different effects
        * via GUI, key-presses, command line or both?
        * how changes interact with the data structures and physics?
    * [ ] explore performance
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
     [ ] geometry emiiter: particles are emited from multiple sources arranged in some geometrical pattern
   * [x] apply the data structure to each of the particles produced by the emitter in turn
   * [x] add randomness for the particles
4. Control of Particle Parameters
   * [ ] initial velocity
   * [ ] initial color
   * [ ] intensity of gravity
   * [ ] lifetime of particle
   * [ ] number of particles in system
5. Improved/Alternative Redering
   * [ ] draw particles beyond GL_Point
     * faster or slower?
   * Implement at least one of the following:
     * [ ] Particle trails
     * [ ] Render as a little billboarded sprite using GL_QUADS
     * [ ] Others
6. Conduct Experiments to Explore Performance

## Marking Scheme

1. Multiple particles
2. Rendering beyond GL_POINT
3. Interactively control the system to change properties and see appropriate effects
4. Analysis of the fidelity of chosen laws of motion
5. Efficiency of your approach to implement chosen laws of motion
6. Analysis of overall performance / rendering speed and discussion of efficiencies implemented
7. Sophistication and flair

## How to run

## Design and Implementation
