# High-Performance Particle System (C++)

A custom particle engine built from scratch using OpenGL and C++. Designed to handle mass-rendering through instancing and memory pooling.

![Particle System Demo]("./GIFs/Particle_System_01.gif")

## 🚀 Key Features
* **Instanced Rendering:** Utilizes `glDrawElementsInstanced` to render thousands of particles in a single GPU draw call.
* **Object Pooling:** Implemented a custom Ring Buffer pool to eliminate runtime allocations (`new`/`delete`) and prevent memory fragmentation.
* **Ray-Casting:** Implemented 3D Ray-Plane intersection to spawn particles exactly at the mouse position in world space.
* **Visuals:** Additive blending and lifecycle interpolation for color/size/rotation.

## 🛠️ Tech Stack
* **Language:** C++17
* **Graphics API:** OpenGL 3.3 (Core Profile)
* **Dependencies:** GLFW, GLAD, GLM
* **Build System:** Visual Studio / CMake

## 🎮 Controls
* **Left Mouse (Hold):** Spawn Particles
* **WASD:** Move Camera
* **Scroll Wheel:** Zoom In/Out

---
*Author: Anurag Bhatt*