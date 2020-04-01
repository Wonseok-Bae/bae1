#include "simple_t2k.hh"//ok
#include "TMath.h"//ok
#include "RooArgList.h"//ok
#include "RooAbsReal.h"//ok
#include "RooAbsCategory.h"//ok
#include "RooRealVar.h"//ok
#include "RooAbsPdf.h"//ok
#include "RooRealProxy.h"//ok
#include "TString.h"//ok
#include <TVectorD.h>//ok
#include <TCanvas.h>//ok
#include <TLegend.h>//ok
#include <TFrame.h>//ok
//=============================================================================================================1. 필요한 헤더파일 가져오기===========
using namespace std;//ok

 int main(int argc, char**argv){//인풋 받기ok

 RooFitResult* res;//ok
 Sterile * rep = new Sterile ("_rep");//ok
   char formula[10];//ok

 std::cout<<"1. start to run @@@@@@@@@@@@@@@@@@@@"<<std::endl;//첫 번째 아웃풋ok

 rep->setAtmBaseline(0);//repository 저장소
 rep->setDensity(0);
//=============================================================================================================2.1 필요한 변수 res, rep만들기========
 
 TH1D* vecInput1 = new TH1D("","",11,0,11);//그래프1 ok
 TH1D* vecInput2 = new TH1D("","",11,0,11);//그래프2 ok
 
 vecInput1 ->SetBinContent(1, TMath::ASin(TMath::Sqrt(0.85))/2.);//ok
 vecInput1 ->SetBinContent(2, 0);//ok 
 vecInput1 ->SetBinContent(3, 0);//ok 
 vecInput1 ->SetBinContent(4,-1.5);//ok
 vecInput1 ->SetBinContent(5,0.000075);//ok
 vecInput1 ->SetBinContent(6, 0 );//ok
 vecInput1 ->SetBinContent(7, 0 );//ok
 vecInput1 ->SetBinContent(8,1);//ok
 vecInput1 ->SetBinContent(9,1);//ok
 vecInput1 ->SetBinContent(10,1);//ok
 vecInput1 ->SetBinContent(11,1);//ok
 vecInput2 ->SetBinContent(1,TMath::ASin(TMath::Sqrt(0.85+0.021))/2.-TMath::ASin(TMath::Sqrt(0.85))/2.);//ok
 vecInput2 ->SetBinContent(2, 100);//ok
 vecInput2 ->SetBinContent(3,100);//ok
 vecInput2 ->SetBinContent(4,2);//ok
 vecInput2 ->SetBinContent(5,0.0000018);//ok
 vecInput2 ->SetBinContent(6, 100);//ok
 vecInput2 ->SetBinContent(7, 100);//ok
 vecInput2 ->SetBinContent(8, 100);//ok
 vecInput2 ->SetBinContent(9, 100);//ok
 vecInput2 ->SetBinContent(10,0.04); //ok
 vecInput2 ->SetBinContent(11,0.027);//ok

 std::cout<<"2. I've set some inputs @@@@@@@@@@@@@@@@@@@@"<<std::endl;//ok

 //============================================================================================================2.2 그래프 1,2 만들고 설정 넣기====== 

 // binned from 0.5-9 MeV with bin width of 0.25 MeV
 int nBins = 30;//ok
 TH1D* binHist = new TH1D("","",nBins+1,0,nBins+1);//ok
 for(Int_t i=0;i<nBins+1;i++){//ok
   binHist->SetBinContent(i+1, 0.5 + 0.25*i);//ok
 }
 //============================================================================================================2.3 그래프 3 만들고 설정 넣기========
 
 TString fileLocation = "/home/particle/바탕화면/REACTOR-related/";//ok
 rep->setFileLocation(fileLocation);//ok

 //============================================================================================================2.4 데이터 뽑아올 위치 설정=========
 
 TH1D* fissionHist = new TH1D("","",16,0,16);//ok
 double fissionList[16]={0.49,0.09,0.35,0.07,    0.501,0.073,0.353,0.072,    0.679,0.072,0.215,0.035,      0.679,0.072,0.215,0.035};//ok
 for(Int_t i=0;i<16;i++){//ok
   fissionHist->SetBinContent(i+1, fissionList[i]);//ok
 }
 //============================================================================================================2.5 그래프 4 만들고 설정 넣기========
 //=================================================================================================================================================
 
 rep->SetMatrixNameDC(fileLocation+"data/ReactorMatrixND_shape_rho0_NU.root");//ok
 rep->SetMatrixNameDYB(fileLocation+"data/NEOSCorrelationMatrix.root");//ok
 rep->SetMatrixNameRENO(fileLocation+"data/NEOSCorrelationMatrix.root");//ok
 rep->SetMatrixNameNEOS(fileLocation+"data/NEOSCorrelationMatrix.root");//ok
 rep->SetMatrixNamePROS(fileLocation+"data/NEOSCorrelationMatrix.root");//ok
 rep->SetBinning(binHist);//그래프 3 관련, 여기가 끝ok
 rep->SetFissionFraction(fissionHist);//그래프 4 관련, 여기가 끝ok

 TMatrixD* cfMatrix = rep->ConversionMatrix(fileLocation+"data/FinalFitIBDTree_DCIV_ND.root","FinalFitIBDTree");//핵심변수 3.cfMatrix

 //=============================================================================================================2.6 코릴레이션_메트릭스 데이터 추가

 std::vector<TString> mList;//새 변수 mList 안에 방사성 원소들 있음ok
 TString r235 = (fileLocation+"data/huber235.txt");//ok
 TString r238 = (fileLocation+"data/mueller238.txt");//ok
 TString r239 = (fileLocation+"data/huber239.txt");//ok
 TString r241 = (fileLocation+"data/huber241.txt");//ok
 mList.push_back(r235);//ok
 mList.push_back(r238);//ok 
 mList.push_back(r239);//ok
 mList.push_back(r241);//ok
 rep->SetModelList(mList);//ok 여기서 mList변수 끝

 //=============================================================================================================2.7 후버, 뮬러 모델 도입===========
 
 std::vector<TH1D*> tempPredList = rep->preparePrediction(rep->getPullList(), false);//rep에서 끌어낸 것으로 새 변수에 할당 아웃풋 데이터1에 연결ok 
 rep->prepareData(rep->preparePrediction(rep->getPullList(), false));//rep변수에서 뽑기ok
 rep->setPull(vecInput1); //여기가 데이터 피팅 - 어떻게?
 rep->setPullUnc(vecInput2); //여기가 데이터 피팅 - 어떻게?
 rep->addSK(true); //여기가 데이터 피팅 - 어떻게?
 rep->setNBins(34);//reb변수에서 뽑기ok
 rep->setTime(6);//reb변수에서 뽑기ok
 std::cout<<"ended up with setting us basic stuff @@@@@@@@@@@@@@@@@@@@"<<std::endl;//ok
 rep->FillEv(rep->getPullList());//여기서 matrix sum이랑 chi2 나옴 - 어떻게 되었더라?
 std::cout<<"I've set some more & more inputs @@@@@@@@@@@@@@@@@@@@"<<std::endl;//ok

 //=======================================================================================================2.8 데이터 피팅 및 아웃풋1 변수 만들기===
 
 RooArgList list("list");//이건 list라는 변수인것 같은데, 이 뒤로 안 쓰임ok
 list.add(*rep);//list 변수 안에 rep정보를 넣음ok
 sprintf(formula,"%s","@0");//formula라는 문자열에 @0를 넣기, 대충 이런 거ok
 RooFormulaVar* fcn = new RooFormulaVar("fit","fit",formula,list);//새로운 함수 fcn을 설정, 딱 한 번 쓰임ok

 //===============================================================================================================2.9 1차 완료========================
 //===================================================================================================================================================
 
 //  Important setup here 
 rep->fitSingleExp(Form("%s",argv[3])); // 세 번째로 입력하는 것을 NEOS PROSPECT DYB DC RENO 등을 input으로 넣기ok
 rep->ifEqualIso(false); // Isotope 지정 235U unification하려면 이걸 true로 바꿔야 하는 건가?ok
 rep->setSysts(false); // 시스테마틱 에러ok
 rep->setBaselineDYB(560.0);//베이스라인이 분명 미터 단위의 길이를 말하는 것 같다ok
 rep->setBaselineDC(400.0);//ok
 rep->setBaselineNEOS(20.0);//ok
 rep->setBaselineRENO(410.6);//ok
 rep->setBaselinePROS(7.9);//ok

 //================================================================================================================3.1 실험 데이터+동위원소+에러+길이

 rep->getParVar(2)->setConstant(true);//아마 이거 2개가 sterile하고 관련
 rep->getParVar(6)->setConstant(true);//아마 이거 2개가 sterile하고 관련
 rep->getParVar(0)->setConstant(true);
 rep->getParVar(1)->setConstant(true);
 rep->getParVar(3)->setConstant(true);
 rep->getParVar(4)->setConstant(true);
 rep->getParVar(5)->setConstant(true);
 rep->getParVar(7)->setConstant(true);//true면 상수이고, false면 아님ok
 rep->getParVar(8)->setConstant(true);//여때까지 2,6,7,8만 쓰임ok
 rep->getParVar(9)->setConstant(true);
 rep->getParVar(10)->setConstant(true);
 rep->getParVar(11)->setConstant(true);
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

 //================================================================================================================3.2 0부터 54까지 55개의 변수들
 
 std::cout<<"------------  Getting current spectra @@@@@@@@@@@@@@@@@@@@"<<std::endl; //스펙트럼 얻기ok
 std::vector<TH1D*> outPrediction = tempPredList; //1st output 데이터. 5th 그래프. 위에서 만든 tenpPred를 outPrediction으로 받은 것ok
 std::vector<TH1D*> outData = rep->GetCurrentData(outPrediction);//2nd outpur 데이터. 6th 그래프. outPrediction을 어떻게 해서 outData로 만든 것ok
 std::cout<<"------------  Have got current spectra @@@@@@@@@@@@@@@@@@@@"<<std::endl; //얻은 스펙트럼ok

 //★ ★ ★ save the un-oscillated standard prediction and data spectra //오실레이선 고려 안 했을 때 데이터+스펙트럼 얻기ok
 TFile* outputFile = new TFile("outputFigs.root","RECREATE");//오실레이션 안 먹은 아웃풋파일. 1st output 파일ok
 for(Int_t i=0;i<outPrediction.size();i++)//outPrediction의 크기만큼ok 
 {
   outPrediction[i]->Write(Form("outPrediction[%d]",i)); //output 파일에 outPrediction 데이터를 넣고ok
   if(i<5) outData[i]->Write(Form("outData[%d]",i)); //만약 0~4번째면, output파일에 outData 데이터도 넣어준다.ok
 }
 cfMatrix->Write("cfMatrix"); //아웃풋 얻기 핵심변수3 cfMatrix를 output파일에 넣어준다.ok
 outputFile -> Close();//ok
 std::cout<<"first thing saved(un-oscillation) -> outputFigs.root, cfMatrix @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<std::endl;

 ofstream outText;//★ ★ ★ 출력 파일 가능하게 만들어주고ok
 outText.open(Form("result/scan2Dnew_%s_fissionFree_ISO%d_SYST%d_%d_%d.txt",argv[3], rep->GetEqualIso(), rep->GetSysts(), atoi(argv[1]), atoi(argv[2]) ));
 //결과 파일 저장할 때 EqualIso, Systs 설정값을 제목에 붙여서 저장ok
 
 //================================================================================================================3.3 un-oscillation 결과 저장===

 double iDM = atof(argv[1]);//입력한 값을 질량제곱으로ok
 double iST = atof(argv[2]);//입력한 값을 사인세타제곱으로ok

 	rep->getParVar(2)->setVal(iST/125.); //여기 6줄이 실제로 피팅하는 곳, 이전까지는 준비단계ok
	rep->getParVar(6)->setVal(iDM/125.); //왜 하필 125로 나누는 지도 모르겠음ok
	rep->getParVar(2)->setConstant(false);//이걸 자세히 파해쳐봐야 한다ok
 	rep->getParVar(6)->setConstant(false);//ok
	rep->getParVar(7)->setConstant(true);//ok
	rep->getParVar(8)->setConstant(true);//ok

 	RooMinuit m(*fcn);//m이란 변수를 fcn를 따와서 만든다.ok
 	m.setStrategy(2);//m변수 아래에 setStrategy를 만든다.이후로 쓰이는 적 없음ok
 	Double_t callsEDM[2] = {10500., 1.e-6};//callsEDM이라는 변수 만들어서 mnexcm에 넣기ok
 	Int_t irf = 0;//irf라는 변수 만들어서 mnexcm에 넣기ok
 	gMinuit->mnexcm("MIGRAD",callsEDM,2,irf);//Roo+Minuit처럼, g+Minuit라는 형식의 mnexcm 변수 만들어 줌ok
 	m.migrad();//m안에 migrad라는 것고 만들어 주는데, 이후에 쓰이는 적은 없음ok

    	res = m.save();//res variable = m variable ok 
 	double bestFit = res->minNll();//베스트 핏 = res variable =chi2 ok
        std::cout<<"fit status code is : @@@@@@@@@@@@@@@@@@@@"<< res->status()<<std::endl;//fiting status = res->status variable ok	
	//status = 0    : OK
  	//status = 1    : Covariance was mad  epos defined
   	//status = 2    : Hesse is invalid
   	//status = 3    : Edm is above max
   	//status = 4    : Reached call limit
   	//status = 5    : Any other failure
	std::cout<<"quiality code of covariance matrix is : @@@@@@@@@@@@@@@@@@@@"<< res->covQual()<<std::endl;//cov matrix ok
	//status = -1   : not available (inversion failed or Hesse failed)
    	//status =  0   : available but not positive defined
    	//status =  1   : covariance only approximate
    	//status =  2   : full matrix but forced pos def
    	//status =  3   : full accurate matrix

 //===============================================================================3.4 input value / prarmeter fiting / m variable / bestFit =====

 outText<<atoi(argv[1])<<" "<<atoi(argv[2])<<" "<<bestFit<<std::endl;//output filed content ok
 
 outPrediction = rep->GetCurrentPrediction();//outPredictino varibale(1st output data) ok 여기서 fold를 만든다.
 TFile* outputFile2 = new TFile("outputFigs2.root","RECREATE");//output file 2 ok
 for(Int_t i=0;i<outPrediction.size();i++)//for the size of outPrediction ok
 {
   outPrediction[i]->Write(Form("outFit[%d]",i));//save the 1st output data ok	 
 }
 outputFile2->Close();//close ok
 
 std::cout<<"size of output prediction list @@@@@@@@@@@@@@@@@@@@"<<outPrediction.size()<<std::endl;//ok
 std::cout<<"size of output data list @@@@@@@@@@@@@@@@@@@@"<<outData.size()<<std::endl;//ok
 std::cout<<"chi2: @@@@@@@@@@@@@@@@@@@@"<<bestFit <<std::endl;//ok

 //double bb =  rep->getParVar(2)->getAsymErrorLo();//what is this?(value: 0)  ok
 //double dd =  rep->getParVar(2)->getAsymErrorHi();//what is this?(value: 0)  ok. if I don need it, delete it.

 }
//===================================================================================3.5 outText / outputFile2 / 1st, 2nd output / bb,dd =========
