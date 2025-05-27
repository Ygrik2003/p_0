#include "overlay/overlay.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>

int main(int argc, const char** argv)
{
    auto main_overlay = overlay();
    assert(std::max(0, 1) == 1);
    return EXIT_SUCCESS;
}