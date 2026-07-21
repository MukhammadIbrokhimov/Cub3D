# cub3D

[![build](https://github.com/MukhammadIbrokhimov/Cub3D/actions/workflows/build.yml/badge.svg)](https://github.com/MukhammadIbrokhimov/Cub3D/actions/workflows/build.yml)

A first-person raycasting engine written in C, inspired by Wolfenstein 3D. Walls are rendered by casting rays across the field of view with the DDA algorithm; each ray's hit point selects a texture column and draws a vertically-scaled slice. Runs on Linux (X11 / MinilibX) and macOS. Part of the 42 Berlin Common Core.

Built with [Ghazaleh Ansari](https://github.com/ghazalehans).

## Features

### Mandatory
- DDA-based raycasting with fish-eye correction
- Textured walls with per-direction textures (N / S / E / W)
- Configurable floor and ceiling colours (RGB)
- Map parser for the `.cub` format with enclosure validation via flood fill
- Smooth WASD movement and arrow-key rotation
- Proper exit cleanup (MLX windows, images, memory)

### Bonus
- Minimap overlay with player position and ray visualisation
- Extra parsing paths and texture-coordinate helpers
- Additional maps (`cray`, `hard`, `medium`, `no_gravity`, `simple`, `zelij`) with custom Berlin-themed textures

## Architecture

```
.cub file  ─►  parser  ─►  validated map + textures + spawn
                               │
                               ▼
 keyboard ─►  game loop  ─►  raycaster (DDA)  ─►  renderer  ─►  MLX
```

- **Parser** (`src_mandatory/parsing/`) — reads the `.cub` header, loads textures, extracts map dimensions, then runs flood fill from the spawn point to prove the map is fully enclosed.
- **Raycaster** (`src_mandatory/raycasting/raycasting.c`) — classic DDA: compute `delta_dist` and `side_dist`, step along the grid until a wall is hit, record side and distance.
- **Renderer** (`src_mandatory/raycasting/rendering.c`, `drawing.c`) — translates ray distance into a scaled vertical slice and draws it column-by-column into an MLX image buffer.

## Build and run

### Linux

```bash
sudo apt-get install -y libx11-dev libxext-dev libbsd-dev zlib1g-dev
# MinilibX auto-detected in mlx_linux/ if present, otherwise system-installed
make          # builds cub3D (mandatory)
make bonus    # builds with minimap
./cub3D maps/mandatory/sample.cub
```

### macOS

MinilibX for macOS is expected in `mlx_macos/` at the repo root. If you don't have it, grab the 42 copy, or let `make` print the expected location.

```bash
make
./cub3D maps/mandatory/sample.cub
```

## Controls

| Key | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move forward / strafe left / back / strafe right |
| `←` / `→` | Rotate view |
| `ESC` | Exit |

## Map format

A `.cub` file is a textures-and-colours header followed by a grid of `0` (empty) / `1` (wall) / `N S E W` (spawn facing direction):

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm
F 220,100,0
C 225,30,0

1111111111
1000000001
100N000001
1000000001
1111111111
```

The parser enforces: exactly one spawn, fully enclosed by walls, all four textures present, valid RGB colours.

## Constraints

From the 42 subject:

- C, compiled with `cc -Wall -Wextra -Werror`
- 42 norm: 80-char lines, ≤25-line functions, no globals
- Only MinilibX, libc, and maths functions allowed
- No leaks (including on error paths and on exit)
- Map validation must reject malformed input with a clear error

## What was technically hard

- **Flood-fill enclosure check**: proving the map is closed in the face of irregular shapes, odd spacing, and trailing characters.
- **Texture selection per ray hit**: deciding which of the four textures applies based on which side of the grid cell was hit, then mapping pixel columns correctly without stretching.
- **MLX memory ownership**: every image and window handle must be destroyed before exit; a single stray handle causes a visible leak.
- **Avoiding fish-eye distortion**: using perpendicular distance instead of Euclidean distance when computing wall-slice height.

## Authors

[Mukhammad Ibrokhimov](https://github.com/MukhammadIbrokhimov) and [Ghazaleh Ansari](https://github.com/Ghazaleh-ans).
