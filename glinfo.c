// Note: Need to create a context before using glGetString

#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  GLFWwindow *window;

  if(!glfwInit()) {
    return -1;
  }

  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
  window = glfwCreateWindow(vidmode->width, vidmode->height, "GL Info", monitor, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  printf("Vendor: %s\nVersion: %s\nExtensions: %s\nRenderer: %s\nGLSL Version %s\n", glGetString(GL_VENDOR), glGetString(GL_VERSION), glGetString(GL_EXTENSIONS), glGetString(GL_RENDERER), glGetString(GL_SHADING_LANGUAGE_VERSION));
  glfwTerminate();
  return 0;
}
