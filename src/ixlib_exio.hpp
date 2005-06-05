// ----------------------------------------------------------------------------
//  Description      : I/O exception
// ----------------------------------------------------------------------------
//  (c) Copyright 1996 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_EXIO
#define IXLIB_EXIO




#include <cerrno>
#include <ixlib_exbase.hpp>




// Error codes ----------------------------------------------------------------
#define ECIO_NOMATCH    		1
#define ECIO_NOWILD			2
#define ECIO_INVALIDPATH		3
#define ECIO_INVALIDDOSPATH     	4
#define ECIO_SEEK                     	5
#define ECIO_READEND                  	6
#define ECIO_WRITEEND                 	7
#define ECIO_READONLY                 	8
#define ECIO_CLIP                     	9

#define ECIO_INTERNAL			10
#define ECIO_NOTFOUND			11
#define ECIO_ACCESS			12
#define ECIO_EXISTS			13
#define ECIO_NFILES			14
#define ECIO_SPACE			15
#define ECIO_2BIG			16
#define ECIO_HARDWARE			17

#define ECIO_INVALIDJOINPATH		18
#define ECIO_CONTINUITY                 19
#define ECIO_UNSUPPORTED                20
#define ECIO_FILEFORMAT                 21
#define ECIO_WILDREPLACE    		22

#define ECIO_INVALIDCHUNK               23

#define ECIO_CRC                        24




// io_exception ---------------------------------------------------------------
namespace ixion {
  struct io_exception : public base_exception {
    io_exception(TErrorCode error,char const *info = NULL,char *module = NULL,
      TIndex line = 0)
      : base_exception(error,info,module,line,"IO")
      { }
    io_exception(char const *info = NULL,char *module = NULL,TIndex line = 0)
      : base_exception(getErrNoError(),info,module,line,"IO")
      { }
    virtual char *getText() const;
  
    private:
    TErrorCode getErrNoError();
    };
  }




#endif
