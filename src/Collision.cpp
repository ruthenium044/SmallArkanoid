#include "Collision.h"

namespace collision
{
    bool intersect(const Circle& circle1, const Circle& circle2)
    {
        float distX = circle1.x - circle2.x;
        float distY = circle1.y - circle2.y;
        float distance = sqrt((distX * distX) + (distY * distY));
        if (distance <= circle1.r + circle2.r)
        {
            return true;
        }
        return false;
    }

    bool intersect(const SDL_FRect& square, const Circle& circle)
    {
        float x = circle.x;
        float y = circle.y;
        if (circle.x < square.x)
        {
            x = square.x;
        }
        else if (circle.x > square.x + square.w)
        {
            x = square.x + square.w;
        }

        if (circle.y < square.y)
        {
            y = square.y;
        }
        else if (circle.y > square.y + square.h)
        {
            y = square.y + square.h;
        }

        float distX = circle.x - x;
        float distY = circle.y - y;
        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= circle.r)
        {
            return true;
        }
        return false;
    }

    bool intersect(const Line& line, const Circle& circle)
    {
        if (intersect(line.a, circle) || intersect(line.b, circle))
        {
            return true;
        }

        float distX = line.a.x - line.b.x;
        float distY = line.a.y - line.b.y;
        float length = sqrt((distX * distX) + (distY * distY));

        float dot = (((circle.x - line.a.x) * (line.b.x - line.a.x)) +
            ((circle.y - line.a.y) * (line.b.y - line.a.y))) / pow(length, 2);

        float closestX = line.a.x + (dot * (line.b.x - line.a.x));
        float closestY = line.a.y + (dot * (line.b.y - line.a.y));

        Point point{ closestX, closestY };
        bool onSegment = intersect(line, point);
        if (!onSegment)
        {
            return false;
        }

        distX = closestX - circle.x;
        distY = closestY - circle.y;

        float distance = sqrt((distX * distX) + (distY * distY));

        if (distance <= circle.r)
        {
            return true;
        }
        return false;
    }

    bool intersect(const Point& point, const Circle& circle)
    {
        float distX = point.x - circle.x;
        float distY = point.y - circle.y;
        float distance = sqrt((distX * distX) + (distY * distY));
        if (distance <= circle.r) {
            return true;
        }
        return false;
    }

    bool intersect(const Line& line, const Point& point)
    {
        float dist1 = sqrt(pow(point.x - line.a.x, 2) + pow(point.y - line.a.y, 2));
        float dist2 = sqrt(pow(point.x - line.b.x, 2) + pow(point.y - line.b.y, 2));
        float lineLength = sqrt(pow(line.a.x - line.b.x, 2) + pow(line.a.y - line.b.y, 2));

        if (dist1 + dist2 >= lineLength && dist1 + dist2 <= lineLength)
        {
            return true;
        }
        return false;
    }
}