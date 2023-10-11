#include "headers.h"

const GLint altura = 650 , largu = 650;

int main(){

    if (!glfwInit()){
        std::cout<<"GLFW falhou";
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GL_TRUE);

    GLFWwindow *janela = glfwCreateWindow(altura, largu , "Testando figas",NULL,NULL);
    if (!janela){
        std::cout<<"Falha ao criar a janela";
        glfwTerminate();
        return 1;
    }
    int bufferWi , bufferHei;
    glfwGetFramebufferSize(janela, &bufferWi, &bufferHei);

    glfwMakeContextCurrent(janela);
    glewExperimental = GL_TRUE;

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK){
        std::cout<<"Falha ao inicializar GLEW";
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWi, bufferHei);

    while(!glfwWindowShouldClose(janela)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3f, 0.8f, 0.8f, 0.2f);
        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    return 0;
}