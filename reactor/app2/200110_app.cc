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
//=============================================================================================================1. 필요한 헤더파일 가져오기===========
using namespace std;

 int main(int argc, char**argv){//인풋 받기


 RooFitResult* res;
 Sterile * rep = new Sterile ("_rep");
   char formula[10];

 std::cout<<"start to run @@@@@@@@@@@@@@@@@@@@"<<std::endl;//첫 번째 아웃풋

 rep->setAtmBaseline(0);//repository 저장소
 rep->setDensity(0);
 TH1D* vecInput1 = new TH1D("","",11,0,11);
 TH1D* vecInput2 = new TH1D("","",11,0,11);
 //============================================================================================================2. 설정깔고 히스토그램 설정=========== 
 //vecInput1->Print();

 vecInput1 ->SetBinContent(1, TMath::ASin(TMath::Sqrt(0.85))/2.);
 vecInput1 ->SetBinContent(2, 0); //TMath::ASin(TMath::Sqrt(0.95))/2.);
 vecInput1 ->SetBinContent(3, 0); //0.1);
 vecInput1 ->SetBinContent(4,-1.5);
 vecInput1 ->SetBinContent(5,0.000075);
 vecInput1 ->SetBinContent(6, 0 ); //0.00238);
 vecInput1 ->SetBinContent(7, 0 ); //0.00244);
 vecInput1 ->SetBinContent(8,1);
 vecInput1 ->SetBinContent(9,1);
 vecInput1 ->SetBinContent(10,1);
 vecInput1 ->SetBinContent(11,1);

 vecInput2 ->SetBinContent(1,TMath::ASin(TMath::Sqrt(0.85+0.021))/2.-TMath::ASin(TMath::Sqrt(0.85))/2.);
 vecInput2 ->SetBinContent(2, 100); //2);
 vecInput2 ->SetBinContent(3,100);
 vecInput2 ->SetBinContent(4,2);
 vecInput2 ->SetBinContent(5,0.0000018);
 vecInput2 ->SetBinContent(6, 100); //0.0001);
 vecInput2 ->SetBinContent(7, 100); //0.00009);
 //vecInput2 ->SetBinContent(8,0.009);
 //vecInput2 ->SetBinContent(9,0.03);
 vecInput2 ->SetBinContent(8, 100);
 vecInput2 ->SetBinContent(9, 100);
 vecInput2 ->SetBinContent(10,0.04); 
 vecInput2 ->SetBinContent(11,0.027);

 std::cout<<"I've set some inputs @@@@@@@@@@@@@@@@@@@@"<<std::endl;

 //==============================================================================================================3. 히스토그램에 대한 설정??인풋?=== 

 // binned from 0.5-9 MeV with bin width of 0.25 MeV
 int nBins = 30;
 TH1D* binHist = new TH1D("","",nBins+1,0,nBins+1);
 for(Int_t i=0;i<nBins+1;i++){
   binHist->SetBinContent(i+1, 0.5 + 0.25*i);
 }
 //==============================================================================================================4. 히스토그램에 bin 설정 박기======
 
 TString fileLocation = "/home/particle/바탕화면/REACTOR-related/";
 rep->setFileLocation(fileLocation);

 //==============================================================================================================5. 데이터 뽑아올 위치 설정=========
 
 TH1D* fissionHist = new TH1D("","",16,0,16);
 double fissionList[16]={0.49,0.09,0.35,0.07,    0.501,0.073,0.353,0.072,    0.679,0.072,0.215,0.035,      0.679,0.072,0.215,0.035};
 for(Int_t i=0;i<16;i++){
   fissionHist->SetBinContent(i+1, fissionList[i]);
 }
 //==============================================================================================================6. fissonList 16개원소 순서대로 넣기
 
 rep->SetMatrixNameDC(fileLocation+"data/ReactorMatrixND_shape_rho0_NU.root");
 rep->SetMatrixNameDYB(fileLocation+"data/NEOSCorrelationMatrix.root");
 rep->SetMatrixNameRENO(fileLocation+"data/NEOSCorrelationMatrix.root");
 rep->SetMatrixNameNEOS(fileLocation+"data/NEOSCorrelationMatrix.root");
 rep->SetMatrixNamePROS(fileLocation+"data/NEOSCorrelationMatrix.root");

 rep->SetBinning(binHist);
 rep->SetFissionFraction(fissionHist);

 TMatrixD* cfMatrix = rep->ConversionMatrix(fileLocation+"data/FinalFitIBDTree_DCIV_ND.root","FinalFitIBDTree");
 //rep->ConversionMatrix("data/FinalFitIBDTree_DCIV_ND.root","FinalFitIBDTree");
 //TH2D* fHist = rep->GetConversionMatrix();

 //std::cout<<"'ve set some more inputs, conversiont matrix summation is : "<<fHist->Integral()<<std::endl;

 //==============================================================================================================7. 코릴레이션_메트릭스 데이터로 피팅

 std::vector<TString> mList;
 TString r235 = (fileLocation+"data/huber235.txt");
 TString r238 = (fileLocation+"data/mueller238.txt");
 TString r239 = (fileLocation+"data/huber239.txt");
 TString r241 = (fileLocation+"data/huber241.txt");

 mList.push_back(r235);
 mList.push_back(r238); 
 mList.push_back(r239);
 mList.push_back(r241);

 rep->SetModelList(mList);

 //===============================================================================================================8. 후버, 뮬러 모델 도입===========

 //rep->preparePrediction(rep->getPullList(), false);
 std::vector<TH1D*> tempPredList = rep->preparePrediction(rep->getPullList(), false);
 rep->prepareData(rep->preparePrediction(rep->getPullList(), false));

 rep->setPull(vecInput1); //여기가 데이터 피팅
 rep->setPullUnc(vecInput2); //여기가 데이터 피팅
 rep->addSK(true); //여기가 데이터 피팅

 rep->setNBins(34);
 rep->setTime(6);

 //================================================================================================================9. 데이터 피팅===============

 std::cout<<"ended up with setting us basic stuff @@@@@@@@@@@@@@@@@@@@"<<std::endl;

 rep->FillEv(rep->getPullList());//여기서 matrix sum이랑 chi2 나옴

 std::cout<<"I've set some more & more inputs @@@@@@@@@@@@@@@@@@@@"<<std::endl;

 //===============================================================================================================10. 1차 완료==================
 
 RooArgList list("list");
 list.add(*rep);
 sprintf(formula,"%s","@0");
 RooFormulaVar* fcn = new RooFormulaVar("fit","fit",formula,list);

 //===============================================================================================================11. ??? =====================
 
 // ******************************** Important setup here *************************************
 // *******************************************************************************************
 rep->fitSingleExp(Form("%s",argv[3])); // NEOS PROSPECT DYB DC RENO 등을 input으로 넣기
 rep->ifEqualIso(false); // Isotope 지정
 rep->setSysts(false); // 시스테마틱 에러
 // *******************************************************************************************
 // ******************************************************************************************* 

 rep->setBaselineDYB(560.0);
 rep->setBaselineDC(400.0);
 rep->setBaselineNEOS(20.0);
 rep->setBaselineRENO(410.6);
 rep->setBaselinePROS(7.9);

 //================================================================================================================12. 실험 데이터+동위원소+에러

 //rep->getParVar(3)->setVal(2.5);
 rep->getParVar(2)->setConstant(true);
 rep->getParVar(6)->setConstant(true);

 rep->getParVar(0)->setConstant(true);
 rep->getParVar(1)->setConstant(true);
 rep->getParVar(3)->setConstant(true);
 rep->getParVar(4)->setConstant(true);
 rep->getParVar(5)->setConstant(true);
 rep->getParVar(7)->setConstant(true);
 rep->getParVar(8)->setConstant(true);
 rep->getParVar(9)->setConstant(true);
 rep->getParVar(10)->setConstant(true);
 rep->getParVar(11)->setConstant(true);
/*
 rep->getParVar(12)->setConstant(true);  // 0.5 - 0.75
 rep->getParVar(13)->setConstant(true);  // 0.75 - 1
 rep->getParVar(14)->setConstant(true);  // 1 - 1.25
 rep->getParVar(15)->setConstant(true);  // 1.25 - 1.5
 rep->getParVar(16)->setConstant(true);  // 1.5 - 1.75
 rep->getParVar(17)->setConstant(true);  // 1.75 - 2
 rep->getParVar(18)->setConstant(true);  // 2 - 2.25
 rep->getParVar(19)->setConstant(true);  // 2.25 - 2.5
 rep->getParVar(20)->setConstant(true);  // 2.5 - 2.75
 rep->getParVar(21)->setConstant(true);  // 2.75 - 3
 rep->getParVar(22)->setConstant(true);  // 3 - 3.25
 rep->getParVar(23)->setConstant(true);  // 3.25 - 3.5
 rep->getParVar(24)->setConstant(true);  // 3.5 - 3.75
 rep->getParVar(25)->setConstant(true);  // 3.75 - 4
 rep->getParVar(26)->setConstant(true);  // 4 - 4.25
 rep->getParVar(27)->setConstant(true);  // 4.25 - 4.5
 rep->getParVar(28)->setConstant(true);  // 4.5 - 4.75
 rep->getParVar(29)->setConstant(true);  // 4.75 - 5
 rep->getParVar(30)->setConstant(true);  // 5 - 5.25
 rep->getParVar(31)->setConstant(true);  // 5.25 - 5.5
 rep->getParVar(32)->setConstant(true);  // 5.5 - 5.75
 rep->getParVar(33)->setConstant(true);  // 5.75 - 6
 rep->getParVar(34)->setConstant(true);  // 6 - 6.25
 rep->getParVar(35)->setConstant(true);  // 6.25 - 6.5
 rep->getParVar(36)->setConstant(true);  // 6.5 - 6.75
 rep->getParVar(37)->setConstant(true);  // 6.75 - 7
 rep->getParVar(38)->setConstant(true);  // 7 - 7.25
 rep->getParVar(39)->setConstant(true);  // 7.25 - 7.5
 rep->getParVar(40)->setConstant(true);  // 7.5 - 7.75
 rep->getParVar(41)->setConstant(true);  // 7.75 - 8
 rep->getParVar(42)->setConstant(true);  // 8 - 8.25
 rep->getParVar(43)->setConstant(false);  // 8.25 - 8.5
 rep->getParVar(44)->setConstant(true);  // 8.5 - 8.75
 rep->getParVar(45)->setConstant(true);  // 8.75 - 9

 rep->getParVar(12)->setConstant(true);  // 0.5 - 0.75
 rep->getParVar(13)->setConstant(false);  // 0.75 - 1
 rep->getParVar(14)->setConstant(false);  // 1 - 1.25
 rep->getParVar(15)->setConstant(false);  // 1.25 - 1.5
 rep->getParVar(16)->setConstant(false);  // 1.5 - 1.75
 rep->getParVar(17)->setConstant(false);  // 1.75 - 2
 rep->getParVar(18)->setConstant(false);  // 2 - 2.25
 rep->getParVar(19)->setConstant(false);  // 2.25 - 2.5
 rep->getParVar(20)->setConstant(false);  // 2.5 - 2.75
 rep->getParVar(21)->setConstant(false);  // 2.75 - 3
 rep->getParVar(22)->setConstant(false);  // 3 - 3.25
 rep->getParVar(23)->setConstant(false);  // 3.25 - 3.5
 rep->getParVar(24)->setConstant(false);  // 3.5 - 3.75
 rep->getParVar(25)->setConstant(false);  // 3.75 - 4
 rep->getParVar(26)->setConstant(false);  // 4 - 4.25
 rep->getParVar(27)->setConstant(false);  // 4.25 - 4.5
 rep->getParVar(28)->setConstant(false);  // 4.5 - 4.75
 rep->getParVar(29)->setConstant(false);  // 4.75 - 5
 rep->getParVar(30)->setConstant(false);  // 5 - 5.25
 rep->getParVar(31)->setConstant(false);  // 5.25 - 5.5
 rep->getParVar(32)->setConstant(false);  // 5.5 - 5.75
 rep->getParVar(33)->setConstant(false);  // 5.75 - 6
 rep->getParVar(34)->setConstant(false);  // 6 - 6.25
 rep->getParVar(35)->setConstant(false);  // 6.25 - 6.5
 rep->getParVar(36)->setConstant(false);  // 6.5 - 6.75
 rep->getParVar(37)->setConstant(false);  // 6.75 - 7
 rep->getParVar(38)->setConstant(false);  // 7 - 7.25
 rep->getParVar(39)->setConstant(false);  // 7.25 - 7.5
 rep->getParVar(40)->setConstant(false);  // 7.5 - 7.75
 rep->getParVar(41)->setConstant(false);  // 7.75 - 8
 rep->getParVar(42)->setConstant(false);  // 8 - 8.25
 rep->getParVar(43)->setConstant(false);  // 8.25 - 8.5
 rep->getParVar(44)->setConstant(false);  // 8.5 - 8.75
 rep->getParVar(45)->setConstant(true);  // 8.75 - 9
*/

 rep->getParVar(12)->setConstant(true);  // 0.5 - 0.75
 rep->getParVar(13)->setConstant(true);  // 0.75 - 1
 rep->getParVar(14)->setConstant(true);  // 1 - 1.25
 rep->getParVar(15)->setConstant(true);  // 1.25 - 1.5
 rep->getParVar(16)->setConstant(true);  // 1.5 - 1.75
 rep->getParVar(17)->setConstant(true);  // 1.75 - 2
 rep->getParVar(18)->setConstant(true);  // 2 - 2.25
 rep->getParVar(19)->setConstant(true);  // 2.25 - 2.5
 rep->getParVar(20)->setConstant(false);  // 2.5 - 2.75
 rep->getParVar(21)->setConstant(false);  // 2.75 - 3
 rep->getParVar(22)->setConstant(false);  // 3 - 3.25
 rep->getParVar(23)->setConstant(false);  // 3.25 - 3.5
 rep->getParVar(24)->setConstant(false);  // 3.5 - 3.75
 rep->getParVar(25)->setConstant(false);  // 3.75 - 4
 rep->getParVar(26)->setConstant(false);  // 4 - 4.25
 rep->getParVar(27)->setConstant(false);  // 4.25 - 4.5
 rep->getParVar(28)->setConstant(false);  // 4.5 - 4.75
 rep->getParVar(29)->setConstant(false);  // 4.75 - 5
 rep->getParVar(30)->setConstant(false);  // 5 - 5.25
 rep->getParVar(31)->setConstant(false);  // 5.25 - 5.5
 rep->getParVar(32)->setConstant(false);  // 5.5 - 5.75
 rep->getParVar(33)->setConstant(false);  // 5.75 - 6
 rep->getParVar(34)->setConstant(false);  // 6 - 6.25
 rep->getParVar(35)->setConstant(false);  // 6.25 - 6.5
 rep->getParVar(36)->setConstant(false);  // 6.5 - 6.75
 rep->getParVar(37)->setConstant(false);  // 6.75 - 7
 rep->getParVar(38)->setConstant(false);  // 7 - 7.25
 rep->getParVar(39)->setConstant(true);  // 7.25 - 7.5
 rep->getParVar(40)->setConstant(true);  // 7.5 - 7.75
 rep->getParVar(41)->setConstant(true);  // 7.75 - 8
 rep->getParVar(42)->setConstant(true);  // 8 - 8.25
 rep->getParVar(43)->setConstant(true);  // 8.25 - 8.5
 rep->getParVar(44)->setConstant(true);  // 8.5 - 8.75
 rep->getParVar(45)->setConstant(true);  // 8.75 - 9


 // energy scales for four exp.
 rep->getParVar(45)->setConstant(true);  
 rep->getParVar(46)->setConstant(true);  
 rep->getParVar(47)->setConstant(true);  
 rep->getParVar(48)->setConstant(true);  
 rep->getParVar(49)->setConstant(true);  
 rep->getParVar(50)->setConstant(true);  
 rep->getParVar(51)->setConstant(true);  
 rep->getParVar(52)->setConstant(true);
 rep->getParVar(53)->setConstant(true);
 rep->getParVar(54)->setConstant(true);

 //================================================================================================================12. 에너지? 등 히스토그램에 설정
 
 //    for(Int_t nn= 0; nn< npts ; ++nn) {

 //rep->setNBins(binSetup );
 //rep->setTime(atof(argv[5]));

 std::cout<<"------------  Getting current spectra @@@@@@@@@@@@@@@@@@@@"<<std::endl; //스펙트럼 얻기
 std::vector<TH1D*> outPrediction = tempPredList; // rep->GetCurrentPrediction();
 std::vector<TH1D*> outData = rep->GetCurrentData(outPrediction);//여기서도 출력(큰 수)
 std::cout<<"------------  Have got current spectra @@@@@@@@@@@@@@@@@@@@"<<std::endl; //얻은 스펙트럼

 // save the un-oscillated standard prediction and data spectra //오실레이선 고려 안 했을 때 데이터+스펙트럼 얻기
 TFile* outputFile = new TFile("outputFigs.root","RECREATE");//오실레이션 안 먹은 아웃풋파일
 for(Int_t i=0;i<outPrediction.size();i++)
 {
   outPrediction[i]->Write(Form("outPrediction[%d]",i)); //데이터 넣기
   if(i<5) outData[i]->Write(Form("outData[%d]",i)); //데이터 넣기
 }
 cfMatrix->Write("cfMatrix"); //아웃풋 얻기
 outputFile -> Close();
 //exit(1);
 std::cout<<"first thing saved -> outputFigs.root, cfMatrix @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<std::endl;

 //================================================================================================================13. 결과 저장(오실레이션x)=======

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // variations of the predicted spectra with different oscillation parameters
 /* if(true){
    

   //1번 오실레이션(질량제곱이랑 사인세타제곱 계속 달라짐)
   cout<<"1st Oscillation->outputFigVar1.root"<<endl;
   TFile* outputFileOsc = new TFile("outputFigVar1.root","RECREATE");//오실레이션 먹은 아웃풋파일 
   float dmVar = 0.001 ;//질량제곱
   float stVar = 0.1 ;//사인세타제곱
   rep->getParVar(2)->setVal(stVar);//folded
   rep->getParVar(6)->setVal(dmVar);//folded 
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     //cout<<"-----------dmVar(질량제곱)--------------@@@@@@@@@@@@@@@@@@@@ "<<dmVar<<endl;
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
   }
   outputFileOsc -> Close();


   //2번 오실레이션
   cout<<"2nd Oscillation->outputFigVar2.root"<<endl;
   TFile* outputFileOsc2 = new TFile("outputFigVar2.root","RECREATE");
   dmVar = 0.1 ;
   stVar = 0.1 ;
   rep->getParVar(2)->setVal(stVar);
   rep->getParVar(6)->setVal(dmVar); 
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar, stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i, dmVar,stVar));
   }
   outputFileOsc2 -> Close();


   //3번 오실레이션
   cout<<"3st Oscillation->outputFigVar3.root"<<endl;
   TFile* outputFileOsc3 = new TFile("outputFigVar3.root","RECREATE");
   dmVar = 1 ;
   stVar = 0.1 ;
   rep->getParVar(2)->setVal(stVar);
   rep->getParVar(6)->setVal(dmVar); 
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar ));
   }
   outputFileOsc3 -> Close();


   //4번 오실레이션
   cout<<"4th Oscillation->outputFigVar4.root"<<endl;
   TFile* outputFileOsc4 = new TFile("outputFigVar4.root","RECREATE");
   dmVar = 0.001 ;
   stVar = 0.01 ;
   rep->getParVar(2)->setVal(stVar);
   rep->getParVar(6)->setVal(dmVar); 
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar ));
   }
   outputFileOsc4 -> Close();


   //5번 오실레이션
   cout<<"5th Oscillation->outputFigVar5.root"<<endl;
   TFile* outputFileOsc5 = new TFile("outputFigVar5.root","RECREATE");
   dmVar = 0.01 ;
   stVar = 0.01 ;
   rep->getParVar(2)->setVal(stVar);
   rep->getParVar(6)->setVal(dmVar);
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
   }
   outputFileOsc5 -> Close();


   //6번 오실레이션
   cout<<"6th Oscillation->outputFigVar6.root"<<endl;
   TFile* outputFileOsc6 = new TFile("outputFigVar6.root","RECREATE");
   dmVar = 1 ;
   stVar = 0.01 ;
   rep->getParVar(2)->setVal(stVar);
   rep->getParVar(6)->setVal(dmVar); 
   outPrediction = rep->GetCurrentPrediction();
   //outData = rep->GetCurrentData(outPrediction);
   for(Int_t i=0;i<outPrediction.size();i++)
   {
     outPrediction[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
     //outData[i]->Write(Form("outOsc[%d]_dm%f_st%f",i,dmVar,stVar));
   }
   outputFileOsc6 -> Close();
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
*/

 //===================================================================================================================14. 결과저장(오실레이션o)======

 ofstream outText;
 outText.open(Form("result/scan2Dnew_%s_fissionFree_ISO%d_SYST%d_%d_%d.txt",argv[3], rep->GetEqualIso(), rep->GetSysts(), atoi(argv[1]), atoi(argv[2]) ));

 double iDM = atof(argv[1]);
 double iST = atof(argv[2]);

 //====================================================================================================15. 결과파일 만들고, 질량제곱,사인세타제곱 입력 
 
 //for(Int_t iDM=0;iDM<50;iDM++)
 //{
     //for(Int_t iST=0;iST<50;iST++)
     //{
        // means that s2t14 0.001 - 1 and dm2 0.01 - 10
        //rep->getParVar(2)->setVal(TMath::Power(10.,(-3.*iST*2/100.)));
        //rep->getParVar(6)->setVal(TMath::Power(10,(-2 + 5.*iDM*2/100.)));
	rep->getParVar(2)->setVal(iST/125.); //여기 6줄이 실제로 피팅하는 곳, 이전까지는 준비단계
	rep->getParVar(6)->setVal(iDM/125.);
	rep->getParVar(2)->setConstant(false);
 	rep->getParVar(6)->setConstant(false);
	rep->getParVar(7)->setConstant(true);
	rep->getParVar(8)->setConstant(true);

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
 	double bestFit = res->minNll();//베스트 핏만 골라내는 건가?
        std::cout<<"fit status code is : @@@@@@@@@@@@@@@@@@@@"<< res->status()<<std::endl;	
	//status = 0    : OK
  	//status = 1    : Covariance was mad  epos defined
   	//status = 2    : Hesse is invalid
   	//status = 3    : Edm is above max
   	//status = 4    : Reached call limit
   	//status = 5    : Any other failure
	std::cout<<"quiality code of covariance matrix is : @@@@@@@@@@@@@@@@@@@@"<< res->covQual()<<std::endl;
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

 outPrediction = rep->GetCurrentPrediction();
 //outData = rep->GetCurrentData(outPrediction);


 //std::cout<<"list of reactor pulls : "<<std::endl;
 //for(Int_t i=18;i<41;i++){std::cout<<" "<<rep->getPar(i)<<std::endl;}

 TFile* outputFile2 = new TFile("outputFigs2.root","RECREATE");
 for(Int_t i=0;i<outPrediction.size();i++)
 {
   outPrediction[i]->Write(Form("outFit[%d]",i));	 
 }

 outputFile2->Close();

 std::cout<<"size of output prediction list @@@@@@@@@@@@@@@@@@@@"<<outPrediction.size()<<std::endl;
 std::cout<<"size of output data list @@@@@@@@@@@@@@@@@@@@"<<outData.size()<<std::endl;

 //std::cout<<"result list: "<<std::endl;
 std::cout<<"chi2: "<<bestFit <<std::endl;

 double bb =  rep->getParVar(2)->getAsymErrorLo();
 double dd =  rep->getParVar(2)->getAsymErrorHi();

 //cout<<"errors are "<<bb<<" "<<dd<<endl;

 //for(Int_t i=0;i<11;i++){std::cout<<" "<<rep->getPar(i)<<std::endl;}
 //int aa = (atof(argv[5])+0.000001)*100;
 //cout<<atoi(argv[2])<<" "<<aa<<" "<<dd<<endl; 
 //  }
 }
