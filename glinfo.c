// Note: Need to create a context before using glGetString

#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  GLFWwindow *window;

  if(!glfwInit()) {
    return -1;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
  window = glfwCreateWindow(vidmode->width, vidmode->height, "GL Info", monitor, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  printf("Vendor: %s\nVersion: %s\nExtensions: %s\nRenderer: %s\n", glGetString(GL_VENDOR), glGetString(GL_VERSION), glGetString(GL_EXTENSIONS), glGetString(GL_RENDERER));
  glfwTerminate();
  return 0;
}
