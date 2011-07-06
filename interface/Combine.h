#ifndef HiggsAnalysis_CombinedLimit_Combine_h
#define HiggsAnalysis_CombinedLimit_Combine_h
#include <TString.h>
#include <boost/program_options.hpp>

class TDirectory;
class TTree;
class LimitAlgo;
class RooWorkspace;
class RooAbsData;
namespace RooStats { class ModelConfig; }

extern Float_t t_cpu_, t_real_, g_quantileExpected_;
//RooWorkspace *writeToysHere = 0;
extern TDirectory *outputFile;
extern TDirectory *writeToysHere;
extern TDirectory *readToysFromHere;
extern LimitAlgo * algo, * hintAlgo ;
extern int verbose;
extern bool withSystematics;
extern bool doSignificance_;
extern float cl;

class Combine {
public:
  Combine() ;
  
  boost::program_options::options_description & statOptions() { return statOptions_; }    
  boost::program_options::options_description & ioOptions() { return ioOptions_; }    
  boost::program_options::options_description & miscOptions() { return miscOptions_; }    
  void applyOptions(const boost::program_options::variables_map &vm) ;
  
  void run(TString hlfFile, const std::string &dataset, double &limit, double &limitErr, int &iToy, TTree *tree, int nToys);
  
private:
  bool mklimit(RooWorkspace *w, RooStats::ModelConfig *mc_s, RooStats::ModelConfig *mc_b, RooAbsData &data, double &limit, double &limitErr) ;
  
  boost::program_options::options_description statOptions_, ioOptions_, miscOptions_;
 
  // statistics-related variables
  bool unbinned_, generateBinnedWorkaround_; 
  float rMin_, rMax_;
  std::string prior_;
  bool hintUsesStatOnly_;
  bool toysNoSystematics_;
  bool toysFrequentist_;
  float expectSignal_;

  // input-output related variables
  bool saveWorkspace_;
  std::string workspaceName_;
  std::string modelConfigName_, modelConfigNameB_;
  bool validateModel_;
  bool saveToys_;
  float mass_;

  // implementation-related variables
  bool compiledExpr_;
  bool makeTempDir_;
  bool rebuildSimPdf_;
  bool optSimPdf_;
};

#endif
