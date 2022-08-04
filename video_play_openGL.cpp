#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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

    /* set the rendering window size */
    glViewport(0, 0, 800, 600);

    /* tell GLFW the resize function */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    while(!glfwWindowShouldClose(window)){
        processInput(window); // check if press the key ESC
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // set the color after clear
        glClear(GL_COLOR_BUFFER_BIT); // set the color in glClearColor


        glfwSwapBuffers(window); // swap the buffer that stored last image with the current drawing buffer
        glfwPollEvents();     // check if there's some triggered events
    }

    glfwTerminate();    // release the allocated resources
    return 0;

    

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    /* process if press the key ESC to close the window */
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

