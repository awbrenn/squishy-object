**Author:** Austin Brennan  
**Date:** 9/19/2016  
**Course:** [CPSC 8170 - Physically Based Animation (Dr. Donald House)](https://people.cs.clemson.edu/~dhouse/courses/817/)    
**Institution:** Clemson University  
**Repository:** https://github.com/awbrenn/velocity-field-with-particles

# Voxel Velocity Field With Particles Solver
A particle system that is influenced by the velocities of a velocity field rendered in OpenGL.

## Assignment
For this assignment, you are to extend the concepts that you developed in your bouncing ball project to a large-scale particle system simulation. Your project should include at least one particle generator, and your particles should be able to at least bounce off of fixed polygonal faces. An easy and very effective extension is to make it possible for the particles to bounce off of spherical obstacles. The particle generator should generate unique particles, with attributes drawn from probability distributions chosen appropriately for each particle attribute. Attributes that should be treated in this way should include at least initial position and velocity, mass, lifespan and color. You can use your imagination to come up with other possibilities.

##Features
* FGA file reader for reading in velocity grids
* Particle emission randomly distributed in a cube
* Multiple emitter support
* Multiple sphere collider support
* Adjustable particle color
* Velocity grid visualization

## Un-Implemented
* Parameter file option for multiple emitters
* Parameter file option for multiple colliders
* Particle emission on sphere surfaces
* Particle emission within a sphere
* Collision with polygonal planes
* Improved rendering of particles


## Compilation
```
$> make
```


## Usage
```
$> ParticleSystem parameters
```

## Interaction
```
r or R - Activate render mode
l or L - Activate line render in render mode
p or P - Activate point render in render mode
d or D - Activate debug view of particle simulation
g   - Toggle grid
esc - Quit the program
q   - Quit the program
```

## Acknowledgements
Vector Class - Donald House

Matrix Class - Donald House

Camera Class - Christopher Root, Donald House, Yujie Shu
