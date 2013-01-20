
# ifndef _RADIOGROUPMANAGER_H_
# define _RADIOGROUPMANAGER_H_

#include <sui/sharpuicore.h>
#include <sui/RadioButton.h>
#include <suic/tools/map.h>

typedef suic::Map<suic::String, suic::String> RadioMap;

class RadioSet : public suic::RefObject
{
public:

    RadioSet();

    void Insert(ui::RadioButtonPtr btn);
    void Remove(ui::RadioButtonPtr btn);

    int GetCount();
    void MoveFirst();
    bool HasNext();
    void MoveNext();
    ui::RadioButtonPtr GetValue();

protected:

    suic::Map<ui::RadioButtonPtr, ui::RadioButtonPtr> _sets;
    suic::Map<ui::RadioButtonPtr, ui::RadioButtonPtr>::iterator _iter;
};

typedef suic::shared<RadioSet> RadioSetPtr;

class RadioGroupManager : public suic::RefObject
{
public:
    
    RadioGroupManager();

    ui::RadioButtonPtr LookupCheckedRadioFromGroup(const suic::String & name);
    void CheckGroupElement(ui::RadioButtonPtr & element);
    void RemoveRadioFromGroup(ui::RadioButtonPtr & element);

protected:

    suic::Map<suic::String, RadioSetPtr> _groups;
};

# endif
