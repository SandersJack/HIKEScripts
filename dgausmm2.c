#include <iostream>
#include <vector>

void dgausmm2() {
  TFile *f = new TFile("nominalsetup.root");
  f->cd("PnnK2piNormAnalysis");
  //TH2F *h;
  TH1F *h = (TH1F *)gDirectory->Get("deltamm2");
  double par[6];
  //TF1 *G1 = new TF1("G1", "gaus", -0.004, 0.004);
  TF1 *G2 = new TF1("G2", "gaus", -0.002, 0.002);

  //h->Fit(G1, "R");
  h->Fit(G2, "R");

  //G1->GetParameters(&par[0]);
  //G2->GetParameters(&par[3]);

  //TF1 *fy = new TF1("f", "gaus(0)+gaus(3)", -0.03, 0.03);
  //fy->SetParameters(par);
  //h->Fit(fy, "R");

  h->GetXaxis()->SetTitle("M_{#pi_{0}}^{2} [GeV^{2}/c^{4}]");
  h->Draw("SAME");
}
