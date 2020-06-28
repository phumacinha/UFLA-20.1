#ifndef CLIP_RECTANGLE_H
#define CLIP_RECTANGLE_H

#include "line.h"
#include <string>

class ClipRectangle
{
    friend std::ostream& operator << (std::ostream& os, const ClipRectangle& r);
    public:
        ClipRectangle() : mInitialized(false) {}
        ClipRectangle(double xmin, double xmax, double ymin, double ymax);
        void Set(double xmin, double xmax, double ymin, double ymax);
        Line* Clip(const Line& l);
        void Read(const std::string& prompt);
        bool Initialized() { return mInitialized; }
        double XMin() { return mXmin; }
        double XMax() { return mXmax; }
        double YMin() { return mYmin; }
        double YMax() { return mYmax; }
        static const int INSIDE = 0; // 0000 
        static const int LEFT = 1; // 0001 
        static const int RIGHT = 2; // 0010 
        static const int BOTTOM = 4; // 0100 
        static const int TOP = 8; // 1000

    private:
        bool Positive(double n) { return n > 0; }
        int PositionCode(const Point &P);
        double mXmin;
        double mXmax;
        double mYmin;
        double mYmax;
        bool mInitialized;
};

#endif
			

