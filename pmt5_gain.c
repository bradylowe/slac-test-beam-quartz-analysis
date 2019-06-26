// Brady Lowe // lowebra2@isu.edu

#include <TMath.h>


float pmt5_gain(int voltage) {
	//return 27311.7 * TMath::Power(voltage / 7.60457 / 100.0, 7.60457);
	return 31320.5 * TMath::Power(voltage / 7.82176 / 100.0, 7.82176);
}
