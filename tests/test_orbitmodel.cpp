#include "orbitmodel_sgp4.h"
#include "OpenGLEarth.hpp"
#include <iostream>

int main(int argc, char **argv)
{
#ifdef USE_OPENGL_TEST
    initEarth(argc, argv);
#endif

    oat::OrbitModel_SGP4 model = oat::OrbitModel_SGP4(
        "1 25544U 98067A   20290.52835648  .00000867  00000-0  22898-4 0  9993",
        "2 25544  51.6443  92.0000 0001405  89.0000  271.0000 15.49300004250789",
        2459123.5, 2459124.5, 0.0006944444444444445);

    std::vector<oat::OrbitData> oribitData = model.getOrbitData();

    for (size_t i = 0; i < oribitData.size(); ++i)
    {
        std::cout << "jd: " << oribitData[i].jd << " position: " << oribitData[i].position << " velocity: " << oribitData[i].velocity << std::endl;
    }
    return 0;
}
