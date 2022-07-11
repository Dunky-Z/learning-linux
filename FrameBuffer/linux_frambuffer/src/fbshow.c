/**
 * File:   fbshow.c
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  snap framebuffer to png file
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "linux_fb.h"
#include "shmem.h"

int main(int argc, char* argv[]) {
  fb_info_t* fb = NULL;
  const char* filename = NULL;
  const char* fbfilename = NULL;
  // fb_info_t  *shmem_fb   = (fb_info_t *)create_shm();
  if (argc != 3) {
    printf("\nUsage: %s outputfilename [framebuffer dev]\n", argv[0]);
    printf("Example: %s data/rgba.png /dev/fb0\n", argv[0]);
    printf("-----------------------------------------\n");

    return 0;
  }

  filename = argv[1];
  fbfilename = argv[2];

  fb = linux_fb_open(fbfilename);
  if (fb != NULL) {
    bitmap_t* b = bitmap_load(filename);
    if (b != NULL) {
      linux_fb_from_bitmap(fb, b);
      bitmap_destroy(b);
    }
    // shmem_fb->w   = fb->w;
    // shmem_fb->h   = fb->h;
    // shmem_fb->bpp = fb->bpp;
    // printf("data addr = %p\n", shmem_fb->data);
    // // memcpy(shmem_fb->data, fb->data, 3145728);
    // printf("xres = %u\n", shmem_fb->w);
    // printf("yres = %u\n", shmem_fb->h);

    linux_fb_close(fb);
  }

  return 0;
}
