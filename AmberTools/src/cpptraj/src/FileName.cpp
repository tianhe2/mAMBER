#include "FileName.h"
#include "StringRoutines.h" // tildeExpansion

void FileName::clear() {
  fullPathName_.clear();
  baseName_.clear();
  extension_.clear();
  compressExt_.clear();
}

/** Main routine for setting file name. Assume nameIn is the full path
  * filename. Determine the base file name and extensions. If compress
  * status is yes, set the compression extension and prior extension
  * (if any). If compress status is unknown, see if extension is a 
  * recognized compression extension.
  */
int FileName::SetFileName(std::string const& nameIn, FileName::CompressStatus compressed) {
  // null filename allowed for WRITE (indicates STDOUT)
  if (nameIn.empty()) {
    clear();
    return 0;
  }
  // Assign filename with full path
  fullPathName_.assign( nameIn );
  // Get position of last occurence of '/' to determine base filename
  size_t found = fullPathName_.find_last_of("/");
  if (found == std::string::npos)
    baseName_ = fullPathName_;
  else
    baseName_ = fullPathName_.substr(found+1);
  // Get the filename extension
  found = baseName_.find_last_of(".");
  if (found == std::string::npos) {
    extension_.clear();
  } else {
    extension_ = baseName_.substr(found);
  }
  bool searchExtension = (compressed == YES);
  // If compression is unknown (e.g. on writes), see if the extension is one 
  // of the 2 recognized compression extensions.
  if (compressed == UNKNOWN) {
    if ( extension_ == ".gz" || extension_ == ".bz2" )
      searchExtension = true;
  }
  if ( searchExtension ) {
    // If file is compressed, the extension just found should be the compression
    // extension.
    compressExt_ = extension_;
    // Get everything before the compressed extension
    std::string compressPrefix = baseName_.substr(0,found);
    // See if there is another extension
    found = compressPrefix.find_last_of(".");
    if (found == std::string::npos) 
      // No other extension
      extension_.clear();
    else 
      extension_ = compressPrefix.substr(found);
  } else
    compressExt_.clear();
  return 0;
}

int FileName::SetFileName( std::string const& nameIn ) {
  return SetFileName( nameIn, UNKNOWN );
}

int FileName::SetFileName( std::string const& nameIn, bool isCompressed ) {
  if (isCompressed)
    return SetFileName( nameIn, YES );
  return SetFileName( nameIn, NO );
}

int FileName::SetFileNameWithExpansion( std::string const& nameIn ) {
  return SetFileName( tildeExpansion( nameIn.c_str() ), UNKNOWN );
}
