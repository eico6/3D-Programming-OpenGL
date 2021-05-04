#ifndef QUADTREE_H
#define QUADTREE_H

#include <unordered_map>
#include <list>
#include <vector>


namespace gsml
{
typedef std::pair<double,double> Point2D; //Our own Vector2D

template<class ID, class T>
class Quadtree
{
private:
    //The corner points that define the boundary of the quadtree
    Point2D nwCorner;
    Point2D neCorner;
    Point2D swCorner;
    Point2D seCorner;

    //Potential subtrees
    Quadtree* nwSubtree;
    Quadtree* neSubtree;
    Quadtree* swSubtree;
    Quadtree* seSubtree;

    //List that stores all the objects in this quad
    //Can be used to search for objects of class T or an object's ID.
    std::list<std::pair<ID,T>> mObjects;
    std::vector<T>mAllObjects;

    bool isLeaf() const;
    void traverseAll(std::vector<T>& allObjects);
public:
   Quadtree();
   Quadtree(const Point2D &nw, const Point2D &ne, const Point2D &sw, const Point2D & se);
   void init(const Point2D &nw, const Point2D &ne, const Point2D &sw, const Point2D & se);
   void subDivide(int n);
   void print() const;
   void printAll() const;
   Quadtree* insert(const Point2D& point, const ID& id, const T& object);
   Quadtree* find(const Point2D& p);
   const Quadtree* find(const Point2D& p) const;
   T& find(const ID& id);
   T& operator[] (ID id);

   // Jukser litt med disse iteratorene. Det er ikke ekte iteratorfunksjoner
   // for QuadTre klassen, men for en container av T-er
   typename std::vector<T>::iterator begin()
   {
       traverseAll(mAllObjects);
       return mAllObjects.begin();
   }
   typename std::vector<T>::iterator end()
   {
       return mAllObjects.end();
   }
};
}
#endif // QUADTREE_H
