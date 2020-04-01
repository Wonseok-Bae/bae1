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

  TFile f1("outputFigs.root");
  TFile f2("outputFigs2.root");
  TH1D* pred0t = (TH1D*)f1.Get("outPrediction[0]");
  TH1D* pred1t = (TH1D*)f1.Get("outPrediction[1]");
  TH1D* pred2t = (TH1D*)f1.Get("outPrediction[2]");
  TH1D* pred3t = (TH1D*)f1.Get("outPrediction[3]");
  TH1D* pred4t = (TH1D*)f1.Get("outPrediction[4]");
  TH1D* data0t = (TH1D*)f1.Get("outData[0]");
  TH1D* data1t = (TH1D*)f1.Get("outData[1]");
  TH1D* data2t = (TH1D*)f1.Get("outData[2]");
  TH1D* data3t = (TH1D*)f1.Get("outData[3]");
  TH1D* data4t = (TH1D*)f1.Get("outData[4]");
  TH1D* fit0t = (TH1D*)f2.Get("outFit[0]");
  TH1D* fit1t = (TH1D*)f2.Get("outFit[1]");
  TH1D* fit2t = (TH1D*)f2.Get("outFit[2]");
  TH1D* fit3t = (TH1D*)f2.Get("outFit[3]");
  TH1D* fit4t = (TH1D*)f2.Get("outFit[4]");

  TH1D* pred0 = new TH1D("","",pred0t->GetNbinsX(),pred0t->GetBinCenter(1),pred0t->GetBinCenter(pred0t->GetNbinsX()+1));
  TH1D* pred1 = new TH1D("","",pred1t->GetNbinsX(),pred1t->GetBinCenter(1),pred1t->GetBinCenter(pred1t->GetNbinsX()+1));
  TH1D* pred2 = new TH1D("","",pred2t->GetNbinsX(),pred2t->GetBinCenter(1),pred2t->GetBinCenter(pred2t->GetNbinsX()+1));
  TH1D* pred3 = new TH1D("","",pred3t->GetNbinsX(),pred3t->GetBinCenter(1),pred3t->GetBinCenter(pred3t->GetNbinsX()+1));
  TH1D* pred4 = new TH1D("","",pred4t->GetNbinsX(),pred4t->GetBinCenter(1),pred4t->GetBinCenter(pred4t->GetNbinsX()+1));
  TH1D* data0 = new TH1D("","",data0t->GetNbinsX(),data0t->GetBinCenter(1),data0t->GetBinCenter(data0t->GetNbinsX()+1));
  TH1D* data1 = new TH1D("","",data1t->GetNbinsX(),data1t->GetBinCenter(1),data1t->GetBinCenter(data1t->GetNbinsX()+1));
  TH1D* data2 = new TH1D("","",data2t->GetNbinsX(),data2t->GetBinCenter(1),data2t->GetBinCenter(data2t->GetNbinsX()+1));
  TH1D* data3 = new TH1D("","",data3t->GetNbinsX(),data3t->GetBinCenter(1),data3t->GetBinCenter(data3t->GetNbinsX()+1));  
  TH1D* data4 = new TH1D("","",data4t->GetNbinsX(),data4t->GetBinCenter(1),data4t->GetBinCenter(data4t->GetNbinsX()+1));
  TH1D* fit0 = new TH1D("","",fit0t->GetNbinsX(),fit0t->GetBinCenter(1),fit0t->GetBinCenter(fit0t->GetNbinsX()+1));
  TH1D* fit1 = new TH1D("","",fit1t->GetNbinsX(),fit1t->GetBinCenter(1),fit1t->GetBinCenter(fit1t->GetNbinsX()+1));
  TH1D* fit2 = new TH1D("","",fit2t->GetNbinsX(),fit2t->GetBinCenter(1),fit2t->GetBinCenter(fit2t->GetNbinsX()+1));
  TH1D* fit3 = new TH1D("","",fit3t->GetNbinsX(),fit3t->GetBinCenter(1),fit3t->GetBinCenter(fit3t->GetNbinsX()+1));
  TH1D* fit4 = new TH1D("","",fit4t->GetNbinsX(),fit4t->GetBinCenter(1),fit4t->GetBinCenter(fit4t->GetNbinsX()+1));

  for(Int_t i=0;i<pred0t->GetNbinsX();i++)
  {
     pred0->SetBinContent(i+1, pred0t->GetBinContent(i+1));
     pred1->SetBinContent(i+1, pred1t->GetBinContent(i+1));
     pred2->SetBinContent(i+1, pred2t->GetBinContent(i+1));
     pred3->SetBinContent(i+1, pred3t->GetBinContent(i+1));
     pred4->SetBinContent(i+1, pred4t->GetBinContent(i+1));
     data0->SetBinContent(i+1, data0t->GetBinContent(i+1));
     data1->SetBinContent(i+1, data1t->GetBinContent(i+1));
     data2->SetBinContent(i+1, data2t->GetBinContent(i+1));
     data3->SetBinContent(i+1, data3t->GetBinContent(i+1));
     data4->SetBinContent(i+1, data4t->GetBinContent(i+1));
     fit0->SetBinContent(i+1, fit0t->GetBinContent(i+1));
     fit1->SetBinContent(i+1, fit1t->GetBinContent(i+1));
     fit2->SetBinContent(i+1, fit2t->GetBinContent(i+1));
     fit3->SetBinContent(i+1, fit3t->GetBinContent(i+1));
     fit4->SetBinContent(i+1, fit4t->GetBinContent(i+1));
  }	  

  pred0->Scale(data0->Integral() / pred0->Integral());
  pred1->Scale(data1->Integral() / pred1->Integral());
  pred2->Scale(data2->Integral() / pred2->Integral());
  pred3->Scale(data3->Integral() / pred3->Integral());
  pred4->Scale(data4->Integral() / pred4->Integral());
  fit0->Scale(data0->Integral() / fit0->Integral());
  fit1->Scale(data1->Integral() / fit1->Integral());
  fit2->Scale(data2->Integral() / fit2->Integral());
  fit3->Scale(data3->Integral() / fit3->Integral());
  fit4->Scale(data4->Integral() / fit4->Integral());

  new TCanvas();
  pred0->SetLineWidth(3);
  pred0->SetLineColor(2);
  data0->SetLineWidth(3);
  data0->SetLineColor(1);  
  fit0->SetLineWidth(3);
  fit0->SetLineColor(4);
  pred0->Draw("hist");
  data0->Draw("ep same");
  fit0->Draw("same");
  pred0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  TLegend* legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(data0,"Data","l");
  legend->AddEntry(pred0,"Prediction","l");
  legend->AddEntry(fit0,"Best fit","l");
  legend->Draw();

  new TCanvas();
  pred1->SetLineWidth(3);
  pred1->SetLineColor(2);
  data1->SetLineWidth(3);
  data1->SetLineColor(1);
  fit1->SetLineWidth(3);
  fit1->SetLineColor(4);
  pred1->Draw("hist");
  data1->Draw("ep same");
  fit1->Draw("same");
  pred1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");  
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Daya Bay");
  legend->AddEntry(data1,"Data","l");
  legend->AddEntry(pred1,"Prediction","l");
  legend->AddEntry(fit1,"Best fit","l");
  legend->Draw();

  new TCanvas();
  pred2->SetLineWidth(3);
  pred2->SetLineColor(2);
  data2->SetLineWidth(3);
  data2->SetLineColor(1);
  fit2->SetLineWidth(3);
  fit2->SetLineColor(4);
  pred2->Draw("hist");
  data2->Draw("ep same");
  fit2->Draw("same");
  pred2->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred2->GetYaxis()->SetTitle("Events/ (0.25 MeV)");  
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("RENO");
  legend->AddEntry(data2,"Data","l");
  legend->AddEntry(pred2,"Prediction","l");
  legend->AddEntry(fit2,"Best fit","l");
  legend->Draw();

  new TCanvas();
  pred3->SetLineWidth(3);
  pred3->SetLineColor(2);
  data3->SetLineWidth(3);
  data3->SetLineColor(1);
  fit3->SetLineWidth(3);
  fit3->SetLineColor(4);
  pred3->Draw("hist");
  data3->Draw("ep same");
  fit3->Draw("same");  
  pred3->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred3->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("NEOS");
  legend->AddEntry(data3,"Data","l");
  legend->AddEntry(pred3,"Prediction","l");
  legend->AddEntry(fit3,"Best fit","l");
  legend->Draw();

  new TCanvas();
  pred4->SetLineWidth(3);
  pred4->SetLineColor(2);
  data4->SetLineWidth(3);
  data4->SetLineColor(1);
  fit4->SetLineWidth(3);
  fit4->SetLineColor(4);
  pred4->Draw("hist");
  data4->Draw("ep same");
  fit4->Draw("same");
  pred4->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred4->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("PROSPECT");
  legend->AddEntry(data4,"Data","l");
  legend->AddEntry(pred4,"Prediction","l");
  legend->AddEntry(fit4,"Best fit","l");
  legend->Draw();

  TCanvas* cc1 = new TCanvas();
  cc1->Divide(2,2);
  cc1->cd(1);
  pred0->SetLineWidth(3);
  pred0->SetLineColor(2);
  data0->SetLineWidth(3);
  data0->SetLineColor(1);
  fit0->SetLineWidth(3);
  fit0->SetLineColor(4);
  pred0->Draw("hist");
  data0->Draw("ep same");
  fit0->Draw("same");
  pred0->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred0->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Double Chooz");
  legend->AddEntry(data0,"Data","l");
  legend->AddEntry(pred0,"Prediction","l");
  legend->AddEntry(fit0,"Best fit","l");
  legend->Draw();
  cc1->cd(2);
  pred1->SetLineWidth(3);
  pred1->SetLineColor(2);
  data1->SetLineWidth(3);
  data1->SetLineColor(1);
  fit1->SetLineWidth(3);
  fit1->SetLineColor(4);
  pred1->Draw("hist");
  data1->Draw("ep same");
  fit1->Draw("same");
  pred1->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred1->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("Daya Bay");
  legend->AddEntry(data1,"Data","l");
  legend->AddEntry(pred1,"Prediction","l");
  legend->AddEntry(fit1,"Best fit","l");
  legend->Draw();
  cc1->cd(3);
  pred4->SetLineWidth(3);
  pred4->SetLineColor(2);
  data4->SetLineWidth(3);
  data4->SetLineColor(1);
  fit4->SetLineWidth(3);
  fit4->SetLineColor(4);
  pred4->Draw("hist");
  data4->Draw("ep same");
  fit4->Draw("same");
  pred4->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred4->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("PROSPECT");
  legend->AddEntry(data4,"Data","l");
  legend->AddEntry(pred4,"Prediction","l");
  legend->AddEntry(fit4,"Best fit","l");
  legend->Draw();
  cc1->cd(4);
  pred3->SetLineWidth(3);
  pred3->SetLineColor(2);
  data3->SetLineWidth(3);
  data3->SetLineColor(1);
  fit3->SetLineWidth(3);
  fit3->SetLineColor(4);
  pred3->Draw("hist");
  data3->Draw("ep same");
  fit3->Draw("same");
  pred3->GetXaxis()->SetTitle("Neutrino energy (MeV)");
  pred3->GetYaxis()->SetTitle("Events/ (0.25 MeV)");
  legend = new TLegend(0.65, 0.65, 0.9, 0.9);
  legend->SetHeader("NEOS");
  legend->AddEntry(data3,"Data","l");
  legend->AddEntry(pred3,"Prediction","l");
  legend->AddEntry(fit3,"Best fit","l");
  legend->Draw();


}
