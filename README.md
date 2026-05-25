# particle-system - GPU Particle Simulator

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

### Emitter & Gravity
- **Alt + Left Click**: Move emitter position
- **Alt + Right Click**: Move gravity point position

### Particle Reset Shapes
- **1**: Reset particles to sphere shape
- **2**: Reset particles to cube shape

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
