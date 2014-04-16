#include "include.h"
#include "bezier-main.h"

using namespace std;

BezierMain mainBez;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);				// clear the color buffer

    glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
    glLoadIdentity();				        // make sure transformation is "zero'd"

    // drawing is done here
    mainBez.draw();
    // end drawing

    glFlush();
    glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

void reshape(int w, int h) {

}

void handleInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:    // ESCAPE KEY
        exit(0);
        break;
    // spacebar closes window
    case ' ':
        exit(0);
        break;
    case '-':
        mainBez.transform(SCALE, Vector3f(0.8,0.8,0.8));
        display();
        break;
    case '+':
        mainBez.transform(SCALE, Vector3f(1.2,1.2,1.2));
        display();
        break;
    case 'w':
        mainBez.toggle_draw_mode();
        display();
        break;
    }
}

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} ArrowKeyState;

ArrowKeyState arrow_state;

void handleSpecialKeypress(int key, int x, int y) {
    int mod = glutGetModifiers();
    switch (key) {
        case GLUT_KEY_LEFT:
            arrow_state = LEFT;
            // handle left key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                mainBez.transform(TRANSLATION, Vector3f(-0.05,0,0));
            } else {
                // rotate it around the normal
                mainBez.transform(ROTATION, mainBez.get_normal(), 8);
            }
            break;

        case GLUT_KEY_RIGHT:
            arrow_state = RIGHT;
            // handle right key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                mainBez.transform(TRANSLATION, Vector3f(0.05,0,0));
            } else {
                // rotate it around the normal
                mainBez.transform(ROTATION, mainBez.get_normal(), -8);
            }
            break;

        case GLUT_KEY_UP:
            arrow_state = UP;
            // handle up key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                mainBez.transform(TRANSLATION, Vector3f(0,0.05,0));
            } else {
                // rotate it around the right vector
                mainBez.transform(ROTATION, mainBez.get_right(), -8);
            }
            break;

        case GLUT_KEY_DOWN:
            arrow_state = DOWN;
            // handle down key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                mainBez.transform(TRANSLATION, Vector3f(0,-0.05,0));
            } else {
                // rotate it around the right vector
                mainBez.transform(ROTATION, mainBez.get_right(), 8);
            }
            break;
    }
    display();
}

void handleSpecialKeyReleased(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            arrow_state = NONE;
            break;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        mainBez.parsePatchfile(argv[1]);
        float subdivision_param = atof(argv[2]);
        string type = argv[3];
        if (type == "-u") {
            mainBez.apply_uniform_subdivision(subdivision_param);
        } else if (type == "-a") {
            // CREATE ADAPTIVE HERE
        }
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

    // set handleInput() function to take keyboard events
    glutKeyboardFunc(handleInput);
    // special func for arrow keys... wtf
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);

    glutMainLoop();

    return 0;
}
