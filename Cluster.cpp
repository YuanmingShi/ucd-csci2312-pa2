#include <iostream>
#include <sstream>
#include <iomanip>



#include "cluster.h"

namespace Clustering
{

    LNode::LNode(const Point &p, LNodePtr n) : point (p)
    {
        point = p;
        next = n;
    }

    Cluster::Cluster()
    {
        __size = 0;
        __points = nullptr;

    }

    Cluster::Cluster(const Cluster &c) : Cluster()
    {
        for (int i = 0; i < c.__size; i++)
        {
            add(c[i]);
        }
    }

    //need
    Cluster& Cluster::operator=(const Cluster &c)
    {
        __points = nullptr;



        if (__size > 0)
        {
            __size = 0;
            LNodePtr curr= __points;
            LNodePtr prev;



            while (curr != nullptr)
            {
                prev = curr;
                curr = curr->next;

                delete prev;
            }

        }

        for (int i = 0; i < c.__size; ++i)
        {
            add(c[i]);
        }

        return *this;
    }


    Cluster::~Cluster()
    {

        LNodePtr currNode;
        while (__points != nullptr)
        {
            currNode = __points;
            __points = currNode -> next;

            delete currNode;

        }

    }


    // Getters
    int Cluster::getSize() const
    {
        return __size;

    }


    void Cluster::add(const Point &p)
    {

        if (__size == 0)
        {
            __points = new LNode(p, nullptr);
            __size++;
            return;

        }
        else
        {
            if (contains(p))
                return;

            LNodePtr next;
            LNodePtr prev;

            next = __points;
            prev = nullptr;


            while (next != nullptr)
            {
                if (p < next->point)
                {

                    if (prev == nullptr)
                    {

                        __points = new LNode(p, next);

                        __size++;

                        return;
                    }
                    else
                    {

                        prev->next = new LNode(p, next);

                        __size++;

                        return;
                    }
                }

                prev = next;
                next = next->next;

            }


            prev->next = new LNode(p, nullptr);

            __size++;
        }
    }


    const Point &Cluster::remove(const Point &p)
    {

        LNodePtr curr;
        LNodePtr before = nullptr;

        curr = __points;

        if (contains(p))
        {


            while (curr != nullptr)
            {
                if (curr->point == p)
                {
                    __points = curr->next;

                    delete curr;

                    __size--;

                    break;

                }
                else if (before != nullptr)
                {

                    before->next = curr->next;

                    delete curr;

                    __size--;

                    break;
                }


                before = curr;
                curr = curr->next;
            }
        }

        return p;
    }


    bool Cluster::contains(const Point &p)
    {
        LNodePtr curr = this -> __points;
        for ( ; curr != nullptr; curr = curr -> next)
        {
            if (curr -> point == p)
            {
                return true;
            }
        }

        return false;

    }

    // Overloaded operators

    // Members: Subscript
    const Point &Cluster::operator[](unsigned int index) const
    {

        LNodePtr curr = __points;

        for (int i = 0; i < index; i++ )
        {

            curr = curr -> next;
        }

        return curr -> point;

    }

    // Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &p)
    {
        add(p);

        return *this;
    }

    Cluster &Cluster::operator-=(const Point &p)
    {
        remove(p);
        return *this;
    }

    // Members: Compound assignment (Cluster argument)
    Cluster &Cluster::operator+=(const Cluster &c) // union
    {
        for (int i = 0; i < c.__size; i++)
        {
            add(c[i]);
        }


        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &c) // (asymmetric) difference
    {

        for (int i = 0; i < c.__size; i++)
        {

            remove(c[i]);


        }


        return *this;
    }



    // Friends: IO
    std::ostream &operator<<(std::ostream &o, const Cluster &c)
    {

        LNodePtr curr = c.__points;
        if (curr != NULL)
        {
            for (int i = 0; i < c.__size; i++)
            {
                o << &curr[i] << std::endl;

            }

        }

        return o;

    }



    std::istream &operator>>(std::istream &i, Cluster &c)
    {
        while (!i.eof())
        {

            Point p(1);
            std::string line;

            while (getline(i, line))
            {
                if (line.length() >0)
                {
                    std :: stringstream s (line);
                    s >> p;
                    c.add(p);
                }
            }
        }
        return i;



    }


    // Friends: Comparison
    bool operator==(const Cluster &c, const Cluster &c1)
    {
        bool equal = true;
        if (c.__size != c1.__size)
        {
            return false;
        }
        else if (c.__size == c1.__size)
        {
            return true;
        }
        while(c.__points != nullptr && c1.__points != nullptr)
        {
            if ( c.__points -> point != c1.__points -> point)
                equal = false;
            c.__points -> next = c.__points;
            c1.__points -> next = c1.__points;
        }
        return true;
    }


    bool operator!=(const Cluster &c, const Cluster &c1)
    {
        return !(c==c1);
    }

    // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &c, const Point &p)
    {
        Cluster newCluster(c);
        newCluster += p;
        return newCluster;

    }

    const Cluster operator-(const Cluster &c, const Point &p)
    {
        Cluster newCluster (c);
        newCluster -= p;
        return newCluster;
    }

    // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &c, const Cluster &p) // union
    {
        Cluster newCluster(c);
        newCluster += p;
        return newCluster;
    }

    const Cluster operator-(const Cluster &c, const Cluster &p) // (asymmetric) difference
    {
        Cluster newCluster (c);
        newCluster -= p;
        return newCluster;
    }


}