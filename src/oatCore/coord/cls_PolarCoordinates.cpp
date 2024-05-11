#include "cls_PolarCoordinates.h"
#include <math.h>

cls_PolarCoordinates::cls_PolarCoordinates(  )
{
	double_Radius = 0;
	double_Phi = 0;
	double_Theta = 0;
}

cls_PolarCoordinates::cls_PolarCoordinates( double in_double_Radius , double in_double_RadiusPhi , double in_double_RadiusTheta )
{
	double_Radius = in_double_Radius;
	double_Phi = in_double_RadiusPhi;
	double_Theta = in_double_RadiusTheta;
}

cls_PolarCoordinates::~cls_PolarCoordinates( )
{
}

cls_PolarCoordinates cls_PolarCoordinates::Convert( struct_RelativesInPolarCoordinates in_struct_RelativesInPolarCoordinates )
{
	double _double_R = in_struct_RelativesInPolarCoordinates.double_Radius;
	double _double_RadiusTheta = in_struct_RelativesInPolarCoordinates.double_Theta;
	double _double_RadiusPhi = in_struct_RelativesInPolarCoordinates.double_Phi;
	double _double_Theta = in_struct_RelativesInPolarCoordinates.double_Theta;
	double _double_Phi = in_struct_RelativesInPolarCoordinates.double_Phi;

	double _double_a = double_Radius * sin( double_Theta ) * cos( double_Phi ) - _double_R * sin( _double_RadiusTheta ) * cos( _double_RadiusPhi );
	double _double_b = double_Radius * sin( double_Theta ) * sin( double_Phi ) - _double_R * sin( _double_RadiusTheta ) * sin( _double_RadiusPhi );
	double _double_c = double_Radius * cos( double_Theta ) - _double_R * cos( _double_RadiusTheta );

	double _double_RadiusFinal = sqrt( _double_a * _double_a + _double_b * _double_b + _double_c * _double_c );
	double _double_PhiFinal = atan( _double_b / _double_a ) - _double_Phi;
	double _double_ThetaFinal = acos( _double_c / _double_RadiusFinal ) - _double_Theta;

	return cls_PolarCoordinates( _double_RadiusFinal , _double_PhiFinal , _double_ThetaFinal );
}
