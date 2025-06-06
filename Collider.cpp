#include <iostream> 
using namespace std;
#ifndef COLLIDER
#define COLLIDER

class Collider
{
    public:

    int x;
    int y;

    int xwidth;
    int ywidth;

    Collider(){

    }

    Collider(int xpos, int ypos, int xwidth, int ywidth){
        this -> x = xpos;
        this -> y = ypos;
        this -> xwidth = xwidth;
        this -> ywidth = ywidth;
    }

    void updatePosition(int newx, int newy){
        this -> x = newx;
        this -> y = newy;
    }

    bool checkCollition(Collider c){
        // if the corners of c are between 
        return (c.x <= x && c.x +c.xwidth >= x + xwidth) && (c.y <= y && c.y +c.ywidth >= y + ywidth);
    }
};
#endif