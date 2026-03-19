#ifndef CLI_HXX
#define CLI_HXX

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