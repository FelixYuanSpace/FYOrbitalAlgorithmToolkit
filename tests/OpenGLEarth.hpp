#ifdef USE_OPENGL_TEST
#include <GL/glut.h>

float eyeX = 0.0, eyeY = 0.0, eyeZ = 20000000.0; // Camera position
float centerX = 0.0, centerY = 0.0, centerZ = 0.0; // Look-at point
float angleX = 0.0;          // Rotation angle around the X-axis
float angleY = 0.0;          // Rotation angle around the Y-axis
bool leftButtonDown = false; // Tracks whether the left mouse button is pressed
int lastX, lastY;            // Stores the last mouse position

void addSatellite(float x, float y, float z, float radius, float r, float g, float b)
{

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);

    glRotatef(-90.0, 1.0, 0.0, 0.0); // Rotate the Earth to align the axis

    glRotatef(angleX, 1.0, 0.0, 0.0); // Rotate around the X-axis
    glRotatef(angleY, 0.0, 0.0, 1.0); // Rotate around the Y-axis
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(6371000.0, 50, 50);
    glFlush();
}


void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            leftButtonDown = true; // Left mouse button pressed
            lastX = x;             // Record current mouse position
            lastY = y;
        }
        else if (state == GLUT_UP)
        {
            leftButtonDown = false; // Left mouse button released
        }
    }
    if (button == 3 && state == GLUT_DOWN)
    { // Mouse wheel up
        eyeZ -= 1000000.0;
    }
    else if (button == 4 && state == GLUT_DOWN)
    { // Mouse wheel down
        eyeZ += 1000000.0;
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    if (leftButtonDown) { // Only process when the left mouse button is pressed
        int deltaX = lastX - x;
        int deltaY = lastY - y;
        angleY -= deltaX * 0.1; // Adjust Y-axis rotation based on X movement
        angleX -= deltaY * 0.1; // Adjust X-axis rotation based on Y movement
        lastX = x;
        lastY = y;
        glutPostRedisplay();
    }
}

void mouseEntry(int state)
{
    if (state == GLUT_ENTERED)
    {
        glutMotionFunc(motion); // Register motion function when mouse enters window
    }
    else
    {
        glutMotionFunc(NULL); // Unregister when mouse leaves window
    }
}

void initEarth(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Hello World");

    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)1024 / (double)768, 1.0, 100000000.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    //glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion); // Register mouse motion event handler

    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        eyeZ -= 1000000.0; // Move forward
        break;
    case 's':
        eyeZ += 1000000.0; // Move backward
        break;
    case 'a':
        eyeX -= 1000000.0; // Move left
        break;
    case 'd':
        eyeX += 1000000.0; // Move right
        break;
    case 'q':
        eyeY += 1000000.0; // Move up
        break;
    case 'e':
        eyeY -= 1000000.0; // Move down
        break;
    }
    glutPostRedisplay();
}
#endif