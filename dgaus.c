#include <iostream>
#include <vector>

void dgaus() {
  TFile *f = new TFile("pi0_mm2_large2.root");
  f->cd("PnnK2piNormAnalysis");
  //TH2F *h;
  TH1F *h = (TH1F *)gDirectory->Get("deltamomentum");
  double par[6];
  TF1 *G1 = new TF1("G1", "gaus", -0.2, 0.2);
  TF1 *G2 = new TF1("G2", "gaus", -1, 1);

  h->Fit(G1, "R");
  h->Fit(G2, "R");

  G1->GetParameters(&par[0]);
  G2->GetParameters(&par[3]);

  TF1 *fy = new TF1("f", "gaus(0)+gaus(3)", -1, 1);
  fy->SetParameters(par);
  h->Fit(fy, "R");
  h->GetXaxis()->SetTitle("(p_{Reco}-p_{True}) [GeV]");
  h->Draw();
}
