#include "quadtree.h"
#include <QDebug>
#include <iostream>

template<class ID, class T>
bool gsml::Quadtree<ID, T>::isLeaf() const
{
    return nwSubtree == nullptr && neSubtree == nullptr && swSubtree == nullptr && seSubtree == nullptr;
}

template<class ID, class T>
void gsml::Quadtree<ID, T>::traverseAll(std::vector<T> &allObjects)
{
    for(auto it = mObjects.begin(); it!=mObjects.end(); it++)
    {
        allObjects.push_back(it->second);
        if(nwSubtree) nwSubtree->traverseAll(allObjects);
        if(neSubtree) neSubtree->traverseAll(allObjects);
        if(swSubtree) swSubtree->traverseAll(allObjects);
        if(seSubtree) seSubtree->traverseAll(allObjects);
    }
}

template<class ID, class T>
gsml::Quadtree<ID, T>::Quadtree()
    : nwSubtree{nullptr}, neSubtree{nullptr}, swSubtree{nullptr}, seSubtree{nullptr}
{
    //
}

template<class ID, class T>
gsml::Quadtree<ID, T>::Quadtree
(const gsml::Point2D &nw,
 const gsml::Point2D &ne,
 const gsml::Point2D &sw,
 const gsml::Point2D &se)
    : nwCorner{nw}, neCorner{ne}, swCorner{sw}, seCorner{se}, nwSubtree{nullptr}, neSubtree{nullptr}, swSubtree{nullptr}, seSubtree{nullptr}
{
    //
}

template<class ID, class T>
void gsml::Quadtree<ID, T>::init
(const gsml::Point2D &nw,
 const gsml::Point2D &ne,
 const gsml::Point2D &sw,
 const gsml::Point2D &se)
{
    nwCorner = nw;
    neCorner = ne;
    swCorner = sw;
    seCorner = se;
}

template<class ID, class T>
void gsml::Quadtree<ID, T>::subDivide(int n)
{
    //this function is recursive where n is how many times the Quadtree shall be subdivided
    if(n>0)
    {
        gsml::Point2D north {(nwCorner.first+neCorner.first)/2, (nwCorner.second+neCorner.second)/2};
        gsml::Point2D south {(swCorner.first+seCorner.first)/2, (swCorner.second+seCorner.second)/2};
        gsml::Point2D east {(neCorner.first+seCorner.first)/2, (neCorner.second+seCorner.second)/2};
        gsml::Point2D west {(nwCorner.first+swCorner.first)/2, (nwCorner.second+swCorner.second)/2};
        gsml::Point2D center{(nwCorner.first+seCorner.first)/2, (nwCorner.second+seCorner.second)/2};

        //new Quadtree(nw,ne,sw,se)
        nwSubtree = new Quadtree(nwCorner, north, west, center);
        nwSubtree->subDivide(n-1);

        neSubtree = new Quadtree(north, neCorner, center, east);
        neSubtree->subDivide(n-1);

        swSubtree = new Quadtree(west, center, seCorner, south);
        swSubtree->subDivide(n-1);

        seSubtree = new Quadtree(center, east, south, seCorner);
        seSubtree->subDivide(n-1);
    }
}

template<class ID, class T>
void gsml::Quadtree<ID, T>::print() const
{
    Point2D center = Point2D{(nwCorner.first+seCorner.first)/2, (nwCorner.second+seCorner.second)/2};
    //qDebug() << "Center =(" << center.first << ", " << std::to_string(center.second) << ")\n";
    qDebug() << center.first << center.second;
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        qDebug() << it->first.c_str() << ", " << it->second->getName().c_str() << "\n";
    }
}

template<class ID, class T>
void gsml::Quadtree<ID, T>::printAll() const
{
    print();
        if (nwSubtree) nwSubtree->printAll();
        if (neSubtree) neSubtree->printAll();
        if (swSubtree) swSubtree->printAll();
        if (seSubtree) seSubtree->printAll();
}

template<class ID, class T>
gsml::Quadtree<ID,T> *gsml::Quadtree<ID, T>::insert(const gsml::Point2D &point, const ID &id, const T &gameObject)
{
    //This function is recursive and will loop until it finds a leaf to push the object on to.
    if(isLeaf())
    {
        mObjects.push_back(std::pair<ID,T>{id,gameObject});
    }
    else
    {
        Point2D center{(nwCorner.first+seCorner.first)/2, (nwCorner.second+seCorner.second)/2};

        //Check if object is within one of the two north subtree's boundaries
        if(point.second > center.second)
        {
            //Check if object is within upper northwest subtree's boundaries
            if(point.first < center.first)
                nwSubtree->insert(point, id, gameObject);
            //Object is within northeast subtree's boundaries
            else
                neSubtree->insert(point, id, gameObject);
        }
        //Object is within one of the two south subtree's boundaries
        else
        {
            //Check if object is within southwest subtree's boundaries
            if(point.first < center.first)
                swSubtree->insert(point, id, gameObject);
            //Object is within southeast subtree's boundaries
            else
                seSubtree->insert(point, id, gameObject);
        }
    }
}

template<class ID, class T>
gsml::Quadtree<ID,T> *gsml::Quadtree<ID, T>::find(const gsml::Point2D &p)
{
    //This function is recursive and will loop until it finds a leaf to return.
    if(isLeaf())
    {
        return this;
    }
    else
    {
        Point2D center{(nwCorner.first+seCorner.first)/2, (nwCorner.second+seCorner.second)/2};

        if(p.second > center.second)
        {
            if(p.first < center.first)
                nwSubtree->find(p);
            else
                neSubtree->find(p);
        }
        else
        {
            if(p.first < center.first)
               swSubtree->find(p);
            else
               seSubtree->find(p);
        }
    }
}
