#include "./oat_physics_const.h"
#include "./orbitmodel.h"

namespace oat
{
    OrbitModel::OrbitModel()
    	:m_period(0.0)
		, m_boundingRadius(0.0)
		, m_beginTime(0.0)
		, m_endTime(0.0)
    {

    }

    OrbitModel::~OrbitModel()
    {

    }

    Vec3 OrbitModel::positionAtJD(double jd)
    {
        return Vec3(0,0,0);
    }

    Vec3 OrbitModel::velocityAtJD(double jd)
    {
        return Vec3(0,0,0);
    }

    Quat OrbitModel::quatAtJD(double jd)
    {
        return Quat(0,0,0,0);
    }

    void OrbitModel::sample(double curJD, int ptNum, std::map<double, Vec3>& mapTime2Position)
    {
		double dDT = getPeriod() / (double)ptNum;
		for (int i = -ptNum / 2; i<ptNum / 2; ++i)
		{
			double dJD = i*dDT + curJD;
			mapTime2Position[dJD] = positionAtJD(dJD) * phy_kmToSimUnit;
		}
    }
}