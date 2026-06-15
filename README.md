# particle-system - GPU Particle Simulator

## Demo
<video src="https://github-production-user-asset-6210df.s3.amazonaws.com/142665919/607970201-8473ecb1-2a20-4235-892b-85215d57e9d3.mp4?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAVCODYLSA53PQK4ZA%2F20260615%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20260615T141722Z&X-Amz-Expires=300&X-Amz-Signature=d8976876250aaa491eef7fb5fdbb22f3364523c44e6b37d1e58d3501c3d1a734&X-Amz-SignedHeaders=host&response-content-type=video%2Fmp4" autoplay loop muted playsinline></video>

## Gallery

<p align="center">
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/e7aae392-2040-4512-87ea-72a1ffc688ca" title="Cube Shape"/>
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/317fdb4c-522b-4fa9-b060-792ce4adfb46" title="Sphere Shape with Smoke Mode"/>
</p>
<p align="center">
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/892e7bf1-9130-4234-bc72-de39a364e404" title="Gravity Color Mode"/>
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/e8417efe-3743-485a-89e1-7e022b6939ae" title="Mouse Position Color Mode"/>
</p>
<p align="center">
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/8b26c2df-3dbf-434a-b1ac-c17242857dd5" title="Flame Color Mode"/>
  <img width="49%" alt="Image" src="https://github.com/user-attachments/assets/920576f7-2902-4310-9e52-90e86f1076c8" title="Emitter Color Mode"/>
</p>

---

## Overview

**particle-system** is a real-time GPU-driven particle simulator built with Modern OpenGL.  
The entire simulation runs on the GPU via **compute shaders**, no particle data ever touches the CPU at runtime.

The project focuses on:

- Massively parallel particle simulation using compute shaders
- GPU-side state management with Shader Storage Buffer Objects (SSBO)
- Real-time interaction with simulation parameters
- Implementing a minimal rendering and camera system
- Designing a clean, modular architecture

## Features

### GPU-Driven Simulation
- Full simulation running on compute shaders
- Particle positions, velocities, and lifetimes managed via SSBOs
- Gravity point and emission point stored GPU-side and updated in real time
- Scales to several million particles with no CPU bottleneck

### Color Presets
- Distance-based coloring relative to the mouse cursor
- Distance-based coloring relative to the emitter
- Distance-based coloring relative to the gravity point
- Lifetime-based coloring (color evolves as the particle ages)

### Particle Controls
- Adjust active particle count at runtime (up to the simulation maximum)
- No dynamic allocation, unused particles are simply skipped by the shader
- Allows live tuning from e.g. 100k down to a few thousand and back up

### Simulation Time Control
- Simulation speed adjustable from 0% (full pause) to 100%
- Pausing freezes everything including particle lifetimes
- Useful for inspecting slow motion or frame-by-frame movement

### Emitter & Gravity
- Emitter position editable in real time
- Gravity point position editable in real time
- Toggle gravity on/off

### Particle Reset Shapes
- Reset all particles into a sphere or cube formation

### Camera System
- Interactive camera to navigate around the simulation
- Zoom and look-around controls

### Smoke Mode (F2)
- Particles rendered as textured quads instead of single pixels
- Opacity and size evolve over the particle lifetime for a natural fade-in/out
- Upward velocity applied by default to simulate rising smoke
- Gravity behaves like wind when applied away from the emitter

## Architecture

Organized into `core/`, `graphics/`, `simulation/`, and `scene/` modules — similar structure to [scop](https://github.com/qmorineau/scop).

---

## Keybindings

Since the program does not display help in the window, here is the complete control list.

### Camera Controls
- **W / A / S / D**: Move the camera
- **Mouse**: Look around
- **Scroll Wheel**: Zoom
- **R**: Recenter the camera

### Simulation Controls
- **Up / Down Arrow**: Increase / Decrease active particle count
- **Left / Right Arrow**: Increase / Decrease simulation speed
- **G**: Toggle gravity on / off
- **E**: Toggle emitter on / off

### Emitter & Gravity
- **Alt + Left Click**: Move emitter position
- **Alt + Right Click**: Move gravity point position

### Particle Reset Shapes
- **1**: Reset particles to sphere shape
- **2**: Reset particles to cube shape

### Particle Mode
- **F1**: Default mode, 1 particle = 1px
- **F2**: Smoke mode

### Color Presets
- **C**: Cycle through color presets

### Misc
- **Tab**: Show cursor (required to set emitter and gravity positions)
- **Left Click** *(cursor visible)*: Recapture mouse
- **Esc**: Quit

---

## Compiling

particle-system uses **C++17**, **OpenGL**, **GLFW**, and **GLAD**.

### Requirements

- C++17 compiler
- Make
- OpenGL 4.3+ *(compute shader support required)*

> GLFW and GLAD are bundled — a single `make` is all you need.

## Quick Start

```bash
make
./particle-system
```

---

Developed by *Quentin Morineau*
