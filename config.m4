dnl $Id$
dnl config.m4 for opaccel

PHP_ARG_ENABLE(opaccel, whether to enable opaccel,
[  --disable-opaccel           Disable opaccel], yes)

PHP_ARG_ENABLE(opaccel-strlen, enable opaccel strlen,
[  --disable-opaccel-strlen    Disable opaccel strlen], yes)

PHP_ARG_ENABLE(opaccel-useless-call-optimization, enable optimization of useless calls,
[  --disable-opaccel-useless-call-optimization    Disable opaccel optimization of useless calls], yes)

if test "$PHP_OPACCEL" != "no"; then
  PHP_NEW_EXTENSION(opaccel, Opaccel.c, $ext_shared)
  
  if test "$PHP_OPACCEL_STRLEN" != "no"; then
  	AC_DEFINE([HAVE_OPACCEL_STRLEN], [], [Enable opaccel strlen])
  fi
fi
