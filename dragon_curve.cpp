//
// Author: NagaChaitanya Vellanki
//

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <climits>

static float LINE_LENGTH = 0.5f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}


//angle: 120°
// initial string F
// string rewriting rules
// F ↦ F+F−F
// - turn left by 90 degrees
// + turn right by 90 degrees
std::string terDragonLSystemRepresentation() {
  int generation = 0;
  std::string current = "F";

  while(generation < 14) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'F':
        next.append("F+F-F");
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


//angle: 90°
//initial string FX+FX+
//string rewriting rules
//X ↦ X+YF
//Y ↦ FX−Y
// - turn left by 90 degrees
// + turn right by 90 degrees
std::string twinDragonLSystemRepresentation() {
  int generation = 0;
  std::string current = "FX+FX+";

  while(generation < 20) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'X':
        next.append("X+YF");
        break;
        case 'Y':
        next.append("FX-Y");
        break;
        case 'F':
        next.append("F");
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


// Heighway dragon
// angle: 90°
// initial: string FX
// string rewriting rules
// X ↦ X+YF+
// Y ↦ −FX−Y.
// - turn left by 90 degrees
// + turn right by 90 degrees
std::string heighwayDragonLSystemRepresentation() {
  int generation = 0;
  std::string current = "FX";

  while(generation < 21) {
    std::string next;
    for(std::string::iterator it = current.begin(); it != current.end(); it++) {
      switch(*it) {
        case 'X':
        next.append("X+YF+");
        break;
        case 'Y':
        next.append("-FX-Y");
        break;
        case 'F':
        next.append("F");
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

void drawDragon(int type, float x, float y) {
  std::string lrep;
  float angle;

  switch(type) {
    case 0:
    lrep = heighwayDragonLSystemRepresentation();
    angle = 90.0f;
    break;
    case 1:
    lrep = twinDragonLSystemRepresentation();
    angle = 90.0f;
    break;
    case 2:
    lrep = terDragonLSystemRepresentation();
    angle = 120.0f;
    break;
  };


  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  for(std::string::iterator it = lrep.begin(); it != lrep.end(); it++) {
    if(*it == 'F') {
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
      int sign = ((*it == '-') ? 1 : -1);
      glRotatef(sign * angle, 0.0f, 0.0f, 1.0f);
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

  window = glfwCreateWindow(vidmode->width, vidmode->height, "Sierpinski Triangle", monitor, NULL);
  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  int width, height;

  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, 0.0f, height, 0.0, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  long int count = 0;
  while(!glfwWindowShouldClose(window)) {
    if(count > 100) {
      count = 0;
    }

    switch(++count % 3) {
      case 0:
      drawDragon(0, width / 2, height / 2);
      break;
      case 1:
      drawDragon(1, width / 2, height / 2);
      break;
      case 2:
      drawDragon(2, width / 2, height - 200.0f);
      break;
    };
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
