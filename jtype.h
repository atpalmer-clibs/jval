#ifndef JTYPE_H
#define JTYPE_H


enum jtype {
    JTYPE_INTEGER = 1 << 0,
    JTYPE_NUMBER = 1 << 1,
    JTYPE_STRING = 1 << 2,
    JTYPE_ARRAY = 1 << 3,
    JTYPE_OBJECT = 1 << 4,
};


#endif
