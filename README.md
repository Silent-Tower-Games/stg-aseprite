# STG ASEprite

ASEprite JSON metadada library in C. Requires the [JSON-C](https://github.com/json-c/json-c) library.

## How To Use

First, export your ASEprite metadata (Ctrl + E). Select "JSON Data", and instead of "Hash", select "Array".

Then, write your code after including this library! Here is an example:

```c
#include <json_c.h>
#include <STGASeprite/STGASeprite.h>

int main()
{
    json_object* json;
    
    STGAseprite aseprite = STGAseprite_LoadFromFile(&json, "aseprite.json");
    
    // Use your ASEprite metadata here; e.g.
    for(int i = 0; i < aseprite->framesLength; i++)
    {
        STGAseprite_Frame* frame = aseprite->frames[i];
        
        // Here, you can get all of the relevant data for a given frame
    }
    
    // Free your ASEprite data here
    STGAseprite_Destroy(&aseprite);
    
    // Free all JSON-C data here
    json_object_put(json);
    
    return 0;
}
```
