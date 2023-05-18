#pragma once

template <typename type>
class Data2 {
public:
    type x;
    type y;
public:
    Data2() {}

    Data2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Data2(float v)  {
        this->x = v;
        this->y = v;
    }
};

typedef Data2<float> Float2;
typedef Data2<float> Vector2;

typedef Data2<int> Int2;
typedef Data2<int> Vector2Int;