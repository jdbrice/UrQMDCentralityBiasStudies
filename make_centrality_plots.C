




void make_centrality_plots( TString plc = "pi" ){

	TCanvas * c = new TCanvas( "c", "", 1600, 800 );
	TFile *f = new TFile( "output.root" );

	gStyle->SetOptStat(0);
	TH1D* b_vs_cbin_frame = new TH1D( "b_vs_cbin_frame", ";%Centrality ;N_{coll} bias", 100, 0, 85 );

	const int n = 7;
	float x[n], y[n], ex[n], ey[n];

	vector<TString> clabel;
	// x[0] = 40; ex[0] = 40; clabel.push_back( "00_80" );// 00-80
	x[0] = 70; ex[0] = 10; clabel.push_back( "60_80" );// 60-80
	x[1] = 55; ex[1] = 5; clabel.push_back( "50_60" ); // 50-60
	x[2] = 45; ex[2] = 5; clabel.push_back( "40_50" ); // 40-50
	x[3] = 35; ex[3] = 5; clabel.push_back( "30_40" ); // 30-40
	x[4] = 25; ex[4] = 5; clabel.push_back( "20_30" ); // 20-30
	x[5] = 15; ex[5] = 5; clabel.push_back( "10_20" ); // 10-20
	x[6] = 5; ex[6] = 5; clabel.push_back( "05_10" ); // 05-10
	// x[7] = 75; ex[7] = 5; clabel.push_back( "70_80" );// 70-80
	// x[8] = 65; ex[8] = 5; clabel.push_back( "60_70" ); // 60-70
	// x[10] = 2.5; ex[10] = 2.5; clabel.push_back( "00_05" ); // 00-05

	for ( int i = 0; i < n; i++ ){
		TString name = TString::Format( "%s_ncoll_track_bias_%s", plc.Data(), clabel[i].Data() );
		cout << "get " << name << endl;
		TH2 * h2 = (TH2*) f->Get( name );
		y[i] = h2->GetMean(2);
		ey[i] = h2->GetMeanError(2) * 10;
	}

	TGraphErrors * b_vs_cbin = new TGraphErrors( n, x, y, ex, ey );

	b_vs_cbin_frame->Draw();
	b_vs_cbin_frame->GetYaxis()->SetRangeUser( 0.9, 1.1 );

	b_vs_cbin->SetMarkerStyle(8);
	b_vs_cbin->SetMarkerSize(2);

	b_vs_cbin->Draw("same Ep");
	c->Print( "ncoll_bias_vs_cbin.pdf" );


}