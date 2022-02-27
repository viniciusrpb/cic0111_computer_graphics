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

GLfloat theta = 0.0f;

void drawPyramid()
{
    glBegin(GL_POLYGON);
	// Face frontal da piramide
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);	// vertice superior
	glVertex3f(-1.0f,-1.0f, 1.0f);	// vertice esquerdo
	glVertex3f(1.0f,-1.0f, 1.0f);	// vertice direito

	// Face da direita da piramide
	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f( 0.0f, 1.0f, 0.0f); // vertice superior
	glVertex3f( 1.0f,-1.0f, 1.0f);   // vertice esquerdo
	glVertex3f( 1.0f,-1.0f, -1.0f);  // vertice direito

	// back face of pyramid
	glColor3f(0.0f,0.0f,0.0f); 
	glVertex3f( 0.0f, 1.0f, 0.0f);   // vertice superior
	glVertex3f( 1.0f,-1.0f, -1.0f);    // vertice esquerdo
	glVertex3f(-1.0f,-1.0f, -1.0f);    // vertice da direita

	// left face of pyramid.
	glColor3f(1.0f,0.0f,0.0f); 
	glVertex3f( 0.0f, 1.0f, 0.0f);   // vertice superior
	glVertex3f(-1.0f,-1.0f,-1.0f);    // vertice da esquerda
	glVertex3f(-1.0f,-1.0f, 1.0f);    // vertice da direita
	
	// Fazer a base da piramide!!!
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


void ajustaCamera(GLfloat x, GLfloat y, GLfloat z)
{
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    /* glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal); */

    //glOrtho(-0.5f, 0.5f, -0.5f, 0.5f, -0.25f, 0.25f);
    
    /* 
      glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble nearVal, GLdouble farVal);
     */
     glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 5.0f);
    
    //
    
    /*
     * gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
     * fovy: rotacao da camera
     * aspect : razão entre altura e largura da janela de recorte
     * zNear: proximidade da camera com a janela de recorte
     * zFar: proximidade da camera com o fundo de visao
     * 
     */
     //gluPerspective(0.5f, 1.0f, 0.25f, 2.0f);

    
    //gluLookAt(0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);
    
}

void desenhaCena()
{
    /* Criar um triangulo rotacionado em 45 graus */
    //gluOrtho2D(-5.0f,-5.0f,5.0f,5.0f);
    /* Limpa o buffer e coloca a cor padrao de fundo */
    glClear(GL_COLOR_BUFFER_BIT);
    /* cor rgb: verde */
    glColor3f(0.0f,0.4f,0.2f);
    
    //gluLookAt(0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 0.0, 1.0, 0.0);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    /* Cria um triangulo preenchido */
    //drawRectangle();
    /*
    glPushMatrix();
    //glRectf (0.2f, 0.2f, 0.35f, 0.2f);
    //rotacao2D(45.0f);
    glColor3f (1.0f, 0.0f, 0.0f);
    drawTriangle();
    
    glPopMatrix();*/
    
    //rotaciona e escala uma esfera 'aramado'
    //glRotatef(30.0f, 0, 1, 0);
    //glRotatef(45.0f, 1, 0, 0);
    //glScalef(delta, delta, delta);
    glColor3f(0.5, 1, 0);
    //glRotatef(60.0f,1.0f,0.0f,0.0f);

    rotacao2D(theta);
    
    //glutWireSphere(0.5f, 30, 30);
    drawPyramid();
    //glutSolidCube(0.8f);
    //desenha um 'piso' sob a esfera
    //glTranslatef(0, -1, 0);
    //glScalef(4, 0.1f, 4);
    //glColor3f(0, 0, 1);
    //glutSolidCube(1.0f);
    //forca o desenho das primitivas
    //glFlush();

    
    /* rotaciona o objeto na tela em 45 graus */
    //rotacao2D(45.0f);
    //glutSwapBuffers();
    /* Forca a atualizacao da imagem para notificar o hardware
     a iniciar a renderizacao */
    
    ajustaCamera(1.0f,1.0f,1.0f);
    
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

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    //gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    //glMatrixMode(GL_MODELVIEW);
    //glViewport(0,0,x,y);  //Use the whole window for rendering
}

void idleFunc()
{
    
     theta += 0.001f;
     
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