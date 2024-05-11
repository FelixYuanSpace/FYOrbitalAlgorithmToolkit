#pragma once
#define MeanAnomalyPercentBiasAllowed 0.00000000000001
struct struct_polarCoordination
{
	double double_radius; // polar coordination of radius, unit: meter
	double double_theta; // polar coordination of theta, unit: -

	struct_polarCoordination( )
	{
		double_radius = 149600000000;
		double_theta = 0;
	}
};


struct struct_ResultWithBias
{
	double double_EccentricAnomaly; // calculated EccentricAnomaly of Kepler equation 
	double double_BiasOfMeanAnomaly; // bias of MeanAnomaly : 100 % * (calculated Mean Anomaly - Mean Anomaly)/Mean Anomaly

	/*struct_ResultWithBias( )
	{
		double_EccentricAnomaly = 0;
		double_BiasOfMeanAnomaly = 0;
	}*/
};

class cls_orbit
{
	/*data members*/
	private:
	struct_polarCoordination stct_polarCoordination;

	private:
	double double_Period; // time period, unit : second
	double double_Eccentricity; // eccentricity
	double double_SemiMajorAxis; // semimajor axis, unit : meter

	/*constructor and deconstructor*/
	public:
	cls_orbit( );
	virtual ~cls_orbit( );

	/*function members*/
	public:
	/*
	function : PositionOfTime
	usage: calculate the radius and theta in polar coordination since perihelion with time.
	return : return radius and theta in struct_polarCoordination
	input : in_doudle_time, unit: second
	*/
	struct_polarCoordination PositionOfTime( double in_double_Time );

	private:
	struct_ResultWithBias KeplerEquationSlover( double in_double_MeanAnomaly , double in_double_Eccentricity, double in_double_MeanAnomalyPercentBiasAllowed );
	unsigned int factorial( unsigned int in_number );
};