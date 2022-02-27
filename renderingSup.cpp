/* Universidade de Brasília
 * Departamento de Ciência da Computação
 * 116483 - Computação Gráfica 
 * Prof. Dr. Vinicius R. P. Borges
 * 
 * Aula: Metodos de rendering de superficie
 * 
 * Funcao desse programa: implementacao dos metodos de rendering de superficie
 * 
 * Compilar: g++ renderingSup.cpp -lglut -lGLU -lGL -o rendering
 * Executar: ./rendering
 */

#define SIZE_GAUSSIAN 40
#include<GL/glut.h>
#include <math.h>

struct vertice
{
    GLfloat x; 
    GLfloat y;
    GLfloat z;
};

typedef struct vertice Ponto3D;

struct celula
{
    Ponto3D ponto;
    Ponto3D normal;
};

typedef struct celula Cell;

// Identificador da janela
int window;

// Estrutura que armazena a Gaussiana
Cell gaussian[SIZE_GAUSSIAN+2][SIZE_GAUSSIAN+2];

void projecaoOrtogonal()
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
    gluLookAt(1.5, 0.75, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    /* define a matriz atual como a de projecao */
    glMatrixMode(GL_PROJECTION); 
    
    /* carrega a matriz identidade para a matriz atual */
    glLoadIdentity();
    
    /* define uma projecao paralela */
    glOrtho(-2.5, 2.5, -2.5, 2.5, -4.5, 4.5);
}

void lighting()
{
    GLfloat position[] = {1.0f,1.5f,-0.5f,1.0f};
    GLfloat white[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat black[] = {0.0f,0.0f,0.0f,1.0f};
    
    /* Define a luz puntual da cena: Luz 0 */
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);
    
    /* Ativa as rotinas de iluminacao */
    glEnable(GL_LIGHTING);
    
    /* Ativa a luz 0 */
    glEnable(GL_LIGHT0);
}


// Calcula o produto vetorial
Ponto3D crossproduct(Ponto3D a, Ponto3D b){
  
        Ponto3D prod;
 
	prod.x = a.y*b.z - a.z*b.y;
        prod.y = a.z*b.x - a.x*b.z;
        prod.z = a.x*b.y - a.y*b.x;
        
	return prod;     
}

// Normaliza o vetor normal
Ponto3D normalize(Ponto3D p){
  
        Ponto3D novo;
	
	// Produto escalar
        GLfloat norm = (float) sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	
        novo.x = p.x/norm;
        novo.y = p.y/norm;
        novo.z = p.z/norm;
	
        return novo;     
}

// Calcula vetor normal
void calculaNormal()
{
     // Contadores
     int i;
     int j;
     
     // Pontos auxiliares
     Ponto3D v1;
     Ponto3D v2;
     Ponto3D v3;
     Ponto3D vec1;
     Ponto3D vec2;
     
     // Calcula a normal de cada face da superfície da Gaussiana
     for(i = 1; i < SIZE_GAUSSIAN-1;i++){
           for( j = 1; j < SIZE_GAUSSIAN-1;j++){
                
                v1 = gaussian[i][j].ponto;
                v2 = gaussian[i][j+1].ponto;
                v3 = gaussian[i+1][j].ponto;
                
		// Subtracao entre tres pontos (v2-v1)x(v1-v3) antes de calcular a normal
                vec1.x = v2.x - v1.x;
                vec1.y = v2.y - v1.y;
                vec1.z = v2.z - v1.z;
                
                vec2.x = v1.x - v3.x;
                vec2.y = v1.y - v3.y;
                vec2.z = v1.z - v3.z;
                
		// Calcula o vetor normal da face e normaliza
                gaussian[i][j].normal = normalize(crossproduct(vec1,vec2));
		
          }
     }
}

// Funcao que desenha a Gaussiana
void criaGaussiana()
{

    // Contadores
    int i;
    int j;
    
    // Variaveis auxiliares
    GLfloat x;
    GLfloat z;
    GLfloat y;
    GLfloat xexp;
    GLfloat zexp;
    
    // Formula da Gaussiana
    for(i = 0; i < SIZE_GAUSSIAN+2;i++){
	for(j = 0; j < SIZE_GAUSSIAN+2;j++){
	    x =  (4.0f * j) / ((float) SIZE_GAUSSIAN + 2) - 2.0f;
	    z =  (4.0f * i) / ((float) SIZE_GAUSSIAN + 2) - 2.0f;
	    
	    xexp = exp(-x * x);
	    zexp = exp(-z * z);
            y = (float) xexp*zexp;
            
	    gaussian[i][j].ponto.x = x;
	    gaussian[i][j].ponto.y = y;
	    gaussian[i][j].ponto.z = z;
	}
    }

}

// Desenha a superficie utilizando renderização flat
void drawSurface_flat()
{
    int i;
    int j;
  
    glPushMatrix();
    
    	// Cria matriz com as células para desenho
	criaGaussiana();
	
	// Calcula a normal de cada face da gaussiana
	calculaNormal();
	
	// Declaracao de variaveis para desenho da superficie
	GLfloat diffuse[] = {0.5f,0.5f,0.8f,1.0f};
	GLfloat specular[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat shininess = 100.0f;
	
	// Definicao das luzes difusa, especular e coeficiente do material da superficie gaussiana
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	
	// Desenha a superfície
	for (i = 1; i < SIZE_GAUSSIAN - 1; i++) {
	    for (j = 1; j < SIZE_GAUSSIAN - 1; j++) {
	      
	      // Define a normal calculada em cada face da Gaussiana
	      glNormal3f(gaussian[i][j].normal.x,gaussian[i][j].normal.y,gaussian[i][j].normal.z);
	      
		// Desenha cada face
		glBegin(GL_TRIANGLE_STRIP);
		    glVertex3f(gaussian[i+1][j].ponto.x, gaussian[i+1][j].ponto.y, gaussian[i+1][j].ponto.z);
		    glVertex3f(gaussian[i+1][j+1].ponto.x, gaussian[i+1][j+1].ponto.y, gaussian[i+1][j+1].ponto.z);
		    glVertex3f(gaussian[i][j].ponto.x, gaussian[i][j].ponto.y, gaussian[i][j].ponto.z);
		    glVertex3f(gaussian[i][j+1].ponto.x, gaussian[i][j+1].ponto.y, gaussian[i][j+1].ponto.z);
		glEnd();
		
    	    }
	}
	
    glPopMatrix();
}

// Desenha a superficie utilizando renderização flat
void drawSurface_Gouraud()
{
    int i;
    int j;
  
    glPushMatrix();
    
    	// Cria matriz com as células para desenho
	criaGaussiana();
	
	// Calcula a normal de cada face da gaussiana
	calculaNormal();
	
	// Declaracao de variaveis para desenho da superficie
	GLfloat diffuse[] = {0.5f,0.5f,0.8f,1.0f};
	GLfloat specular[] = {1.0f,1.0f,1.0f,1.0f};
	GLfloat shininess = 100.0f;
	
	// Definicao das luzes difusa, especular e coeficiente do material da superficie gaussiana
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glMaterialf(GL_FRONT,GL_SHININESS,shininess);
	
	// Desenha a superfície
	for (i = 1; i < SIZE_GAUSSIAN - 1; i++) {
	    for (j = 1; j < SIZE_GAUSSIAN - 1; j++) {
	     
		  glBegin(GL_TRIANGLE_STRIP);
		  
		      glNormal3f(gaussian[i+1][j].normal.x,gaussian[i+1][j].normal.y,gaussian[i+1][j].normal.z);
		      glVertex3f(gaussian[i+1][j].ponto.x, gaussian[i+1][j].ponto.y, gaussian[i+1][j].ponto.z);
		      
		      glNormal3f(gaussian[i+1][j+1].normal.x,gaussian[i+1][j+1].normal.y,gaussian[i+1][j+1].normal.z);
		      glVertex3f(gaussian[i+1][j+1].ponto.x, gaussian[i+1][j+1].ponto.y, gaussian[i+1][j+1].ponto.z);
		      
		      glNormal3f(gaussian[i][j].normal.x,gaussian[i][j].normal.y,gaussian[i][j].normal.z);
		      glVertex3f(gaussian[i][j].ponto.x, gaussian[i][j].ponto.y, gaussian[i][j].ponto.z);
		      
		      glNormal3f(gaussian[i][j+1].normal.x,gaussian[i][j+1].normal.y,gaussian[i][j+1].normal.z);
		      glVertex3f(gaussian[i][j+1].ponto.x, gaussian[i][j+1].ponto.y, gaussian[i][j+1].ponto.z);

		glEnd();
		
    	    }
	}
	
    glPopMatrix();
}

// Funcao que desenha a cena grafica na tela
void desenhaCena() {
  
    // Limpa a tela e o Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glEnable(GL_DEPTH_TEST);
    
    // Desenha os objetos na cena utilizando o modelo de Flat
    //drawSurface_flat();
    
    // Desenha a superfície Gaussiana utilizando o modelo de Gouraud
    drawSurface_Gouraud();
    
    /* ativa os recursos de iluminacao da cena */
    lighting();
    
    /* cria uma projecao ortogonal */
    projecaoOrtogonal();

    /* Alterna entre os buffers para cada chamada do desenho */
    glutSwapBuffers();
    
    /* Processa as rotinas do OpenGL o mais rapido possi­vel */
    glFlush();
}

int main(int argc, char **argv)
{
    /* Iniciar a GLUT para que recursos computacionais sejam 
       disponibilizados para este programa */
    glutInit(&argc,argv);
    
    /* Iniciar o buffer de memoria para armazenar a imagem 
       GLUT_SINGLE */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    /* Tamanho da janela principal */
    glutInitWindowSize(500,500);
    
    /* Coordenadas de tela inicial da janela do OpenGL no canto esquerdo */
    glutInitWindowPosition(100,100);
    
    /* Apresenta a janela na tela*/
    glutCreateWindow("Rendering de superficie");
    
    /* Funcao que inicia o processo de renderizacao */
    glutDisplayFunc(desenhaCena);
    
    /* Coloca esse programa OpenGL em loop infinito: deve ser o ultimo comando do codigo-fonte */
    glutMainLoop();
    
    /* retorna para o sistema sucesso um sinal de finalizacao 
     desse programa*/
    return 0;
}
