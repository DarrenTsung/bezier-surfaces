#include "include.h"
#include "bezier-main.h"

using namespace std;

BezierMain mainBez;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

    glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
    glLoadIdentity();				        // make sure transformation is "zero'd"

    // drawing is done here
    glutWireSphere(0.5,10,10);
    // end drawing

    glFlush();
    glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

void reshape(int w, int h) {

}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        mainBez.parsePatchfile(argv[1]);

    } else {
        cout << "No filename inputted." << endl;
    }

    //This initializes glut
    glutInit(&argc, argv);

    //This tells glut to use a double-buffered window with red, green, and blue channels
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bezier-Surfaces");

    glutDisplayFunc(display);				// function to run when its time to draw something
    glutReshapeFunc(reshape);				// function to run when the window gets resized

    glutMainLoop();

    return 0;
}
