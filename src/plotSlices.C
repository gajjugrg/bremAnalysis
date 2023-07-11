//Usage  : root 'plotSlices.C("inputfileName", "outputfileName")'
//example: root 'plotSlices.C("../outputfiles/bremDMG4_bias_3.4e-25.root", "../outputfiles/slicesDMG4_bias_e-15.root")' 
//

#include <TFile.h>
#include <TTree.h>


void plotSlices(const char* inputfilename, const char* outputFilename){
	TFile* file = new TFile(inputfilename, "read");
	TTree* ana = (TTree*)file->Get("brem");

	Double_t nEntries = ana->GetEntries();

	cout << "The root file has : "<< nEntries << " Entries" << endl;
	Int_t           TrackID;
	Double_t        fKineticEnergy;
	Double_t        fTrackLength_X0;
	Char_t          fProcess[16];
	// List of branches
	ana->SetBranchAddress("TrackID" , &TrackID);
	ana->SetBranchAddress("fKineticEnergy", &fKineticEnergy);
	ana->SetBranchAddress("fTrackLength_X0", &fTrackLength_X0);
	ana->SetBranchAddress("fProcess", &fProcess);

//	Double_t Energy[3] = {100, 300, 700};


	Double_t Energy[3] = {10, 30, 45};
	// Initialize the 1-D histogram for each slice of energy
	TH1D* slice0 = new TH1D("slice0", "; Depth in units of Radiation Length; Probability / Bin ", 100, 0, 10);
	slice0 -> SetLineColor(8);
	TH1D* slice1 = new TH1D("slice1", "; Depth in units of Radiation Length; Probability / Bin ", 100, 0, 10);
	slice1 -> SetLineColor(6);
	TH1D* slice2 = new TH1D("slice2", "; Depth in units of Radiation Length; Probability / Bin", 100, 0, 10);
	slice2 -> SetLineColor(4);
	
	// Filling the histograms
	for(Int_t i = 0; i < ana->GetEntries(); i ++){
		ana->GetEntry(i);
		if( TrackID != 1) continue;
		if(fKineticEnergy >= (Energy[0]*1000-10) && fKineticEnergy < (Energy[0]*1000+10)){slice0->Fill(fTrackLength_X0);}
		if(fKineticEnergy >= (Energy[1]*1000-10) && fKineticEnergy < (Energy[1]*1000+10)){slice1->Fill(fTrackLength_X0);}
		if(fKineticEnergy >= (Energy[2]*1000-10) && fKineticEnergy < (Energy[2]*1000+10)){slice2->Fill(fTrackLength_X0);}
	}
	auto c = new TCanvas("c","c");
	slice0->DrawNormalized("e1p");
	slice1->DrawNormalized("e1p same");
	slice2->DrawNormalized("e1p same");
	c->SetLogy(1);
	gStyle->SetOptStat(0); //this removes the Statbox
	auto legend = new TLegend();
	legend->SetHeader("Legend","C");
	legend->AddEntry(slice0, Form("%.f GeV", Energy[0]) ,"l");
	legend->AddEntry(slice1, Form("%.f GeV", Energy[1]) ,"l");
	legend->AddEntry(slice2, Form("%.f GeV", Energy[2]) ,"l");
	legend->Draw();
	TFile f(outputFilename,"recreate");
	slice0->Write();
	slice1->Write();
	slice2->Write();
}


