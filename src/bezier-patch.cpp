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
