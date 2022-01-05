#include <stdio.h>
#include <json.h>

int main()
{
    printf("Hello, World!\n");
    
    struct json_object* parsedJSON = json_tokener_parse("{\"message\":\"hello, world\",\"number\":1,\"obj\":{\"name\":\"John Doe\",\"num\":3}}");
    
    struct json_object* message;
    struct json_object* number;
    json_object_object_get_ex(parsedJSON, "message", &message);
    json_object_object_get_ex(parsedJSON, "number", &number);
    
    printf(
        "Message: `%s`\nNumber: %d\n",
        json_object_get_string(message),
        json_object_get_int(number)
    );
    
    struct json_object* obj;
    struct json_object* name;
    struct json_object* num;
    json_object_object_get_ex(parsedJSON, "obj", &obj);
    json_object_object_get_ex(obj, "name", &name);
    json_object_object_get_ex(obj, "num", &num);
    
    printf(
        "===\nName: `%s`\nNum: %d\n",
        json_object_get_string(name),
        json_object_get_int(num)
    );
    
    json_object_put(parsedJSON);
    
    return 0;
}
