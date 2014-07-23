//
// Author: NagaChaitanya Vellanki
//
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static float LINE_LENGTH = 10.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

// Alphabet : A, B
// Constants : F + -
// Axiom : A
// Production rules:
// A → - B F + A F A + F B -
// B → + A F - B F B - F A +
// - turn left by 90 degrees
// + turn right by 90 degrees
std::string hilbertCurveLSystemRepresentation() {
  std::string current("FA");
  int generation = 0;

  while(generation < 7) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'A':
          next.append("-BF+AFA+FB-");
          break;
        case 'B':
          next.append("+AF-BFB-FA+");
          break;
        case '-':
          next.append("-");
          break;
        case '+':
          next.append("+");
          break;
        case 'F':
          next.append("F");
          break;
      };
    }

    current = next;
    generation++;
    //std::cout << "Generation: " <<  " " << current << std::endl;
  }

  return current;
}

void drawHilbertCurve(float x, float y, std::string lrep) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  for(std::string::iterator it = lrep.begin(); it != lrep.end(); it++) {
    if(*it == 'F') {
      glColor4f(0.5f, 1.0f, 0.0f, 1.0f);
      glLineWidth(4.0f);
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
      float angle = ((*it == '-') ? 90.0f : -90.0f);
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

  window = glfwCreateWindow(vidmode->width, vidmode->height, "Hilbert Curve", monitor, NULL);
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

  std::string lrep = hilbertCurveLSystemRepresentation();
  while(!glfwWindowShouldClose(window)) {
    drawHilbertCurve(width / 4, 20.0f, lrep);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
