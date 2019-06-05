// Brady Lowe // lowebra2@isu.edu

#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TROOT.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>

#include "Math/SpecFunc.h"
#include "read_csv.h"
#include "load_files.h"

#include "pmt_analyzer_showermax.c"

#include <TMinuit.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TLine.h>

float showermax_lateral_scan_1a(int binWidth = 2){

	TCanvas* can = new TCanvas("can", "can");
	can->cd();
	gStyle->SetOptStat(10);
	gStyle->SetOptFit(1110);

	int sig, rms;
	float res;

	int pmt = 5;
	int hv = 1200;
	int pedestal = 1297;
	float onePEsig = GetSignalFromPmtAndHV(pmt, hv);

	const int num_runs = 13;
	int runs[num_runs];
	float pos[num_runs];
	float all_sig[num_runs];

	int i;
	i=0; runs[i] = 189; pos[i] = 0.;
	i=1; runs[i] = 190; pos[i] = pos[i-1] - 2.;
	i=2; runs[i] = 191; pos[i] = pos[i-1] - 3.;
	i=3; runs[i] = 192; pos[i] = pos[i-1] - 3.;
	i=4; runs[i] = 193; pos[i] = pos[i-1] - 4.;

	i=5; runs[i] = 195; pos[i] = pos[i-1] - 0.;
	i=6; runs[i] = 196; pos[i] = pos[i-1] - 3.;
	i=7; runs[i] = 197; pos[i] = pos[i-1] - 0.;
	i=8; runs[i] = 198; pos[i] = pos[i-1] - 3.;
	i=9; runs[i] = 199; pos[i] = pos[i-1] - 3.;
	i=10; runs[i] = 200; pos[i] = pos[i-1] - 2.;
	i=11; runs[i] = 201; pos[i] = pos[i-1] - 0.5;
	i=12; runs[i] = 202; pos[i] = pos[i-1] - 0.;

	for (int j = 0; j < num_points; j++) {
		all_sig[j] = pmt_analyzer_showermax(runs[j]);
	}
	
	TGraph *gr = new TGraph(num_runs, pos, all_sig);
	TCanvas* can = new TCanvas("can", "can", 200, 10, 600, 400);
	gr->Draw("AC*");

	
	return 0.0;
}

