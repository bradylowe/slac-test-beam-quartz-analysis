// Brady Lowe // lowebra2@isu.edu

#include <TMath.h>
#include "gainToSig.c"
#include "pmt5_gain.c"

float pmt5_signal(int voltage, int range = 1) {
	return gainToSig(pmt5_gain(voltage), 1.0, range);
}
