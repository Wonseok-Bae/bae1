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

  std::cout<<"start the contour "<<std::endl;
  double bin_x[51];
  double bin_y[51];
  for(int i=50;i>=0;i--){bin_x[50-i]=TMath::Power(10.,(-3.*i*2/100.));}
  for(int i=0;i<51;i++){bin_y[i]=TMath::Power(10,(-2 + 5.*i*2/100.));}

  double aa,bb,cc;
  TH2D* p1_CL = new TH2D("p1_CL","p1_CL",50,bin_x,50,bin_y);
  TH2D* p2_CL = new TH2D("p2_CL","p2_CL",50,bin_x,50,bin_y);
  TH2D* p3_CL = new TH2D("p3_CL","p3_CL",50,bin_x,50,bin_y);

  TH2D* hContour = new TH2D("","",50,bin_x,50,bin_y);

  ifstream inContour;
  inContour.open("result/scan2Dnew_DYBNEOSPROSPECT_sterile+fission+escale.txt");

  ifstream inContourv;
  inContourv.open("result/scan2Dnew_DYBNEOSPROSPECT_sterile+fission+escale.txt");  

  double minv = 100000000;
  double mina, minb;
  while(! inContourv.eof())
  {
      inContourv>>aa>>bb>>cc;
      if(cc< minv) {minv = cc; mina = aa; minb = bb;}
  }

  std::cout<<"minimum value is "<<mina<<" "<<minb<<" "<<minv<<std::endl;

  while(! inContour.eof())
  {
      inContour>>aa>>bb>>cc;
      //double dM = 5 * TMath::Exp(-aa*0.1);
      //double dS = TMath::Exp(-bb*0.1);
      double dM = TMath::Power(10.,(-3.*aa*2/100.));
      double dS = TMath::Power(10,(-2 + 5.*bb*2/100.));
      //std::cout<<dM<<" "<<dS<<std::endl;
      //p1_CL->Fill(dS,dM,cc);
      //p2_CL->Fill(dS,dM,cc);
      //p3_CL->Fill(dS,dM,cc);
      p1_CL->SetBinContent(bb,50-aa,cc-minv);
      p2_CL->SetBinContent(bb,50-aa,cc-minv);
      p3_CL->SetBinContent(bb,50-aa,cc-minv);
      hContour->SetBinContent(bb,50-aa, cc-minv);
  }
 
  double conto[1];
  conto[0] = 25;
  p1_CL->SetContour(1,conto);
  p1_CL->SetLineWidth(3);
  p1_CL->SetLineColor(1);

  double conto2[1];
  conto2[0] = 49;
  p2_CL->SetContour(1,conto2);
  p2_CL->SetLineWidth(3);
  p2_CL->SetLineColor(2);

  double conto3[1];
  conto3[0] = 100;
  p3_CL->SetContour(1,conto3);
  p3_CL->SetLineWidth(3);
  p3_CL->SetLineColor(4);

  TCanvas* c1 = new TCanvas();
  p1_CL->GetXaxis()->SetTitle("sin#theta_{s}");
  p1_CL->GetYaxis()->SetTitle("#Delta m^{2}_{s}");  
  p1_CL->Draw("cont3");
  p2_CL->Draw("cont3 same");
  p3_CL->Draw("cont3 same");
  c1->SetLogy();
  c1->SetLogx();

  TCanvas* c2 = new TCanvas();
  hContour->GetXaxis()->SetTitle("sin#theta_{s}");
  hContour->GetYaxis()->SetTitle("#Delta m^{2}_{s}");
  hContour->Draw("colz");
  c2->SetLogy();
  c2->SetLogx();

  c1->SaveAs("test_plot1.png");
  c2->SaveAs("test_plot2.png");

}
