cmake_minimum_required(VERSION 3.0)
project(CaptureImage)

# Encontre o OpenCV
find_package(OpenCV REQUIRED)

# Adicione o executável
add_executable(capture_image capture_image.cpp)

# Vincule as bibliotecas do OpenCV
target_link_libraries(capture_image ${OpenCV_LIBS})
