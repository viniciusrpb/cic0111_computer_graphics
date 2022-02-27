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
 * Compilar: g++ shading3D.cpp -lglut -lGLU -lGL -o shade
 * Executar: ./shade
 */

#include<GL/glut.h>
#include<iostream>

using namespace std;

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
    gluLookAt(7.0f, 3.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f);
    
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
    
    GLfloat superficie[] = {0.25f, 0.25f, 0.25f, 1.0f};
    
    glMaterialfv(GL_FRONT, GL_EMISSION, superficie);
    
    glMatrixMode(GL_MODELVIEW);
    
    /* define a cor vermelha */
    glColor3f(0.0f,1.0f,0.0f);
    
    /* desenha um cubo na origem */
    glPushMatrix();
    glTranslatef(2.5f,0.0f,0.0f);
    glutSolidCube(1.5f);
    glPopMatrix();
    
    /* define a cor vermelha */
    glColor3f(0.0f,0.0f,1.0f);
    
    /* desenha uma esfera atras do cubo */
    glPushMatrix();
    
    glTranslatef(-1.5f,0.0f,0.0f);
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glRotatef(theta,0.0f,0.0f,1.0f);
    
    glutSolidSphere(1.0f,30,30);
    glPopMatrix();
    
    lighting();
    
    projecaoPerspectiva();
    glutSwapBuffers();
    glFlush();
}


/* Metodo que trata eventos (teclas pressionadas especiais)
 * do teclado*/
void keyboard(unsigned char key, int x, int y)
{
    /*if(key == 'l')
    {
        mode = 1;
        cout <<"Apertou r\n";
        projecaoOrtogonal();
    }
    if(key == 'o')
    {
        mode = 3;
        cout <<"Apertou r\n";
    }
    if(key == 'p')
    {
        mode = 2;
        cout <<"Apertou r\n";*/
    //}
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

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    
    projecaoPerspectiva();
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
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
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
    
        glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
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