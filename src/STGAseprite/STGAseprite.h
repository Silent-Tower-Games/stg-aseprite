#pragma once

#include <json.h>

#define STGASEPRITE_SET(src, func) {\
    json_object_object_get_ex(json, #src, &prop); \
    parent.src = func(prop); \
}

#define STGASEPRITE_FOREACH(src, func, type) {\
    json_object_object_get_ex(json, #src, &prop); \
    size_t length = json_object_array_length(prop); \
    parent.src = malloc(sizeof(type) * length); \
    for(int i = 0; i < length; i++) \
    { \
        struct json_object* index = json_object_array_get_idx(prop, i); \
        parent.src[i] = func(index); \
    }\
}

typedef struct STGAseprite_Rect
{
    int x;
    int y;
    int w;
    int h;
} STGAseprite_Rect;

typedef struct STGAseprite_Position
{
    int x;
    int y;
} STGAseprite_Position;

typedef struct STGAseprite_Size
{
    int w;
    int h;
} STGAseprite_Size;

typedef struct STGAseprite_FrameTag
{
    const char* name;
    int from;
    int to;
    const char* direction;
} STGAseprite_FrameTag;

typedef struct STGAseprite_Layer
{
    const char* name;
    int opacity;
    const char* blendMode;
} STGAseprite_Layer;

typedef struct STGAseprite_Slice_Key
{
    int frame;
    STGAseprite_Rect bounds;
    STGAseprite_Rect center;
    STGAseprite_Position pivot;
} STGAseprite_Slice_Key;

typedef struct STGAseprite_Slice
{
    const char* name;
    const char* color;
    const char* data;
    STGAseprite_Slice_Key* keys;
} STGAseprite_Slice;

typedef struct STGAseprite_Frame
{
    const char* filename;
    STGAseprite_Rect frame;
    char rotated;
    char trimmed;
    STGAseprite_Rect spriteSourceSize;
    STGAseprite_Size sourceSize;
    int duration;
} STGAseprite_Frame;

typedef struct STGAseprite_Meta
{
    const char* app;
    const char* version;
    const char* image;
    const char* format;
    STGAseprite_Size size;
    const char* scale;
    STGAseprite_FrameTag* frameTags;
    STGAseprite_Layer* layers;
    STGAseprite_Slice* slices;
} STGAseprite_Meta;

typedef struct STGAseprite
{
    STGAseprite_Frame* frames;
    STGAseprite_Meta meta;
} STGAseprite;

STGAseprite STGAseprite_LoadFromFile(json_object** json, const char* filename);

STGAseprite STGAseprite_CreateFromJSON(struct json_object* json);

STGAseprite_Frame STGAseprite_Frame_CreateFromJSON(struct json_object* json);

STGAseprite_Meta STGAseprite_Meta_CreateFromJSON(struct json_object* json);

STGAseprite_Rect STGAseprite_Rect_CreateFromJSON(struct json_object* json);

STGAseprite_Position STGAseprite_Position_CreateFromJSON(struct json_object* json);

STGAseprite_Size STGAseprite_Size_CreateFromJSON(struct json_object* json);

STGAseprite_FrameTag STGAseprite_FrameTag_CreateFromJSON(struct json_object* json);

STGAseprite_Layer STGAseprite_Layer_CreateFromJSON(struct json_object* json);

STGAseprite_Slice_Key STGAseprite_Slice_Key_CreateFromJSON(struct json_object* json);

STGAseprite_Slice STGAseprite_Slice_CreateFromJSON(struct json_object* json);
