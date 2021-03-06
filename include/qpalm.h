/**
 * @file qpalm.h
 * @author Ben Hermans
 * @brief QPALM main solver API.
 * @details This file contains the main functions that can be called by the user.
 * The user can load the default settings, setup the workspace with data and settings,
 * warm_start the primal and dual variables, run the solver, and cleanup the workspace afterwards.
 */

#ifndef QPALM_H
#define QPALM_H

#include "types.h"
#include "global_opts.h"

/********************
* Main Solver API  *
********************/

/**
 * @name Main solver API
 * @{
 */


/**
 * Set default settings from constants.h file.
 * Assumes settings are already allocated in memory.
 * @param settings Settings structure
 */
void qpalm_set_default_settings(QPALMSettings *settings);


/**
 * Initialize QPALM solver allocating memory.
 *
 * All the inputs must be already allocated in memory before calling.
 *
 * It performs:
 * - data and settings validation
 * - problem data scaling
 *
 * @param  data         Problem data
 * @param  settings     Solver settings
 * @param  c            Cholmod environment
 * @return              Solver environment
 */
QPALMWorkspace* qpalm_setup(const QPALMData *data,
                          const QPALMSettings     *settings,
                          cholmod_common    *c);


/**
 * Warm start workspace variables x, x_0, x_prev, Ax, Qx, y and sigma
 * 
 * If x_warm_start or y_warm_start is given as NULL, then the related variables
 * will be initialized to 0. This function also initializes the penalty parameters
 * sigma and the matrix Asqrtsigma.
 * 
 * @param work Workspace
 * @param x_warm_start Warm start for the primal variables
 * @param y_warm_start Warm start for the dual variables
 */
void qpalm_warm_start(QPALMWorkspace *work, 
                const c_float        *x_warm_start, 
                const c_float        *y_warm_start);

/**
 * Solve the quadratic program.
 *
 * The final solver information is stored in the \a work->info structure.
 *
 * The solution is stored in the \a work->solution structure.
 *
 * If the problem is primal infeasible, the certificate is stored
 * in \a work->delta_y.
 *
 * If the problem is dual infeasible, the certificate is stored in \a
 * work->delta_x.
 *
 * @param  work Workspace
 */
void qpalm_solve(QPALMWorkspace *work);



/**
 * Cleanup the workspace by deallocating memory.
 *
 * This function should be the called after the user is done using QPALM.
 * @param  work Workspace
 */
void qpalm_cleanup(QPALMWorkspace *work);

/**
 * @}
 */

#endif
