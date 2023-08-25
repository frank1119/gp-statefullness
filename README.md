# C++ Gig Performer Extension StateFullness 
Gig Performer is a live performance VST-host with lots of features. See [Gig Performer](https://gigperformer.com/) for details.  
This extension uses the [Gig Performer SDK](https://github.com/gigperformer/gp-sdk) and is based on the gp-extension-cpp example.  

## Purpose
This extension works in conjunction with StateFullness.vst3. Primary goal is to save userdefined string, double, integer and/or boolean variables in gig file. These variables are relative to the rackspace and when a rackspace is duplicated, the vst plugins are responsible for saving sthe state.
You might call this extension 'headless', because it has no menus or panels. It only adds some scripting functions.
**USE AT YOUR OWN RISK!**

## Disclaimer
I'm in no way affilated to Gig Performer(r) or Deskew(r). Although you can contact me at their forum, Gig Performer ot Deskew are not able to provide any support for this extenstion or the accompanying vst3

## How to build...
These instructions are a copy of build instructions for the gp-extension-cpp example. The vst3 project won't build on macOS since I use in the vst3 some Windows dedicated calls. That renders this project rather useless on macOS.

### ... on Windows

-   Make sure you have [CMake](https://cmake.org), [Git](https://git-scm.com) and a C(++) compiler installed.
    You can get that for example by installing [Visual Studio](https://visualstudio.microsoft.com) with the _Desktop development with C++_ workload and the _Git for Windows_ component.
-   Build (and install) the project via CMake.
    For your convenience we have provided a `build.cmd` which contains all necessary commands:

    ```powershell
    build.cmd
    ```

    **Make sure to run the script from the Visual Studio developer command prompt!**

## How to use in the Global Rackspace
Here are the main script calls for the global rackspace

### Declare a variable

-   Integer declaration
    
    ```gpscript
    var
        b : boolean
        
        b = StateFullness_CreateInt("NumberOfSongparts")
        Print(b)
    ```

-   String declaration
    
    ```gpscript
    var
        b : boolean
        
        b = StateFullness_CreateString("Author")
        Print(b)
    ```
    
-   Declaration with an error
    
    ```gpscript
    var
        b : boolean
        
        b = StateFullness_CreateString("global_1")
        
        b = StateFullness_CreateInt("global_1") // Will return false: global_1 already exists
        Print(b)
    ```
   
### Assigning a value

-   Assigning an integer
    
    ```gpscript
    var
        b : boolean
        
        b = StateFullness_SetInt("NumberOfSongparts", 100)
        Print(b)
    ```
    
-   Assigning a string
    
    ```gpscript
    var
        b : boolean
        author : string
        
        author = "Frank"
        
        b = StateFullness_SetString("Author", author, Length(author))
        Print(b)
    ```

### Getting values

-   Getting an integer

    ```gpscript
    Print (StateFullness_GetInt("NumberOfSongparts"))
    ```

-   Getting a string

    ```gpscript
    Print (StateFullness_GetString("Author"))
    ```

-   Getting an integer from an array

    ```gpscript
    Print (GlobalVars_GetIntFromArray("PowersOfTwo", 2))
    Print (GlobalVars_GetIntFromArray("PowersOfTwo", 3))
    ```

### Removing variables

-   Removing specific variables

    ```gpscript
    Print (StateFullness_DestroyVariable("Contributors"))
    Print (StateFullness_DestroyVariable("NumberOfSongparts"))
    ```

-   Erase all

    ```gpscript
    GlobalVars_RemoveAll()
    ```

### Informational

-   Variable type

    ```gpscript
    var
        tp : integer
    
        tp = StateFullness_GetVariableType("PowersOfTwo")
        Print (tp)
        
        // 0 -> Does not exist
        // 1 -> String value
        // 2 -> Integer value
        // 3 -> Double value
        // 4 -> Boolean value
    ```

## How to use in a Local Rackspace
Here are the main script calls for a Local Rackspace. The main difference is that you need to pass a handle that represents the rackspace

### Declare a variable

-   Integer declaration
    
    ```gpscript
    var
        b : boolean
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
        
        b = StateFullness_CreateInt(handle, "NumberOfSongparts")
        Print(b)
    ```

-   String declaration
    
    ```gpscript
    var
        b : boolean
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
        
        b = StateFullness_CreateString(handle, "Author")
        Print(b)
    ```
    
-   Declaration with an error
    
    ```gpscript
    var
        b : boolean
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
        
        b = StateFullness_CreateString(handle, "global_1")
        
        b = StateFullness_CreateInt(handle, "global_1") // Will return false: global_1 already exists
        Print(b)
    ```
   
### Assigning a value

-   Assigning an integer
    
    ```gpscript
    var
        b : boolean
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
        
        b = StateFullness_SetInt(handle, "NumberOfSongparts", 100)
        Print(b)
    ```
    
-   Assigning a string
    
    ```gpscript
    var
        b : boolean
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
        author : string
        
        author = "Frank"
        
        b = StateFullness_SetString(handle, "Author", author, Length(author))
        Print(b)
    ```

### Getting values

-   Getting an integer

    ```gpscript
    var
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())
    Print (StateFullness_GetInt(handle, "NumberOfSongparts"))
    ```

-   Getting a string

    ```gpscript
    var
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())

    Print (StateFullness_GetString(handle, "Author"))
    ```

### Removing variables

-   Removing specific variables

    ```gpscript
    var
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())

    Print (StateFullness_DestroyVariable(handle, "Contributors"))
    Print (StateFullness_DestroyVariable(handle, "NumberOfSongparts"))
    ```

-   Erase all

    ```gpscript
    var
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())

    GlobalVars_RemoveAll(handle)
    ```

### Informational

-   Variable type

    ```gpscript
    var
        handle : string = StateFullness_GetRackHandle(GetRackspaceName())

    var
        tp : integer
    
        tp = StateFullness_GetVariableType(handle, "PowersOfTwo")
        Print (tp)
        
        // 0 -> Does not exist
        // 1 -> String value
        // 2 -> Integer value
        // 3 -> Double value
        // 4 -> Boolean value
    ```

    
