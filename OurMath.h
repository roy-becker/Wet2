//
// Created by roybe on 06-Dec-22.
//

#ifndef UNTITLED_OURMATH_H
#define UNTITLED_OURMATH_H

#include <iostream>

template <class KEY>
KEY ourMax(KEY a, KEY b)
{
    if (b > a)
    {
        return b;
    }
    else
    {
        return a;
    }
}

template <class KEY>
KEY* ourMax(KEY* a, KEY* b)
{
    if (*b > *a)
    {
        return b;
    }
    else
    {
        return a;
    }
}

#endif //UNTITLED_OURMATH_H
