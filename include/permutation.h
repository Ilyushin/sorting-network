//
// Created by Evgeny Ilyushin on 11/24/17.
//

#ifndef SORTINGNETWORK_PERMUTATION_H
#define SORTINGNETWORK_PERMUTATION_H

class Permutation {
private:
    int _left;
    int _right;
public:
    Permutation();
    Permutation(int left, int right);

    void setLeft(int value) { _left = value; };

    int getLeft() const { return _left; };

    void setRight(int value) { _right = value; };

    int getRight() const { return _right; };
};

#endif //SORTINGNETWORK_PERMUTATION_H
