/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Modelos de iluminacao
 * 
 * Funcao desse programa: apresentar as interacoes de iluminacao entre
 *                        objetos de uma cena
 * 
 * Compilar: g++ textura3D.cpp -lglut -lGLU -lGL `pkg-config --libs --cflags opencv` -o texture
 * Executar: ./texture
 */

#include<GL/glut.h>
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

GLfloat theta = 0.0f;
GLfloat p = 2.0f;
GLfloat angle = 0.0f;
int mode=2;

GLfloat position_type[] = { -5.0f, 5.0f, 5.0f, 0.0 };

/* Projecao perspectiva simetrica 
 utilizando gluPerspective */
void projecaoPerspectiva()
{
    /* define a cor de fundo */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
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


void ambient_light()
{
    
    GLfloat global_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);

}

void especular()
{
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void lighting()
{
    //GL_LIGHT0, GL_LIGHT1, ... , GL_LIGHT7
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    /* Cria uma fonte de luz puntual */
    glLightfv(GL_LIGHT0, GL_POSITION, position_type);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    ambient_light();
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void desenhaCena()
{

    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    glRotatef(45.0f,1.0f,0.0f,0.0f);
    glRotatef(45.0f,0.0f,1.0f,0.0f);
    glRotatef(theta,0.0f,0.0f,1.0f);
    
    Mat img = imread("terra.jpg",CV_LOAD_IMAGE_COLOR);
    
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, img.cols, img.rows, 1, 0, GL_BGR,GL_UNSIGNED_BYTE, img.ptr());
        
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        
    glEnable(GL_TEXTURE_3D);
    
        GLUquadric *quadObj = gluNewQuadric();
        
        gluQuadricDrawStyle(quadObj,GLU_FILL);
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        
        gluQuadricTexture(quadObj, GL_TRUE);
        gluSphere(quadObj, 1.5f, 100, 100);
        
        gluDeleteQuadric(quadObj);
        
    glDisable(GL_TEXTURE_3D);
    
    glPopMatrix();
    
    lighting();
    
    projecaoPerspectiva();
    glutSwapBuffers();
    glFlush();
}


void idleFunc()
{
    
     theta += 0.05f;
     
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
    glutCreateWindow("Textura 3D");
    
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