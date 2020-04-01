void Validation6()
{
//=========Macro generated from canvas: c1_n6/c1_n6
//=========  (Sat Nov 17 18:59:56 2018) by ROOT version 6.13/08
   TCanvas *c1_n6 = new TCanvas("c1_n6", "c1_n6",0,0,700,500);
   c1_n6->SetHighLightColor(2);
   c1_n6->Range(0,0,1,1);
   c1_n6->SetFillColor(0);
   c1_n6->SetBorderMode(0);
   c1_n6->SetBorderSize(2);
   c1_n6->SetFrameBorderMode(0);
   
   TF1 *IBDXsecF2 = new TF1("IBDXsecF","0.0952*(x-0.8)*( sqrt((x-0.8)*(x-0.8)-0.5*0.5))",1.8,10, TF1::EAddToList::kDefault);
   IBDXsecF2->SetFillColor(19);
   IBDXsecF2->SetFillStyle(0);
   IBDXsecF2->SetLineColor(2);
   IBDXsecF2->SetLineWidth(2);
   IBDXsecF2->GetXaxis()->SetLabelFont(42);
   IBDXsecF2->GetXaxis()->SetLabelSize(0.035);
   IBDXsecF2->GetXaxis()->SetTitleSize(0.035);
   IBDXsecF2->GetXaxis()->SetTitleFont(42);
   IBDXsecF2->GetYaxis()->SetLabelFont(42);
   IBDXsecF2->GetYaxis()->SetLabelSize(0.035);
   IBDXsecF2->GetYaxis()->SetTitleSize(0.035);
   IBDXsecF2->GetYaxis()->SetTitleOffset(0);
   IBDXsecF2->GetYaxis()->SetTitleFont(42);
   IBDXsecF2->Draw("");
   
   Double_t Graph0_fx2[10] = {
   0,
   1,
   2,
   3,
   4,
   5,
   6,
   7,
   8,
   9};
   Double_t Graph0_fy2[10] = {
   6e-05,
   0.0007,
   0.008,
   0.3,
   0.7,
   1.4,
   2.1,
   3.2,
   4,
   5.5};
   TGraph *graph = new TGraph(10,Graph0_fx2,Graph0_fy2);
   graph->SetName("Graph0");
   graph->SetTitle("data/IBDXsec.dat");
   graph->SetFillStyle(1000);
   graph->SetLineColor(4);
   graph->Draw("");
   c1_n6->Modified();
   c1_n6->cd();
   c1_n6->SetSelected(c1_n6);
}
