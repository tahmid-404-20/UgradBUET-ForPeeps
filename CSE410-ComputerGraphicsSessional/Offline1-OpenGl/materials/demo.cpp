#include <bits/stdc++.h>

#ifdef __linux__
#include <GL/glut.h>
#elif WIN32
#include <glut.h>
#include <windows.h>
#endif

double objX = 0, objY = 0, objZ = 0;
double camera_ex, camera_ey, camera_ez, camera_lx, camera_ly, camera_lz,
    camera_hx, camera_hy, camera_hz;

double x_pos = 0, y_pos = 0, z_pos = 0;

#define CAMERA_CHANGE 0.5
#define OBJECT_ROTATION 0.1

void init() {
  printf("Do your initialization here\n");
  glClearColor(0.0f, 0.0f, 0.0f,
               1.0f); // Set background color to black and opaque

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1, 1, 500);

  //   initialize camera position
  camera_ex = 40;
  camera_ey = 40;
  camera_ez = 40;
  camera_lx = 0;
  camera_ly = 0;
  camera_lz = 0;
  camera_hx = 0;
  camera_hy = 0;
  camera_hz = 1;

  x_pos = 0;
  y_pos = 0;
  z_pos = 0;
}

void keyboardSpecialListener(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    printf("Up arrow pressed\n");
    camera_ez += CAMERA_CHANGE;
    break;

  case GLUT_KEY_DOWN:
    printf("Down arrow pressed\n");
    camera_ez -= CAMERA_CHANGE;
    break;

  case GLUT_KEY_RIGHT:
    printf("Right arrow pressed\n");
    camera_ex += CAMERA_CHANGE;
    break;

  case GLUT_KEY_LEFT:
    printf("Left arrow pressed\n");
    camera_ex -= CAMERA_CHANGE;
    break;

  case GLUT_KEY_PAGE_UP:
    printf("Page up pressed\n");
    camera_ey += CAMERA_CHANGE;
    break;

  case GLUT_KEY_PAGE_DOWN:
    printf("Page down pressed\n");
    camera_ey -= CAMERA_CHANGE;
    break;

  default:
    printf("We don't know what you pressedBRO\n");
    break;
  }
}

void keyboardListener(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    printf("w pressed\n");
    objX += OBJECT_ROTATION;
    break;

  case 's':
    printf("s pressed\n");
    objX -= OBJECT_ROTATION;
    break;

  case 'a':
    printf("a pressed\n");
    objY += OBJECT_ROTATION;
    break;

  case 'd':
    printf("d pressed\n");
    objY -= OBJECT_ROTATION;
    break;

  case 'z':
    printf("z pressed\n");
    objZ += OBJECT_ROTATION;
    break;

  case 'x':
    printf("x pressed\n");
    objZ -= OBJECT_ROTATION;
    break;

  case 'i':
    printf("i pressed\n");
    x_pos += 1;
    printf("x_pos = %lf\n", x_pos);
    break;

  case 'k':
    printf("k pressed\n");
    printf("x_pos = %lf\n", x_pos);
    x_pos -= 1;
    break;

  case 'j':
    printf("j pressed\n");
    y_pos += 1;
    printf("y_pos = %lf\n", y_pos);
    break;

  case 'l':
    printf("l pressed\n");
    y_pos -= 1;
    printf("y_pos = %lf\n", y_pos);
    break;

  case 'n':
    printf("n pressed\n");
    z_pos += 1;
    break;

  case 'm':
    printf("m pressed\n");
    z_pos -= 1;
    break;

  default:
    printf("We don't know what you pressedBRO\n");
    break;
  }
}

void drawCheckerBox(double a, int color = 0) {
  glBegin(GL_QUADS);
  {
    if (color == 0) {
      glColor3f(0.0f, 0.0f, 0.0f); // Black
    } else {
      glColor3f(1.0f, 1.0f, 1.0f); // White
    }
    glVertex3f(0, 0, 0);
    glVertex3f(0, a, 0);
    glVertex3f(a, a, 0);
    glVertex3f(a, 0, 0);
  }
  glEnd();
}

void drawCheckers(double a) {
  for (int i = -40; i < 40; i++) {
    for (int j = -40; j < 40; j++) {
      glPushMatrix();
      glTranslatef(i * a, j * a, 0);
      drawCheckerBox(a, (i + j) % 2);
      glPopMatrix();
    }
  }
}

void drawSquare(double a) {
  glBegin(GL_QUADS);
  {
    glVertex3f(0, 0, 0);
    glVertex3f(0, a, 0);
    glVertex3f(a, a, 0);
    glVertex3f(a, 0, 0);
  }
  glEnd();
}

void axes() {
  glBegin(GL_LINES);
  {
    glColor3f(1.0f, 0.0f, 0.0f); // Red - x axis
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);

    glColor3f(0.0f, 1.0f, 0.0f); // Green - y axis
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);

    glColor3f(0.0f, 0.0f, 1.0f); // Blue - z axis
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
  }
  glEnd();
}

void display() {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camera_ex, camera_ey, camera_ez, camera_lx, camera_ly, camera_lz,
            camera_hx, camera_hy, camera_hz);
  axes();
  //   drawCheckers(5);

  glColor3f(1.0f, 0.5f, 0.0f);
  glPushMatrix();
  {
    
    glRotatef(objX * 180 / M_PI, 1, 0, 0);
    // glRotatef(objY * 180 / M_PI, 0, 1, 0);
    // glRotatef(objZ * 180 / M_PI, 0, 0, 1);
    glTranslatef(x_pos, y_pos, z_pos);
    drawSquare(6);
  }
  glPopMatrix();

  glutSwapBuffers();
}

void idle() {
  glutPostRedisplay(); // Post a re-paint request to activate display(),
                       // variable set koire then call koro display
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(600, 600); // Set the window's initial width & height
  glutInitWindowPosition(750,
                         250); // Position the window's initial top-left corner
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Demo - Tahmid");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardListener);
  glutSpecialFunc(keyboardSpecialListener);

  glutIdleFunc(idle);
  init();

  glutMainLoop();
  return 0;
}