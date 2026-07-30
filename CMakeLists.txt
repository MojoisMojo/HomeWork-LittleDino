cmake_minimum_required(VERSION 3.20)

project(HomeWorkLittleDino LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(DinoGame
    src/DinoGame.c
    src/Base.c
    src/Box.c
    src/Cloud_Moon.c
    src/BGD.c
    src/DinoCharecter.c
    src/GndObs.c
    src/SkyObs.c
    src/Obs.c
    src/Help.c
    src/WordsAndFont.c
)

# Keep a console for Debug diagnostics, but hide it in release-style builds.
if(WIN32)
    set_property(TARGET DinoGame PROPERTY WIN32_EXECUTABLE
        "$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>"
    )
endif()

target_link_libraries(DinoGame PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    m
)

foreach(resource_dir IN ITEMS image font data)
    add_custom_command(TARGET DinoGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/src/${resource_dir}"
            "$<TARGET_FILE_DIR:DinoGame>/${resource_dir}"
        VERBATIM
    )
endforeach()
