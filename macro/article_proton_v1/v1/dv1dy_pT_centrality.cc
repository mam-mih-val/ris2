#include "ris2.h"
// #include "src/wrap.h"
// #include "src/wrap.h"
#include <Axis.hpp>
#include <Rtypes.h>
#include <TAttMarker.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <string>

void dv1dy_pT_centrality(){
  using namespace ris2;

  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style.cc" );
  
  std::vector<double> centrality_edges{ 10, 30 };
  std::vector<double> y_egdes{ 0.5, 1.0 };
  std::vector<double> pT_egdes;
  
  const std::string file_pT = "/home/mikhail/ris2/macro/article_proton_v1/files/dv1dy.pT.proton.2024.06.18.root";
  const std::string file_c = "/home/mikhail/ris2/macro/article_proton_v1/files/dv1dy.centrality.proton.2024.06.18.root";

  auto bunch_pT = Bunch<Correlation>{};
  bunch_pT
    .AddToBunch(
      "v_{1}{F1}",
      file_pT,
      std::vector<std::string>{
          "fit_par1",
    })
  ;

  auto bunch_c = Bunch<Correlation>{};
  bunch_c
    .AddToBunch(
      "v_{1}{F1}",
      file_c,
      std::vector<std::string>{
          "fit_par1",
    })
  ;
  
  bunch_pT.GetPalette().SetPalette( std::vector{
      Style().SetColor( kRed ).SetMarker(kFullCircle),
  } );

  bunch_c.GetPalette().SetPalette( std::vector{
      Style().SetColor( kRed ).SetMarker(kFullCircle),
  } );
  
  auto pT_proj = bunch_pT;
  pT_proj.Perform( []( auto& w ){
    w
      .Project( std::vector<Qn::AxisD>{{"trPt", 5, 0.4, 1.4}} ); 
  } );
  
  auto c_proj = bunch_c;

  auto plot = Plot( {2000, 1100} );
  
  auto zero_line_pT = new TLine( 0.0, 0.0, 2.0, 0.0 );
  zero_line_pT->SetLineStyle(9);
  
  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 0.5, 1.0 } )
      .SetXAxis(Axis().SetTitle("p_{T} (GeV/c)").SetLo(0.0).SetHi(1.5))
      .SetYAxis(Axis().SetTitle("dv_{1}/dy").SetLo(0.01).SetHi(0.65))
      .AddText( Text().SetText("Xe+CsI 3.8A GeV").SetPosition({0.25, 0.9}).SetSize(0.04) )
      .AddText( Text().SetText("10-30%; -0.2<y_{cm}<0.8").SetPosition({0.25, 0.85}).SetSize(0.035) )
      .AddToPlot( *pT_proj )
      // .AddLine( zero_line_pT )
      ;
  
  plot.AddSubPlot( std::vector<double>{ 0.5, 0.0, 1.0, 1.0 } )
      .SetXAxis(Axis().SetTitle("centrality (%)").SetLo(0.0).SetHi(40.0))
      .SetYAxis(Axis().SetTitle("dv_{1}/dy").SetLo(0.01).SetHi(0.65))
      .AddText( Text().SetText("Xe+CsI 3.8A GeV").SetPosition({0.25, 0.9}).SetSize(0.04) )
      .AddText( Text().SetText("0.4<p_{T}<2 (GeV/c); -0.2<y_{cm}<0.8").SetPosition({0.25, 0.85}).SetSize(0.035) )
      .AddToPlot( *c_proj )
      // .AddLine( zero_line_pT )
      ;
  
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/dv1dy_pT_centrality.png" );
}