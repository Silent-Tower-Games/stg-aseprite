#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <json.h>
#include "STGAseprite/STGAseprite.h"

#define assertStr(var, str) assert(strcmp(aseprite.var, str) == 0);

int main()
{
    printf("Hello, World!\n");
    
    struct json_object* parsedJSON = NULL;
    
    STGAseprite aseprite = STGAseprite_LoadFromFile(&parsedJSON, "test.json");
    
    assertStr(meta.app, "http://www.aseprite.org/");
    assertStr(meta.image, "8x8.png");
    assertStr(meta.version, "1.2.30-x64");
    assertStr(meta.format, "RGBA8888");
    assert(aseprite.meta.size.w == 64);
    assert(aseprite.meta.size.h == 40);
    assertStr(meta.scale, "1");
    
    if(aseprite.meta.frameTagsLength)
    {
        assert(aseprite.meta.frameTags != NULL);
        assertStr(meta.frameTags[0].name, "man-die");
        assert(aseprite.meta.frameTags[0].from == 0);
        assert(aseprite.meta.frameTags[0].to == 1);
        assertStr(meta.frameTags[0].direction, "forward");
        
        assertStr(meta.frameTags[1].name, "ball");
        assert(aseprite.meta.frameTags[1].from == 30);
        assert(aseprite.meta.frameTags[1].to == 30);
        assertStr(meta.frameTags[1].direction, "forward");
    }
    
    if(aseprite.meta.layersLength)
    {
        assert(aseprite.meta.layers != NULL);
        assertStr(meta.layers[0].name, "Layer 1");
        assert(aseprite.meta.layers[0].opacity == 255);
        assertStr(meta.layers[0].blendMode, "normal");
    }
    
    if(aseprite.meta.slicesLength)
    {
        assert(aseprite.meta.slices != NULL);
        assertStr(meta.slices[0].name, "Slice 1");
        assertStr(meta.slices[0].color, "#0000ffff");
        assertStr(meta.slices[0].data, "kljasdf");
        
        if(aseprite.meta.slices[0].keysLength)
        {
            assert(aseprite.meta.slices[0].keys != NULL);
            assert(aseprite.meta.slices[0].keys[0].frame == 0);
            assert(aseprite.meta.slices[0].keys[0].bounds.x == 1);
            assert(aseprite.meta.slices[0].keys[0].bounds.y == 1);
            assert(aseprite.meta.slices[0].keys[0].bounds.w == 6);
            assert(aseprite.meta.slices[0].keys[0].bounds.h == 6);
            assert(aseprite.meta.slices[0].keys[0].center.x == 1);
            assert(aseprite.meta.slices[0].keys[0].center.y == 1);
            assert(aseprite.meta.slices[0].keys[0].center.w == 4);
            assert(aseprite.meta.slices[0].keys[0].center.h == 4);
            assert(aseprite.meta.slices[0].keys[0].pivot.x == 0);
            assert(aseprite.meta.slices[0].keys[0].pivot.y == 0);
            
            assert(aseprite.meta.slices[0].keys[1].frame == 1);
            assert(aseprite.meta.slices[0].keys[1].bounds.x == 1);
            assert(aseprite.meta.slices[0].keys[1].bounds.y == 1);
            assert(aseprite.meta.slices[0].keys[1].bounds.w == 6);
            assert(aseprite.meta.slices[0].keys[1].bounds.h == 6);
            assert(aseprite.meta.slices[0].keys[1].center.x == 1);
            assert(aseprite.meta.slices[0].keys[1].center.y == 1);
            assert(aseprite.meta.slices[0].keys[1].center.w == 4);
            assert(aseprite.meta.slices[0].keys[1].center.h == 4);
            assert(aseprite.meta.slices[0].keys[1].pivot.x == 0);
            assert(aseprite.meta.slices[0].keys[1].pivot.y == 0);
        }
    }
    
    if(aseprite.framesLength)
    {
        assert(aseprite.frames != NULL);
        assertStr(frames[0].filename, "8x8 0.aseprite");
        assert(aseprite.frames[0].frame.x == 0);
        assert(aseprite.frames[0].frame.y == 0);
        assert(aseprite.frames[0].frame.w == 8);
        assert(aseprite.frames[0].frame.h == 8);
        assert(aseprite.frames[0].rotated == 0);
        assert(aseprite.frames[0].trimmed == 0);
        assert(aseprite.frames[0].spriteSourceSize.x == 0);
        assert(aseprite.frames[0].spriteSourceSize.y == 0);
        assert(aseprite.frames[0].spriteSourceSize.w == 8);
        assert(aseprite.frames[0].spriteSourceSize.h == 8);
        assert(aseprite.frames[0].sourceSize.w == 8);
        assert(aseprite.frames[0].sourceSize.h == 8);
        assert(aseprite.frames[0].duration == 500);
        
        assertStr(frames[1].filename, "8x8 1.aseprite");
        assert(aseprite.frames[1].frame.x == 8);
        assert(aseprite.frames[1].frame.y == 0);
        assert(aseprite.frames[1].frame.w == 8);
        assert(aseprite.frames[1].frame.h == 8);
        assert(aseprite.frames[1].rotated == 0);
        assert(aseprite.frames[1].trimmed == 0);
        assert(aseprite.frames[1].spriteSourceSize.x == 0);
        assert(aseprite.frames[1].spriteSourceSize.y == 0);
        assert(aseprite.frames[1].spriteSourceSize.w == 8);
        assert(aseprite.frames[1].spriteSourceSize.h == 8);
        assert(aseprite.frames[1].sourceSize.w == 8);
        assert(aseprite.frames[1].sourceSize.h == 8);
        assert(aseprite.frames[1].duration == 500);
    }
    
    STGAseprite_Destroy(&aseprite);
    
    json_object_put(parsedJSON);

    printf("Goodbye!\n");
    
    return 0;
}
