#include "../include/DynamicObject.hpp"

void nearestIntersectionPlayers(const Point2D& positionClick, DynamicObject& currentObject, std::vector<DynamicObject*> players)
{
    Point2D tmpIntersection(2000, 2000);
    Point2D intersection(2000, 2000);
    float   tmpDistance    = 2000;
    Point2D objectPosition = currentObject.getPosition();
    float   distance       = objectPosition.getDistance(intersection);
    for (const auto& player : players) {
        Point2D positionPlayer = player->getPosition();
        float   radius         = player->getRadius();
        if (!(objectPosition == positionPlayer)) {
            if (intersectCircle(positionPlayer, radius, objectPosition, objectPosition.getDirection(positionClick), tmpIntersection)) {
                tmpDistance = objectPosition.getDistance(tmpIntersection);
                distance    = objectPosition.getDistance(intersection);
                if (tmpDistance < distance) {
                    intersection = tmpIntersection;
                }
            }
        }
    }
    currentObject.setIntersectionPlayers(intersection);
}

void nearestIntersectionFieldLimits(const Point2D& positionClick, DynamicObject& currentObject, std::vector<Point2D*> fieldLimits)
{
    Point2D tmpIntersection(2000, 2000);
    float   tmpDistance = 2000;
    Point2D intersection(2000, 2000);
    Point2D objectPosition = currentObject.getPosition();
    float   distance       = objectPosition.getDistance(intersection);

    for (int i = 0; i < 4; i++) {
        if (intersectSegment(objectPosition, objectPosition.getDirection(positionClick), *fieldLimits[i % 4], *fieldLimits[(i + 1) % 4], tmpIntersection)) {
            tmpDistance = objectPosition.getDistance(tmpIntersection);
            distance    = objectPosition.getDistance(intersection);
            if (tmpDistance < distance) {
                intersection = tmpIntersection;
            }
        }
    }
    currentObject.setIntersectionFieldLimits(intersection);
}

void nearestIntersection(const Point2D& positionClick, DynamicObject& currentObject, std::vector<DynamicObject*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    //nearestIntersectionPlayers(positionClick, currentObject, players);
    nearestIntersectionFieldLimits(positionClick, currentObject, fieldLimits);

    float distancePlayers = currentObject.getIntersectionPlayers().getDistance(positionClick);
    //float distanceFieldLimits = currentObject.getIntersectionFieldLimits().getDistance(positionClick);

    //     if (distancePlayers < distanceFieldLimits) {
    //         intersection = currentObject.getIntersectionPlayers();
    //     }
    //     else {
    //         intersection = currentObject.getIntersectionFieldLimits();
    //     }
}

Point2D getNormal(Point2D intersection)
{
    Point2D normal;
    if (intersection.getX() == Game::xPadding) {
        normal.setPoint(1, 0);
    }
    else if (intersection.getX() == Game::WINDOW_WIDTH - Game::xPadding) {
        normal.setPoint(-1, 0);
    }
    else if (intersection.getY() == Game::yPadding) {
        normal.setPoint(0, 1);
    }
    else {
        normal.setPoint(0, -1);
    }
    return normal;
}

Point2D getReflection(Point2D intersection, Point2D direction)
{
    Point2D normal     = getNormal(intersection);
    Point2D reflection = -direction + normal * (dot(direction, normal) * 2);
    return reflection;
}