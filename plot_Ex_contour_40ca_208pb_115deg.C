#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TLegend.h"
#include "TPaveStats.h"

void plot_Ex_contour_40ca_208pb_115deg(){


 std::ifstream contourfile("40Ca_208Pb_39K_Ex_115deg.dat",std::ios::in);

  TGraph2D* contour = new TGraph2D();

  int pointno = 0;

  if(contourfile.good()){


    while(!contourfile.eof()){


      std::string line;



      getline(contourfile,line);




      if(line.size()>0){



        TString lin(line);

        TObjArray* tokens = lin.Tokenize(TString("\t"));

        tokens->SetOwner(kTRUE);

        double E_over_Vb = ((TObjString*)tokens->At(0))->String().Atof();

        double Ex = ((TObjString*)tokens->At(1))->String().Atof();

        double dP_dEx = ((TObjString*)tokens->At(2))->String().Atof();

	contour->SetPoint(pointno,Ex,E_over_Vb,dP_dEx);

        pointno++;

    }



  }




}

  TCanvas* c = new TCanvas("contour_canvas","contour_canvas");

  c->cd();                                                                                                                                                

  std::cout<<"g points = "<<contour->GetN()<<endl;

  contour->SetTitle("");

  contour->GetHistogram()->GetXaxis()->SetTitle("Ex (MeV)");
  contour->GetHistogram()->GetYaxis()->SetTitle("E / V_{B}");
  contour->GetHistogram()->GetZaxis()->SetTitle("dP / dE_{x} (MeV^{-1})");
  contour->GetHistogram()->GetXaxis()->CenterTitle();
  contour->GetHistogram()->GetYaxis()->CenterTitle();
  contour->GetHistogram()->GetZaxis()->CenterTitle();
  contour->GetHistogram()->GetZaxis()->SetTitleOffset(0.7);

  TH2D* contourhist = contour->GetHistogram();

  contour->SetMinimum(0.00001);
  contour->SetMaximum(0.005);

  contour->Draw("CONT4Z"); // Or contour->Draw("TRI2Z"); OR contour->Draw("CONT5Z");
  contour->GetHistogram()->SetContour(50);
  // canvas->SetTheta(90);   // where TRI2 option used
  // canvas->SetPhi(0);                        // where TRI2 option used
}
