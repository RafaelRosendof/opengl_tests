//g++ Source.cpp -o my.elf -std=c++11 -Wall -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

#include <GL/glut.h>  // Inclui a biblioteca OpenGL
#include <iostream>
#include <cmath>

// Função de desenho
void drawTriangle() {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa o buffer de cor

    glBegin(GL_TRIANGLES);  
    glColor3f(1.0f, 0.8f, 0.5f);  // Define a cor vermelha

    glVertex2f(0.5f, 0.5f);  // first

    glVertex2f(-0.5f, -0.5f);  // second vert

    glVertex2f(0.5f, -0.5f);  //third

    glEnd();   

    glFlush();  
}

const int sides = 100;  // Número de lados do círculo
const GLfloat radius = 0.5f;  // Raio do círculo
const GLfloat pi = 3.14159265358979323846;
void circulo(){

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.7f , 0.9f , 0.5f);

    //raio dos circulos

    for(int i{0};i<sides;i++){
        GLfloat figas = 2.0f * pi * GLfloat(i) / GLfloat(sides);
        GLfloat x = radius * cos(figas);
        GLfloat y = radius * sin(figas);

        glVertex2f(x,y);
    }

    glEnd();
    glFlush();
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);  
    int a;
    std::cout<<"Para qual gráfico queres gerar uma imagem: 1 para triangulo 2 para circulo: ";
    std::cin>>a;
    glutCreateWindow("Triangle OpenGL ");

        glutDisplayFunc(circulo);
  
    
    glutMainLoop();
    
    return 0;
}
