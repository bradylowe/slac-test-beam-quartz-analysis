// Brady Lowe // lowebra2@isu.edu

#include "pmt_analyzer_showermax.c"

float showermax_vertical_scan_1a(){

	TCanvas* can = new TCanvas("can", "can", 200, 10, 600, 400);
	can->cd();
	gStyle->SetOptStat(10);
	gStyle->SetOptFit(1110);

	float res;

	int pmt = 5;
	int hv;
	float sig;
	float onePEsig;
	int i;

	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle("ShowerMax1A Vertical Scan (5.5 GeV);Vertical Position of Beam w.r.t. Run 189 (cm);Detector Response (PEs)");

	// First vertical scan
	const int num_runs1 = 14;
	int runs1[num_runs1];
	float pos1[num_runs1];
	float npe1[num_runs1];
	i=0; runs1[i] = 189; pos1[i] = 0.;
	i=1; runs1[i] = 190; pos1[i] = pos1[i-1] - 2.;
	i=2; runs1[i] = 191; pos1[i] = pos1[i-1] - 3.;
	i=3; runs1[i] = 192; pos1[i] = pos1[i-1] - 3.;
	i=4; runs1[i] = 193; pos1[i] = pos1[i-1] - 4.;
	i=5; runs1[i] = 194; pos1[i] = pos1[i-1] - 0.;
	i=6; runs1[i] = 195; pos1[i] = pos1[i-1] - 0.;
	i=7; runs1[i] = 196; pos1[i] = pos1[i-1] - 3.;
	i=8; runs1[i] = 197; pos1[i] = pos1[i-1] - 0.;
	i=9; runs1[i] = 198; pos1[i] = pos1[i-1] - 3.;
	i=10; runs1[i] = 199; pos1[i] = pos1[i-1] - 3.;
	i=11; runs1[i] = 200; pos1[i] = pos1[i-1] - 2.;
	i=12; runs1[i] = 201; pos1[i] = pos1[i-1] - 0.5;
	i=13; runs1[i] = 202; pos1[i] = pos1[i-1] - 0.;

	for (int j = 0; j < num_runs1; j++) {
		hv = GetHvFromRun(runs1[j]);
		onePEsig = GetSignalFromPmtAndHV(pmt, hv);
		sig = GetSignalFromRun(runs1[j]);
		npe1[j] = ((float)(sig)) / onePEsig;
		//printf("%.1f, %.2f\n", pos1[j], npe1[j]);
	}
	
	TGraph* gr1 = new TGraph(num_runs1, pos1, npe1);
	gr1->SetMarkerColor(1);
	gr1->SetMarkerStyle(8);
	mg->Add(gr1);

	// Second vertical scan
	const int num_runs2 = 9;
	int runs2[num_runs2];
	float pos2[num_runs2];
	float npe2[num_runs2];
        i=0; runs2[i] = 205; pos2[i] = pos1[num_runs1 - 1];;
        i=1; runs2[i] = 206; pos2[i] = pos2[i-1] + 2.5;
        i=2; runs2[i] = 207; pos2[i] = pos2[i-1] + 0.;
        i=3; runs2[i] = 208; pos2[i] = pos2[i-1] + 3.;
        i=4; runs2[i] = 209; pos2[i] = pos2[i-1] + 3.;
        i=5; runs2[i] = 210; pos2[i] = pos2[i-1] + 4.;
        i=6; runs2[i] = 211; pos2[i] = pos2[i-1] + 3.;
        i=7; runs2[i] = 212; pos2[i] = pos2[i-1] + 3.;
        i=8; runs2[i] = 213; pos2[i] = pos2[i-1] + 2.;
	
        for (int j = 0; j < num_runs2; j++) {
                hv = GetHvFromRun(runs2[j]);
                onePEsig = GetSignalFromPmtAndHV(pmt, hv);
                sig = GetSignalFromRun(runs2[j]);
                npe2[j] = ((float)(sig)) / onePEsig;
                //printf("%.1f, %.2f\n", pos2[j], npe2[j]);
        }

        TGraph* gr2 = new TGraph(num_runs2, pos2, npe2);
	gr2->SetMarkerColor(2);
	gr2->SetMarkerStyle(8);
	mg->Add(gr2);

	// Third vertical scan
	const int num_runs3 = 8;
	int runs3[num_runs3];
	float pos3[num_runs3];
	float npe3[num_runs3];
        i=0; runs3[i] = 214; pos3[i] = pos2[num_runs2 - 1];
        i=1; runs3[i] = 215; pos3[i] = pos3[i-1] - 2.;
        i=2; runs3[i] = 216; pos3[i] = pos3[i-1] - 3.;
        i=3; runs3[i] = 217; pos3[i] = pos3[i-1] - 3.;
        i=4; runs3[i] = 218; pos3[i] = pos3[i-1] - 4.;
        i=5; runs3[i] = 219; pos3[i] = pos3[i-1] - 3.;
        i=6; runs3[i] = 220; pos3[i] = pos3[i-1] - 3.;
        i=7; runs3[i] = 221; pos3[i] = pos3[i-1] - 2.;
        for (int j = 0; j < num_runs3; j++) {
                hv = GetHvFromRun(runs3[j]);
                onePEsig = GetSignalFromPmtAndHV(pmt, hv);
                sig = GetSignalFromRun(runs3[j]);
                npe3[j] = ((float)(sig)) / onePEsig;
                //printf("%.1f, %.2f\n", pos3[j], npe3[j]);
        }

        TGraph* gr3 = new TGraph(num_runs3, pos3, npe3);
	gr3->SetMarkerColor(3);
	gr3->SetMarkerStyle(8);
	mg->Add(gr3);

	

	mg->Draw("AP");
	
	return 0.0;
}

