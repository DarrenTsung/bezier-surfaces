#ifndef BEZIER_PATCH_H
#define BEZIER_PATCH_H

#include "include.h"

class BezierPatch {
    private:
        // control points
        vector<vector<Point3f*> > p;
        // subdivision
        vector<vector<Point3f*> > uniform_p;

        Point3f* calculateUVpoint(float u, float v);
        Matrix4f getDimensionMatrixOfPoints(int spec);

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        // subdivision methods
        void uniform_subdivision(float step_size);


        // constructors
        BezierPatch();
        BezierPatch(vector<vector<Point3f*> > a);

        void draw(Transform<float,3,Affine> T);

        vector<vector<Point3f*> > get_matrix();
        void set_matrix(vector<vector<Point3f*> > a);
};

#endif // BEZIER_PATCH_H
