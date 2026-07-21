#ifndef FNAFONDS_DOOR_H
#define FNAFONDS_DOOR_H

#include <nds.h> // For u8 type

class Door {
    u8 state = 0;
    static constexpr char closed = 1 << 0;
    static constexpr char closed2 = 1 << 1;
    static constexpr char light = 1 << 2;

public:
    bool getClosed() { return (state & closed) != 0; }

};


#endif //FNAFONDS_DOOR_H