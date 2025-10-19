#ifndef UI_HXX
#define UI_HXX

typedef unsigned char u8;

namespace ui
{
    enum prompt
    {
        mount,
        unmount,
        clone,
        exit,
    };
    bool display_prompt(prompt type);
}

#endif