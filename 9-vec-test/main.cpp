#include <glad/glad.h>
#include <abstract/loader.h>
#include <GLFW/glfw3.h>

#include <iostream>


void processInput(GLFWwindow* window, int& mode)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        (mode == 1 ? mode = 0 : mode = 1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

const char* vertexShader = R"shader(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)shader";

//Global Uniform Shader
//Use this rather than individually colored shaders
const char* uniformFragmentShader = R"shader(
    #version 330 core
    out vec4 FragColor;

    uniform vec4 Color;

    void main()
    {
       FragColor = Color;
    }
)shader";


int success;
char infoLog[512];

int main()
{

    glfwSetErrorCallback(&glfwError);

    glfwInit();
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* glfwWindowHint(GLFW_DECORATED, GL_FALSE); */

    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    float topVertices[] {
        1.0f, 1.0f,  //Top Right
        1.0f, 0.90f, //Bottom Right
       -1.0f, 0.90f, //Bottom Left
       -1.0f, 1.0f  //Top Left
    };

    float vertices[] {
        1.0f,  1.0f,
        1.0f, -1.0f,
       -1.0f, -1.0f,
       -1.0f,  1.0f
    };
    
    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };


    /* //Vertex Shader */
    /* unsigned int vShader; */
    /* vShader = glCreateShader(GL_VERTEX_SHADER); */
    /* glShaderSource(vShader, 1, &vertexShader, NULL); */
    /* glCompileShader(vShader); */

    /* //Test for vertex shader compilation failure */
    /* glGetShaderiv(vShader, GL_COMPILE_STATUS, &success); */
    /* if (!success) */
    /* { */
    /*     glGetShaderInfoLog(vShader, 512, NULL, infoLog); */
    /*     std::cout << "ERROR::SHADER::VERTEX::COMPLIATION::FAILED\n" << infoLog << std::endl; */
    /* } */

    /* //Uniform Fragment Shasder */
    /* unsigned int uniformfShader; */
    /* uniformfShader = glCreateShader(GL_FRAGMENT_SHADER); */
    /* glShaderSource(uniformfShader, 1, &uniformFragmentShader, NULL); */
    /* glCompileShader(uniformfShader); */

    /* //Uniform Shader Program */
    /* unsigned int uniformShaderProgram; */
    /* uniformShaderProgram = glCreateProgram(); */
    /* glAttachShader(uniformShaderProgram, vShader); */
    /* glAttachShader(uniformShaderProgram, uniformfShader); */
    /* glLinkProgram(uniformShaderProgram); */

    /* //Delete old shaders */
    /* glDeleteShader(vShader); */
    /* glDeleteShader(uniformfShader); */

    //Title Bar
    //Vertex Attributes
    //Element Buffer Object
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(topVertices), topVertices, GL_STATIC_DRAW);   

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Middle Rectangle
    //Vertex Attributes
    //Element Buffer Object
    unsigned int mVAO, mVBO, mEBO;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mEBO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);   

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int currentColor = 0;

    Shader shaderTest("../shaders/generic.vs", "../shaders/uniform.fs");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, currentColor);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << currentColor << std::endl;

        /* if (currentColor == 0) */
        /*     glUseProgram(backgroundShaderProgram); */
        /* if (currentColor == 1) */
        /*     glUseProgram(titleShaderProgram); */

        //Title Coloring   
        //FragColor = vec4(0.12f, 0.12f, 0.20f, 1.0f);

        //Background Coloring
        //FragColor = vec4(0.105f, 0.125f, 0.141f, 1.0f);


        /* glUseProgram(uniformShaderProgram); */

        shaderTest.use();
        glBindVertexArray(mVAO);
        shaderTest.setFloat("Color", 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* int vertexColorLocation = glGetUniformLocation(uniformShaderProgram, "Color"); */
        /* std::cout << vertexColorLocation << std::endl; */

        /* //Background Coloring */
        /* glUniform4f(vertexColorLocation, 0.141f, 0.164f, 0.188f, 1.0f); */
        /* glBindVertexArray(mVAO); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        /* //Title Bar Coloring */
        /* glUniform4f(vertexColorLocation, 0.165f, 0.180f, 0.255f, 1.0f); */
        /* glBindVertexArray(VAO); */
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
