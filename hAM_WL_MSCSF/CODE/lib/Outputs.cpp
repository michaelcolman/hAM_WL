// Source code associated with  ===========================  //
// "Multi-scale cardiac simulation framework" =============  //
// For simulation of cardiac cellular and tissue dynamics =  //
// from the spatial cellular to full organ scales. ========  //
// With implementation of multiple, published cell models =  //
// as well as novel models developed in my lab. ===========  //
// ========================================================  //
// This file: Outputs. For outputting settings, data and ==  //
// disclaimer references to file and screen ===============  //
// ========================================================  //
// GNU 3 LICENSE TEXT =====================================  //
// COPYRIGHT (C) 2016-2019 MICHAEL A. COLMAN ==============  //
// THIS PROGRAM IS FREE SOFTWARE: YOU CAN REDISTRIBUTE IT =  //
// AND/OR MODIFY IT UNDER THE TERMS OF THE GNU GENERAL ====  //
// PUBLIC LICENSE AS PUBLISHED BY THE FREE SOFTWARE =======  //
// FOUNDATION, EITHER VERSION 3 OF THE LICENSE, OR (AT YOUR  //
// OPTION) ANY LATER VERSION. =============================  //
// THIS PROGRAM IS DISTRIBUTED IN THE HOPE THAT IT WILL BE=  //
// USEFUL, BUT WITHOUT ANY WARRANTY; WITHOUT EVEN THE =====  //
// IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR A ===  //
// PARTICULAR PURPOSE.  SEE THE GNU GENERAL PUBLIC LICENSE=  //
// FOR MORE DETAILS. ======================================  //
// YOU SHOULD HAVE RECEIVED A COPY OF THE GNU GENERAL =====  //
// PUBLIC LICENSE ALONG WITH THIS PROGRAM.  IF NOT, SEE ===  //
// <https://www.gnu.org/licenses/>. =======================  //
// ========================================================  //
// ADDITIONAL LICENSE TEXT ================================  //
// THIS SOFTWARE IS PROVIDED OPEN SOURCE AND MAY BE FREELY=  //
// USED, DISTRIBUTED AND UPDATED, PROVIDED: ===============  //
//  (i) THE APPROPRIATE WORK(S) IS(ARE) CITED. THIS =======  //
//      PERTAINS TO THE CITATION OF COLMAN 2019 PLOS COMP =  //
//      BIOL (FOR THIS IMPLEMTATION) AND ALL WORKS ========  //
//      ASSOCIATED WITH THE SPECIFIC MODELS AND COMPONENTS=  //
//      USED IN PARTICULAR SIMULATIONS. IT IS THE USER'S ==  //
//      RESPONSIBILITY TO ENSURE ALL RELEVANT WORKS ARE ===  //
//      CITED. PLEASE SEE FULL DOCUMENTATION AND ON-SCREEN=  //
//      DISCLAIMER OUTPUTS FOR A GUIDE. ===================  //
//  (ii) ALL OF THIS TEXT IS RETAINED WITHIN OR ASSOCIATED=  //
//      WITH THE SOURCE CODE AND/OR BINARY FORM OF THE ====  //
//      SOFTWARE. =========================================  //
// ========================================================  //
// ANY INTENDED COMMERCIAL USE OF THIS SOFTWARE MUST BE BY   //
// EXPRESS PERMISSION OF MICHAEL A COLMAN ONLY. IN NO EVENT  //
// ARE THE COPYRIGHT HOLDERS LIABLE FOR ANY DIRECT, =======  //
// INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL  //
// DAMAGES ASSOCIATED WITH USE OF THIS SOFTWARE ===========  //
// ========================================================  //
// THIS SOFTWARE CONTAINS IMPLEMENTATIONS OF MODELS AND ===  //
// COMPONENTS WHICH I (MICHAEL COLMAN) DID NOT DEVELOP.====  //
// ALL OF THESE COMPONENTS HAVE BEEN CODED FROM PROVIDED ==  //
// SOURCE CODE OR INFORMATION IN THE PUBLICATIONS. ========  //
// I CLAIM NO RIGHTS OR INTELLECTUAL PROPERTY OWNERSHIP ===  //
// FOR THESE MODELS AND COMPONENTS, OTHER THAN THEIR ======  //
// SPECIFIC IMPLEMENTATION IN THIS CODE PACKAGE. FURTHER TO  //
// THE ABOVE STATEMENT, ANY INDTENDED COMMERCIAL USE OF ===  //
// THOSE COMPONENTS MUST BE BY EXPRESS PERMISSION OF THE ==  //
// ORIGINAL COPYRIGHT HOLDERS. ============================  //
// WHERE IMPLEMENTED FROM PROVIDED CODE, ANY DISCLAIMERS ==  //
// PRESENT IN THE ORIGINAL CODE HAVE BEEN RETAINED IN THE =  //
// RELEVANT FILE. =========================================  //
// ========================================================  //
// Contact: m.a.colman@leeds.ac.uk ========================  //
// For updates, corrections etc, please check: ============  //
// 1. http://physicsoftheheart.com/ =======================  //
// 2. https://github.com/michaelcolman ====================  //
// ========================================================  //

#include "Structs.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

// Function list ================================================================================\\|
//	output_properties_to_screen()   || Properties_log.dat
//	output_currents()				|| Currents.dat
//	output_excitation_properties()	|| Properties.dat
//	
//	spatial data out
//	    linescan_out_X()
//	    linescan_out_Y()
//	    linescan_out_Z()
//	
//	    data_2D_XYslice_output()
//	    data_2D_XZslice_output()
//	    data_2D_YZslice_output()
//	
//	    vtk_3D_output()
//	    data_3D_output()
//	    array_1D_output()
//	    array_1D_binary_read()
//	
//	    Output_activation()
//	
//	output_settings()
//	output_settings_tissue()
//	output_settings_3D_cell()
//	output_settings_0D_cell()
//	output_disclaimer_citations()
// End Function list ============================================================================//|

// Common - screen and file data outputs ========================================================\\|
// Final properties to file and screen
void output_properties_to_screen(const char * log_reference, Model_variables var, Simulation_parameters Sim)
{
	// Screen Outputs
	printf("Final two beat properties ****\n");
	printf("\tFINAL beat\t\t:  APD_-70mV = %.2f ms | dv/dt_max = %.2f mV/ms\n", var.APD_t, var.dvdt_max);
	printf("\tPENULTIMATE beat\t:  APD_-70mV = %.2f ms | dv/dt_max = %.2f mV/ms\n", var.APD_t_prev, var.dvdt_max_prev);
	printf("\tFINAL beat\t\t:  APD_30    = %.2f ms  | APD_50    = %.2f ms | APD_70    = %.2f ms | APD_90 = %.2f ms\n", var.APD_p[2], var.APD_p[4], var.APD_p[6], var.APD_p[8]);
	printf("\tPENULTIMATE beat\t:  APD_30    = %.2f ms  | APD_50    = %.2f ms | APD_70    = %.2f ms | APD_90 = %.2f ms\n", var.APD_p_prev[2], var.APD_p_prev[4], var.APD_p_prev[6], var.APD_p_prev[8]);
	printf("\tFINAL beat\t\t:  Vmin      = %.2f mV | Vmax      = %.2f mV  | Amplitude = %.2f mV\n", var.Vmin_prev, var.Vmax, var.Vamp);   // Vmin prev as want Vmin just before final stimulus applied, not at end of simulation
	printf("\tPENULTIMATE beat\t:  Vmin      = %.2f mV | Vmax      = %.2f mV  | Amplitude = %.2f mV\n", var.Vmin_prev_prev, var.Vmax_prev, var.Vamp_prev);    // Vmin prev as want Vmin just before final stimulus applied, not at end of simulation
	printf("\tFINAL beat\t\t:  CaT_min   = %.2f uM   | CaT_max   = %.2f uM   | CaSR_min  = %.2f mM   | CaSR_max = %.2f mM\n", 1e3*var.CaT_min, 1e3*var.CaT_max, var.CaSR_min, var.CaSR_max);
	printf("\tPENULTIMATE beat\t:  CaT_min   = %.2f uM   | CaT_max   = %.2f uM   | CaSR_min  = %.2f mM   | CaSR_max = %.2f mM\n\n", 1e3*var.CaT_min_prev, 1e3*var.CaT_max_prev, var.CaSR_min_prev, var.CaSR_max_prev);

	// Output to file
	FILE *out;
	out = fopen(log_reference, "a");    // Note: Appended, not overwritten
	fprintf(out, "%d %d %f %f %f %f %f %f %f %f %f %f ", Sim.BCL, Sim.S2_CL, var.APD_t, var.APD_t_prev, var.APD_p[2], var.APD_p_prev[2], var.APD_p[4], var.APD_p_prev[4], var.APD_p[6], var.APD_p_prev[6], var.APD_p[8], var.APD_p_prev[8]);
	fprintf(out, "%f %f %f %f %f %f %f %f ", var.dvdt_max, var.dvdt_max_prev, var.Vmin_prev, var.Vmin_prev_prev, var.Vmax, var.Vmax_prev, var.Vamp, var.Vamp_prev);
	fprintf(out, "%f %f %f %f %f %f %f %f\n", 1e3*var.CaT_min, 1e3*var.CaT_min_prev, 1e3*var.CaT_max, 1e3*var.CaT_max_prev, var.CaSR_min, var.CaSR_min_prev, var.CaSR_max, var.CaSR_max_prev);
	fclose(out);

}

// Output currents and gates to file
void output_currents(std::ostream& out, double sim_time, Model_variables var, State_variables s, double Vm)
{
	//1-3
	out<<sim_time<<" "<<Vm<<" "<<var.Istim  \

		// 4-7
		<<" "<<var.INa<<" "<<s.INa_va<<" "<<s.INa_vi_1<<" "<<s.INa_vi_2 \

		// 8-11
		<<" "<<var.Ito<<" "<<s.Ito_va<<" "<<s.Ito_vi<<" "<<s.Ito_vi_s   \

		// 12-15
		<<" "<<var.ICaL<<" "<<s.ICaL_va<<" "<<s.ICaL_vi<<" "<<s.ICaL_ci   \

		// 16-18
		<<" "<<var.IKur<<" "<<s.IKur_va<<" "<<s.IKur_vi \

		// 19-21
		<<" "<<var.IKr<<" "<<s.IKr_va<<" "<<var.IKr_vi_ti   \

		// 22-23
		<<" "<<var.IKs<<" "<<s.IKs_va   \

		// 24-25
		<<" "<<var.IK1<<" "<<var.IK1_va_ti  \

		// 26-30 
		<<" "<<var.INCX<<" "<<var.ICaP<<" "<<var.INab<<" "<<var.ICab<<" "<<var.IKb  \

		// 31-33
		<<" "<<var.INaK<<" "<<var.IClCa<<" "<<var.IClb     \

		// 34-39
		<<" "<<s.Cai<<" "<<s.Cai_sl<<" "<<s.Cai_j<<" "<<s.CajSR<<" "<<s.CanSR<<" "<<s.Cao		\

		// 40-42		
		<<" "<<s.RyRo<<" "<<s.RyRr<<" "<<s.RyRi   \

		// 43-48
		<<" "<<s.Nai<<" "<<s.Nai_sl<<" "<<s.Nai_j<<" "<<s.Ki<<" "<<s.Nao<<" "<<s.Ko     \

        //<<" "<<var.J_SERCA                                       \

		<<std::endl;
}

// Excitation properties to file
void output_excitation_properties(std::ostream& out, double sim_time, Model_variables var, double Vm)
{
	//1-3
	out<<sim_time<<" "<<Vm<<" "<<var.ex_switch      \

		// 4-5
		<<" "<<var.dvdt<<" "<<var.dvdt_max              \

		// 6-8
		<<" "<<var.Vmin<<" "<<var.Vmax<<" "<<var.Vamp   \

		// 9-10
		<<" "<<var.APD_t_switch<<" "<<var.APD_t         \

		// 11-14 || 2 = APD_30, 4 = APD_50, 6 = APD_70, 8 = APD_90
		<<" "<<var.APD_p[2]<<" "<<var.APD_p[4]<<" "<<var.APD_p[6]<<" "<<var.APD_p[8]         \

		// 15-18
		<<" "<<1e3*var.CaT_min<<" "<<1e3*var.CaT_max<<" "<<var.CaSR_min<<" "<<var.CaSR_max         \

        // 19
        //<<"  "<<var.J_SERCA_integral<<" "<<var.J_rel_integral            \

		<<std::endl;
}
// End Common - screen file outputs =============================================================//|

// Spatial outputs  =============================================================================\\|
// 1D linescan  X
void linescan_out_X(std::ostream& out, SC_variables sc, double * variable, int y, int z)
{
	for (int x=0;x<sc.NX;x++)
	{
		int idx = x + (sc.NX * y) + (sc.NX * sc.NY * z);
		out<<variable[idx]<<"  ";
	}
	out<<std::endl;
}

// 1D linescan  Y
void linescan_out_Y(std::ostream& out, SC_variables sc, double * variable, int x, int z)
{
	for (int y=0;y<sc.NY;y++)
	{
		int idx = x + (sc.NX * y) + (sc.NX * sc.NY * z);
		out<<variable[idx]<<"  ";
	}
	out<<std::endl;
}

// 1D linescan  Z
void linescan_out_Z(std::ostream& out, SC_variables sc, double * variable, int x, int y)
{
	for (int z=0;z<sc.NZ;z++)
	{
		int idx = x + (sc.NX * y) + (sc.NX * sc.NY * z);
		out<<variable[idx]<<"  ";
	}
	out<<std::endl;
}

// 2D slices
void data_2D_XYslice_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count, int Z)
{
	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_2D_XYslice_z_%d_time_%04d.dat", dir, dir2, string, Z, count);
	out = fopen(str, "wt");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					if (z == Z) fprintf(out, "%f ", variable[cell_count]);
					cell_count++;
				}
				else if (z == Z) fprintf(out, "-100 ");
			}
			fprintf(out, "\n");
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

void data_2D_XZslice_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count, int Y)
{
	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_2D_XZslice_y_%d_time_%04d.dat", dir, dir2, string, Y, count);
	out = fopen(str, "wt");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					if (y == Y) fprintf(out, "%f ", variable[cell_count]);
					cell_count++;
				}
				else if (y == Y) fprintf(out, "-100 ");
			}
			fprintf(out, "\n");
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

void data_2D_YZslice_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count, int X)
{
	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_2D_YZslice_x_%d_time_%04d.dat", dir, dir2, string, X, count);
	out = fopen(str, "wt");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					if (x == X) fprintf(out, "%f ", variable[cell_count]);
					cell_count++;
				}
				else if (x == X) fprintf(out, "-100 ");
			}
			fprintf(out, "\n");
		}
		fprintf(out, "\n");
	}
	fclose(out);
}

// VTK
void vtk_3D_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count)
{

	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_%04d.vtk", dir, dir2, string, count);
	out = fopen(str, "wt");

	fprintf(out, "# vtk DataFile Version 3.0\n");
	fprintf(out, "vtk output\n");
	fprintf(out, "ASCII\n");
	fprintf(out, "DATASET STRUCTURED_POINTS\n");
	fprintf(out, "DIMENSIONS %d %d %d\n", sc.NX, sc.NY, sc.NZ);
	fprintf(out, "SPACING 1 1 1\n");
	fprintf(out, "ORIGIN 0 0 0\n");
	fprintf(out, "POINT_DATA %d\n", sc.NX*sc.NY*sc.NZ);
	//fprintf(out, "SCALARS ImageFile float 1\n");
	fprintf(out, "SCALARS %s float 1\n", string);
	fprintf(out, "LOOKUP_TABLE default\n");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					fprintf(out, "%f ", variable[cell_count]);
					cell_count++;
				}
				else fprintf(out, "-100 ");
			}
			fprintf(out, "\n");
		}
	}
	fclose(out);
}

// 3D data (same as VTK without header)
void data_3D_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count)
{

	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_%04d.dat", dir, dir2, string, count);
	out = fopen(str, "wt");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					fprintf(out, "%f ", variable[cell_count]);
					cell_count++;
				}
				else fprintf(out, "-100 ");
			}
			fprintf(out, "\n");
		}
	}
	fclose(out);
}

// 1D array  || binary
void array_1D_output(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count)
{

	FILE * out;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/%s_output_%04d.bin", dir, dir2, string, count);
	out = fopen(str, "wb");
	fwrite(variable,sizeof(double),sc.N,out);
	fclose(out);
}

// binary data read, for converting binary to .dat or .vtk
void array_1D_binary_read(const char *string,  const char * dir, const char * dir2, double *variable, SC_variables sc, int count)
{
	FILE * in;
	char str[1000];
	sprintf(str, "%s/%s/%s_output_%04d.bin", dir, dir2, string, count);
	in = fopen(str, "r");
	if (in == NULL)
	{
		printf("Cannot load data file %s; are the directories correct? Does the file exist?\n", str);
		exit(1);
	}
	printf("File %s being read\n", str);
	fread(variable,sizeof(double),sc.N,in);
	fclose(in);
}

// Activation time
void Output_activation(const char * dir, const char * dir2, Model_variables *v, SC_variables sc)
{
	FILE *out, *out2;
	//char *str = (char*)malloc(50);
	char str[1000];

	int cell_count = 0;
	int idx;

	sprintf(str, "%s/%s/Activation_output.vtk", dir, dir2);
	out = fopen(str, "wt");

	sprintf(str, "%s/%s/Activation_output.dat", dir, dir2);
	out2 = fopen(str, "wt");

	fprintf(out, "# vtk DataFile Version 3.0\n");
	fprintf(out, "vtk output\n");
	fprintf(out, "ASCII\n");
	fprintf(out, "DATASET STRUCTURED_POINTS\n");
	fprintf(out, "DIMENSIONS %d %d %d\n", sc.NX, sc.NY, sc.NZ);
	fprintf(out, "SPACING 1 1 1\n");
	fprintf(out, "ORIGIN 0 0 0\n");
	fprintf(out, "POINT_DATA %d\n", sc.NX*sc.NY*sc.NZ);
	fprintf(out, "SCALARS Vm_activation float 1\n");
	fprintf(out, "LOOKUP_TABLE default\n");

	for (int z = 0; z < sc.NZ; z++) {
		for (int y = 0; y < sc.NY; y++) {
			for (int x = 0; x < sc.NX; x++){
				idx = x + (sc.NX*y) + (sc.NX*sc.NY*z);
				if (sc.geo[idx] > 0)
				{
					fprintf(out, "%f ", v[cell_count].t_ex);
					fprintf(out2, "%f ", v[cell_count].t_ex);
					cell_count++;
				}
				else 
				{
					fprintf(out, "-100 ");
					fprintf(out2, "-100 ");
				}
			}
			fprintf(out, "\n");
			fprintf(out2, "\n");
		}
	}
	fclose(out);
	fclose(out2);
}
// End Spatial outputs  =========================================================================//|

// Settings and initialisation ===========================================================================\\|
// Output settings to screen ====================================================================\\|
void output_settings(Simulation_parameters sim, char const * directory, bool DC_current_mod_arg, Cell_parameters p, int argc, char *argin[])
{
	int counter = 0;

	char * filename       = (char*)malloc(500);
	sprintf(filename, "%s/Settings.dat", directory);

	FILE * so;
	so = fopen(filename, "wt");

	// Screen
	printf("\n*************************************************************************************************************\n");
	printf("OUTPUTS REFERENCE \"%s\" RESULTS REFERENCE \"%s\"\n", sim.reference, sim.results_reference);
	printf("MODEL SETTINGS\n\n");
	printf("Simulation settings:\n");
	printf("\tVoltage clamp is %s || Write state is \"%s\" with reference \"%s\" || Read state is \"%s\" with reference \"%s\"\n", sim.Vclamp, sim.Write_state, sim.state_reference_write, sim.Read_state, sim.state_reference_read);
	printf("\tBCL = %d ms || NBeats = %d || Total_time = %d ms || Paced_time = %d ms || dt = %f ms\n", sim.BCL, sim.NBeats, sim.Total_time, sim.Paced_time, sim.dt);
	if (sim.S2_CL > 0) printf("\tS2  = %d ms || NS2   = %d || S2_time = %d\n", sim.S2_CL, sim.NS2, sim.S2_time);
	printf("\nModel settings:\n");
	printf("\tModel = %s || Celltype = %s || Remodelling = %s*%.2f (max) || Agent = %s*%.2f(max) || Mutation = %s\n\tISO = %f uM/0-sat || ACh = %f uM/0-sat || spatial gradient = %s value %.2f", p.Model, p.Celltype, p.Remodelling, p.Remodelling_prop, p.Agent, p.Agent_prop, p.Mutation, p.ISO, p.ACh, p.spatial_gradient, p.spatial_gradient_prop);
	if (p.ISO > 0) printf(" || ISO_model = %s\n", p.ISO_model);
	else printf("\n");
	if (p.ACh > 0) printf(" || ACh_model = %s\n", p.ACh_model);
	else printf("\n");
	if (p.hAM == true) printf("\thAM single cell model is being used; cell environment is %s ", p.environment);
	if (strcmp(p.environment, "isolated") == 0) printf ("|| Ihyp = %0.2f pA/pF\n", p.AIhyp);
	else printf("\n");
	if (DC_current_mod_arg == true)
	{
		printf("Direct control of modifier parameters has also been passed. See Log.dat for arguments and Outputs_X/Parameters_Y/Modifier_parameters.dat for full modifier values\n");
	}
    printf("\nInitial concentrations:\n");
    printf("\tKo %.02f Ki %.02f Nao %.02f Nai %.02f Cao %.02f Cai %.02f\n", p.Ko, p.Ki, p.Nao, p.Nai, p.Cao, p.Cai);
	printf("*************************************************************************************************************\n\n");

	// File
    // First print a copy of all run-time arguments to ensure full repeatability
    if (argc > 1)
    {
        fprintf(so, "./exe ");
        for (counter = 1; counter < argc-1; counter+=2)
        {
            fprintf(so, "%s %s ", argin[counter], argin[counter+1]); 
        }
        fprintf(so, "\n\n");
    }

    fprintf(so, "OUTPUTS REFERENCE \"%s\" RESULTS REFERENCE \"%s\"\n", sim.reference, sim.results_reference);
    fprintf(so,"Simulation settings:\n");
	fprintf(so, "\tVoltage clamp is %s || Write state is \"%s\" with reference \"%s\" || Read state is \"%s\" with reference \"%s\"\n", sim.Vclamp, sim.Write_state, sim.state_reference_write, sim.Read_state, sim.state_reference_read);
	fprintf(so,"\tBCL = %d ms || NBeats = %d || Total_time = %d ms || Paced_time = %d ms || dt = %f ms\n", sim.BCL, sim.NBeats, sim.Total_time, sim.Paced_time, sim.dt);
	if (sim.S2_CL > 0) fprintf(so, "\tS2  = %d ms || NS2   = %d || S2_time = %d\n", sim.S2_CL, sim.NS2, sim.S2_time);
	fprintf(so,"Model settings:\n");
	fprintf(so, "\tModel = %s || Celltype = %s || Remodelling = %s*%.2f (max) || Agent = %s*%.2f(max) || Mutation = %s\n\tISO = %f uM/0-sat || ACh = %f uM/0-sat || spatial gradient = %s value %.2f", p.Model, p.Celltype, p.Remodelling, p.Remodelling_prop, p.Agent, p.Agent_prop, p.Mutation, p.ISO, p.ACh, p.spatial_gradient, p.spatial_gradient_prop);
	if (p.ISO > 0) fprintf(so, " || ISO_model = %s\n", p.ISO_model);
	else fprintf(so, "\n");
	if (p.ACh > 0) fprintf(so, " || ACh_model = %s\n", p.ACh_model);
	else fprintf(so, "\n");
	if (p.hAM == true) fprintf(so, "\thAM single cell model is being used; cell environment is %s ", p.environment);
	if (strcmp(p.environment, "isolated") == 0) fprintf (so, "|| Ihyp = %0.2f pA/pF\n", p.AIhyp);
	else fprintf(so, "\n");
    fprintf(so, "\nInitial concentrations:\n");
    fprintf(so, "\tKo %.02f Ki %.02f Nao %.02f Nai %.02f Cao %.02f Cai %.02f\n", p.Ko, p.Ki, p.Nao, p.Nai, p.Cao, p.Cai);
	if (DC_current_mod_arg == true)
	{
		fprintf(so, "Direct control of modifier parameters has also been passed. See Log.dat for arguments and below for final modifier values (args + modulation)\n");
	}
	fprintf(so,"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
	fprintf(so,"Modifiers: (these correspond to the combination of directly passed modifications with celltype and modulation settings. I.e. the final value of these factors)\n");
	fprintf(so,"  Current/Flux scaling:\t\t");
	fprintf(so,"INa_scale  = %.02f || INaL_scale  = %.02f || Ito_scale = %.02f || ICaL_scale = %.02f || IKur_scale  = %.02f\n", p.GNa, p.GNaL, p.Gto, p.GCaL, p.GKur);
	fprintf(so,"\t\t\t\tIKr_scale  = %.02f || IKs_scale   = %.02f || IK1_scale = %.02f || INCX_scale = %.02f || ICaP_scale  = %.02f\n", p.GKr, p.GKs, p.GK1, p.GNCX, p.GCaP);
	fprintf(so,"\t\t\t\tINab_scale = %.02f || ICab_scale  = %.02f || IKb_scale = %.02f || INaK_scale = %.02f || IClCa_scale = %.02f\n", p.GNab, p.GCab, p.GKb, p.GNaK, p.GClCa);
	fprintf(so,"\t\t\t\tJup_scale  = %.02f || Jleak_scale = %.02f || || Jrel_scale = %0.2f\n\n", p.Gup, p.Gleak, p.Grel);

	fprintf(so,"  Time constant scaling:\t");
	fprintf(so,"INa_va_tau_scale  = %.02f || INa_vi_1_tau_scale = %.02f || INa_vi_2_tau_scale = %.02f || INaL_va_tau_scale = %.02f || INaL_vi_tau_scale = %.02f\n", p.INa_va_tau_scale, p.INa_vi_1_tau_scale, p.INa_vi_2_tau_scale, p.INaL_va_tau_scale, p.INaL_vi_tau_scale);
	fprintf(so,"\t\t\t\tIto_va_tau_scale  = %.02f || Ito_vi_tau_scale   = %.02f || ICaL_va_tau_scale  = %.02f || ICaL_vi_tau_scale = %.02f\n", p.Ito_va_tau_scale, p.Ito_vi_tau_scale, p.ICaL_va_tau_scale, p.ICaL_vi_tau_scale);
	fprintf(so,"\t\t\t\tIKur_va_tau_scale = %.02f || IKur_vi_tau_scale  = %.02f || IKr_va_tau_scale   = %0.2f || IKs_va_tau_sacle  = %0.2f\n\n", p.IKur_va_tau_scale, p.IKur_vi_tau_scale, p.IKr_va_tau_scale, p.IKs_va_tau_scale);

	fprintf(so,"  Voltage dependence shifts:\t");
	fprintf(so,"INa_va_shift     = %.02f || INa_vi_shift      = %.02f || INaL_va_shift    = %.02f || INaL_vi_shift     = %.02f\n", p.INa_va_shift, p.INa_vi_shift, p.INaL_va_shift, p.INaL_vi_shift);
	fprintf(so,"\t\t\t\tIto_va_ss_shift  = %.02f || Ito_va_tau_shift  = %.02f || Ito_vi_ss_shift  = %.02f || Ito_vi_tau_shift  = %.02f\n", p.Ito_va_ss_shift, p.Ito_va_tau_shift, p.Ito_vi_ss_shift, p.Ito_vi_tau_shift);
	fprintf(so,"\t\t\t\tICaL_va_ss_shift = %.02f || ICaL_va_tau_shift = %.02f || ICaL_vi_ss_shift = %.02f || ICaL_vi_tau_shift = %.02f\n", p.ICaL_va_ss_shift, p.ICaL_va_tau_shift, p.ICaL_vi_ss_shift, p.ICaL_vi_tau_shift);
	fprintf(so,"\t\t\t\tIKur_va_ss_shift = %.02f || IKur_va_tau_shift = %.02f || IKur_vi_ss_shift = %.02f || IKur_vi_tau_shift = %.02f\n", p.IKur_va_ss_shift, p.IKur_va_tau_shift, p.IKur_vi_ss_shift, p.IKur_vi_tau_shift);
	fprintf(so,"\t\t\t\tIKr_va_ss_shift  = %.02f || IKr_va_tau_shift  = %.02f || IKr_vi_ss_shift  = %.02f\n\t\t\t\tIKs_va_ss_shift  = %.02f || IKs_va_tau_shift  = %.02f || IK1_va_shift     = %.02f\n\n", p.IKr_va_ss_shift, p.IKr_va_tau_shift, p.IKr_vi_ss_shift, p.IKs_va_ss_shift, p.IKs_va_tau_shift, p.IK1_va_shift);

	fprintf(so,"  Voltage dependence gradients:\t");
	fprintf(so,"Ito_va_ss_kscale  = %.02f || Ito_vi_ss_kscale  = %.02f || ICaL_va_ss_kscale = %.02f || ICaL_vi_ss_kscale = %.02f\n\t\t\t\tIKur_va_ss_kscale = %.02f || IKur_vi_ss_kscale = %.02f\n", p.Ito_va_ss_kscale, p.Ito_vi_ss_kscale, p.ICaL_va_ss_kscale, p.ICaL_vi_ss_kscale, p.IKur_va_ss_kscale, p.IKur_vi_ss_kscale);
	fprintf(so,"\t\t\t\tIKr_va_ss_kscale  = %.02f || IKr_vi_ss_kscale  = %.02f || IKs_va_ss_kscale = %.02f\n", p.IKr_va_ss_kscale, p.IKr_vi_ss_kscale, p.IKs_va_ss_kscale);
	fprintf(so,"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");

	fclose(so);
}

void output_settings_tissue(Simulation_parameters sim, Tissue_parameters t, char const * directory)
{
	char * filename       = (char*)malloc(500);
	sprintf(filename, "%s/Settings.dat", directory);

	FILE * so;
	so = fopen(filename, "a");

	// Screen
	printf("Tissue settings:\n");
	printf("\tTissue order = %s || Tissue_model = %s || Tissue type = %s\n\tOrientation type = %s || D_uniformity = %s || Dscale = %0.2f || D_AR_scale = %0.2f\n", t.Tissue_order, t.Tissue_model, t.Tissue_type, t.Orientation_type, t.D_uniformity, t.Dscale, t.D_AR_scale);
	if (strcmp(t.Tissue_order, "geo") != 0 || ( strcmp(t.Tissue_order, "geo") == 0 && ( strcmp(t.S1_loc_type, "coords") == 0 || strcmp(t.S2_loc_type, "coords") == 0)  )) 
	{
		printf("\tStimulus location type = %s, shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.S1_loc_type, t.S1_shape, t.S1_x_loc, t.S1_x_size, t.S1_y_loc, t.S1_y_size, t.S1_z_loc, t.S1_z_size);
		if (sim.S2_CL > 0) printf("\tS2 Stimulus location type = %s, shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.S2_loc_type, t.S2_shape, t.S2_x_loc, t.S2_x_size, t.S2_y_loc, t.S2_y_size, t.S2_z_loc, t.S2_z_size);
	}
	else printf(" || Stimulus location type from file\n");
	printf("\tMulti_stim option is %s\n", t.Multi_stim);
	printf("\tRemodelling map is %s\t ISO map is %s\t ACh map is %s\t SRF map is %s\t Dscale mod map is %s D_AR_scale_map is %s Direct_modulation map is %s\n", t.remod_map_on, t.ISO_map_on, t.ACh_map_on, t.SRF_map_on, t.Dscale_map_on, t.D_AR_scale_map_on, t.Direct_modulation_map_on);
	if (strcmp(t.remod_map_on, "On") == 0 || strcmp(t.ISO_map_on, "On") == 0 || strcmp(t.ACh_map_on, "On") == 0 || strcmp(t.SRF_map_on, "On") == 0 || strcmp(t.Dscale_map_on, "On") == 0 || strcmp(t.D_AR_scale_map_on, "On") == 0 || strcmp(t.Direct_modulation_map_on, "On") == 0)
	{
		printf("\t\tAll maps will be set from %s\n", t.map_in_type);
		if (strcmp(t.map_in_type, "coords") == 0) printf("\t\tmap shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.ideal_map_shape, t.ideal_map_x_loc, t.ideal_map_x_size, t.ideal_map_y_loc, t.ideal_map_y_size, t.ideal_map_z_loc, t.ideal_map_z_size);
	}
	printf("\tSpatial gradient map is %s\n", t.spatial_gradient_map_on);
	printf("\tMultiple models is %s ", t.Multiple_models);
	if (strcmp(t.Multiple_models, "On") == 0) printf(" and second model used is %s\n", t.Tissue_model_2);
	else printf("\n");
	printf("\tDiffusion properties: (D1 = %.2f Diso = %.2f)*Dscale(=%.2f); D2 = D1/(%.2f*D_AR_scale(=%.2f)); dx = %.2f dy = %.2f dz = %.2f\n\t\tand global fibres (if ideal): X = %.2f Y = %.2f Z = %.2f\n", t.D1, t.Diso, t.Dscale, t.D_AR, t.D_AR_scale, t.dx, t.dy, t.dz, t.OX, t.OY, t.OZ);
	if (strcmp(t.Global_orientation_direction, "Off") != 0) printf("\t\tGlobal orientation was set by direction %s\n", t.Global_orientation_direction);
    printf("\tTime range over which spatial data will be output (if intervals != 0) = %d to %d\n", sim.Spatial_output_start_time, sim.Spatial_output_end_time);
	printf("\tSpatial output interval (vtk) = %d ms Spatial output interval (data) = %d ms\n", sim.Spatial_output_interval_vtk, sim.Spatial_output_interval_data);
	printf("*************************************************************************************************************\n\n");

	// File
	fprintf(so, "Tissue settings:\n");
	fprintf(so, "\tTissue order = %s || Tissue_model = %s || Tissue type = %s\n\tOrientation type = %s || D_uniformity = %s || Dscale = %0.2f || D_AR_scale = %0.2f\n", t.Tissue_order, t.Tissue_model, t.Tissue_type, t.Orientation_type, t.D_uniformity, t.Dscale, t.D_AR_scale);
	if (strcmp(t.Tissue_order, "geo") != 0) 
	{
		fprintf(so, "\tStimulus location type = %s, shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.S1_loc_type, t.S1_shape, t.S1_x_loc, t.S1_x_size, t.S1_y_loc, t.S1_y_size, t.S1_z_loc, t.S1_z_size);
		if (sim.S2_CL > 0) fprintf(so, "\tS2 Stimulus location type = %s, shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.S2_loc_type, t.S2_shape, t.S2_x_loc, t.S2_x_size, t.S2_y_loc, t.S2_y_size, t.S2_z_loc, t.S2_z_size);
	}
	else fprintf(so, " || Stimulus location type from file\n");
	fprintf(so, "\tMulti_stim option is %s\n", t.Multi_stim);
	fprintf(so, "\tRemodelling map is %s\t ISO map is %s\t ACh map is %s\t SRF map is %s\t Dscale mod map is %s D_AR_scale_map is %s Direct_modulation map is %s\n", t.remod_map_on, t.ISO_map_on, t.ACh_map_on, t.SRF_map_on, t.Dscale_map_on, t.D_AR_scale_map_on, t.Direct_modulation_map_on);
	if (strcmp(t.remod_map_on, "On") == 0 || strcmp(t.ISO_map_on, "On") == 0 || strcmp(t.ACh_map_on, "On") == 0 || strcmp(t.SRF_map_on, "On") == 0 || strcmp(t.Dscale_map_on, "On") == 0 || strcmp(t.D_AR_scale_map_on, "On") == 0 || strcmp(t.Direct_modulation_map_on, "On") == 0)
	{
		fprintf(so, "\t\tAll maps will be set from %s\n", t.map_in_type);
		if (strcmp(t.map_in_type, "coords") == 0) fprintf(so, "\t\tmap shape = %s and specifics: loc_x = %d size_x = %d loc_y = %d size_y = %d loc_z = %d size_z = %d\n", t.ideal_map_shape, t.ideal_map_x_loc, t.ideal_map_x_size, t.ideal_map_y_loc, t.ideal_map_y_size, t.ideal_map_z_loc, t.ideal_map_z_size);
	}
	fprintf(so, "\tSpatial gradient map is %s\n", t.spatial_gradient_map_on);
	fprintf(so, "\tMultiple models is %s ", t.Multiple_models);
	if (strcmp(t.Multiple_models, "On") == 0) fprintf(so, " and second model used is %s\n", t.Tissue_model_2);
	else fprintf(so, "\n");
	fprintf(so, "\tDiffusion properties: (D1 = %.2f Diso = %.2f)*Dscale(=%.2f); D2 = D1/(%.2f*D_AR_scale(=%.2f)); dx = %.2f dy = %.2f dz = %.2f\n\t\tand global fibres (if ideal): X = %.2f Y = %.2f Z = %.2f\n", t.D1, t.Diso, t.Dscale, t.D_AR, t.D_AR_scale, t.dx, t.dy, t.dz, t.OX, t.OY, t.OZ);
	if (strcmp(t.Global_orientation_direction, "Off") != 0) fprintf(so, "\t\tGlobal orientation was set by direction %s\n", t.Global_orientation_direction);
    fprintf(so, "\tTime range over which spatial data will be output (if intervals != 0) = %d to %d\n", sim.Spatial_output_start_time, sim.Spatial_output_end_time);
	fprintf(so, "\tSpatial output interval (vtk) = %d ms Spatial output interval (data) = %d ms\n", sim.Spatial_output_interval_vtk, sim.Spatial_output_interval_data);

	fclose(so);
}

// Output disclaimer for all relevant citations under model conditions ==========================\\|
void output_disclaimer_citations(Cell_parameters p, Simulation_parameters sim)
{
	// Whole framework
	printf("DISCLAIMER: BY USING THIS SOFTWARE YOU AGREE TO CITE ALL RELEVANT WORKS.\nPLEASE READ DISCLAIMER AT TOP OF MAIN CODE AND IN DOCUMENTATION FOR FULL DESCRIPTION OF LISCENCES ETC\n");
	printf("\tAny use of this software must cite in the first instance: \n\tColman MA. “Arrhythmia Mechanisms and Spontaneous Calcium Release: Bi-directional coupling between re-entry and focal excitation” PLOS Comp Biol 2019.\n\n");

	// Baseline cell model ==============================\\|
	printf("Baseline cell model:\n");
	if (strcmp(p.Model, "hAM_CRN") == 0)        printf("\tModel \"%s\" must cite: Courtemanche et al. 1998 Am. J. Physiol.-Heart Circ. Physiol. 275, H301–H321.\n", p.Model);
	if (strcmp(p.Model, "hAM_NG") == 0)         printf("\tModel \"%s\" must cite: Nygren et al. 1998 Circ. Res. 82, 63–81\n", p.Model);
	if (strcmp(p.Model, "hAM_MT") == 0)         printf("\tModel \"%s\" must cite: Maleckar et al. 2009 Am. J. Physiol. Heart Circ. Physiol. 297, H1398-1410.\n", p.Model);
	if (strcmp(p.Model, "hAM_GB") == 0)         printf("\tModel \"%s\" must cite: Grandi et al. 2011 Circ. Res. 109, 1055–1066.\n\t\tand: Chang et al 2014 PLOS Computational Biology 10 (12): e1004011\n", p.Model);
	if (strcmp(p.Model, "hAM_WL_CRN") == 0)     printf("\tModel \"%s\" must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\tand: Courtemanche et al. 1998 Am. J. Physiol.-Heart Circ. Physiol. 275, H301–H321.\n", p.Model);
	if (strcmp(p.Model, "hAM_CRN_mWL") == 0)    printf("\tModel \"%s\" must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\tand: Courtemanche et al. 1998 Am. J. Physiol.-Heart Circ. Physiol. 275, H301–H321.\n", p.Model);
	if (strcmp(p.Model, "hAM_WL_GB") == 0)      printf("\tModel \"%s\" must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\tand: Grandi et al. 2011 Circ. Res. 109, 1055–1066.\n\t\tand: Chang et al 2014 PLOS Computational Biology 10 (12): e1004011\n", p.Model);
	if (strcmp(p.Model, "hAM_GB_mWL") == 0)     printf("\tModel \"%s\" must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\tand: Grandi et al. 2011 Circ. Res. 109, 1055–1066.\n\t\tand: Chang et al 2014 PLOS Computational Biology 10 (12): e1004011\n", p.Model);
	if (strcmp(p.Model, "hAM_NG_mWL") == 0)     printf("\tModel \"%s\" must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\tand: Nygren et al. 1998 Circ. Res. 82, 63–81\n", p.Model);

	if (strcmp(p.Model, "hVM_ORD_s") == 0)      printf("\tModel \"%s\" must cite: O’Hara et al. 2011 PLOS Comp. Biol. 7, e1002061\n", p.Model);
	if (strcmp(p.Model, "hAM_CAZ_s") == 0)      printf("\tModel \"%s\" must cite: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Model);

	if (strcmp(p.Model, "dAM_VA") == 0)         printf("\tModel \"%s\" must cite: Varela et al. 2016 PLOS Comp. Biol. 12, e1005245\n\t\tand Ramirez et al. 2000 Am J Physiol Heart Circ Physiol 279(4):H1767-85\n", p.Model);
	// End Baseline cell model ==========================//|

	// Regional cell models and modulation ==============\\|
	printf("\nCelltype and modulation\n");

	// human atrial regional celltypes
	if (strcmp(p.Model, "hAM_CRN") == 0 && strcmp(p.Celltype, "RA") != 0)       printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_NG") == 0 && strcmp(p.Celltype, "RA") != 0)        printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_MT") == 0 && strcmp(p.Celltype, "RA") != 0)        printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_GB") == 0 && strcmp(p.Celltype, "RA") != 0)        printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_WL_CRN") == 0 && strcmp(p.Celltype, "RA") != 0)    printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_WL_GB") == 0 && strcmp(p.Celltype, "RA") != 0)     printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_CRN_mWL") == 0 && strcmp(p.Celltype, "RA") != 0)   printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_GB_mWL") == 0 && strcmp(p.Celltype, "RA") != 0)    printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype);  
	if (strcmp(p.Model, "hAM_CNG_mWL") == 0 && strcmp(p.Celltype, "RA") != 0)   printf("\tCelltpye \"%s\" regional heterogeneity from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Celltype); 

	// isolated human atrial cell conditions:
	if (strcmp(p.environment, "isolated") == 0) printf("\t\"%s\" environment must cite: Colman et al. 2018 Front. Physiol. 9 1211\n\t\t", p.environment);	

	// ISO 
	if (p.ISO > 0.0)
	{
		if (strcmp(p.ISO_model, "Col") == 0)        printf("\tISO model \"%s\" for human atrial cells implementation from: Colman 2014 pg:115–55. Springer Theses. https://doi.org/10.1007/978-3-319-01643-6_5.\n", p.ISO_model);
		if (strcmp(p.ISO_model, "GB") == 0)    		printf("\tISO model \"%s\" for human atrial cells implementation from: Grandi et al. 2011 Circ. Res. 109, 1055–1066.\n", p.ISO_model);
		if (strcmp(p.ISO_model, "Toy_methods_demonstration") == 0) printf("\tISO model \"%s\" for demonstration of methods used in Colman 2019 baseline publication. NOT a biophysically detailed ISO model!!!!!!!\n", p.ISO_model);
	}

	// Human atrial remodelling cAF
	if (p.hAM == true && strcmp(p.Remodelling, "AF_GB") == 0)      printf("\tcAF remodelling model \"%s\" for human atrial cells implementation from: Grandi et al. 2011 Circ. Res. 109, 1055–1066.\n", p.Remodelling);
	if (p.hAM == true && strcmp(p.Remodelling, "AF_Col_1") == 0)   printf("\tcAF remodelling model \"%s\" for human atrial cells implementation from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Remodelling);
	if (p.hAM == true && strcmp(p.Remodelling, "AF_Col_2") == 0)   printf("\tcAF remodelling model \"%s\" for human atrial cells implementation from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Remodelling);
	if (p.hAM == true && strcmp(p.Remodelling, "AF_Col_3") == 0)   printf("\tcAF remodelling model \"%s\" for human atrial cells implementation from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Remodelling);
	if (p.hAM == true && strcmp(p.Remodelling, "AF_Col_4") == 0)   printf("\tcAF remodelling model \"%s\" for human atrial cells implementation from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n", p.Remodelling);

    // Canine atrial AF remodelling
    if (strcmp(p.Model, "dAM_VA") == 0 && strcmp(p.Remodelling, "AF_moderate") == 0)  printf("\t\"AF_moderate\" remodelling for canine atrial cells from: Varela et al. 2016 PLOS Comp. Biol. 12, e1005245\n");
    if (strcmp(p.Model, "dAM_VA") == 0 && strcmp(p.Remodelling, "AF_severe") == 0)    printf("\t\"AF_severe\" remodelling for canine atrial cells from: Varela et al. 2016 PLOS Comp. Biol. 12, e1005245\n");

	// Remodelling global
	if (strcmp(p.Remodelling, "RSERCA_NCX") == 0)	printf("\tRemodelling model \"%s\" for demonstration of methods used in Colman 2019 baseline publication. NOT a biophysically detailed model!!!!!!!\n", p.ISO_model);
	if (strcmp(p.Remodelling, "RCRU") == 0)			printf("\tRemodelling model \"%s\" for demonstration of methods used in Colman 2019 baseline publication. NOT a biophysically detailed model!!!!!!!\n", p.ISO_model);

	// Pharmacological agents
	if (strcmp(p.Agent, "MC-II-157c") == 0)     printf("\tPharmagological agent \"%s\" implementation is from: Colman et al. 2017 Front. Physiol 8\n\t\tAnd original data for the compound: Guo et al. 2014 PLOS One 9, e105553.\n", p.Agent);

	// Mutations
	if (strcmp(p.Mutation, "D322H") == 0)		printf("\tMutation model \"%s\" implementation is from Colman, Ni et al. 2017 PLOS Comp Biol 13(6):e1005587\n");
	if (strcmp(p.Mutation, "Y155C") == 0)		printf("\tMutation model \"%s\" implementation is from Colman, Ni et al. 2017 PLOS Comp Biol 13(6):e1005587\n");
	// End Regional cell models and modulation ==========//|

	// Test model warnings ==============================\\|
	if (p.ACh > 0.0) if (strcmp(p.ACh_model, "test_global") == 0)   printf("***WARNING: ACh model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Agent, "test_global") == 0)                        printf("***WARNING: Agent model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Celltype, "test_global") == 0)                     printf("***WARNING: Celltype model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Mutation, "test_global") == 0)                     printf("***WARNING: Mutation model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.ISO_model, "test_global") == 0)                    printf("***WARNING: ISO model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Remodelling, "test_global") == 0)                  printf("***WARNING: Remodelling model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (p.ACh > 0.0) if (strcmp(p.ACh_model, "test") == 0)          printf("***WARNING: ACh model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Agent, "test") == 0)                               printf("***WARNING: Agent model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Celltype, "test") == 0)                            printf("***WARNING: Celltype model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Mutation, "test") == 0)                            printf("***WARNING: Mutation model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (p.ISO > 0.0) if (strcmp(p.ISO_model, "test") == 0)          printf("***WARNING: ISO model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.Remodelling, "test") == 0)                         printf("***WARNING: Remodelling model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.spatial_gradient, "apico_basal_example") == 0) 	printf("***WARNING: Spatial gradient model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	if (strcmp(p.spatial_gradient, "SAN_distance_example") == 0) 	printf("***WARNING: Spatial gradient model being used is provided for test purposes only. NOT TO BE USED IN RESEARCH***\n");
	// End Test model warnings ==========================//|
}

void output_disclaimer_citations_tissue(Cell_parameters p, Tissue_parameters t)
{
	printf("\nTissue model\n");

	if (strcmp(t.Tissue_model, "Human_vent_wedge") == 0)        printf("\tHuman ventricular wedge geometry from: Benson et al. 2007 Chaos 17(1):015105\n");
	if (strcmp(t.Tissue_model, "Canine_vent") == 0)             printf("\tCanine bi-ventricle geometry from: Benson et al. 2008 Progress in Biophysics and Molecular Biology, Cardiovascular Physiome, 96(1): 187-208\n");
	if (strcmp(t.Tissue_model, "Canine_atria_VA_control") == 0) printf("\tCanine atrial geometry from: Varela et al. 2016 PLOS Comp. Biol. 12, e1005245\n");
	if (strcmp(t.Tissue_model, "Canine_atria_VA_remod") == 0)   printf("\tCanine atrial geometry from: Varela et al. 2016 PLOS Comp. Biol. 12, e1005245\n");
	if (strcmp(t.Tissue_model, "Human_atria_Colman_Krueger") == 0) printf("\tHuman atrial geometry and segmentation from: Colman et al. 2013 J. Physiol. 591, 4249–4272\n\t\tand: Krueger MW et al. IEEE Trans Med Imaging. 2013 Jan;32(1):73–84\n\t\tincorporating the SAN reconstruction from Chandler et al. Anat Rec 2011 Jun;294(6):970-9\n");
}
// End Settings and initialisation =======================================================================//|
