// tmp_octavebands.cpp : Defines the exported functions for the static library.
//

#include "tmp_octavebands.h"

// This is an example of an exported variable
int ntmp_octavebands=0;

// This is an example of an exported function.
int fntmp_octavebands(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see tmp_octavebands.h for the class definition
Ctmp_octavebands::Ctmp_octavebands()
{
    return;
}
