/* Author: NagaChaitanya Vellanki */

#include <GLFW/glfw3.h>

void cantor_set(float x, float y, float length) {

  glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
  glLineWidth(5.0f);
  glBegin(GL_LINES);
  glVertex2f(x, y);
  glVertex2f(x + length, y);
  glEnd();
  y -= 20.0f;
  if(length > 1.0f) {
    cantor_set(x, y, length / 3);
    cantor_set(x + 2 * (length / 3), y, length / 3);
  }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  int main(int argc, char *argv[]) {
    GLFWwindow* window;

    if(!glfwInit()) {
      return -1;
    }

    GLFWmonitor* monitor  = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    window = glfwCreateWindow(vidmode->width, vidmode->height, "Cantor Set", monitor, NULL);
    if(!window) {
      glfwTerminate();
      return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float x = 0.0f;
    float y = height / 2;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while(!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      cantor_set(x, y, width);
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
