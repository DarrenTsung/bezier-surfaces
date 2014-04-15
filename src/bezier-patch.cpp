#include "bezier-patch.h"

void BezierPatch::uniform_subdivision(float step_size) {
    // compute number of subdivisions for step-size
    int num_subdivisions = ((1.0f + 0.0005f) / step_size);

    for(int i=0; i<=num_subdivisions; i++) {
        // create new rows for the new 2D vector
        vector<Point3f*> row(num_subdivisions+1);
        uniform_p.push_back(row);

        float u = i*step_size;
        for(int j=0; j<=num_subdivisions; j++) {
            float v = j*step_size;

            Point3f *point = calculateUVpoint(u, v);
            uniform_p[i][j] = point;
        }
    }
}

Point3f* BezierPatch::calculateUVpoint(float u, float v) {
    RowVector4f U(pow(u, 3), pow(u, 2), u, 1);
    RowVector4f V(pow(v, 3), pow(v, 2), v, 1);
    Vector4f trans_V = V.transpose();

    Matrix4f M;
    M <<  -1,  3, -3, 1,
           3, -6,  3, 0,
          -3,  3,  0, 0,
           1,  0,  0, 0;

    Matrix4f trans_M = M.transpose();

    // get the matrix of x's for the points only
    Matrix4f p_x = getDimensionMatrixOfPoints(0);
    float x = U * M * p_x * trans_M * trans_V;
    Matrix4f p_y = getDimensionMatrixOfPoints(1);
    float y = U * M * p_y * trans_M * trans_V;
    Matrix4f p_z = getDimensionMatrixOfPoints(2);
    float z = U * M * p_z * trans_M * trans_V;

    Point3f *p = new Point3f(x, y, z);
    return p;
}

Matrix4f BezierPatch::getDimensionMatrixOfPoints(int spec) {
    Matrix4f m;
    // pull out the value you want from the points and create a 4x4 matrix
    m << (*(p[0][0]))[spec], (*(p[0][1]))[spec], (*(p[0][2]))[spec], (*(p[0][3]))[spec],
        (*(p[1][0]))[spec], (*(p[1][1]))[spec], (*(p[1][2]))[spec], (*(p[1][3]))[spec],
        (*(p[2][0]))[spec], (*(p[2][1]))[spec], (*(p[2][2]))[spec], (*(p[2][3]))[spec],
        (*(p[3][0]))[spec], (*(p[3][1]))[spec], (*(p[3][2]))[spec], (*(p[3][3]))[spec];
    return m;
}

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
    vector<vector<Point3f*> > p = this->uniform_p;

    // draw each quad of the patch
    for(int i=0; i<p.size()-1; i++) {
        for(int j=0; j<p[i].size()-1; j++) {
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
