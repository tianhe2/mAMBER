#ifndef INC_ACTION_ANGLE_H
#define INC_ACTION_ANGLE_H
#include "Action.h"
// Class: Action_Angle
/// Calculate angle between atom(s) in 3 masks
class Action_Angle: public Action {
  public:
    Action_Angle();

    static DispatchObject* Alloc() { return (DispatchObject*)new Action_Angle(); }
    static void Help();

    void Print() {}
  private:
    Action::RetType Init(ArgList&, TopologyList*, FrameList*, DataSetList*,
                          DataFileList*, int);
    Action::RetType Setup(Topology*, Topology**);
    Action::RetType DoAction(int, Frame*, Frame**);

    DataSet *ang_;
    bool useMass_;
    AtomMask Mask1_;
    AtomMask Mask2_;
    AtomMask Mask3_;
};
#endif
