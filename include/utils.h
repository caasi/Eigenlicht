#ifndef __EIGENLICHT_UTILS_H__
#define __EIGENLICHT_UTILS_H__

#include <iostream>
#include <iomanip>

using namespace std;

#include <matrix4.h>
#include <vector3d.h>
#include <triangle3d.h>

using namespace irr::core;

ostream &operator<< (ostream &out, const matrix4 &m)
{
    out << "{" << endl;

    for (int i = 0; i < 16; ++i)
    {
        out << setw(10) << setfill(' ') << m[i];
        if (i % 4 != 3) out << ",";
        if (i % 4 == 3) out << endl;
    }

    out << "}";

    return out;
}

ostream &operator<< (ostream &out, const vector3df &v)
{
    return out << "{ "
               << setw(10) << setfill(' ') << v.X << ","
               << setw(10) << setfill(' ') << v.Y << ","
               << setw(10) << setfill(' ') << v.Z
               << " }";
}

ostream &operator<< (ostream &out, const triangle3df &t)
{
    return out << "{" << endl
               << "\t" << t.pointA << endl
               << "\t" << t.pointB << endl
               << "\t" << t.pointC << endl
               << "}";
}

#endif
