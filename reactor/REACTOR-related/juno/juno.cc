/*
 *  t2k simple combined fit
 *
 *  Author: Guang Yang
 */
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
#include <TFile.h>

using namespace std;

  Sterile ::Sterile (const char* name) 
  : RooAbsReal(name,name)
{

// there will be: pull 0-2 s12, s23, s13, pull 3, CP delta, pull 4-6 dm2(21,32,31), pull 7-10 numu, nue Xsec and numu, nue selections

  _pulls     = new RooListProxy("_pulls","_pulls",this);
  RooRealVar* Par1 = new RooRealVar("par1","par1",0,-100,100);
  RooRealVar* Par2 = new RooRealVar("par2","par2",0,-100,100); // TMath::ASin(TMath::Sqrt(0.95))/2.,0,100);
  RooRealVar* Par3 = new RooRealVar("par3","par3",0,-100,100);
  RooRealVar* Par4 = new RooRealVar("par4","par4",0,-100,100);
  RooRealVar* Par5 = new RooRealVar("par5","par5",0.000075,-10,10);
  RooRealVar* Par6 = new RooRealVar("par6","par6",0,0,10); // 0.00238,-10,10);
  RooRealVar* Par7 = new RooRealVar("par7","par7",0,0,10);
  RooRealVar* Par8 = new RooRealVar("par8","par8",1,0.,100);
  RooRealVar* Par9 = new RooRealVar("par9","par9",1,0.,100);
  RooRealVar* Par10 = new RooRealVar("par10","par10",1,0.,100);
  RooRealVar* Par11 = new RooRealVar("par11","par11",1,0.,100);

  Par1->setConstant(true);
  Par2->setConstant(true);
  Par3->setConstant(true);
  Par4->setConstant(true);
  Par5->setConstant(true);
  Par6->setConstant(true);
  Par7->setConstant(true);
  Par8->setConstant(true);
  Par9->setConstant(true);
  Par10->setConstant(true);
  Par11->setConstant(true);

  _parlist.add(*Par1);
  _parlist.add(*Par2);
  _parlist.add(*Par3);
  _parlist.add(*Par4);
  _parlist.add(*Par5);
  _parlist.add(*Par6);
  _parlist.add(*Par7);
  _parlist.add(*Par8);
  _parlist.add(*Par9);
  _parlist.add(*Par10);
  _parlist.add(*Par11);
  _pulls->add(_parlist);

  this->addServerList(*_pulls);

  obsLE2Dm = new TMatrixD(400,400);
  predLE2Dm = new TMatrixD(400,400);
  predLE2Dorign = new TMatrixD(400,400);

  obsLE1Dm = new TMatrixD(400,400);
  predLE1Dm = new TMatrixD(400,400);
  predLE1Dorign = new TMatrixD(400,400);

  hereShift = new TMatrixD(400,400);
};

Sterile ::~Sterile ()
{;}


Double_t Sterile ::getPar(int i) {
(((RooAbsReal*)_pulls->at(i))->getVal());
}

RooRealVar* Sterile ::getParVar(int i) {
return ((RooRealVar*)_pulls->at(i));
}

void Sterile :: setPull(TH1D* pullvecCV){
  pullCV = new TVectorD(11);
  for(Int_t i=0;i<11;i++){
    (*pullCV)[i] =  pullvecCV->GetBinContent(i+1);
  }
}

void Sterile :: setPullUnc(TH1D* pullvecUnc){
  pullUnc = new TVectorD(11);
  for(Int_t i=0;i<11;i++){
    (*pullUnc)[i] = pullvecUnc->GetBinContent(i+1);
  }
}

Double_t Sterile::getPullUnc(Int_t pN){
  return (*pullUnc)[pN];
}

void Sterile::DataSwitch(Bool_t dataSwitch) const
{
  Bool_t _dataSwitch = dataSwitch;
}

Bool_t Sterile::getDataSwitch() const
{
  return _dataSwitch;
}

RooListProxy* Sterile::getPullList() const
{
  return _pulls;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// need to set up L_bins, E_bins, Ao, T_12, days, fract, Np, efficiency, Radius, Nmc
// need to input dm41, theta, 

void Sterile::Fillup( RooListProxy* _pulls, bool preEScale ) const
{

  double total_flux=Ao/TMath::Log(2)*T_12*24*3600*(1-TMath::Exp(-TMath::Log(2)*days/(T_12)))*fract*Np*efficiency;//may be frac is not needed here
  //energy shape function
  TF1 *shape=new TF1("shape","pol7", 0., 3.);
  shape->FixParameter(0,-0.000122132);
  shape->FixParameter(1,-0.0277255);
  shape->FixParameter(2,1.13235);
  shape->FixParameter(3,-1.53562);
  shape->FixParameter(4,1.20701);
  shape->FixParameter(5,-0.551793);
  shape->FixParameter(6,0.127225);
  shape->FixParameter(7,-0.0113842);

  //IBD cross-section
  TF1 *xsec=new TF1("xsec","1e-47*sqrt(pow(x-1.29,2)-0.511*0.511)*(x-1.29)*pow(x,-0.07056+0.02018*log(x)-0.001953*pow(log(x),3))",1.801, 3.);

  double correction_f=4./3.*TMath::Pi()*pow(Radius,3)*shape->Integral(1.801,3.);
  //double correction_f = TMath::Power((2*Radius),3) *shape->Integral(1.801,3.);

  TF1 *probb=new TF1("probb","(1-[1]*sin(1.27*[0]*x)*sin(1.27*[0]*x))",0., 12.);

  probb->SetParameter(0, dm41);
  probb->SetParameter(1, theta);

  TH2D* obsLE2D = new TH2D("","",L_bins,2,Radius*2+4,E_bins,1.8,3);
  TH2D* predLE2D = new TH2D("","",L_bins,2,Radius*2+4,E_bins,1.8,3);
  TH2D* predOrig = new TH2D("","",L_bins,2,Radius*2+4,E_bins,1.8,3);

  TH1D* obsLE1D = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
  TH1D* predLE1D = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
  TH1D* predOrig1D = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);

  TH1D* obsLE1D_temp[7];
  TH1D* predLE1D_temp[7];
  TH1D* predOrig1D_temp[7];

  for(Int_t iter=0; iter<7; iter++){
    obsLE1D_temp[iter] = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
    predLE1D_temp[iter] = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
    predOrig1D_temp[iter] = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
  }

  gRandom->SetSeed(11111);
  TRandom3 *W=new TRandom3(*((TRandom3*) gRandom));

  //generation non-oscillation rate
  for(int i=0; i<Nmc; i++)
  {
    double x=Radius*(1.-2*W->Rndm())+(sourceDis+Radius);
    double y=Radius*(1.-2*W->Rndm());
    double z=Radius*(1.-2*W->Rndm());
    double energy=TMath::Abs(shape->GetRandom());

    //std:cout<<sqrt(x*x+y*y+z*z)<<" "<<energy<<std::endl;
    int counts = 0;
    if((pow(x-sourceDis-Radius,2)+pow(y,2)+pow(z,2))<=Radius*Radius && energy>=1.801)
    {

      counts+=1;
      double Lvalue = sqrt(x*x+y*y+z*z);
      double Evalue = energy;
      double LSvalue = gRandom->Gaus(1,lSmear)*sqrt(x*x+y*y+z*z);
      double ESvalue = gRandom->Gaus(1,eSmear/TMath::Sqrt(energy))*energy;

      if(doEScale){
        LSvalue = gRandom->Gaus(1,lSmear)*sqrt(x*x+y*y+z*z);
        ESvalue = gRandom->Gaus(1,(eSmear+ ((RooAbsReal*)_pulls->at(2))->getVal() )/TMath::Sqrt(energy))*energy * (1+ ((RooAbsReal*)_pulls->at(3))->getVal());
      }

      double wNom = 1./(4.*TMath::Pi()*TMath::Power(Lvalue,2))*xsec->Eval(Evalue)*total_flux*correction_f/(Nmc*((4./3.*TMath::Pi()*pow(Radius,3)))/TMath::Power(2*Radius,3) * (shape->Integral(1.8,3)/shape->Integral(0,3)));
      double wSmr = 1./(4.*TMath::Pi()*TMath::Power(LSvalue,2))*xsec->Eval(ESvalue)*total_flux*correction_f/(Nmc*((4./3.*TMath::Pi()*pow(Radius,3)))/TMath::Power(2*Radius,3) * (shape->Integral(1.8,3)/shape->Integral(0,3)));

      if(do1D == true){
        obsLE1D->Fill(LSvalue/ESvalue, wNom * probb->Eval(Lvalue/Evalue));
        predLE1D->Fill(LSvalue/ESvalue, wNom );
        predOrig1D->Fill(Lvalue/Evalue, wNom );

        if(preEScale){
          for(int iter=0;iter<7;iter++){
            //obsLE1D_temp[iter]->Fill(LSvalue/ESvalue, wNom * probb->Eval(Lvalue/Evalue));
            predLE1D_temp[iter]->Fill(LSvalue / (ESvalue*(1 + /*(-0.03+iter*0.01)/TMath::Sqrt(energy)) +*/ (-0.03+0.01*iter) )), wNom );
            //predOrig1D_temp[iter]->Fill(Lvalue/Evalue, wNom );
	  }
	}
      }

      if(preEScale && !do1D) {std::cout<<"you can't do preEScale with 2D together, exit "<<std::endl; exit(1);}
      if(preEScale && doEScale) {std::cout<<"you can't do preEScale with and EScale together, exit "<<std::endl; exit(1);}

      obsLE2D->Fill(LSvalue, ESvalue, wNom * probb->Eval(Lvalue/Evalue));
      predLE2D->Fill(LSvalue, ESvalue, wNom );
      predOrig->Fill(Lvalue,Evalue, wNom );
      //std::cout<<"probability "<<probb->Eval(Lvalue/Evalue)<<std::endl;
      //L_vec.push_back(sqrt(x*x+y*y+z*z));
      //E_vec.push_back(energy);
      //L_vec_smear.push_back(gRandom->Gaus(1,lSmear)*sqrt(x*x+y*y+z*z));
      //E_vec_smear.push_back(gRandom->Gaus(1,eSmear)*energy);
    }
  }

  for(Int_t i=0;i<obsLE2D->GetNbinsX();i++){
    for(Int_t j=0;j<obsLE2D->GetNbinsY();j++){
      //obsLE2D->SetBinContent(i+1,j+1,obsLE2D->GetBinContent(i+1,j+1)*probb->Eval(obsLE2D->ProjectionX()->GetBinCenter(i+1)/obsLE2D->ProjectionY()->GetBinCenter(j+1)));
      //std::cout<<"oscillation probability "<<dm41<<" "<<theta<<" "<<obsLE2D->ProjectionX()->GetBinCenter(i+1)/obsLE2D->ProjectionY()->GetBinCenter(j+1)<<" "<<probb->Eval(obsLE2D->ProjectionX()->GetBinCenter(i+1)/obsLE2D->ProjectionY()->GetBinCenter(j+1))<<std::endl;
      (*obsLE2Dm)(i,j) = obsLE2D->GetBinContent(i+1,j+1);
    }	    
  }  
  
  for(Int_t i=0;i<predLE2D->GetNbinsX();i++){
    for(Int_t j=0;j<predLE2D->GetNbinsY();j++){
      //predLE2D->SetBinContent(i+1,j+1,predLE2D->GetBinContent(i+1,j+1)*(1+((RooAbsReal*)_pulls->at(0))->getVal())*(1+((RooAbsReal*)_pulls->at(1))->getVal()));
      (*predLE2Dm)(i,j) = predLE2D->GetBinContent(i+1,j+1);
      (*predLE2Dorign)(i,j) = predOrig->GetBinContent(i+1,j+1);
    }
  }
  std::cout<<"integral of obsLE2D and predLE2D "<<obsLE2D->Integral()<<" "<<predLE2D->Integral()<<std::endl;

  if(do1D == true){
    for(Int_t i=0;i<obsLE1D->GetNbinsX();i++){
      (*obsLE1Dm)(i,0) = obsLE1D->GetBinContent(i+1);
    }
    for(Int_t i=0;i<predLE1D->GetNbinsX();i++){
      (*predLE1Dm)(i,0) = predLE1D->GetBinContent(i+1);
      (*predLE1Dorign)(i,0) = predOrig1D->GetBinContent(i+1);
    }
  }

  if(preEScale){
    for(int iter=0;iter<7;iter++){
      for(int jter=0;jter<predLE1D->GetNbinsX();jter++)
        (*hereShift)(iter, jter) = predLE1D_temp[iter]->GetBinContent(jter+1) - predLE1D->GetBinContent(jter+1);
    }
  }

}

//////////////////////////////////////////////////////////////////////
Double_t Sterile::FillEv( RooListProxy* _pulls ) const
{
  TH2D* obsLE2D = new TH2D("","",L_bins,2,Radius*2+4,E_bins,1.8,3);
  TH2D* predLE2D = new TH2D("","",L_bins,2,Radius*2+4,E_bins,1.8,3);

  TH1D* obsLE1D = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);
  TH1D* predLE1D = new TH1D("","",A1D_bins, 2./3. ,(Radius*2+4)/1.8);


  for(Int_t i=0;i<obsLE2D->GetNbinsX();i++){
    for(Int_t j=0;j<obsLE2D->GetNbinsY();j++){
      obsLE2D->SetBinContent(i+1,j+1, (*obsLE2Dm)(i,j) );
    }
  }

  for(Int_t i=0;i<predLE2D->GetNbinsX();i++){
    for(Int_t j=0;j<predLE2D->GetNbinsY();j++){
      //if(predLE2D->ProjectionX()->GetBinCenter(i+1) > Radius*2 - 1 ) {
      //  predLE2D->SetBinContent(i+1,j+1, (*predLE2Dm)(i,j)*(1+((RooAbsReal*)_pulls->at(0))->getVal())*(1+((RooAbsReal*)_pulls->at(1))->getVal())*(1+((RooAbsReal*)_pulls->at(2))->getVal()) );
      //}
      //else{
        predLE2D->SetBinContent(i+1,j+1, (*predLE2Dm)(i,j)*(1+((RooAbsReal*)_pulls->at(0))->getVal())*(1+((RooAbsReal*)_pulls->at(1))->getVal()) );
      //}
    }
  }

  if(do1D == true){
    for(Int_t j=0;j<obsLE1D->GetNbinsX();j++){
      obsLE1D->SetBinContent(j+1, (*obsLE1Dm)(j,0) );
    }
    std::cout<<"doing 1D "<<endl;
    for(Int_t j=0;j<predLE1D->GetNbinsX();j++){
      if (preEScale) predLE1D->SetBinContent(j+1, ((*predLE1Dm)(j,0) + (*hereShift)(4,j) * ((((RooAbsReal*)_pulls->at(2))->getVal() - (*pullCV)[2])/(*pullUnc)[2]) )  *(1+((RooAbsReal*)_pulls->at(0))->getVal())*(1+((RooAbsReal*)_pulls->at(1))->getVal()) );
      else predLE1D->SetBinContent(j+1, (*predLE1Dm)(j,0)*(1+((RooAbsReal*)_pulls->at(0))->getVal())*(1+((RooAbsReal*)_pulls->at(1))->getVal()) );
    }
  }

  std::cout<<"recheck integral of obsLE2D and predLE2D "<<obsLE2D->Integral()<<" "<<predLE2D->Integral()<<std::endl;  

  double chii = 0;
  if(do1D == false){
    for(int i=0; i<L_bins; i++){
      for(int j=0; j<E_bins; j++){
        if (obsLE2D->GetBinContent(i+1,j+1)>0){
          if (doGaussian) chii += TMath::Power(predLE2D->GetBinContent(i+1,j+1)-obsLE2D->GetBinContent(i+1,j+1),2) / predLE2D->GetBinContent(i+1,j+1);
	  if (doLikelihood) chii += 2*(predLE2D->GetBinContent(i+1,j+1)-obsLE2D->GetBinContent(i+1,j+1)+obsLE2D->GetBinContent(i+1,j+1)*TMath::Log(TMath::Abs(obsLE2D->GetBinContent(i+1,j+1)/predLE2D->GetBinContent(i+1,j+1))));
        }
      }
    }
  }
  else{
    for(int i=0; i<A1D_bins; i++){
      if(predLE1D->GetBinContent(i+1) > 0){
        if (doGaussian) chii += TMath::Power(predLE1D->GetBinContent(i+1)-obsLE1D->GetBinContent(i+1),2) / predLE1D->GetBinContent(i+1);
        if (doLikelihood) chii += 2*(predLE1D->GetBinContent(i+1)-obsLE1D->GetBinContent(i+1)+obsLE1D->GetBinContent(i+1)*TMath::Log(TMath::Abs(obsLE1D->GetBinContent(i+1)/predLE1D->GetBinContent(i+1))));
      }
    }
  }
  std::cout<<"current chi2 sans pull : "<<chii<<std::endl;
  return chii;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t Sterile ::evaluate() const
{
  Double_t matPart = this->FillEv(_pulls);
  if(doEScale) this->Fillup(_pulls, false);

  Double_t extraPull = this -> ExtraPull (_pulls);
  Double_t tot = matPart + extraPull; //If needed, add pull terms here.

  return tot;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Double_t Sterile ::ExtraPull (RooListProxy* _pulls) const
{
  Double_t pullAdd = 0;
  for(Int_t i=0;i<11;i++){
    pullAdd += TMath::Power(( ((RooAbsReal*)_pulls->at(i))->getVal() - (*pullCV)[i] ),2) / TMath::Power( (*pullUnc)[i],2) ;
  }
  std::cout<<"extra pull penalty: "<<pullAdd<<std::endl;
  return pullAdd;
}
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// need to set up L_bins, E_bins, Ao, T_12, days, fract, Np, efficiency, Radius, Nmc
// need to input dm41, theta, 
void Sterile::SetLbins(int Lbins){
  L_bins = Lbins;
}
void Sterile::SetEbins(int Ebins){
  E_bins = Ebins;
}
void Sterile::Set1Dbins(int bins){
  A1D_bins = bins;
}
void Sterile::SetAO(double ao){
  Ao = ao;
}
void Sterile::SetT12(double t12){
  T_12 = t12;
}
void Sterile::SetDAYS(double _days){
  days = _days;
}
void Sterile::SetFRACT(double _fract){
  fract = _fract;
}
void Sterile::SetNP(double np){
  Np = np;
}
void Sterile::SetEfficiency(double eff){
  efficiency = eff;
}
void Sterile::SetRADIUS(double radius){
  Radius = radius;
}
void Sterile::SetNMC(int nmc){
  Nmc = nmc;
}
void Sterile::SetDM41(double _dm41){
  dm41 = _dm41;
}
void Sterile::SetTHETA(double _theta){
  theta = _theta;
}
void Sterile::SetSourceDis(double dis){
  sourceDis = dis;
}
void Sterile::SetLSmear(double sm){
  lSmear = sm;
}
void Sterile::SetESmear(double sme){
  eSmear = sme;
}

double Sterile::GetDM41(){
  return dm41;
}
double Sterile::GetTHETA(){
  return theta;
}

bool Sterile::SetStatGaus(bool gaus){
  if(gaus) {
    doGaussian = true;
    doLikelihood = false;
  }
  if(!gaus) {
    doGaussian = false;
    doLikelihood = true;
  }

}

bool Sterile::ifDo1D(bool vec){
  do1D = vec;
}

bool Sterile::ifDoEScale(bool vec){
  doEScale = vec;
}
bool Sterile::ifPreEScale(bool vec){
  preEScale = vec;
}

