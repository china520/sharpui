// RadioGroupManager.cpp : Defines the entry point for the DLL application.
//

#include <internal/RadioGroupManager.h>

RadioSet::RadioSet()
{
}

void RadioSet::Insert(ui::RadioButtonPtr btn)
{
    _sets.Add(btn, btn);
}

void RadioSet::Remove(ui::RadioButtonPtr btn)
{
    _sets.Remove(btn);
}

int RadioSet::GetCount()
{
    return _sets.GetCount();
}

void RadioSet::MoveFirst()
{
    _sets.First();
}

bool RadioSet::HasNext()
{
    return _sets.HasNext();
}

void RadioSet::MoveNext()
{
    _sets.Next();
}

ui::RadioButtonPtr RadioSet::GetValue()
{
    return _sets.GetKey();
}

RadioGroupManager::RadioGroupManager()
{
}

ui::RadioButtonPtr RadioGroupManager::LookupCheckedRadioFromGroup(const suic::String & name)
{
    ui::RadioButtonPtr ret;

    if (_groups.GetCount() > 0)
    {
        RadioSetPtr rSet;

        if (!_groups.TryGetValue(name, rSet))
        {
            return ret;
        }

        if (rSet->GetCount() > 0)
        {
            rSet->MoveFirst();

            while (rSet->HasNext())
            {
                if (rSet->GetValue()->IsChecked())
                {
                    ret = rSet->GetValue();
                    break;
                }

                rSet->MoveNext();
            }
        }
    }

    return ret;
}

void RadioGroupManager::CheckGroupElement(ui::RadioButtonPtr & element)
{
    RadioSetPtr rSet;

    if (!_groups.TryGetValue(element->GetGroup(), rSet))
    {
        rSet = new RadioSet();

        rSet->Insert(element);
        _groups.Add(element->GetGroup(), rSet.get());
    }
    else
    {
        rSet->Insert(element);
    }
}

void RadioGroupManager::RemoveRadioFromGroup(ui::RadioButtonPtr & element)
{
    RadioSetPtr rSet;

    if (_groups.TryGetValue(element->GetGroup(), rSet))
    {
        rSet->Remove(element);
    }
}

