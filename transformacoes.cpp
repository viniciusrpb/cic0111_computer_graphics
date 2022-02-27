#include<GL/glut.h>
#include<iostream>

int modo;

void translacao2D(GLfloat tx, GLfloat ty)
{
    /* Habilita a matriz de transformacoes geometricas */
    glMatrixMode(GL_MODELVIEW);
    
    /* Reseta a matrix de modelo para transformacoes
     geometricas, colocando-a como Identidade */
    glLoadIdentity();
    
    glPushMatrix();
    
    glTranslatef(tx,ty,0.0f);
    
    glPushMatrix();
    
    glPopMatrix();
}

void rotacao2D(GLfloat angulo)
{    
    
    GLfloat cx,cy;
    
    cx = (0.5f + 0.5f + 0.7f + 0.7f)/4.0;
    cy = (0.5f + 0.7f + 0.7f + 0.5f)/4.0;
    
    glPushMatrix();
    
    glTranslatef(cx,cy,0.0f);
    
    glRotatef(angulo,0.0f,0.0f,1.0f);
    
    glTranslatef(-cx,-cy,0.0f);
    
    glPushMatrix();
    
    glPopMatrix();
    
}

void drawRectangle()
{
    glColor3f(0.5f,0.5f,0.5f);
    
    glBegin(GL_QUADS);
        glVertex2f(0.5f,0.5f);
        glVertex2f(0.5f,0.7f);
        glVertex2f(0.7f,0.7f);
        glVertex2f(0.7f,0.5f);
    glEnd();
}

void drawTriangle()
{
    /* Criar um triangulo */
    
    /* cor rgb: branca */
    glColor3f(0.8f,0.4f,0.3f);
    
    glBegin(GL_TRIANGLE_FAN);
        
        glVertex2f(0.2f,0.2f);
        glVertex2f(0.4f,0.2f);
        glVertex2f(0.3f,0.4f);
        
    glEnd();
}

void criaCena()
{
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*drawTriangle();*/
    
    drawRectangle();
    
    /*translacao2D(-0.3f,0.0f);*/
    
    rotacao2D(45.0);
    
    /* Atualizar a imagem da tela */
    glFlush();
}

void keyboard(unsigned int key)
{
    if(key == 'r')
    {
        modo=1;
    }
}

void keyboard_special(int key, int x, int y)
{
    if(GLUT_KEY_UP == key)
    {
        std::cout << "Para cima!\n";
        translacao2D(0.1f,0.0f);
    }
    if(GLUT_KEY_DOWN == key)
    {
        std::cout << "Para baixo!\n";
    }
    if(GLUT_KEY_RIGHT == key)
    {
        std::cout << "Para direita!\n";
    }
    if(GLUT_KEY_LEFT == key)
    {
        std::cout << "Para esquerda!\n";
    }
    /* redesenha a tela */
    glutDisplayFunc(criaCena);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    /* Iniciar a GLUT para que recursos computacionais sejam 
       disponibilizados para este programa */
    glutInit(&argc,argv);
    
    /* Iniciar o buffer de memoria para armazenar a imagem 
       GLUT_DOUBLE */
    glutInitDisplayMode(GLUT_SINGLE);
    
    /* Tamanho da janela principal */
    glutInitWindowSize(600,600);
    
    /* Coordenadas de tela inicial da janela do OpenGL*/
    glutInitWindowPosition(100,100);
    
    /* Apresenta a janela na tela*/
    glutCreateWindow("Transformacoes Geometricas 2D");
    
    /* Funcao que inicia o processo de renderizacao */
    glutDisplayFunc(criaCena);
    
    /* Habilitar o teclado usando recursos da GLUT
       chama o metodo keyboard_special */
    glutSpecialFunc(&keyboard_special);
    
    /* Coloca esse programa OpenGL em loop infinito */
    glutMainLoop();
    
    /* retorna para o sistema sucesso um sinal de finalizacao 
     desse programa*/
    return 0;
}