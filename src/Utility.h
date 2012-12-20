#pragma once


#define PI2 3.14159265359
#define CP_to_SF_ANGLE(angle) { return angle-PI2/2; }



class Utility
{
public:
	Utility(void);
	~Utility(void);

	static float RAD_to_DEG(float angle_rad) { return angle_rad * 180/PI; };
	static float DEG_to_RAD(float angle_deg) { return angle_deg * PI/180; };
	static float CP_to_SF_ANGLER(float angle) { return angle - PI2/2.f; }
	static float CP_to_SF_ANGLED(float angle) { return angle - 90.f; }
};

