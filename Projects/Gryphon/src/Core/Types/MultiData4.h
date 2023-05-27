#pragma once

// Things of the same type like Float3s

template <typename type>
class SameData4 {
public:
    union {    
        struct {
            type x;
            type y;
            type z;
            type w;
        };

        struct {
            type r;
            type g;
            type b;
            type a;
        };
    };
public:
    SameData4() {}

    SameData4(type x, type y, type z, type w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    SameData4(type v)  {
        this->x = v;
        this->y = v;
        this->z = v;
        this->w = v;
    }
};

typedef SameData4<float> Float4;
typedef SameData4<float> Vector4;

typedef SameData4<float> Quaternion;

typedef SameData4<int> Int4;
typedef SameData4<int> Vector4Int;

// Things of different types

template <typename type1, typename type2, typename type3, typename type4>
class DiffData4 {
public:
    union {
        struct {
            type1 x;
            type2 y;
            type3 z;
            type4 w;
        };
    
        struct {
            type1 r;
            type2 g;
            type3 b;
            type4 a;
        };
    };
public:
    DiffData4() {}

    DiffData4(type1 x, type2 y, type3 z, type4 w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

typedef DiffData4<int, int, int, float> Color;