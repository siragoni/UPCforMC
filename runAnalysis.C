// to run:
//   alien-token-init
//   source /tmp/gclient_env_501
//   aliroot runAnalysis.C\(opt\)


// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "AliAnalysisTaskUPCforwardMC.h"

void runAnalysis(Int_t opt)
{


  /**
   * RUN ON LOCAL:
   */
  // Bool_t local    = kTRUE;
  // Bool_t gridTest = kFALSE;

  /**
   * RUN ON GRIDTEST:
   */
  Bool_t local    = kFALSE;
  Bool_t gridTest = kTRUE;


  /**
   * FULL GRID MOD:
   */
  // Bool_t local    = kFALSE;
  // Bool_t gridTest = kFALSE;



  Int_t listOfGoodRunNumbersLHC18l7[] = { 295585, 295586, 295587, 295588, 295589, 295612,
                                          295615, 295665, 295666, 295667, 295668, 295671,
                                          295673, 295675, 295676, 295677, 295714, 295716,
                                          295717, 295718, 295719, 295723, 295725, 295753,
                                          295754, 295755, 295758, 295759, 295762, 295763,
                                          295786, 295788, 295791, 295816, 295818, 295819,
                                          295822, 295825, 295826, 295829, 295831, 295854,
                                          295855, 295856, 295859, 295860, 295861, 295863,
                                          295881, 295908, 295909, 295910, 295913, 295936,
                                          295937, 295941, 295942, 295943, 295945, 295947, // 60
                                          296061, 296062, 296063, 296065, 296066, 296068,
                                          296123, 296128, 296132, 296133, 296134, 296135,
                                          296142, 296143, 296191, 296192, 296194, 296195,
                                          296196, 296197, 296198, 296241, 296242, 296243,
                                          296244, 296246, 296247, 296269, 296270, 296273,
                                          296279, 296280, 296303, 296304, 296307, 296309,
                                          296312, 296376, 296377, 296378, 296379, 296380, // mind that 296376 is rejected by data
                                          296381, 296383, 296414, 296419, 296420, 296423,
                                          296424, 296433, 296472, 296509, 296510, 296511,
                                          296514, 296516, 296547, 296548, 296549, 296550, // 60
                                          296551, 296552, 296553, 296615, 296616, 296618,
                                          296619, 296622, 296623, // end 18q MC
                                          296690, 296691, 296694, 296749, 296750, 296781,
                                          296784, 296785, 296786, 296787, 296791, 296793,
                                          296794, 296799, 296836, 296838, 296839, 296848,
                                          296849, 296850, 296851, 296852, 296890, 296894,
                                          296899, 296900, 296903, 296930, 296931, 296932,
                                          296934, 296935, 296938, 296941, 296966, 296967,
                                          296968, 296969, 296971, 296975, 296976, 296977, // 296977 is rejected
                                          296979, 297029, 297031, 297035, 297085, 297117, // 57
                                          297118, 297119, 297123, 297124, 297128, 297129,
                                          297132, 297133, 297193, 297194, 297196, 297218,
                                          297219, 297221, 297222, 297278, 297310, 297312,
                                          297315, 297317, 297363, 297366, 297367, 297372,
                                          297379, 297380, 297405, 297408, 297413, 297414,
                                          297415, 297441, 297442, 297446, 297450, 297451,
                                          297452, 297479, 297481, 297483, 297512, 297537,
                                          297540, 297541, 297542, 297544, 297558, 297588,
                                          297590, 297595, 297623, 297624 };               // 52  = 229



  Int_t listOfGoodRunNumbersLHC15o[] = { /*244918,*/ 244980, 244982, 244983, 245064, 245066, 245068, 245145, 245146, 245151,
                                         245152, 245231, 245232, 245233, 245253, 245259, 245343, 245345, 245346, 245347,
                                         245353, 245401, 245407, 245409, 245410, 245446, 245450, 245496, 245501, 245504,
                                         245505, 245507, 245535, 245540, 245542, 245543, 245554, 245683, 245692, 245700,
                                         245705, 245729, 245731, 245738, 245752, 245759, 245766, 245775, 245785, 245793,
                                         245829, 245831, 245833, 245949, 245952, 245954, 245963, 245996, 246001, 246003,
                                         246012, 246036, 246037, 246042, 246048, 246049, 246053, 246087, 246089, 246113,
                                         246115, 246148, 246151, 246152, 246153, 246178, 246181, 246182, 246217, 246220,
                                         246222, 246225, 246272, 246275, 246276, 246390, 246391, 246392, 246424, 246428,
                                         246431, 246433, 246434, 246487, 246488, 246493, 246495, 246675, 246676, 246750,
                                         246751, 246755, 246757, 246758, 246759, 246760, 246763, 246765, 246804, 246805,
                                         246806, 246807, 246808, 246809, 246844, 246845, 246846, 246847, 246851, 246855,
                                         246859, 246864, 246865, 246867, 246871, 246930, 246937, 246942, 246945, 246948,
                                         246949, 246980, 246982, 246984, 246989, 246991, 246994       //136
                                       };


    // since we will compile a class, tell root where to look for headers
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("AliAnalysisTaskUPCforwardMC.cxx++g");
    AliAnalysisTaskUPCforwardMC *task = reinterpret_cast<AliAnalysisTaskUPCforwardMC*>(gInterpreter->ExecuteMacro("AddTaskUPCforwardMC.C"));
#else
    gROOT->LoadMacro("AliAnalysisTaskUPCforwardMC.cxx++g");
    gROOT->LoadMacro("AddTaskUPCforwardMC.C");
    AliAnalysisTaskUPCforwardMC *task = AddTaskUPCforwardMC();
#endif


    if(!mgr->InitAnalysis()) return;
    // mgr->SetDebugLevel(2);
    // mgr->PrintStatus();
    // mgr->SetUseProgressBar(1, 25);

    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)

        // FILE *f = fopen("listMCsample.txt","r");
        FILE *f = fopen("listAxE.txt","r");
        // FILE *f = fopen("list.txt","r");
        char fileadd[300];
        Int_t flaggingValue = 0;
        while(fscanf(f,"%s",fileadd)==1){
            // chain->AddFile(fileadd);
            flaggingValue = chain->Add(fileadd);
            if(flaggingValue == 0) std::cout << fileadd << std::endl;
            flaggingValue = 0;
        }


        // chain->Add("AliAOD/*");

        // chain->Add("LHC18q/0001/*");
        // chain->Add("LHC18q/0002/*");
        // chain->Add("LHC18q/0003/*");
        // chain->Add("LHC18q/0004/*");
        // chain->Add("LHC18q/0005/*");
        // chain->Add("LHC18q/0006/*");
        // chain->Add("LHC18q/0007/*");
        // chain->Add("LHC18q/0008/*");
        // chain->Add("LHC18q/0009/*");

        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskUPCforwardMC.cxx AliAnalysisTaskUPCforwardMC.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskUPCforwardMC.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20181028_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");
        // select the input data for 2018 q
        // alienHandler->SetCheckCopy(kFALSE);



      // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kTwoGammaToMuMedium/");
      // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kIncohJpsiToMu/");
      // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kIncohPsi2sToMuPi/");
      alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohJpsiToMu/");
      // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohJpsiToMuLP/");
      // alienHandler->SetGridDataDir("/alice/sim/2018/LHC18l7/kCohJpsiToMuNP/");
  	  alienHandler->SetDataPattern("*AOD/*AliAOD.root");
      // for( Int_t iRunLHC18l7 = 20; iRunLHC18l7 <  229; iRunLHC18l7++){
      for( Int_t iRunLHC18l7 = 0; iRunLHC18l7 <  228; iRunLHC18l7++){
        // if ( listOfGoodRunNumbersLHC18l7[iRunLHC18l7] == 296269 ) continue;
        alienHandler->AddRunNumber( listOfGoodRunNumbersLHC18l7[iRunLHC18l7] );
      }

      // alienHandler->AddRunNumber(295829);



      // alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2a/");
      // // alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2i/");
      // // alienHandler->SetGridDataDir("/alice/sim/2016/LHC16b2j/");
  	  // alienHandler->SetDataPattern("*AOD/*AliAOD.root");
      // for( Int_t iRunLHC15o = 0; iRunLHC15o < 136; iRunLHC15o++){
      //   // if( fRunNum == listOfGoodRunNumbersLHC15o[iRunLHC15o] ) checkIfGoodRun = kTRUE;
      //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC15o[iRunLHC15o] );
      // }


      // alienHandler->AddRunNumber(245729);


        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(50);
        alienHandler->SetExecutable("MC.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("MC.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with "kTRUE" and "full" for normal run
        // to merge on grid run jobs in SetRunMode("terminate")
        // to collect final results set SetMergeViaJDL(kFALSE)
        alienHandler->SetMergeViaJDL(kTRUE);

        /* - The setting to kFALSE is to download the output files
           -
         */
        // alienHandler->SetMergeViaJDL(kFALSE);
        alienHandler->SetMaxMergeStages(3);


        TString LHC18l7("LHC18l7");
        TString LHC16b2("LHC16b2a");
        // define the output folders
        alienHandler->SetGridWorkingDir("MC_LHC18l7_QT_AxE");
        alienHandler->SetGridOutputDir(LHC18l7.Data());
        // alienHandler->SetGridOutputDir(LHC18l7.Data());



        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(2);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis

            /* - The option FULL is to send the full analysis.
               -
             */
            alienHandler->SetRunMode("full");

            /* - This option TERMINATE is used for the merging of the files.
               -
             */
            // alienHandler->SetRunMode("terminate");
            mgr->StartAnalysis("grid");
        }
    }
}

/* -
 * - Welcome my dear ALICE user! To use ALICE software from CVMFS:
 * - List all packages         --> alienv q
 * - List AliPhysics packages  --> alienv q | grep -i aliphysics
 * - Enable a specific package --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1
 * - Enable multiple packages  --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1,VO_ALICE@fastjet::v3.2.1_1.024-alice3-7
 */
