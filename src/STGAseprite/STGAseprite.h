#pragma once

#include <json.h>

#define STGASEPRITE_SET(src, func) {\
    json_object_object_get_ex(json, #src, &prop); \
    parent.src = func(prop); \
}

#define STGASEPRITE_FOREACH(src, func, type) {\
    json_object_object_get_ex(json, #src, &prop); \
    size_t length = json_object_array_length(prop); \
    parent.src ## Length = length; \
    if(length) \
    { \
        parent.src = malloc(sizeof(type) * length); \
        for(int i = 0; i < length; i++) \
        { \
            struct json_object* index = json_object_array_get_idx(prop, i); \
            parent.src[i] = func(index); \
        } \
    } \
    else \
    { \
        parent.src = NULL;\
    } \
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
    int keysLength;
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
    int frameTagsLength;
    STGAseprite_Layer* layers;
    int layersLength;
    STGAseprite_Slice* slices;
    int slicesLength;
} STGAseprite_Meta;

typedef struct STGAseprite
{
    STGAseprite_Frame* frames;
    int framesLength;
    STGAseprite_Meta meta;
} STGAseprite;

/**
 * @brief Load ASEprite JSON metadata from file & create an ASEprite metadata object from it.
 * 
 * @param json pointer to a JSON object pointer
 * @param filename path to the ASEprite JSON metadata file
 * @return STGAseprite ASEprite metadata object
 */
STGAseprite STGAseprite_LoadFromFile(json_object** json, const char* filename);

/**
 * @brief Create an ASEprite metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite JSON metadata
 * @return STGAseprite ASEprite metadata object
 */
STGAseprite STGAseprite_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Frame metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Frame metadata JSON
 * @return STGAseprite_Frame ASEprite Frame metadata object
 */
STGAseprite_Frame STGAseprite_Frame_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Meta metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Meta metadata JSON
 * @return STGAseprite_Meta ASEprite Meta metadata object
 */
STGAseprite_Meta STGAseprite_Meta_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Rect metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Rect metadata JSON
 * @return STGAseprite_Meta ASEprite Rect metadata object
 */
STGAseprite_Rect STGAseprite_Rect_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Position metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Position metadata JSON
 * @return STGAseprite_Meta ASEprite Position metadata object
 */
STGAseprite_Position STGAseprite_Position_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Size metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Size metadata JSON
 * @return STGAseprite_Meta ASEprite Size metadata object
 */
STGAseprite_Size STGAseprite_Size_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite FrameTag metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite FrameTag metadata JSON
 * @return STGAseprite_Meta ASEprite FrameTag metadata object
 */
STGAseprite_FrameTag STGAseprite_FrameTag_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Layer metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Layer metadata JSON
 * @return STGAseprite_Meta ASEprite Layer metadata object
 */
STGAseprite_Layer STGAseprite_Layer_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Key metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Key metadata JSON
 * @return STGAseprite_Meta ASEprite Key metadata object
 */
STGAseprite_Slice_Key STGAseprite_Slice_Key_CreateFromJSON(struct json_object* json);

/**
 * @brief Create an ASEprite Slice metadata object from a JSON object.
 * 
 * @param json JSON object pointer that has the ASEprite Slice metadata JSON
 * @return STGAseprite_Meta ASEprite Slice metadata object
 */
STGAseprite_Slice STGAseprite_Slice_CreateFromJSON(struct json_object* json);

/**
 * @brief Free all memory allocated for the ASEprite metadata object.
 * 
 * @param aseprite pointer to ASEprite metadata object
 */
void STGAseprite_Destroy(STGAseprite* aseprite);

/**
 * @brief Free all memory allocated for the ASEprite Meta metadata object.
 * 
 * @param meta pointer to ASEprite Meta metadata object
 */
void STGAseprite_Meta_Destroy(STGAseprite_Meta* meta);
