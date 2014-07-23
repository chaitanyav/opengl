//
// Author: NagaChaitanya Vellanki
//
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static float LINE_LENGTH = 0.25f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

// variables : X F
// constants : + − [ ]
// start  : X
// rules  : (X → F-[[X]+X]+F[+FX]-X), (F → FF)
// angle  : 35°
// - turn left by 25 degrees
// + turn right by 25 degrees
std::string fractalPlantLSystemRepresentation() {
  std::string current("X");
  int generation = 0;

  while(generation < 11) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'X':
          next.append("F-[[X]+X]+F[+FX]-X");
          break;
        case 'F':
          next.append("FF");
          break;
        case '-':
          next.append("-");
          break;
        case '+':
          next.append("+");
          break;
        case '[':
          next.append("[");
          break;
        case ']':
          next.append("]");
          break;
      };
    }

    current = next;
    generation++;
    //std::cout << "Generation: " <<  " " << current << std::endl;
  }

  return current;
}

void drawFractalPlant(float x, float y, std::string lrep) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  for(std::string::iterator it = lrep.begin(); it != lrep.end(); it++) {
    if(*it == 'F') {
      glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
      glLineWidth(3.0f);
      glBegin(GL_LINES);
      glVertex2f(x, y);
      y = y + LINE_LENGTH;
      glVertex2f(x, y);
      glEnd();
    }
    if(*it == '[') {
      glPushMatrix();
    }
    if(*it == ']') {
      glPopMatrix();
    }
    if(*it == '-' || *it == '+') {
      glTranslatef(x, y, 0.0f);
      x = 0.0f;
      y = 0.0f;
      float angle = ((*it == '-') ? 25.0f : -25.0f);
      glRotatef(angle, 0.0f, 0.0f, 1.0f);
    }
  }
  glPopMatrix();
}

int main(int argc, char *argv[]) {
  GLFWwindow* window;

  if(!glfwInit()) {
    return -1;
  }

  GLFWmonitor* monitor  = glfwGetPrimaryMonitor();
  const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

  window = glfwCreateWindow(vidmode->width, vidmode->height, "Fractal Plant", monitor, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  float x;
  float y;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  std::string lrep = fractalPlantLSystemRepresentation();
  while(!glfwWindowShouldClose(window)) {
    drawFractalPlant(width / 2, height / 8, lrep);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
