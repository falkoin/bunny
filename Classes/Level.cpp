//
//  Level.cpp
//  platPro
//
//  Created by Falko Döhring on 07.05.15.
//
//

#include "Level.h"
#include "Globals.h"

Level::Level()
{
}

Level::~Level()
{
    map->release();
}

void Level::loadMap(const char* mapname, cocos2d::Layer *layer)
{
    map = TMXTiledMap::create(mapname);
    map->retain();
//    auto lights = map->getLayer("Lights");
//    lights->setGlobalZOrder(14);
//    Size s = lights->getLayerSize();
//    int mapHeight = s.height-1;
//    for (int x = 0; x < s.width; ++x)
//    {
//        for (int y = 0; y < s.height; ++y)
//        {
//            Sprite *tile = lights->getTileAt(Point(x,mapHeight-y));
//            
//            if (tile != NULL)
//            {
//                auto light = Light::create();
//                light->retain();
//                light->setPosition(this->tileCoordinateToPosition(Point(x,y))+Point(8*SCALE_FACTOR,8*SCALE_FACTOR));
//                layer->addChild(light,999);
//                light->setGlobalZOrder(999);
//            }
//        }
//    }
}

TMXTiledMap* Level::getMap()
{
    return map;
}

Point Level::tileCoordinateToPosition(Point point)
{    
    int x = floor(point.x * map->getTileSize().width * SCALE_FACTOR);
    int y = floor(point.y * map->getTileSize().height * SCALE_FACTOR);
    
    return Point(x, y);
}

Point Level::positionToTileCoordinate(Point point)
{
    int x = floor(point.x / (map->getTileSize().width * SCALE_FACTOR));
    int y = floor(point.y / (map->getTileSize().height * SCALE_FACTOR));
    
    return Point(x, y);
}

vector<Rect> Level::getCollisionTilesX(Point minY, Point maxY, Point midY, int direction)
{
    vector<Rect> list;
    TMXLayer *walls = map->getLayer("walls");
    int mapheight = (int)map->getMapSize().height - 1;
    
    Sprite *tile = walls->getTileAt(Point(minY.x + direction, mapheight - minY.y));
    
    if (tile != NULL)
    {
        Rect tileRect = Rect();
        
        Point tmp = walls->getPositionAt(Point(minY.x + direction, mapheight - minY.y));
        tileRect.setRect((int)(tmp.x * SCALE_FACTOR), (int)(tmp.y * SCALE_FACTOR), (int)(map->getTileSize().width * SCALE_FACTOR), (int)(map->getTileSize().height * SCALE_FACTOR));
        list.push_back(tileRect);
    }
    tile = walls->getTileAt(Point(maxY.x + direction, mapheight - maxY.y));
    
    if (tile != NULL)
    {
        Rect tileRect = Rect();
        
        Point tmp = walls->getPositionAt(Point(maxY.x + direction, mapheight - maxY.y));
        tileRect.setRect((int)(tmp.x * SCALE_FACTOR), (int)(tmp.y * SCALE_FACTOR), (int)(map->getTileSize().width * SCALE_FACTOR), (int)(map->getTileSize().height * SCALE_FACTOR));
        list.push_back(tileRect);
    }
    tile = walls->getTileAt(Point(midY.x + direction, mapheight - midY.y));
    
    if (tile != NULL)
    {
        Rect tileRect = Rect();
        
        Point tmp = walls->getPositionAt(Point(midY.x + direction, mapheight - midY.y));
        tileRect.setRect((int)(tmp.x * SCALE_FACTOR), (int)(tmp.y * SCALE_FACTOR), (int)(map->getTileSize().width * SCALE_FACTOR), (int)(map->getTileSize().height * SCALE_FACTOR));
        list.push_back(tileRect);
    }
    
    return list;
}

vector<Rect> Level::getCollisionTilesY(Point minX, Point maxX, int direction)
{
    vector<Rect> list;
    TMXLayer *walls = map->getLayer("walls");
    int mapheight = (int)map->getMapSize().height - 1;
    
    Sprite *tile = walls->getTileAt(Point(minX.x, mapheight - (minX.y + direction)));
    
    if (tile != NULL)
    {
        Rect tileRect = Rect();
        Point tmp = walls->getPositionAt(Point((int)minX.x, mapheight - ((int)minX.y + direction)));
        tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);
        list.push_back(tileRect);
    }
    tile = walls->getTileAt(Point(maxX.x, mapheight - (maxX.y + direction)));
    
    if (tile != NULL)
    {
        Rect tileRect = Rect();
        Point tmp = walls->getPositionAt(Point((int)maxX.x, mapheight - ((int)maxX.y + direction)));
        tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);
        list.push_back(tileRect);
    }
    
    return list;
}