#ifndef __EIGEN_UTILS_H__
#define __EIGEN_UTILS_H__

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

#endif
