
/************************************************************************/
/*  specials qualifiers for mathematical functions                      */
/************************************************************************/
#define MATH_FUNC_QUALIFIER inline


/************************************************************************/
/*  specify the default floating type									*/
/************************************************************************/
#define MATH_FLOAT_DEFAULT float

/************************************************************************/
/*  Enable or disable the fast blending optimization					*/
/*  The blending will have some error when used with int types but will */
/*  at least two times faster											*/
/************************************************************************/
#define GRAPHIC_FAST_BLENDING



/************************************************************************/
/* Enable or disable blending branching optimizations					*/
/************************************************************************/
#define GRAPHIC_BRANCHING_BLENDING

/************************************************************************/
/* Enabled logging or not                                               */
/************************************************************************/
//#define LOG											<= Please set it inside the compilations options

/************************************************************************/
/* Select what to log (0 = ALL, 1 = INFO, 2 = WARNING, 3 = ERROR)       */
/************************************************************************/
#define LOG_SEVERITY 1


/************************************************************************/
/* If the this is a debug build						      */
/************************************************************************/
//#define DEBUG											<= Please set it inside the compilations options


/************************************************************************/
/* enable or disable memory debug                                       */
/************************************************************************/
//#define DEBUG_MEMORY										<= Please set it inside the compilations options

