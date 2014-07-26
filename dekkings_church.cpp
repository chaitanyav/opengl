//
// Author: NagaChaitanya Vellanki
//
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static float LINE_LENGTH = 15.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

// constants : + −
// Axiom: wxyz
// F = nothing
// w = Fw+F-zFw-F+x
// z = ++F--y-F+x++F--y-F+x
// y = ++F--y+F-z
// x = Fw+F-z
// angle : 90°
// + turn  left by 90 degrees
// - turn right by 90 degrees
std::string dekkingsChurchlSystemRepresentation() {
  std::string current("wxyz");
  int generation = 1;

  while(generation < 8) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'F':
        break;
        case 'w':
        next.append("Fw+F-zFw-F+x");
        break;
        case 'x':
        next.append("Fw+F-z");
        break;
        case 'y':
        next.append("++F--y+F-z");
        break;
        case 'z':
        next.append("++F--y-F+x++F--y-F+x");
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
  GLFWwindow* window;

  if(!glfwInit()) {
    return -1;
  }

  GLFWmonitor* monitor  = glfwGetPrimaryMonitor();
  const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

  window = glfwCreateWindow(vidmode->width, vidmode->height, "Dekking's Church", monitor, NULL);
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

  std::string lrep = dekkingsChurchlSystemRepresentation();

  while(!glfwWindowShouldClose(window)) {
    x = width / 3.5f;
    y = height / 4.0f;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    for(std::string::iterator it = lrep.begin(); it != lrep.end(); it++) {
      if(*it == 'F') {
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glLineWidth(4.0f);

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
        float angle = ((*it == '-') ? -90.0f : 90.0f);
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
