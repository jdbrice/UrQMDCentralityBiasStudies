
#include "ncoll_for_b.C"

TH2 * hbrm = NULL;
TH1 * hbb = NULL;
double b_for_refmult( int rm1, int rm2 ){
	return hbrm->ProjectionY( "b", rm1+1, rm2+1 )->GetMean();
}

double avg_b_in_range( double b1, double b2 ){
	hbb->GetXaxis()->SetRangeUser( b1, b2 );
	return hbb->GetMean();
}

void compare_refmult_vs_b( int rm1=8, int rm2=26, double b1=10.9, double b2=12.6, string label="60-80%" ){

	TFile *f = new TFile( "output.root" );
	hbrm = (TH2*)f->Get( "b_vs_refmult_zs" );
	hbb = hbrm->ProjectionY( "bonly" );

	cout << label << ":" << endl;
	double bfrm = b_for_refmult( rm1, rm2 );
	double avgb = avg_b_in_range( b1, b2 );
	float ncollrm = ncoll_for_b( bfrm - 0.1, bfrm + 0.1 );
	float ncollb = ncoll_for_b( b1, b2 );
	cout << "b (rm) = " << bfrm << ", b (avg) = " << avgb << endl;
	cout << "<ncoll> = " << ncollrm << " == " << ncollb << endl;
	cout << "<ncoll>(rm) / <ncoll>(b) = " << ncollrm / ncollb << endl;

}