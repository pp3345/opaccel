dnl $Id$
dnl config.m4 for opaccel

PHP_ARG_ENABLE(opaccel, whether to enable opaccel,
[  --disable-opaccel           Disable opaccel], yes)

if test "$PHP_OPACCEL" != "no"; then
  PHP_NEW_EXTENSION(opaccel, Opaccel.c, $ext_shared,,,,yes)
 fi
