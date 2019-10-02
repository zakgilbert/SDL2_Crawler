
/**
*  Calc.c
*/

#include <SDL2/SDL.h>
#include "Calc.h"
#include "Header.h"

/**
 * Return the angle between two points in radians
 */
double get_radian_angle(int x_1, int y_1, int x_2, int y_2)
{
    typedef struct _point {
        int x;
        int y;
    } point;
    point p1 = { x_2, y_2 };
    point p2 = { x_1, y_1 };

    double delta_X = (double)(p1.x - p2.x);
    double delta_Y = (double)(p2.y - p1.y);
    double result  = atan2(delta_X, delta_Y);
    return (result * (180 / PI));
}

/**
 * Convert radian to degrees
 */
double get_degree_angle(double angle)
{
    double dif = 0.0f;
    if (angle < 0.0f) {
        dif = (abs(abs(angle) - 180.0f));
        dif += 180.0f;
    } else {
        dif = angle;
    }
    return dif;
}
