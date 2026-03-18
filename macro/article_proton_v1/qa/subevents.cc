#include "ris2_noqntools.h"
// #include "src/picture.h"
#include <TAttMarker.h>

void subevents(){
  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style2D.cc" );
  using namespace ris2;

  auto f1_pave = new TPaveText( 0.5, 0.8, 0.55, 0.7, "NDC" );
  f1_pave->SetFillColor(kRed+2);
  f1_pave->AddText("F1");
  f1_pave->SetTextColor(kWhite);

  auto f3_pave = new TPaveText( 0.5, 0.65, 0.55, 0.55, "NDC" );
  f3_pave->SetFillColor(kGreen+2);
  f3_pave->AddText("F3");
  f3_pave->SetTextColor(kWhite);

  auto f2_pave = new TPaveText( 0.57, 0.8, 0.67, 0.55, "NDC" );
  f2_pave->SetFillColor(kBlue+2);
  f2_pave->AddText("F2");
  f2_pave->SetTextColor(kWhite);

  auto plot = Plot( {1000, 1100} );
  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 1.0, 1.0 } )
    .SetXAxis(Axis().SetTitle("#eta").SetLo(0.0).SetHi(8.0))
    .SetYAxis(Axis().SetTitle( "p_{T}#timesq (GeV/c)").SetLo(-3.0).SetHi(3.0) )
    .SetZAxis(Axis().SetTitle("").SetLo(1e2).SetHi(1e5).SetLog())
    .AddPave(f1_pave)
    .AddPave(f3_pave)
    .AddPave(f2_pave)
    .AddToPlot( "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root", "h2_eta_pT_TpOrTn" )
    ;
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/subevents.png" );
};