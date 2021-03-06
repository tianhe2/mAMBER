#include "Trajout.h"
#include "CpptrajStdio.h"
#include "StringRoutines.h" // fileExists

// CONSTRUCTOR
Trajout::Trajout() :
  numFramesProcessed_(0),
  trajio_(0),
  trajIsOpen_(false),
  nobox_(false),
  append_(false),
  hasRange_(false),
  rangeframe_(FrameRange_.end())
{}

// DESTRUCTOR
Trajout::~Trajout() {
  if (trajio_!=0) {
    if (trajIsOpen_) EndTraj();
    trajIsOpen_ = false;
    delete trajio_;
  }
}

// Trajout::SetupTrajWrite()
int Trajout::SetupTrajWrite(std::string const& tnameIn, ArgList *argIn, Topology *tparmIn,
                                   TrajFormatType writeFormatIn)
{
  TrajectoryFile::TrajFormatType writeFormat = writeFormatIn;
  // Require a filename
  if (tnameIn.empty()) {
    mprinterr("Internal Error: SetupTrajWrite: No filename given.\n");
    return 1;
  }
  // Check and set associated parm file
  if ( SetTrajParm( tparmIn ) ) return 1;
  // Mark as not yet open
  trajIsOpen_ = false;
  // Check for append keyword
  if (argIn!=0) 
    append_ = argIn->hasKey("append");
  // Set file name 
  SetTrajFileName( tnameIn, false );
  // If a write format was not specified (UNKNOWN_TRAJ) check the argument
  // list to see if format was specified there. Defaults to AMBERTRAJ.
  if (writeFormat==UNKNOWN_TRAJ) {
    if (argIn != 0)
      writeFormat = GetFormatFromArg(*argIn);
    else
      writeFormat = AMBERTRAJ;
    // If still AMBERTRAJ this means no type specified. Check to see if
    // the filename extension is recognized.
    if (writeFormat == AMBERTRAJ) {
      writeFormat = GetTypeFromExtension( TrajFilename().Ext() );
      if (writeFormat == UNKNOWN_TRAJ) writeFormat = AMBERTRAJ;
    }
  }
  // If appending, file must exist and must match the current format.
  if (append_) {
    if (fileExists(tnameIn.c_str())) { 
      TrajectoryFile::TrajFormatType appendFormat = TrajFormat( tnameIn );
      if (appendFormat == TrajectoryFile::UNKNOWN_TRAJ)
        mprintf("Warning: Could not determine file format for 'append'. Using %s\n",
                FormatString( writeFormat ) );
      else
        writeFormat = appendFormat;
    } else {
      mprintf("Warning: 'append' specified for non-existent file.\n");
      append_ = false;
    }
  }
  // Set up for the specified format
  trajio_ = AllocTrajIO( writeFormat );
  if (trajio_ == 0) return 1;
  trajio_->SetDebug( debug_ );
  // Process additional arguments
  if (argIn != 0) {
    // Get specified title if any - will not set if null 
    trajio_->SetTitle( argIn->GetStringKey("title") );
    /*// If supported, set temperature write
    trajio_->SetTemperature( argIn->hasKey("remdtraj") );
    // If supported, set velocity write
    trajio_->SetVelocity( !argIn->hasKey("novelocity" ) );*/

    // Get a frame range for trajout
    std::string onlyframes = argIn->GetStringKey("onlyframes");
    if (!onlyframes.empty()) {
      if ( FrameRange_.SetRange(onlyframes) )
        mprintf("Warning: trajout %s: onlyframes: %s is not a valid range.\n",
                TrajFilename().full(), onlyframes.c_str());
      else
        FrameRange_.PrintRange("\tSaving frames",0);
      // User frame args start from 1. Start from 0 internally.
      FrameRange_.ShiftBy(-1);
      hasRange_ = true;
    } else {
      if (frameCount_.InitFrameCounter( *argIn )) return 1;
      hasRange_ = false;
    }

    // Check for nobox argument - will override any box info present in parm
    // when trajectory IO is set up.
    nobox_ = argIn->hasKey("nobox");

    // Process any write arguments specific to certain formats not related
    // to parm file. Options related to parm file are handled on the first
    // write in WriteFrame.
    if (trajio_->processWriteArgs(*argIn)) {
      mprinterr("Error: trajout %s: Could not process arguments.\n",TrajFilename().full());
      return 1;
    }
  }

  // No more setup here; Write is set up when first frame written.
  return 0;
}

// Trajout::SetupTrajWriteWithArgs()
int Trajout::SetupTrajWriteWithArgs(std::string const& tnameIn, const char *argstring,
                                           Topology *tparmIn, TrajFormatType fmtIn)
{
  ArgList tempArg(argstring, " ");
  return SetupTrajWrite(tnameIn,&tempArg,tparmIn,fmtIn);
}

// Trajout::EndTraj()
void Trajout::EndTraj() {
  if (trajIsOpen_) {
    trajio_->closeTraj();
    trajIsOpen_ = false;
  }
}

// Trajout::WriteFrame()
// TODO: Make const frame&
int Trajout::WriteFrame(int set, Topology *tparmIn, Frame &FrameOut) {
  // Check that input parm matches setup parm - if not, skip
  if (tparmIn->Pindex() != TrajParm()->Pindex()) return 0;

  // First frame setup - set up for the input parm, not necessarily the setup
  // parm; this allows things like atom strippping, etc. A stripped parm will
  // have the same pindex as the original parm.
  if (!trajIsOpen_) {
    if (debug_>0) rprintf("\tSetting up %s for WRITE, %i atoms, originally %i atoms.\n",
                          TrajFilename().base(),tparmIn->Natom(),TrajParm()->Natom());
    SetTrajParm( tparmIn );
    // Use parm to set up box info for the traj unless nobox was specified.
    if (nobox_) 
      trajio_->SetBox( Box() );
    else
      trajio_->SetBox( tparmIn->ParmBox() );
    // Determine how many frames will be written
    int NframesToWrite = TrajParm()->Nframes();
    if (hasRange_)
      NframesToWrite = FrameRange_.Size();
    // Set up write and open for the current parm file 
    if (trajio_->setupTrajout(TrajFilename().Full(), TrajParm(), NframesToWrite, append_)) 
      return 1;
    trajIsOpen_ = true;
    // If a framerange is defined set it to the begining of the range
    if (hasRange_)
      rangeframe_ = FrameRange_.begin();
    numFramesProcessed_ = 0;
  }
  // If there is a framerange defined, check if this frame matches. If so,
  // write this frame and increment to the next frame in the range.
  if (hasRange_) {
    // If no more frames in the framerange, skip.
    if (rangeframe_ == FrameRange_.end()) return 0;
    // If this frame is not the next in the range, skip.
    if ( *rangeframe_ != set ) return 0;
    // This frame is next in the range. Advance FrameRange iterator.
    ++rangeframe_;
  } else {
    if (frameCount_.CheckFrameCounter( set )) return 0;
  }

  // Write
  //fprintf(stdout,"DEBUG: %20s: Writing %i\n",trajName,set);
  if (trajio_->writeFrame(set, FrameOut.xAddress(), FrameOut.vAddress(),
                               FrameOut.bAddress(), FrameOut.Temperature())) return 1;
  ++numFramesProcessed_;

  return 0;
}

// Trajout::PrintInfo()
void Trajout::PrintInfo(int showExtended) {
  mprintf("  [%s] ",TrajFilename().base());
  trajio_->Info();
  mprintf(", Parm %s",TrajParm()->c_str());
  if (trajio_->HasBox()) mprintf(" (with box info)");
  if (hasRange_)
    FrameRange_.PrintRange(": Writing frames",OUTPUTFRAMESHIFT);
  else {
    mprintf(": Writing %i frames", TrajParm()->Nframes());
    frameCount_.FrameCounterBrief();
  }
  
  if (append_) mprintf(", appended");
  mprintf("\n");
}
