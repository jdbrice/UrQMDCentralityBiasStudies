#define UrQMD_cxx
#include "UrQMD.h"
#include <TH2F.h>
#include "TH1D.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>

#include <iostream>

using namespace std;


TH2 * hbrm = NULL;
TH2 * hncoll2d = NULL;

double mean_b_for_refmult( int rm1, int rm2 ){
	return hbrm->ProjectionY( "b", rm1+1, rm2+1 )->GetMean();
}

float ncoll_for_b( double b, double db = 0.1 ){

	int b1 = hncoll2d->GetYaxis()->FindBin( b - db );
	int b2 = hncoll2d->GetYaxis()->FindBin( b + db );
	// cout << "ncoll from " << b1 << " to " << b2 << endl;
	TH1 * hncoll = hncoll2d->ProjectionX( "ncoll", b1, b2 );
	float m = hncoll->GetRandom();
	delete hncoll;


	return m;
}

void UrQMD::Loop()
{

	int maxRM = 1000;
	TH2F * h2 = new TH2F( "b_vs_refmult", "refmult", maxRM, 0, maxRM, 200, 0, 20 );
	TH2F * h2zs = new TH2F( "b_vs_refmult_zs", "refmult", maxRM, 0, maxRM, 200, 0, 20 );
	TH2F * hbncoll = new TH2F( "b_vs_ncoll", "refmult", maxRM, 0, maxRM, 200, 0, 20 );
	TH2F * hrmncoll = new TH2F( "refmul_vs_ncoll", "refmult", maxRM, 0, maxRM, maxRM, 0, maxRM );

	


	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;

	

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		int refmult = 0;
		float Ncoll = ncoll_for_b( b );

		for (Int_t it = 0; it < Tracks_; it++ ){
			int gid = Tracks_mGeantID[it];
			
			if ( Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5  ){
				if ( 8==gid || 9==gid || 11==gid || 12 ==gid || 14==gid || 15==gid ){
					refmult++;
				}
			}
		}

		
		h2->Fill( refmult, b );
		if ( refmult > 0 )
			h2zs->Fill( refmult, b );

		hbncoll->Fill( Ncoll, b );
		hrmncoll->Fill( Ncoll, refmult );


	} // event loop


	TFile * f = new TFile( "output_aggregate.root", "RECREATE" );
	f->cd();
	h2->Write();
	h2zs->Write();
	hbncoll->Write();
	hrmncoll->Write();

	f->Write();

}


void aggregate(){

	TFile *f2 = new TFile( "b_vs_ncoll.root" );
	hncoll2d = (TH2*)f2->Get( "b_vs_ncoll" )->Clone( "hncoll2d" );
	hncoll2d->SetDirectory( 0 );
	f2->Close();



	TChain *c = new TChain( "urqmd" );
	c->Add( "urqmd_AuAu_14p5.root" );
	UrQMD *t = new UrQMD( c );
	t->Loop();
}