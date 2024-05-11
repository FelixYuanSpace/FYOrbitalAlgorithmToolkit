#include "cls_orbit.h"
#define _USE_MATH_DEFINES // use M_PI marco define in math.h
#include <math.h>

cls_orbit::cls_orbit( )
{
	/* The earth related constants is put into the default initialization */
	double_Period = 365.2564 * 24 * 3600;
	double_Eccentricity = 0.0167;
	double_SemiMajorAxis = 149600000000;
}

cls_orbit::~cls_orbit( )
{
}

struct_polarCoordination cls_orbit::PositionOfTime( double in_double_Time )
{
	/* step 1 : Compute the mean motion n = (2¦Ð radians)/P, where P is the period.*/
	double _double_MeanMotion = 2 * M_PI / double_Period;

	/* step 2: Compute the mean anomaly M = nt, where t is the time since perilhelion.*/
	double _double_Time = in_double_Time;
	while ( _double_Time >= double_Period )
	{
		_double_Time = _double_Time - double_Period;
	}
	double _double_MeanAnomaly = _double_MeanMotion * _double_Time;

	/* step 3: Compute the eccentric anomaly E by solving Kepler's equation:
	{M = E - epsilon * sin E}, where epsilon is the eccentricity.*/
	//double _double_EccentricAnomaly = KeplerEquationSlover( _double_MeanAnomaly , double_Eccentricity );
	struct_ResultWithBias _struct_ResultWithBias = KeplerEquationSlover( _double_MeanAnomaly , double_Eccentricity , MeanAnomalyPercentBiasAllowed );

	/* step 4: Compute the true anomaly theta by solving the equation:
	{( 1 - epsilon ) * tan^2 (theta/2) = ( 1 + epsilon )* tan^2 (E/2) */
	stct_polarCoordination.double_theta = 2 * atan( sqrt( ( 1 + double_Eccentricity ) / ( 1 - double_Eccentricity ) ) * tan( _struct_ResultWithBias.double_EccentricAnomaly / 2 ) );
	if ( stct_polarCoordination.double_theta < 0 )
	{
		stct_polarCoordination.double_theta = stct_polarCoordination.double_theta + 2 * M_PI;
	}


	/* step 5: Compute the heliocentric distance r:
	{r = a ( 1- epsilon * cos (E))}, where a is the semimajor axis.*/
	stct_polarCoordination.double_radius = double_SemiMajorAxis * ( 1 - double_Eccentricity * cos( _struct_ResultWithBias.double_EccentricAnomaly ) );

	return stct_polarCoordination;
}

struct_ResultWithBias cls_orbit::KeplerEquationSlover( double in_double_MeanAnomaly , double in_double_Eccentricity , double in_double_MeanAnomalyPercentBiasAllowed )
{
	/*
	M = E - epsilon * sin E
	E is from 0 to 2*M_PI
	*/
	//#define method1
	//#define method2
	#define method3 // Newton Dichotomy
	/*
	//#ifdef method1
	//double _double_EccentricAnomalyOld = 0;
	//_double_step_double_EccentricAnomaly = M_PI_4 / 10000000;
	//double _double_EccentricAnomalyNew = in_double_MeanAnomaly + in_double_Eccentricity * sin( _double_EccentricAnomalyOld );
	//double _double_EccentricAnomalyBiasAllowed = _double_step_double_EccentricAnomaly;

	//while ( fabs( _double_EccentricAnomalyNew - _double_EccentricAnomalyOld ) > _double_EccentricAnomalyBiasAllowed )
	//{
	//	_double_EccentricAnomalyOld = _double_EccentricAnomalyOld + _double_step_double_EccentricAnomaly;
	//	_double_EccentricAnomalyNew = in_double_MeanAnomaly + in_double_Eccentricity * sin( _double_EccentricAnomalyOld );
	//}

	//struct_ResultWithBias _struct_ResultWithBias = { _double_EccentricAnomalyNew , 100 * ( _double_EccentricAnomalyNew - double_Eccentricity * sin( _double_EccentricAnomalyNew ) - in_double_MeanAnomaly ) / in_double_MeanAnomaly };
	//return _struct_ResultWithBias;
	//#endif // method1

	//#ifdef method2
	//double _double_1 = in_double_MeanAnomaly / ( 1 - in_double_Eccentricity );
	//double _double_2 = in_double_Eccentricity * pow( in_double_MeanAnomaly , 3 ) / ( pow( 1 - in_double_Eccentricity , 4 ) * factorial( 3 ) );
	//double _double_3 = ( 9 * pow( in_double_Eccentricity , 2 ) + in_double_Eccentricity ) * pow( in_double_MeanAnomaly , 5 ) / ( pow( 1 - in_double_Eccentricity , 7 ) * factorial( 5 ) );
	//double _double_4 = ( 225 * pow( in_double_Eccentricity , 3 ) + 54 * pow( in_double_Eccentricity , 2 ) + in_double_Eccentricity ) * pow( in_double_MeanAnomaly , 7 ) / ( pow( 1 - in_double_Eccentricity , 10 ) * factorial( 7 ) );
	//double _double_5 = ( 11025 * pow( in_double_Eccentricity , 4 ) + 4131 * pow( in_double_Eccentricity , 3 ) + 243 * pow( in_double_Eccentricity , 2 ) + in_double_Eccentricity ) * pow( in_double_MeanAnomaly , 9 ) / ( pow( 1 - in_double_Eccentricity , 13 ) * factorial( 9 ) );

	//double _double_EccentricAnomaly = _double_1 + ( -_double_2 ) + _double_3 + ( -_double_4 ) + _double_5;
	//double _double_BiasOfMeanAnomaly = 100 * ( _double_EccentricAnomaly - double_Eccentricity * sin( _double_EccentricAnomaly ) - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
	//struct_ResultWithBias _struct_ResultWithBias = { _double_EccentricAnomaly , _double_BiasOfMeanAnomaly };
	//return _struct_ResultWithBias;
	//#endif // method2
	*/
	#ifdef method3
	double _double_EccentricAnomalyMin = 0;
	double _double_EccentricAnomalyMax = 2 * M_PI;
	double _double_EccentricAnomalyMiddle = M_PI;
	double _double_MeanAnomalyMin;
	double _double_MeanAnomalyMax;
	double _double_MeanAnomalyMiddle = _double_EccentricAnomalyMiddle - in_double_Eccentricity * sin( _double_EccentricAnomalyMiddle );
	double _double_BiasOfMeanAnomaly = 100 * fabs( _double_MeanAnomalyMiddle - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
	if ( 0 == in_double_MeanAnomaly )
	{
		_double_EccentricAnomalyMiddle = 0;
		_double_BiasOfMeanAnomaly = 0;
	}
	else
	{
		while ( _double_BiasOfMeanAnomaly > in_double_MeanAnomalyPercentBiasAllowed )
		{
			if ( in_double_MeanAnomaly > _double_MeanAnomalyMiddle )
			{
				_double_EccentricAnomalyMin = _double_EccentricAnomalyMiddle;
				_double_MeanAnomalyMin = _double_EccentricAnomalyMin - in_double_Eccentricity * sin( _double_EccentricAnomalyMin );
				_double_EccentricAnomalyMiddle = ( _double_EccentricAnomalyMin + _double_EccentricAnomalyMax ) / 2;
				double _double_MeanAnomalyMiddleTemp = _double_EccentricAnomalyMiddle - in_double_Eccentricity * sin( _double_EccentricAnomalyMiddle );
				if ( _double_MeanAnomalyMiddleTemp == _double_MeanAnomalyMiddle )
				{
					_double_BiasOfMeanAnomaly = 100 * fabs( _double_MeanAnomalyMiddle - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
					break;
				}
				else
				{
					_double_MeanAnomalyMiddle = _double_MeanAnomalyMiddleTemp;
				}
			}
			else if ( in_double_MeanAnomaly < _double_MeanAnomalyMiddle )
			{
				_double_EccentricAnomalyMax = _double_EccentricAnomalyMiddle;
				_double_MeanAnomalyMax = _double_EccentricAnomalyMax - in_double_Eccentricity * sin( _double_EccentricAnomalyMax );
				_double_EccentricAnomalyMiddle = ( _double_EccentricAnomalyMin + _double_EccentricAnomalyMax ) / 2;
				double _double_MeanAnomalyMiddleTemp = _double_EccentricAnomalyMiddle - in_double_Eccentricity * sin( _double_EccentricAnomalyMiddle );
				if ( _double_MeanAnomalyMiddleTemp == _double_MeanAnomalyMiddle )
				{
					_double_BiasOfMeanAnomaly = 100 * fabs( _double_MeanAnomalyMiddle - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
					break;
				}
				else
				{
					_double_MeanAnomalyMiddle = _double_MeanAnomalyMiddleTemp;
				}
			}
			else // the difference of in_double_MeanAnomaly and _double_MeanAnomalyMiddle less than current presicion
			{
				_double_BiasOfMeanAnomaly = 100 * fabs( _double_MeanAnomalyMiddle - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
				break;
			}
			_double_BiasOfMeanAnomaly = 100 * fabs( _double_MeanAnomalyMiddle - in_double_MeanAnomaly ) / in_double_MeanAnomaly;
		}
	}

	struct_ResultWithBias _struct_ResultWithBias = { _double_EccentricAnomalyMiddle , _double_BiasOfMeanAnomaly };
	return _struct_ResultWithBias;
	#endif // method3


}

unsigned int cls_orbit::factorial( unsigned int in_uint_number )
{
	unsigned int uint_result = in_uint_number;
	if ( 1 < in_uint_number )
	{
		uint_result = uint_result * factorial( in_uint_number - 1 );
	}
	return uint_result;
}
