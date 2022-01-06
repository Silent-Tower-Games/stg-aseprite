#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <json.h>
#include "STGAseprite/STGAseprite.h"

int main()
{
    struct json_object* parsedJSON;
    
    STGAseprite aseprite = STGAseprite_LoadFromFile(&parsedJSON, "8x8.json");
    
    assert(strcmp(aseprite.meta.image, "8x8.png") == 0);
    
    json_object_put(parsedJSON);
    
    return 0;
}
