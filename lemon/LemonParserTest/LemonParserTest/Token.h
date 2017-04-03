#pragma once

struct SToken
{
    // position in source code.
    unsigned position = 0;
    // token value (always 0 for most tokens).
    double value;
};