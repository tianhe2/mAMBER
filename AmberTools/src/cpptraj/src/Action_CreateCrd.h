#ifndef ACTION_CREATECRD_H
#define ACTION_CREATECRD_H
#include "Action.h"
#include "DataSet_Coords.h"
class Action_CreateCrd : public Action {
  public:
    Action_CreateCrd();
    static DispatchObject* Alloc() { return (DispatchObject*)new Action_CreateCrd(); }
    static void Help();
    void Print() {}
  private:
    Action::RetType Init(ArgList&, TopologyList*, FrameList*, DataSetList*,
                          DataFileList*, int);
    Action::RetType Setup(Topology*, Topology**);
    Action::RetType DoAction(int, Frame*, Frame**);

    DataSet_Coords* coords_;
    int pindex_;
};
#endif
