


double meanNcoll( TChain *c, double b ){
	TH1D * htemp = new TH1D( "htemp", "htemp", 2000, 0, 2000 );
	TString cut = TString::Format( "b > %f && b < %f", b -0.5, b+0.5 );
	c->Draw( "ncoll>>htemp", cut );
	float m = htemp->GetMean();
	cout << "mean ncoll @ b=" << b <<  " : " << m << endl; 
	delete htemp;
	return m;
}

double meanErrorNcoll( TChain *c, double b ){
	TH1D * htemp = new TH1D( "htemp", "htemp", 2000, 0, 2000 );
	TString cut = TString::Format( "b > %f && b < %f", b -0.5, b+0.5 );
	c->Draw( "ncoll>>htemp", cut );
	float m = htemp->GetMeanError();
	delete htemp;
	return m;
}



void ncoll_bias(){
	

	TChain *c = new TChain( "tree" );
	c->Add( "glauber_nominal.root" );

	TFile *f = new TFile( "bias_midrapidity_check.root" );

	TH1 * hbbias = new TH1F( "hbbias", "", 10, 0, 100 );
	TH1 * hncollbias = new TH1F( "hncollbias", "", 10, 0, 100 );

	TH1 * hbbias2 = new TH1F( "hbbias2", "", 5, 0, 100 );
	TH1 * hncollbias2 = new TH1F( "hncollbias2", "", 5, 0, 100 );

	size_t NCs = 10;

	int clow[] = {
		0, 
		10,
		20,
		30,
		40,
		50,
		60,
		60,
		70,
		0
	};

	int chigh[] = {
		10, 
		20,
		30,
		40,
		50,
		60,
		70,
		80,
		80,
		5
	};


	TFile *fout = new TFile( "bias_ncoll.root" , "RECREATE" );
	fout->cd();

	for ( size_t i = 0; i < NCs; i++ ){
		int c1 = clow[i];
		int c2 = chigh[i];

		TString title = TString::Format( "b_vs_leading_pion_c%d_%d", c1, c2 );


		TH2 * h2 = (TH2*)f->Get( title );
		TProfile *pfx = h2->ProfileX();

		TF1 * f1 = new TF1( "fpol0", "pol0" );
		pfx->Fit( f1, "QR", "", 0, 10 );
		float m0 = f1->GetParameter(0);
		float e0 = f1->GetParError(0);
		cout << "mean (0<pT): " << m0 << endl;

		pfx->Fit( f1, "QR", "", 1.0, 10 );
		float m1 = f1->GetParameter(0);
		float e1 = f1->GetParError(0);
		cout << "mean (1.5<pT): " << m1 << endl;

		float v = m1/m0;

		float mnc0 = meanNcoll(c, m0);
		float mnc1 = meanNcoll(c, m1);
		float enc0 = meanNcoll(c, m0) - meanNcoll(c, m0 + e0);
		float enc1 = meanNcoll(c, m1) - meanNcoll(c, m1 + e1);
		float vnc = mnc1 / mnc0;
		float enc = (enc0/mnc0 + enc1/mnc1) * vnc;

		int ibin = (c1+c2)/20.0 +1;
		if ( c1 == 60 && c2 == 80 ){
			ibin = (c1+c2)/40.0 +1;
			hbbias2->SetBinContent( ibin, v );
			hbbias2->SetBinError( ibin, (e0/m0 + e1/m1) * v );
			hncollbias2->SetBinContent( ibin, vnc  );
			hncollbias2->SetBinError( ibin, enc );
		} else {
			hbbias->SetBinContent( ibin, v );
			hbbias->SetBinError( ibin, (e0/m0 + e1/m1) * v );
			hncollbias->SetBinContent( ibin, vnc  );
			hncollbias->SetBinError( ibin, enc );
		}

		

		// if ( c1 == 60 && c2 == 80 ){
		// 	hbbias2->SetBinContent( ibin-1, v );
		// 	hbbias2->SetBinError( ibin-1, (e0/m0 + e1/m1) * v );
		// 	hbbias2->SetBinContent( ibin, v );
		// 	hbbias2->SetBinError( ibin, (e0/m0 + e1/m1) * v );

		// 	hncollbias2->SetBinContent( ibin, vnc  );
		// 	hncollbias2->SetBinError( ibin, enc );
		// 	hncollbias2->SetBinContent( ibin-1, vnc  );
		// 	hncollbias2->SetBinError( ibin-1, enc );
		// }
		

	}


	hbbias->Write();
	hncollbias->Write();

	hbbias2->Write();
	hncollbias2->Write();

	fout->Write();

	
}