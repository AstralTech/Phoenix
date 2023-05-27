#pragma once

// Things of the same type like Float3s

template <typename type>
class SameData3 {
public:
    union {
        struct {
            type x;
            type y;
            type z;
        };

        struct {
            type r;
            type g;
            type b;
        };
    };
public:
    SameData3() {}

    SameData3(type x, type y, type z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    SameData3(type v)  {
        this->x = v;
        this->y = v;
        this->z = v;
    }
};

typedef SameData3<float> Float3;
typedef SameData3<float> Vector3;

typedef SameData3<int> Int3;
typedef SameData3<int> Vector3Int;

// Things of different types

template <typename type1, typename type2, typename type3>
class DiffData3 {
public:
    union {    
        struct {
            type1 x;
            type2 y;
            type3 z;
        };

        struct {
            type1 r;
            type2 g;
            type3 b;
        };
    };
public:
    DiffData3() {}

    DiffData3(type1 x, type2 y, type3 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};