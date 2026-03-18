#include "ris2_noqntools.h"
// #include "src/picture.h"
#include <TAttMarker.h>

void m2_pq(){
  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style2D.cc" );
  using namespace ris2;
  gStyle->SetPadTopMargin(0.15);

  auto plot = Plot( {2000, 1100} );
  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 0.5, 1.0 } )
    .AddText( Text().SetText("TOF-400").SetPosition({0.2, 0.9}).SetSize(0.05) )
    .SetXAxis(Axis().SetTitle("p/q (GeV/c)").SetLo(-2.0).SetHi(8.0))
    .SetYAxis(Axis().SetTitle("m^{2} (GeV^{2}/c^{4})").SetLo(-0.5).SetHi(9.5))
    .SetZAxis(Axis().SetTitle("v_{1}").SetLog())
    .AddToPlot( "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root", "h2_pq_mass2_tof400" )
    ;
  plot.AddSubPlot( std::vector<double>{ 0.5, 0.0, 1.0, 1.0 } )
    .AddText( Text().SetText("TOF-700").SetPosition({0.2, 0.9}).SetSize(0.05) )
    .SetXAxis(Axis().SetTitle("p/q (GeV/c)").SetLo(-2.0).SetHi(8.0))
    .SetYAxis(Axis().SetTitle("m^{2} (GeV^{2}/c^{4})").SetLo(-0.5).SetHi(9.5))
    .SetZAxis(Axis().SetTitle("v_{1}").SetLog())
    .AddToPlot( "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root", "h2_pq_mass2_tof700" )
    ;
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/m2_pq.png" );
};