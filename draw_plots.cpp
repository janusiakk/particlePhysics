#include "TFile.h"
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TStyle.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void draw_plots(int argc, char *argv[]) {
  const fs::path OutDir = (argc > 1) ? fs::path(argv[1]) : fs::current_path();
  const fs::path pngDir = OutDir / "png";
  const fs::path pdfDir = OutDir / "pdf";

  fs::create_directories(pngDir);
  fs::create_directories(pdfDir);
  TFile *f = TFile::Open("analysis.root");
  // Null ptr handling
  if (!f) {
    std::cout << "Failed to open \"analysis.root\"";
    return;
  }

}
