

int findCentrality( TH1 * hc, double c ){
	for ( int i = 1; i < hc->GetXaxis()->GetNbins()+1; i++ ){
		float bc = hc->GetBinContent( i );
		if ( bc >= c ) return i-1;
	}
	return -1;
}


void centrality(){

	TFile * f = new TFile( "b_vs_refmult.root" );
	TH2 * h = (TH2*)f->Get( "b_vs_refmult" );

	TH1 * hRefMult = h->ProjectionX( "hRefMult" );
	
	hRefMult->SetBinContent( 1, 0 );

	hRefMult->Scale( 1.0 / hRefMult->Integral() );
	TH1 * hCum = hRefMult->GetCumulative();

	for ( float c = 0.0; c < 1.0; c += 0.05 ){
		cout << "Centrality " << (1.0-c) << " = " << findCentrality( hCum, c ) << endl;
	}


}