/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Transformacoes Geometricas 2D 
 * 
 * Funcao desse programa: desenha um triangulo na tela 
 * 
 * Compilar: g++ viewing3D.cpp -lglut -lGLU -lGL -o view
 * Executar: ./view
 */

#include<GL/glut.h>
#include<iostream>

using namespace std;

GLfloat px = 2.0f;
GLfloat py = 4.0f;

void projecaoOrtogonal()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0f,4.0f,-4.0f,4.0f,-4.0f,4.0f);
}

void projecaoPerspectiva()
{
    //glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0f,1.0f,2.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(0.0f,1.0f,0.5f,10.0f);
    //glFrustum(-1.5f,-1.5f,-1.5f,-1.5f,0.5f,5.0f);
}

void desenhaCena()
{
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Limpa a cor do buffer para branco (1.0,1.0,1.0)*/
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    
    /* Configura o ambiente com projecao ortogonal 
    projecaoOrtogonal();*/
    
    /* Configura o ambiente com projecao perspectiva */
    projecaoPerspectiva();
    
    /* A cor dos desenhos eh agora, vermelho */
    glColor3f(1.0f,0.0f,0.0f);
    
    /* Desenha um cubo aramado */
    glPushMatrix();
    glutWireCube(1.5f);
    glPopMatrix();

    /* Forca o OpenGL a desenhar os objetos geometricos */
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
        px = px+0.01;
        cout<<"Para direita "<<px<<endl;
    }
    else
    {
        if(key == GLUT_KEY_LEFT)
        {
            px = px-0.01;
            cout<<"Para esquerda "<<px<<endl;
        }
        else
        {
            if(key == GLUT_KEY_UP)
            {
                py=py+0.05;
                cout<<"Para cima "<<py<<endl;;
            }
            else
            {
                if(key == GLUT_KEY_DOWN)
                {
                    py=py-0.05;
                    cout<<"Para baixo "<<py<<endl;;
                }
	    }
	}
    }
}


void idleFunc()
{     
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