// RadioGroupManager.cpp : Defines the entry point for the DLL application.
//

#include <internal/RadioGroupManager.h>

RadioSet::RadioSet()
{
}

void RadioSet::Insert(ui::RadioButtonPtr btn)
{
    _sets.insert(btn, btn);
}

void RadioSet::Remove(ui::RadioButtonPtr btn)
{
    _sets.erase(btn);
}

int RadioSet::GetCount()
{
    return _sets.size();
}

void RadioSet::MoveFirst()
{
    _iter = _sets.begin();
}

bool RadioSet::HasNext()
{
    return (_iter != _sets.end());
}

void RadioSet::MoveNext()
{
    ++_iter;
}

ui::RadioButtonPtr RadioSet::GetValue()
{
    return _iter->second;
}

RadioGroupManager::RadioGroupManager()
{
}

ui::RadioButtonPtr RadioGroupManager::LookupCheckedRadioFromGroup(const suic::String & name)
{
    ui::RadioButtonPtr ret;

    if (_groups.size() > 0)
    {
        suic::Map<suic::String, RadioSetPtr>::iterator iter = _groups.find(name);
        RadioSetPtr rSet;

        if (iter == _groups.end())
        {
            return ret;
        }

        rSet = iter->second;

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
    
    suic::Map<suic::String, RadioSetPtr>::iterator iter = _groups.find(element->GetGroup());

    if (iter == _groups.end())
    {
        RadioSetPtr rSet(new RadioSet());

        rSet->Insert(element);
        _groups.insert(element->GetGroup(), rSet.get());
    }
    else
    {
        iter->second->Insert(element);
    }
}

void RadioGroupManager::RemoveRadioFromGroup(ui::RadioButtonPtr & element)
{
    suic::Map<suic::String, RadioSetPtr>::iterator iter = _groups.find(element->GetGroup());

    if (iter != _groups.end())
    {
        iter->second->Remove(element);
    }
}

