#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

int main() {
    CvCapture* capture = cvCreateCameraCapture(0); // 0 é o índice da câmera USB padrão

    if (!capture) {
        printf("Não foi possível acessar a câmera.\n");
        return -1;
    }

    IplImage* frame = cvQueryFrame(capture);

    if (!frame) {
        printf("Não foi possível capturar a imagem.\n");
        return -1;
    }

    cvSaveImage("captured_image.jpg", frame);

    cvReleaseCapture(&capture);

    return 0;
}
