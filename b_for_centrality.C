


void b_for_centrality(int mlow, int mhigh ){
	TFile * f = new TFile( "b_vs_refmult.root" );
	TFile * f2 = new TFile( "b_vs_ncoll.root" );
	TH2 * h = (TH2*)f->Get( "b_vs_refmult" );
	TH2 * hbncoll = (TH2*)f2->Get( "b_vs_ncoll" );


	TH1 * hb = h->ProjectionY( "b", mlow+1, mhigh+1 );

	TCanvas *can1 = new TCanvas( "can1", "" );
	hb->Draw();
	float avgb = hb->GetMean();

	TCanvas *can2 = new TCanvas( "can2", "" );
	int bin1 = hbncoll->GetYaxis(  )->FindBin( avgb );
	int bin2 = hbncoll->GetYaxis(  )->FindBin( avgb );
	TH1 * hncoll = hbncoll->ProjectionX( "hncoll", bin1, bin2 );
	hncoll->Draw();

	float ncoll_cent[] = {
		9.32,  // 75%-80%
		14.05, // 70%-75%
		21.03, // 65%-70%
		29.40,
		41.17,
		58.22,
		81.03,
		108.87,
		145.26,
		192.08,
		247.28,
		315.65,
		400.63,
		633.51,
		787.91
	};

}
	

