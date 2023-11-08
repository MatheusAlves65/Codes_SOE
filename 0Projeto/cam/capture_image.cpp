#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture capture(0); // 0 é o índice da câmera USB padrão

    if (!capture.isOpened()) {
        std::cout << "Não foi possível acessar a câmera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    capture >> frame;

    if (frame.empty()) {
        std::cout << "Não foi possível capturar a imagem." << std::endl;
        return -1;
    }

    cv::imwrite("captured_image.jpg", frame);

    return 0;
}
