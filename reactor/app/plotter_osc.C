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

  gStyle->SetHistLineWidth(3);
  gStyle->SetFrameLineWidth(3);
  gStyle->SetFuncWidth(3);

  gStyle->SetStatFont(42);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);

  std::cout<<"starting"<<std::endl;

  TFile f1("outputFigVar1.root");
  TFile f2("outputFigVar2.root");
  TFile f3("outputFigVar3.root");
  TFile f4("outputFigVar4.root");
  TFile f5("outputFigVar5.root");
  TFile f6("outputFigVar6.root");
  TH1D* predDC0 = (TH1D*)f1.Get("outOsc[0]_dm0.100000_st0.100000");
  TH1D* predDC1 = (TH1D*)f2.Get("outOsc[0]_dm1.000000_st0.100000");
  TH1D* predDC2 = (TH1D*)f3.Get("outOsc[0]_dm10.000000_st0.100000");
  TH1D* predDC3 = (TH1D*)f4.Get("outOsc[0]_dm0.100000_st0.010000");
  TH1D* predDC4 = (TH1D*)f5.Get("outOsc[0]_dm1.000000_st0.010000");
  TH1D* predDC5 = (TH1D*)f6.Get("outOsc[0]_dm10.000000_st0.010000");

  TH1D* predDYB0 = (TH1D*)f1.Get("outOsc[1]_dm0.100000_st0.100000");
  TH1D* predDYB1 = (TH1D*)f2.Get("outOsc[1]_dm1.000000_st0.100000");
  TH1D* predDYB2 = (TH1D*)f3.Get("outOsc[1]_dm10.000000_st0.100000");
  TH1D* predDYB3 = (TH1D*)f4.Get("outOsc[1]_dm0.100000_st0.010000");
  TH1D* predDYB4 = (TH1D*)f5.Get("outOsc[1]_dm1.000000_st0.010000");
  TH1D* predDYB5 = (TH1D*)f6.Get("outOsc[1]_dm10.000000_st0.010000");

  TH1D* predRENO0 = (TH1D*)f1.Get("outOsc[2]_dm0.100000_st0.100000");
  TH1D* predRENO1 = (TH1D*)f2.Get("outOsc[2]_dm1.000000_st0.100000");
  TH1D* predRENO2 = (TH1D*)f3.Get("outOsc[2]_dm10.000000_st0.100000");
  TH1D* predRENO3 = (TH1D*)f4.Get("outOsc[2]_dm0.100000_st0.010000");
  TH1D* predRENO4 = (TH1D*)f5.Get("outOsc[2]_dm1.000000_st0.010000");
  TH1D* predRENO5 = (TH1D*)f6.Get("outOsc[2]_dm10.000000_st0.010000");

  TH1D* predNEOS0 = (TH1D*)f1.Get("outOsc[3]_dm0.100000_st0.100000");
  TH1D* predNEOS1 = (TH1D*)f2.Get("outOsc[3]_dm1.000000_st0.100000");
  TH1D* predNEOS2 = (TH1D*)f3.Get("outOsc[3]_dm10.000000_st0.100000");
  TH1D* predNEOS3 = (TH1D*)f4.Get("outOsc[3]_dm0.100000_st0.010000");
  TH1D* predNEOS4 = (TH1D*)f5.Get("outOsc[3]_dm1.000000_st0.010000");
  TH1D* predNEOS5 = (TH1D*)f6.Get("outOsc[3]_dm10.000000_st0.010000");

  predDC1->Scale(predDC0->Integral() / predDC1->Integral());
  predDC2->Scale(predDC0->Integral() / predDC2->Integral());
  predDC3->Scale(predDC0->Integral() / predDC3->Integral());
  predDC4->Scale(predDC0->Integral() / predDC4->Integral());
  predDC5->Scale(predDC0->Integral() / predDC5->Integral());

  predDYB1->Scale(predDYB0->Integral() / predDYB1->Integral());
  predDYB2->Scale(predDYB0->Integral() / predDYB2->Integral());
  predDYB3->Scale(predDYB0->Integral() / predDYB3->Integral());
  predDYB4->Scale(predDYB0->Integral() / predDYB4->Integral());
  predDYB5->Scale(predDYB0->Integral() / predDYB5->Integral());

  predRENO1->Scale(predRENO0->Integral() / predRENO1->Integral());
  predRENO2->Scale(predRENO0->Integral() / predRENO2->Integral());
  predRENO3->Scale(predRENO0->Integral() / predRENO3->Integral());
  predRENO4->Scale(predRENO0->Integral() / predRENO4->Integral());
  predRENO5->Scale(predRENO0->Integral() / predRENO5->Integral());

  predNEOS1->Scale(predNEOS0->Integral() / predNEOS1->Integral());
  predNEOS2->Scale(predNEOS0->Integral() / predNEOS2->Integral());
  predNEOS3->Scale(predNEOS0->Integral() / predNEOS3->Integral());
  predNEOS4->Scale(predNEOS0->Integral() / predNEOS4->Integral());
  predNEOS5->Scale(predNEOS0->Integral() / predNEOS5->Integral());


  new TCanvas();
  predDC0->SetLineWidth(3);
  predDC0->SetLineColor(1);
  predDC1->SetLineWidth(3);
  predDC1->SetLineColor(2);
  predDC2->SetLineWidth(3);
  predDC2->SetLineColor(3);
  predDC3->SetLineWidth(3);
  predDC3->SetLineColor(4);
  predDC4->SetLineWidth(3);
  predDC4->SetLineColor(6);
  predDC5->SetLineWidth(3);
  predDC5->SetLineColor(8);

  predDC0->Draw("hist");
  predDC1->Draw("same");
  predDC2->Draw("same");
  predDC3->Draw("same");
  predDC4->Draw("same");
  predDC5->Draw("same");  
  predDC0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDC0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDC0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDC4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDC5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();

  new TCanvas();
  predDYB0->SetLineWidth(3);
  predDYB0->SetLineColor(1);
  predDYB1->SetLineWidth(3);
  predDYB1->SetLineColor(2);
  predDYB2->SetLineWidth(3);
  predDYB2->SetLineColor(3);
  predDYB3->SetLineWidth(3);
  predDYB3->SetLineColor(4);
  predDYB4->SetLineWidth(3);
  predDYB4->SetLineColor(6);
  predDYB5->SetLineWidth(3);
  predDYB5->SetLineColor(8);

  predDYB0->Draw("hist");
  predDYB1->Draw("same");
  predDYB2->Draw("same");
  predDYB3->Draw("same");
  predDYB4->Draw("same");
  predDYB5->Draw("same");
  predDYB0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDYB0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Daya Bay");
  legend->AddEntry(predDYB0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDYB4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDYB5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();

  new TCanvas();
  predRENO0->SetLineWidth(3);
  predRENO0->SetLineColor(1);
  predRENO1->SetLineWidth(3);
  predRENO1->SetLineColor(2);
  predRENO2->SetLineWidth(3);
  predRENO2->SetLineColor(3);
  predRENO3->SetLineWidth(3);
  predRENO3->SetLineColor(4);
  predRENO4->SetLineWidth(3);
  predRENO4->SetLineColor(6);
  predRENO5->SetLineWidth(3);
  predRENO5->SetLineColor(8);

  predRENO0->Draw("hist");
  predRENO1->Draw("same");
  predRENO2->Draw("same");
  predRENO3->Draw("same");
  predRENO4->Draw("same");
  predRENO5->Draw("same");
  predRENO0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predRENO0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("RENO");
  legend->AddEntry(predRENO0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predRENO4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predRENO5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();

  new TCanvas();
  predNEOS0->SetLineWidth(3);
  predNEOS0->SetLineColor(1);
  predNEOS1->SetLineWidth(3);
  predNEOS1->SetLineColor(2);
  predNEOS2->SetLineWidth(3);
  predNEOS2->SetLineColor(3);
  predNEOS3->SetLineWidth(3);
  predNEOS3->SetLineColor(4);
  predNEOS4->SetLineWidth(3);
  predNEOS4->SetLineColor(6);
  predNEOS5->SetLineWidth(3);
  predNEOS5->SetLineColor(8);

  predNEOS0->Draw("hist");
  predNEOS1->Draw("same");
  predNEOS2->Draw("same");
  predNEOS3->Draw("same");
  predNEOS4->Draw("same");
  predNEOS5->Draw("same");
  predNEOS0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predNEOS0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("NEOS");
  legend->AddEntry(predNEOS0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predNEOS4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predNEOS5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();
  
  TCanvas* cc1 = new TCanvas();
  cc1->Divide(2,2);
  cc1->cd(1);
  predDC0->SetLineWidth(3);
  predDC0->SetLineColor(1);
  predDC1->SetLineWidth(3);
  predDC1->SetLineColor(2);
  predDC2->SetLineWidth(3);
  predDC2->SetLineColor(3);
  predDC3->SetLineWidth(3);
  predDC3->SetLineColor(4);
  predDC4->SetLineWidth(3);
  predDC4->SetLineColor(6);
  predDC5->SetLineWidth(3);
  predDC5->SetLineColor(8);
  predDC0->Draw("hist");
  predDC1->Draw("same");
  predDC2->Draw("same");
  predDC3->Draw("same");
  predDC4->Draw("same");
  predDC5->Draw("same");
  predDC0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDC0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(predDC0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDC3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDC4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDC5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();
  cc1->cd(2);
  predDYB0->SetLineWidth(3);
  predDYB0->SetLineColor(1);
  predDYB1->SetLineWidth(3);
  predDYB1->SetLineColor(2);
  predDYB2->SetLineWidth(3);
  predDYB2->SetLineColor(3);
  predDYB3->SetLineWidth(3);
  predDYB3->SetLineColor(4);
  predDYB4->SetLineWidth(3);
  predDYB4->SetLineColor(6);
  predDYB5->SetLineWidth(3);
  predDYB5->SetLineColor(8);
  predDYB0->Draw("hist");
  predDYB1->Draw("same");
  predDYB2->Draw("same");
  predDYB3->Draw("same");
  predDYB4->Draw("same");
  predDYB5->Draw("same");
  predDYB0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predDYB0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Daya Bay");
  legend->AddEntry(predDYB0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predDYB3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDYB4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predDYB5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();
  cc1->cd(3);
  predRENO0->SetLineWidth(3);
  predRENO0->SetLineColor(1);
  predRENO1->SetLineWidth(3);
  predRENO1->SetLineColor(2);
  predRENO2->SetLineWidth(3);
  predRENO2->SetLineColor(3);
  predRENO3->SetLineWidth(3);
  predRENO3->SetLineColor(4);
  predRENO4->SetLineWidth(3);
  predRENO4->SetLineColor(6);
  predRENO5->SetLineWidth(3);
  predRENO5->SetLineColor(8);
  predRENO0->Draw("hist");
  predRENO1->Draw("same");
  predRENO2->Draw("same");
  predRENO3->Draw("same");
  predRENO4->Draw("same");
  predRENO5->Draw("same");
  predRENO0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predRENO0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("RENO");
  legend->AddEntry(predRENO0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predRENO3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predRENO4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predRENO5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();
  cc1->cd(4);
  predNEOS0->SetLineWidth(3);
  predNEOS0->SetLineColor(1);
  predNEOS1->SetLineWidth(3);
  predNEOS1->SetLineColor(2);
  predNEOS2->SetLineWidth(3);
  predNEOS2->SetLineColor(3);
  predNEOS3->SetLineWidth(3);
  predNEOS3->SetLineColor(4);
  predNEOS4->SetLineWidth(3);
  predNEOS4->SetLineColor(6);
  predNEOS5->SetLineWidth(3);
  predNEOS5->SetLineColor(8);
  predNEOS0->Draw("hist");
  predNEOS1->Draw("same");
  predNEOS2->Draw("same");
  predNEOS3->Draw("same");
  predNEOS4->Draw("same");
  predNEOS5->Draw("same");
  predNEOS0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  predNEOS0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("NEOS");
  legend->AddEntry(predNEOS0,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS1,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS2,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.1","l");
  legend->AddEntry(predNEOS3,"#Delta m^{2}_{41} 0.1 sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predNEOS4,"#Delta m^{2}_{41} 1   sin^{2}2#theta_{14} 0.01","l");
  legend->AddEntry(predNEOS5,"#Delta m^{2}_{41} 10  sin^{2}2#theta_{14} 0.01","l");
  legend->Draw();


  std::cout<<"start the contour "<<std::endl;
  double bin_x[50];
  double bin_y[50];
  for(int i=49;i>=0;i--){bin_x[49-i]=TMath::Power(10.,(-3.*i*2/100.));}
  for(int i=0;i<50;i++){bin_y[i]=TMath::Power(10,(-2 + 5.*i*2/100.));}

  double aa,bb,cc;
  TH2D* p1_CL = new TH2D("p1_CL","p1_CL",49,bin_x,49,bin_y);
  TH2D* p2_CL = new TH2D("p2_CL","p2_CL",49,bin_x,49,bin_y);
  TH2D* p3_CL = new TH2D("p3_CL","p3_CL",49,bin_x,49,bin_y);

  TH2D* hContour = new TH2D("","",49,bin_x,49,bin_y);

  ifstream inContour;
  inContour.open("result/scan2D.txt");
  while(! inContour.eof())
  {
      inContour>>aa>>bb>>cc;
      //double dM = 5 * TMath::Exp(-aa*0.1);
      //double dS = TMath::Exp(-bb*0.1);
      double dM = TMath::Power(10.,(-3.*aa*2/100.));
      double dS = TMath::Power(10,(-2 + 5.*bb*2/100.));
      //sin^{2}2#theta_{14}d::cout<<dM<<" "<<dS<<std::endl;
      //p1_CL->Fill(dS,dM,cc);
      //p2_CL->Fill(dS,dM,cc);
      //p3_CL->Fill(dS,dM,cc);
      p1_CL->SetBinContent(bb,aa,cc);
      p2_CL->SetBinContent(bb,aa,cc);
      p3_CL->SetBinContent(bb,aa,cc);
      hContour->SetBinContent(bb,aa, cc);
  }
 
  double conto[1];
  conto[0] = 1;
  p1_CL->SetContour(1,conto);
  p1_CL->SetLineWidth(3);

  double conto2[1];
  conto2[0] = 4;
  p2_CL->SetContour(1,conto2);
  p2_CL->SetLineWidth(3);
  p2_CL->SetLineColor(2);

  double conto3[1];
  conto3[0] = 9;
  p3_CL->SetContour(1,conto3);
  p3_CL->SetLineWidth(3);
  p3_CL->SetLineColor(4);

  new TCanvas();
  p1_CL->GetXaxis()->SetTitle("sin#theta_{s}");
  p1_CL->GetYaxis()->SetTitle("#Delta m^{2}_{s}");  
  p1_CL->Draw("cont3");
  p2_CL->Draw("cont3 same");
  p3_CL->Draw("cont3 same");

  new TCanvas();
  hContour->GetXaxis()->SetTitle("sin#theta_{s}");
  hContour->GetYaxis()->SetTitle("#Delta m^{2}_{s}");
  hContour->Draw("colz");

}
