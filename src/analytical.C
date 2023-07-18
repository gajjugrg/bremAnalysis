// Author: Gajendra Gurung
// UT at Arlington
// This is the function to plot the analytical data: 
// equation 22 from https://doi.org/10.1103/PhysRev.149.1248

Double_t Intensity(Double_t E_0, Double_t E, Double_t t){
    return (1/E_0)*(1/tgamma(4*t/3))*pow(log(E_0/E),4*t/3-1);
}
void analytical(){
    Int_t N = 20000;
    Double_t E_0 = 10 ; //Initial Energy of the initial electron shot 
//    Double_t E_i[3] = {, , };     //Energy slice 1 GeV
    Double_t E_i[3] = {1, 3, 5};  //Energy slice 10 GeV
//    Double_t E_i[3] = {10, 30, 45}; //Energy slice 100 GeV

    Double_t delta_t = 0.001; //Step in track length
    Double_t delta_E = 0.00001; //Step in Energy (for +- 100 MeV)
    Double_t t = 0.0;         //Initial Track length
    Double_t Prob;            //Place holder for probability

    // Initializing the histogram slices
    TH1F* slice[3];
    for(Int_t i = 0 ; i < 3 ; i++){
        TString name = Form("slice%d", i);
        slice[i] = new TH1F(name , "; Depth in units of Radiation Length; Probability / Bin", 100, 0, 10);
        slice[i] -> SetLineColor(i+1);
    }

    // Here g is for each energy value
    for (Int_t g = 0; g < 3; g++) {
            Double_t Ei = E_i[g] - 0.10;
            t = 0.0;
            Prob = 0.0;
            for (Int_t i = 0; i < N; i++) {
                Prob = Intensity(E_0, Ei, t);
                slice[g] -> Fill(t,Prob);
//                cout << "g; " << g << " t: " << t << " Ei: " << Ei << " Prob: " << Prob << endl;
                t = t + delta_t;
                Ei = Ei + delta_E;
            }
    }

    TCanvas* c = new TCanvas("c", "Track Length distribution slices at different energies");
    slice[0] -> DrawNormalized("hist");
    slice[1] -> DrawNormalized("hist same");
    slice[2] -> DrawNormalized("hist same");

    TFile f(Form("../outputfiles/slices/slicesAna_%.fGeV.root", E_0),"recreate");
    slice[0] -> Write();
    slice[1] -> Write();
    slice[2] -> Write();
}
