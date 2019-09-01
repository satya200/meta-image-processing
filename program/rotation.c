/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 1-Sept-2019
 * Contact: tinkusahu.com@gmail.com
 * DESC: This is used for image rotation
 * */

#include"my_header.h"

int bmp_img_right_rot(struct image_reader_mat img_rd, struct image_writer_mat *img_wr, int rot)
{
	int ret = -1;
	int row, col, x, y;

	if (img_wr == NULL) {
		printf("NULL pointer\n");
		return -1;
	}
	row = img_rd.width;
	col = img_rd.height;
	printf("=====>row1 = %d\ncol1 = %d\n", row, col);
	//printf("rd====>%x\n",img_rd.buf[0][0]);
	//printf("wr=====>%x\n",img_wr->buf[0][0]);
	if (rot == 1) {
		printf("Satya==>In rotation\n");
		for (x = 0; x < row; x++) {
			//printf("Satya==>row%d\n",x);
			for (y = 0; y < col; y++) {
				//printf("Satya==>col%d\n",y);
				img_wr->buf[y][col-1-x] = img_rd.buf[x][y];
				//img_wr->buf[x][y] = img_rd.buf[x][y];
			}
		}
		ret = 0;
	} else if (rot == 2) {
		printf("Cooming Soon\n");
	} else if (rot == 3) {
		printf("Cooming Soon\n");
	} else {
		printf("In valid choice\n");
	}
	return ret;
}

int bmp_image_rotation()
{
	int ret = -1;
	int x, y, rot, img_size, row, col;
	FILE *fp_src = NULL;

	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader_mat img_rd;
	struct image_writer_mat img_wr;

	printf("Please Enter bmp image name and rotation choice\n1: Right\n2: Left\n3: rot 180\n");
	scanf("%s%d",src_img_name, &rot);
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	sprintf(img_name_dst_path, "%s/rot%d_%s",IMG_SEARCH_PATH, rot, src_img_name);
	printf("Source image:%s\nDest image:%s\n",img_name_src_path, img_name_dst_path);

	strcpy(img_rd.image_name, img_name_src_path);
	ret = bmp_image_read_mat(&img_rd);
	if (ret < 0) {
		printf("Error return from bmp_brightness_correction()\n");
	} else {
		printf("Image read success\n");
        }

	strcpy(img_wr.new_image_name, img_name_dst_path);
	printf("====> New name: %s\n",img_wr.new_image_name);
	memcpy(img_wr.header, img_rd.header, sizeof(img_rd.header));
	memcpy(img_wr.colorTable, img_rd.colorTable, sizeof(img_rd.colorTable));
	img_wr.bitDepth = img_rd.bitDepth;

	row = img_rd.width;
        col = img_rd.height;
	img_size = (img_rd.height) * (img_rd.width);
	printf("=====>row = %d\ncol = %d\n", row, col);
	/* DMA Memory Allocation */
        img_wr.buf = (unsigned char ** )malloc((row) * sizeof(unsigned char *));
        if (img_wr.buf == NULL) {
                printf("malloc return NULL\n");
                return -1;
        }
        for (int i = 0; i < row; i++) {
                img_wr.buf[i] = (unsigned char *)malloc((col) * sizeof(unsigned char));
                if (img_wr.buf[i] == NULL) {
                        printf("malloc return NULL\n");
                        return -1;
                }
        }

	if (rot == 1) {
		ret = bmp_img_right_rot(img_rd, &img_wr, rot);
		if (ret < 0) {
			printf("Right Rotating Failed\n");
		}
	} else if (rot == 2) {
		ret = bmp_img_right_rot(img_rd, &img_wr, rot);
		if (ret < 0) {
			printf("Left Rotating Failed\n");
		}
	} else if (rot == 3) {
		ret = bmp_img_right_rot(img_rd, &img_wr, rot);
		if (ret < 0) {
			printf("180 Rotating Failed\n");
		}
	} else {
		printf("This Rotation not yet implemented\n");
	}
	if (ret < 0) {
		printf("Rotation return invalid\n");
		return -2;
	}
	ret = bmp_image_write_mat(&img_wr, img_size);
	if (ret < 0) {
		printf("Error return from image_erite bmp_brightness_correction()\n");
	} else {
		printf("Image write success\n");
        }
	return ret;
}
