/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Transformacoes Geometricas 2D 
 * 
 * Funcao desse programa: desenha um triangulo na tela 
 * 
 * Compilar: g++ transfGeom2D.cpp -lglut -lGLU -lGL -o transf
 * Executar: ./transf
 */

#include<GL/glut.h>
#include<iostream>

using namespace std;

void drawTriangle()
{
    /* Cria um triangulo preenchido */
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.3f, 0.4f);
    glEnd();
}

void drawRectangle()
{
    /* Redesenha "o mesmo" triangulo transladado em vermelho */
    glBegin(GL_QUADS);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.8f, 0.5f);
        glVertex2f(0.8f, 0.6f);
        glVertex2f(0.5f, 0.6f);
    glEnd();
}

/* Funcao que faz a escala*/
void escala2D(GLfloat sx, GLfloat sy){
  
    GLfloat cx,cy;
    
    /* Calcula o ponto medio do objeto */
    cx = (0.2f + 0.3f + 0.4f)/3.0f;
    cy = (0.2f + 0.2f + 0.4f)/3.0f;
    
    /* Carrega a matriz de modelo */
    glMatrixMode(GL_MODELVIEW);
    
    /* Move o objeto para a posicao inicial */
    glTranslatef(cx,cy,0.0f);
    
    /* Faz a escala */
    glScalef(sx, sy,0.0f);
    
    /* Move o objeto para a origem */
    glTranslatef(-cx,-cy,0.0f);
}

/* Funcao que faz a escala*/
void rotacao2D(GLfloat angulo){
  
    GLfloat cx,cy;
    
    /* Calcula o ponto medio do objeto */
    cx = (0.2f + 0.3f + 0.4f)/3.0f;
    cy = (0.2f + 0.2f + 0.4f)/3.0f;
    
    /* Carrega a matriz de modelo para executar transformacoes geometricas */
    glMatrixMode(GL_MODELVIEW);
    
    /* Armazena na pilha o estado atual da matriz de transformacoes MODELVIEW */
    glPushMatrix();
    
    /* Move o objeto para a posicao inicial */
    glTranslatef(cx,cy,0.0f);
    
    /* Faz a escala */
    glRotatef(angulo, 0.0f,0.0f,1.0f);
    
    /* Move o objeto para a origem */
    glTranslatef(-cx,-cy,0.0f);
    
    /* Recupera o estado da matriz de transformacoes geometricas antes da rotacao */
    /* glPopMatrix(); comentado de proposito */
    
}

void desenhaCena()
{
    /* Criar um triangulo rotacionado em 45 graus */
    //gluOrtho2D(-5.0f,-5.0f,5.0f,5.0f);
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT);
    /* cor rgb: verde */
    glColor3f(0.0f,0.4f,0.2f);
    
    glMatrixMode(GL_MODELVIEW);
    
    /* Cria um triangulo preenchido */
    drawRectangle();
    
    glPushMatrix();
    //glRectf (0.2f, 0.2f, 0.35f, 0.2f);
    //rotacao2D(45.0f);
    glColor3f (1.0f, 0.0f, 0.0f);
    drawTriangle();
    
    glPopMatrix();
    
    /* rotaciona o objeto na tela em 45 graus */
    //rotacao2D(45.0f);
    //glutSwapBuffers();
    /* Forca a atualizacao da imagem para notificar o hardware
     a iniciar a renderizacao */
    glFlush();
    
}

/* Metodo que trata eventos (teclas pressionadas especiais)
 * do teclado*/
void keyboard(unsigned char key, int x, int y)
{
    if(key == 'r')
    {
        cout <<"Apertou r\n";
    }
}

/* Metodo que trata eventos (teclas pressionadas especiais)
 * do teclado*/
void keyboard_special(int key, int x, int y)
{
    if(key == GLUT_KEY_RIGHT)
    {
        cout<<"Para direita\n";
    }
    else
    {
        if(key == GLUT_KEY_LEFT)
        {
            cout<<"Para esquerda\n";
        }
        else
        {
            if(key == GLUT_KEY_UP)
            {
                cout<<"Para cima\n";
            }
            else
            {
                if(key == GLUT_KEY_DOWN)
                {
                    cout<<"Para baixo\n";
                }
	    }
	}
    }
}

int main(int argc, char **argv)
{
    /* Iniciar a GLUT para que recursos computacionais sejam 
       disponibilizados para este programa */
    glutInit(&argc,argv);
    
    /* Iniciar o buffer de memoria para armazenar a imagem 
       GLUT_SINGLE */
    glutInitDisplayMode(GLUT_SINGLE);
    
    /* Tamanho da janela principal */
    glutInitWindowSize(500,500);
    
    /* Coordenadas de tela inicial da janela do OpenGL no canto esquerdo */
    glutInitWindowPosition(100,100);
    
    /* Apresenta a janela na tela*/
    glutCreateWindow("Transformacoes Geometricas 2D");
    
    /* Registra a funcao de tratamento de tecla pressionada do teclado 
    ajustando o callback do teclado (ASCII) para a janela atual */
    glutKeyboardFunc(&keyboard);
    
    /* Registra a funcao de tratamento de tecla pressionada do teclado 
     ajustando o callback de teclas especiais (F1,F2,..) para a janela atual.*/
    glutSpecialFunc(&keyboard_special);
    
    /* Funcao que inicia o processo de renderizacao */
    glutDisplayFunc(desenhaCena);
    
    /* Coloca esse programa OpenGL em loop infinito: deve ser o ultimo comando do codigo-fonte */
    glutMainLoop();
    
    /* retorna para o sistema sucesso um sinal de finalizacao 
     desse programa*/
    return 0;
}