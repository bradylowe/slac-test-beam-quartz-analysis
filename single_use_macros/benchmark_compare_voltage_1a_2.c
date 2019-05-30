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

float benchmark_compare_voltage_1a_2(int binWidth = 8){

	TCanvas* can = new TCanvas("can", "can");
	can->cd();
	gStyle->SetOptStat(10);
	gStyle->SetOptFit(1110);
	int pedestal = 1297;
	int stacks = 0;
	int pmt, hv, sig, rms, index, color, run;
	float onePEsig, res;

	TH1F* qdc[5];
	TF1* fit[5];
	TPaveStats* stats[5];
	TLegend* legend = new TLegend(0.1, 0.7, 0.48, 0.9);
	legend->SetHeader("Voltage");

	// 1100
	index = 0;
	color = 1;
	run = 317;
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1A (5.5 GeV): 2 tungsten");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw();
	qdc[index]->Fit("gaus", "R+", "", sig - 2.0 * rms, sig + 2.0 * rms);
	qdc[index]->GetFunction("gaus")->SetLineColor(color);
	can->Update();
	stats[index] = (TPaveStats*)qdc[index]->FindObject("stats");
	stats[index]->SetX1NDC(0.15);
	stats[index]->SetX2NDC(0.40);
	stats[index]->SetY1NDC(0.9);
	stats[index]->SetY2NDC(0.6);
	stats[index]->SetTextColor(color);
	res = qdc[index]->GetFunction("gaus")->GetParameter(2) / qdc[index]->GetFunction("gaus")->GetParameter(1);
	stats[index]->AddText(Form("Sigma/Mean = %.3f", res));
	stats[index]->DrawClone();

	// 1000
	index = 1;
	color = 2;
	run = 318;
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 319, 320, 321, 322);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1A (5.5 GeV): 2 tungsten");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw("sames");
	qdc[index]->Fit("gaus", "R+", "", sig - 2.0 * rms, sig + 2.0 * rms);
	qdc[index]->GetFunction("gaus")->SetLineColor(color);
	can->Update();
	stats[index] = (TPaveStats*)qdc[index]->FindObject("stats");
	stats[index]->SetX1NDC(0.40);
	stats[index]->SetX2NDC(0.65);
	stats[index]->SetY1NDC(0.9);
	stats[index]->SetY2NDC(0.6);
	stats[index]->SetTextColor(color);
	res = qdc[index]->GetFunction("gaus")->GetParameter(2) / qdc[index]->GetFunction("gaus")->GetParameter(1);
	stats[index]->AddText(Form("Sigma/Mean = %.3f", res));
	stats[index]->DrawClone();

	legend->AddEntry(qdc[0], " 1100", "l");
	legend->AddEntry(qdc[1], " 1000", "l");
	legend->Draw();

	can->Modified();
	
	return 0.0;
}

