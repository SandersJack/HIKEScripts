#include <iostream>
#include <vector>

void resolutionmm2() {
  TFile *f = new TFile("nominalsetup.root");
  f->cd("K2piSelection");
  //TH2F *h;
  TH2F *h = (TH2F *)gDirectory->Get("deltamassvsmomentum");
  TAxis *xaxis = h->GetXaxis();
  TAxis *yaxis = h->GetYaxis();
  //h->RebinY(5);
  //h->Draw();
  std::cout << h->GetNbinsX() << " " << h->GetNbinsY() << std::endl;
  /////// Setup dictionary for y bin
  double dict[201];
  double a = -0.01;
  for(int k{0}; k < 101; k++) {
    //std::cout << a << std::endl;
    dict[k] = a;
    a += (2e-4);
    //std::cout << k << std::endl;
  }

  double sigma[201] = {0};
  double sigmaerr[201] = {0};
  double energy[201] = {0};

  for(int i{0}; i < h->GetNbinsX(); i++) {
    TH1F *h1 = new TH1F("h1", "Distibution for each bin", 101, -0.01, 0.01);
    double bin[501];
    int sum{0};
    for(int j{0}; j < h->GetNbinsY(); j++) {
      //std::cout << xaxis->GetMinimumBin() << std::endl;
      //std::cout << yaxis->FindBin(-1) << std::endl;
      bin[j] = h->GetBinContent(i, j);
      std::cout << bin[j] << " " << j << " " << dict[j - 1] << std::endl;
      std::vector<int> values;
      for(int t{0}; t < bin[j]; t++) {
        values.push_back(dict[j - 1]);
        h1->Fill(dict[j - 1]);
        sum += 1;
      }

      //h1->Draw();
    }
    std::cout << sum << std::endl;
    if(sum > 500) {
      TF1 *G2 = new TF1("G2", "gaus", -0.002, 0.002);
      //h1->Fit("gaus");
      h1->Fit(G2, "R");
      // TF1 *fit = h1->GetFunction("gaus");
      //double stan = h1->GetFunction("gaus")->GetParameter(2);
      std::cout << i << std::endl;
      TF1 *fit = h1->GetFunction("G2");
      energy[i] = i - 1;
      sigma[i] = fit->GetParameter(2);
      //std::cout << fit->GetParameter(2) << std::endl;
      sigmaerr[i] = fit->GetParError(2);
      //gr1->SetPoint(gr1->GetN(), (i - 1), sig);
      //gr1->SetPointError(gr1->GetN(), (i - 1), sig)
      //if(i == 12) {
      //  h1->Draw();
      //  break;
      //}
    }
    //std::cout << h->GetBinContent(i) << std::endl;
    delete h1;
  }
  //for(int i{0}; i < h->GetNbinsX(); i++) {
  //  std::cout << sigma[i] << std::endl;
  //}
  TCanvas *c = new TCanvas("c", "c");
  c->SetLeftMargin(0.15);
  auto *gr1 = new TGraphErrors(h->GetNbinsX(), energy, sigma, 0, sigmaerr);
  TF1 *SiPM_f2 = new TF1("SiPM_f2", "sqrt([0]*[0] + (x*[1])**2)");
  SiPM_f2->SetParameters(3e-3, 1e-3);
  gr1->SetTitle("#sigma(m^{2}_{miss}) vs Momentum");
  gr1->GetYaxis()->SetTitle("#sigma(m^{2}_{miss})");
  gr1->GetXaxis()->SetTitle("True #pi_{+} Momentum [GeV]");
  //gr1->Fit("SiPM_f2");
  gr1->Draw("AP*");
}