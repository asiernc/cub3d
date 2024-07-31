<div align="center">
<h1 align="center">
    <br>Cub3D</br>
</h1>
<p align="center">
    <img src="./cub3d.png" alt="cub3d logo"/>
</p>
<p align="center">
    <img src="https://img.shields.io/badge/Barcelona-100000?style=flat-square&logo=42&logoColor=white&labelColor=000000&color=000000" alt="42 Barcelona"/>
</p>
</div>

## Table of Contents
- [Summary](#-summary)
- [Simple example of functionality](#-simpleexampleoffunctionality)
- [Usage](#-usage)
- [Usage](#-screenshots)
- [Installation](#-installation)


# Summary

### What is "cub3D"?
Cub3D is a 42 school team project to create a dynamic view inside a 3D maze.
Using the MiniLibX42 library (codam), we must implement raycasting in the style of the famous Wolfenstein 3D game, the first true FPS in videogame history.


## Simple example of functionality
The following is an example of a *.cub file we use as an input for our program:

```
NO textures/purplestone.xpm42
SO textures/redbrick.xpm42
WE textures/wood.xpm42
EA textures/bluestone.xpm42

F 18,53,25
C 153,204,255

111111111111
1       1111
1      10001
111111111111
10S000000001
111111111111
11         1
111111111111

```

# Usage

```sh
./cub3D [map file path]
```

Example: 

```sh
./cub3D maps/good/subject_map.cub
```
💡 Tip: .

## Screenshots

![App Screenshot](./screenshot.png)

## Installation

1. Clone the repository:
```sh
git clone
```

2. Change to the project directory:
```sh
cd cub3d
```

3. Compile the library:

    Using Makefile you can create the file cub3D<br/>
    Makefile has 4 main options:<br/>
    ```sh
    make
    ```
    to compile C files - create object files and library libft.a
    ```sh
    make clean
    ```
    to remove object files.
    ```sh
    make fclean
    ```
    remove libft.a file.
    ```sh
    make re
    ```
    recompile the library.



[**Return**](#Top)
