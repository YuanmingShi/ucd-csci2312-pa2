// Define the function in the point.h

#include "Point.h"
#include <cmath> // for the pow,sqrt
#include <sstream>

namespace Clustering {

    unsigned int Point::__idGen = 0; //set gengerator to 0

    Point::Point(int NEWDIM)
    {
        __dim = NEWDIM;
        __values = new double[__dim];

        for(int i = 0; i < __dim; i++)
        {
            __values[i] = 0.00;
        }

        __id = __idGen;
        __idGen++;

    }


    Point::Point(int NEWDIM, double *NEWVAL)  //SELF CHECK
    {
            __dim = NEWDIM;
            __values = NEWVAL;
            __id = __idGen;
            __idGen++;
    }

    Point::Point(const Point &point)  //cpy ctor
    {
        __dim = point.__dim;
        __values = new double[__dim];

        for(int i = 0; i < __dim; i++)
        {
            __values[i] = point.__values[i];
        }

        __id = point.__id;
    }

    Point & Point::operator=(const Point &point) //overloaded operator=
    {
        if (this == &point) { return *this; }


        for (int i = 0; i < __dim; i++)
        { this->__values[i] = point.__values[i]; }
        return *this;

    }


    Point::~Point()  //dtor
    {

        delete[] __values;

    }


    // Accessors & mutators
    int Point::getId() const
    {
        return __id;
    }

    int Point::getDims() const  //mutators
    {
        return __dim;
    }

    void Point::setValue(int I, double Val)
    {
        __values[I] = Val;
    }


    double Point::getValue(int i) const
    {

        return __values[i];


    }

    double Point::distanceTo(const Point &point) const
    {

            double trans = 0.00;
            double totalDistan = 0.00;

        for (int i = 0; i < __dim; i++)
        {
            trans += (pow((__values[i] - point.__values[i]), 2));

        }
            totalDistan = sqrt(trans);

        return totalDistan;
    }



    Point &Point::operator*=(double val)
    {
            for(int i = 0; i < __dim; i++)
            {
                __values[i] *= val;
            }

        return *this;
    }// p *= 6; p.operator*=(6);


    Point &Point::operator/=(double val)
    {
        for(int i = 0; i < __dim; i++)
        {
            __values[i] /= val;
        }
    return *this;
    }


    const Point Point::operator*(double val) const
{
    Point point(*this);

    for(int i = 0; i < __dim; i++)
    {
        point[i] *= val;
    }

    return point;
}


    const Point Point::operator/(double divide) const
    {
        Point point(*this);

        for(int i = 0; i < __dim; i++)
        {
            point[i] = divide;
        }
        return point;
    }


    double &Point::operator[](int index)
    {
        return __values[index];
    }

    // Friends
     Point &operator+=(Point &left, const Point &right)
    {
        for(int i = 0; i < left.__dim; i++)
        {
            left.__values[i] += right.__values[i];
        }
    return left;
    }


     Point &operator-=(Point &left, const Point &right)
     {

        for(int i = 0; i < left.__dim; i++)
        {
            left.__values[i] -= right.__values[i];
        }

         return left;
     }

    const Point operator+(const Point &left, const Point &right)
    {
        Point point(left);

        point += right;

        return point;
    }

    const Point operator-(const Point &left, const Point &right)
    {
        Point point(left);

        point -= right;

        return point;
    }

     bool operator==(const Point &left, const Point &right)
     {
         bool get = true;

         if(left.__id != right.__id )
            get = false;

         else
         {
             for(int i = 0; i < left.__dim; i++)
             {
                 if(left.__values[i] != right.__values[i])
                     get = false;
             }
         }
         return get;
     }

    bool operator!=(const Point &left, const Point &right)
    {
            return (!(left == right));
    }

     bool operator<(const Point &left, const Point &right)
     {
         bool small =false;
         for(int i = 0; i < left.__dim; i++)
         {
             if(left.__values[i] < right.__values[i])
                 return true;

             if(left.__values[i] > right.__values[i])
                 return false;
         }
        return small;
     }

    bool operator>(const Point &left, const Point &right)
    {
        return operator < (right, left);
    }

     bool operator<=(const Point &left, const Point &right)
     {
        return !operator > (left, right);
     }

     bool operator>=(const Point &left, const Point &right)
    {
        return !operator < (left, right);
    }

    std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        for(int i = 0; i < point.__dim - 1; i++)
        {
            os << point.__values[i] << ".";
            os << point.__values[i];
        }

        return os;
    }


    std::istream &operator>>(std::istream &is, Point &point)
    {
        std:: string line;

        for( int i =0; i < point.__dim; i++)
        {
            getline(is, line, ',');
            std:: stringstream in(line);
            in >> point.__values[i];

        }
        return is;
    }

}
