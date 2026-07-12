cmake_minimum_required(VERSION 3.16)
project(CyberPongModern CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options de compilation strictes — OBLIGATOIRES
add_compile_options(-Wall -Wextra -Wpedantic)

# NOTE : le sujet demande SFML 2.5, mais seule SFML 3.x est disponible
# facilement via Homebrew sur macOS (Apple Silicon) à la date du projet.
# L'API a été adaptée en conséquence (cf. rapport, section "choix techniques").
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

# Collecter tous les fichiers sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

add_executable(CyberPongModern ${SOURCES})
target_include_directories(CyberPongModern PRIVATE src/)
target_link_libraries(CyberPongModern PRIVATE
    SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Copier les assets automatiquement
add_custom_command(TARGET CyberPongModern POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:CyberPongModern>/assets)

# Cible de vérification mémoire
add_custom_target(memcheck
    COMMAND valgrind --leak-check=full --error-exitcode=1 ./CyberPongModern
    DEPENDS CyberPongModern)

add_executable(CyberPongModern_asan ${SOURCES})
target_include_directories(CyberPongModern_asan PRIVATE src/)
target_link_libraries(CyberPongModern_asan PRIVATE
    SFML::Graphics SFML::Window SFML::System SFML::Audio)
target_compile_options(CyberPongModern_asan PRIVATE -fsanitize=address -g)
target_link_options(CyberPongModern_asan PRIVATE -fsanitize=address)