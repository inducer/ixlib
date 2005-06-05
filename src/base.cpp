// ----------------------------------------------------------------------------
//  Description      : String object
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <clocale>
#include <ixlib_base.hpp>
#include <ixlib_config.hpp>
#include <ixlib_i18n.hpp>




int ixion::ixlibGetMajorVersion() {
  return IXLIB_MAJOR_VERSION;
  }




int ixion::ixlibGetMinorVersion() {
  return IXLIB_MINOR_VERSION;
  }




int ixion::ixlibGetMicroVersion() {
  return IXLIB_MICRO_VERSION;
  }




void ixion::ixlibInitI18n() {
  #ifndef WIN32
  setlocale(LC_MESSAGES,"");
  bindtextdomain(PACKAGE,LOCALEDIR);
  textdomain(PACKAGE);
  #endif
  }
