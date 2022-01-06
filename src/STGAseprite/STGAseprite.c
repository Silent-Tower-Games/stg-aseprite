#include <assert.h>
#include <stdio.h>
#include "STGAseprite.h"

STGAseprite STGAseprite_LoadFromFile(json_object** json, const char* filename)
{
    char* rawJson;
    
    FILE* f = fopen(filename, "r");
    assert(f != NULL);
    
    fseek(f, 0, SEEK_END);
    uint32_t length = ftell(f);
    fseek(f, 0, SEEK_SET);
    rawJson = malloc(sizeof(char) * (length + 1));
    fread(rawJson, 1, length, f);
    fclose(f);
    rawJson[length] = '\0';
    
    *json = json_tokener_parse(rawJson);
    
    free(rawJson);
    
    return STGAseprite_CreateFromJSON(*json);
}

STGAseprite STGAseprite_CreateFromJSON(struct json_object* json)
{
    STGAseprite parent;
    struct json_object* prop;
    
    STGASEPRITE_FOREACH(frames, STGAseprite_Frame_CreateFromJSON, STGAseprite_Frame);
    
    STGASEPRITE_SET(meta, STGAseprite_Meta_CreateFromJSON);
    
    return parent;
}

STGAseprite_Frame STGAseprite_Frame_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Frame parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(filename, json_object_get_string);
    STGASEPRITE_SET(frame, STGAseprite_Rect_CreateFromJSON);
    STGASEPRITE_SET(rotated, json_object_get_int);
    STGASEPRITE_SET(trimmed, json_object_get_int);
    STGASEPRITE_SET(spriteSourceSize, STGAseprite_Rect_CreateFromJSON);
    STGASEPRITE_SET(sourceSize, STGAseprite_Size_CreateFromJSON);
    STGASEPRITE_SET(duration, json_object_get_int);
    
    return parent;
}

STGAseprite_Meta STGAseprite_Meta_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Meta parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(app, json_object_get_string);
    STGASEPRITE_SET(version, json_object_get_string);
    STGASEPRITE_SET(image, json_object_get_string);
    STGASEPRITE_SET(format, json_object_get_string);
    STGASEPRITE_SET(size, STGAseprite_Size_CreateFromJSON);
    STGASEPRITE_SET(scale, json_object_get_string);
    
    STGASEPRITE_FOREACH(frameTags, STGAseprite_FrameTag_CreateFromJSON, STGAseprite_FrameTag);
    STGASEPRITE_FOREACH(layers, STGAseprite_Layer_CreateFromJSON, STGAseprite_Layer);
    STGASEPRITE_FOREACH(slices, STGAseprite_Slice_CreateFromJSON, STGAseprite_Slice);
    
    return parent;
}

STGAseprite_Rect STGAseprite_Rect_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Rect parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(x, json_object_get_int);
    STGASEPRITE_SET(y, json_object_get_int);
    STGASEPRITE_SET(w, json_object_get_int);
    STGASEPRITE_SET(h, json_object_get_int);
    
    return parent;
}

STGAseprite_Size STGAseprite_Size_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Size parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(w, json_object_get_int);
    STGASEPRITE_SET(h, json_object_get_int);
    
    return parent;
}

STGAseprite_Position STGAseprite_Position_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Position parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(x, json_object_get_int);
    STGASEPRITE_SET(y, json_object_get_int);
    
    return parent;
}

STGAseprite_FrameTag STGAseprite_FrameTag_CreateFromJSON(struct json_object* json)
{
    STGAseprite_FrameTag parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(name, json_object_get_string);
    STGASEPRITE_SET(from, json_object_get_int);
    STGASEPRITE_SET(to, json_object_get_int);
    STGASEPRITE_SET(direction, json_object_get_string);
    
    return parent;
}

STGAseprite_Layer STGAseprite_Layer_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Layer parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(name, json_object_get_string);
    STGASEPRITE_SET(opacity, json_object_get_int);
    STGASEPRITE_SET(blendMode, json_object_get_string);
    
    return parent;
}

STGAseprite_Slice_Key STGAseprite_Slice_Key_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Slice_Key parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(frame, json_object_get_int);
    STGASEPRITE_SET(bounds, STGAseprite_Rect_CreateFromJSON);
    STGASEPRITE_SET(center, STGAseprite_Rect_CreateFromJSON);
    STGASEPRITE_SET(pivot, STGAseprite_Position_CreateFromJSON);
    
    return parent;
}

STGAseprite_Slice STGAseprite_Slice_CreateFromJSON(struct json_object* json)
{
    STGAseprite_Slice parent;
    struct json_object* prop;
    
    STGASEPRITE_SET(name, json_object_get_string);
    STGASEPRITE_SET(color, json_object_get_string);
    STGASEPRITE_SET(data, json_object_get_string);
    STGASEPRITE_FOREACH(keys, STGAseprite_Slice_Key_CreateFromJSON, STGAseprite_Slice_Key);
    
    return parent;
}

void STGAseprite_Destroy(STGAseprite* aseprite)
{
    free(aseprite->frames);
    STGAseprite_Meta_Destroy(&aseprite->meta);
}

void STGAseprite_Meta_Destroy(STGAseprite_Meta* meta)
{
    // frameTags, layers, slices
    free(meta->frameTags);
    free(meta->layers);
    
    for(int i = 0; i < meta->slicesLength; i++)
    {
        free(meta->slices[i].keys);
    }
    free(meta->slices);
}
