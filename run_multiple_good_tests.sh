#!/bin/bash

# Lista de archivos de entrada
input_files=(
    "maps/good/creepy.cub"
    "maps/good/sad_face.cub"
    "maps/good/test_pos_bottom.cub"
    "maps/good/test_whitespace.cub"
    "maps/good/cheese_maze.cub"
    "maps/good/square_map.cub"
    "maps/good/test_pos_left.cub"
    "maps/good/works.cub"
    "maps/good/dungeon.cub"
    "maps/good/subject_map.cub"
    "maps/good/test_pos_right.cub"
    "maps/good/library.cub"
    "maps/good/test_map.cub"
    "maps/good/test_pos_top.cub"
    "maps/good/matrix.cub"
    "maps/good/test_map_hole.cub"
    "maps/good/test_textures.cub"
)

# Ejecutar el programa .cub3d para cada archivo de entrada
for file in "${input_files[@]}"
do
    echo "Ejecutando ./cub3d con el archivo $file"
    ./cub3d "$file"
    echo "______________________________________________"
done
