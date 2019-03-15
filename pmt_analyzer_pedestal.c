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

#include <TMinuit.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TAxis.h>
#include <TLine.h>


double poisson_peak_calculator(int n, double mu){
	double numerator = TMath::Exp(-mu) * TMath::Power(mu, n);
	double denominator = TMath::Factorial(n);
	return numerator / denominator;
}


// This function reads the PMT root file from a hard-coded directory and fits the distribution
// to a Poisson convoluted with some gaussians and an exponential.
float pmt_analyzer_pedestal(int runNum, float initialPed = -1.0, int low = 0, int high = 0, int run2 = 0, int run3 = 0, int run4 = 0, int run5 = 0, int run6 = 0, int run7 = 0, int run8 = 0, int run9 = 0, int run10 = 0){

	// Define histogram numbers
	Int_t binWidth = 1;
	const int MAX_BIN = 4095;
	int adc_range = 1;

	// Grab initial values from csv files or use defaults
	if (initialPed < 0.0) initialPed = (float)(GetPedestalFromRun(runNum));
	if (initialPed < 0.0) {
		if (runNum < 177) initialPed = 877.0;
		else initialPed = 1298.0;
	}
	if (low == 0) low = initialPed - 15.0;
	if (high == 0) high = initialPed + 15.0;

	// Define ADC channels used
	int chanUpstream = 2;
	int chanDownstream = 0;

        // Create histogram
        Int_t bins = MAX_BIN / binWidth + 1;
	TH1F* h_QDC = load_files(adc_range, binWidth, chanUpstream, runNum, run2, run3, run4, run5, run6, run7, run8, run9, run10); 
	Int_t nentries = h_QDC->GetEntries();
	if (nentries < 3) return -1.0;
	else printf("Total entries: %d\n", nentries);

	// If we are overflowing, just don't even run the fit
	if (high >= MAX_BIN) return -2.0; 

	// Define fitting function
	TF1 *ped_func=new TF1("ped_func", "gaus", low, initialPed + 120.0); 
	ped_func->SetLineColor(4); // Dark blue
	ped_func->SetNpx(2000);
	ped_func->SetLineWidth(2);
	ped_func->SetParName(0, "Norm0");
	ped_func->SetParName(1, "Q0");
	ped_func->SetParName(2, "S0");

	// Initialize the pedestal + rms
	ped_func->SetParameter(0, 2000.0);
	ped_func->SetParameter(1, initialPed);
	ped_func->SetParameter(2, 2.0);
	
	// Set bounds on parameters where necessary
	ped_func->SetParLimits(1, initialPed - 5.0, initialPed + 5.0);

	// Setup histogram for printing
        h_QDC->GetXaxis()->SetTitle("ADC channels");
        h_QDC->GetYaxis()->SetTitle("Counts (integral normalized)");
        h_QDC->SetTitle("Low-light PE fit");
	h_QDC->SetLineColor(1);
	h_QDC->SetMarkerSize(0.7);
	h_QDC->SetMarkerStyle(20);
	h_QDC->GetXaxis()->SetTitle("QDC channel");
	h_QDC->GetYaxis()->SetTitle("Normalized yield");
	h_QDC->GetXaxis()->SetRangeUser(low, high);
	
	// Create canvas and draw histogram
	TCanvas *can = new TCanvas("can","can");
	can->cd();
	gStyle->SetOptFit(1);
	TGaxis::SetMaxDigits(3);
	h_QDC->Draw("same");

	// Define results pointer 
	TFitResultPtr ped_res = h_QDC->Fit(ped_func, "RS", "", low, high);
	can->Update();

	// Create vector and grab return parameters
	Double_t ped_back[3];
	ped_func->GetParameters(ped_back);

	// Grab some stats info from the fit
	Double_t chi = ped_func->GetChisquare();
	Int_t ndf = ped_func->GetNDF();
	Int_t nfitpoints = ped_func->GetNumberFitPoints();

	// Get output values
	Double_t norm1out = ped_back[0];
	Double_t pedout = ped_back[1];
	Double_t pedrmsout = ped_back[2];
	Double_t norm1outerr = ped_func->GetParError(0);
	Double_t pedouterr = ped_func->GetParError(1);
	Double_t pedrmsouterr = ped_func->GetParError(2);

	// Grab the parameters for this run
	int pmt = GetPmtFromRun(runNum);
	int hv = GetHvFromRun(runNum);
	// Print out results and a copy of all inputs to check them
	printf("Run:  %d\n", runNum);
	printf("Range: %d, %d\n", low, high);
	printf("HV:  %d\n", hv);
	printf("PMT: %d\n", pmt);
	//printf("Detector:  %s\n", detector.c_str());
	//printf("Energy:  %.1f\n", energy);
	printf("Ped: %.5f +/- %.5f\n", pedout, pedrmsout);

//	ofstream myfile("pedestal_output.csv", ios::out | ios::app);
//	if (myfile.is_open()) {
//		myfile << Form("%d,%.2f,%.2f", runNum, pedout, pedrmsout) << endl;
//		myfile.close();
//	}
	
	return pedout;
}

