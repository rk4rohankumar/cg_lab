#include <GL/glut.h>

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);              // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);               // Set the type of depth-test
    glShadeModel(GL_SMOOTH);              // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity();                                   // Reset the view
    glTranslatef(0.0f, 0.0f, -5.0f);                   // Move into the screen
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);               // Rotate about the x-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);               // Rotate about the y-axis

    // Draw a cube
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    // Top face
    glColor3f(0.0f, 1.0f, 0.0f);      // Green
    glVertex3f(1.0f, 1.0f, -1.0f);    // Top-right of top face
    glVertex3f(-1.0f, 1.0f, -1.0f);   // Top-left of top face
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom-left of top face
    glVertex3f(1.0f, 1.0f, 1.0f);     // Bottom-right of top face
    // Bottom face
    glColor3f(1.0f, 0.5f, 0.0f);      // Orange
    glVertex3f(1.0f, -1.0f, 1.0f);    // Top-right of bottom face
    glVertex3f(-1.0f, -1.0f, 1.0f);   // Top-left of bottom face
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom-left of bottom face
    glVertex3f(1.0f, -1.0f, -1.0f);   // Bottom-right of bottom face
    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);      // Red
    glVertex3f(1.0f, 1.0f, 1.0f);     // Top-right of front face
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top-left of front face
    glVertex3f(-1.0f, -1.0f, 1.0f);   // Bottom-left of front face
    glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom-right of front face
    // Back face
    glColor3f(1.0f, 1.0f, 0.0f);      // Yellow
    glVertex3f(1.0f, -1.0f, -1.0f);   // Top-right of back face
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Top-left of back face
    glVertex3f(-1.0f, 1.0f, -1.0f);   // Bottom-left of back face
    glVertex3f(1.0f, 1.0f, -1.0f);    // Bottom-right of back face
    // Left face
    glColor3f(0.0f, 0.0f, 1.0f);      // Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top-right of left face
    glVertex3f(-1.0f, 1.0f, -1.0f);   // Top-left of left face
    glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom-left of left face
    glVertex3f(-1.0f, -1.0f, 1.0f);   // Bottom-right of left face
    // Right face
    glColor3f(1.0f, 0.0f, 1.0f);      // Magenta
    glVertex3f(1.0f, 1.0f, -1.0f);    // Top-right of right face
    glVertex3f(1.0f, 1.0f, 1.0f);     // Top-left of right face
    glVertex3f(1.0f, -1.0f, 1.0f);    // Bottom-left of right face
    glVertex3f(1.0f, -1.0f, -1.0f);   // Bottom-right of right face
    glEnd();                          // End of drawing color-cube
    glFlush();                        // Flush the OpenGL pipeline to the viewport
    glutSwapBuffers();                // Swap the front and back frame buffers (double buffering)
}

void reshape(int width, int height) {
    if (height == 0) height = 1; // Prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, width, height); // Set the viewport to cover the new window
    glMatrixMode(GL_PROJECTION);     // To operate on the Projection matrix
    glLoadIdentity();                // Reset
    gluPerspective(45.0f, aspect, 0.1f, 100.0f); // Set the perspective
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'x':
        angleX += 1.0f;
        break;
    case 'X':
        angleX -= 1.0f;
        break;
    case 'y':
        angleY += 1.0f;
        break;
    case 'Y':
        angleY -= 1.0f;
        break;
    }
    glutPostRedisplay(); // Post a paint request to activate display()
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);             // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);   // Enable double buffered mode
    glutInitWindowSize(640, 480);      // Set the window's initial width & height
    glutInitWindowPosition(50, 50);     // Position the window's initial top-left corner
    glutCreateWindow("3D Transformation"); // Create window with the given title

    glutDisplayFunc(display); // Register callback handler for window re-paint event
    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    glutKeyboardFunc(keyboard); // Register callback handler for keyboard event

    initGL(); // Our own OpenGL initialization
    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}