#include "../include/DynamicObject.hpp"

void nearestIntersectionPlayers(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<DynamicObject*> players, Point2D& intersection)
{
    Point2D tmpIntersection;
    intersection.setPoint(2000, 2000);
    float   tmpDistance;
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
}

void nearestIntersectionFieldLimits(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    Point2D tmpIntersection;
    float   tmpDistance;
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
    if (intersectSegment(objectPosition, objectPosition.getDirection(positionClick), *fieldLimits[0], *fieldLimits[1], tmpIntersection)) {
        tmpDistance = objectPosition.getDistance(tmpIntersection);
        distance    = objectPosition.getDistance(intersection);
        if (tmpDistance < distance) {
            intersection = tmpIntersection;
        }
    }
}

void nearestIntersection(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<DynamicObject*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    nearestIntersectionPlayers(positionClick, currentObject, players, intersection);
    nearestIntersectionFieldLimits(positionClick, currentObject, fieldLimits, intersection);
    intersection.print();
}