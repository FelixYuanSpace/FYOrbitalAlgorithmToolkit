#ifndef OAT_PHYSICS_CONST_H
#define OAT_PHYSICS_CONST_H


#define LY_UNIT      1
#define METER_UNIT   2
#define AU_UNIT      3

#define SIM_USE_UNIT  METER_UNIT


namespace oat {
    #if (SIM_USE_UNIT == LY_UNIT)
    const double phy_locToSimUnit = 1.0;
    const double phy_simToLocUnit = 1.0;
    const double phy_meterToSimUnit = 1.0570008340246154637094605244851e-16;
    const double phy_kmToSimUnit = 1.0570008340246154637094605244851e-13;
    #endif

    #if (SIM_USE_UNIT == METER_UNIT)
    //ly is 9460730472580.8km
    //ly convert to sim unit need plus g_locToSimUnit
    const double phy_locToSimUnit = 9460730472580.8e3;
    //sim convert ly
    const double phy_simToLocUnit = 1.0570008340246154637094605244851e-16;
    //meter convert to sim
    const double phy_meterToSimUnit = 1.0;
    //km convert to sim plus phy_kmToSimUnit
    const double phy_kmToSimUnit = 1000.0;
    #endif
}


#endif