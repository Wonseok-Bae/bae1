/*
 *  t2k simple combined fit
 *
 *  Author: Guang Yang
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

  Sterile ::Sterile (const char* name) 
  : RooAbsReal(name,name)
{

// there will be: pull 0-2 s12, s23, s13, pull 3, CP delta, pull 4-6 dm2(21,32,31), pull 7-10 numu, nue Xsec and numu, nue selections

  _pulls     = new RooListProxy("_pulls","_pulls",this);
  RooRealVar* Par1 = new RooRealVar("s12","par1",TMath::ASin(TMath::Sqrt(0.85))/2.,0,100);
  RooRealVar* Par2 = new RooRealVar("s23","par2",0,0,100); // TMath::ASin(TMath::Sqrt(0.95))/2.,0,100);
  RooRealVar* Par3 = new RooRealVar("s14","par3",0.1,0,100);
  RooRealVar* Par4 = new RooRealVar("delta","par4",-1.5,-10,10);
  RooRealVar* Par5 = new RooRealVar("dm21","par5",0.000075,-10,10);
  RooRealVar* Par6 = new RooRealVar("dm32","par6",0,0,10); // 0.00238,-10,10);
  RooRealVar* Par7 = new RooRealVar("dm41","par7",0.00244,0,10);
  RooRealVar* Par8 = new RooRealVar("numuX","par8",1,0.,100);
  RooRealVar* Par9 = new RooRealVar("nueX","par9",1,0.,100);
  RooRealVar* Par10 = new RooRealVar("numuSel","par10",1,0.,100);
  RooRealVar* Par11 = new RooRealVar("nueSel","par11",1,0.,100);

  RooRealVar* Par12 = new RooRealVar("reactorVar1","par12",1,-10,10) ;
  RooRealVar* Par13 = new RooRealVar("reactorVar2","par13",1,-10,10) ;
  RooRealVar* Par14 = new RooRealVar("reactorVar3","par14",1,-10,10) ;
  RooRealVar* Par15 = new RooRealVar("reactorVar4","par15",1,-10,10) ;
  RooRealVar* Par16 = new RooRealVar("reactorVar5","par16",1,-10,10) ;
  RooRealVar* Par17 = new RooRealVar("reactorVar6","par17",1,-10,10) ;
  RooRealVar* Par18 = new RooRealVar("reactorVar7","par18",1,-10,10) ;
  RooRealVar* Par19 = new RooRealVar("reactorVar8","par19",1,-10,10) ;
  RooRealVar* Par20 = new RooRealVar("reactorVar9","par20",1,-10,10) ;
  RooRealVar* Par21 = new RooRealVar("reactorVar10","par21",1,-10,10) ;
  RooRealVar* Par22 = new RooRealVar("reactorVar11","par22",1,-10,10) ;
  RooRealVar* Par23 = new RooRealVar("reactorVar12","par23",1,-10,10) ;
  RooRealVar* Par24 = new RooRealVar("reactorVar13","par24",1,-10,10) ;
  RooRealVar* Par25 = new RooRealVar("reactorVar14","par25",1,-10,10) ;
  RooRealVar* Par26 = new RooRealVar("reactorVar15","par26",1,-10,10) ;
  RooRealVar* Par27 = new RooRealVar("reactorVar16","par27",1,-10,10) ;
  RooRealVar* Par28 = new RooRealVar("reactorVar17","par28",1,-10,10) ;
  RooRealVar* Par29 = new RooRealVar("reactorVar18","par29",1,-10,10) ;
  RooRealVar* Par30 = new RooRealVar("reactorVar19","par30",1,-10,10) ;
  RooRealVar* Par31 = new RooRealVar("reactorVar20","par31",1,-10,10) ;
  RooRealVar* Par32 = new RooRealVar("reactorVar21","par32",1,-10,10) ;
  RooRealVar* Par33 = new RooRealVar("reactorVar22","par33",1,-10,10) ;
  RooRealVar* Par34 = new RooRealVar("reactorVar23","par34",1,-10,10) ;
  RooRealVar* Par35 = new RooRealVar("reactorVar24","par35",1,-10,10) ;
  RooRealVar* Par36 = new RooRealVar("reactorVar25","par36",1,-10,10) ;
  RooRealVar* Par37 = new RooRealVar("reactorVar26","par37",1,-10,10) ;
  RooRealVar* Par38 = new RooRealVar("reactorVar27","par38",1,-10,10) ;
  RooRealVar* Par39 = new RooRealVar("reactorVar28","par39",1,-10,10) ;
  RooRealVar* Par40 = new RooRealVar("reactorVar29","par40",1,-10,10) ;
  RooRealVar* Par41 = new RooRealVar("reactorVar30","par41",1,-10,10) ;
  RooRealVar* Par42 = new RooRealVar("reactorVar31","par42",1,-10,10) ;
  RooRealVar* Par43 = new RooRealVar("reactorVar32","par43",1,-10,10) ;
  RooRealVar* Par44 = new RooRealVar("reactorVar33","par44",1,-10,10) ;
  RooRealVar* Par45 = new RooRealVar("reactorVar34","par45",1,-10,10) ;

  RooRealVar* Par46 = new RooRealVar("EscaleVar1DC", "par45",1,-10,10);
  RooRealVar* Par47 = new RooRealVar("EscaleVar2DC", "par47",1,-10,10);
  RooRealVar* Par48 = new RooRealVar("EscaleVar3DYB", "par48",1,-10,10);
  RooRealVar* Par49 = new RooRealVar("EscaleVar4DYB", "par49",1,-10,10);
  RooRealVar* Par50 = new RooRealVar("EscaleVar5RENO", "par50",1,-10,10);
  RooRealVar* Par51 = new RooRealVar("EscaleVar6RENO", "par51",1,-10,10);
  RooRealVar* Par52 = new RooRealVar("EscaleVar7NEOS", "par52",1,-10,10);
  RooRealVar* Par53 = new RooRealVar("EscaleVar8NEOS", "par53",1,-10,10);
  RooRealVar* Par54 = new RooRealVar("EscaleVar9PROS", "par54",1,-10,10);
  RooRealVar* Par55 = new RooRealVar("EscaleVar10PROS", "par55",1,-10,10);

  Par1->setConstant(false);
  Par2->setConstant(false);
  Par3->setConstant(false);
  Par4->setConstant(false);
  Par5->setConstant(false);
  Par6->setConstant(false);
  Par7->setConstant(false);
  Par8->setConstant(false);
  Par9->setConstant(false);
  Par10->setConstant(false);
  Par11->setConstant(false);
  Par12->setConstant(false);
  Par13->setConstant(false);
  Par14->setConstant(false);
  Par15->setConstant(false);
  Par16->setConstant(false);
  Par17->setConstant(false);
  Par18->setConstant(false);
  Par19->setConstant(false);
  Par20->setConstant(false);
  Par21->setConstant(false);
  Par22->setConstant(false);
  Par23->setConstant(false);
  Par24->setConstant(false);
  Par25->setConstant(false);
  Par26->setConstant(false);
  Par27->setConstant(false);
  Par28->setConstant(false);
  Par29->setConstant(false);
  Par30->setConstant(false);
  Par31->setConstant(false);
  Par32->setConstant(false);
  Par33->setConstant(false);
  Par34->setConstant(false);
  Par35->setConstant(false);
  Par36->setConstant(false);
  Par37->setConstant(false);
  Par38->setConstant(false);
  Par39->setConstant(false);
  Par40->setConstant(false);
  Par41->setConstant(false);
  Par42->setConstant(false);
  Par43->setConstant(false);
  Par44->setConstant(false);
  Par45->setConstant(false);

  Par46->setConstant(false);
  Par47->setConstant(false);
  Par48->setConstant(false);
  Par49->setConstant(false);
  Par50->setConstant(false);
  Par51->setConstant(false);
  Par52->setConstant(false);
  Par53->setConstant(false);
  Par54->setConstant(false);
  Par55->setConstant(false);

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
  _parlist.add(*Par12);
  _parlist.add(*Par13);
  _parlist.add(*Par14);
  _parlist.add(*Par15);
  _parlist.add(*Par16);
  _parlist.add(*Par17);
  _parlist.add(*Par18);
  _parlist.add(*Par19);
  _parlist.add(*Par20);
  _parlist.add(*Par21);
  _parlist.add(*Par22);
  _parlist.add(*Par23);
  _parlist.add(*Par24);
  _parlist.add(*Par25);
  _parlist.add(*Par26);
  _parlist.add(*Par27);
  _parlist.add(*Par28);
  _parlist.add(*Par29);
  _parlist.add(*Par30);
  _parlist.add(*Par31);
  _parlist.add(*Par32);
  _parlist.add(*Par33);
  _parlist.add(*Par34);
  _parlist.add(*Par35);
  _parlist.add(*Par36);
  _parlist.add(*Par37);
  _parlist.add(*Par38);
  _parlist.add(*Par39);
  _parlist.add(*Par40);
  _parlist.add(*Par41);
  _parlist.add(*Par42);
  _parlist.add(*Par43);
  _parlist.add(*Par44);
  _parlist.add(*Par45);

  _parlist.add(*Par46);
  _parlist.add(*Par47);
  _parlist.add(*Par48);
  _parlist.add(*Par49);
  _parlist.add(*Par50);
  _parlist.add(*Par51);
  _parlist.add(*Par52);
  _parlist.add(*Par53);
  _parlist.add(*Par54);
  _parlist.add(*Par55);
  _pulls->add(_parlist);

  this->addServerList(*_pulls);

/*
  predDC = new TH1D("","predDC",34, 0.5, 8.);
  predDYB = new TH1D("","predDYB",34, 0.5, 8.);
  predRENO = new TH1D("","predRENO",34, 0.5, 8.);
  predNEOS = new TH1D("","predNEOS",34, 0.5, 8.);
*/
  dataDC = new TH1D("","dataDC",30, 0.5, 8.);
  dataDYB = new TH1D("","dataDYB",30, 0.5, 8.);
  dataRENO = new TH1D("","dataRENO",30, 0.5, 8.);
  dataNEOS = new TH1D("","dataNEOS",30, 0.5, 8.);
  dataPROS = new TH1D("","dataPROS",30, 0.5, 8.);
};

Sterile ::~Sterile ()
{;}

//=========================================================================================================================================================================1. Sterile========
TMatrixD* Sterile::prepareCovMatrix(Int_t nBins, TVectorD* fVec) const
{

  TFile fMatrixDC(fileNameDC);
  TFile fMatrixDYB(fileNameDYB);
  TFile fMatrixRENO(fileNameRENO);
  TFile fMatrixNEOS(fileNameNEOS);
  TFile fMatrixPROS(fileNamePROS);

  TMatrixD* outMat = new TMatrixD(5 * nBins , 5 * nBins);

  if(inSyst){

      TMatrixD* fracMatDC = (TMatrixD*)fMatrixDC.Get("frac_approx");
      for(Int_t i=0;i<nBins;i++)
      {
          for(Int_t j=0;j<nBins;j++)
          {
              (*fracMatDC)(i,j) = (*fracMatDC)(i,j);
          }
      }
      fracMatDC->ResizeTo(nBins , nBins);

      TMatrixD* fracMatDYB = new TMatrixD(100,100);
      TH2D* fracTH2DYB = (TH2D*)fMatrixDYB.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2DYB->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2DYB->GetNbinsY();j++)
          {
              (*fracMatDYB)(i+2,j+2) = fracTH2DYB->GetBinContent(i+1,j+1);
          }
      }
      fracMatDYB->ResizeTo(nBins,nBins);

      TMatrixD* fracMatRENO = new TMatrixD(100,100);
      TH2D* fracTH2RENO = (TH2D*)fMatrixRENO.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2RENO->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2RENO->GetNbinsY();j++)
          {
              (*fracMatRENO)(i+2,j+2) = fracTH2RENO->GetBinContent(i+1,j+1);
          }
      }
      fracMatRENO->ResizeTo(nBins,nBins);

      TMatrixD* fracMatNEOS = new TMatrixD(100,100);
      TH2D* fracTH2NEOS = (TH2D*)fMatrixNEOS.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2NEOS->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2NEOS->GetNbinsY();j++)
          {
              (*fracMatNEOS)(i+2,j+2) = fracTH2NEOS->GetBinContent(i+1,j+1);
          }
      }
      fracMatNEOS->ResizeTo(nBins,nBins);

      TMatrixD* fracMatPROS = new TMatrixD(100,100);
      TH2D* fracTH2PROS = (TH2D*)fMatrixPROS.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2PROS->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2PROS->GetNbinsY();j++)
          {
              (*fracMatPROS)(i+2,j+2) = fracTH2PROS->GetBinContent(i+1,j+1);
          }
      }
      fracMatPROS->ResizeTo(nBins,nBins);

      (*fracMatDYB)(0,0) = fracTH2DYB->GetBinContent(1,1);
      (*fracMatDYB)(1,1) = fracTH2DYB->GetBinContent(1,1);
      (*fracMatRENO)(0,0) = fracTH2RENO->GetBinContent(1,1);
      (*fracMatRENO)(1,1) = fracTH2RENO->GetBinContent(1,1);
      (*fracMatNEOS)(0,0) = fracTH2NEOS->GetBinContent(1,1);
      (*fracMatNEOS)(1,1) = fracTH2NEOS->GetBinContent(1,1);
      (*fracMatPROS)(0,0) = fracTH2PROS->GetBinContent(1,1);
      (*fracMatPROS)(1,1) = fracTH2PROS->GetBinContent(1,1);

//==========================================================================================================================================================2.Matrix==================

      // Reactor flux error vector from DYB paper : arXiv. 1607.05378
      double errlist_all[100]={0.042,0.03,0.025,0.022,0.021,0.019,0.017,0.015,0.015,0.0155,
    	  		       0.017,0.018,0.02,0.022,0.025,0.029,0.033,0.035,0.037,0.041,
  			       0.052,0.065,0.072
  			      };
      double errlist_flux[100]={0.01,0.01,0.09,0.09,0.09,0.09,0.09,0.09,0.09,0.01,
	  		        0.01,0.01,0.01,0.011,0.013,0.014,0.015,0.016,0.018,
			        0.02,0.022,0.025  
  			       };
      TVectorD* errList = new TVectorD(nBins);
      for(Int_t i = 0; i< nBins; i++)
      {
          (*errList)[i] = errlist_all[i];
      }
      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      for(Int_t i = 0; i< nBins; i++)
      {
        for(Int_t j =0 ;j<nBins; j++) 
        { 
            //std::cout<<(*fracMat)(i,j)<<std::endl; 
            //if((*fracMatDC)(4,4) > 0.5 )
            //    (*outMat)(i,j) = (*fracMatDC)(i,j) * (*errList)[i] * (*errList)[j] * (*fVec)[i] * (*fVec)[j];
	    //else      
	        (*outMat)(i,j) = (*fracMatDC)(i,j) * (*fVec)[i] * (*fVec)[j];
        }
      }

      for(Int_t i = nBins; i< 2 * nBins; i++)
      {
        for(Int_t j = nBins ;j< 2 *nBins; j++) 
        {
	    //std::cout<<"in loading second matrix "<<std::endl;
	    //std::cout<<(*fracMatDYB)(0,0)<<std::endl;
	    //if((*fracMatDYB)(4,4) > 0.5)
	        (*outMat)(i,j) = (*fracMatDYB)(i-nBins,j-nBins) * (*errList)[i-nBins] * (*errList)[j-nBins]  * (*fVec)[i] * (*fVec)[j];
	    //else
            //    (*outMat)(i,j) = (*fracMatDYB)(i-nBins,j-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }
      //std::cout<<"in middle of matrix preparation "<<std::endl;

      for(Int_t i = nBins+nBins; i<nBins*3; i++)
      {
        for(Int_t j = nBins+nBins ;j < nBins*3; j++) 
        {
	    //if((*fracMatRENO)(4,4) > 0.5)
	        (*outMat)(i,j) = (*fracMatRENO)(i-nBins-nBins,j-nBins-nBins) * (*errList)[i-nBins-nBins] * (*errList)[j-nBins-nBins]  * (*fVec)[i] * (*fVec)[j];		
	    //else
       	    //    (*outMat)(i,j) = (*fracMatRENO)(i-nBins-nBins,j-nBins-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }

      for(Int_t i = nBins*3; i< nBins*4; i++)
      {
        for(Int_t j = nBins*3 ;j< nBins*4; j++) 
        {
	    //if((*fracMatNEOS)(4,4) > 0.5)
                (*outMat)(i,j) = (*fracMatNEOS)(i-nBins-nBins-nBins,j-nBins-nBins-nBins) * (*errList)[i-nBins-nBins-nBins] * (*errList)[j-nBins-nBins-nBins]  * (*fVec)[i] * (*fVec)[j];
            //else	    
      	    //    (*outMat)(i,j) = (*fracMatNEOS)(i-nBins-nBins-nBins,j-nBins-nBins-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }

      std::cout<<"DC1_Doing PROSPECT matrix setup "<<std::endl;
      for(Int_t i = nBins*4; i< nBins*5; i++)
      {
        for(Int_t j = nBins*4 ;j< nBins*5; j++)
        {
	    //std::cout<<(*fracMatPROS)(i-4*nBins,j-4*nBins)<<" "<<(*errList)[i-4*nBins]<<" "<<(*fVec)[i]<<" "<<(*fVec)[j]<<std::endl;
            (*outMat)(i,j) = (*fracMatPROS)(i-4*nBins,j-4*nBins) * (*errList)[i-4*nBins] * (*errList)[j-4*nBins]  * (*fVec)[i] * (*fVec)[j];
        }
      }
  }
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  for(Int_t i = 0; i< nBins*5 ; i++)
  {
    (*outMat)(i,i) += (*fVec)[i] ;
    if((*outMat)(i,i) == 0) (*outMat)(i,i) += 0.0000000001;
  }

//std::cout<<"DC2_matrix sum "<<outMat ->Sum()<<std::endl;
return outMat ;
}

//============================================================================================================================================3. making Matrix using error List======

Double_t Sterile::surv_Prob(Double_t E, RooListProxy* _pulls, Double_t L) const //survival probability. energy, pulls(theta, mass_differance, CP angle) length.
{
  Double_t delta_21 = ((RooAbsReal*)_pulls->at(4))->getVal()* (L/E)*1.27 ;//the angle theta that used for Oscillation Probabiltiy
  Double_t delta_32 = ((RooAbsReal*)_pulls->at(5))->getVal()* (L/E)*1.27 ;
  Double_t delta_31 = ((RooAbsReal*)_pulls->at(6))->getVal()* (L/E)*1.27 ;

  //Double_t prob = 1 - 0.085 * TMath::Power(TMath::Sin(1.27 * 0.00244 * (L/E) ),2) - ((RooAbsReal*)_pulls->at(2))->getVal() *  TMath::Power(TMath::Sin(delta_31),2);
  Double_t prob = 1 - ((RooAbsReal*)_pulls->at(2))->getVal() *  TMath::Power(TMath::Sin(delta_31),2);

  return prob;       
}

//============================================================================================================================================4. Survival Probaability

Double_t Sterile ::FillEv( RooListProxy* _pulls ) const 
{

   //std::cout<<"DC3_in FillEv() "<<std::endl;
   int nBins = _nBins;

   std::vector<TH1D*> tempPredList = this->preparePrediction(_pulls, true);
   //std::cout<<"DC4_filled in new pediction "<<std::endl;
   //std::vector<TH1D*> tempDataList = this->prepareData();
   TH1D* predDC = tempPredList[0];
   TH1D* predDYB = tempPredList[1];
   TH1D* predRENO = tempPredList[2];
   TH1D* predNEOS = tempPredList[3]; 
   TH1D* predPROS = tempPredList[4];

   TVectorD* fVec = new TVectorD(nBins * 5);
   TVectorD* fData = new TVectorD(nBins * 5);

   TH1D* tempVec[5]; 
   TH1D* tempDat[5]; 
   for(Int_t i=0;i<5;i++){
     tempVec[i] = new TH1D("","",100,0,10);
     tempDat[i] = new TH1D("","",100,0,10);
   }
   //-----------------------------------------------------------------------------------------------------------------------------------tempPredList----------------------------------

/*
   for(Int_t i=0;i<nBins;i++){  

	 double recoE = predDC->GetBinCenter(i+1);
	 (*fVec)[i]               = 0;
         (*fVec)[nBins + i]       = 0;
         (*fVec)[2 * nBins + i]   = 0;
         (*fVec)[3 * nBins + i]   = 0;

	 for(Int_t inl=0;inl<predDC->GetNbinsX(); inl++){
	   double prob = (*unfoldingMatrix)(i, inl);
	   double unfoldE = predDC->GetBinCenter(inl+1);
           Double_t thisE = (((RooAbsReal*)_pulls->at(8))->getVal()-1.) + ((RooAbsReal*)_pulls->at(7))->getVal() * unfoldE;
           (*fVec)[i]               += prob * predDC->GetBinContent(i+1) * this->surv_Prob( (thisE) , _pulls, 400)  ;
	   (*fVec)[nBins + i]       += prob * predDYB->GetBinContent(i+1) * this->surv_Prob( (thisE) , _pulls, 560)  ;
           (*fVec)[2 * nBins + i]   += prob * predRENO->GetBinContent(i+1) * this->surv_Prob( (thisE) , _pulls, 410.6)  ;
           (*fVec)[3 * nBins + i]   += prob * predNEOS->GetBinContent(i+1) * this->surv_Prob( (thisE) , _pulls, 20)  ;
	 }
   }
*/

   for(Int_t i=0;i<nBins;i++){	 
         //Double_t thisE = (((RooAbsReal*)_pulls->at(8))->getVal()-1.) + ((RooAbsReal*)_pulls->at(7))->getVal() * predDC->GetBinCenter(i+1);
         (*fVec)[i]               = predDC->GetBinContent(i+1) ; //* this->surv_Prob( (thisE) , _pulls, 400)  ;
         (*fVec)[nBins + i]       = predDYB->GetBinContent(i+1) ; //* this->surv_Prob( (thisE) , _pulls, 560)  ;
         (*fVec)[2 * nBins + i]   = predRENO->GetBinContent(i+1) ; //* this->surv_Prob( (thisE) , _pulls, 410.6)  ;
         (*fVec)[3 * nBins + i]   = predNEOS->GetBinContent(i+1) ; //* this->surv_Prob( (thisE) , _pulls, 20)  ;
         (*fVec)[4 * nBins + i]   = predPROS->GetBinContent(i+1) ;
         tempVec[0] -> SetBinContent(i+1, (*fVec)[i]);
	 tempVec[1] -> SetBinContent(i+1, (*fVec)[nBins + i]);
	 tempVec[2] -> SetBinContent(i+1, (*fVec)[2 * nBins + i]);
	 tempVec[3] -> SetBinContent(i+1, (*fVec)[3 * nBins + i]);
         tempVec[4] -> SetBinContent(i+1, (*fVec)[4 * nBins + i]);
   }
   //std::cout<<"prepared new prediction"<<std::endl;
         
   for(Int_t i=0;i<nBins;i++){
	//std::cout<<dataDC->GetBinContent(i+1)<<" "<<dataDYB->GetBinContent(i+1)<<std::endl;
   	(*fData)[i]             = dataDC->GetBinContent(i+1)   ;
        (*fData)[nBins + i]     = dataDYB->GetBinContent(i+1)  ;
        (*fData)[2 * nBins + i] = dataRENO->GetBinContent(i+1) ;
        (*fData)[3 * nBins + i] = dataNEOS->GetBinContent(i+1) ;
        (*fData)[4 * nBins + i] = dataPROS->GetBinContent(i+1) ;
        tempDat[0] -> SetBinContent(i+1, (*fData)[i]);
        tempDat[1] -> SetBinContent(i+1, (*fData)[nBins + i]);
        tempDat[2] -> SetBinContent(i+1, (*fData)[2 * nBins + i]);
        tempDat[3] -> SetBinContent(i+1, (*fData)[3 * nBins + i]);
        tempDat[4] -> SetBinContent(i+1, (*fData)[4 * nBins + i]);
   }
   //std::cout<<"data ready also "<<std::endl;
   //--------------------------------------------------------------------------------------------------------------------------------Data------------------------------------

   // scale to same total rate, doing shape only analysis 
   double scaling1 = tempDat[0]->Integral() / tempVec[0]->Integral();
   double scaling2 = tempDat[1]->Integral() / tempVec[1]->Integral();
   double scaling3 = tempDat[2]->Integral() / tempVec[2]->Integral();
   double scaling4 = tempDat[3]->Integral() / tempVec[3]->Integral();
   double scaling5 = tempDat[4]->Integral() / tempVec[4]->Integral();

   for(Int_t i=0;i<nBins;i++){
      (*fData)[i]             = 0; //dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  ;
      (*fData)[nBins + i]     = 0; //dataDYB->GetBinContent(i+1)  - (*fVec)[nBins + i] * scaling2;
      (*fData)[2 * nBins + i] = 0; //dataRENO->GetBinContent(i+1) - (*fVec)[2 * nBins + i] * scaling3 ;
      (*fData)[3 * nBins + i] = 0; //dataNEOS->GetBinContent(i+1) - (*fVec)[3 * nBins + i] * scaling4;
      (*fData)[4 * nBins + i] = 0;
   }

   if (singleExp.Contains("DC")){
     //std::cout<<"DC5_Adding DC "<<std::endl;
     for(Int_t i=0;i<nBins;i++){
        (*fData)[i]             = dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  ;
     }
   }
   if (singleExp.Contains("DYB")){
     //std::cout<<"DC6_Adding DYB "<<std::endl;
     for(Int_t i=0;i<nBins;i++){
        (*fData)[nBins + i]     = dataDYB->GetBinContent(i+1)  - (*fVec)[nBins + i] * scaling2;
     }
   }
   if (singleExp.Contains("RENO")){
     //std::cout<<"DC7_Adding RENO "<<std::endl;
     for(Int_t i=0;i<nBins;i++){
        (*fData)[2 * nBins + i] = dataRENO->GetBinContent(i+1) - (*fVec)[2 * nBins + i] * scaling3 ;
     }
   }
   if (singleExp.Contains("NEOS")){
     //std::cout<<"DC8_Adding NEOS "<<std::endl;
     for(Int_t i=0;i<nBins;i++){
        (*fData)[3 * nBins + i] = dataNEOS->GetBinContent(i+1) - (*fVec)[3 * nBins + i] * scaling4;
     }
   }
   if (singleExp.Contains("PROS")){
     //std::cout<<"DC9_Adding PROSPECT "<<std::endl;
     for(Int_t i=0;i<nBins;i++){
        (*fData)[4 * nBins + i] = dataPROS->GetBinContent(i+1) - (*fVec)[4 * nBins + i] * scaling5;
     }
   }
   if (singleExp.Contains("ALL")){
     for(Int_t i=0;i<nBins;i++){ 
     //std::cout<<"DC10_Adding ALL at one time "<<std::endl;
        (*fData)[i]             = TMath::Abs( dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  );
        (*fData)[nBins + i]     = TMath::Abs( dataDYB->GetBinContent(i+1)  - (*fVec)[nBins + i] * scaling2 );
	(*fData)[2 * nBins + i] = TMath::Abs( dataRENO->GetBinContent(i+1) - (*fVec)[2 * nBins + i] * scaling3 );
	(*fData)[3 * nBins + i] = TMath::Abs( dataNEOS->GetBinContent(i+1) - (*fVec)[3 * nBins + i] * scaling4 );
        (*fData)[4 * nBins + i] = TMath::Abs( dataPROS->GetBinContent(i+1) - (*fVec)[4 * nBins + i] * scaling5 );
	//std::cout<<(*fData)[i]<<" "<<(*fData)[nBins + i] <<" "<<(*fData)[2 * nBins + i]<<" "<<(*fData)[3 * nBins + i]<<" "<<(*fData)[4 * nBins + i]<<std::endl;
	//std::cout<<dataDC->GetBinContent(i+1)<<" "<<dataDYB->GetBinContent(i+1)<<" "<<dataRENO->GetBinContent(i+1)<<" "<<dataNEOS->GetBinContent(i+1)<<" "<<dataPROS->GetBinContent(i+1)<<std::endl;
     }
   }

   //std::cout<<"DC11_preparing matrix "<<std::endl;
   //--------------------------------------------------------------------------------------------------------------------making matrix using data-----------------------------------------
   TMatrixD* covMat = this->prepareCovMatrix(nBins , fVec);

   covMat->Invert();

   TVectorD mulVec(*fData);
   mulVec *= (*covMat);

   Double_t currentResult = TMath::Abs(mulVec*(*fData));
   //std::cout<<"DC12_chi2 sans pull "<<currentResult<<std::endl;

   return (Double_t) currentResult ; 
}

//================================================================================================================================================5. Fill the Ev, Prediction===============
Double_t Sterile ::evaluate() const
{ 

Double_t matPart = this->FillEv(_pulls);//original FillEv is matPart

Double_t extraPull = this -> ExtraPull (_pulls);//same variable extraPull
Double_t tot = matPart + extraPull; //If needed, add pull terms here.

return tot;

}


Double_t Sterile ::ExtraPull (RooListProxy* _pulls) const
{
Double_t pullAdd = 0;
for(Int_t i=0;i<11;i++){
 pullAdd += TMath::Power(( ((RooAbsReal*)_pulls->at(i))->getVal() - (*pullCV)[i] ),2) / TMath::Power( (*pullUnc)[i],2) ;
    }
 //std::cout<<"DC13_extra pull penalty: "<<pullAdd<<std::endl;
 return pullAdd;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////=====================6. original FillEv + extraPall=========

TF1* Sterile:: GetIBDXsecFormula() const
{
  //TGraph* IBDXsec = new TGraph("data/IBDXsec.dat");
  TF1* IBDXsecF = new TF1("IBDXsecF","0.0952*(x)*( sqrt((x)*(x)-0.5*0.5))" ,1.8,10);
  return IBDXsecF;
}

TGraph* Sterile:: GetIBDXsecPoints() const
{
  TGraph* IBDXsec = new TGraph("data/IBDXsec.dat");
  //TF1* IBDXsec = new TF1("IBDXsec","0.0952*(x-0.8)*( sqrt((x-0.8)*(x-0.8)-0.5*0.5))" ,1.8,10);
  return IBDXsec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////======================7. IBDXsec ========================

std::vector<TH1D*> Sterile:: GetFluxPrediction(RooListProxy* _pulls, bool Iosc)  
{

  TGraph* meuller235;
  TGraph* meuller238;
  TGraph* meuller239;
  TGraph* meuller241;

  if(modelList.at(0)==fileLocation+"/data/mueller235.txt")
  //if(modelList.at(0)=="data/huber235.txt")
          meuller235 = new TGraph(modelList.at(0), "%lg %*lg %lg %*lg %*lg %*lg %*lg %*lg", "");
  else
          meuller235 = new TGraph(modelList.at(0), "%lg %lg %*lg", "");

  if(modelList.at(1)==fileLocation+"/data/mueller238.txt")
          meuller238 = new TGraph(modelList.at(1), "%lg %lg %*lg %*lg %*lg", "");
  else
          meuller238 = new TGraph(modelList.at(1), "%lg %lg %*lg", "");

  if(modelList.at(2)==fileLocation+"/data/mueller239241.txt")
  //if(modelList.at(2)=="data/huber239.txt")
          meuller239 = new TGraph(modelList.at(2), "%lg %*lg %lg %*lg %*lg %*lg %*lg", "");
  else
          meuller239 = new TGraph(modelList.at(2), "%lg %lg %*lg", "");

  if(modelList.at(3)==fileLocation+"/data/mueller239241.txt")
  //if(modelList.at(2)=="data/huber241.txt")
          meuller241 = new TGraph(modelList.at(3), "%lg %*lg %*lg %*lg %*lg %lg %*lg", "");
  else
          meuller241 = new TGraph(modelList.at(3), "%lg %lg %*lg", "");

  TGraph* IBDXsec = new TGraph(fileLocation+"/data/IBDXsec.dat");
  //TF1* IBDXsec = new TF1("IBDXsec","0.0952*(x-0.8)*( sqrt((x-0.8)*(x-0.8)-0.5*0.5))" ,1.8,10);

  //---------------------------------------------------------------------------------------------------------------------------------------------7.1 prediction using meuller model------  

  // at peak, DC 15,000  DYB 80,000  RENO 1,200  NEOS 24,750  ; with factor = 5,000, peaked with 1,400, thus scaling as following: 
  double rateFactorDC = 5000 * (15./1.); // 5000 * (15./1.4);
  double rateFactorDYB = 5000 * (80./1.); // 5000 * (80./1.4);
  double rateFactorRENO = 5000 * (12./10.); // 5000 * (12./14.);
  double rateFactorNEOS = 5000 * (24.75/1.); // 5000 * (24.75/1.4);
  double rateFactorPROS = 5000 * (24.75/1.); // 5000 * (24.75/1.4);

  TH1D* predDC = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predDYB = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predRENO = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predNEOS = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predPROS = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);

  std::cout<<"DC14_entered into preparePrediction "<<std::endl;

  //---------------------------------------------------------------------------------------------------------------------------------------------7.2 making prediction graph frame------ 

  for(Int_t i=0;i<33;i++){
    if((binEdge[i]+binEdge[i+1])/2.>1.8){
    //std::cout<<"bin edge and fission fraction "<<i<<" "<<binEdge[i]<<" "<<fissionFraction[i]<<" "<<((RooAbsReal*)_pulls->at(i+12))->getVal()<<std::endl;
    //std::cout<<"fission rates: "<<meuller235->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller238->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller239->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller241->Eval((binEdge[i]+binEdge[i+1])/2.)<<std::endl;

      double oscDC   = 1.;
      double oscDYB  = 1.;
      double oscRENO = 1.;
      double oscNEOS = 1.;
      double oscPROS = 1.;
      Double_t thisE_DC    = (((RooAbsReal*)_pulls->at(46))->getVal()-1.) + ((RooAbsReal*)_pulls->at(45))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_DYB   = (((RooAbsReal*)_pulls->at(48))->getVal()-1.) + ((RooAbsReal*)_pulls->at(47))->getVal() * (binEdge[i]+binEdge[i+1])/2.; 
      Double_t thisE_RENO  = (((RooAbsReal*)_pulls->at(50))->getVal()-1.) + ((RooAbsReal*)_pulls->at(49))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_NEOS  = (((RooAbsReal*)_pulls->at(52))->getVal()-1.) + ((RooAbsReal*)_pulls->at(51))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_PROS  = (((RooAbsReal*)_pulls->at(54))->getVal()-1.) + ((RooAbsReal*)_pulls->at(53))->getVal() * (binEdge[i]+binEdge[i+1])/2.;

      if (Iosc) 
      {
	  oscDC   = this->surv_Prob( (thisE_DC) , _pulls, baselineDC)  ;
	  oscDYB  = this->surv_Prob( (thisE_DYB) , _pulls, baselineDYB)  ;
 	  oscRENO = this->surv_Prob( (thisE_RENO) , _pulls, baselineRENO)  ;
	  oscNEOS = this->surv_Prob( (thisE_NEOS) , _pulls, baselineNEOS)  ;
          oscPROS = this->surv_Prob( (thisE_PROS) , _pulls, baselinePROS)  ;
      }

      //std::cout<<"oscillation probability "<<oscDC<<" "<<oscDYB<<" "<<oscRENO<<" "<<oscNEOS<<std::endl;
      predDC -> SetBinContent( i+1,  oscDC *  rateFactorDC * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[0] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[1] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[2] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[3] ));
      std::cout<<"DC15_predDC value in GetFlux "<<predDC->GetBinContent(i+1)<<std::endl;

      predDYB -> SetBinContent( i+1, oscDYB * rateFactorDYB * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[4] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[5] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[6] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[7] ));

      predRENO -> SetBinContent( i+1, oscRENO * rateFactorRENO * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[8] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[9] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[10] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[11] ));

      predNEOS -> SetBinContent( i+1, oscNEOS * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));

      predPROS -> SetBinContent( i+1, oscPROS * rateFactorPROS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * 1. *  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

    }
  }

  std::cout<<"DC16_in the middle of getFluxPrediction "<<std::endl;
  std::vector<TH1D*> predictionListF;
  predictionListF.push_back(predDC);
  predictionListF.push_back(predDYB);
  predictionListF.push_back(predRENO);
  predictionListF.push_back(predNEOS);
  predictionListF.push_back(predPROS);

  return predictionListF;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////--------------------7.3 Fill prediction graph--------------------------

std::vector<TH1D*> Sterile:: preparePrediction(RooListProxy* _pulls, bool Iosc) const
{
	
  //std::cout<<"DC17_in preparePrediction fMatrix integral "<<fMatrix->GetNcols()<<" "<<fMatrix->GetNrows()<<std::endl;

  TGraph* meuller235;
  TGraph* meuller238;
  TGraph* meuller239;
  TGraph* meuller241;

  if(modelList.at(0)==fileLocation+"/data/mueller235.txt")
          meuller235 = new TGraph(modelList.at(0), "%lg %*lg %lg %*lg %*lg %*lg %*lg %*lg", "");
  else
          meuller235 = new TGraph(modelList.at(0), "%lg %lg %*lg", "");

  if(modelList.at(1)==fileLocation+"/data/mueller238.txt")
          meuller238 = new TGraph(modelList.at(1), "%lg %lg %*lg %*lg %*lg", "");
  else
          meuller238 = new TGraph(modelList.at(1), "%lg %lg %*lg", "");

  if(modelList.at(2)==fileLocation+"/data/mueller239241.txt")
          meuller239 = new TGraph(modelList.at(2), "%lg %*lg %lg %*lg %*lg %*lg %*lg", "");
  else
          meuller239 = new TGraph(modelList.at(2), "%lg %lg %*lg", "");

  if(modelList.at(3)==fileLocation+"/data/mueller239241.txt")
          meuller241 = new TGraph(modelList.at(3), "%lg %*lg %*lg %*lg %*lg %lg %*lg", "");
  else
          meuller241 = new TGraph(modelList.at(3), "%lg %lg %*lg", "");


  TGraph* IBDXsec = new TGraph(fileLocation+"/data/IBDXsec.dat");
  //TF1* IBDXsec = new TF1("IBDXsec","0.0952*(x-0.8)*( sqrt((x-0.8)*(x-0.8)-0.5*0.5))" ,1.8,10);
  //TF1* IBDXsec = new TF1("IBDXsec","0.0952*(x)*( sqrt((x)*(x)-0.5*0.5))" ,1.8,10);

  // at peak, DC 15,000  DYB 80,000  RENO 1,200  NEOS 24,750  ; with factor = 5,000, peaked with 1,400, thus scaling as following: 
  double rateFactorDC = 5000 * (15./1.); // 5000 * (15./1.4);
  double rateFactorDYB = 5000 * (80./1.); // 5000 * (80./1.4);
  double rateFactorRENO = 5000 * (12./10.) * (165./12.); // 5000 * (12./14.) * (165./12.);
  double rateFactorNEOS = 5000 * (24.75/1.); // 5000 * (24.75/1.4);
  double rateFactorPROS = 5000 * (2/1.) * (2.5/2.0); // 5000 * (2/1.4) * (2.5/2.0); // based on rateFactorDYB

  //std::cout<<"DC18_important binning check in preparePrediction; "<<_nBins<<" "<<binEdge[0]<<" "<<binEdge[_nBins]<<std::endl;
  TH1D* predDC = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predDYB = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predRENO = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predNEOS = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  TH1D* predPROS = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);

  //std::cout<<"DC19_entered into preparePrediction "<<std::endl;
  for(Int_t i=0;i<33;i++){
    if((binEdge[i]+binEdge[i+1])/2.>1.8){
    //std::cout<<"bin edge and fission fraction "<<i<<" "<<binEdge[i]<<" "<<fissionFraction[i]<<" "<<((RooAbsReal*)_pulls->at(i+12))->getVal()<<std::endl;
    //std::cout<<"fission rates: "<<meuller235->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller238->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller239->Eval((binEdge[i]+binEdge[i+1])/2.)<<" "<<meuller241->Eval((binEdge[i]+binEdge[i+1])/2.)<<std::endl;

      double oscDC   = 1.;
      double oscDYB  = 1.;
      double oscRENO = 1.;
      double oscNEOS = 1.;
      double oscPROS = 1.;

      Double_t thisE_DC    = (((RooAbsReal*)_pulls->at(46))->getVal()-1.) + ((RooAbsReal*)_pulls->at(45))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_DYB   = (((RooAbsReal*)_pulls->at(48))->getVal()-1.) + ((RooAbsReal*)_pulls->at(47))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_RENO  = (((RooAbsReal*)_pulls->at(50))->getVal()-1.) + ((RooAbsReal*)_pulls->at(49))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_NEOS  = (((RooAbsReal*)_pulls->at(52))->getVal()-1.) + ((RooAbsReal*)_pulls->at(51))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      Double_t thisE_PROS  = (((RooAbsReal*)_pulls->at(54))->getVal()-1.) + ((RooAbsReal*)_pulls->at(53))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      
      //Double_t thisE = (((RooAbsReal*)_pulls->at(8))->getVal()-1.) + ((RooAbsReal*)_pulls->at(7))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      //baseline number used : DC 400  DYB 560  RENO 410.6  NEOS 20  PROSTPECT 7.9
      if (Iosc) 
      {
	  oscDC   = this->surv_Prob( (thisE_DC) , _pulls, baselineDC)  ;
	  oscDYB  = this->surv_Prob( (thisE_DYB) , _pulls, baselineDYB)  ;
 	  oscRENO = this->surv_Prob( (thisE_RENO) , _pulls, baselineRENO)  ;
	  oscNEOS = this->surv_Prob( (thisE_NEOS) , _pulls, baselineNEOS)  ;
          oscPROS = this->surv_Prob( (thisE_PROS) , _pulls, baselinePROS)  ;
      }

      if(equalIso){

        //std::cout<<"oscillation probability "<<oscDC<<" "<<oscDYB<<" "<<oscRENO<<" "<<oscNEOS<<" "<<oscPROS<<std::endl;
        predDC -> SetBinContent( i+1,  oscDC * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) *  rateFactorDC * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[0] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[1]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[2]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[3]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predDYB -> SetBinContent( i+1, oscDYB * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorDYB * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[4] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[5]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[6]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[7]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predRENO -> SetBinContent( i+1, oscRENO * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorRENO * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[8] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[9]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[10]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[11]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predNEOS -> SetBinContent( i+1, oscNEOS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predPROS -> SetBinContent( i+1, oscPROS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorPROS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * 1. /*all coming from 235U for PROSPECT*/ * ((RooAbsReal*)_pulls->at(i+12))->getVal()  ));

      }

      else{
        //std::cout<<"IBDXsec: "<<IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.)<<std::endl;
        //std::cout<<"oscillation probability "<<oscDC<<" "<<oscDYB<<" "<<oscRENO<<" "<<oscNEOS<<" "<<oscPROS<<std::endl;
        predDC -> SetBinContent( i+1,  oscDC * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) *  rateFactorDC * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[0] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[1] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[2] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[3] ));
        //std::cout<<"predDC value in preparePrediction "<<predDC->GetBinContent(i+1)<<" "<<dataDC->GetBinContent(i+1)<<std::endl;

        predDYB -> SetBinContent( i+1, oscDYB * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorDYB * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[4] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[5] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[6] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[7] ));
        //std::cout<<"predDYB value in preparePrediction "<<predDYB->GetBinContent(i+1)<<" "<<dataDYB->GetBinContent(i+1)<<std::endl;

        predRENO -> SetBinContent( i+1, oscRENO * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorRENO * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[8] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[9] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[10] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[11] ));
        //std::cout<<"predRENO value in preparePrediction "<<predRENO->GetBinContent(i+1)<<" "<<dataRENO->GetBinContent(i+1)<<std::endl;

        predNEOS -> SetBinContent( i+1, oscNEOS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));
        //std::cout<<"predNEOS value in preparePrediction "<<predNEOS->GetBinContent(i+1)<<" "<<dataNEOS->GetBinContent(i+1)<<std::endl;

        predPROS -> SetBinContent( i+1, oscPROS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorPROS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * 1. /*all coming from 235U for PROSPECT*/ * ((RooAbsReal*)_pulls->at(i+12))->getVal()  ));
        //std::cout<<"predPROS value in preparePrediction "<<predPROS->GetBinContent(i+1)<<" "<<dataPROS->GetBinContent(i+1)<<std::endl;
      }
    }
  }
//===================================================================================================================================================================7.4 prediction graph again====== 

  //std::cout<<"DC20_beginning of folding "<<std::endl;
  TH1D* fpredDC   = this->folding(predDC);
  TH1D* fpredDYB  = this->folding(predDYB);
  TH1D* fpredRENO = this->folding(predRENO);
  TH1D* fpredNEOS = this->folding(predNEOS);
  TH1D* fpredPROS = this->folding(predPROS);

  //std::cout<<"DC21_in the middle of preparePrediction "<<std::endl;
  std::vector<TH1D*> predictionList;
  predictionList.clear();
/*
  predictionList.push_back(predDC);
  predictionList.push_back(predDYB);
  predictionList.push_back(predRENO);
  predictionList.push_back(predNEOS);
*/
  //std::cout<<"DC22_pushing back "<<std::endl;
  predictionList.push_back(fpredDC);
  predictionList.push_back(fpredDYB);
  predictionList.push_back(fpredRENO);
  predictionList.push_back(fpredNEOS);
  predictionList.push_back(fpredPROS);

  //std::cout<<"DC23_pushed back"<<std::endl;
  // seems pushing back the prompt energy spectrum
  return predictionList;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////==============================7.5 print prediction with folding===


std::vector<TH1D*> Sterile:: prepareData(std::vector<TH1D*> tempPredList) const// 
{

  //dataDC = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  //dataDYB = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  //dataRENO = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);
  //dataNEOS = new TH1D("","",_nBins,binEdge[0],binEdge[_nBins]);

  TGraph* gradataDC   = new TGraph(fileLocation+"/data/dataDC.txt", "%*lg %lg %lg", "");
  TGraph* gradataDYB  = new TGraph(fileLocation+"/data/dataDYB.txt", "%*lg %lg %lg", "");
  TGraph* gradataRENO = new TGraph(fileLocation+"/data/dataRENO.txt", "%*lg %lg %lg", "");
  TGraph* gradataNEOS = new TGraph(fileLocation+"/data/dataNEOS.txt", "%*lg %lg %lg", "");
  TGraph* gradataPROS = new TGraph(fileLocation+"/data/dataPROS.txt", "%*lg %lg %lg", "");

  TH1D* predDC = tempPredList[0];
  TH1D* predDYB = tempPredList[1];
  TH1D* predRENO = tempPredList[2];
  TH1D* predNEOS = tempPredList[3];
  TH1D* predPROS = tempPredList[4];

  for(Int_t i=0;i<predDC->GetNbinsX();i++)
  {
    dataDC -> SetBinContent(i+1, predDC->GetBinContent(i+1)  * gradataDC->Eval(predDC->GetBinCenter(i+1)) );
    dataDYB -> SetBinContent(i+1,  predDYB->GetBinContent(i+1)  * gradataDYB->Eval(predDYB->GetBinCenter(i+1)) );
    dataRENO -> SetBinContent(i+1,  predRENO->GetBinContent(i+1)  * gradataRENO->Eval(predRENO->GetBinCenter(i+1)) );
    dataNEOS -> SetBinContent(i+1,  predNEOS->GetBinContent(i+1)  * gradataNEOS->Eval(predNEOS->GetBinCenter(i+1)) );
    dataPROS -> SetBinContent(i+1,  predPROS->GetBinContent(i+1)  * gradataPROS->Eval(predPROS->GetBinCenter(i+1)) );
    //std::cout<<"DC23.5 "<<predPROS->GetBinContent(i+1)<<" "<<predPROS->GetBinContent(i+1)  * gradataPROS->Eval(predPROS->GetBinCenter(i+1))<<std::endl;
  }

  std::vector<TH1D*> dataList;
  dataList.push_back(dataDC);
  dataList.push_back(dataDYB);
  dataList.push_back(dataRENO);
  dataList.push_back(dataNEOS);
  dataList.push_back(dataPROS);

  return dataList;

}

//===========================================================================================================================================================8. prepareData ========================

Double_t Sterile ::getPar(int i) {
(((RooAbsReal*)_pulls->at(i))->getVal());
}

RooRealVar* Sterile ::getParVar(int i) {
return ((RooRealVar*)_pulls->at(i));
}


void Sterile :: setSyst(Double_t syst){
_syst = syst;
}

void Sterile :: setdm2CV(Double_t dm2CV){
_dm2CV = dm2CV;
}

void Sterile :: setdm2Unc(Double_t dm2Unc){
_dm2Unc = dm2Unc;
}

void Sterile :: addSK(Bool_t wSK){
withSK = wSK;
}

void Sterile :: setAtmBaseline(Double_t AtmBaseline){
_AtmBaseline = AtmBaseline;
}

void Sterile :: setDensity(Double_t Density){
_Density = Density;
}

void Sterile :: setNBins(Double_t Bins){
_Bins= Bins;
}

void Sterile :: setTime(Double_t time){
_time= time;
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

void Sterile::SetBinning(TH1D* binHist)
{
for(Int_t i=0;i< binHist->GetNbinsX(); i++)
{
binEdge[i] = binHist->GetBinContent(i+1);
}
_nBins = binHist->GetNbinsX()-1;
}

void Sterile::SetFissionFraction(TH1D* fissionHist)
{
for(Int_t i=0; i< fissionHist->GetNbinsX();i++)
fissionFraction[i] = fissionHist->GetBinContent(i+1);
}

void Sterile::SetMatrixNameDC(TString matrixName)
{
fileNameDC = matrixName;
}

void Sterile::SetMatrixNameDYB(TString matrixName)
{
fileNameDYB = matrixName;
}

void Sterile::SetMatrixNameNEOS(TString matrixName)
{
fileNameNEOS = matrixName;
}

void Sterile::SetMatrixNamePROS(TString matrixName)
{
fileNamePROS = matrixName;
}


void Sterile::SetMatrixNameRENO(TString matrixName)
{
fileNameRENO = matrixName;
}

void Sterile::SetModelList(std::vector<TString> mlist)
{
modelList = mlist;
}

std::vector<TH1D*> Sterile:: GetCurrentPrediction()
{
return this->preparePrediction(this->getPullList(), true);
}

std::vector<TH1D*> Sterile:: GetCurrentData(std::vector<TH1D*> predAList)
{
return this->prepareData(predAList);
}

void Sterile:: fitSingleExp(TString input)
{
singleExp = input;
}

void Sterile::setBaselineDC(Double_t bl)
{
baselineDC = bl;
}
void Sterile::setBaselineDYB(Double_t bl)
{ 
baselineDYB = bl;
}
void Sterile::setBaselineRENO(Double_t bl)
{ 
baselineRENO = bl;
}
void Sterile::setBaselineNEOS(Double_t bl)
{ 
baselineNEOS = bl;
}
void Sterile::setBaselinePROS(Double_t bl)
{
baselinePROS = bl;
}

void Sterile::ifEqualIso(bool iso)
{
equalIso = iso;
}

bool Sterile::GetEqualIso()
{
return equalIso;
}

void Sterile::setFileLocation(TString fileL)
{
fileLocation = fileL;
}

void Sterile::setSysts(bool syst)
{
inSyst = syst;
}

bool Sterile::GetSysts()
{
return inSyst;
}

//////////////////////////////////////////////////////////////////////////////////////////////==========================================9. making short function in Sterile variable============

TMatrixD* Sterile:: ConversionMatrix(TString inputFile, TString inputTree)
{
TFile f(inputFile);
TTree* t = (TTree*)f.Get(inputTree);
//   double binEdge[100];
//   Int_t  _nBins;
//std::cout<<"DC24_ "<<_nBins<<std::endl;

fHist = new TH2D("","",_nBins,binEdge,_nBins,binEdge);
TH2D* cfHist = new TH2D("","",_nBins,0.5,0.5+_nBins*0.25,_nBins,0.5,0.5+_nBins*0.25);
//TH2D* fHist = new TH2D("","",34,0.5,9,34,0.5,9);

fMatrix = new TMatrixD(_nBins, _nBins);
TMatrixD* cfMatrix = new TMatrixD(_nBins, _nBins);
uMatrix = new TMatrixD(_nBins, _nBins);
unfoldingMatrix = new TMatrixD(_nBins, _nBins);

double nu, prompt;
t->SetBranchAddress("myNeutrinoEnergy_Th",&nu);
t->SetBranchAddress("myPromptEvisID",&prompt);

for(Int_t i=0;i<t->GetEntries();i++){
  t->GetEntry(i);
  fHist->Fill(nu, prompt);
  cfHist->Fill(nu, prompt);
  //std::cout<<" true vs. prompt "<<nu<<" "<<prompt<<std::endl;
}

for(Int_t i=0;i<fHist->GetNbinsX();i++){
  double summ = 0;
  for(Int_t j=0;j<fHist->GetNbinsY();j++){
     summ += fHist->GetBinContent(i+1,j+1);
  }
  //std::cout<<"DC25_ "<<summ<<std::endl;
  for(Int_t j=0;j<fHist->GetNbinsY();j++){
     if(summ>0) fHist->SetBinContent(i+1,j+1,fHist->GetBinContent(i+1,j+1)/summ);
     (*fMatrix)(j,i) = fHist->GetBinContent(i+1,j+1);
     (*cfMatrix)(j,i) = fHist->GetBinContent(i+1,j+1);
     (*uMatrix)(j,i) = fHist->GetBinContent(i+1,j+1);
  }
}

for(Int_t i=0;i<fHist->GetNbinsY();i++){
  double summ = 0;
  for(Int_t j=0;j<fHist->GetNbinsX();j++){
     summ += fHist->GetBinContent(j+1,i+1);
  }
  //std::cout<<"DC26_ "<<summ<<std::endl;
  for(Int_t j=0;j<fHist->GetNbinsX();j++){
     if(summ>0) fHist->SetBinContent(j+1,i+1,fHist->GetBinContent(j+1,i+1)/summ);
     (*unfoldingMatrix)(i,j) = fHist->GetBinContent(j+1,i+1);
  }
}

//std::cout<<"DC27_fHist integral "<<fHist->Integral()<<std::endl;

t->Delete();
f.Close();
return cfMatrix;
}

//////////////////////////////////////////////////////////////////////////////////////////////////===================================================10. making  a lot of graph=========

TH1D* Sterile:: folding(TH1D* input) const{
TH1D* output(input);
for(Int_t i=0;i<uMatrix->GetNrows();i++){	
  double sum = 0;
  for(Int_t j=0;j<input->GetNbinsX();j++){
    sum += (*uMatrix)(i,j)*input->GetBinContent(j+1);
  }	  
  output->SetBinContent(i+1,sum);
}
//std::cout<<"DC28_folded "<<std::endl;
return output;
}
