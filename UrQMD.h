//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 11 12:08:16 2017 by ROOT version 5.34/36
// from TTree urqmd/
// found on file: urqmd_0.tx.root
//////////////////////////////////////////////////////////

#ifndef UrQMD_h
#define UrQMD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxTracks = 5000;

class UrQMD {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Tracks_;
   UInt_t          Tracks_fUniqueID[kMaxTracks];   //[Tracks_]
   UInt_t          Tracks_fBits[kMaxTracks];   //[Tracks_]
   Int_t           Tracks_mGeantID[kMaxTracks];   //[Tracks_]
   Double_t        Tracks_mPt[kMaxTracks];   //[Tracks_]
   Double_t        Tracks_mEta[kMaxTracks];   //[Tracks_]
   Double_t        Tracks_mPhi[kMaxTracks];   //[Tracks_]
   Float_t         b;

   // List of branches
   TBranch        *b_Tracks_;   //!
   TBranch        *b_Tracks_fUniqueID;   //!
   TBranch        *b_Tracks_fBits;   //!
   TBranch        *b_Tracks_mGeantID;   //!
   TBranch        *b_Tracks_mPt;   //!
   TBranch        *b_Tracks_mEta;   //!
   TBranch        *b_Tracks_mPhi;   //!
   TBranch        *b_b;   //!

   UrQMD(TTree *tree=0);
   virtual ~UrQMD();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef UrQMD_cxx
UrQMD::UrQMD(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("urqmd_0.tx.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("urqmd_0.tx.root");
      }
      f->GetObject("urqmd",tree);

   }
   Init(tree);
}

UrQMD::~UrQMD()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t UrQMD::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t UrQMD::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void UrQMD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Tracks", &Tracks_, &b_Tracks_);
   fChain->SetBranchAddress("Tracks.fUniqueID", Tracks_fUniqueID, &b_Tracks_fUniqueID);
   fChain->SetBranchAddress("Tracks.fBits", Tracks_fBits, &b_Tracks_fBits);
   fChain->SetBranchAddress("Tracks.mGeantID", Tracks_mGeantID, &b_Tracks_mGeantID);
   fChain->SetBranchAddress("Tracks.mPt", Tracks_mPt, &b_Tracks_mPt);
   fChain->SetBranchAddress("Tracks.mEta", Tracks_mEta, &b_Tracks_mEta);
   fChain->SetBranchAddress("Tracks.mPhi", Tracks_mPhi, &b_Tracks_mPhi);
   fChain->SetBranchAddress("b", &b, &b_b);
   Notify();
}

Bool_t UrQMD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void UrQMD::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t UrQMD::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef UrQMD_cxx
