/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Mapeamento de textura 3D
 * 
 * Funcao desse programa: mapear a textura do planeta Terra em uma esfera gluQuadric
 * 
 * Compilar: g++ textura3D.cpp -lglut -lGLU -lGL `pkg-config --libs --cflags opencv` -o texture
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

/* Trata da iluminacao global ambiente da cena */
void global_ambient_light()
{
    GLfloat global_ambient[] = {1.0f, 1.0f, 1.0f, 0.0f};
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

/* Metodo responsavel por configuras as fontes de luz da cena */
void lighting()
{
    /* Define as propriedades da luz */
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat position_type[] = { 2.0f, -2.0f, 2.0f, 0.0f };

    /* Cria uma fonte de luz puntual */
    glLightfv(GL_LIGHT0, GL_POSITION, position_type);
    
    /* Configura os coeficientes ambiente, difuso e especular da fonte de luz */
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    /* configura iluminacao global ambiente */
    global_ambient_light();
    
    /* Habilita o uso de luzes na cena */
    glEnable(GL_LIGHTING);
    
    /* Habilita a luz puntual */
    glEnable(GL_LIGHT0);
}

void desenhaCena()
{
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Coloca na matriz MODELVIEW para desenhar os objetos */
    glMatrixMode(GL_MODELVIEW);
    
    /* Salva o estado atual da matriz de transformacoes */
    glPushMatrix();
    
    /* Realiza as rotacoes convenientes para deixar tudo mais realistico */
    glRotatef(45.0f,1.0f,0.0f,0.0f);
    glRotatef(45.0f,0.0f,1.0f,0.0f);
    glRotatef(theta,0.0f,0.0f,1.0f);
    
    /* Cria um objeto Imagem do OpenCV*/
    Mat img = imread("terra.jpg",CV_LOAD_IMAGE_COLOR);
    
    /* Cria uma textura 3D com base na imagem referenciada pelo objeto img*/
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, img.cols, img.rows, 1, 0, GL_BGR,GL_UNSIGNED_BYTE, img.ptr());
    
    /* Configura os filtros para textura */
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Configura o processo de mapeamento de textura em cada Coordenada
       da textura (S,T,R) */
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    
    /* Habilita a textura 3D recem-criada, ou seja, todos
       os objetos 3D desenhados a seguir terao a textura especificada acima */
    glEnable(GL_TEXTURE_3D);
    
        /* Cria um objeto do tipo GLUquadric que aceita mapeamento de textura*/
        GLUquadric *quadObj = gluNewQuadric();
        
        /* Ajusta propriedades do objeto: estilo de desenho e como modelar as normais das faces */
        gluQuadricDrawStyle(quadObj,GLU_FILL);
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        
        /* Mapeia a textura no objeto */
        gluQuadricTexture(quadObj, GL_TRUE);
        
        /* Cria uma esfera como sendo um quadObj */
        gluSphere(quadObj, 1.5f, 100, 100);
        
        /* Destroi o objeto quadric da memoria */
        gluDeleteQuadric(quadObj);
    
    /* Desabilita o uso da texture especificada */
    glDisable(GL_TEXTURE_3D);
    
    /* Recupera a matriz de transformacoes antes das transformacoes feitas */
    glPopMatrix();
    
    /* Habilita as rotinas de iluminacao da cena */
    lighting();
    
    /* Configura a cena com projecao perspectiva */
    projecaoPerspectiva();
    
    /* Faz a troca constante dos buffers frame buffers para desempenho */
    glutSwapBuffers();
    
    /* Forca o OpenGL a desenhar as rotinas o mais rapido possivel */
    glFlush();
}

/* Funcao que permite animar a cena */
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