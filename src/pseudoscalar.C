void pseudoscalar(){
    
    Double_t E0 = 10; //Initial electron energy in GeV
    //Double_t Energy[3] = {.1, .3, .5}; //For 1 GeV
    Double_t Energy[3] = {1, 3, 5}; //For 10 GeV
    //Double_t Energy[3] = {10, 30, 45}; //for 100 GeV

    TH1F* Ana_slice[3];
    TFile* g = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slicesAna_%.fGeV.root", E0));
    Ana_slice[0] = (TH1F*)g -> Get("slice0"); Ana_slice[0] -> SetLineColor(7);
    Ana_slice[1] = (TH1F*)g -> Get("slice1"); Ana_slice[1] -> SetLineColor(7);
    Ana_slice[2] = (TH1F*)g -> Get("slice2"); Ana_slice[2] -> SetLineColor(7);

    TH1F* MC_slice[3];
    TFile* f = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_g4_%.fGeV.root", E0));
    MC_slice[0] = (TH1F*)f -> Get("slice0"); MC_slice[0] -> SetLineColor(9); MC_slice[0] -> Sumw2();
    MC_slice[1] = (TH1F*)f -> Get("slice1"); MC_slice[1] -> SetLineColor(9); MC_slice[1] -> Sumw2();
    MC_slice[2] = (TH1F*)f -> Get("slice2"); MC_slice[2] -> SetLineColor(9); MC_slice[2] -> Sumw2();

    TH1F* DMG4_e0_slice[3];
    TFile* i = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_%.fGeV_bias_e7.root", E0));
    DMG4_e0_slice[0] = (TH1F*)i -> Get("slice0"); DMG4_e0_slice[0] -> SetLineColor(2);
    DMG4_e0_slice[1] = (TH1F*)i -> Get("slice1"); DMG4_e0_slice[1] -> SetLineColor(2);
    DMG4_e0_slice[2] = (TH1F*)i -> Get("slice2"); DMG4_e0_slice[2] -> SetLineColor(2);

    TH1F* DMG4_e3_slice[3];
    TFile* h = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_%.fGeV_bias_e-15.root", E0));
    DMG4_e3_slice[0] = (TH1F*)h -> Get("slice0"); DMG4_e3_slice[0] -> SetLineColor(1);
    DMG4_e3_slice[1] = (TH1F*)h -> Get("slice1"); DMG4_e3_slice[1] -> SetLineColor(1);
    DMG4_e3_slice[2] = (TH1F*)h -> Get("slice2"); DMG4_e3_slice[2] -> SetLineColor(1);

    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(80);

    TCanvas* c = new TCanvas("c", Form("Ratio of Probability distribution at %.f GeV",Energy[0]));
    Ana_slice[0]->Scale(.1/Ana_slice[0]->Integral("width"));
    MC_slice[0]->Scale(.1/MC_slice[0]->Integral(), "width");
    DMG4_e0_slice[0]->Scale(.1/DMG4_e0_slice[0]->Integral(), "width");
    DMG4_e3_slice[0]->Scale(.1/DMG4_e3_slice[0]->Integral(), "width");


    Ana_slice[0]->Draw("hist");
    MC_slice[0]->Draw("e1p same");
    DMG4_e0_slice[0]->Draw("e1p same");
    DMG4_e3_slice[0]->Draw("e1p same");


    auto leg = new TLegend();
    leg->SetHeader("Legend","C");
    leg->AddEntry(Ana_slice[0],"Ana","le");
    leg->AddEntry(MC_slice[0],"G4","le");
    leg->AddEntry(DMG4_e0_slice[0],"DMG4 bias 1e7","le");
    leg->AddEntry(DMG4_e3_slice[0],"DMG4 bias 1e-15","le");
    leg->Draw();

    TCanvas* c1 = new TCanvas("c1", Form("Ratio of Probability distribution at %.f GeV",Energy[1]));
    Ana_slice[1]->Scale(.1/Ana_slice[1]->Integral("width"));
    MC_slice[1]->Scale(.1/MC_slice[1]->Integral(), "width");
    DMG4_e0_slice[1]->Scale(.1/DMG4_e0_slice[1]->Integral(), "width");
    DMG4_e3_slice[1]->Scale(.1/DMG4_e3_slice[1]->Integral(), "width");

    Ana_slice[1]->Draw("hist");
    MC_slice[1]->Draw("e1p same");
    DMG4_e0_slice[1]->Draw("e1p same");
    DMG4_e3_slice[1]->Draw("e1p same");

    auto leg1 = new TLegend();
    leg1->SetHeader("Legend","C");
    leg1->AddEntry(Ana_slice[1],"Ana","le");
    leg1->AddEntry(MC_slice[1],"G4","le");
    leg1->AddEntry(DMG4_e0_slice[1],"DMG4 bias 1e7","le");
    leg1->AddEntry(DMG4_e3_slice[1],"DMG4 bias 1e-15","le");
    leg1->Draw();

    TCanvas* c2 = new TCanvas("c2", Form("Ratio of Probability distribution at %.f GeV",Energy[2]));
    Ana_slice[2]->Scale(.1/Ana_slice[2]->Integral("width"));
    MC_slice[2]->Scale(.1/MC_slice[2]->Integral(), "width");
    DMG4_e0_slice[2]->Scale(.1/DMG4_e0_slice[2]->Integral(), "width");
    DMG4_e3_slice[2]->Scale(.1/DMG4_e3_slice[2]->Integral(), "width");


    Ana_slice[2]->Draw("hist");
    MC_slice[2]->Draw("same");
    DMG4_e0_slice[2]->Draw("e1p same");
    DMG4_e3_slice[2]->Draw("e1p same");

    auto leg2 = new TLegend();
    leg2->SetHeader("Legend","C");
    leg2->AddEntry(Ana_slice[2],"Ana","le");
    leg2->AddEntry(MC_slice[2],"G4","le");
    leg2->AddEntry(DMG4_e0_slice[2],"DMG4 bias 1e7","le");
    leg2->AddEntry(DMG4_e3_slice[2],"DMG4 bias 1e-15","le");
    leg2->Draw();

}
