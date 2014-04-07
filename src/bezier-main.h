#ifndef BEZIER_MAIN_H
#define BEZIER_MAIN_H

#include "include.h"
#include "bezier-patch.h"
#include <sstream>

typedef enum {
    ROTATION,
    TRANSLATION
} TransformationType;

class BezierMain {
    public:
        // constructors
        BezierMain();

        void parsePatchfile(char* filename);
        void draw();

        void transform(TransformationType a, Vector3f axis, float degrees);
        void transform(TransformationType a, Vector3f amount);

        Vector3f get_normal();
        Vector3f get_right();

    private:
        vector<BezierPatch*> patches;
        Transform<float,3,Affine> t;
        Vector3f normal, right;
};

#endif // BEZIER_MAIN_H
