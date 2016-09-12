#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLchar *vertexShaderSource = "#version 410 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "layout (location = 1) in vec3 color;\n"
                                   "out vec3 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "ourColor = color;\n"
                                   "}\0";
const GLchar *fragmentShaderSource = "#version 410 core\n"
                                     "in vec3 ourColor;\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = vec4(ourColor, 1.0f);\n"
                                     "}\n\0";
int main()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "Failed to Initialise the GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(600, 600, "Square Annulus", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        std::cout << "Vertex shader compilation failed:\n"
                  << log << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "Fragment shader compilation failed:\n"
                  << log << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cout << "Shader program linking failed:\n"
                  << log << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // triangle 1 RED
        -0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // GREEN
        0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,  // BLUE
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // triangle 2 RED
        0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f,  // GREEN
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,    // BLUE
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // triangle 3 RED
        0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f,  // GREEN
        0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,   // BLUE
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // triangle 4 RED
        0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f,   // GREEN
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,     // BLUE
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     //triangle 5 RED
        0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f,   // GREEN
        -0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,  // BLUE
        -0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f,  // triangle 6 RED
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,     // GREEN
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,    // BLUE
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // triangle 7 RED
        -0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // GREEN
        -0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,  // BLUE
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,    // triangle 8 RED
        -0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // GREEN
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f};  // BLUE

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 24);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}