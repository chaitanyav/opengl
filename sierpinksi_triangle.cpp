//
// Author: NagaChaitanya Vellanki
//
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static float LINE_LENGTH = 6.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

// variables : A B
// constants : + −
// start  : A
// rules  : (A → B−A−B), (B → A+B+A)
// angle  : 60°
// A, B move forward
// + turn left by 60 degrees
// - turn right by 60 degrees

static std::string current("A");
static int generation = 0;

void lSystemRepresentation() {
  while(generation < 8) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'A':
          next.append("B-A-B");
          break;
        case 'B':
          next.append("A+B+A");
          break;
        case '-':
          next.append("-");
          break;
        case '+':
          next.append("+");
          break;
      };
    }

    current = next;
    generation++;
    //std::cout << "Generation: " << generation++ <<  " " << current << std::endl;
  }
}

int main(int argc, char *argv[]) {
  GLFWwindow* window;

  if(!glfwInit()) {
    return -1;
  }

  GLFWmonitor* monitor  = glfwGetPrimaryMonitor();
  const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

  window = glfwCreateWindow(vidmode->width, vidmode->height, "Sierpinski Triangle", monitor, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float x = 0.0f;
  float y = 0.0f;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  lSystemRepresentation();

  while(!glfwWindowShouldClose(window)) {
    x = width / 4;
    y = 0.0f;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      if(*it == 'A' || *it == 'B') {
        glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(x, y);
        x = x + LINE_LENGTH;
        glVertex2f(x, y);
        glEnd();
      }
      if(*it == '-' || *it == '+') {
        glTranslatef(x, y, 0.0f);
        x = 0.0f;
        y = 0.0f;
        float angle = ((*it == '-') ? -60.0f : 60.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
      }
    }
    glPopMatrix();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
