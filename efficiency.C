void efficiency()
{
    TFile * file = new TFile("/Users/gwon/cut_nocut/hist_2D_purity.root");

    TH1F * efficiency_arm = new TH1F("efficiency","efficiency",20,0,200);
    TH1F * efficiency_time = new TH1F("efficiency","efficiency",25,0,25);

    TH1F * cut_arm = new TH1F;
    TH1F * cut_time = new TH1F;
    TH1F * nocut_arm = new TH1F;
    TH1F * nocut_time = new TH1F;

    cut_arm = (TH1F*)file->Get("cut_arm");
    cut_time = (TH1F*)file->Get("cut_time");
    nocut_arm = (TH1F*)file->Get("nocut_arm");
    nocut_time = (TH1F*)file->Get("nocut_time");

    for(int i = 1; i < 1000; i++)
    {
        efficiency_arm->SetBinContent(i,cut_arm->GetBinContent(i)/nocut_arm->GetBinContent(i));
        efficiency_time->SetBinContent(i,cut_time->GetBinContent(i)/nocut_time->GetBinContent(i));
    }

    float a=0, b=0;
    for(int i = 1; i < 27; i++)
    {
        a += efficiency_time->GetBinContent(i);
        //cout<<i<<","<<efficiency_time->GetBinContent(i)<<endl;;
    }
    for(int i = 1; i < 22; i++)
    {
        b += efficiency_arm->GetBinContent(i);
        //cout<<i<<","<<efficiency_arm->GetBinContent(i)<<endl;;
    }
    cout<<"/////////////////"<<endl;
    cout<<a<<"  ,  "<<b<<endl;
    cout<<"/////////////////"<<endl;

    /*
    TCanvas * can = new TCanvas;
    can->Divide(2,1);
    can->cd(1);
    efficiency_arm->GetXaxis()->SetTitle("Lever arm [cm]");
    efficiency_arm->GetYaxis()->SetRangeUser(0,1);
    efficiency_arm->SetStats(false);
    efficiency_arm->Draw();
    can->cd(2);
    efficiency_time->GetXaxis()->SetTitle("time [ns]");
    efficiency_time->GetYaxis()->SetRangeUser(0,1);
    efficiency_time->SetStats(false);
    efficiency_time->Draw();
    */

    /*
    TFile * cut = new TFile("/Users/gwon/0.5MeV_cut.root");
    TFile * nocut = new TFile("/Users/gwon/nocut.root");
    TH1D * hist_cut_x = new TH1D("x","x",20,0,200);

    TH2F * hist_cut = new TH2F;
    hist_cut = (TH2F*)cut->Get("hist_number_of_signal");
    for(int i = 0; i<20; i++)
    {
        hist_cut_x->SetBinContent(i,hist_cut->Integral(i*10,i*10+10,0,25));
        //hist_cut_x->SetBinContent(i,i*1);
    }

    
    TH2F * hist_nocut = new TH2F;
    hist_nocut = (TH2F*)nocut->Get("hist_number_of_signal");

    TCanvas * can = new TCanvas;
    TH2F *efficiency = new TH2F("efficiency","efficiency",20,0,200,25,0,25);
    for(int i = 0; i < 10000; i++)
    {
        float temp;
        if(hist_nocut->GetBinContent(i) != 0)
            temp = hist_cut->GetBinContent(i)/hist_nocut->GetBinContent(i);
        else
            temp = 0;
        if(temp != 0)
            efficiency->SetBinContent(i,temp);
        else
            efficiency->SetBinContent(i,0);
    }
    efficiency->SetStats(false);
    //efficiency->Draw("colz");
    hist_cut_x->Draw();
    */
}
