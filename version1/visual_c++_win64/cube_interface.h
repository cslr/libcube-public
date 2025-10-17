/*
 * Cube C API for DLL/shared library
 *
 * These C API function calls are NOT thread-safe
 * (especially cube creation and removal cannot be used at the same time with other functions.)
 * 
 * Functions return 0 or -1 for failure, positive value for success.
 */


#ifndef __cube_interface_h
#define __cube_interface_h

#ifdef WINOS
#define DLL_FUNCTION __declspec(dllexport)
#else
#define DLL_FUNCTION
#endif

#ifdef __cplusplus
extern "C"
{
#endif

  /* returns allocated cube number (starting from zero to positive infinity) [returns negative if failure] */
  DLL_FUNCTION int cube_init_new_cube();

  /* removes cube and frees memory */
  DLL_FUNCTION int cube_free_cube(unsigned int cube);
  
  
  /* return number of new messages and stores messages in *messages */
  DLL_FUNCTION int cube_get_unread_messages(unsigned int cube,
					    char*** messages); 
  
  
  DLL_FUNCTION int cube_start_calculate_parameter_reduction(unsigned int cube,
							    float** presets,
							    unsigned int NUM_PRESETS,
							    unsigned int DIM_PRESETS,
							    unsigned int method,
							    unsigned int REDUCED_DIMENSIONS,
							    float quality);
  
  const unsigned int CUBE_METHOD_ICA = 0; // method uses linear ICA and neural network
  const unsigned int CUBE_METHOD_TSNE = 1; // method uses t-SNE and neuraln network
  

  DLL_FUNCTION int cube_is_parameter_reducer_computing(unsigned int cube);

  DLL_FUNCTION int cube_stop_parameter_reduction_calculations(unsigned int cube);

  DLL_FUNCTION int cube_has_model(unsigned int cube);


  /* return number of restored_preset dimensions and stores restored preset in *restored_preset pointer (mallocs)
   * preset values should be in the range of [-2,+2] (Normal(0,I) distribution)
   */
  DLL_FUNCTION int cube_restore(unsigned int cube,
				float* preset, unsigned int DIM_PRESET,
				float** restored_preset);

  DLL_FUNCTION int cube_get_input_dimensions(unsigned int cube);

  DLL_FUNCTION int cube_get_restored_dimensions(unsigned int cube);

  /* malloc()s memory and stores pointer to *model_params, return model parameters dimensions */
  DLL_FUNCTION int cube_export_model(unsigned int cube,
				     double** model_params);

  DLL_FUNCTION int cube_import_model(unsigned int cube,
				     double* model_params, unsigned int DIM_PARAMS);


  DLL_FUNCTION int cube_save(unsigned int cube,
			     char* filename);

  DLL_FUNCTION int cube_load(unsigned int cube,
			     char* filename);

#ifdef __cplusplus
};
#endif

#endif
