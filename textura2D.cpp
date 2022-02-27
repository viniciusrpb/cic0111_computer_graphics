/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Mapeamento de textura
 * 
 * Funcao desse programa: apresentar como realizar o mapeamento de textura em objetos 2D
 * 
 * Compilar: g++ textura2D.cpp -lglut -lGLU -lGL `pkg-config --libs --cflags opencv` -o texture
 * Executar: ./texture
 */

#include<GL/glut.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

GLfloat theta = 0.0f;

/* Projecao perspectiva simetrica utilizando gluPerspective */
void projecaoPerspectiva()
{
    /* define a cor de fundo */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    /* habilita o teste de profundidade */
    glEnable(GL_DEPTH_TEST);
    
    /* define a matriz de transformacoes como a atual */
    glMatrixMode(GL_MODELVIEW);
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define a posicao da camera, para onde ela aponta, e a orientacao da camera */
    gluLookAt(3.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f);
    
    /* define a matriz atual como a de projecao */
    glMatrixMode(GL_PROJECTION); 
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define uma projecao perspectiva */
    gluPerspective(45.0f,1.0f,1.0f,30.0f);
}


void desenhaCena()
{
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Coloca na matriz MODELVIEW para desenhar os objetos */
    glMatrixMode(GL_MODELVIEW);
    
    /*
     * GLubyte matrixTex[32][32][4];
     glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,32,32,0,GL_RGBA,GL_UNSIGNED_BYTE,matrixTex); */
    
    /* Cria um objeto Imagem do OpenCV*/
    Mat img = imread("grama.jpg");
    
    /* Define uma textura 2D a partir da imagem do OpenCV no objeto img*/
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, img.cols , img.rows , 0 , GL_BGR , GL_UNSIGNED_BYTE,img.ptr());
    
    /* Configura os filtros para textura */
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    /* Configura o processo de mapeamento de textura em cada Coordenada
       da textura (S,T) */
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    /* Habilita a textura 2D recem-criada, ou seja, todos
       os objetos desenhados terao a textura especificada acima */
    glEnable(GL_TEXTURE_2D);
    
    /* Define um quadrado, juntamente com as coordenadas de textura */
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex2d(-0.5, 0.5);
        
        glTexCoord2f(0.0, 0.0);
        glVertex2d(-0.5, -0.5);
        
        glTexCoord2f(1.0, 0.0);
        glVertex2d(0.5, -0.5);
        
        glTexCoord2f(1.0, 1.0);
        glVertex2d(0.5, 0.5);
    glEnd();
        
    /* Desabilita o uso da texture especificada */
    glDisable(GL_TEXTURE_2D);
    
    glPushMatrix();
        glTranslatef(2.0f,0.0f,0.0f);
        glutWireSphere(1.5f,40,40);
    glPopMatrix();
    
    /* Configura a cena com projecao perspectiva */
    projecaoPerspectiva();
    
    /* Faz a troca constante dos buffers frame buffers para desempenho */
    glutSwapBuffers();
    
    /* Forca o OpenGL a desenhar as rotinas o mais rapido possivel */
    glFlush();

}

void idleFunc()
{
     /* Atualiza o angulo de rotacao do planeta */
     theta += 0.05f;
     
     /* Forca a atualizacao da cena na tela */
     glutPostRedisplay();
     
     glFlush();
}

int main(int argc, char **argv)
{
    /* Iniciar a GLUT para que recursos computacionais sejam 
       disponibilizados para este programa */
    glutInit(&argc,argv);
    
    /* Iniciar o buffer de memoria para armazenar a imagem 
       GLUT_SINGLE */
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    /* Tamanho da janela principal */
    glutInitWindowSize(500,500);
    
    /* Coordenadas de tela inicial da janela do OpenGL no canto esquerdo */
    glutInitWindowPosition(100,100);
    
    /* Apresenta a janela na tela*/
    glutCreateWindow("Textura 2D");
    
    /* Funcao que inicia o processo de renderizacao */
    glutDisplayFunc(desenhaCena);
    
    /* Animacoes */
    glutIdleFunc(idleFunc);
    
    /* Coloca esse programa OpenGL em loop infinito: deve ser o ultimo comando do codigo-fonte */
    glutMainLoop();
    
    /* retorna para o sistema sucesso um sinal de finalizacao 
     desse programa*/
    return 0;
}