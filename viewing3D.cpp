/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Viewing 3D
 * 
 * Funcao desse programa: trabalhar com os diferentes tipos de projecoes
 *                    e posicionamento de cameras
 * 
 * Compilar: g++ viewing3D.cpp -lglut -lGLU -lGL -o view
 * Executar: ./view
 */

#include<GL/glut.h>
#include<iostream>

using namespace std;

GLfloat theta = 0.0f;
GLfloat p = 2.0f;
GLfloat angle = 0.0f;
int mode=2;

/* Define uma projecao ortogonal/paralela para a cena */
void projecaoOrtogonal()
{
    /* habilita o teste de profundidade */
    glEnable(GL_DEPTH_TEST);
    
    /* a matriz atual eh a de projecao*/
    glMatrixMode(GL_PROJECTION);  
    
    /* inicializa a matriz de projecao */
    glLoadIdentity();
    
    /* define as caracteristicas da projecao ortogonal
     1 xwmin
     2 xwmax
     3 ywmin
     4 ywmax
     5 dnear
     6 dfar
     */
    glOrtho(-5.0f,5.0f,-5.0f,5.0f,0.5f,10.0f);
    
}

void transfVisao()
{
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    
    glOrtho(-6.0f,6.0f,-6.0f,6.0f,-6.0f,6.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(p, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f);

}

/* Projecao perspectiva simetrica 
 utilizando gluPerspective */
void projecaoPerspectiva()
{
    /* define a cor de fundo */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /* habilita o teste de profundidade */
    //glEnable(GL_DEPTH_TEST);
    
    /* define a matriz de transformacoes como a atual */
    glMatrixMode(GL_MODELVIEW);
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define a posicao da camera, para onde ela aponta, e a orientacao da camera */
    gluLookAt(7.0f, 3.0f, 3.0f, 2.0f, -2.0f, 2.0f, 0.0f, 1.0f,0.0f);
    
    /* define a matriz atual como a de projecao */
    glMatrixMode(GL_PROJECTION); 
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define uma projecao perspectiva */
    gluPerspective(45.0f,1.0f,1.0f,30.0f);


}

/* Projecao perspectiva generica utilizando gluFrustum */
void projecaoPerspectivaObliqua()
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
    //gluLookAt(5.0f, 3.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f);
    gluLookAt(7.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f);
    
    /* define a matriz atual como a de projecao*/
    glMatrixMode(GL_PROJECTION);
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define uma projecao perspectiva obliqua
     * glFrustum(GLdouble xwmin, GLdouble xwmax,
     *           GLdouble ywmin, GLdouble ywmax,
                 GLdouble dnear, GLdouble dfar);
                 
                 (xwmin,ywmin) e (xwmax,ywmax) definem as coordenadas da janela de recorte
                 dnear e dfar definem as distancias da origem do sistema de coordenadas dos planos near/far ao longo do eixo zview

    */
    glFrustum(-2.0f,2.0f,-2.0f,2.0f,4.0f,18.0f);
}


void desenhaCena()
{

    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* define a cor vermelha */
    glColor3f(1.0f,0.0f,0.0f);
    
    glMatrixMode(GL_MODELVIEW);
    
    /* desenha um cubo na origem */
    glPushMatrix();
    glTranslatef(2.5f,0.0f,0.0f);
    glutWireCube(1.5f);
    glPopMatrix();
    
    /* desenha uma esfera atras do cubo */
    glPushMatrix();
    
    glTranslatef(-1.5f,0.0f,0.0f);
    //glRotatef(90.0f,1.0f,0.0f,0.0f);
    glRotatef(theta,0.0f,0.0f,1.0f);
    
    glutWireSphere(1.0f,30,30);
    glPopMatrix();
    
    glFlush();
}


/* Metodo que trata eventos (teclas pressionadas especiais)
 * do teclado*/
void keyboard(unsigned char key, int x, int y)
{
    if(key == 'l')
    {
        mode = 1;
        cout <<"Apertou paralela/ortogonal\n";
        projecaoOrtogonal();
    }
    if(key == 'o')
    {
        mode = 3;
        cout <<"Apertou obliqua\n";
        projecaoPerspectivaObliqua();
    }
    if(key == 'p')
    {
        mode = 2;
        cout <<"Apertou perspectiva\n";
        projecaoPerspectiva();
    }
}

/* Metodo que trata eventos (teclas pressionadas especiais)
 * do teclado*/
void keyboard_special(int key, int x, int y)
{
    if(key == GLUT_KEY_RIGHT)
    {
        p=p+0.1;
        cout<<"Para direita "<<p<<endl;
    }
    else
    {
        if(key == GLUT_KEY_LEFT)
        {
            p = p-0.1;
            cout<<"Para esquerda "<<p<<endl;
        }
        else
        {
            if(key == GLUT_KEY_UP)
            {
                angle=angle+0.05f;
                cout<<"Para cima "<<theta<<endl;
                projecaoPerspectivaObliqua();
                
            }
            else
            {
                if(key == GLUT_KEY_DOWN)
                {
                    angle=angle-0.05f;
                    cout<<"Para baixo "<<theta<<endl;
                }
	    }
	}
    }
}

void idleFunc()
{
    
     theta += 0.01f;
     
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
    glutInitDisplayMode(GLUT_SINGLE);
    
    /* Tamanho da janela principal */
    glutInitWindowSize(500,500);
    
    /* Coordenadas de tela inicial da janela do OpenGL no canto esquerdo */
    glutInitWindowPosition(100,100);
    
    /* Apresenta a janela na tela*/
    glutCreateWindow("Viewing 3D");
    
    /* Registra a funcao de tratamento de tecla pressionada do teclado 
    ajustando o callback do teclado (ASCII) para a janela atual */
    glutKeyboardFunc(&keyboard);
    
    /* Registra a funcao de tratamento de tecla pressionada do teclado 
     ajustando o callback de teclas especiais (F1,F2,..) para a janela atual.*/
    glutSpecialFunc(&keyboard_special);
    
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