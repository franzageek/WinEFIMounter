#ifndef CLI_HXX
#define CLI_HXX

typedef unsigned char u8;

namespace cli
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