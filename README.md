# hAM_WL
C/C++ code for human atrial cell models; Colman et al. Frontiers in Physiology 2018 (https://www.frontiersin.org/articles/10.3389/fphys.2018.01211/full)

23/06/2019 - Fix: Small issue with writing the settings file for the Tissue model has been fixed, so it writes now to correct folder.
             [output_settings_tissue(Sim, Tissue, directory) -> output_settings_tissue(Sim, Tissue, res_dir_full) in Tissue_native_main.cc]

20/06/2019 - UPDATE: New code format (in-line with the full MSCSF) now uploaded; small error in Maleckar model Ito v1/2 has been corrected.
