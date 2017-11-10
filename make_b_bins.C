


#include "TMath.h"

void make_b_bins(){

	TFile *f = new TFile( "output.root" );

	TH2 * h = (TH2*)f->Get( "b_vs_refmult" );
	TH1 * hb = h->ProjectionY("hb");

	hb->Scale( 1.0 / hb->Integral() );
	hb->Draw();

	TH1 * hc = (TH1*)hb->GetCumulative(true)->Clone( "hcum" );

	hc->Draw();

	for ( float i = 1.0; i >= 0; i -= 0.05  ){
		cout << ceil(i*100) << "% : " << "(" << hc->FindFirstBinAbove( i ) << ") = " << hc->GetBinLowEdge(hc->FindFirstBinAbove( i )) << endl;
	}




}