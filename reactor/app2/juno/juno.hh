/*
 *  Sterile for radioactive source header file.
 *
 *  Author: Guang Yang
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <sstream>
#include <TList.h>

#include <TROOT.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TH1.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TFile.h>
#include <TRint.h>
#include <TH2.h>
#include <TFormula.h>
#include <TF1.h>
#include <TF2.h>
#include <TMath.h>
#include <Math/DistFunc.h>
#include <TLine.h>
#include <TTree.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TRandom2.h>
#include <TRandom3.h>
#include <TGraphErrors.h>
#include <TVirtualFFT.h>
#include <TFoamIntegrand.h>
#include <TMatrixD.h>
#include <TVectorT.h>
#include <TDecompChol.h>

#include <RooFit.h>
#include "RooGlobalFunc.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooDataSet.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooWorkspace.h"
#include "RooMinuit.h"
#include "RooNLLVar.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooExtendPdf.h"
#include "RooChi2Var.h"
#include "RooMinuit.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooRandom.h"
#include <RooMsgService.h>
#include <RooHist.h>
#include <RooTrace.h>
#include <RooCategory.h>
#include "RooConstVar.h"
#include "RooBinning.h"

#include "TStopwatch.h"
#include "TFile.h"
#include "TMinuit.h"

#include "RooFit.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "TMinuit.h"
#include <RooRealVar.h>

using namespace RooFit;


  class Sterile : public RooAbsReal {

  public:

    Sterile (const char* name);

    Sterile (const Sterile & other, const char* name = 0): RooAbsReal(other,name) {};
    virtual TObject* clone(const char* newname) const {return new Sterile (*this, newname);};
    virtual ~Sterile () ;
    Sterile (const Sterile & Sterile );

    void randomGo(int newIsotope, RooListProxy* _pulls);

    Sterile & operator=(const Sterile & rhs);

    RooFormulaVar* Chi2() ;

    Double_t FillEv(RooListProxy* _pulls) const;

    //void Fillup(RooListProxy* _pulls) const;
    void Fillup(RooListProxy* _pulls, bool vec) const;

    Double_t ExtraPull(RooListProxy* _pulls) const;

    void setPull(TH1D* pullvecCV) ;
    void setPullUnc(TH1D* pullvecUnc) ;
    Double_t getPullUnc(Int_t pN) ;

    void SetLbins(int Lbins);
    void SetEbins(int Ebins);
    void Set1Dbins(int bins);
    void SetAO(double ao);
    void SetT12(double t12);
    void SetDAYS(double _days);
    void SetFRACT(double _fract);
    void SetNP(double np);
    void SetEfficiency(double eff);
    void SetRADIUS(double radius);
    void SetNMC(int nmc);
    void SetDM41(double _dm41);
    void SetTHETA(double _theta);
    void SetSourceDis(double dis);
    void SetLSmear(double sm);
    void SetESmear(double sm);
    double GetDM41();
    double GetTHETA();

    bool SetStatGaus(bool gaus);
    bool ifDo1D(bool vec);
    bool ifDoEScale(bool vec);
    bool ifPreEScale(bool vec);
    
    RooRealVar Par1 ;
    RooRealVar Par2 ;
    RooRealVar Par3 ;
    RooRealVar Par4 ;
    RooRealVar Par5 ;
    RooRealVar Par6 ;
    RooRealVar Par7 ;
    RooRealVar Par8 ;
    RooRealVar Par9 ;
    RooRealVar Par10 ;
    RooRealVar Par11 ;
    RooRealVar Par12 ;

    Double_t _par1;
    Double_t _par2;
    Double_t _par3;
    Double_t _par4;
    Double_t _par5;
    Double_t _par6;
    Double_t _par7;
    Double_t _par8;
    Double_t _par9;
    Double_t _par10;
    Double_t _par11;
    Double_t _par12;

    Double_t getPar(int i) ;
    void DataSwitch(Bool_t dataSwitch=true) const;
    Bool_t getDataSwitch() const;

    RooRealVar* getParVar(int i) ;
    RooListProxy* getParVar() ;
    RooListProxy* getPullList() const;

    TMatrixD* GetCurrentPredLE() const  {return predLE2Dm; }  
    TMatrixD* GetCurrebtObsLE() const {return obsLE2Dm; }
    TMatrixD* GetCurrentPredOrig() const {return predLE2Dorign; }

    RooArgList _parlist;
    RooListProxy* _pulls;

    TH2D* fHist;
    TMatrixD* fMatrix;
    TMatrixD* uMatrix;
    TMatrixD* unfoldingMatrix;

    TH2D* conv;
    TH1D* nueAfter;
    TH1D* nueBefore;
    TH1D* numuTrue;

    Double_t _syst;
    Double_t _dm2CV;
    Double_t _dm2Unc;

    Double_t _Density;
    Double_t _AtmBaseline;
    Double_t _time;
    Double_t _Bins;
    Double_t _Corr1;
    Double_t _Corr2;
    Double_t _Corr3;
    Double_t _Corr4;
    Double_t dataSet;
    Bool_t _dataSwitch;

    TVectorD* pullCV; 
    TVectorD* pullUnc;
    TVectorD* fData_t2k;
    TVectorD* fData_sk;
    TVectorD* fData_JUNO;

    TVectorD* fVec_t2k;
    TVectorD* fVec_t2k_nd;
    TVectorD* fVec_sk;
    TVectorD* fVec_JUNO;
    TVectorD* fVecShadow_JUNO;
 
    TVectorD* MCDelegate;
    TVectorD* dataDelegate;

    TH1D* hData_JUNO;
    TH1D* hShadow_JUNO;
    
    Bool_t withSK ;

    TString fileName;
    TString fileNameRENO;
    TString fileNameNEOS;
    TString fileNameDC;
    TString fileNameDYB;
    TString fileNamePROS;
    double fissionFraction[100];
    double binEdge[100];
    Int_t  _nBins;
    TString singleExp;
    double baselineDC;
    double baselineDYB;
    double baselineRENO;
    double baselineNEOS;
    double baselinePROS;

    bool inSyst;
    bool equalIso;
    TString fileLocation;

    TH1D* dataDC;
    TH1D* dataDYB;
    TH1D* dataRENO;
    TH1D* dataNEOS;
    TH1D* dataPROS;
    //TH1D* predDC;
    //TH1D* predDYB;
    //TH1D* predRENO;
    //TH1D* predNEOS;

    std::vector<TString> modelList;

    std::vector<TH1D*> dataList;

    int L_bins;
    int E_bins;
    int A1D_bins;
    double Ao;
    double T_12;
    double days;
    double fract;
    double Np;
    double efficiency;
    double Radius;
    int Nmc;
    double dm41;
    double theta;
    double sourceDis;
    double lSmear;
    double eSmear;
    
    bool doGaussian;
    bool doLikelihood;
    bool do1D;
    bool doEScale;
    bool preEScale;

    TMatrixD* obsLE2Dm;
    TMatrixD* predLE2Dm;
    TMatrixD* predLE2Dorign;

    TMatrixD* obsLE1Dm;
    TMatrixD* predLE1Dm;
    TMatrixD* predLE1Dorign;

    TMatrixD* hereShift;

    TMatrixD* GetPreEScaleShift() { return hereShift;}
    bool GetPreEScale(){ return preEScale; }

    //  private:
   
   virtual  Double_t evaluate() const ;

   protected:
  };


