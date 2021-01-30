#ifndef AVIONICS_H
#define AVIONICS_H
#pragma once
#include "Maths.h"
#include "BaseComponent.h"
#include "Input.h"
#include "AircraftState.h"
#include "CP741.h"
namespace Scooter
{//begin namespace

class Avionics : public BaseComponent
{
public:
	Avionics(Input& input, AircraftState& state);
	~Avionics();
	virtual void zeroInit();
	virtual void coldInit();
	virtual void hotInit();
	virtual void airborneInit();

	void updateAvionics(double dt);
	inline void setYawDamperPower( bool power );
	inline bool getValidBombingSolution();

	inline CP741& getComputer();
private:

	//constants
	const double m_timeConstant = 4.5; //was 4.5
	const double m_baseGain = 2.5;

	inline double washoutFilter(double input, double dt);
	double m_x = 0.0;

	Input& m_input;
	AircraftState& m_state;
	CP741 m_bombingComputer;

	bool m_damperEnabled = false;
};

double Avionics::washoutFilter(double input, double dt)
{
	double sampleRatio = dt / m_timeConstant;
	m_x = clamp((1.0 - (sampleRatio)) * m_x + sampleRatio * input, -0.1,0.1);
	return input - m_x;
}

void Avionics::setYawDamperPower( bool power )
{
	m_damperEnabled = power;
}

bool Avionics::getValidBombingSolution()
{

}

CP741& Avionics::getComputer()
{
	return m_bombingComputer;
}

}//end namespace
#endif