// ----------------------------------------------------------------------------
//  Description      : I/O exception.
// ----------------------------------------------------------------------------
//  (c) Copyright 1996 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include "ixlib_i18n.hpp"
#include <ixlib_exio.hpp>




using namespace ixion;




// Exception support ----------------------------------------------------------
static char *IOPlainText[] = { 
  N_("Unmatched wildcard"),
  N_("Parameter error: wildcard"),
  N_("Path syntax error"),
  N_("Path relative or invalid"),
  N_("Seek error"),
  N_("Read request across EOF"),
  N_("Write request across EOF"),
  N_("Write protection violation"),
  N_("File clipping violation"),
  N_("Internal error"),
  N_("No such file or directory"),
  N_("Access denied"),
  N_("File exists"),
  N_("Too many open files"),
  N_("Out of media space"),
  N_("File too big"),
  N_("Hardware failure"),
  N_("Path inaccessible"),
  N_("Continuity violation"),
  N_("Not supported"),
  N_("Invalid file format"),
  N_("Invalid replacement sequence"),
  N_("Invalid chunk"),
  N_("CRC error"),
  };




// io_exception ---------------------------------------------------------------
char *io_exception::getText() const {
  return _(IOPlainText[Error]);
  }




TErrorCode io_exception::getErrNoError() {
  switch (errno) {
    case ENOENT:
      return ECIO_NOTFOUND;
    case EACCES:
    case EPERM:
      return ECIO_ACCESS;

    case EEXIST:
      return ECIO_EXISTS;
    case ENFILE:
    case EMFILE:
      return ECIO_NFILES;
    case ENOSPC:
      return ECIO_SPACE;
    case EFBIG:
      return ECIO_2BIG;
    case EIO:
      return ECIO_HARDWARE;
    default:
      return ECIO_INTERNAL;
    }
  }





