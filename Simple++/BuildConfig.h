/**
 * @file	BuildConfig.h.
 *
 * @brief	Constants to be changed to customize the project.
 * @author	Clément Gerber
 * @date
 */

 /** @brief	specials qualifiers for mathematical functions */
#define MATH_FUNC_QUALIFIER inline

/** @brief	specify the default floating type */
#define MATH_FLOAT_DEFAULT float

/** @brief	Enable or disable the fast blending optimization
 *			The blending will have some error when used with int types but will
 *			at least two times faster
 */
#define GRAPHIC_FAST_BLENDING

 /** @brief	Windows explicit parts on WIN32 system */
//#define ENABLE_WIN32

/** @brief	Enable or disable blending branching optimizations */
#define GRAPHIC_BRANCHING_BLENDING

/** @brief	Enable logging or not */
//#define LOG											<= Please set it inside the compilations options

 /** @brief	Select what to log (0 = ALL, 1 = INFO, 2 = WARNING, 3 = ERROR) */
#define LOG_SEVERITY 1

/** @brief Display or not the calling file in logs. */
//#define LOG_DISPLAY_FILEPATH

/** @brief	if the this is a debug build */
//#define DEBUG											<= Please set it inside the compilations options

/** @brief	enable or disable memory debug */
//#define DEBUG_MEMORY										<= Please set it inside the compilations options

/** @brief	Enable or disable the UI part */
// #define _UI

/** @brief Additional information for lib export */
#define EXPORT __declspec(dllexport)

