


#include "TMath.h"

void make_refmult_bins(){

	TFile *f = new TFile( "output.root" );

	TH2 * h = (TH2*)f->Get( "b_vs_refmult_zs" );
	TH1 * hrm = h->ProjectionX("hrm");

	hrm->Scale( 1.0 / hrm->Integral() );
	hrm->Draw();

	TH1 * hc = (TH1*)hrm->GetCumulative(false)->Clone( "hcum" );

	hc->Draw();

	for ( float i = 1.0; i >= 0; i -= 0.05  ){
		cout << ceil(i*100) << "% : " << hc->FindLastBinAbove( i ) << endl;
	}




}