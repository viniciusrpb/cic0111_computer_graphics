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
 * Compilar: g++ surface3D.cpp -lglut -lGLU -lGL -o surface
 * Executar: ./surface
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
    //define a posição e parâmetros da luz 0
    float position[] = {7.0f, 3.0f, 3.0f, 1.0f};
    float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    glLightfv(GL_LIGHT0,GL_POSITION, position);
    glLightfv(GL_LIGHT0,GL_AMBIENT, black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0,GL_SPECULAR, white);
    
    //ativa a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    //ativa transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
}

void desenhaCena()
{
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);

    /* desenha um cubo na origem */
    glPushMatrix();
        float diffuse2[] = {0.9f, 0.25f, 0.65f, 0.5f};
        float specular2[] = {0.9f, 0.9f, 0.9f, 0.5f};
        float shininess2 = 23.0f;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
        glTranslatef(-3.0f,-1.5f,0.0f);
        glScalef(4.0f,0.1f,4.0f);
        glutSolidCube(1.5f);
    glPopMatrix();
    
    GLfloat superficie[] = {0.25f, 0.25f, 0.25f, 1.0f};
    
    glMaterialfv(GL_FRONT, GL_EMISSION, superficie);

    float diffuse1[] = {0.0f, 0.65f, 0.0f, 0.25f};
    float specular1[] = {0.9f, 0.9f, 0.9f, 0.25f};
    float shininess1 = 65.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess1);
    
    
    /* desenha uma esfera atras do cubo */
    glPushMatrix();
    glTranslatef(-1.5f,0.0f,0.0f);
    glRotatef(90.0f,1.0f,0.0f,0.0f);
    glRotatef(theta,0.0f,0.0f,1.0f);
    
    glutSolidSphere(1.0f,30,30);
    glPopMatrix();
    
    ambient_light();
    
    projecaoPerspectiva();
    
    lighting();
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