#include <TROOT.h>
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
using namespace std;
void draw_plots(const char *outDirArg = "") {
  // Output dir management
  const fs::path OutDir = (std::string(outDirArg) != "") ? fs::path(outDirArg) : fs::current_path();
  const fs::path pngDir = OutDir / "png";
  const fs::path pdfDir = OutDir / "pdf";

  fs::create_directories(pngDir);
  fs::create_directories(pdfDir);
  TFile *f = TFile::Open("analysis.root");
  //Render canvases offscreen
  gROOT->SetBatch(kTRUE);

  // Null ptr handling
  if (!f) {
    cerr << "Failed to open \"analysis.root\"";
    return;
  }

  // Predefined histograms
  const vector<string> species = {
      "charged", "piPlus", "piMinus", "kPlus", "kMinus", "proton", "pbar",
  };
  const vector<string> histTypes = {"hN", "hPt", "hEta", "hPhi"};

  // Read checker for future pdf
  bool ok = 1;
  for (const string &h : histTypes) {
    for (const string &s : species) {
      const string name = h + "_" + s;
      TH1D *hist = f->Get<TH1D>(name.c_str());
      if (!hist) {
        cerr << "Histogram not found: " << name << "\n";
        ok = 0;
        continue;
      }
      // Canvas loop
      TCanvas *c = new TCanvas(("c_" + name).c_str(), name.c_str(), 1600, 900);
      hist->Draw();
      c->SaveAs((pngDir / (name + ".png")).string().c_str());
      c->SaveAs((pdfDir / (name + ".pdf")).string().c_str());
      delete c;
    }
  }

  f->Close();
}
