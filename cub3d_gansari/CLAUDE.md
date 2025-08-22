# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

- `make all` - Build the mandatory version (no conditional compilation)
- `make bonus` - Build the bonus version with minimap and mouse controls
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Rebuild the project
- `make norm` - Check coding style with norminette (if available)
- `make test` - Test with sample map (requires maps/simple.cub)
- `make info` - Show project configuration details (shows current build type)
- `make install-deps` - Install system dependencies

## Running the Game

```bash
./cub3D maps/simple.cub    # Run with simple map
./cub3D maps/medium.cub    # Run with medium complexity map
./cub3D maps/hard.cub      # Run with hard map
```

## Project Architecture

This is a 3D raycasting game engine (similar to Wolfenstein 3D) built in C using the MLX graphics library. The codebase is organized into **two separate, complete code series** - no conditional compilation:

### Code Organization

**Mandatory Version** (`src_mandatory/`, `includes_mandatory/`):
- Clean, minimal raycasting engine
- Keyboard-only controls
- No minimap
- 19 source files

**Bonus Version** (`src_bonus/`, `includes_bonus/`):
- Enhanced raycasting engine with minimap
- Keyboard + mouse controls
- Minimap display system
- 21 source files (includes minimap.c and game_init_bonus.c)

### Core Systems (Both Versions)

1. **Parsing System** (`parsing/`):
   - Validates and parses .cub map files
   - Extracts textures, colors, and map data
   - Validates map walls and player positioning

2. **Game Engine** (`game/`):
   - Game initialization and state management
   - Input handling (keyboard only in mandatory, +mouse in bonus)
   - Player movement with collision detection

3. **Raycasting Engine** (`raycasting/`):
   - Core raycasting algorithm implementation
   - Wall texture rendering
   - Background color rendering
   - Minimap system (bonus only)

4. **Memory Management**:
   - MLX resource cleanup
   - String array management
   - Texture path management

### Key Data Structures

- `t_game` - Main orchestrating structure containing all subsystems
- `t_map` - Map configuration and grid data
- `t_player` - Player position, direction, and movement state
- `t_ray` - Raycasting calculation data
- `t_textures` - Wall texture and display buffer management
- `t_mlx` - MLX window and graphics management

### Map File Format

Map files (.cub) contain:
- Texture paths: `NO`, `SO`, `EA`, `WE` for wall directions
- Colors: `F` (floor), `C` (ceiling) in RGB format
- Map grid with `1` (walls), `0` (empty), `N/S/E/W` (player spawn)

### Platform Support

The Makefile automatically detects the platform and configures MLX accordingly:
- **Linux**: Uses system MLX or local mlx_linux directory
- **macOS**: Uses local mlx_macos directory

### Key Differences Between Versions

**Mandatory Features**:
- WASD movement, arrow key rotation
- 3D raycasted walls with textures
- Floor and ceiling colors
- Clean, minimal implementation

**Bonus Features** (additional to mandatory):
- Minimap showing player position and map layout
- Mouse controls for rotation
- Enhanced player movement tracking
- Additional minimap initialization system

### Development Notes

- **NO conditional compilation** - completely separate code bases
- Uses 42 School coding standards (norminette)
- Custom libft library for utility functions
- Optimized compilation with `-O3` flag
- Comprehensive error handling and memory management
- Smooth player movement and rotation
- Smart build system automatically detects and rebuilds when switching versions