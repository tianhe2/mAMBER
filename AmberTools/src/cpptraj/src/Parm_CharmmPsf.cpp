// Parm_CharmmPsf.cpp
#include <cstdio> // sscanf
#include <cstring> // strncmp
#include "Parm_CharmmPsf.h"
#include "CpptrajStdio.h"

bool Parm_CharmmPsf::ID_ParmFormat(CpptrajFile& fileIn) {
  // Assumes already set up
  if (fileIn.OpenFile()) return false;
  std::string nextLine = fileIn.GetLine();
  if (nextLine.empty()) return false;
  bool isPSF = ( nextLine.compare(0, 3, "PSF") == 0 );
  fileIn.CloseFile();
  return isPSF;
}

// Parm_CharmmPsf::ReadParm()
/** Open the Charmm PSF file specified by filename and set up topology data.
  * Mask selection requires natom, nres, names, resnames, resnums.
  */
int Parm_CharmmPsf::ReadParm(std::string const& fname, Topology &parmOut) {
  const size_t TAGSIZE = 10; 
  char tag[TAGSIZE];
  tag[0]='\0';

  CpptrajFile infile;
  if (infile.OpenRead(fname)) return 1;
  mprintf("    Reading Charmm PSF file %s as topology file.\n",infile.Filename().base());
  // Read the first line, should contain PSF...
  const char* buffer = 0;
  if ( (buffer=infile.NextLine()) == 0 ) return 1;
  // Advance to <ntitle> !NTITLE
  int ntitle = 0;
  while (strncmp(tag,"!NTITLE",7)!=0) {
    if ( (buffer=infile.NextLine()) == 0 ) return 1;
    sscanf(buffer,"%i %10s",&ntitle, tag);
  }
  // Only read in 1st title
  std::string psftitle;
  if (ntitle > 0) {
    buffer = infile.NextLine();
    psftitle.assign( buffer );
  }
  parmOut.SetParmName( psftitle, infile.Filename().Base() );
  // Advance to <natom> !NATOM
  int natom = 0;
  while (strncmp(tag,"!NATOM",6)!=0) {
    if ( (buffer=infile.NextLine()) == 0 ) return 1;
    sscanf(buffer,"%i %10s",&natom,tag);
  }
  mprintf("\tPSF: !NATOM tag found, natom=%i\n", natom);
  // If no atoms, probably issue with PSF file
  if (natom<=0) {
    mprinterr("Error: No atoms in PSF file.\n");
    return 1;
  }
  // Read the next natom lines
  int psfresnum = 0;
  int last_res = -1;
  char psfresname[6];
  char psfname[6];
  char psftype[6];
  double psfcharge;
  double psfmass;
  for (int atom=0; atom < natom; atom++) {
    if ( (buffer=infile.NextLine()) == 0 ) {
      mprinterr("Error: ReadParmPSF(): Reading atom %i\n",atom+1);
      return 1;
    }
    // Read line
    // ATOM# SEGID RES# RES ATNAME ATTYPE CHRG MASS (REST OF COLUMNS ARE LIKELY FOR CMAP AND CHEQ)
    sscanf(buffer,"%*i %*s %i %s %s %s %lf %lf",&psfresnum, psfresname, 
           psfname, psftype, &psfcharge, &psfmass);
    parmOut.AddTopAtom( Atom( psfname, psfcharge, 0, psfmass, 0, psftype, 0, 0, psfresnum),
                     psfresname, psfresnum, last_res, 0 );
  } // END loop over atoms 
  // Advance to <nbond> !NBOND
  int nbond = 0;
  int bondatoms[8];
  while (strncmp(tag,"!NBOND",6)!=0) {
    if ( (buffer=infile.NextLine()) == 0 ) return 1;
    sscanf(buffer,"%i %10s",&nbond,tag);
  }
  int nlines = nbond / 4;
  if ( (nbond % 4) != 0) nlines++;
  for (int bondline=0; bondline < nlines; bondline++) {
    if ( (buffer=infile.NextLine()) == 0 ) {
      mprinterr("Error: ReadParmPSF(): Reading bond line %i\n",bondline+1);
      return 1;
    }
    // Each line has 4 pairs of atom numbers
    int nbondsread = sscanf(buffer,"%i %i %i %i %i %i %i %i",bondatoms,bondatoms+1,
                            bondatoms+2,bondatoms+3, bondatoms+4,bondatoms+5,
                            bondatoms+6,bondatoms+7);
    // NOTE: Charmm atom nums start from 1
    for (int bondidx=0; bondidx < nbondsread; bondidx+=2)
      parmOut.AddBond(bondatoms[bondidx]-1, bondatoms[bondidx+1]-1);
  }
  mprintf("\tPSF contains %i atoms, %i residues.\n", parmOut.Natom(), parmOut.Nres());

  infile.CloseFile();

  return 0;
}

