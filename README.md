# Ray Tracing project
## Development Environment
- MAC OS 10.15.7
- Intel CPU
- Apple clang version 12.0.0 (clang-1200.0.32.28)

## Make program
- make : basic ray tracing program. (Phong Reflection Model)
- make bonus : advanced ray tracing program. (Phong Reflection Model and Path Tracing)

## Execute program
- If you create program using "make" command
  - "./miniRT [map file name].rt"
  - Ex) ./miniRT maps/box.rt
- If you create program using "make bonus" command
  - "./miniRT [map file name]_bonus.rt"
  - Ex) ./miniRT maps/box_bonus.rt

## Advanced feature
- If you create program using "make bonus", you can use advanced feature as following:
  - Multi-Threading : Program created including Multi-Threading feature. Therefore program optimize the loading process.
  - Change Rendering Mode : If you want to change rendering mode to Path Tracing, you can modify code "minirt->illumination = PHONG;" to "minirt->illumination = PATH;" in "bonus/src/main_bonus.c".

## Feature
- miniLibX(graphics library).
- Ray Tracing.
- Phong Reflection.
- Path Tracing.
- Rendering object(sphere, plane, cylinder, cone).
- Camera.
- Multi-spot light.
- Checkerborad texture.
- Bump map(Normal map) texture.

## Limitation
- In "PATH" rendering mode, program uses Path Tracing and it takes a more time to rendering.
