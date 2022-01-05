#pragma once

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

typedef struct STGAseprite_FrameTags
{
    char* name;
    int from;
    int to;
    char* direction;
} STGAseprite_FrameTags;

typedef struct STGAseprite_Layers
{
    char* name;
    int opacity;
    char* blendMode;
} STGAseprite_Layers;

typedef struct STGAseprite_Slices_Keys
{
    int frame;
    STGAseprite_Rect bounds;
    STGAseprite_Rect center;
    STGAseprite_Position pivot;
} STGAseprite_Slices_Keys;

typedef struct STGAseprite_Slices
{
    char* name;
    char* color;
    char* data;
    STGAseprite_Slices_Keys* keys;
} STGAseprite_Slices;

typedef struct STGAseprite_Frames
{
    char* filename;
    STGAseprite_Rect frame;
    char rotated;
    char trimmed;
    STGAseprite_Rect spriteSourceSize;
    STGAseprite_Size sourceSize;
    int duration;
} STGAseprite_Frames;

typedef struct STGAseprite_Meta
{
    char* app;
    char* version;
    char* image;
    char* format;
    STGAseprite_Size size;
    char* scale;
    STGAseprite_FrameTags* frameTags;
    STGAseprite_Layers* layers;
    void* slices;
} STGAseprite_Meta;

typedef struct STGAseprite
{
    STGAseprite_Frames* frames;
    STGAseprite_Meta* meta;
} STGAseprite;

STGAseprite STGAseprite_Create();
