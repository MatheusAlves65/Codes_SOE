cmake_minimum_required(VERSION 3.0)
project(MeuProjeto)

# Encontre as bibliotecas necessárias
find_package(OpenCV 4 REQUIRED)
find_library(WIRINGPI_LIB wiringPi)
find_library(TESSERACT_LIBRARIES tesseract)
find_library(LEPTONICA_LIBRARIES leptonica)

# Inclua os diretórios de cabeçalho
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    #${WIRINGPI_INCLUDE_DIRS}
    ${TESSERACT_INCLUDE_DIRS}
    ${LEPTONICA_INCLUDE_DIRS}
)

# Adicione os executáveis
add_executable(seu_programa main.cpp)

# Vincule as bibliotecas necessárias
target_link_libraries(seu_programa 
    ${OpenCV_LIBS}
    ${WIRINGPI_LIB}
    ${TESSERACT_LIBRARIES}
    ${LEPTONICA_LIBRARIES}
    pthread # Se o seu código usar threads
)
