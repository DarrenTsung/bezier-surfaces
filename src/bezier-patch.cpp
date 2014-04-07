#include "bezier-patch.h"

BezierPatch::BezierPatch() {
    for(int i=0; i<4; i++)
    {
        vector<Point3f*> row(4);
        p.push_back(row);
    }
}

BezierPatch::BezierPatch(vector<vector<Point3f*> > a) {
    for(int i=0; i<4; i++)
    {
        vector<Point3f*> row(4);
        p.push_back(row);
    }
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            p[i][j] = a[i][j];
        }
    }
}

void BezierPatch::draw(Transform<float,3,Affine> T) {
    // draw each quad of the patch
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            glBegin(GL_QUADS);
            // counter-clockwise order
            Point3f a = T * (*(p[i+1][j]));
            glVertex2f(a[0], a[1]);
            a = T * (*(p[i][j]));
            glVertex2f(a[0], a[1]);
            a = T * (*(p[i][j+1]));
            glVertex2f(a[0], a[1]);
            a = T * (*(p[i+1][j+1]));
            glVertex2f(a[0], a[1]);
            glEnd();
        }
    }
}

vector<vector<Point3f*> > BezierPatch::get_matrix() {
    return p;
}

void BezierPatch::set_matrix(vector<vector<Point3f*> > a) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            p[i][j] = a[i][j];
        }
    }
}
