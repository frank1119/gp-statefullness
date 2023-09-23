#pragma once

#include "GlobalVarsMapArray.h"
#include "gigperformer/sdk/GPMidiMessages.h"
#include "gigperformer/sdk/GPUtils.h"
#include "gigperformer/sdk/GigPerformerAPI.h"
#include "gigperformer/sdk/types.h"

class LibMain;

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
  protected:
  public:
    /// <summary>
    /// Holds the constructed object.
    /// Provides a way to execute GP_Functions like consoleLog(..)
    /// </summary>
    static LibMain *thisObj;

    /// <summary>
    /// Cache for the uuid of the Global Rackspace
    /// </summary>
    string GRSUuid;

    /// <summary>
    /// Object holding all global vars
    /// </summary>
    GlobalVarsMapArray gv;

    // These must be here but no need to do anything unless you want extra behavior
    explicit LibMain(LibraryHandle handle)
        : GigPerformerAPI(handle)
    {
        thisObj = this;
    }

    ~LibMain() override;

    void OnStatusChanged(GPStatusType status) override;

    void Initialization() override;

    int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                             ExternalAPI_GPScriptFunctionDefinition **list) override;

    void OnRackspaceActivated() override;

    // This MUST be defined in your class
    string GetProductDescription() override;
};
