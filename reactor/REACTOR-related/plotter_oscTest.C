{
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetOptStat("");

  gStyle->SetLabelFont(102,"");
  gStyle->SetLabelSize(0.06,"");
  gStyle->SetLabelFont(102,"xyz");
  gStyle->SetLabelSize(0.06,"xyz");
  gStyle->SetLabelOffset(0.001,"x");
  gStyle->SetLabelOffset(0.01,"y");

  gStyle->SetTitleFont(42,"xyz");
  gStyle->SetTitleFontSize(0.06);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetTitleOffset(1.05,"x");
  gStyle->SetTitleOffset(1.25,"y");

  gStyle->SetStripDecimals(kFALSE);

  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);

  gStyle->SetStatW(0.35);
  gStyle->SetStatH(0.25);

  //gStyle->SetTitleW(0.2);
  //gStyle->SetTitleH(0.2);

  gStyle->SetPadTickX(kTRUE);
  gStyle->SetPadTickY(kTRUE);

  gStyle->SetPalette(1);
  gStyle->SetNumberContours(99);

  gStyle->SetHistLineColor(3);
  gStyle->SetFrameLineColor(3);
  gStyle->SetFuncWidth(3);

  gStyle->SetStatFont(42);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  std::cout<<"starting"<<std::endl;

  //double PROSPECT[11]={};
  //double equal[11]={};
  //double u235[11]={};


  TFile f1("outputFigs.root");
  TFile f2("outputFigs2.root");
  TFile f3("outputFigs3.root");
  TFile f4("outputFigs4.root");
  TFile f5("outputFigs5.root");
  TFile f6("outputFigs6.root");
  TH1D* predDCo1b1 = (TH1D*)f1.Get("outPrediction[0]");
  TH1D* predDCo2b1 = (TH1D*)f2.Get("outPrediction[0]");
  TH1D* predDCo3b1 = (TH1D*)f3.Get("outPrediction[0]");
  TH1D* predDCo4b1 = (TH1D*)f4.Get("outPrediction[0]");
  TH1D* predDCo5b1 = (TH1D*)f5.Get("outPrediction[0]");
  TH1D* predDCo6b1 = (TH1D*)f6.Get("outPrediction[0]");

  TH1D* predDCo1b2 = (TH1D*)f1.Get("outPrediction2[0]");
  TH1D* predDCo2b2 = (TH1D*)f2.Get("outPrediction2[0]");
  TH1D* predDCo3b2 = (TH1D*)f3.Get("outPrediction2[0]");
  TH1D* predDCo4b2 = (TH1D*)f4.Get("outPrediction2[0]");
  TH1D* predDCo5b2 = (TH1D*)f5.Get("outPrediction2[0]");
  TH1D* predDCo6b2 = (TH1D*)f6.Get("outPrediction2[0]");

  TH1D* predDCo1b3 = (TH1D*)f1.Get("outPrediction3[0]");
  TH1D* predDCo2b3 = (TH1D*)f2.Get("outPrediction3[0]");
  TH1D* predDCo3b3 = (TH1D*)f3.Get("outPrediction3[0]");
  TH1D* predDCo4b3 = (TH1D*)f4.Get("outPrediction3[0]");
  TH1D* predDCo5b3 = (TH1D*)f5.Get("outPrediction3[0]");
  TH1D* predDCo6b3 = (TH1D*)f6.Get("outPrediction3[0]");

  TH1D* predDCo1b4 = (TH1D*)f1.Get("outPrediction4[0]");
  TH1D* predDCo2b4 = (TH1D*)f2.Get("outPrediction4[0]");
  TH1D* predDCo3b4 = (TH1D*)f3.Get("outPrediction4[0]");
  TH1D* predDCo4b4 = (TH1D*)f4.Get("outPrediction4[0]");
  TH1D* predDCo5b4 = (TH1D*)f5.Get("outPrediction4[0]");
  TH1D* predDCo6b4 = (TH1D*)f6.Get("outPrediction4[0]");

  predDCo1b1->Scale(predDCo1b4->Integral() / predDCo1b1->Integral());
  predDCo1b2->Scale(predDCo1b4->Integral() / predDCo1b2->Integral());
  predDCo1b3->Scale(predDCo1b4->Integral() / predDCo1b3->Integral());

  predDCo2b1->Scale(predDCo2b4->Integral() / predDCo2b1->Integral());
  predDCo2b2->Scale(predDCo2b4->Integral() / predDCo2b2->Integral());
  predDCo2b3->Scale(predDCo2b4->Integral() / predDCo2b3->Integral());

  predDCo3b1->Scale(predDCo3b4->Integral() / predDCo3b1->Integral());
  predDCo3b2->Scale(predDCo3b4->Integral() / predDCo3b2->Integral());
  predDCo3b3->Scale(predDCo3b4->Integral() / predDCo3b3->Integral());

  predDCo4b1->Scale(predDCo4b4->Integral() / predDCo4b1->Integral());
  predDCo4b2->Scale(predDCo4b4->Integral() / predDCo4b2->Integral());
  predDCo4b3->Scale(predDCo4b4->Integral() / predDCo4b3->Integral());

  predDCo5b1->Scale(predDCo5b4->Integral() / predDCo5b1->Integral());
  predDCo5b2->Scale(predDCo5b4->Integral() / predDCo5b2->Integral());
  predDCo5b3->Scale(predDCo5b4->Integral() / predDCo5b3->Integral());

  predDCo6b1->Scale(predDCo6b4->Integral() / predDCo6b1->Integral());
  predDCo6b2->Scale(predDCo6b4->Integral() / predDCo6b2->Integral());
  predDCo6b3->Scale(predDCo6b4->Integral() / predDCo6b3->Integral());

  TH1D* predDCo1b2_div = (TH1D*)predDCo1b2->Clone();
  TH1D* predDCo1b3_div = (TH1D*)predDCo1b3->Clone();
  TH1D* predDCo1b4_div = (TH1D*)predDCo1b4->Clone();
  predDCo1b2_div->Divide(predDCo1b1);
  predDCo1b3_div->Divide(predDCo1b1);
  predDCo1b4_div->Divide(predDCo1b1);

  TH1D* predDCo2b2_div = (TH1D*)predDCo2b2->Clone();
  TH1D* predDCo2b3_div = (TH1D*)predDCo2b3->Clone();
  TH1D* predDCo2b4_div = (TH1D*)predDCo2b4->Clone();
  predDCo2b2_div->Divide(predDCo2b1);
  predDCo2b3_div->Divide(predDCo2b1);
  predDCo2b4_div->Divide(predDCo2b1);

  TH1D* predDCo3b2_div = (TH1D*)predDCo3b2->Clone();
  TH1D* predDCo3b3_div = (TH1D*)predDCo3b3->Clone();
  TH1D* predDCo3b4_div = (TH1D*)predDCo3b4->Clone();
  predDCo3b2_div->Divide(predDCo3b1);
  predDCo3b3_div->Divide(predDCo3b1);
  predDCo3b4_div->Divide(predDCo3b1);

  TH1D* predDCo4b2_div = (TH1D*)predDCo4b2->Clone();
  TH1D* predDCo4b3_div = (TH1D*)predDCo4b3->Clone();
  TH1D* predDCo4b4_div = (TH1D*)predDCo4b4->Clone();
  predDCo4b2_div->Divide(predDCo4b1);
  predDCo4b3_div->Divide(predDCo4b1);
  predDCo4b4_div->Divide(predDCo4b1);

  TH1D* predDCo5b2_div = (TH1D*)predDCo5b2->Clone();
  TH1D* predDCo5b3_div = (TH1D*)predDCo5b3->Clone();
  TH1D* predDCo5b4_div = (TH1D*)predDCo5b4->Clone();
  predDCo5b2_div->Divide(predDCo5b1);
  predDCo5b3_div->Divide(predDCo5b1);
  predDCo5b4_div->Divide(predDCo5b1);

  TH1D* predDCo6b2_div = (TH1D*)predDCo6b2->Clone();
  TH1D* predDCo6b3_div = (TH1D*)predDCo6b3->Clone();
  TH1D* predDCo6b4_div = (TH1D*)predDCo6b4->Clone();
  predDCo6b2_div->Divide(predDCo6b1);
  predDCo6b3_div->Divide(predDCo6b1);
  predDCo6b4_div->Divide(predDCo6b1);

  predDCo1b1->SetLineColor(1);
  predDCo1b2->SetLineColor(2);
  predDCo1b3->SetLineColor(3);
  predDCo1b4->SetLineColor(4);

  predDCo2b1->SetLineColor(1);
  predDCo2b2->SetLineColor(2);
  predDCo2b3->SetLineColor(3);
  predDCo2b4->SetLineColor(4);

  predDCo3b1->SetLineColor(1);
  predDCo3b2->SetLineColor(2);
  predDCo3b3->SetLineColor(3);
  predDCo3b4->SetLineColor(4);

  predDCo4b1->SetLineColor(1);
  predDCo4b2->SetLineColor(2);
  predDCo4b3->SetLineColor(3);
  predDCo4b4->SetLineColor(4);

  predDCo5b1->SetLineColor(1);
  predDCo5b2->SetLineColor(2);
  predDCo5b3->SetLineColor(3);
  predDCo5b4->SetLineColor(4);

  predDCo6b1->SetLineColor(1);
  predDCo6b2->SetLineColor(2);
  predDCo6b3->SetLineColor(3);
  predDCo6b4->SetLineColor(4);

  predDCo1b2_div->SetLineColor(2);
  predDCo1b3_div->SetLineColor(3);
  predDCo1b4_div->SetLineColor(4);

  predDCo2b2_div->SetLineColor(2);
  predDCo2b3_div->SetLineColor(3);
  predDCo2b4_div->SetLineColor(4);

  predDCo3b2_div->SetLineColor(2);
  predDCo3b3_div->SetLineColor(3);
  predDCo3b4_div->SetLineColor(4);

  predDCo4b2_div->SetLineColor(2);
  predDCo4b3_div->SetLineColor(3);
  predDCo4b4_div->SetLineColor(4);

  predDCo5b2_div->SetLineColor(2);
  predDCo5b3_div->SetLineColor(3);
  predDCo5b4_div->SetLineColor(4);

  predDCo6b2_div->SetLineColor(2);
  predDCo6b3_div->SetLineColor(3);
  predDCo6b4_div->SetLineColor(4);

  TCanvas* c1 = new TCanvas();
  c1->Divide(2,2);
  c1->cd(1);
  predDCo1b1->Draw("hist");
  predDCo1b2->Draw("same");
  predDCo1b3->Draw("same");
  predDCo1b4->Draw("same");
  predDCo1b1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo1b1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo1b1,"baseline 7.9 #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo1b2,"baseline 20  #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo1b3,"baseline 400 #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo1b4,"baseline 500 #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c1->cd(2);
  predDCo2b1->Draw("hist");
  predDCo2b2->Draw("same");
  predDCo2b3->Draw("same");
  predDCo2b4->Draw("same");
  predDCo2b1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo2b1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo2b1,"baseline 7.9 #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo2b2,"baseline 20  #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo2b3,"baseline 400 #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo2b4,"baseline 500 #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c1->cd(3);
  predDCo3b1->Draw("hist");
  predDCo3b2->Draw("same");
  predDCo3b3->Draw("same");
  predDCo3b4->Draw("same");
  predDCo3b1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo3b1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo3b1,"baseline 7.9 #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo3b2,"baseline 20  #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo3b3,"baseline 400 #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo3b4,"baseline 500 #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c1->cd(4);
  predDCo4b1->Draw("hist");
  predDCo4b2->Draw("same");
  predDCo4b3->Draw("same");
  predDCo4b4->Draw("same");
  predDCo4b1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo4b1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo4b1,"baseline 7.9 #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo4b2,"baseline 20  #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo4b3,"baseline 400 #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo4b4,"baseline 500 #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();


  TCanvas* c2 = new TCanvas();
  c2->Divide(2,2);
  c2->cd(1);
  predDCo1b4_div->Draw("hist");
  predDCo1b3_div->Draw("same");
  predDCo1b2_div->Draw("same");
  predDCo1b2_div->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo1b2_div->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo1b2_div,"baseline 20  #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo1b3_div,"baseline 400 #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo1b4_div,"baseline 500 #Delta m^{2}_{41} 0.01 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c2->cd(2);
  predDCo2b4_div->Draw("hist");
  predDCo2b3_div->Draw("same");
  predDCo2b2_div->Draw("same");
  predDCo2b2_div->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo2b2_div->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo2b2_div,"baseline 20  #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo2b3_div,"baseline 400 #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo2b4_div,"baseline 500 #Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c2->cd(3);
  predDCo3b4_div->Draw("hist");
  predDCo3b3_div->Draw("same");
  predDCo3b2_div->Draw("same");
  predDCo3b2_div->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo3b2_div->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo3b2_div,"baseline 20  #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo3b3_div,"baseline 400 #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo3b4_div,"baseline 500 #Delta m^{2}_{41} 1 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c2->cd(4);
  predDCo4b4_div->Draw("hist");
  predDCo4b3_div->Draw("same");
  predDCo4b2_div->Draw("same");
  predDCo4b2_div->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDCo4b2_div->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDCo4b2_div,"baseline 20  #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo4b3_div,"baseline 400 #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDCo4b4_div,"baseline 500 #Delta m^{2}_{41} 10 sin^{2}2#theta_{14} 0.1","l");
  legend->Draw();

  c2->SaveAs("example_Jan21_2019.png");
}
