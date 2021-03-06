#ifndef ACTION_BOX_H
#define ACTION_BOX_H
#include "Action.h"
/// Manipulate box coords
class Action_Box : public Action {
  public:
    Action_Box();
    static DispatchObject* Alloc() { return (DispatchObject*)new Action_Box(); }
    static void Help();
    void Print() {}
  private:
    Action::RetType Init(ArgList&, TopologyList*, FrameList*, DataSetList*,
                          DataFileList*, int);
    Action::RetType Setup(Topology*, Topology**);
    Action::RetType DoAction(int, Frame*, Frame**);

    Box box_;
    bool nobox_;
};
#endif
