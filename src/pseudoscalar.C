void pseudoscalar(Double_t E0){
    Double_t Energy[3]; 
    Energy[0] = 0.3*E0;
    Energy[1] = 0.5*E0;
    Energy[2] = 0.7*E0;

    TH1F* ANA[3];
    TFile* g = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slicesANA_%.1fGeV.root", E0));
    ANA[0] = (TH1F*)g -> Get("slice0"); ANA[0] -> SetLineColor(7);
    ANA[1] = (TH1F*)g -> Get("slice1"); ANA[1] -> SetLineColor(7);
    ANA[2] = (TH1F*)g -> Get("slice2"); ANA[2] -> SetLineColor(7);

    TH1F* MC[3];
    TFile* f = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_g4_%.1fGeV.root", E0));
    MC[0] = (TH1F*)f -> Get("slice0"); MC[0] -> SetLineColor(9); MC[0] -> Sumw2();
    MC[1] = (TH1F*)f -> Get("slice1"); MC[1] -> SetLineColor(9); MC[1] -> Sumw2();
    MC[2] = (TH1F*)f -> Get("slice2"); MC[2] -> SetLineColor(9); MC[2] -> Sumw2();

    TH1F* DMG4_bias[3];
    TFile* i = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_vec_%.1fGeV_bias_1.root", E0));
    DMG4_bias[0] = (TH1F*)i -> Get("slice0"); DMG4_bias[0] -> SetLineColor(2);
    DMG4_bias[1] = (TH1F*)i -> Get("slice1"); DMG4_bias[1] -> SetLineColor(2);
    DMG4_bias[2] = (TH1F*)i -> Get("slice2"); DMG4_bias[2] -> SetLineColor(2);

    TH1F* DMG4_0[3];
    TFile* h = new TFile(Form("/Users/Gajju/bremAnalysis/outputfiles/slices/slices_vec_%.1fGeV_bias_1.root", E0));
    DMG4_0[0] = (TH1F*)h -> Get("slice0"); DMG4_0[0] -> SetLineColor(1);
    DMG4_0[1] = (TH1F*)h -> Get("slice1"); DMG4_0[1] -> SetLineColor(1);
    DMG4_0[2] = (TH1F*)h -> Get("slice2"); DMG4_0[2] -> SetLineColor(1);

    gStyle->SetOptStat(0);
    gStyle->SetLegendFont(80);

    // ************************** ---- First Canvas------- ************************** //

    TCanvas* c = new TCanvas("c", Form("Ratio of Probability distribution at %.1f GeV",Energy[0]));
    //Here we divide the TCanvas in two Pads
    TPad* a = new TPad("a", "This is pad a", 0.02, 0.25, 0.98, 0.98);
    TPad* b = new TPad("b", "This is pad b", 0.02, 0.02, 0.98, 0.25);
    a -> Draw(); // draw pad a
    b -> Draw(); // draw pad b
    a -> cd();   // move into pad a
    ANA[0]->Scale(.1/ANA[0]->Integral("width")); // normalize the histograms
    MC[0]->Scale(.1/MC[0]->Integral(), "width");
    DMG4_bias[0]->Scale(.1/DMG4_bias[0]->Integral(), "width");
    DMG4_0[0]->Scale(.1/DMG4_0[0]->Integral(), "width");

    // Plotting the histograms in Pad a
    ANA[0]->Draw("hist");
    MC[0]->Draw("e1p same");
    DMG4_bias[0]->Draw("e1p same");
    DMG4_0[0]->Draw("e1p same");

    // Input text on the plot
    TLatex* tx = new TLatex();
    tx->SetTextFont(82);
    tx->SetTextSize(0.04);
    tx->SetTextAlign(13);
    tx->DrawLatex(4.79, 0.027, Form("Initial e- energy: %.1f GeV", E0));
    tx->DrawLatex(5.14, 0.025, Form("Final e- energy: %.1f GeV", Energy[0]));
    // Adding legend
    auto leg = new TLegend();
    leg->SetHeader("Legend","C");
    leg->AddEntry(ANA[0],"ANA","le");
    leg->AddEntry(MC[0],"G4","le");
    leg->AddEntry(DMG4_bias[0],"DMG4 bias 1e7","le");
    leg->AddEntry(DMG4_0[0],"DMG4 bias 1","le");
    leg->Draw();

    // Moving into Pad b
    b -> cd();
    TH1F* Ana0 = (TH1F*)ANA[0] -> Clone("Ana0");
    TH1F* Dbias0 = (TH1F*)DMG4_bias[0] -> Clone("Dbias0");
    TH1F* DZero0 = (TH1F*)DMG4_0[0] -> Clone("DZero0");
    Ana0 -> Divide(MC[0]);
    Dbias0 -> Divide(MC[0]);
    DZero0 -> Divide(MC[0]);
    Ana0 -> Draw();
    Dbias0 -> Draw("ep same");
    DZero0 -> Draw("ep same");
    c -> Update();

    // ************************** ---- Second Canvas------- ************************** //

    TCanvas* c1 = new TCanvas("c1", Form("Ratio of Probability distribution at %.1f GeV",Energy[1]));
    TPad* padc = new TPad("padc", "This is pad c", 0.02, 0.25, 0.98, 0.98);
    TPad* d = new TPad("d", "This is pad d", 0.02, 0.02, 0.98, 0.25);
    padc -> Draw();
    d -> Draw();

    padc -> cd();
    ANA[1]->Scale(.1/ANA[1]->Integral("width"));
    MC[1]->Scale(.1/MC[1]->Integral(), "width");
    DMG4_bias[1]->Scale(.1/DMG4_bias[1]->Integral(), "width");
    DMG4_0[1]->Scale(.1/DMG4_0[1]->Integral(), "width");

    ANA[1]->Draw("hist");
    MC[1]->Draw("e1p same");
    DMG4_bias[1]->Draw("e1p same");
    DMG4_0[1]->Draw("e1p same");

    TLatex* tx1 = new TLatex();
    tx1->SetTextFont(82); 
    tx1->SetTextSize(0.04);
    tx1->SetTextAlign(13);  // Align at top

    tx1->DrawLatex(4.79, 0.04, Form("Initial e- energy: %.1f GeV", E0));
    tx1->DrawLatex(5.74, 0.035, Form("Final e- energy: %.1f GeV", Energy[1]));
    auto leg1 = new TLegend();
    leg1->SetHeader("Legend","C");
    leg1->AddEntry(ANA[1],"ANA","le");
    leg1->AddEntry(MC[1],"G4","le");
    leg1->AddEntry(DMG4_bias[1],"DMG4 bias 1e7","le");
    leg1->AddEntry(DMG4_0[1],"DMG4 bias 1","le");
    leg1->Draw();

    // Moving into Pad d
    d -> cd();
    TH1F* Ana1 = (TH1F*)ANA[1] -> Clone("Ana1");
    TH1F* Dbias1 = (TH1F*)DMG4_bias[1] -> Clone("Dbias1");
    TH1F* DZero1 = (TH1F*)DMG4_0[1] -> Clone("DZero1");
    Ana1 -> Divide(MC[1]);
    Dbias1 -> Divide(MC[1]);
    DZero1 -> Divide(MC[1]);
    Ana1 -> Draw();
    Dbias1 -> Draw("ep same");
    DZero1 -> Draw("ep same");
    c1 -> Update();

    /// ************************** ---- Third Canvas------- ************************** //

    TCanvas* c2 = new TCanvas("c2", Form("Ratio of Probability distribution at %.1f GeV",Energy[2]));
    TPad* pade = new TPad("pade", "This is pad e", 0.02, 0.25, 0.98, 0.98);
    TPad* padf = new TPad("padf", "This is pad f", 0.02, 0.02, 0.98, 0.25);
    pade -> Draw();
    padf -> Draw();
   
    pade -> cd();
    ANA[2]->Scale(.1/ANA[2]->Integral("width"));
    MC[2]->Scale(.1/MC[2]->Integral(), "width");
    DMG4_bias[2]->Scale(.1/DMG4_bias[2]->Integral(), "width");
    DMG4_0[2]->Scale(.1/DMG4_0[2]->Integral(), "width");

    ANA[2]->Draw("hist");
    MC[2]->Draw("same");
    DMG4_bias[2]->Draw("e1p same");
    DMG4_0[2]->Draw("e1p same");

    TLatex* tx2 = new TLatex();
    tx2->SetTextFont(82);  
    tx2->SetTextSize(0.04);
    tx2->SetTextAlign(13); 

    tx2->DrawLatex(5.79, 0.045, Form("Initial e- energy: %.1f GeV", E0));
    tx2->DrawLatex(5.74, 0.04, Form("Final e- energy: %.1f GeV", Energy[2]));

    auto leg2 = new TLegend();
    leg2->SetHeader("Legend","C");
    leg2->AddEntry(ANA[2],"ANA","le");
    leg2->AddEntry(MC[2],"G4","le");
    leg2->AddEntry(DMG4_bias[2],"DMG4 bias 1e7","le");
    leg2->AddEntry(DMG4_0[2],"DMG4 bias 1","le");
    leg2->Draw();

    padf -> cd();
    TH1F* Ana2 = (TH1F*)ANA[2] -> Clone("Ana2");
    TH1F* Dbias2 = (TH1F*)DMG4_bias[2] -> Clone("Dbias2");
    TH1F* DZero2 = (TH1F*)DMG4_0[2] -> Clone("DZero2");
    Ana2 -> Divide(MC[2]);
    Dbias2 -> Divide(MC[2]);
    DZero2 -> Divide(MC[2]);
    Ana2 -> Draw();
    Dbias2 -> Draw("ep same");
    DZero2 -> Draw("ep same");
    c2 -> Update();
}
