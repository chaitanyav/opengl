#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float PI = 3.14159265358979323846;
static float RADIUS = 300.0f;

void draw_circle(float x, float y, float radius) {
  glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
  glPointSize(2.0f);
  glBegin(GL_POINTS);
  for (int radian = 0; radian < 360; radian++)
    {
      float degree = radian * (PI / 180.0);
      glVertex2f(x + radius * cosf(degree), y + radius * sinf(degree));
    }

    glEnd();
    if(radius > 10.0f) {
      draw_circle(x + radius, y, radius / 2);
      draw_circle(x - radius, y, radius / 2);
      draw_circle(x, y + radius, radius / 2);
      draw_circle(x, y - radius, radius / 2);
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

      window = glfwCreateWindow(vidmode->width, vidmode->height, "Circle Recursive", monitor, NULL);
      if(!window) {
        glfwTerminate();
        return -1;
      }

      glfwSetKeyCallback(window, key_callback);
      glfwMakeContextCurrent(window);

      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      float x = width / 2;
      float y = height / 2;

      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_circle(x, y, RADIUS);
        glfwSwapBuffers(window);
        glfwPollEvents();
      }

      glfwTerminate();
      return 0;
    }
