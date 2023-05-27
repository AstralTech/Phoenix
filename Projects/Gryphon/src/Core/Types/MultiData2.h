#pragma once

// Things of the same type like Float2s

template <typename type>
class SameData2 {
public:
    union {
        struct {
            type a;
            type b;
        };
    
        struct {
            type x;
            type y;
        };
    };
public:
    SameData2() {}

    SameData2(type x, type y) {
        this->x = x;
        this->y = y;
    }

    SameData2(type v)  {
        this->x = v;
        this->y = v;
    }
};

typedef SameData2<float> Float2;
typedef SameData2<float> Vector2;

typedef SameData2<int> Int2;
typedef SameData2<int> Vector2Int;

// Things of different types

template <typename type1, typename type2>
class DiffData2 {
public:
    union {
        struct {
            type1 a;
            type2 b;
        };
    
        struct {
            type1 x;
            type2 y;
        };
    };
public:
    DiffData2() {}

    DiffData2(type1 x, type2 y) {
        this->x = x;
        this->y = y;
    }
};