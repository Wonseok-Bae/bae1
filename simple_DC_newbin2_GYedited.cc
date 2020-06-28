/*
 *  t2k simple combined fit
 *
 *  Author: Guang Yang
 */
//May,18,2020 : Changing the range of ds and dm
//May,20,2020 : Scaling for Fitted plot
//May,30,2020 : 1000 oscillation in surv_Prob function
//June,3,2020 : Print out Scaling4 & PredNEOS
//June,6,2020 : Changing the range of Eshift scale
 
#include "simple_t2k_wonseok.hh"
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


Double_t prob[10000];//May,30,2020 : 1000 oscillation in surv_Prob function
double scaling44=123.456;//June,3,2020 : Print out Scaling4
double predNEOS2[100];
Double_t thisE_NEOS;

//Double_t binorder;//May,30,2020 : 1000 oscillation in surv_Prob function

/*
int newBin_DCDYB = 24; //60bin
int newBin_RENO = 26; //60bin
int newBin_NEOS = 61; //60bin
int newBin_PROS = 29; //60
double binWidth = 0.125; //60bin
int newBin_total = newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + newBin_PROS;

*/
//TF1* func = new TF1("spectrum","1" ,0.5,8);

using namespace std;

  Sterile ::Sterile (const char* name) 
  : RooAbsReal(name,name)
{

// there will be: pull 0-2 s12, s23, s13, pull 3, CP delta, pull 4-6 dm2(21,32,31), pull 7-10 numu, nue Xsec and numu, nue selections

  _pulls     = new RooListProxy("_pulls","_pulls",this);
  RooRealVar* Par1 = new RooRealVar("s12","par1",TMath::ASin(TMath::Sqrt(0.85))/2.,0,100);
  RooRealVar* Par2 = new RooRealVar("s23","par2",0,0,100); // TMath::ASin(TMath::Sqrt(0.95))/2.,0,100);
  RooRealVar* Par3 = new RooRealVar("s14","par3",0,0,1);// May,18,2020 0,0,100 -> 0,0,1
  RooRealVar* Par4 = new RooRealVar("delta","par4",-1.5,-10,10);
  RooRealVar* Par5 = new RooRealVar("dm21","par5",0.000075,-10,10);
  RooRealVar* Par6 = new RooRealVar("dm32","par6",0,0,10); // 0.00238,-10,10);
  RooRealVar* Par7 = new RooRealVar("dm41","par7",0,0,1000);// May,18,2020 0,0,10 -> 0,0,1000
  RooRealVar* Par8 = new RooRealVar("numuX","par8",1,0.,100);
  RooRealVar* Par9 = new RooRealVar("nueX","par9",1,0.,100);
  RooRealVar* Par10 = new RooRealVar("numuSel","par10",1,0.,100);
  RooRealVar* Par11 = new RooRealVar("esscalehist","par11",0,-2.2,2.2);// June,6,2020 -100,100 -> -2.2,2.2

  RooRealVar* Par12 = new RooRealVar("reactorVar1","par12",1,0,10) ;//it was `-10, 10'
  RooRealVar* Par13 = new RooRealVar("reactorVar2","par13",1,0,10) ;
  RooRealVar* Par14 = new RooRealVar("reactorVar3","par14",1,0,10) ;
  RooRealVar* Par15 = new RooRealVar("reactorVar4","par15",1,0,10) ;
  RooRealVar* Par16 = new RooRealVar("reactorVar5","par16",1,0,10) ;
  RooRealVar* Par17 = new RooRealVar("reactorVar6","par17",1,0,10) ;
  RooRealVar* Par18 = new RooRealVar("reactorVar7","par18",1,0,10) ;
  RooRealVar* Par19 = new RooRealVar("reactorVar8","par19",1,0,10) ;
  RooRealVar* Par20 = new RooRealVar("reactorVar9","par20",1,0,10) ;
  RooRealVar* Par21 = new RooRealVar("reactorVar10","par21",1,0,10) ;
  RooRealVar* Par22 = new RooRealVar("reactorVar11","par22",1,0,10) ;
  RooRealVar* Par23 = new RooRealVar("reactorVar12","par23",1,0,10) ;
  RooRealVar* Par24 = new RooRealVar("reactorVar13","par24",1,0,10) ;
  RooRealVar* Par25 = new RooRealVar("reactorVar14","par25",1,0,10) ;
  RooRealVar* Par26 = new RooRealVar("reactorVar15","par26",1,0,10) ;
  RooRealVar* Par27 = new RooRealVar("reactorVar16","par27",1,0,10) ;
  RooRealVar* Par28 = new RooRealVar("reactorVar17","par28",1,0,10) ;
  RooRealVar* Par29 = new RooRealVar("reactorVar18","par29",1,0,10) ;
  RooRealVar* Par30 = new RooRealVar("reactorVar19","par30",1,0,10) ;
  RooRealVar* Par31 = new RooRealVar("reactorVar20","par31",1,0,10) ;
  RooRealVar* Par32 = new RooRealVar("reactorVar21","par32",1,0,10) ;
  RooRealVar* Par33 = new RooRealVar("reactorVar22","par33",1,0,10) ;
  RooRealVar* Par34 = new RooRealVar("reactorVar23","par34",1,0,10) ;
  RooRealVar* Par35 = new RooRealVar("reactorVar24","par35",1,0,10) ;
  RooRealVar* Par36 = new RooRealVar("reactorVar25","par36",1,0,10) ;
  RooRealVar* Par37 = new RooRealVar("reactorVar26","par37",1,0,10) ;
  RooRealVar* Par38 = new RooRealVar("reactorVar27","par38",1,0,10) ;
  RooRealVar* Par39 = new RooRealVar("reactorVar28","par39",1,0,10) ;
  RooRealVar* Par40 = new RooRealVar("reactorVar29","par40",1,0,10) ;
  RooRealVar* Par41 = new RooRealVar("reactorVar30","par41",1,0,10) ;
  RooRealVar* Par42 = new RooRealVar("reactorVar31","par42",1,0,10) ;
  RooRealVar* Par43 = new RooRealVar("reactorVar32","par43",1,0,10) ;
  RooRealVar* Par44 = new RooRealVar("reactorVar33","par44",1,0,10) ;
  RooRealVar* Par45 = new RooRealVar("reactorVar34","par45",1,0,10) ;

  RooRealVar* Par46 = new RooRealVar("EscaleVar1DC", "par46",1,-10,10);
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
  dataDC = new TH1D("","dataDC",newBin_DCDYB, 0.5, 8.);//1.125, 6.875
  dataDYB = new TH1D("","dataDYB",newBin_DCDYB, 0.5, 8.);//1.125, 6.875
  dataRENO = new TH1D("","dataRENO",newBin_RENO, 0.5, 8.);//1.3, 6.7
  dataNEOS = new TH1D("","dataNEOS",newBin_NEOS, 0.5, 8.);//1.05, 8.5
  dataPROS = new TH1D("","dataPROS",newBin_PROS, 0.5, 8.);//0.89, 6.49
  //histForScale  = new TH1D("","histForScale",30, 0.5, 8.);//May,20,2020
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
  std::cout<<"check point9 ###########################################################################################################################"<<std::endl;
  TMatrixD* outMat = new TMatrixD(newBin_total , newBin_total);
  std::cout<<"check point9.05 ###########################################################################################################################"<<std::endl;

  if(inSyst){

      TMatrixD* fracMatDC = (TMatrixD*)fMatrixDC.Get("frac_approx");
      std::cout<<"check point9.06 ###########################################################################################################################"<<std::endl;

//CCC : Make the limit be something like ->GetNbinsX() - Edited
      for(Int_t i=0;i<fracTH2DC->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2DC->GetNbinsY();j++)
          {
              (*fracMatDC)(i,j) = (*fracMatDC)(i,j);
              //std::cout<<"check point9.07 ###########################################################################################################################"<<std::endl;
          }
      }
      fracMatDC->ResizeTo(newBin_DCDYB , newBin_DCDYB);

      std::cout<<"check point9.1 ###########################################################################################################################"<<std::endl;
      TMatrixD* fracMatDYB = new TMatrixD(100,100);
      TH2D* fracTH2DYB = (TH2D*)fMatrixDYB.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2DYB->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2DYB->GetNbinsY();j++)
          {
              (*fracMatDYB)(i+2,j+2) = fracTH2DYB->GetBinContent(i+1,j+1);
          }
      }
      fracMatDYB->ResizeTo(newBin_DCDYB,newBin_DCDYB);//need
      std::cout<<"check point9.2 ###########################################################################################################################"<<std::endl;

      TMatrixD* fracMatRENO = new TMatrixD(100,100);
      TH2D* fracTH2RENO = (TH2D*)fMatrixRENO.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2RENO->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2RENO->GetNbinsY();j++)
          {
              (*fracMatRENO)(i+2,j+2) = fracTH2RENO->GetBinContent(i+1,j+1);
          }
      }
      fracMatRENO->ResizeTo(newBin_RENO,newBin_RENO);//need

      TMatrixD* fracMatNEOS = new TMatrixD(100,100);
      TH2D* fracTH2NEOS = (TH2D*)fMatrixNEOS.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2NEOS->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2NEOS->GetNbinsY();j++)
          {
              (*fracMatNEOS)(i+2,j+2) = fracTH2NEOS->GetBinContent(i+1,j+1);
          }
      }
      fracMatNEOS->ResizeTo(newBin_NEOS,newBin_NEOS);//need

      TMatrixD* fracMatPROS = new TMatrixD(100,100);
      TH2D* fracTH2PROS = (TH2D*)fMatrixPROS.Get("hCorrelation_0.25MeV");
      for(Int_t i=0;i<fracTH2PROS->GetNbinsX();i++)
      {
          for(Int_t j=0;j<fracTH2PROS->GetNbinsY();j++)
          {
              (*fracMatPROS)(i+2,j+2) = fracTH2PROS->GetBinContent(i+1,j+1);
          }
      }
      fracMatPROS->ResizeTo(newBin_PROS,newBin_PROS);//need

      std::cout<<"check point9.3 ###########################################################################################################################"<<std::endl;
      (*fracMatDYB)(0,0) = fracTH2DYB->GetBinContent(1,1);
      (*fracMatDYB)(1,1) = fracTH2DYB->GetBinContent(1,1);
      (*fracMatRENO)(0,0) = fracTH2RENO->GetBinContent(1,1);
      (*fracMatRENO)(1,1) = fracTH2RENO->GetBinContent(1,1);
      (*fracMatNEOS)(0,0) = fracTH2NEOS->GetBinContent(1,1);
      (*fracMatNEOS)(1,1) = fracTH2NEOS->GetBinContent(1,1);
      (*fracMatPROS)(0,0) = fracTH2PROS->GetBinContent(1,1);
      (*fracMatPROS)(1,1) = fracTH2PROS->GetBinContent(1,1);
      std::cout<<"check point10 ###########################################################################################################################"<<std::endl;
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

      TVectorD* errList_DCDYB = new TVectorD(newBin_DCDYB);
      for(Int_t i = 0; i< newBin_DCDYB; i++)
      {
          (*errList_DCDYB)[i] = errlist_all[i];
      }
      TVectorD* errList_RENO = new TVectorD(newBin_RENO);
      for(Int_t i = 0; i< newBin_RENO; i++)
      {
          (*errList_RENO)[i] = errlist_all[i];
      }
      TVectorD* errList_NEOS = new TVectorD(newBin_NEOS);
      for(Int_t i = 0; i< newBin_NEOS; i++)
      {
          (*errList_NEOS)[i] = errlist_all[i];
      }
      TVectorD* errList_PROS = new TVectorD(newBin_PROS);
      for(Int_t i = 0; i< newBin_PROS; i++)
      {
          (*errList_PROS)[i] = errlist_all[i];
      }
  

      //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      for(Int_t i = 0; i< newBin_DCDYB; i++)//need
      {
        for(Int_t j =0 ;j<newBin_DCDYB; j++)//need
        { 
            //std::cout<<(*fracMat)(i,j)<<std::endl; 
            //if((*fracMatDC)(4,4) > 0.5 )
                (*outMat)(i,j) = (*fracMatDC)(i,j) * (*errList_DCDYB)[i] * (*errList_DCDYB)[j] * (*fVec)[i] * (*fVec)[j];
	    //else      
	    //    (*outMat)(i,j) = (*fracMatDC)(i,j) * (*fVec)[i] * (*fVec)[j];//need to check
        }
      }

      for(Int_t i = newBin_DCDYB; i< newBin_DCDYB + newBin_DCDYB; i++)
      {
	      // CCC : a bug here, j should go larger - Edited
        for(Int_t j = newBin_DCDYB ;j< newBin_DCDYB + newBin_DCDYB; j++) 
        {
	    //std::cout<<"in loading second matrix "<<std::endl;
	    //std::cout<<(*fracMatDYB)(0,0)<<std::endl;
	    //if((*fracMatDYB)(4,4) > 0.5)
	        (*outMat)(i,j) = (*fracMatDYB)(i-newBin_DCDYB,j-newBin_DCDYB) * (*errList_DCDYB)[i-newBin_DCDYB] * (*errList_DCDYB)[j-newBin_DCDYB]  * (*fVec)[i] * (*fVec)[j];
	    //else
            //    (*outMat)(i,j) = (*fracMatDYB)(i-nBins,j-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }
      //std::cout<<"in middle of matrix preparation "<<std::endl;

      for(Int_t i = newBin_DCDYB+newBin_DCDYB; i<newBin_DCDYB + newBin_DCDYB + newBin_RENO; i++)
      {
        for(Int_t j = newBin_DCDYB+newBin_DCDYB ;j < newBin_DCDYB + newBin_DCDYB + newBin_RENO; j++) 
        {
	    //if((*fracMatRENO)(4,4) > 0.5)
	        (*outMat)(i,j) = (*fracMatRENO)(i-newBin_DCDYB-newBin_DCDYB,j-newBin_DCDYB-newBin_DCDYB) * (*errList_RENO)[i-newBin_DCDYB-newBin_DCDYB] * (*errList_RENO)[j-newBin_DCDYB-newBin_DCDYB]  * (*fVec)[i] * (*fVec)[j];		
	    //else
       	    //    (*outMat)(i,j) = (*fracMatRENO)(i-nBins-nBins,j-nBins-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }

      for(Int_t i = newBin_DCDYB + newBin_DCDYB + newBin_RENO; i< newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS; i++)
      {
        for(Int_t j = newBin_DCDYB + newBin_DCDYB + newBin_RENO ;j< newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS; j++) 
        {
	    //if((*fracMatNEOS)(4,4) > 0.5)
                (*outMat)(i,j) = (*fracMatNEOS)(i-newBin_DCDYB - newBin_DCDYB - newBin_RENO,j-newBin_DCDYB - newBin_DCDYB - newBin_RENO) * (*errList_NEOS)[i-newBin_DCDYB - newBin_DCDYB - newBin_RENO] * (*errList_NEOS)[j-newBin_DCDYB - newBin_DCDYB - newBin_RENO]  * (*fVec)[i] * (*fVec)[j];
            //else	    
      	    //    (*outMat)(i,j) = (*fracMatNEOS)(i-nBins-nBins-nBins,j-nBins-nBins-nBins) * (*fVec)[i] * (*fVec)[j];
        }
      }

      //std::cout<<"Doing PROSPECT matrix setup "<<std::endl;
      //std::cout<<"DC1_Doing PROSPECT matrix setup "<<std::endl;
      for(Int_t i = newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS; i< newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + newBin_PROS; i++)
      {
        for(Int_t j = newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS ;j< newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + newBin_PROS; j++)
        {
	    //std::cout<<(*fracMatPROS)(i-4*nBins,j-4*nBins)<<" "<<(*errList)[i-4*nBins]<<" "<<(*fVec)[i]<<" "<<(*fVec)[j]<<std::endl;
            (*outMat)(i,j) = (*fracMatPROS)(i-newBin_DCDYB - newBin_DCDYB - newBin_RENO - newBin_NEOS,j-newBin_DCDYB - newBin_DCDYB - newBin_RENO - newBin_NEOS) * (*errList_PROS)[i-newBin_DCDYB - newBin_DCDYB - newBin_RENO - newBin_NEOS] * (*errList_PROS)[j-newBin_DCDYB - newBin_DCDYB - newBin_RENO - newBin_NEOS]  * (*fVec)[i] * (*fVec)[j];
        }
      }
  }
  //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  for(Int_t i = 0; i< newBin_total ; i++)//need
  {
    (*outMat)(i,i) += (*fVec)[i] ;//need to check
    if((*outMat)(i,i) == 0) (*outMat)(i,i) += 0.0000000001;
  }
  std::cout<<"check point11 ###########################################################################################################################"<<std::endl;
//std::cout<<"matrix sum "<<outMat ->Sum()<<std::endl;
//std::cout<<"DC2_matrix sum "<<outMat ->Sum()<<std::endl;
return outMat ;
}

//============================================================================================================================================3. making Matrix using error List======
//May,30,2020 : 1000 oscillation in surv_Prob function
Double_t Sterile::surv_Prob(Double_t E, RooListProxy* _pulls, Double_t L, TF1* func) const //survival probability. energy, pulls(theta, mass_differance, CP angle) length.
{  
  //std::cout<<" E : "<<E<<std::endl; 

  Double_t prob_sum = 0;
  Double_t prob_average =0;
  Double_t prob_E = E;
  
  double delta_31_fit=0;
  double survival_prob_fit=0;
  
  if(L==20)//=NEOS
  {     
   
        prob_E = prob_E - 0.125 - 0.00025;
        
        for(Int_t i = 0; i < 1000 ; i++)
        {
        prob_E = prob_E + 0.00025;
        Double_t delta_31 = ((RooAbsReal*)_pulls->at(6))->getVal()* (L/prob_E)*1.27 ;
        prob[i] = (1 - ((RooAbsReal*)_pulls->at(2))->getVal() *  TMath::Power(TMath::Sin(delta_31),2));//*weight[weight_number];
        prob_sum = prob_sum + prob[i];
        //std::cout<<i<<" "<<prob_E<<" "<<weight_number<<endl;
        }
                     
        prob_average = prob_sum/1000;
        //std::cout<<" Input E : "<<E<<" prob_average : "<<prob_average<<endl;
        	     
  }
  
  return prob_average;       
}

//============================================================================================================================================4. Survival Probaability

Double_t Sterile ::FillEv( RooListProxy* _pulls ) const 
{

   //std::cout<<"in FillEv() "<<std::endl;
   int nBins = _nBins;

   std::vector<TH1D*> tempPredList = this->preparePrediction(_pulls, true);
   //std::cout<<"filled in new pediction "<<std::endl;

   //std::vector<TH1D*> tempDataList = this->prepareData();
   TH1D* predDC = tempPredList[0];
   TH1D* predDYB = tempPredList[1];
   TH1D* predRENO = tempPredList[2];
   TH1D* predNEOS = tempPredList[3]; 
   TH1D* predPROS = tempPredList[4];
   /*
   for(Int_t i=0;i<nBins;i++){
   cout<<" TEST FillEv : ine 461 i "<<i<<" predNEOS->GetBinContent(i+1) : "<<predNEOS->GetBinContent(i+1)<<endl;
   }
   *///June,3,2020 : Print out Scaling4
   std::cout<<"check point5 ###########################################################################################################################"<<std::endl;
   TVectorD* fVec = new TVectorD(newBin_total);//Up to date prediction. current prediction
   TVectorD* fData = new TVectorD(newBin_total);

   TH1D* tempVec[5]; 
   TH1D* tempDat[5]; 
   for(Int_t i=0;i<5;i++){
// CCC : binning needs to be changed here - the largest bin is 61(NEOS) so, isn't it 100 is enough?	   
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
   std::cout<<"check point6 ###########################################################################################################################"<<std::endl;
   for(Int_t i=0;i<newBin_DCDYB;i++){
   (*fVec)[i]               = predDC->GetBinContent(i+1) ;
   tempVec[0] -> SetBinContent(i+1, (*fVec)[i]);
   (*fData)[i]             = dataDC->GetBinContent(i+1)   ;
   tempDat[0] -> SetBinContent(i+1, (*fData)[i]);
   }

   for(Int_t i=0;i<newBin_DCDYB;i++){
   (*fVec)[newBin_DCDYB + i]       = predDYB->GetBinContent(i+1) ;
   tempVec[1] -> SetBinContent(i+1, (*fVec)[newBin_DCDYB + i]);
   (*fData)[newBin_DCDYB + i]     = dataDYB->GetBinContent(i+1)  ;
   tempDat[1] -> SetBinContent(i+1, (*fData)[newBin_DCDYB + i]);
   }

   for(Int_t i=0;i<newBin_RENO;i++){
   (*fVec)[newBin_DCDYB + newBin_DCDYB + i]   = predRENO->GetBinContent(i+1) ;
   tempVec[2] -> SetBinContent(i+1, (*fVec)[newBin_DCDYB + newBin_DCDYB + i]);
   (*fData)[newBin_DCDYB + newBin_DCDYB + i] = dataRENO->GetBinContent(i+1) ;
   tempDat[2] -> SetBinContent(i+1, (*fData)[newBin_DCDYB + newBin_DCDYB + i]);
   }

   for(Int_t i=0;i<newBin_NEOS;i++){
   (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i]   = predNEOS->GetBinContent(i+1) ;
   tempVec[3] -> SetBinContent(i+1, (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i]);
   (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] = dataNEOS->GetBinContent(i+1) ;
   tempDat[3] -> SetBinContent(i+1, (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i]);
   }

   for(Int_t i=0;i<newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS ;i++){
   (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i]   = predPROS->GetBinContent(i+1) ;
   tempVec[4] -> SetBinContent(i+1, (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i]);
   (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] = dataPROS->GetBinContent(i+1) ;
   tempDat[4] -> SetBinContent(i+1, (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i]);
   }

   /*	 
         //Double_t thisE = (((RooAbsReal*)_pulls->at(8))->getVal()-1.) + ((RooAbsReal*)_pulls->at(7))->getVal() * predDC->GetBinCenter(i+1);
         (*fVec)[i]               = predDC->GetBinContent(i+1) ; // this->surv_Prob( (thisE) , _pulls, 400)  ; //need to check
         (*fVec)[newBin + i]       = predDYB->GetBinContent(i+1) ; // this->surv_Prob( (thisE) , _pulls, 560)  ;
         (*fVec)[2 * newBin + i]   = predRENO->GetBinContent(i+1) ; // this->surv_Prob( (thisE) , _pulls, 410.6)  ;
         (*fVec)[3 * newBin + i]   = predNEOS->GetBinContent(i+1) ; // this->surv_Prob( (thisE) , _pulls, 20)  ;
         (*fVec)[4 * newBin + i]   = predPROS->GetBinContent(i+1) ;
         tempVec[0] -> SetBinContent(i+1, (*fVec)[i]);
	 tempVec[1] -> SetBinContent(i+1, (*fVec)[newBin + i]);
	 tempVec[2] -> SetBinContent(i+1, (*fVec)[2 * newBin + i]);
	 tempVec[3] -> SetBinContent(i+1, (*fVec)[3 * newBin + i]);
         tempVec[4] -> SetBinContent(i+1, (*fVec)[4 * newBin + i]);
   }
   //std::cout<<"prepared new prediction"<<std::endl;
         
   for(Int_t i=0;i<newBin;i++){
	//std::cout<<dataDC->GetBinContent(i+1)<<" "<<dataDYB->GetBinContent(i+1)<<std::endl;
   	(*fData)[i]             = dataDC->GetBinContent(i+1)   ;//need to check
        (*fData)[newBin + i]     = dataDYB->GetBinContent(i+1)  ;
        (*fData)[2 * newBin + i] = dataRENO->GetBinContent(i+1) ;
        (*fData)[3 * newBin + i] = dataNEOS->GetBinContent(i+1) ;
        (*fData)[4 * newBin + i] = dataPROS->GetBinContent(i+1) ;
        tempDat[0] -> SetBinContent(i+1, (*fData)[i]);
        tempDat[1] -> SetBinContent(i+1, (*fData)[newBin + i]);
        tempDat[2] -> SetBinContent(i+1, (*fData)[2 * newBin + i]);
        tempDat[3] -> SetBinContent(i+1, (*fData)[3 * newBin + i]);
        tempDat[4] -> SetBinContent(i+1, (*fData)[4 * newBin + i]);
   }
   */
   std::cout<<"check point7 ###########################################################################################################################"<<std::endl;
   //std::cout<<"data ready also "<<std::endl;
   //--------------------------------------------------------------------------------------------------------------------------------Data------------------------------------

   // scale to same total rate, doing shape only analysis 
   double scaling1 = tempDat[0]->Integral() / tempVec[0]->Integral();
   double scaling2 = tempDat[1]->Integral() / tempVec[1]->Integral();
   double scaling3 = tempDat[2]->Integral() / tempVec[2]->Integral();
   double scaling4 = tempDat[3]->Integral() / tempVec[3]->Integral();//june
   //std::cout<<" tempDat[3]->Integral() : "<<tempDat[3]->Integral()<<" tempVec[3]->Integral() : "<<tempVec[3]->Integral()<<" scaling4 : " << scaling4 << endl;
   //June,3,2020 : Print out Scaling4
   double scaling5 = tempDat[4]->Integral() / tempVec[4]->Integral();

   for(Int_t i=0;i<newBin_DCDYB;i++){
      (*fData)[i]             = 0; //dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  ; //need
   }
   for(Int_t i=0;i<newBin_DCDYB;i++){
      (*fData)[newBin_DCDYB + i]     = 0; //dataDYB->GetBinContent(i+1)  - (*fVec)[nBins + i] * scaling2;
   }
   for(Int_t i=0;i<newBin_RENO;i++){
      (*fData)[newBin_DCDYB + newBin_DCDYB + i] = 0; //dataRENO->GetBinContent(i+1) - (*fVec)[2 * nBins + i] * scaling3 ;
   }
   for(Int_t i=0;i<newBin_NEOS;i++){
      (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] = 0; //dataNEOS->GetBinContent(i+1) - (*fVec)[3 * nBins + i] * scaling4;
   }
// CCC : should be newBin_PROS - Edited
   for(Int_t i=0;i<newBin_PROS;i++){
      (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] = 0;
   }

   if (singleExp.Contains("DC")){
     //std::cout<<"DC5_Adding DC "<<std::endl;
     for(Int_t i=0;i<newBin_DCDYB;i++){//need
        (*fData)[i]             = dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  ;
     }
   }
   if (singleExp.Contains("DYB")){
     //std::cout<<"DC6_Adding DYB "<<std::endl;
     for(Int_t i=0;i<newBin_DCDYB;i++){
        (*fData)[newBin_DCDYB + i]     = dataDYB->GetBinContent(i+1)  - (*fVec)[newBin_DCDYB + i] * scaling2;
     }
   }
   if (singleExp.Contains("RENO")){
     //std::cout<<"DC7_Adding RENO "<<std::endl;
     // CCC : should be newBin_RENO - Edited
     for(Int_t i=0;i<newBin_DCRENO;i++){
        (*fData)[newBin_DCDYB + newBin_DCDYB + i] = dataRENO->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + i] * scaling3 ;
     }
   }
   double SumfVec = 0.;//May,20,2020
   if (singleExp.Contains("NEOS")){
     //std::cout<<"DC8_Adding NEOS "<<std::endl;
     for(Int_t i=0;i<newBin_NEOS;i++){
	// CCC : should be newBin_DCDYB + newBin_DCDYB + newBin_RENO, check following three lines carefully! - Edited
        (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] = dataNEOS->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] * scaling4;
        SumfVec += (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO  + i] * scaling4;//May,20,2020
  
        (*testVec)[i]=(*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO  + i] * scaling4; //May,21,2020
        //std::cout<<"SIMPLE_DC "<<(*testVec)[i]<<endl;
     }
   }
   //std::cout<<"dataNEOS->Integral() : "<<dataNEOS->Integral() <<endl; //May,20,2020
   //std::cout<<"*fVec's Integral : "<< SumfVec <<endl;//May,20,2020
   
   if (singleExp.Contains("PROS")){
     //std::cout<<"DC9_Adding PROSPECT "<<std::endl;
     // CCC : should be newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS, check it carefully! -Edited
     for(Int_t i=0;i<newBin_PROS;i++){
        (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] = dataPROS->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] * scaling5;
     }
   }
   if (singleExp.Contains("ALL")){
     for(Int_t i=0;i<newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + newBin_PROS ;i++){ 
     //std::cout<<"DC10_Adding ALL at one time "<<std::endl;
        (*fData)[i]             = TMath::Abs( dataDC->GetBinContent(i+1)   - (*fVec)[i] * scaling1  );
        (*fData)[newBin_DCDYB + i]     = TMath::Abs( dataDYB->GetBinContent(i+1)  - (*fVec)[newBin_DCDYB + i] * scaling2 );
	(*fData)[newBin_DCDYB + newBin_DCDYB + i] = TMath::Abs( dataRENO->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + i] * scaling3 );
	(*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] = TMath::Abs( dataNEOS->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + i] * scaling4 );
        (*fData)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] = TMath::Abs( dataPROS->GetBinContent(i+1) - (*fVec)[newBin_DCDYB + newBin_DCDYB + newBin_RENO + newBin_NEOS + i] * scaling5 );
	
     }
   }
   std::cout<<"check point8 ###########################################################################################################################"<<std::endl;

   //for(Int_t i=0;i<nBins;i++) (*testVec)[i]=(*fVec)[3 * nBins + i] * scaling4; //May,21,2020



   /* 
   //May,18,2020
      std::vector<double> wonseokPreparePrediction(TVectorD* fVec);
   {
   	std::cout<<"This function is working"<<endl;
        for(Int_t i=0;i<nBins;i++){
        
        std::cout<<(*fVec)[3 * nBins + i] * scaling4<<endl;
        
        //histForScale->SetBinContent(i,(*fVec)[3 * nBins + i] * scaling4);
        
        //std::vector<double> histForScale; 
	//histForScale.push_back((*fVec)[3 * nBins + i] * scaling4);
        //for(int n : v) {
        //std::cout << n << '\n';
        //}

	}
        return histForScale;
     
        
   }
   */

   //std::cout<<"DC11_preparing matrix "<<std::endl;
   //--------------------------------------------------------------------------------------------------------------------making matrix using data-----------------------------------------
   TMatrixD* covMat = this->prepareCovMatrix(newBin , fVec);// fVec=Up to date prediction, current prediction 
    /*
    TFile* outputFile3 = new TFile("outputFigs3.root","RECREATE");// NEW######
    TH2D * covMat2D = new TH2D("TMatrixD","",covMat->GetNcols(),covMat->GetColLwb(),1+covMat->GetColUpb(),covMat->GetNrows(),covMat->GetRowLwb(),1+covMat->GetRowUpb());
    for(int i = covMat->GetColLwb(); i<1+covMat->GetColUpb(); i++)
    {
         for(int j = covMat->GetRowLwb(); j<1+covMat->GetRowUpb(); j++)
         {
                 covMat2D->SetBinContent(i,j,(*covMat)(i,j));
         }
    }
    covMat2D->Write("covMatrix2D");
    outputFile3 -> Close();
    */
   std::cout<<"check point12 ###########################################################################################################################"<<std::endl;
   covMat->Invert();

   TVectorD mulVec(*fData);
   mulVec *= (*covMat);

   Double_t currentResult = TMath::Abs(mulVec*(*fData));
   //std::cout<<"DC12_chi2 sans pull "<<currentResult<<std::endl;
 
   scaling44 = scaling4;//June,3,2020 : Print out Scaling4 
   //std::cout<<" scaling44-1 : "<<scaling44<<std::endl;//June,3,2020 : Print out Scaling4
   std::cout<<"check point12.1 ###########################################################################################################################"<<std::endl;
   return (Double_t) currentResult ; 
}

//================================================================================================================================================5. Fill the Ev, Prediction===============
Double_t Sterile ::evaluate() const
{ 

Double_t matPart = this->FillEv(_pulls);//original FillEv is matPart

Double_t extraPull = this -> ExtraPull (_pulls);//same variable extraPull
Double_t tot = matPart + extraPull; //If needed, add pull terms here.

return tot;

std::cout<<"check point12.2 ###########################################################################################################################"<<std::endl;

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

  TH1D* predDC = new TH1D("","",newBin_DCDYB,binEdge[0],binEdge[newBin_DCDYB]);//need
  TH1D* predDYB = new TH1D("","",newBin_DCDYB,binEdge[0],binEdge[newBin_DCDYB]);
  TH1D* predRENO = new TH1D("","",newBin_RENO,binEdge[0],binEdge[newBin_RENO]);
  TH1D* predNEOS = new TH1D("","",newBin_NEOS,binEdge[0],binEdge[newBin_NEOS]);
  TH1D* predPROS = new TH1D("","",newBin_PROS,binEdge[0],binEdge[newBin_PROS]);
 
  //---------------------------------------------------------------------------------------------------------------------------------------------7.2 making prediction graph frame------ 

  for(Int_t i=0;i<newBin+3;i++){//need
    if(((binEdge[i]+binEdge[i+1])/2.>1.8)&&(binEdge[i+1]>0.01)){
    //if((binEdge[i]+binEdge[i+1])/2.>1.8){
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
	  oscDC   = this->surv_Prob( (thisE_DC) , _pulls, baselineDC, fitting_function)  ;
	  oscDYB  = this->surv_Prob( (thisE_DYB) , _pulls, baselineDYB, fitting_function)  ;
 	  oscRENO = this->surv_Prob( (thisE_RENO) , _pulls, baselineRENO, fitting_function)  ;
	  oscNEOS = this->surv_Prob( (thisE_NEOS) , _pulls, baselineNEOS, fitting_function)  ;
          oscPROS = this->surv_Prob( (thisE_PROS) , _pulls, baselinePROS, fitting_function)  ;
      }
      //std::cout<< "i : " <<i<< " oscNEOS : "<<oscNEOS<<endl;

      //std::cout<<"oscillation probability "<<oscDC<<" "<<oscDYB<<" "<<oscRENO<<" "<<oscNEOS<<std::endl;
      predDC -> SetBinContent( i+1,  oscDC *  rateFactorDC * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[0] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[1] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[2] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[3] ));
      //std::cout<<"predDC value in GetFlux "<<predDC->GetBinContent(i+1)<<std::endl;

      predDYB -> SetBinContent( i+1, oscDYB * rateFactorDYB * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[4] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[5] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[6] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[7] ));

      predRENO -> SetBinContent( i+1, oscRENO * rateFactorRENO * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[8] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[9] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[10] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[11] ));

      predNEOS -> SetBinContent( i+1, oscNEOS * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));
      std::cout<<" predNEOS TEST in GetFluxPrediction "<< predNEOS->GetBinContent(i+1) <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
      //June,3,2020 : Print out Scaling4 & PredNEOS
      predPROS -> SetBinContent( i+1, oscPROS * rateFactorPROS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * 1. *  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

    }
  }

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
  std::cout<<"check point0.5 ###########################################################################################################################"<<std::endl;	
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

  TH1D* predDC = new TH1D("","",newBin_DCDYB,binEdge[0],binEdge[newBin_DCDYB]);
  TH1D* predDYB = new TH1D("","",newBin_DCDYB,binEdge[0],binEdge[newBin_DCDYB]);
  TH1D* predRENO = new TH1D("","",newBin_RENO,binEdge[0],binEdge[newBin_RENO]);
  TH1D* predNEOS = new TH1D("","",newBin_NEOS,binEdge[0],binEdge[newBin_NEOS]);
  TH1D* predPROS = new TH1D("","",newBin_PROS,binEdge[0],binEdge[newBin_PROS]);
  std::cout<<"check point1 ###########################################################################################################################"<<std::endl;
  for(Int_t i=0;i<newBin+3;i++){//need
    if(((binEdge[i]+binEdge[i+1])/2.>1.8)&&(binEdge[i+1]>0.01)){
      //std::cout<<"binEdge[i+1] : "<<binEdge[i+1]<<endl;
     //if(binEdge[i+1]>0.01)
    //if((binEdge[i]+binEdge[i+1])/2.>0.){
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
      thisE_NEOS  = (((RooAbsReal*)_pulls->at(52))->getVal()-1.) + ((RooAbsReal*)_pulls->at(51))->getVal() * (binEdge[i]+binEdge[i+1])/2.;  //June
      //std::cout<<" i : "<<i<<" binEdge[i] : "<<binEdge[i]<<" binEdge[i+1] : "<<binEdge[i+1]<< " (binEdge[i]+binEdge[i+1])/2. : "<<(binEdge[i]+binEdge[i+1])/2.<<" thisE_NEOS : "<<thisE_NEOS<<endl;
      Double_t thisE_PROS  = (((RooAbsReal*)_pulls->at(54))->getVal()-1.) + ((RooAbsReal*)_pulls->at(53))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      
      //Double_t thisE = (((RooAbsReal*)_pulls->at(8))->getVal()-1.) + ((RooAbsReal*)_pulls->at(7))->getVal() * (binEdge[i]+binEdge[i+1])/2.;
      //baseline number used : DC 400  DYB 560  RENO 410.6  NEOS 20  PROSTPECT 7.9
      if (Iosc) 
      {
	  oscDC   = 1. ; //this->surv_Prob( (thisE_DC) , _pulls, baselineDC, fitting_function)  ;
	  oscDYB  = 1. ; //this->surv_Prob( (thisE_DYB) , _pulls, baselineDYB, fitting_function)  ;
 	  oscRENO = 1. ; //this->surv_Prob( (thisE_RENO) , _pulls, baselineRENO, fitting_function)  ;
	  oscNEOS = 1. ; //this->surv_Prob( (thisE_NEOS) , _pulls, baselineNEOS, fitting_function)  ;
          oscPROS = 1. ; //this->surv_Prob( (thisE_PROS) , _pulls, baselinePROS, fitting_function)  ;
      }
	//std::cout<< "i : " <<i<< " oscNEOS : "<<oscNEOS<<endl;
      if(equalIso){

	// CCC : you need to set oscXXX all to 1 if you want to oscillate the whole spectrum below. - Edited
	      
        //std::cout<<"oscillation probability "<<oscDC<<" "<<oscDYB<<" "<<oscRENO<<" "<<oscNEOS<<" "<<oscPROS<<std::endl;
        predDC -> SetBinContent( i+1,  oscDC * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) *  rateFactorDC * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[0] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[1]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[2]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[3]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predDYB -> SetBinContent( i+1, oscDYB * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorDYB * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[4] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[5]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[6]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[7]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predRENO -> SetBinContent( i+1, oscRENO * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorRENO * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[8] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[9]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[10]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[11]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));

        predNEOS -> SetBinContent( i+1, oscNEOS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15]*  ((RooAbsReal*)_pulls->at(i+12))->getVal() ));
        std::cout<<" predNEOS TEST in preparePrediction equalIso=1 "<< predNEOS->GetBinContent(i+1) <<"###########################################"<<std::endl;
        //June,3,2020 : Print out Scaling4 & PredNEOS
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

        //predNEOS -> SetBinContent( i+1, oscNEOS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));
        predNEOS -> SetBinContent( i+1, oscNEOS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));
        predNEOS2[i]= 1 * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorNEOS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] *  ((RooAbsReal*)_pulls->at(i+12))->getVal() + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] );
        //std::cout<<" i : "<<i<<" predNEOS2 : "<<predNEOS2[i]<<endl;
        //predNEOS -> SetBinContent( i+1, 1 * rateFactorNEOS ); //(meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[12] + meuller238->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[13] + meuller239->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[14] + meuller241->Eval((binEdge[i]+binEdge[i+1])/2.) * fissionFraction[15] ));
        predPROS -> SetBinContent( i+1, oscPROS * IBDXsec->Eval((binEdge[i]+binEdge[i+1])/2.) * rateFactorPROS * (meuller235->Eval((binEdge[i]+binEdge[i+1])/2.) * 1. /*all coming from 235U for PROSPECT*/ * ((RooAbsReal*)_pulls->at(i+12))->getVal()  ));
        //std::cout<<"E "<<(binEdge[i]+binEdge[i+1])/2.<<" predPROS value in preparePrediction "<<predPROS->GetBinContent(i+1)<<" "<<dataPROS->GetBinContent(i+1)<<"   -- fission pull value: "<<((RooAbsReal*)_pulls->at(i+12))->getVal()<<std::endl;
      }
    }
  }
    std::cout<<"check point2 ###########################################################################################################################"<<std::endl; 
    TFile* outputFile3 = new TFile("outputFigs3.root","RECREATE");// NEW######
    TH1D * forFittingFunction = new TH1D("forFittingFunction","title",newBin,0.5,8);
    for(Int_t i=0; i<newBin; i++)
    {
    	//std::cout<<" i : "<<i<<" predNEOS2 : "<<predNEOS2[i+4]<<endl;
        forFittingFunction->SetBinContent(i, predNEOS->GetBinContent(i) );//oscSpectrum-30bin-3.root
        //std::cout<<" outputFig3.root "<<forFittingFunction->GetBinContent(i)<<std::endl;
    }
    forFittingFunction->Write("forFittingFunction");
    outputFile3 -> Close();
    std::cout<<"check point3 ###########################################################################################################################"<<std::endl;
    double E2[2500];
    double number_of_neutrino[2500];
    double total_number_of_neutrino=0;
    double weight[250];
    double delta_31_fit=0;
    double survival_prob_fit=0;
    double L=baselineNEOS;

    //Part 1. Creating Fitting Function of predNEOS TH1D
    TFile inputfile("./outputFigs3.root","READ");
    TFile inputfile2("./outputFigs3_0_0.root","READ");
    TH1D* forFittingFunction2 = (TH1D*)inputfile.Get("forFittingFunction");
    if( forFittingFunction2->Integral(1.75,8.0) ){
    }
    else{
    forFittingFunction2 = (TH1D*)inputfile2.Get("forFittingFunction");
    }

    forFittingFunction2->Fit("pol9");
    TF1* FittingFunction = forFittingFunction2->GetFunction("pol9");
 
    /*
    TFile * inputfile = new TFile("./outputFigs3.root");
    TH1D* forFittingFunction2 = (TH1D*)inputfile->Get("forFittingFunction");
    forFittingFunction2->Fit("pol9");
    TF1* FittingFunction = forFittingFunction2->GetFunction("pol9");
    */

    //Part 2. Do a Ocillation for the Fitting Function
    for(int i=1; i<2501; i++){
    E2[i]=1.75-(0.025/2)+i*0.0025;//need
    number_of_neutrino[i]=FittingFunction->Eval(1.75-(0.025/2)+i*0.0025);
    }

    TFile* outputFile = new TFile("outputFigs4.root","RECREATE");
    TH1D * forOscFittingFunction = new TH1D("forOscFittingFunction","title",2500,1.75,8);
    TH1D* forOscFittingFunction2 = (TH1D*)outputFile->Get("forOscFittingFunction");

    for(Int_t i=1;i<2501;i++)
    {
          delta_31_fit =  ((RooAbsReal*)_pulls->at(6))->getVal() * (L/E2[i])*1.27;
          survival_prob_fit = 1 -  ((RooAbsReal*)_pulls->at(2))->getVal() *  TMath::Power(TMath::Sin(delta_31_fit),2);
          forOscFittingFunction2->SetBinContent(i, survival_prob_fit * number_of_neutrino[i] );//oscSpectrum-2500bin-4.root
    }

    //Part 3. Getting TH1D from the Oscillated Fitting Function
    TH1D * forOscFittingFunction_100 = new TH1D("forOscFittingFunction_100","title",newBin,0.5,8);
    TH1D* forOscFittingFunction2_100 = (TH1D*)outputFile->Get("forOscFittingFunction_100");
    int w=0;
    int v=1;
    double SUM100 = 0;
    for(Int_t i=1;i<2501;i++)
    {
          w++;
          SUM100 = SUM100 + forOscFittingFunction2->GetBinContent(i);
          if(w==100)
          {      
          predNEOS->SetBinContent( v+5, SUM100/100. );//oscSpectrum-30bin-4.root
          //std::cout<<"v : "<<v<<" outputFig4.root "<<predNEOS->GetBinContent(v)<<std::endl;
          //std::cout<<" v : "<<v<<" SUM100 : "<<SUM100<<std::endl;
          SUM100 = 0;
          v++;
          w=0;
          }
    }
    std::cout<<"check point4 ###########################################################################################################################"<<std::endl;
    
    for(Int_t i=0; i<predNEOS->GetNbinsX(); i++)
    {
          //std::cout<<" i : "<<i<<" outputFig4.root : "<<predNEOS->GetBinContent(i)<<std::endl;
    }
    

//===================================================================================================================================================================7.4 prediction graph again====== 

  //std::cout<<"************* before folding "<<predPROS->Integral()<<std::endl;
  TH1D* fpredDC   = this->folding(predDC);
  TH1D* fpredDYB  = this->folding(predDYB);
  TH1D* fpredRENO = this->folding(predRENO);
  TH1D* fpredNEOS = this->folding(predNEOS);
  TH1D* fpredPROS = this->folding(predPROS);
   /*
   for(Int_t i=0;i<33;i++){
     std::cout<<"predNEOS TEST-5 "<< predNEOS->GetBinContent(i+1) <<std::endl;
       std::cout<<"fpredNEOS TEST-5 "<<fpredNEOS->GetBinContent(i+1)<<std::endl;  
         }
   */  
  std::cout<<"check point4.1 ###########################################################################################################################"<<std::endl; 
  forOscFittingFunction->Write();
  forOscFittingFunction_100->Write();
  outputFile->Close();
  //inputfile->Close();
  inputfile.Close();
  inputfile2.Close();  
  std::cout<<"check point4.2 ###########################################################################################################################"<<std::endl;
   //June,3,2020 : Print out Scaling4 & PredNEOS
  if(ifEHist == true){
    for(int iii = 0 ; iii< fpredNEOS->GetNbinsX(); iii++){
      //std::cout<<" iii "<<iii<<std::endl;
      //std::cout<<"------------------- "<<(*vecEscale)(iii)<<" "<<((RooAbsReal*)_pulls->at(10))->getVal()<<std::endl;
      fpredNEOS->SetBinContent( iii+1, fpredNEOS->GetBinContent(iii+1) * (1 + (*vecEscale)(iii) * ((RooAbsReal*)_pulls->at(10))->getVal()) );   //need
      if(iii==fpredNEOS->GetNbinsX()-1){
      //std::cout<<"ifEHist Check - fpredNEOS : "<< fpredNEOS->GetBinContent(iii+1) <<std::endl;
      //std::cout<<"ifEHist (*vecEscale)(iii) : "<< (*vecEscale)(iii) <<std::endl;
      //std::cout<<"ifEHist ((RooAbsReal*)_pulls->at(10)) : "<<((RooAbsReal*)_pulls->at(10))->getVal()<<std::endl;
      //June,3,2020 : Print out Scaling4 & PredNEOS
      }

    }    
  }
  std::cout<<"check point4.5 ###########################################################################################################################"<<std::endl;
   /* 
   for(Int_t i=0;i<33;i++){
   std::cout<<"&&&&&&&&&&&&&&&&&&&&  predNEOS TEST-6 "<< predNEOS->GetBinContent(i+1) <<std::endl;
   std::cout<<"&&&&&&&&&&&&&&&&&&&&  fpredNEOS TEST-6 "<< fpredNEOS->GetBinContent(i+1) <<std::endl;  
   }
   */
   //June,3,2020 : Print out Scaling4 & PredNEOS
/*
  for(Int_t i=0;i<33;i++){
    std::cout<<"E "<<(binEdge[i]+binEdge[i+1])/2.<<" predPROS value in preparePrediction "<<predPROS->GetBinContent(i+1)<<" "<<dataPROS->GetBinContent(i+1)<<"   -- fission pull value: "<<((RooAbsReal*)_pulls->at(i+12))->getVal()<<std::endl;
  }
*/
  //TH1D* fpredDC(predDC);
  //TH1D* fpredDYB(predDYB);
  //TH1D* fpredRENO(predRENO);
  //TH1D* fpredNEOS(predNEOS);

  //std::cout<<"in the middle of preparePrediction "<<std::endl;
  std::vector<TH1D*> predictionList;
  predictionList.clear();
/*
  predictionList.push_back(predDC);
  predictionList.push_back(predDYB);
  predictionList.push_back(predRENO);
  predictionList.push_back(predNEOS);
*/
  predictionList.push_back(fpredDC);
  predictionList.push_back(fpredDYB);
  predictionList.push_back(fpredRENO);
  predictionList.push_back(fpredNEOS);
  predictionList.push_back(fpredPROS);

  //std::cout<<"************* before folding "<<predPROS->Integral()<<std::endl;
  //TH1D* temp(predPROS);
  //TH1D* fpredPROS = this->folding(temp);
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

  // CCC : the binning here should be changed according to each experiment - Edited
  for(Int_t i=0;i<predDC->GetNbinsX();i++)
  {
    dataDC -> SetBinContent(i+1, predDC->GetBinContent(i+1)  * gradataDC->Eval(predDC->GetBinCenter(i+1)) );
  }
  for(Int_t i=0;i<predDYB->GetNbinsX();i++)
  {
    dataDYB -> SetBinContent(i+1,  predDYB->GetBinContent(i+1)  * gradataDYB->Eval(predDYB->GetBinCenter(i+1)) );
  }
  for(Int_t i=0;i<predRENO->GetNbinsX();i++)
  {
    dataRENO -> SetBinContent(i+1,  predRENO->GetBinContent(i+1)  * gradataRENO->Eval(predRENO->GetBinCenter(i+1)) );
  }
  for(Int_t i=0;i<predNEOS->GetNbinsX();i++)
  {
    dataNEOS -> SetBinContent(i+1,  predNEOS->GetBinContent(i+1)  * gradataNEOS->Eval(predNEOS->GetBinCenter(i+1)) );
  }
  for(Int_t i=0;i<predPROS->GetNbinsX();i++)
  {
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

TVectorD* Sterile::getTestVec(){
return testVec;
}//May,20,2020

Double_t Sterile::getScaling4(){
return scaling44;
}//June,3,2020


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

void Sterile::ifEShiftHist(bool eshifthist)
{
ifEHist = eshifthist;
}

bool Sterile::getIfEShiftHist()
{
return ifEHist ;
}

/*
TF1* Sterile::getFittingFunction()
{
return fitting_function ;
}

void Sterile::setFittingFunction(TF1* f)
{
fitting_function = f ;
}
*/

void Sterile::setEShiftHist(TString file)
{
TFile eshift(file);
//std::cout<<"taking escale file "<<file<<std::endl;
TH1D* histEscale = (TH1D*)eshift.Get("Escalefraction");
vecEscale = new TVectorD(64);

(*vecEscale)[0] = histEscale->GetBinContent(1);
(*vecEscale)[1] = histEscale->GetBinContent(1);
(*vecEscale)[2] = histEscale->GetBinContent(2);
(*vecEscale)[3] = histEscale->GetBinContent(2);
(*vecEscale)[4] = histEscale->GetBinContent(3);
(*vecEscale)[5] = histEscale->GetBinContent(3);
(*vecEscale)[6] = histEscale->GetBinContent(4);
(*vecEscale)[7] = histEscale->GetBinContent(4);
(*vecEscale)[8] = histEscale->GetBinContent(5);
(*vecEscale)[9] = histEscale->GetBinContent(5);
(*vecEscale)[10] = histEscale->GetBinContent(6);
(*vecEscale)[11] = histEscale->GetBinContent(6);
(*vecEscale)[12] = histEscale->GetBinContent(7);
(*vecEscale)[13] = histEscale->GetBinContent(7);
(*vecEscale)[14] = histEscale->GetBinContent(8);
(*vecEscale)[15] = histEscale->GetBinContent(8);
(*vecEscale)[16] = histEscale->GetBinContent(9);
(*vecEscale)[17] = histEscale->GetBinContent(9);
(*vecEscale)[18] = histEscale->GetBinContent(10);
(*vecEscale)[19] = histEscale->GetBinContent(10);
(*vecEscale)[20] = histEscale->GetBinContent(11);
(*vecEscale)[21] = histEscale->GetBinContent(11);
(*vecEscale)[22] = histEscale->GetBinContent(12);
(*vecEscale)[23] = histEscale->GetBinContent(12);
(*vecEscale)[24] = histEscale->GetBinContent(13);
(*vecEscale)[25] = histEscale->GetBinContent(13);
(*vecEscale)[26] = histEscale->GetBinContent(14);
(*vecEscale)[27] = histEscale->GetBinContent(14);
(*vecEscale)[28] = histEscale->GetBinContent(15);
(*vecEscale)[29] = histEscale->GetBinContent(15);
(*vecEscale)[30] = histEscale->GetBinContent(16);
(*vecEscale)[31] = histEscale->GetBinContent(16);
(*vecEscale)[32] = histEscale->GetBinContent(17);
(*vecEscale)[33] = histEscale->GetBinContent(17);
(*vecEscale)[34] = histEscale->GetBinContent(18);
(*vecEscale)[35] = histEscale->GetBinContent(18);
(*vecEscale)[36] = histEscale->GetBinContent(19);
(*vecEscale)[37] = histEscale->GetBinContent(19);
(*vecEscale)[38] = histEscale->GetBinContent(20);
(*vecEscale)[39] = histEscale->GetBinContent(20);
(*vecEscale)[40] = histEscale->GetBinContent(21);
(*vecEscale)[41] = histEscale->GetBinContent(21);
(*vecEscale)[42] = histEscale->GetBinContent(22);
(*vecEscale)[43] = histEscale->GetBinContent(22);
(*vecEscale)[44] = histEscale->GetBinContent(23);
(*vecEscale)[45] = histEscale->GetBinContent(23);
(*vecEscale)[46] = histEscale->GetBinContent(24);
(*vecEscale)[47] = histEscale->GetBinContent(24);
(*vecEscale)[48] = histEscale->GetBinContent(25);
(*vecEscale)[49] = histEscale->GetBinContent(25);
(*vecEscale)[50] = histEscale->GetBinContent(26);
(*vecEscale)[51] = histEscale->GetBinContent(26);
(*vecEscale)[52] = histEscale->GetBinContent(27);
(*vecEscale)[53] = histEscale->GetBinContent(27);
(*vecEscale)[54] = histEscale->GetBinContent(28);
(*vecEscale)[55] = histEscale->GetBinContent(28);
(*vecEscale)[56] = histEscale->GetBinContent(29);
(*vecEscale)[57] = histEscale->GetBinContent(29);
(*vecEscale)[58] = histEscale->GetBinContent(30);
(*vecEscale)[59] = histEscale->GetBinContent(30);
(*vecEscale)[60] = histEscale->GetBinContent(31);
(*vecEscale)[61] = histEscale->GetBinContent(31);
(*vecEscale)[62] = histEscale->GetBinContent(32);
(*vecEscale)[63] = histEscale->GetBinContent(32);
//for(int i=0;i<histEscale->GetNbinsX();i++){
for(int i=0;i<64;i++){
  std::cout<<" i : "<<i<<"(*vecEscale)[i] : "<<(*vecEscale)[i]<<std::endl;
   //(*vecEscale)[i] = histEscale->GetBinContent(i+1);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////==========================================9. making short function in Sterile variable============

TMatrixD* Sterile:: ConversionMatrix(TString inputFile, TString inputTree)
{
TFile f(inputFile);
TTree* t = (TTree*)f.Get(inputTree);
//   double binEdge[100];
//   Int_t  _nBins;

/*
fHist = new TH2D("","",_nBins,binEdge,_nBins,binEdge);
TH2D* cfHist = new TH2D("","",_nBins,0.5,0.5+_nBins*0.25,_nBins,0.5,0.5+_nBins*0.25);
//TH2D* fHist = new TH2D("","",34,0.5,9,34,0.5,9);

fMatrix = new TMatrixD(_nBins, _nBins);
TMatrixD* cfMatrix = new TMatrixD(_nBins, _nBins);
uMatrix = new TMatrixD(_nBins, _nBins);
unfoldingMatrix = new TMatrixD(_nBins, _nBins);
*/

//newBin
fHist = new TH2D("","",newBin,binEdge,newBin,binEdge);//need
TH2D* cfHist = new TH2D("","",newBin,0.5,0.5+_nBins*0.25/2,newBin,0.5,0.5+newBin*0.25/2);//need
//TH2D* fHist = new TH2D("","",34,0.5,9,34,0.5,9);

fMatrix = new TMatrixD(newBin, newBin);//need
TMatrixD* cfMatrix = new TMatrixD(newBin, newBin);//need
uMatrix = new TMatrixD(newBin, newBin);//need
unfoldingMatrix = new TMatrixD(newBin, newBin);//need

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
  for(Int_t j=0;j<fHist->GetNbinsX();j++){
     if(summ>0) fHist->SetBinContent(j+1,i+1,fHist->GetBinContent(j+1,i+1)/summ);
     (*unfoldingMatrix)(i,j) = fHist->GetBinContent(j+1,i+1);
  }
}


t->Delete();
f.Close();
return cfMatrix;
}

TH1D* Sterile:: folding(TH1D* input) const{
TH1D* output(input);
for(Int_t i=0;i<uMatrix->GetNrows();i++){	
  double sum = 0;
  for(Int_t j=0;j<input->GetNbinsX();j++){
    //std::cout<<"uMatrix->GetNrows() : "<<uMatrix->GetNrows()<<"input->GetNbinsX() : "<<input->GetNbinsX()<<endl; //newBin 
    sum += (*uMatrix)(i,j)*input->GetBinContent(j+1);
  }	  
  output->SetBinContent(i+1,sum);
}
//std::cout<<"folded "<<std::endl;
return output;
}
