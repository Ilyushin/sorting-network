//
// Created by Evgeny Ilyushin on 11/30/17.
//

#ifndef SORTINGNETWORK_POINT_H
#define SORTINGNETWORK_POINT_H


class Point {
private:
    float _coord[2];
    int _index;

public:
    Point();
    Point(float x, float y);

    void setX(float x){_coord[0] = x};
    void setY(float y){_coord[1] = y};

    float getX(){return _coord[0];};
    float getY(){return _coord[1];};

};


#endif //SORTINGNETWORK_POINT_H
