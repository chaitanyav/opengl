/* Author: NagaChaitaya Vellanki */

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static float PI = 3.14159265358979323846;
static float RADIUS = 40.0f;

void draw_circle(float x, float y) {
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glLineWidth(4.0f);
  glBegin(GL_TRIANGLE_FAN);
  for (int radian = 0; radian < 360; radian++)
    {
      float degree = radian * (PI / 180.0);
      glVertex2f(x + RADIUS * cosf(degree), y + RADIUS * sinf(degree));
    }

    glEnd();
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

      window = glfwCreateWindow(vidmode->width, vidmode->height, "Bouncing Ball", monitor, NULL);
      if(!window) {
        glfwTerminate();
        return -1;
      }

      glfwSetKeyCallback(window, key_callback);
      glfwMakeContextCurrent(window);

      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      float ratio = width / (float) height;
      float x = 0.0f;
      float y = 0.0f;
      float xspeed = 10.0f;
      float yspeed = 10.0f;

      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        x = x + xspeed;
        y = y + yspeed;

        if ((x > width) || (x < 0)) {
          xspeed = xspeed * -1;
        }
        if ((y > height) || (y < 0)) {
          yspeed = yspeed * -1;
        }

        draw_circle(x, y);
        glfwSwapBuffers(window);
        glfwPollEvents();
      }

      glfwTerminate();
      return 0;
    }
