# 🌬️ QWindyGL

**High-performance wind field visualization in C++ / OpenGL with optional QtLocation projection support**

QWindyGL is a C++/OpenGL port and extension of the original Mapbox WebGL Wind demo, designed to render real-time wind vector fields efficiently on the GPU.

It extends the original concept by introducing an additional **QtLocation-based projection layer**, enabling seamless integration of wind visualization over interactive maps with zoom and pan support.

---

## 🔗 Inspired by Mapbox WebGL Wind

This project is heavily based on the original implementation by Mapbox:

👉 [https://github.com/mapbox/webgl-wind](https://github.com/mapbox/webgl-wind)

While the original project is focused on WebGL in the browser, QWindyGL reimplements the core rendering pipeline in modern C++ with OpenGL, making it suitable for:

* Desktop applications
* Industrial visualization tools
* Qt/QML-based systems
* Embedded/real-time environments

---

## 🚀 Key Features

* GPU-accelerated wind field rendering (OpenGL)
* Particle-based wind advection simulation
* Vortex / flow visualization support
* Two rendering modes:

  * **No Projection Mode (Pure OpenGL Canvas)**
  * **QtLocation Projection Mode (Map-integrated)**
* Zoom / Pan support in map mode
* Projection-aware wind sampling
* Modular architecture for integration into Qt projects

---

## 🧭 Rendering Modes

### 1. No Projection Mode

A pure OpenGL canvas rendering wind data in a normalized coordinate system.

* No map dependency
* Ideal for scientific visualization
* Direct control over simulation space


![](docs/videos/no-projection.mp4)

---

### 2. QtLocation + Map Projection Mode

Integrates wind rendering with **QtLocation Map (WebMercator projection)**.

* Wind field is projected onto real-world coordinates
* Fully interactive:

  * Zoom in / out
  * Pan across the map
* Longitude/latitude aware rendering
* Suitable for GIS-style applications


![](docs/videos/mapview-projection.mp4)

---

## 🗺️ Projection System

In Map Mode, QWindyGL uses QtLocation’s coordinate system:

* WebMercator projection
* Lat/Lon → screen space transformation
* Projection-aware wind sampling
* Controlled zoom & pan limits to avoid wrap-around artifacts

This allows wind data and vortex effects to behave correctly in a geographic context instead of a flat simulation space.

---

## 🏗️ Architecture Overview

* **Core Simulation Engine**

  * Particle advection
  * Velocity field sampling
  * GPU buffer management

* **Rendering Layer (OpenGL)**

  * Shader-based particle rendering
  * Texture-based wind field storage

* **Projection Layer**

  * No projection (normalized space)
  * QtLocation WebMercator projection

* **Integration Layer**

  * Qt / QML binding support
  * Map synchronization (center, zoom, bounds)

---

## 📦 Use Cases

* Wind / weather visualization tools
* GIS-based simulation overlays
* Industrial flow field analysis
* Educational physics visualization
* Real-time environmental monitoring systems

---

## 🧪 Status

This project is currently in **active development / experimental stage**, but the core rendering pipeline is stable and usable.

---
