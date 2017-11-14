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
TH2 * hrmncoll = NULL;

double mean_b_for_refmult( int rm1, int rm2 ){
	if ( NULL == hbrm )
		assert( 0 );
	return hbrm->ProjectionY( "b", rm1+1, rm2+1 )->GetMean();
}

double mean_ncoll_for_refmult( int rm1, int rm2 ){
	if ( NULL == hrmncoll )
		assert( 0 );
	return hrmncoll->ProjectionX( "ncoll", rm1+1, rm2+1 )->GetMean();
}

float ncoll_for_b( double b, double db = 0.1 ){

	if ( NULL == hncoll2d )
		assert( 0 );
	int b1 = hncoll2d->GetYaxis()->FindBin( b - db );
	int b2 = hncoll2d->GetYaxis()->FindBin( b + db );
	// cout << "ncoll from " << b1 << " to " << b2 << endl;
	TH1 * hncoll = hncoll2d->ProjectionX( "ncoll", b1, b2 );
	float m = hncoll->GetRandom();;
	delete hncoll;


	return m;
}

void UrQMD::Loop()
{
	cout << "Loop()" << endl;
	TH2F * h2 = new TH2F( "b_vs_refmult", "refmult", 4000, 0, 4000, 200, 0, 20 );
	TH2F * h2zs = new TH2F( "b_vs_refmult_zs", "refmult", 4000, 0, 4000, 200, 0, 20 );

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
	cbins.push_back( std::make_pair( 8, 500 ) ); clabel.push_back( "00_80" );// 00-80
	cbins.push_back( std::make_pair( 8, 26 ) ); clabel.push_back( "60_80" );// 60-80
	cbins.push_back( std::make_pair( 8, 15 ) ); clabel.push_back( "70_80" );// 70-80
	cbins.push_back( std::make_pair( 15, 26 ) ); clabel.push_back( "60_70" ); // 60-70
	cbins.push_back( std::make_pair( 26, 43 ) ); clabel.push_back( "50_60" ); // 50-60
	cbins.push_back( std::make_pair( 43, 67 ) ); clabel.push_back( "40_50" ); // 40-50
	cbins.push_back( std::make_pair( 67, 100 ) ); clabel.push_back( "30_40" ); // 30-40
	cbins.push_back( std::make_pair( 100, 145 ) ); clabel.push_back( "20_30" ); // 20-30
	cbins.push_back( std::make_pair( 145, 209 ) ); clabel.push_back( "10_20" ); // 10-20
	cbins.push_back( std::make_pair( 209, 252 ) ); clabel.push_back( "05_10" ); // 05-10
	cbins.push_back( std::make_pair( 252, 500 ) ); clabel.push_back( "00_05" ); // 00-05



	TH2F* hpibias[50];
	TH2F* hkbias[50];
	TH2F* hpbias[50];

	TH2F* hpitbias[50];
	TH2F* hktbias[50];
	TH2F* hptbias[50];

	TH2F* hpibiasnc[50];
	TH2F* hkbiasnc[50];
	TH2F* hpbiasnc[50];

	TH2F* hpitbiasnc[50];
	TH2F* hktbiasnc[50];
	TH2F* hptbiasnc[50];

	vector<float> mean_b;
	vector<float> mean_nc;

	cout << "Making centrality histograms" << endl;
	for ( size_t i = 0; i < cbins.size(); i++ ){
		hpibias[i] = ( new TH2F( TString::Format( "pi_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{#pi} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hkbias[i] = ( new TH2F( TString::Format( "k_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{k} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hpbias[i] = ( new TH2F( TString::Format( "p_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{p} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );

		hpitbias[i] = ( new TH2F( TString::Format( "pi_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{#pi} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hktbias[i] = ( new TH2F( TString::Format( "k_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{k} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hptbias[i] = ( new TH2F( TString::Format( "p_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{p} (GeV/c); b / <b>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );

		hpibiasnc[i] = ( new TH2F( TString::Format( "pi_ncoll_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{#pi} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hkbiasnc[i] = ( new TH2F( TString::Format( "k_ncoll_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{k} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hpbiasnc[i] = ( new TH2F( TString::Format( "p_ncoll_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{p} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );

		hpitbiasnc[i] = ( new TH2F( TString::Format( "pi_ncoll_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{#pi} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hktbiasnc[i] = ( new TH2F( TString::Format( "k_ncoll_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{k} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );
		hptbiasnc[i] = ( new TH2F( TString::Format( "p_ncoll_track_bias_%s", clabel[i].Data() ), TString::Format( "%s; p_{T}^{p} (GeV/c); N_{coll} / <N_{coll}>|_{C}", clabel[i].Data() ), 400, 0, 4, 200, 0.0, 5 ) );

		mean_b.push_back( mean_b_for_refmult( cbins[i].first, cbins[i].second ) );
		mean_nc.push_back( mean_ncoll_for_refmult( cbins[i].first, cbins[i].second ) );
	}

	cout << "Looping on events" << endl;

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

		if ( ientry % 100 == 0 ){
			cout << "." << std::flush;
		}

		int refmult = 0;
		float Ncoll = ncoll_for_b( b );

		for (Int_t it = 0; it < Tracks_; it++ ){
			int gid = Tracks_mGeantID[it];
			
			if ( Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5  ){
				if ( 8==gid || 9==gid || 11==gid || 12 ==gid || 14==gid || 15==gid ){
					refmult++;
				}

				if ( (8==gid || 9==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
					if ( Tracks_mPt[it] > pT_leading_pion )
						pT_leading_pion = Tracks_mPt[it];
				}
				if ( (11==gid || 12==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
					if ( Tracks_mPt[it] > pT_leading_proton )
						pT_leading_proton = Tracks_mPt[it];
				}

				if ( (14==gid || 15==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
					if ( Tracks_mPt[it] > pT_leading_kaon )
						pT_leading_kaon = Tracks_mPt[it];
				}
			}
		}

		for (Int_t it = 0; it < Tracks_; it++ ){
			int gid = Tracks_mGeantID[it];

			for ( size_t i = 0; i < cbins.size(); i++ ){
				// float rand_ncoll = ncoll_for_b( b );
				if ( refmult > cbins[i].first && refmult <= cbins[i].second ){
					if ( (8==gid || 9==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
						hpitbias[i]->Fill( Tracks_mPt[it], b / mean_b[i] );
						hpitbiasnc[i]->Fill( Tracks_mPt[it], Ncoll / mean_nc[i] );
					}
					if ( (11==gid || 12==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
						hptbias[i]->Fill( Tracks_mPt[it], b / mean_b[i] );
						hptbiasnc[i]->Fill( Tracks_mPt[it], Ncoll / mean_nc[i] );
					}

					if ( (14==gid || 15==gid) && Tracks_mPt[it] > 0.15 && fabs(Tracks_mEta[it]) < 0.5){
						hktbias[i]->Fill( Tracks_mPt[it], b / mean_b[i] );
						hktbiasnc[i]->Fill( Tracks_mPt[it], Ncoll / mean_nc[i] );
					}

				} // check centrality bin
			} // loop on centrality bins
		} // loop on tracks again

		
		h2->Fill( refmult, b );
		if ( refmult > 0 )
			h2zs->Fill( refmult, b );


		for ( size_t i = 0; i < cbins.size(); i++ ){
			if ( refmult > cbins[i].first && refmult <= cbins[i].second ){
				hpibias[i]->Fill( pT_leading_pion, b / mean_b[i] );
				hkbias[i]->Fill( pT_leading_kaon, b / mean_b[i] );
				hpbias[i]->Fill( pT_leading_proton, b / mean_b[i] );	

				float rand_ncoll = ncoll_for_b( b );
				hpibiasnc[i]->Fill( pT_leading_pion, rand_ncoll / mean_nc[i] );
				hkbiasnc[i]->Fill( pT_leading_kaon, rand_ncoll / mean_nc[i] );
				hpbiasnc[i]->Fill( pT_leading_proton, rand_ncoll / mean_nc[i] );	
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

		hpitbias[i]->Write();
		hktbias[i]->Write();
		hptbias[i]->Write();

		hpibiasnc[i]->Write();
		hkbiasnc[i]->Write();
		hpbiasnc[i]->Write();

		hpitbiasnc[i]->Write();
		hktbiasnc[i]->Write();
		hptbiasnc[i]->Write();
	}

	f->Write();

}


void UrQMD(){

	TFile *f = new TFile( "output_aggregate.root" );
	hbrm = (TH2*)f->Get( "b_vs_refmult_zs" )->Clone( "pre_computed_b_vs_refmult" );
	hbrm->SetDirectory( 0 );
	hrmncoll = (TH2*) f->Get( "refmul_vs_ncoll" )->Clone("pre_computed_refmult_vs_ncoll");
	hrmncoll->SetDirectory( 0 );
	f->Close();

	TFile *f2 = new TFile( "b_vs_ncoll.root" );
	hncoll2d = (TH2*)f2->Get( "b_vs_ncoll" )->Clone( "hncoll2d" );
	hncoll2d->SetDirectory( 0 );
	f2->Close();



	TChain *c = new TChain( "urqmd" );
	c->Add( "urqmd_AuAu_14p5.root" );
	UrQMD *t = new UrQMD( c );
	t->Loop();
}