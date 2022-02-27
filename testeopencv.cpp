/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * 
 * Funcao desse programa: testa se o OpenCV estah corretamente instalado
 * 
 * Compilar: g++ testeopencv.cpp `pkg-config --libs --cflags opencv` -o testar
 * Executar: ./testar
 */

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{

    Mat img = imread("grama.jpg",CV_LOAD_IMAGE_COLOR);
    
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow("Display window",img);
    waitKey(0); 
    return 0;
}
