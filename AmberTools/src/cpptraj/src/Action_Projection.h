#ifndef INC_ACTION_PROJECTION_H
#define INC_ACTION_PROJECTION_H
#include "Action.h"
#include "DataSet_Modes.h"
#include "ActionFrameCounter.h"
/// project snapshots on normal modes
class Action_Projection : public Action, ActionFrameCounter {
  public:
    Action_Projection();

    static DispatchObject* Alloc() { return (DispatchObject*)new Action_Projection(); }
    static void Help();

    void Print() {}
  private:
    Action::RetType Init(ArgList&, TopologyList*, FrameList*, DataSetList*,
                          DataFileList*, int);
    Action::RetType Setup(Topology*, Topology**);
    Action::RetType DoAction(int, Frame*, Frame**);

    typedef std::vector<DataSet*> Darray;
    Darray project_;
    DataSet_Modes modinfo_;
    int beg_;
    int end_;
    std::vector<double> sqrtmasses_;
    AtomMask mask_;
};
#endif
