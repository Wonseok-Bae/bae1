/*
Things to be validated:

-  correlation matrix from RENO/DYB and DC. What is the difference?

-  Prediction, Mueller/Huber model splines correct?

-  All four experiments data points are correct? Are we using the latest RENO data-points?

-  IBD Cross section spline correct? Really no way to be better?

-  Does (theta14,dms41) oscillation curves make sense?
*/

#include "simple_t2k.hh"
#include "TMath.h"

#include "RooArgList.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "TString.h"
#include <TVectorD.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFrame.h>

using namespace std;

int main(int argc, char**argv){

 // Prediction from Mueller/Huber + reactor correlation matrix + four experiments data points
   
 Sterile * rep = new Sterile ("_rep");
   char formula[10];

 // binned from 0.5-9 MeV with bin width of 0.25 MeV
 int nBins = 30;
 TH1D* binHist = new TH1D("","",nBins+1,0,nBins+1);
 for(Int_t i=0;i<nBins+1;i++){
   binHist->SetBinContent(i+1, 0.5 + 0.25*i);
 }

 TH1D* fissionHist = new TH1D("","",16,0,16);
 double fissionList[16]={0.49,0.09,0.35,0.07,    0.501,0.073,0.353,0.072,    0.679,0.072,0.215,0.035,      0.679,0.072,0.215,0.035};
 for(Int_t i=0;i<16;i++){
   fissionHist->SetBinContent(i+1, fissionList[i]);
 }

 rep->SetMatrixNameDC("data/ReactorMatrixND_shape_rho0_NU.root");
 rep->SetMatrixNameDYB("data/NEOSCorrelationMatrix.root");
 rep->SetMatrixNameRENO("data/NEOSCorrelationMatrix.root");
 rep->SetMatrixNameNEOS("data/NEOSCorrelationMatrix.root");

 rep->SetBinning(binHist);
 rep->SetFissionFraction(fissionHist);

 TMatrixD* cfMatrix = rep->ConversionMatrix("data/FinalFitIBDTree_DCIV_ND.root","FinalFitIBDTree");
 //TH2D* fHist = rep->GetConversionMatrix();


 //std::cout<<"'ve set some more inputs with cfHist and fHist integral : "<<cfHist->Integral()<<" "<<fHist->Integral()<<std::endl;

 std::vector<TString> mList;
 TString r235 = "data/huber235.txt";
 TString r238 = "data/mueller238.txt";
 TString r239 = "data/huber239.txt";
 TString r241 = "data/huber241.txt";

 mList.push_back(r235);
 mList.push_back(r238);
 mList.push_back(r239);
 mList.push_back(r241);

 rep->SetModelList(mList);

 std::vector<TH1D*> predictionVector = rep->preparePrediction(rep->getPullList(), false);
 std::vector<TH1D*> dataVector       = rep->prepareData(rep->preparePrediction(rep->getPullList(), false));

 std::cout<<"doing a data validation here. "<<std::endl;
 TH1D* valDat[dataVector.size()];
 for(Int_t i=0;i<dataVector.size();i++){
   valDat[i] = new TH1D("","",dataVector[i]->GetNbinsX(), dataVector[i]->GetBinLowEdge(1), dataVector[i]->GetBinLowEdge(dataVector[i]->GetNbinsX()) + dataVector[i]->GetBinWidth(dataVector[i]->GetNbinsX()));
   for(Int_t j=0;j<predictionVector[i]->GetNbinsX();j++){
     valDat[i] ->SetBinContent(j+1, dataVector[i]->GetBinContent(j+1)/predictionVector[i]->GetBinContent(j+1));
   }
 }
	 
 std::vector<TH1D*> fluxVector = rep->GetFluxPrediction(rep->getPullList(), false);
 //std::vector<TH1D*> predictionVector = rep->preparePrediction(rep->getPullList(), false);


 TVectorD* fVec = new TVectorD(nBins * 4);
 TVectorD* fData = new TVectorD(nBins * 4);
 TVectorD* fVecUnit = new TVectorD(nBins * 4);

 for(Int_t i=0;i<nBins;i++){
   (*fVec)[i]               = predictionVector[0]->GetBinContent(i+1)   ;
   (*fVec)[nBins + i]       = predictionVector[1]->GetBinContent(i+1)   ;
   (*fVec)[2 * nBins + i]   = predictionVector[2]->GetBinContent(i+1)  ;
   (*fVec)[3 * nBins + i]   = predictionVector[3]->GetBinContent(i+1)  ;
   (*fVecUnit)[i]               = 1.   ;
   (*fVecUnit)[nBins + i]       = 1.   ;
   (*fVecUnit)[2 * nBins + i]   = 1.   ;
   (*fVecUnit)[3 * nBins + i]   = 1.   ;
 }

 for(Int_t i=0;i<nBins;i++){
   (*fData)[i]             = dataVector[0]->GetBinContent(i+1)   ;
   (*fData)[nBins + i]     = dataVector[1]->GetBinContent(i+1)  ;
   (*fData)[2 * nBins + i] = dataVector[2]->GetBinContent(i+1) ;
   (*fData)[3 * nBins + i] = dataVector[3]->GetBinContent(i+1) ;
 }
 //std::cout<<"data ready also "<<std::endl;

 TMatrixD* covMatrix = rep->prepareCovMatrix(nBins, fVecUnit);

 TF1* xsecF = rep->GetIBDXsecFormula();
 TGraph* xsecP = rep->GetIBDXsecPoints();

 for(Int_t i=1;i<4;i++){
   predictionVector[i]->Scale(predictionVector[0]->Integral()/predictionVector[i]->Integral());
   dataVector[i]->Scale(dataVector[0]->Integral()/dataVector[i]->Integral());
   fluxVector[i]->Scale(fluxVector[0]->Integral()/fluxVector[i]->Integral());
 }


 TCanvas* c1 = new TCanvas();
 covMatrix->Draw("colz");
 c1->SaveAs("Validation1.C");

 TCanvas* c2 = new TCanvas();
 fluxVector[0]->SetLineColor(1);
 fluxVector[1]->SetLineColor(2);
 fluxVector[2]->SetLineColor(3);
 fluxVector[3]->SetLineColor(4);
 fluxVector[0]->Draw("hist");
 fluxVector[1]->Draw("same");
 fluxVector[2]->Draw("same");
 fluxVector[3]->Draw("same");
 c2->SaveAs("Validation2.C"); 

 TCanvas* c3 = new TCanvas();
 predictionVector[0]->SetLineColor(1);
 predictionVector[1]->SetLineColor(2);
 predictionVector[2]->SetLineColor(3);
 predictionVector[3]->SetLineColor(4);
 predictionVector.at(0)->Draw("hist");
 predictionVector.at(1)->Draw("same");
 predictionVector.at(2)->Draw("same");
 predictionVector.at(3)->Draw("same");
 c3->SaveAs("Validation3.C");

 TCanvas* c4 = new TCanvas();
 dataVector[0]->SetLineStyle(2);
 dataVector[1]->SetLineStyle(2);
 dataVector[2]->SetLineStyle(2);
 dataVector[3]->SetLineStyle(2);
 dataVector[0]->SetLineColor(1);
 dataVector[1]->SetLineColor(2);
 dataVector[2]->SetLineColor(3);
 dataVector[3]->SetLineColor(4);
 dataVector[0]->Draw("hist");
 dataVector[1]->Draw("same");
 dataVector[2]->Draw("same");
 dataVector[3]->Draw("same");
 predictionVector.at(0)->Draw("same");
 predictionVector.at(1)->Draw("same");
 predictionVector.at(2)->Draw("same");
 predictionVector.at(3)->Draw("same");
 c4->SaveAs("Validation4.C");

 TCanvas* c5 = new TCanvas();
 xsecF->SetLineColor(2);
 xsecP->SetLineColor(4);
 xsecP->Draw();
 xsecF->Draw("same");
 c5->SaveAs("Validation5.C");

 TCanvas* c6 = new TCanvas();
 TF1* IBDXsecF = new TF1("IBDXsecF","0.0952*(x-0.8)*( sqrt((x-0.8)*(x-0.8)-0.5*0.5))" ,1.8,10);
 IBDXsecF->Draw();
 xsecP->Draw("same");
 c6->SaveAs("Validation6.C");

 TCanvas* c7 = new TCanvas();
 //fHist->GetXaxis()->SetTitle("True energy (MeV)");
 //fHist->GetYaxis()->SetTitle("Prompt energy (MeV)");
 rep->GetConversionMatrix()->Draw("colz");
 c7->SaveAs("Validation7.C");

 TCanvas* c8 = new TCanvas();
 c8->Divide(2,2);
 for(Int_t i=0;i<4;i++){
   c8->cd(i+1);
   valDat[i]->SetLineColor(i+1);
   valDat[i]->GetXaxis()->SetTitle("Reconstruced energy (MeV)");
   valDat[i]->GetYaxis()->SetTitle("Data/Prediction");
   valDat[i]->Draw("hist");
 }
 c8->SaveAs("Validation8.C");
}

