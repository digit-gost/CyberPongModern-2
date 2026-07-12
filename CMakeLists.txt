cmake_minimum_required(VERSION 3.16)
project(CyberPongModern CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Options de compilation strictes — adaptees selon le compilateur.
# MSVC (Windows) ne comprend pas -Wall/-Wextra/-Wpedantic de la meme facon
# que GCC/Clang (macOS, Linux) : on utilise /W4, son equivalent le plus proche.
# ---------------------------------------------------------------------------
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---------------------------------------------------------------------------
# Windows : linking statique de SFML + runtime C++ statique, pour que
# l'executable final ne depende d'aucune DLL externe (ni SFML, ni le
# Visual C++ Redistributable) sur la machine qui l'execute.
# ---------------------------------------------------------------------------
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    add_compile_definitions(SFML_STATIC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# NOTE : le sujet demande SFML 2.5, mais seule SFML 3.x etait disponible
# facilement au moment du developpement (Homebrew sur macOS Apple Silicon).
# L'API a ete adaptee en consequence (cf. rapport, section "choix techniques").
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

# Collecter tous les fichiers sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

add_executable(CyberPongModern ${SOURCES})
target_include_directories(CyberPongModern PRIVATE src/)
target_link_libraries(CyberPongModern PRIVATE
    SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Bibliotheques systeme Windows necessaires au linking statique de SFML
# (deja presentes sur toute machine Windows, rien a telecharger)
if (WIN32)
    target_link_libraries(CyberPongModern PRIVATE
        opengl32 winmm gdi32 freetype ws2_32)
endif()

# ---------------------------------------------------------------------------
# Linux : dire a l'executable de chercher ses bibliotheques partagees (.so)
# dans son propre dossier "lib/" plutot que dans les emplacements systeme,
# pour pouvoir le distribuer sans que SFML soit installee sur la machine
# cible (voir README pour le script de bundling des .so).
# ---------------------------------------------------------------------------
if (UNIX AND NOT APPLE)
    set_target_properties(CyberPongModern PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "$ORIGIN/lib")
endif()

# Copier les assets automatiquement (fonctionne aussi sur Windows/Visual
# Studio grace au generator-expression, qui gere les dossiers Debug/Release)
add_custom_command(TARGET CyberPongModern POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:CyberPongModern>/assets)

# ---------------------------------------------------------------------------
# Cible de verification memoire avec valgrind (Linux/macOS uniquement —
# valgrind n'existe pas sous Windows, et n'est pas fiable sur macOS Apple
# Silicon ; voir cible CyberPongModern_asan ci-dessous pour cette derniere).
# ---------------------------------------------------------------------------
if (NOT WIN32)
    add_custom_target(memcheck
        COMMAND valgrind --leak-check=full --error-exitcode=1 ./CyberPongModern
        DEPENDS CyberPongModern)
endif()

# ---------------------------------------------------------------------------
# Cible de debug avec AddressSanitizer — alternative fiable a valgrind sur
# macOS (notamment Apple Silicon). Non disponible avec la syntaxe MSVC
# standard, donc exclue sous Windows.
# ---------------------------------------------------------------------------
if (NOT MSVC)
    add_executable(CyberPongModern_asan ${SOURCES})
    target_include_directories(CyberPongModern_asan PRIVATE src/)
    target_link_libraries(CyberPongModern_asan PRIVATE
        SFML::Graphics SFML::Window SFML::System SFML::Audio)
    target_compile_options(CyberPongModern_asan PRIVATE -fsanitize=address -g)
    target_link_options(CyberPongModern_asan PRIVATE -fsanitize=address)
endif()