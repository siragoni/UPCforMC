please find 4 files in the attachment. These files have a simple task to run over 2018 data and produce some simple histograms. (The files are slight modifications of original files sent to me by Tomas: thanks!)

 The email is a bit long and may not be clear, so if you have questions, just ask.

 (*)
 Michal argued in favour of each student developing her/his own code. The files in the attachment are a shell for it.
 You have to keep putting in what you need for your particular analyses.

 (*)
 To make this practical, Michal produced so called 'nano-AOD' files containing all events with UPC like events for MUFAST cluster (ie, the J/Psi in the muon spectrometer). The address of the most up-to-date files can be found in the Nano AOD section of https://twiki.cern.ch/twiki/bin/viewauth/ALICE/UltraPeripheralCollisions

 (*)
 The macros I sent can be used to analyse local files or to submit to the GRID.

 (*)
 Let's start with local files. You have to open runAnalysis..C and make sure that the first line reads:
Bool_t local = kTRUE;

 Then you should have downloaded one Nano AOD files for tests. I use for example the file in
/alice/data/2018/LHC18q/000296510/muon_calo_pass2/PWGUD/UD_PbPb_AOD/421_20190103-1942/0002
  This file has enough events for most of the tests you may want to try.

 You should modify the line
 chain->Add("AliAOD.UPCNano.root");
 in runAnalysis..C to point to the file you have downloaded.

 Then you just run as:
 aliroot runAnalysis.C\(opt\)
 where opt is a number 0 or 1, which is only important for GRID submission. That's it.
 You can now modify the code (ie, add new histograms) and test that it works.

 (*)
 Once you are ready to run on the GRID, you get your token (alien-token-init), source the environment (eg, for my own computer 'source /tmp/gclient_env_501' but the number may be different in your system), make sure that you have in runAnalysis..C
Bool_t local = kFALSE;
Bool_t gridTest = kFALSE;

 And run the program: aliroot runAnalysis.C\(opt\)

 Right now I have submitted with opt = 0 and got only 7 jobs ... so this should be quite fast.

 *important* note that I did not optimise the TTL information. Michal, can you make sure that it is reasonable?

 (*)
 That's it. You should be able to run over all 2018 data quite fast. Also, if you add the corresponding info, over 2015 data. If you have any problem, please report to this list: Michal is the real expert, you three can profit from the problems found by others and Orlando and I need to be kept in the loop to be better supervisors.*









The complete structure of this directory is the following:

*AliAnalysisTaskUPCforward* with .cxx .h files, are the core of the analysis
*runAnalysis.C* and *AddMyTask.C* are needed for the AliEn environment
*AnalysisResults...root* are the analysis files obtained at the end, with the label for the date
*fitMacros/* contains my trial macros, unneeded now
*fitFinal/*  contains the final fit macros after development
*Starlight/* contains all that is needed for the Starlight simulations  
