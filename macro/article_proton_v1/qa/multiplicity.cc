#include "ris2_noqntools.h"
// #include "src/picture.h"
#include <TAttMarker.h>

void multiplicity(){
  using namespace ris2;

  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style.cc" );

  auto with_target = Wrap<Histogram>( 
    "W. target"s, 
    "/home/mikhail/ris2/macro/article_proton_v1/files/qa.2026.03.18.root"s,
    "h1_ref_multiplicity"s
  );
  with_target.SetStyle( Style().SetMarker(-1).SetColor( kBlue+2 ) );
  with_target.Perform( [](auto p){ p->Scale( 1.0 / p->Integral() ); } );

  auto leg = new TLegend( 0.6, 0.8, 0.9, 0.9 );
  leg->AddEntry( with_target.GetResult()->Clone(), "w. target", "L" );

  auto plot = Plot( {1000, 1100} );

  auto lines = std::vector<TLine*>{};
  auto multiplicity_edges = std::vector<int>{ 206, 98, 70, 49, 34, 22, 14, 8, 0  };

  with_target.Perform( [&lines, &multiplicity_edges](auto p) mutable { 
    for( auto& edge : multiplicity_edges ){
      auto bin = p->GetXaxis()->FindBin( edge );
      auto val = p->GetBinContent( bin );
      lines.push_back( new TLine( edge, 0, edge, val ) );
    }
  } );

// Upper plots
  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 1.0, 1.0 } )
    .SetXAxis(Axis().SetTitle("Reference N_{ch}").SetLo(0.0).SetHi(400.0))
    .SetYAxis(Axis().SetTitle("dN/dN_{ch}").SetLo(0.000001).SetHi(0.05).SetLog())
    .AddText( Text().SetText("BM@N Xe+CsI E_{kin}=3.8#it{A} GeV").SetPosition({0.25, 0.9}).SetSize(0.035) )
    .AddToPlot( with_target )
    // .AddLegend(leg)
    .AddLine(lines[0])
    .AddLine(lines[1])
    .AddLine(lines[2])
    .AddLine(lines[3])
    .AddLine(lines[4])
  ;
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/multiplicity.png" );
};