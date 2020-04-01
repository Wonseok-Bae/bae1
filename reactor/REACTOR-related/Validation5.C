void Validation5()
{
//=========Macro generated from canvas: c1_n5/c1_n5
//=========  (Sat Nov 17 18:59:56 2018) by ROOT version 6.13/08
   TCanvas *c1_n5 = new TCanvas("c1_n5", "c1_n5",0,0,700,500);
   c1_n5->SetHighLightColor(2);
   c1_n5->Range(0,0,1,1);
   c1_n5->SetFillColor(0);
   c1_n5->SetBorderMode(0);
   c1_n5->SetBorderSize(2);
   c1_n5->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[10] = {
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
   Double_t Graph0_fy1[10] = {
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
   TGraph *graph = new TGraph(10,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("data/IBDXsec.dat");
   graph->SetFillStyle(1000);
   graph->SetLineColor(4);
   graph->Draw("alp");
   
   TF1 *IBDXsecF1 = new TF1("IBDXsecF","0.0952*(x)*( sqrt((x)*(x)-0.5*0.5))",1.8,10, TF1::EAddToList::kDefault);
   IBDXsecF1->SetFillColor(19);
   IBDXsecF1->SetFillStyle(0);
   IBDXsecF1->SetLineColor(2);
   IBDXsecF1->SetLineWidth(2);
   IBDXsecF1->GetXaxis()->SetLabelFont(42);
   IBDXsecF1->GetXaxis()->SetLabelSize(0.035);
   IBDXsecF1->GetXaxis()->SetTitleSize(0.035);
   IBDXsecF1->GetXaxis()->SetTitleFont(42);
   IBDXsecF1->GetYaxis()->SetLabelFont(42);
   IBDXsecF1->GetYaxis()->SetLabelSize(0.035);
   IBDXsecF1->GetYaxis()->SetTitleSize(0.035);
   IBDXsecF1->GetYaxis()->SetTitleOffset(0);
   IBDXsecF1->GetYaxis()->SetTitleFont(42);
   IBDXsecF1->Draw("same");
   c1_n5->Modified();
   c1_n5->cd();
   c1_n5->SetSelected(c1_n5);
}
