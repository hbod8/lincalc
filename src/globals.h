#pragma once

#ifdef DEFINE_GLOBALS

#define GLOBAL_VAR(type, name, init) \
  extern type name;                  \
  type name = init

#else

#define GLOBAL_VAR(type, name, init) extern type name

#endif

/* Global Variables */
