#include <iostream>
#include <vector>

void resolution() {
  TFile *f = new TFile("nominalsetup.root");
  f->cd("K2piSelection");
  //TH2F *h;
  TH2F *h = (TH2F *)gDirectory->Get("deltamomentumvsmomentum");
  TAxis *xaxis = h->GetXaxis();
  TAxis *yaxis = h->GetYaxis();
  //h->RebinY(5);
  //h->Draw();
  std::cout << h->GetNbinsX() << " " << h->GetNbinsY() << std::endl;
  /////// Setup dictionary for y bin
  double dict[201];
  double a = -1;
  dict[0] = a;
  for(int k{0}; k < 201; k++) {
    //std::cout << a << std::endl;
    a += (0.01);
    dict[k] = a;

    //std::cout << k << std::endl;
  }

  std::vector<double> sigma;
  std::vector<double> sigmaerr;
  std::vector<double> energy;

  for(int i{0}; i < h->GetNbinsX(); i++) {
    TH1F *h1 = new TH1F("h1", "Distibution for each bin", 50, -0.01, 0.01);
    double bin[501];
    int sum{0};
    for(int j{0}; j < h->GetNbinsY(); j++) {
      //std::cout << xaxis->GetMinimumBin() << std::endl;
      //std::cout << yaxis->FindBin(-1) << std::endl;
      bin[j] = h->GetBinContent(i, j);
      std::cout << bin[j] << " " << j << " " << dict[j - 1] << std::endl;
      //std::cout << bin[j] << std::endl;
      std::vector<int> values;
      for(int t{0}; t < bin[j]; t++) {
        //std::cout << dict[j - 1] << std::endl;
        values.push_back(dict[j - 1]);
        h1->Fill(dict[j - 1] / ((i - 1)));
        sum += 1;
      }

      //h1->Draw();
    }
    std::cout << sum << std::endl;
    if(sum > 700) {
      TF1 *G2 = new TF1("G2", "gaus", -0.02, 0.02);
      h1->Fit(G2, "R");
      // TF1 *fit = h1->GetFunction("gaus");
      //double stan = h1->GetFunction("gaus")->GetParameter(2);
      std::cout << i << std::endl;
      TF1 *fit = h1->GetFunction("G2");
      energy.push_back((i - 1));
      sigma.push_back(fit->GetParameter(2));
      sigmaerr.push_back(fit->GetParError(2));

      //std::cout << fit->GetParameter(2) << std::endl;

      //gr1->SetPoint(gr1->GetN(), (i - 1), sig);
      //gr1->SetPointError(gr1->GetN(), (i - 1), sig)
      //if(i == 13) {
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

  int N = energy.size();
  double x[N], y[N], ye[N];
  for(int g{0}; g < N; g++) {
    x[g] = energy[g];
    y[g] = sigma[g];
    ye[g] = sigmaerr[g];
  }

  TCanvas *cc = new TCanvas("cc", "Canvas", 1200, 800);
  cc->SetLeftMargin(0.15);
  auto *gr1 = new TGraphErrors(N, x, y, 0, ye);
  //TF1 *SiPM_f2 = new TF1("SiPM_f2","[0]+x*[1]");
  TF1 *SiPM_f2 = new TF1("SiPM_f2", "sqrt([0]*[0] + (x*[1])**2)");
  SiPM_f2->SetParameters(3e-3, 1e-3);
  gr1->SetTitle("Reconstructed Momentum Error vs Momentum");
  //gr1->GetXaxis()->SetRangeUser(0, 75);
  //gr1->GetYaxis()->SetRangeUser(0, 0.01);
  gr1->GetYaxis()->SetTitle("#sigma(dp/p)");
  gr1->GetXaxis()->SetTitle("True Momentum [GeV]");
  gr1->Fit("SiPM_f2");
  gr1->Draw("AP*");
}