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
	float m = hncoll->GetMean();;
	delete hncoll;


	return m;
}

void UrQMD::Loop()
{

	TH2F * h2 = new TH2F( "b_vs_refmult", "refmult", 4000, 0, 4000, 160, 0, 16 );
	TH2F * h2zs = new TH2F( "b_vs_refmult_zs", "refmult", 4000, 0, 4000, 160, 0, 16 );

	std::vector<std::pair<int, int> > cbins;
	vector<TString> clabel;
	// 80% : 8
	// 75% : 11
	// 70% : 15
	// 65% : 20
	// 60% : 26
	// 55% : 34
	// 50% : 43
	// 45% : 54
	// 40% : 67
	// 35% : 82
	// 30% : 100
	// 25% : 121
	// 20% : 145
	// 15% : 175
	// 10% : 209
	// 5% : 252
	cbins.push_back( std::make_pair( 8, 26 ) ); // 60-80
	cbins.push_back( std::make_pair( 8, 15 ) ); // 70-80
	cbins.push_back( std::make_pair( 15, 26 ) ); // 60-70
	cbins.push_back( std::make_pair( 26, 43 ) ); // 50-60
	cbins.push_back( std::make_pair( 43, 67 ) ); // 40-50
	cbins.push_back( std::make_pair( 67, 100 ) ); // 30-40
	cbins.push_back( std::make_pair( 100, 145 ) ); // 20-30
	cbins.push_back( std::make_pair( 145, 209 ) ); // 10-20
	cbins.push_back( std::make_pair( 209, 252 ) ); // 05-10
	cbins.push_back( std::make_pair( 252, 500 ) ); // 00-05



	TH2F* hpibias[50];
	TH2F* hkbias[50];
	TH2F* hpbias[50];

	TH2F* hpibiasnc[50];
	TH2F* hkbiasnc[50];
	TH2F* hpbiasnc[50];
	vector<float> mean_b;
	vector<float> mean_nc;
	for ( size_t i = 0; i < cbins.size(); i++ ){
		hpibias[i] = ( new TH2F( TString::Format( "pi_bias_%d", i ), "", 400, 0, 4, 200, 0.0, 2 ) );
		hkbias[i] = ( new TH2F( TString::Format( "k_bias_%d", i ), "", 400, 0, 4, 200, 0.5, 2 ) );
		hpbias[i] = ( new TH2F( TString::Format( "p_bias_%d", i ), "", 400, 0, 4, 200, 0.5, 2 ) );

		hpibiasnc[i] = ( new TH2F( TString::Format( "pi_ncoll_bias_%d", i ), "", 400, 0, 4, 200, 0.0, 2 ) );
		hkbiasnc[i] = ( new TH2F( TString::Format( "k_ncoll_bias_%d", i ), "", 400, 0, 4, 200, 0.5, 2 ) );
		hpbiasnc[i] = ( new TH2F( TString::Format( "p_ncoll_bias_%d", i ), "", 400, 0, 4, 200, 0.5, 2 ) );

		mean_b.push_back( mean_b_for_refmult( cbins[i].first, cbins[i].second ) );
		mean_nc.push_back( ncoll_for_b( mean_b[i] ) );
	}


	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;

	

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		float pT_leading_pion   = -1;
		float pT_leading_kaon   = -1;
		float pT_leading_proton = -1;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

		int refmult = 0;
		for (Int_t it = 0; it < Tracks_; it++ ){
			int gid = Tracks_mGeantID[it];
			
			if ( Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5  ){
				if ( 8==gid || 9==gid || 11==gid || 12 ==gid || 14==gid || 15==gid ){
					refmult++;
				}

				if ( 8==gid || 9==gid ){
					if ( Tracks_mPt[it] > pT_leading_pion )
						pT_leading_pion = Tracks_mPt[it];
				}
				if ( 11==gid || 12==gid ){
					if ( Tracks_mPt[it] > pT_leading_proton )
						pT_leading_proton = Tracks_mPt[it];
				}

				if ( 14==gid || 15==gid ){
					if ( Tracks_mPt[it] > pT_leading_kaon )
						pT_leading_kaon = Tracks_mPt[it];
				}

			}



		}

		
		h2->Fill( refmult, b );
		if ( refmult > 0 )
			h2zs->Fill( refmult, b );


		for ( size_t i = 0; i < cbins.size(); i++ ){


			if ( refmult > cbins[i].first && refmult <= cbins[i].second ){
				hpibias[i]->Fill( pT_leading_pion, b / mean_b[i] );
				hkbias[i]->Fill( pT_leading_kaon, b / mean_b[i] );
				hpbias[i]->Fill( pT_leading_proton, b / mean_b[i] );	

				hpibiasnc[i]->Fill( pT_leading_pion, ncoll_for_b( b ) / mean_nc[i] );
				hkbiasnc[i]->Fill( pT_leading_kaon, ncoll_for_b( b ) / mean_nc[i] );
				hpbiasnc[i]->Fill( pT_leading_proton, ncoll_for_b( b ) / mean_nc[i] );	
			}

			
		}


	} // event loop



	h2->Draw("colz");

	TFile * f = new TFile( "output.root", "RECREATE" );
	f->cd();
	h2->Write();
	h2zs->Write();

	for ( size_t i = 0; i < cbins.size(); i++ ){

		hpibias[i]->Write();
		hkbias[i]->Write();
		hpbias[i]->Write();
		hpibiasnc[i]->Write();
		hkbiasnc[i]->Write();
		hpbiasnc[i]->Write();
	}

	f->Write();

}


void UrQMD(){

	TFile *f = new TFile( "output.root" );
	hbrm = (TH2*)f->Get( "b_vs_refmult_zs" )->Clone( "pre_computed" );
	hbrm->SetDirectory( 0 );
	f->Close();

	TFile *f2 = new TFile( "b_vs_ncoll.root" );
	hncoll2d = (TH2*)f2->Get( "b_vs_ncoll" )->Clone( "hncoll2d" );
	hncoll2d->SetDirectory( 0 );
	f2->Close();



	TChain *c = new TChain( "urqmd" );
	c->Add( "/Users/danielbrandenburg/bnl/local/data/urqmd_AuAu_14p5.root" );
	UrQMD *t = new UrQMD( c );
	t->Loop();
}