idf_component_register(
    SRCS 
        "uart.c" 
        "wifi.c" 
        "ubx_parse.c" 
        "main.c"
        "json_serialize.c"
        "../submodules/cJSON/cJSON.c"   # add cJSON source here
    INCLUDE_DIRS 
        "." 
        "../submodules/cJSON"           # include folder for cJSON.h
)
