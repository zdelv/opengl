#include <glad/glad.h>
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
    layout (location = 0) in vec3 aPos;
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)shader";

const char* greenFragmentShader = R"shader(
    #version 330 core
    out vec4 FragColor;
    
    void main()
    {
       FragColor = vec4(0.0f, 1.0f, 0.5f, 1.0f);
    }
)shader";

const char* blueFragmentShader = R"shader(
    #version 330 core
    out vec4 FragColor;
    
    void main()
    {
       FragColor = vec4(0.0f, 0.2f, 1.0f, 1.0f);
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

    glfwWindowHint(GLFW_DECORATED, GL_FALSE);

    
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
        1.0f, 1.0f, 0.0f, //Top Right
        1.0f, 0.90f, 0.0f, //Bottom Right
       -1.0f, 0.90f, 0.0f, //Bottom Left
       -1.0f, 1.0f, 0.0f  //Top Left
    };

    float vertices[] {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };
    
    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };


    //Vertex Shader
    unsigned int vShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexShader, NULL);
    glCompileShader(vShader);

    //Test for vertex shader compilation failure
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPLIATION::FAILED\n" << infoLog << std::endl;
    }

    //Green Fragment Shader
    unsigned int greenfShader;
    greenfShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(greenfShader, 1, &greenFragmentShader, NULL);
    glCompileShader(greenfShader);

    //Test for fragment shader compilation failure
    glGetShaderiv(greenfShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(greenfShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    //Blue Fragment Shader
    unsigned int bluefShader;
    bluefShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(bluefShader, 1, &blueFragmentShader, NULL);
    glCompileShader(bluefShader);

    //Test for fragment shader compilation failure
    glGetShaderiv(bluefShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(bluefShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION::FAILED\n" << infoLog << std::endl;
    }


    //Green Shader Program
    unsigned int greenShaderProgram;
    greenShaderProgram = glCreateProgram();
    glAttachShader(greenShaderProgram, vShader);
    glAttachShader(greenShaderProgram, greenfShader);
    glLinkProgram(greenShaderProgram);

    //Test for shader program compilation failure
    glGetProgramiv(greenShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(greenShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILURE" << infoLog << std::endl;
    }

    //Blue Shader Program
    unsigned int blueShaderProgram;
    blueShaderProgram = glCreateProgram();
    glAttachShader(blueShaderProgram, vShader);
    glAttachShader(blueShaderProgram, bluefShader);
    glLinkProgram(blueShaderProgram);

    //Test for shader program compilation failure
    glGetProgramiv(blueShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(blueShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILURE" << infoLog << std::endl;
    }

    //Delete old shaders
    glDeleteShader(vShader);
    glDeleteShader(greenfShader);
    glDeleteShader(bluefShader);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int currentColor = 0;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, currentColor);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << currentColor << std::endl;

        if (currentColor == 0)
            glUseProgram(greenShaderProgram);
        if (currentColor == 1)
            glUseProgram(blueShaderProgram);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}
