#ifndef INC_ACTION_DNAIONTRACKER_H
#define INC_ACTION_DNAIONTRACKER_H
#include "Action.h"
#include "ImagedAction.h"
class Action_DNAionTracker : public Action, ImagedAction {
  public:
    Action_DNAionTracker();

    static DispatchObject* Alloc() { return (DispatchObject*)new Action_DNAionTracker(); }
    static void Help();

    void Print() {}
  private:
    Action::RetType Init(ArgList&, TopologyList*, FrameList*, DataSetList*,
                          DataFileList*, int);
    Action::RetType Setup(Topology*, Topology**);
    Action::RetType DoAction(int, Frame*, Frame**);

    DataSet* distance_;
    enum BINTYPE { COUNT=0, SHORTEST, TOPCONE, BOTTOMCONE };
    BINTYPE bintype_; // iarg3
    double poffset_; // darg2
    bool useMass_;
    AtomMask p1_;
    AtomMask p2_;
    AtomMask base_;
    AtomMask ions_;
};
#endif
