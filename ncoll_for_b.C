



double ncoll_for_b( double bb1, double bb2 ){

	TFile *f = new TFile( "b_vs_ncoll.root" );

	TH2 * h = (TH2*)f->Get( "b_vs_ncoll" );

	int b1 = h->GetYaxis()->FindBin( bb1 );
	int b2 = h->GetYaxis()->FindBin( bb2 );
	// cout << "ncoll from " << b1 << " to " << b2 << endl;
	TH1 * hncoll = h->ProjectionX( "ncoll", b1, b2 );

	return hncoll->GetMean();


}