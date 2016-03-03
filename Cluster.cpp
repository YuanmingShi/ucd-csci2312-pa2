#include <sstream>
#include <fstream>
#include <algorithm>
#include "Cluster.h"



namespace Clustering {

    LNode::LNode(const Point &p, LNodePtr n) : point(p) {
        point = p;     //new value
        next = n;           //next pointer
    }


    Cluster::Cluster() {
        __size = 0; //set the size to ini 0;

        __points = NULL; // set point to null
    }


    Cluster::Cluster(const Cluster &clu) : Cluster()      //copy constructor
    {
        for (int i = 0; i < clu.__size; i++) {
            add(clu[i]);
        }
    }

    Cluster &Cluster::operator=(const Cluster &cluster) {
        if (this == &cluster)
            return *this;

        else {
            while (__points != NULL) {
                LNodePtr cur;
                cur = __points;
                __points = __points->next;
                delete cur;
                __size = 0;
            }

            for (int i = 0; i < cluster.__size; i++) {
                add(cluster[i]);
            }
        }
        return *this;
    }

    Cluster::~Cluster()       //destructor
    {
        if (__points != NULL) {
            LNodePtr before = __points;
            LNodePtr now = NULL;

            while (before != NULL) {
                now = before->next;
                delete before;
                before = now;
            }
        }
    }

    int Cluster::getSize() const {
        return __size;        //return the size

    }

    void Cluster::add(const Point &point) {
        LNodePtr insertPtr = new LNode(point, NULL);
        LNodePtr curr = __points;
        LNodePtr prev = __points;

        if (__points == NULL) {
            __points = insertPtr;
            __size++;
            return;
        }
        else if (__points->next == NULL) {
            if (point < __points->point) {
                __points = insertPtr;
                insertPtr->next = prev;
                __size++;
                return;
            }
            else {
                __points->next = insertPtr;
                __size++;
                return;
            }
        }
        else {
            curr = curr->next;
            if (point < prev->point) {
                __points = insertPtr;
                insertPtr->next = prev;
                __size++;
                return;
            }
            while (curr != nullptr) {
                if (point < curr->point) {
                    prev->next = insertPtr;
                    insertPtr->next = curr;
                    __size++;
                    return;
                }
                curr = curr->next;
                prev = prev->next;
            }
            prev->next = insertPtr;
            __size++;

        }

    }

    const Point &Cluster::remove(const Point &point) {
        LNodePtr currPtr = __points;
        LNodePtr nextPtr = __points;
        if (__points == NULL)
            return point;
        else if (__points->point == point) {
            __points = __points->next;
            delete currPtr;
            __size--;
        }
        else {
            currPtr = __points;
            nextPtr = __points->next;
            while (nextPtr != NULL) {
                if (nextPtr->point == point) {
                    currPtr->next = nextPtr->next;
                    delete nextPtr;
                    __size--;
                    break;
                }
                currPtr = nextPtr;
                nextPtr = nextPtr->next;
            }
        }
        return point;
    }


    bool Cluster::contains(const Point &point) {
        LNodePtr cur = __points;
        while (cur != NULL) {
            if (cur->point == point)
                return true;
            cur = cur->next;
        }
        return false;
    }



}

