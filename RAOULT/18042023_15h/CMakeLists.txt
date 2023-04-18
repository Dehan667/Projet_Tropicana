cmake_minimum_required(VERSION 3.10)  # Version minimale de CMake requise

project(Projet)  # Nom de votre projet

# Déclaration des fichiers sources de votre projet
set(SOURCES
    k8055.cpp
    main.cpp
    # Ajoutez d'autres fichiers sources si nécessaire
)

set(HEADERS
    k8055.h
)


# Créez l'exécutable de votre projet
add_executable(Projet ${SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

include_directories(${LIBUSB_INCLUDE_DIRS})
target_link_libraries(Projet ${LIBUSB_LIBRARIES})