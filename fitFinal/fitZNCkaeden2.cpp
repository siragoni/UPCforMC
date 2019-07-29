#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooCBShape.h"
#include "RooGenericPdf.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TMath.h"
#include "TF1.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooExponential.h"
#include "TLatex.h"
using namespace RooFit;
using namespace std;
#include <math.h>
#include <vector>


//_____________________________________________________________________________
/* - Fit function for the ZNC plots.
   -
 */
void fitZNC(const char* AnalysisName){
  /* - There are three cases for the selectionFlag:
     - 1) = 0 ; this implies the traditional pt-integrated plot;
     - 2) = 1 ; this is instead the coherent component;
     - 3) = 2 ; this is the incoherent component;
     - 4) = 3 ; ******************* ;
     -
   */
  TFile* fileList = new TFile(AnalysisName);
  TDirectory* dir = fileList->GetDirectory("MyTask");
  /* - At this level you could check if everything was okay.
   * - We do a dir->ls() to find out! We get:
   *   dir->ls();
   *   TDirectoryFile*		MyTask	MyTask
   *   KEY: TList	MyOutputContainer;1	Doubly linked list
   */
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);
  /* - We now do the same as before to ascertain if the TList was there and
   * - to try to retrieve the plots. Result:
   *   listings->ls()
   *     OBJ: TList	  MyOutputContainer	          Doubly linked list          : 0
   *     OBJ: TH1F	  fNumberMuonsH	              fNumberMuonsH               : 0 at: 0x5a145f0
   *     OBJ: TH1F	  fCounterH	                  fCounterH                   : 0 at: 0x5a3b570
   *     OBJ: TH1F	  fEtaMuonH	                  fEtaMuonH                   : 0 at: 0x5a3ba80
   *     OBJ: TH1F	  fRAbsMuonH	                fRAbsMuonH                  : 0 at: 0x5a3c0c0
   *     OBJ: TH1F	  fInvariantMassDistributionH	fInvariantMassDistributionH : 0 at: 0x5a3c720
   */
  TH1F *fZNCEnergyAgainstEntriesH = (TH1F*)listings->FindObject("fZNCEnergyAgainstEntriesH");
  fZNCEnergyAgainstEntriesH->Rebin(5);
  fZNCEnergyAgainstEntriesH->Draw();

  /* - This distribution is modelled as the sum of many different gaussians.
     - We add them up together in order to obtain stuff for the ZNC...
     - Maybe something related to the calibration?
     -
   */
  RooRealVar      x             ("x"  ,           "x",   -200.,  1000.0  );
  RooRealVar      mean0Neutrons ("mean0Neutrons",  "",     0,   -5,    5 );
  RooRealVar      sigma0Neutrons("sigma0Neutrons", "",    20,    0,   25 );
  RooRealVar      mean1Neutron  ("mean1Neutron",   "",   200,   190, 220 );
  RooRealVar      sigma1Neutron ("sigma1Neutron",  "",    30,    20,  50 );
  RooRealVar      mean2Neutrons ("mean2Neutrons",  "",   380,   360, 400 );
  RooRealVar      sigma2Neutrons("sigma2Neutrons", "",    30,    20,  70 );
  RooRealVar      mean3Neutrons ("mean3Neutrons",  "",   600,   580, 620 );
  RooRealVar      sigma3Neutrons("sigma3Neutrons", "",    30,    20,  70 );
  /* - The gaussian pdfs.
     -
   */
  RooGaussian     gauss0N("gauss0N","gauss0N", x, mean0Neutrons, sigma0Neutrons);
  RooGaussian     gauss1N("gauss1N","gauss1N", x, mean1Neutron,  sigma1Neutron );
  RooGaussian     gauss2N("gauss2N","gauss2N", x, mean2Neutrons, sigma2Neutrons);
  RooGaussian     gauss3N("gauss3N","gauss3N", x, mean3Neutrons, sigma3Neutrons);
  /* - The respective values for the global pdf's normalizations
     -
   */
  RooRealVar n0Neutrons    ("n0Neutrons",     "",  30000,  20000., 40000.);
  RooRealVar n1Neutron     ("n1Neutron",      "",   2000,   1000.,  2500.);
  RooRealVar n2Neutrons    ("n2Neutrons",     "",   1000,    100.,  2000.);
  RooRealVar n3Neutrons    ("n3Neutrons",     "",    500,    100.,  1000.);
  RooRealVar nAnyNeutrons  ("nAnyNeutrons",   "",   3000,    200.,  5000.);


  RooAddPdf* anyNeutrons = new RooAddPdf( "anyNeutrons", "",
                                          RooArgList( gauss1N,    gauss2N,    gauss3N ),
                                          RooArgList( n1Neutron,  n2Neutrons, n3Neutrons )
                                         );
  /* - We now create the fit function used to fit the data. Hopefully it should
     - work!
     -
   */
  RooAddPdf* fit = new RooAddPdf( "fit", "",
                                  RooArgList( gauss0N,     *anyNeutrons ),
                                  RooArgList( n0Neutrons,  nAnyNeutrons )
                                 );
  RooDataHist* fZNCEnergyAgainstEntriesRoofitH = new RooDataHist( "fZNCEnergyAgainstEntriesH",
                                                                  "",
                                                                  x,
                                                                  fZNCEnergyAgainstEntriesH
                                                                  );
  RooFitResult* fFitResult = fit->fitTo( *fZNCEnergyAgainstEntriesRoofitH,
                                          RooFit::Save(),
                                          Range(-190, 700)
                                         );
  new TCanvas( "ZNCEnergy", "ZNCEnergy", 900, 800 );
  gPad->SetMargin(0.13,0.01,0.12,0.01);
  gPad->SetLogy();


  /* - Beautifying is starting now.
     -
   */
  RooPlot* frame = x.frame();
  frame->SetTitle(  Form(  ";ZNC Energy [a.u.];Counts / (%.0f a.u.)",
                           fZNCEnergyAgainstEntriesH->GetXaxis()->GetBinWidth(1)  )  );
  fZNCEnergyAgainstEntriesRoofitH->plotOn( frame, MarkerStyle(kFullCircle), MarkerSize(1)     );
  fit                            ->plotOn( frame, LineColor(kBlue),         LineStyle(kSolid) );
  fit                            ->plotOn( frame, Components(gauss0N),      LineColor(kMagenta), LineStyle(kSolid)  );
  fit                            ->plotOn( frame, Components(gauss1N),      LineColor(kRed),     LineStyle(kSolid)  );
  fit                            ->plotOn( frame, Components(gauss2N),      LineColor(kGreen+1), LineStyle(kDashed) );
  fit                            ->plotOn( frame, Components(gauss3N),      LineColor(kGreen+2), LineStyle(kDashed) );
  frame->GetXaxis()->SetTitleOffset(1.25);
  // frame->GetYaxis()->SetTitleOffset(1.25);
  frame->GetYaxis()->SetTitleOffset(1.45);
  frame->GetXaxis()->SetTitleSize(0.045);
  frame->GetYaxis()->SetTitleSize(0.045);
  frame->GetXaxis()->SetLabelSize(0.045);
  frame->GetYaxis()->SetLabelSize(0.045);
  frame->GetXaxis()->SetTitleFont(42);
  frame->GetYaxis()->SetTitleFont(42);
  frame->GetXaxis()->SetLabelFont(42);
  frame->GetYaxis()->SetLabelFont(42);
  frame->GetXaxis()->SetNdivisions(408);
  frame->GetYaxis()->SetRangeUser(5,fZNCEnergyAgainstEntriesH->GetMaximum()*10.);
  // gPad ->SetLogy();
  frame->Draw();
  TLatex* latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(42);
  latex->SetTextAlign(11);
  latex->SetNDC();
  latex->DrawLatex(0.17,0.94,"ALICE Performance, PbPb #sqrt{s_{NN}} = 5.02 TeV");
  latex->SetTextSize(0.045);
  // latex->DrawLatex(0.55,0.84,"UPC, #it{L} = 235 ub^{-1}");
  latex->DrawLatex(0.55,0.84,"UPC, LHC18q+LHC18r data");
  // latex->DrawLatex(0.55,0.78,"#it{p}_{T}-integrated");
  latex->DrawLatex(0.55,0.78,Form("%.1f < y < %.1f",-4.0,-2.5));
  latex->DrawLatex(0.55,0.72,Form("N_{0 neutrons} = %.0f #pm %.0f", n0Neutrons.getVal(), n0Neutrons.getError()));
  latex->DrawLatex(0.55,0.66,Form("N_{1 neutrons} = %.0f #pm %.0f",  n1Neutron.getVal(),  n1Neutron.getError()));
  latex->DrawLatex(0.55,0.60,Form("N_{2 neutrons} = %.0f #pm %.0f", n2Neutrons.getVal(), n2Neutrons.getError()));
  latex->DrawLatex(0.55,0.54,Form("N_{3 neutrons} = %.0f #pm %.0f", n3Neutrons.getVal(), n3Neutrons.getError()));
  // latex->DrawLatex(0.55,0.58,Form("m_{0 neutrons} = %.0f #pm %.0f", mean0Neutrons.getVal(), mean0Neutrons.getError()));
  // latex->DrawLatex(0.55,0.54,Form("m_{1 neutron } = %.0f #pm %.0f",  mean1Neutron.getVal(),  mean1Neutron.getError()));
  // latex->DrawLatex(0.55,0.50,Form("m_{2 neutrons} = %.0f #pm %.0f", mean2Neutrons.getVal(), mean2Neutrons.getError()));
  // latex->DrawLatex(0.55,0.46,Form("m_{3 neutrons} = %.0f #pm %.0f", mean3Neutrons.getVal(), mean3Neutrons.getError()));
  // latex->DrawLatex(0.55,0.42,Form("s_{0 neutrons} = %.0f #pm %.0f", sigma0Neutrons.getVal(), sigma0Neutrons.getError()));
  // latex->DrawLatex(0.55,0.38,Form("s_{1 neutron } = %.0f #pm %.0f",  sigma1Neutron.getVal(),  sigma1Neutron.getError()));
  // latex->DrawLatex(0.55,0.34,Form("s_{2 neutrons} = %.0f #pm %.0f", sigma2Neutrons.getVal(), sigma2Neutrons.getError()));
  // latex->DrawLatex(0.55,0.30,Form("s_{3 neutrons} = %.0f #pm %.0f", sigma3Neutrons.getVal(), sigma3Neutrons.getError()));
  /* - Chi square computation.
     -
   */
  RooChi2Var chi2_lowstat("chi2_lowstat","chi2",*fit,*fZNCEnergyAgainstEntriesRoofitH) ;
  latex->DrawLatex(0.55,0.18,Form("      #tilde{#chi}^{2} = %.2f / %.2d = %.2f  ",
                                  chi2_lowstat.getVal(),
                                  fZNCEnergyAgainstEntriesRoofitH->numEntries() - fit->getParameters(*fZNCEnergyAgainstEntriesRoofitH)->selectByAttrib("Constant",kFALSE)->getSize(),
                                  chi2_lowstat.getVal()/( fZNCEnergyAgainstEntriesRoofitH->numEntries() - fit->getParameters(*fZNCEnergyAgainstEntriesRoofitH)->selectByAttrib("Constant",kFALSE)->getSize() )
                                   )
                                 );
  gPad->SaveAs("pngResults/fZNCEnergyAgainstEntries.png", "RECREATE");
}
