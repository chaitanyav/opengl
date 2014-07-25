// Author: NagaChaitanya Vellanki
// Reference: http://en.wikipedia.org/wiki/Gosper_curve


#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static float LINE_LENGTH = 20.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

// constants : + −
// Axiom: A
// Replacement rules:
// A -> A-B--B+A++AA+B-
// B -> +A-BB--B-A++A+B
// angle  : 60°
// + turn  left by 60 degrees
// - turn right by 60 degrees
std::string peanoGosperCurveSystemRepresentation() {
  std::string current("A");
  int generation = 0;

  while(generation < 4) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'A':
          next.append("A-B--B+A++AA+B-");
          break;
        case 'B':
          next.append("+A-BB--B-A++A+B");
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
    //std::cout << "Generation: " <<  " " << current << std::endl;
  }

  return current;
}


int main(int argc, char *argv[]) {
  GLFWwindow *window;

  if(!glfwInit()) {
    return -1;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
  window = glfwCreateWindow(vidmode->width, vidmode->height, "Peano-Gosper Curve", monitor, NULL);

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
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);

  std::string lrep = peanoGosperCurveSystemRepresentation();
  while(!glfwWindowShouldClose(window)) {
    x = width / 1.9f;
    y =  height - 200.0f;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    for(std::string::iterator it = lrep.begin(); it != lrep.end(); it++) {
      if(*it == 'A' || *it == 'B') {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(3.0f);

        GLfloat vertices[] = {x, y, x + LINE_LENGTH, y};
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
        x = x + LINE_LENGTH;
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
