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

float benchmark_compare_stacks_1b(int binWidth = 2){

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

	// 4 stacks
	index = 0;
	color = 7;
	run = 334;
	pedestal = GetPedestalFromRun(run);
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 335, 336, 337);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1B: Compare stacks");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw("same");
	if (false) {
		qdc[index]->Fit("gaus", "R+", "", sig - 1.0 * rms, sig + 1.0 * rms);
		qdc[index]->GetFunction("gaus")->SetLineColor(color);
		can->Update();
		stats[index] = (TPaveStats*)qdc[index]->FindObject("stats");
		stats[index]->SetX1NDC(0.65);
		stats[index]->SetX2NDC(0.90);
		stats[index]->SetY1NDC(0.9);
		stats[index]->SetY2NDC(0.6);
		stats[index]->SetTextColor(color);
		res = qdc[index]->GetFunction("gaus")->GetParameter(2) / qdc[index]->GetFunction("gaus")->GetParameter(1);
		stats[index]->AddText(Form("Sigma/Mean = %.3f", res));
		stats[index]->DrawClone();
	}

	// 3 stacks
	index = 1;
	color = 6;
	run = 325;
	pedestal = GetPedestalFromRun(run);
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 326, 327);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1B: Compare stacks");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw("same");
	if (false) {
		qdc[index]->Fit("gaus", "R+", "", sig - 1.0 * rms, sig + 1.0 * rms);
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
	}

        // 2 stacks
        index = 2;
        color = 4;
        run = 285;
        pedestal = GetPedestalFromRun(run);
        pmt = GetPmtFromRun(run);
        hv = GetHvFromRun(run);
        onePEsig = GetSignalFromPmtAndHV(pmt, hv);
        sig = GetSignalFromRun(run) / onePEsig;
        rms = GetSignalRmsFromRun(run) / onePEsig;
        qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 286, 287);
        qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1B: Compare stacks");
        qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
        qdc[index]->GetYaxis()->SetTitle("Counts");
        qdc[index]->Draw("same");
	if (false) {
        	qdc[index]->Fit("gaus", "R+", "", sig - 1.0 * rms, sig + 1.0 * rms);
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
	}

	// 1 stack
	index = 3;
	color = 2;
	run = 271;
	pedestal = GetPedestalFromRun(run);
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 273);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1B: Compare stacks");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw("same");
	if (false) {
		qdc[index]->Fit("gaus", "R+", "", sig - 1.0 * rms, sig + 1.0 * rms);
		qdc[index]->GetFunction("gaus")->SetLineColor(color);
		can->Update();
		stats[index] = (TPaveStats*)qdc[index]->FindObject("stats");
		stats[index]->SetX1NDC(0.65);
		stats[index]->SetX2NDC(0.90);
		stats[index]->SetY1NDC(0.6);
		stats[index]->SetY2NDC(0.3);
		stats[index]->SetTextColor(color);
		res = qdc[index]->GetFunction("gaus")->GetParameter(2) / qdc[index]->GetFunction("gaus")->GetParameter(1);
		stats[index]->AddText(Form("Sigma/Mean = %.3f", res));
		stats[index]->DrawClone();
	}

	// 0 stacks
	index = 4;
	color = 1;
	run = 253;
	pedestal = GetPedestalFromRun(run);
	pmt = GetPmtFromRun(run);
	hv = GetHvFromRun(run);
	onePEsig = GetSignalFromPmtAndHV(pmt, hv);
	sig = GetSignalFromRun(run) / onePEsig;
	rms = GetSignalRmsFromRun(run) / onePEsig;
	qdc[index] = load_files_ped_corrected(pedestal, onePEsig, 1, binWidth, 2, run, 254, 255, 256, 267, 263, 264);
	qdc[index]->SetLineColor(color);
	qdc[index]->SetTitle("Benchmarking 1B: Compare stacks");
	qdc[index]->GetXaxis()->SetTitle("Photo-electrons");
	qdc[index]->GetYaxis()->SetTitle("Counts");
	qdc[index]->Draw("same");
	if (false) {
		qdc[index]->Fit("gaus", "R+", "", sig - 1.0 * rms, sig + 1.0 * rms);
		qdc[index]->GetFunction("gaus")->SetLineColor(color);
		can->Update();
		stats[index] = (TPaveStats*)qdc[index]->FindObject("stats");
		stats[index]->SetX1NDC(0.40);
		stats[index]->SetX2NDC(0.65);
		stats[index]->SetY1NDC(0.6);
		stats[index]->SetY2NDC(0.3);
		stats[index]->SetTextColor(color);
		res = qdc[index]->GetFunction("gaus")->GetParameter(2) / qdc[index]->GetFunction("gaus")->GetParameter(1);
		stats[index]->AddText(Form("Sigma/Mean = %.3f", res));
		stats[index]->DrawClone();
	}

	legend->AddEntry(qdc[4], "0 stacks (1350 Volts)", "l");
	legend->AddEntry(qdc[3], "1 stacks (1200 Volts)", "l");
	legend->AddEntry(qdc[2], "2 stacks (1150 Volts)", "l");
	legend->AddEntry(qdc[1], "3 stacks (1000 Volts)", "l");
	legend->AddEntry(qdc[0], "4 stacks (1000 Volts)", "l");
	legend->Draw();

	can->Modified();
	
	return 0.0;
}

