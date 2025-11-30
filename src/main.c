// SPDX-License-Identifier: CC0
// SPDX-CopyRightText: 2025 Julian Scheffers

#include <stdint.h>
#include <stdio.h>
#include <sys/unistd.h>
#include "asp/display.h"
#include "asp/input.h"
#include "pax_gfx.h"
#include "pgame_layer.h"
#include "pgame_object.h"
#include "pgame_scene.h"

static bool load_texture(pax_buf_t* texture_out, char const* file) {
}

int main(int argc, char** argv) {
    printf("Hello, World!\n");

    pax_buf_t* gfx;
    asp_disp_get_pax_buf(&gfx);

    pax_buf_t dirt, grass, icy_dirt;
    if (!load_texture(&dirt, "dirt.png")) goto err0;
    if (!load_texture(&grass, "grass.png")) goto err1;
    if (!load_texture(&icy_dirt, "icy_dirt.png")) goto err2;

    pgame_object_t objects[] = {
        (pgame_object_t){
            .flags = 0,
            .pos   = {10, 10, 30, 30},
            .color = 0xffff0000,
        },
        (pgame_object_t){
            .flags = 0,
            .pos   = {50, 10, 30, 30},
            .color = 0xff0000ff,
        },
    };

    pax_buf_t* sprites[] = {
        &dirt,
        &grass,
        &icy_dirt,
    };

    pgame_tile_t const T_EMPTY    = {-1, 0};
    pgame_tile_t const T_DIRT     = {0, 0};
    pgame_tile_t const T_GRASS    = {1, 0};
    pgame_tile_t const T_ICY_DIRT = {2, 0};

    pgame_tile_t tiles_0[] = {
        // clang-format off
        T_EMPTY, T_EMPTY, T_EMPTY, T_EMPTY,
        T_EMPTY, T_EMPTY, T_GRASS, T_ICY_DIRT,
        T_GRASS, T_GRASS, T_DIRT, T_DIRT,
        T_DIRT, T_DIRT, T_DIRT, T_DIRT,
        // clang-format on
    };

    pgame_layer_t glayers[] = {
        (pgame_layer_t){
            .dims      = {4, 4},
            .tile_size = 16,
            .tiles     = tiles_0,
        },
    };

    pgame_scene_t scene = {
        .objects_len = sizeof(objects) / sizeof(pgame_object_t),
        .objects     = objects,
        .sprites_len = sizeof(sprites) / sizeof(pax_buf_t*),
        .sprites     = sprites,
        .glayers_len = sizeof(glayers) / sizeof(pgame_layer_t),
        .glayers     = glayers,
        .background  = 0xff3fbfff,
    };

    pgame_scene_render(gfx, &scene);

    asp_disp_write_pax(gfx);

    while (1) {
        asp_input_event_t event;
        asp_input_poll(&event, INT64_MAX);
        if (event.type == ASP_INPUT_EVENT_TYPE_NAVIGATION && event.args_navigation.state &&
            event.args_navigation.key == ASP_INPUT_NAVIGATION_KEY_ESC) {
            break;
        }
    }

    return 0;

err2:
    pax_buf_destroy(&grass);
err1:
    pax_buf_destroy(&dirt);
err0:
    return 1;
}