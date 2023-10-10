#include "headers.h"


GLuint createTriangleVAO() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Vértice 1
         0.5f, -0.5f, 0.0f, // Vértice 2
         0.0f,  0.5f, 0.0f  // Vértice 3
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindVertexArray(0);

    return vao;
}

int main() {
    // Inicialize o GLFW
    if (!glfwInit()) {
        std::cerr << "Erro ao inicializar o GLFW" << std::endl;
        return -1;
    }

    // Crie uma janela GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Exemplo GLFW", NULL, NULL);
    if (!window) {
        std::cerr << "Erro ao criar uma janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    
    glfwMakeContextCurrent(window);

   
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erro ao inicializar o GLEW" << std::endl;
        return -1;
    }

  
    std::cout << "Versão do OpenGL: " << glGetString(GL_VERSION) << std::endl;

   
    GLuint vao = createTriangleVAO();

    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

       
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Encerre o GLFW
    glfwTerminate();

    return 0;
}