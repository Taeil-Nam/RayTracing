# RayTracing
This project is made by [Taeil-Nam](https://github.com/Taeil-Nam), [GunJoong-Kim](https://github.com/gunjoong-kim)

<!-- LIMITATION -->
## Limitation
- Program doesn't use GPU, only use CPU.
- Not supported Real-Time Rendering.
- In "PATH" rendering mode, program uses Path Tracing and it takes a more time to rendering.
- In "PATH" rendering mode, if you want to see clean image, increase SAMPLE_PER_PIXEL in inc/minirt.h:17
  - Recommend increasing the value at least 500 but rendering would be **TOO SLOW**..

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites
- Intel CPU Mac
- MacOS Version = 12.6.2
- Clang Version = 12.0.0
- MiniLibX (graphics library)
- swiftc 5.7.2 (to compile MiniLibX)

### Installation
1. Git clone
   ```sh
   $> git clone https://github.com/Taeil-Nam/RayTracing.git
   ```
2. Move to project directory
   ```sh
   $> cd RayTracing/
   ```
3. Use "make" command to create program
   ```sh
   $> make
   ```

<!-- USAGE -->
## Usage
Exec the program with valid map file as argument.

Valid map file name format = map/[file name].rt

Ex) rendering map "box.rt"
   ```sh
   $> ./RayTracing map/box.rt
   ```

_please refer to the [Demo video](https://www.youtube.com/watch?v=Fi8H6HPMALA)_

📌All file names with "_bonus" shown in the video have been changed to file names with "_bonus" removed.

### Rendering mode
You can select the rendering mode by editing the code.
1. PHONG(default mode)
   - Uses Phong Reflection model. 
2. PATH
   - Uses Path Tracing model.

Ex)
    in src/main.c:49 ```minirt->illumination = PHONG;``` or ```minirt->illumination = PATH;```

<!-- FEATURES -->
## Features
- Ray Tracing
- Phong Reflection
- Path Tracing
- Rendering object (sphere, plane, cylinder, cone)
- Camera
- Multi-spot light
- Checkerboard texture
- Image texture
- Bump map (Normal map) texture
- multi-threading
- BVH (Boundary Volume Hierarchy)

<!-- RESULTS -->
## Results
- In "PATH" rendering mode, SAMPLE_PER_PIXEL = 2000
![남태일-RT](https://github.com/Taeil-Nam/RayTracing/assets/67255013/e5f7d292-12a3-452b-917e-4f0f2d880f6b)


<!-- LICENSE -->
## License
Distributed under the MIT License. See `LICENSE.txt` for more information.

<!-- CONTACT -->
## Contact
Taeil-Nam - nam0314@gmail.com

Project Link: [https://github.com/Taeil-Nam/RayTracing](https://github.com/Taeil-Nam/RayTracing)
