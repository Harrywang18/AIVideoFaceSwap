#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){

    /* init GLFW window */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* create a window */ 
    GLFWwindow* window = glfwCreateWindow(800, 600, "My window", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // make the window context same as current thread context

    /* init glad which is used to manage the ptr of GLFW */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* define the vertices */
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    /* manage the vertices in GPU memory */
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    /* bind buffer */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // GL_ARRAY_BUFFER is VBO's type

    /* copy the data of vertices to buffer */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // STATIC means not changed

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    /* create a vertexShader */
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    /* compile the source code */
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    /* check if compile success */
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* create and compile the fragment shader */
    const char * fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    /* check if compile success */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    /* create a new shader program */
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    /* attach shader at the program */
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    /* link the program */
    glLinkProgram(shaderProgram);

    /* check if link success */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    return 0;





}
