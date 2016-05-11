#ifndef INC_RANGE_H
#define INC_RANGE_H
#include <list>
#include <string>
// Class: Range
/// The Range class is used to hold an ordered list of numbers. 
/** Range can either be set using a range expression, e.g. 
  * X-Y,C-D (X to Y and C to D) etc, or can be set using a beginning 
  * and end number.
*/
class Range {
  public:
    Range();
    Range(std::string const&);
    Range(std::string const&,int);
    Range(const Range&);
    Range& operator=(const Range&);

    typedef std::list<int>::const_iterator const_iterator;
    const_iterator begin() const { return rangeList_.begin();      }
    const_iterator end()   const { return rangeList_.end();        }
    bool Empty()           const { return rangeList_.empty();      }
    int Size()             const { return (int) rangeList_.size(); }

    int SetRange(std::string const&);
    int SetRange(int,int);

    const char *RangeArg();
    void PrintRange(const char*,int);

    void ShiftBy(int);
    void AddToRange(int);
    void RemoveFromRange(int);
    bool InRange(int);

  private:
    std::string rangeArg_;
    std::list<int> rangeList_;
};
#endif