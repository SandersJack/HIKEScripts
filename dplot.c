#include <iostream>
#include <vector>

void dplot() {
  TFile *f = new TFile("pi0_mm2_large2.root");
  f->cd("PnnK2piNormAnalysis");
  //TH2F *h;
  TH2F *h = (TH2F *)gDirectory->Get("deltamomentumvsmomentum");
  h->GetXaxis()->SetTitle("dp [GeV]");
  h->Draw("COLZ");
}
