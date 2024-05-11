#pragma once

struct struct_RelativesInPolarCoordinates
{
	double double_Radius;
	double double_RadiusTheta;
	double double_RadiusPhi;
	double double_Phi;
	double double_Theta;
};

class cls_PolarCoordinates
{
	/* data members */
	private:
	double double_Radius;
	double double_Phi;
	double double_Theta;

	/*constructor and deconstructor*/
	public:
	cls_PolarCoordinates( );
	cls_PolarCoordinates(double in_double_Radius, double in_double_Phi, double in_double_Theta );
	virtual ~cls_PolarCoordinates( );

	/*function members*/
	public:
	cls_PolarCoordinates Convert( struct_RelativesInPolarCoordinates in_struct_RelativesInPolarCoordinates );
};