#ifndef BEZIER_MAIN_H
#define BEZIER_MAIN_H

#include "include.h"
#include "bezier-patch.h"
#include <sstream>

class BezierMain {
    public:
        // constructors
        BezierMain();

        void parsePatchfile(char* filename);
        void draw();


    private:
        vector<BezierPatch*> patches;
};

#endif // BEZIER_MAIN_H
