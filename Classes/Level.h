//
//  Level.h
//  platPro
//
//  Created by Falko Döhring on 07.05.15.
//
//

#ifndef __platPro__Level__
#define __platPro__Level__

#pragma once

#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class Level : public Node
{
public:
    
    TMXTiledMap *map;
    Point tileCoordinateToPosition(Point point);
    Point positionToTileCoordinate(Point point);
    vector<Rect> getCollisionTilesY(Point point1, Point point2, int direction);
    vector<Rect> getCollisionTilesX(Point point1, Point point2, Point point3, int direction);
    
    void loadMap(const char* name, cocos2d::Layer *layer);
    TMXTiledMap* getMap();
    
    Level();
    virtual ~Level();
    
private:
    
    
};

#endif /* defined(__platPro__Level__) */
