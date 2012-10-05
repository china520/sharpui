
# ifndef _RADIOGROUPMANAGER_H_
# define _RADIOGROUPMANAGER_H_

#include <sui/sharpuicore.h>
#include <sui/RadioButton.h>

typedef suic::StringMapPtr RadioMap;

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

    suic::Dictionary<ui::RadioButtonPtr, ui::RadioButtonPtr> _sets;
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

    suic::Dictionary<suic::String, RadioSetPtr> _groups;
};

# endif
