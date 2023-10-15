#include "headers.h"


const GLint altura = 650 , largu = 650;

GLuint VAO,VBO,shader,uniformXmove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

//vertix shaders
// Vertex shader
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
layout (location = 0) in vec3 position;                                       \n\
uniform float xMove;                                                         \n\
void main()                                                                  \n\
{                                                                            \n\
    gl_Position = vec4(0.4 * position.x + xMove, 0.5 * position.y, position.z, 1.0); \n\
}";

// Fragment shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
out vec4 colour;                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(0.9 , 0.3 , 0.4 , 1.0);                                    \n\
}";


void triangulo(){
    GLfloat vertices []{
        -0.8f,-0.8f,0.0f,
        0.8f,-0.8f,0.0f,
        0.8f,0.8f,0.0f,
        -0.8f,0.8f,0.0f
       
    };

    //paramos aqui 

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

         glGenBuffers(1, &VBO);
             glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);
                glEnableVertexAttribArray(0);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void AddShader(GLuint TheProgram, const char* shaderCode, GLenum shaderType){
   
    GLuint TheShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(TheShader, 1, theCode, codeLength);
    glCompileShader(TheShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

   
    glGetShaderiv(TheShader, GL_COMPILE_STATUS, &result);
    if(!result){
        glGetShaderInfoLog(TheShader, sizeof(eLog), NULL, eLog);
       // fprintf(stderr, "Deu merda mano: '%s'\n",shaderType,eLog);
        return;
    }
    glAttachShader(TheProgram, TheShader);
}



void CompileShader(){
    shader = glCreateProgram();

    if(!shader){
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Deu merda mano  %s\n", eLog);
        return;
    }

    glValidateProgram(shader);

    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Deu merda mano validação  %s\n", eLog);
        return;
    }
}

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


    if (glewInit() != GLEW_OK){
        std::cout<<"Falha ao inicializar GLEW";
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, bufferWi, bufferHei);

    triangulo();
    CompileShader();


    while(!glfwWindowShouldClose(janela)){
        glfwPollEvents();

        if(direction){
            triOffset += triIncrement;
        }else{
            triOffset -= triIncrement;
        }if(abs(triOffset) >= triMaxOffset){
            direction =!direction;
        }


        glClearColor(0.9f, 0.9f, 0.9f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT);
       
        glUseProgram(shader);

        glUniform1f(uniformXmove, triOffset);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 , 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    return 0;
}