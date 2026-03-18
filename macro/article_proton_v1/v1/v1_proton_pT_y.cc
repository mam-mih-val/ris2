#include "ris2.h"
// #include "src/wrap.h"
// #include "src/wrap.h"
#include <Axis.hpp>
#include <Rtypes.h>
#include <TAttMarker.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <string>

void v1_proton_pT_y(){
  using namespace ris2;

  gROOT->Macro( "/home/mikhail/ris2/macro/article_proton_v1/style.cc" );
  
  std::vector<double> centrality_edges{ 10, 30 };
  std::vector<double> y_egdes{ 0.5, 1.0 };
  std::vector<double> pT_egdes;

  std::string file_vf = "/home/mikhail/ris2/macro/bmn_run8/analysis_note/files/vf.recent.clean.2024.06.18.root";
  auto v1_data = DoubleDifferential{
      "RUN8",
      file_vf,
      std::vector<std::string>{
          "proton/v1.F2_RESCALED(F1_RESCALED,F3_RESCALED).y1y1centrality",
          "proton/v1.F3_RESCALED(F1_RESCALED,F2_RESCALED).y1y1centrality",
    }
  };
  v1_data.SetPalette( std::vector{
    Style().SetColor( kRed ).SetMarker(kFullCircle),
    Style().SetColor( kGreen+2 ).SetMarker(kFullTriangleUp),
    Style().SetColor( kBlue ).SetMarker(kFullSquare),
    Style().SetColor( kViolet ).SetMarker(kFullTriangleDown),
  });

  v1_data.Perform( []( auto& w ){ w.Rebin( std::vector{Qn::AxisD{ "centrality", 1, 10, 30 } } ); } );

  auto v1_pT_y = v1_data;
  v1_pT_y.SetSliceAxis(Qn::AxisD{ "trPt", 3, 0.2, 1.4 });
  v1_pT_y.SetProjectionAxis(Qn::AxisD{ "trProtonY", 6, -0.2, 1.0 });

  auto vec_pT_y = *v1_pT_y;
  auto sys_pT_y = std::vector< Wrap<Graph> >{};
  for( auto v1 : vec_pT_y ){
    sys_pT_y.emplace_back( v1.GetTitle(), dynamic_cast<Graph*>(v1.GetResult()->Clone()) );
    sys_pT_y.back().Perform( []( const auto& g1 ){
      for( auto i=int{0}; i<g1->GetN(); ++i ){
        auto y_err = g1->GetPointY(i) * 0.08;
        g1->SetPointError(i, 0.035, y_err);
      }
    });
    sys_pT_y.back().SetStyle(v1.GetStyle());
    sys_pT_y.back().SetOption("2"s);
  }

  auto v1_y_pT = v1_data;
  v1_y_pT.SetProjectionAxis(Qn::AxisD{ "trPt", 9, 0.2, 2.0 });
  v1_y_pT.SetSliceAxis(Qn::AxisD{ "trProtonY", 4, 0.2, 1.0 });

  auto vec_y_pT = *v1_y_pT;
  auto sys_y_pT = std::vector< Wrap<Graph> >{};
  for( auto v1 : vec_y_pT ){
    sys_y_pT.emplace_back( v1.GetTitle(), dynamic_cast<Graph*>(v1.GetResult()->Clone()) );
    sys_y_pT.back().Perform( []( const auto& g1 ){
      for( auto i=int{0}; i<g1->GetN(); ++i ){
        auto y_err = g1->GetPointY(i) * 0.08;
        g1->SetPointError(i, 0.035, y_err);
      }
    });
    sys_y_pT.back().SetStyle(v1.GetStyle());
    sys_y_pT.back().SetOption("2"s);
  }

  // auto leg = new TLegend( 0.25, 0.8, 0.55, 0.65 );
  auto leg_y = v1_pT_y.MakeLegend("p_{T}", "GeV/c", std::vector{0.25, 0.85, 0.8, 0.65});
  auto leg_pT = v1_y_pT.MakeLegend("y", "", std::vector{0.25, 0.85, 0.8, 0.65});
  
  auto plot = Plot( {2000, 1100} );
  
  auto zero_line_y = new TLine( -0.2, 0.0, 1.0, 0.0 );
  zero_line_y->SetLineStyle(9);

  auto zero_line_pT = new TLine( 0.0, 0.0, 1.4, 0.0 );
  zero_line_pT->SetLineStyle(9);

  plot.AddSubPlot( std::vector<double>{ 0.0, 0.0, 0.5, 1.0 } )
    .SetXAxis(Axis().SetTitle("y_{cm}").SetLo(-0.2).SetHi(1.0))
    .SetYAxis(Axis().SetTitle("v_{1}").SetLo(-0.05).SetHi(0.6))
    .AddText( Text().SetText("BM@N 10-30%").SetPosition({0.25, 0.9}).SetSize(0.04) )
    .AddToPlot( (*v1_pT_y) )
    .AddToPlot( sys_pT_y )
    .AddLegend( leg_y )
    .AddLine( zero_line_y )
    ;
  plot.AddSubPlot( std::vector<double>{ 0.5, 0.0, 1.0, 1.0 } )
    .SetXAxis(Axis().SetTitle("p_{T} (GeV/c)").SetLo(0.0).SetHi(1.4))
    .SetYAxis(Axis().SetTitle("v_{1}").SetLo(-0.01).SetHi(0.7))
    .AddText( Text().SetText("BM@N 10-30%").SetPosition({0.25, 0.9}).SetSize(0.04) )
    .AddToPlot( (*v1_y_pT) )
    .AddToPlot( sys_y_pT )
    .AddLegend( leg_pT )
    .AddLine( zero_line_pT )
    ;
  plot.Print( "/home/mikhail/ris2/macro/article_proton_v1/pic/v1_proton_pT_y.png" );
}