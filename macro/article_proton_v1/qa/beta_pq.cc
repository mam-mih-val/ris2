#include "ris2_noqntools.h"
// #include "src/picture.h"
#include <TAttMarker.h>

void beta_pq(){
  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style2D.cc" );
  using namespace ris2;
  gStyle->SetPadTopMargin(0.15);

  auto plot = Plot( {2000, 1100} );
  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 0.5, 1.0 } )
    .AddText( Text().SetText("TOF-400").SetPosition({0.2, 0.9}).SetSize(0.05) )
    .SetXAxis(Axis().SetTitle("p/q (GeV/c)").SetLo(0.0).SetHi(8.0))
    .SetYAxis(Axis().SetTitle("#beta").SetLo(0.2).SetHi(1.2))
    .SetZAxis(Axis().SetTitle("").SetLo(1e2).SetHi(1e5).SetLog())
    .AddToPlot( "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root", "h2_pq_beta_tof400" )
    ;
  plot.AddSubPlot( std::vector<double>{ 0.5, 0.0, 1.0, 1.0 } )
    .AddText( Text().SetText("TOF-700").SetPosition({0.2, 0.9}).SetSize(0.05) )
    .SetXAxis(Axis().SetTitle("p/q (GeV/c)").SetLo(0.0).SetHi(8.0))
    .SetYAxis(Axis().SetTitle("#beta").SetLo(0.2).SetHi(1.2))
    .SetZAxis(Axis().SetTitle("").SetLo(1e2).SetHi(1e5).SetLog())
    .AddToPlot( "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root", "h2_pq_beta_tof700" )
    ;
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/beta_pq.png" );
};