#pragma once


#define PI2 3.14159265359
#define CP_to_SF_ANGLE(angle) { return angle-PI2/2; }
#define RAD2DEG 57.29577951307854999853275233034
#define DEG2RAD 0.01745329251994444444444444444444


class Utility
{
public:
	Utility(void);
	~Utility(void);

	static float RAD_to_DEG(float angle_rad) { return float(angle_rad * RAD2DEG); };
	static float DEG_to_RAD(float angle_deg) { return float(angle_deg * DEG2RAD); };
	static float CP_to_SF_ANGLER(float angle) { return float(angle - PI2/2.f); }
	static float CP_to_SF_ANGLED(float angle) { return float(angle - 90.f); }
};

