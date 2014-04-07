#include "bezier-main.h"

#define PI 3.14159265359

BezierMain::BezierMain() {
    t = Transform<float,3,Affine>::Identity();
    normal = Vector3f(0,0,1);
    right = Vector3f(1,0,0);
}

void BezierMain::parsePatchfile(char *filename) {
    ifstream in(filename);

    String line;
    String patch;

    getline(in, line);

    istringstream sin(line);
    sin >> patch;

    int num_patches = atoi(patch.c_str());

    for(int i=0; i<num_patches; i++) {
        String value;

        // need to create rows every time we use 2d vector
        vector<vector<Point3f*> > mat;
        for(int i=0; i<4; i++)
        {
            vector<Point3f*> row(4);
            mat.push_back(row);
        }

        // four rows of values
        for(int j=0; j<4; j++) {
            getline(in, line);
            istringstream sin(line);
            // four values per row
            for(int k=0; k<4; k++) {
                Point3f *p = new Point3f;
                sin >> value;
                (*p)[0] = atof(value.c_str());
                sin >> value;
                (*p)[1] = atof(value.c_str());
                sin >> value;
                (*p)[2] = atof(value.c_str());

                mat[j][k] = p;
            }
        }

        /* used to print out the patch
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                cout << vectorString((*(mat[i][j]))) << " ";
            }
            cout << endl;
        }
        */

        BezierPatch *new_patch = new BezierPatch(mat);
        patches.push_back(new_patch);
    }
}

void BezierMain::draw() {
    // to go to wireframe mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    for(int i=0; i<patches.size(); i++) {
        patches[i]->draw(t);
    }
    // to go back to normal mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void BezierMain::transform(TransformationType a, Vector3f axis, float degrees) {
    t = AngleAxisf((degrees*PI)/180.0f, axis) * t;
}

void BezierMain::transform(TransformationType a, Vector3f amount) {
    t = Translation<float,3>(amount) * t;
}

Vector3f BezierMain::get_normal() {
    return t.linear() * normal;
}

Vector3f BezierMain::get_right() {
    return t.linear() * right;
}