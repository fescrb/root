#include <root/root.h>
#include <root/graphics/graphics.h>

#include <root/io/log.h>

void root_main(struct android_app* state){
    root::log::d("root_main", "Test");
    root::graphics::init();
}