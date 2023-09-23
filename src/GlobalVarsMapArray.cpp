#include "GlobalVarsMapArray.h"
#define reg regex("^[A-Za-z_][A-Za-z0-9_]{0,39}$")

// fake array notation: ^[A-Za-z_][A-Za-z0-9_]{0,39}([(][0-9]{1,3}[)]){0,1}$  -> Var(1) == OK

bool GlobalVarsMapArray::CreateString(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle];
        return v->CreateString(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateInt(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle];
        return v->CreateInt(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateDouble(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle];
        return v->CreateDouble(name);
    }
    return false;
}

bool GlobalVarsMapArray::CreateBool(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 0)
            AddRackspaceByUuid(handle);

        GlobalVarsMap *v = dicts[handle];
        return v->CreateBool(name);
    }
    return false;
}

int GlobalVarsMapArray::GetVariableType(const string handle, const string name)
{
    if (std::regex_match(name.c_str(), reg))
    {
        if (dicts.count(handle) == 1)
        {
            GlobalVarsMap *v = dicts[handle];
            return v->GetVariableType(name);
        }
    }
    return 0;
}

bool GlobalVarsMapArray::SetString(const string handle, const string name, const string value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->SetString(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetInt(const string handle, const string name, int value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->SetInt(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetDouble(const string handle, const string name, double value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->SetDouble(name, value);
    }

    return false;
}

bool GlobalVarsMapArray::SetBool(const string handle, const string name, bool value)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->SetBool(name, value);
    }

    return false;
}

string GlobalVarsMapArray::GetStringValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->GetStringValue(name);
    }

    return "";
}

int GlobalVarsMapArray::GetIntValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->GetIntValue(name);
    }

    return 0;
}

double GlobalVarsMapArray::GetDoubleValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->GetDoubleValue(name);
    }
    return 0;
}

bool GlobalVarsMapArray::GetBoolValue(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->GetBoolValue(name);
    }
    return 0;
}

bool GlobalVarsMapArray::DestroyVariable(const string handle, const string name)
{
    if (dicts.count(handle) == 1)
    {
        GlobalVarsMap *v = dicts[handle];
        return v->DestroyVariable(name);
    }
    return false;
}

void GlobalVarsMapArray::RemoveAll()
{
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        i->second->RemoveAll();
    }
}

void GlobalVarsMapArray::RemoveAllDictionaires()
{
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        i->second->RemoveAll();
    }
    dicts.clear();
}

void GlobalVarsMapArray::AddRackspaceByUuid(string handle)
{
    if (dicts.count(handle) == 0)
    {
        GlobalVarsMap *gv = new GlobalVarsMap();
        dicts[handle] = gv;
    }
}

void GlobalVarsMapArray::RemoveAllPerRack(string rackspaceUuid)
{
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
        {
            i->second->RemoveAll();
        }
    }
}

std::string GlobalVarsMapArray::getAllState(string rackspaceUuid)
{
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
        {
            string s = i->second->getAllState().dump();
            return s;
        }
    }
    return "";
}

void GlobalVarsMapArray::setAllState(string rackspaceUuid, string state)
{
    AddRackspaceByUuid(rackspaceUuid);
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
            i->second->setAllState(state);
    }
}

void GlobalVarsMapArray::dumpAllState(string rackspaceUuid, LibMain *lib, string rackspaceName)
{
    for (auto i = begin(dicts); i != end(dicts); i++)
    {
        string uuid = i->first;

        if (uuid.compare(rackspaceUuid) == 0)
            i->second->dumpAllState(lib, rackspaceName);
    }
}
