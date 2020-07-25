#pragma once

enum Button {
    upArrow, downArrow, leftArrow, rightArrow,
    space,
    quit,
    f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
    rightSquareBracket, leftSquareBracket
};

template <typename T> 
struct vect {
    T x, y; 
};

template <typename T>
struct rect {
    T x, y, w, h;
};