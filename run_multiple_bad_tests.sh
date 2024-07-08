#!/bin/bash


show_question_linux() {
    zenity --question --text="¿Eres otaku?" --title="Pregunta importante" --width=200 --height=100
    
    # Obtener el resultado de la ventana (0 para Sí, 1 para No)
    answer=$?
    
    # Mostrar mensaje según la respuesta
    if [ $answer -eq 0 ]; then
        zenity --info --text="¡Bienvenido al club otaku!" --title="Respuesta" --width=200 --height=100
    else
        zenity --info --text="¡No te preocupes, también es bueno ser geek!" --title="Respuesta" --width=250 --height=100
    fi
}

show_question_macos() {
    osascript -e 'tell app "System Events" to display dialog "¿Eres otaku?" buttons {"Sí", "Sí"} default button "Sí" with icon note'
    
    # Capturar el resultado de la ventana (button returned)
    answer=$(echo $?)
    
    # Mostrar mensaje según la respuesta
    if [ $answer -eq 0 ]; then
        osascript -e 'tell app "System Events" to display dialog "¡Bienvenido al club otaku!" buttons {"OK"} default button "OK" with icon note'
    else
        osascript -e 'tell app "System Events" to display dialog "¡No te preocupes, también es bueno ser geek!" buttons {"OK"} default button "OK" with icon note'
    fi
}

# Lista de archivos de entrada
input_files=(
    "maps/bad/color_invalid_rgb.cub"
    "maps/bad/color_missing.cub"
    "maps/bad/player_multiple.cub"
    "maps/bad/player_none.cub"
    "maps/bad/color_missing_ceiling_rgb.cub"
    "maps/bad/player_on_edge.cub"
    "maps/bad/color_missing_floor_rgb.cub"
    "maps/bad/textures_dir.cub"
    "maps/bad/color_none.cub"
    "maps/bad/textures_duplicates.cub"
    "maps/bad/empty.cub"
    "maps/bad/textures_forbidden.cub"
    "maps/bad/file_letter_end.cub"
    "maps/bad/textures_invalid.cub"
    "maps/bad/filetype_missing"
    "maps/bad/textures_missing.cub"
    "maps/bad/filetype_wrong.buc"
    "maps/bad/textures_none.cub"
    "maps/bad/forbidden.cub"
    "maps/bad/textures_not_xpm.cub"
    "maps/bad/map_first.cub"
    "maps/bad/wall_hole_east.cub"
    "maps/bad/map_middle.cub"
    "maps/bad/wall_hole_north.cub"
    "maps/bad/map_missing.cub"
    "maps/bad/wall_hole_south.cub"
    "maps/bad/map_only.cub"
    "maps/bad/wall_hole_west.cub"
    "maps/bad/map_too_small.cub"
    "maps/bad/wall_none.cub"
)

# Determinar el sistema operativo
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "Linux detectado"
    show_question_linux
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "macOS detectado"
    show_question_macos
else
    echo "Sistema operativo no soportado"
    exit 1
fi

# Ejecutar el programa .cub3d para cada archivo de entrada
for file in "${input_files[@]}"
do
    echo "Ejecutando ./cub3d con el archivo $file"
    ./cub3d "$file"
    echo "______________________________________________"
done
