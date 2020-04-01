#include "juno.hh"
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

 RooFitResult* res;
 Sterile * rep = new Sterile ("_rep");
   char formula[10];

 std::cout<<"start to run "<<std::endl;

 rep->SetLbins(100);
 rep->SetEbins(100);
 rep->Set1Dbins(150);
 rep->SetAO(100*3.7e13);
 rep->SetT12(284.91);
 rep->SetDAYS(450);
 rep->SetFRACT(1.);
 rep->SetNP(6.4e28);
 rep->SetEfficiency(0.9);
 rep->SetRADIUS(8.2);
 rep->SetNMC(1e7);
 rep->SetSourceDis(2.3);
 rep->SetLSmear(0.12);
 rep->SetESmear(0.08);
 rep->SetStatGaus(true);

 rep->ifDo1D(true);
 rep->ifDoEScale(false);
 rep->ifPreEScale(true);

 for(int iii=0;iii<1;iii++){
 for(int jjj=0;jjj<1;jjj++){
 double iDM = atof(argv[1]);
 double iST = atof(argv[2]);
 //rep->SetDM41(iDM/125.);
 //rep->SetTHETA(iST/125.);

 //rep->SetTHETA(TMath::Power(10.,(-2.*iST*2/100.)));
 //rep->SetDM41(TMath::Power(10,(-2 + 3.*iDM*2/100.)));
 rep->SetTHETA(TMath::Power(10.,(-3.*iST*2/100.)));
 rep->SetDM41(TMath::Power(10,(-2 + 3.*iDM*2/100.)));
 //rep->SetTHETA(iST);
 //rep->SetDM41(iDM);

 std::cout<<"'ve set some inputs "<<std::endl;

 TH1D* vecInput1 = new TH1D("","",11,0,11);
 TH1D* vecInput2 = new TH1D("","",11,0,11);

 vecInput1 ->SetBinContent(1, 0);
 vecInput1 ->SetBinContent(2, 0); //TMath::ASin(TMath::Sqrt(0.95))/2.);
 vecInput1 ->SetBinContent(3, 0); //0.1);
 vecInput1 ->SetBinContent(4, 0);
 vecInput1 ->SetBinContent(5,0.000075);
 vecInput1 ->SetBinContent(6, 0 ); //0.00238);
 vecInput1 ->SetBinContent(7, 0 ); //0.00244);
 vecInput1 ->SetBinContent(8,1);
 vecInput1 ->SetBinContent(9,1);
 vecInput1 ->SetBinContent(10,1);
 vecInput1 ->SetBinContent(11,1);

 vecInput2 ->SetBinContent(1, 0.01);
 vecInput2 ->SetBinContent(2, 0.01); //2);
 vecInput2 ->SetBinContent(3, 0.01);
 vecInput2 ->SetBinContent(4, 0.01);
 vecInput2 ->SetBinContent(5,0.0000018);
 vecInput2 ->SetBinContent(6, 100); //0.0001);
 vecInput2 ->SetBinContent(7, 100); //0.00009);
 vecInput2 ->SetBinContent(8, 100);
 vecInput2 ->SetBinContent(9, 100);
 vecInput2 ->SetBinContent(10,0.04);
 vecInput2 ->SetBinContent(11,0.027);

 rep ->setPull(vecInput1);
 rep ->setPullUnc(vecInput2);

 rep->Fillup(rep->getPullList(), rep->GetPreEScale() );
 TFile* outputFile = new TFile("outputTest1.root","RECREATE");

 TMatrixD* temp1 = rep->GetCurrentPredLE();
 temp1->Write("predLE");
 TMatrixD* temp2 = rep->GetCurrebtObsLE();
 temp2 ->Write("obsLE");
 TMatrixD* temp3 = rep->GetCurrentPredOrig();
 temp3->Write("predOrig");
 TMatrixD* shiftt = rep->GetPreEScaleShift();
 shiftt->Write("hereShift");
 outputFile->Close();

 rep ->FillEv(rep->getPullList());

 std::cout<<"'ve set some more & more inputs "<<std::endl;

 RooArgList list("list");
 list.add(*rep);
 sprintf(formula,"%s","@0");
 RooFormulaVar* fcn = new RooFormulaVar("fit","fit",formula,list);

 rep->getParVar(0)->setConstant(false);
 rep->getParVar(1)->setConstant(false);
 rep->getParVar(2)->setConstant(false);

 std::cout<<"first thing saved "<<std::endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ofstream outText;
 outText.open(Form("/gpfs/projects/McGrewGroup/gyang/REACTOR-related/juno/result/scan2Dnew_jinping8.2_1D_preEScale_log_%s_%f_%f.txt",argv[3], iDM, iST ));

 //double iDM = atof(argv[1]);
 //double iST = atof(argv[2]);
 //for(Int_t iDM=0;iDM<50;iDM++)
 //{
     //for(Int_t iST=0;iST<50;iST++)
     //{
        // means that s2t14 0.001 - 1 and dm2 0.01 - 10
        //rep->getParVar(2)->setVal(TMath::Power(10.,(-3.*iST*2/100.)));
        //rep->getParVar(6)->setVal(TMath::Power(10,(-2 + 5.*iDM*2/100.)));
        //rep->SetTHETA(TMath::Power(10.,(-3.*iST*2/100.)));
	//rep->SetDM41(TMath::Power(10,(-2 + 5.*iDM*2/100.)));
	//rep->SetDM41(iDM/125.);
	//rep->SetTHETA(iST/125.);

	//rep->prepareData(rep->preparePrediction(rep->getPullList(), false));

 	RooMinuit m(*fcn);
 	m.setStrategy(2);
 	Double_t callsEDM[2] = {10500., 1.e-6};
 	Int_t irf = 0;

 	gMinuit->mnexcm("MIGRAD",callsEDM,2,irf);
 	m.migrad();
 	//m.hesse();
 	//m.minos(); 
 	res = m.save();
 	double bestFit = res->minNll();
        std::cout<<"fit status code is : "<< res->status()<<std::endl;	
	//status = 0    : OK
  	//status = 1    : Covariance was mad  epos defined
   	//status = 2    : Hesse is invalid
   	//status = 3    : Edm is above max
   	//status = 4    : Reached call limit
   	//status = 5    : Any other failure
	std::cout<<"quiality code of covariance matrix is : "<< res->covQual()<<std::endl;
	//status = -1 :  not available (inversion failed or Hesse failed)
        //status =  0 : available but not positive defined
        //status =  1 : covariance only approximate
        //status =  2 : full matrix but forced pos def
        //status =  3 : full accurate matrix
	outText<<atoi(argv[1])<<" "<<atoi(argv[2])<<" "<<bestFit<<std::endl;

     //}
 //}

 //////////////////////	
 //inline Int_t status() const 
 //inline Int_t covQual() const 
 //inline Int_t numInvalidNLL() const 
 //inline Double_t edm() const 
 //inline Double_t minNll() const 
 /////////////////////


 double bb =  rep->getParVar(0)->getAsymErrorLo();
 double dd =  rep->getParVar(0)->getAsymErrorHi();

 }
 }
 //cout<<"errors are "<<bb<<" "<<dd<<endl;
}
