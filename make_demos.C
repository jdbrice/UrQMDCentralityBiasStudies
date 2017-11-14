


void make_demos(){

	gStyle->SetOptStat( 0 );
	TCanvas *can = new TCanvas( "c", "", 1200, 800 );
	TFile *f = new TFile( "output.root" );


	TH2 * hpi = (TH2*)f->Get( "pi_bias_60_80" );
	hpipx = hpi->ProfileX();
	
	hpipx->SetMarkerColor(kBlack);
	hpipx->SetMarkerStyle(8);

	hpi->Draw("colz");
	hpi->SetTitle( "pions in 60-80% Central events; p_{T} (GeV/c) of leading pion" );
	hpi->GetYaxis()->SetRangeUser( 0.8, 1.2 );
	hpi->GetXaxis()->SetRangeUser( 0.0, 2.2 );

	hpipx->Draw("same");
	can->Print( "pi_bias_60_80_wpx.png" );


	TH2 * hp = (TH2*)f->Get( "p_bias_60_80" );
	hppx = hp->ProfileX();
	
	hppx->SetMarkerColor(kBlack);
	hppx->SetMarkerStyle(8);

	hp->Draw("colz");
	hp->SetTitle( "p in 60-80% Central events; p_{T} (GeV/c) of leading p" );
	hp->GetYaxis()->SetRangeUser( 0.8, 1.2 );
	hp->GetXaxis()->SetRangeUser( 0.0, 2.2 );

	hppx->Draw("same");
	can->Print( "p_bias_60_80_wpx.png" );

	TH2 * hk = (TH2*)f->Get( "k_bias_60_80" );
	hkpx = hk->ProfileX();
	
	hkpx->SetMarkerColor(kBlack);
	hkpx->SetMarkerStyle(8);

	hk->Draw("colz");
	hk->SetTitle( "k in 60-80% Central events; p_{T} (GeV/c) of leading k" );
	hk->GetYaxis()->SetRangeUser( 0.8, 1.2 );
	hk->GetXaxis()->SetRangeUser( 0.0, 2.2 );

	hkpx->Draw("same");
	can->Print( "k_bias_60_80_wpx.png" );



	TH2 * hpi = (TH2*)f->Get( "pi_track_bias_60_80" );
	hpipx = hpi->ProfileX();
	
	hpipx->SetMarkerColor(kBlack);
	hpipx->SetMarkerStyle(8);

	hpi->Draw("colz");
	hpi->SetTitle( "pions in 60-80% Central events; p_{T} (GeV/c) of all pions" );
	hpi->GetYaxis()->SetRangeUser( 0.8, 1.2 );
	hpi->GetXaxis()->SetRangeUser( 0.0, 2.2 );

	hpipx->Draw("same");
	can->Print( "pi_track_bias_60_80_wpx.png" );


	TH2 * hpi = (TH2*)f->Get( "pi_ncoll_track_bias_60_80" );
	hpipx = hpi->ProfileX();
	
	hpipx->SetMarkerColor(kBlack);
	hpipx->SetMarkerStyle(8);

	hpi->Draw("colz");
	hpi->SetTitle( "pions in 60-80% Central events; p_{T} (GeV/c) of all pions" );
	hpi->GetYaxis()->SetRangeUser( 0.0, 2 );
	hpi->GetXaxis()->SetRangeUser( 0.0, 2.2 );

	hpipx->Draw("same");
	can->Print( "pi_ncoll_track_bias_60_80_wpx.png" );

}