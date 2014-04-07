#ifndef BEZIER_PATCH_H
#define BEZIER_PATCH_H

#include "include.h"

class BezierPatch {
    private:
        vector<vector<Point3f*> > p;

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        // constructors
        BezierPatch();
        BezierPatch(vector<vector<Point3f*> > a);

        void draw();

        vector<vector<Point3f*> > get_matrix();
        void set_matrix(vector<vector<Point3f*> > a);
};

#endif // BEZIER_PATCH_H
