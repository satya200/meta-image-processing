/*
 * AUTHOR: Satya Sundar Sahu
 * DATE: 10-Sept-2019
 * DESC: This is main file for image processing project
 * */

#include"my_header.h"

/*
 * Name: bmp_blur_img()
 * Desc: This is used for Convert RGB to greay scale image.
 * Parameter: No Parameter
 * Return : 0 = on Success
 *          < 0 = On Failure
 * */
int bmp_blur_img()
{
	FILE *fp_src = NULL;
	int ret = -1;

	char img_name_src_path[IMG_NAME_PATH_LENGTH] = {0};
	char img_name_dst_path[IMG_NAME_PATH_LENGTH] = {0};
	char src_img_name[IMG_NAME_BUFF_LENGTH] = {0};
	struct image_reader img_rd;
	struct image_writer img_wr;
	int img_size, blur_level;
	float blur_val;
	float **blur_mat = NULL;
	int temp, i, j;

	printf("Please Enter greay scale image name\n");
	scanf("%s",src_img_name);
	getchar();
	printf("Please enetr between 1 to 3\n");
	scanf("%d",&blur_level);
	if (blur_level > 4) {
		printf("Invalid level, Please enter 1 to 3\n");
		return -2;
	}
	sprintf(img_name_src_path, "%s/%s",IMG_SEARCH_PATH, src_img_name);
	sprintf(img_name_dst_path, "%s/blur_%d_%s",IMG_SEARCH_PATH, blur_level, src_img_name);
	printf("Source image:%s\nDest image:%s\n",img_name_src_path, img_name_dst_path);

	strcpy(img_rd.image_name, img_name_src_path);
	/* DMA allocation according to the use input */
	blur_level = (blur_level*2) + 1;
	blur_val = (blur_level*blur_level);
	printf("blur val=====> %f\n", blur_val);
	blur_mat = (float **)malloc(blur_level * sizeof(float *));
	if (blur_mat == NULL) {
		printf("malloc return NULL\n");
		return -1;
	}
	for (i = 0; i < blur_level; i++) {
		blur_mat[i] = (float *)malloc(blur_level * sizeof(float));
		if (blur_mat[i] == NULL) {
			printf("Null pointer in blur\n");
			return -1;
		}
		for (j = 0; j < blur_level; j++) {
			blur_mat[i][j] = 1.0/blur_val;
			printf("%f ",blur_mat[i][j]);
		}
		printf("\n");
	}
	ret = bmp_image_read(&img_rd);
	if (ret < 0) {
		printf("Error return from bmp_image_read()\n");
	} else {
		printf("Image read success\n");
        }

	if (img_rd.bitDepth == 24) {
		float sum[3] = {0.0};
		printf("This Image is RGB image\n");
	
		strcpy(img_wr.new_image_name, img_name_dst_path);
		printf("====> New name: %s\n",img_wr.new_image_name);
		memcpy(img_wr.header, img_rd.header, sizeof(img_rd.header));
		memcpy(img_wr.colorTable, img_rd.colorTable, sizeof(img_rd.colorTable));
		memcpy(img_wr.buf, img_rd.buf, sizeof(img_rd.buf));
		img_wr.bitDepth = img_rd.bitDepth;

		img_size = (img_rd.height * img_rd.width);

		unsigned char buffer[img_size][3];
		unsigned char out_buffer[img_size][3];
		int index_rd = 0;
		int x = 0, y, height, width;
		height = img_rd.height;
		width = img_rd.width;

		for ( i = 0; i < img_size; i++) {
			buffer[i][0] = img_rd.buf[index_rd];
			index_rd++;
			buffer[i][1] = img_rd.buf[index_rd];
			index_rd++;
			buffer[i][2] = img_rd.buf[index_rd];
			index_rd++;
		}
		for (x = 1; x < height-1; x++) {
			for (y = 1; y < width-1; y++) {
				memset(&sum[0], 0.0, 3 * sizeof(float));
				for (i = -1; i <= blur_level-2; i++) {
					for (j = -1; j <= blur_level-2; j++) {
						sum[0] = sum[0] + (float)blur_mat[i+1][j+1]*buffer[(x+i)*width+(y+j)][0];
						sum[1] = sum[1] + (float)blur_mat[i+1][j+1]*buffer[(x+i)*width+(y+j)][1];
						sum[2] = sum[2] + (float)blur_mat[i+1][j+1]*buffer[(x+i)*width+(y+j)][2];
				}
			}
			out_buffer[(x)*width+(y)][0] = sum[0];
			out_buffer[(x)*width+(y)][1] = sum[1];
			out_buffer[(x)*width+(y)][2] = sum[2];
			}
		}
		/*ret = bmp_image_write(&img_wr);
		if (ret < 0) {
			printf("Error return from bmp_image_write()\n");
		} else {
			printf("Image Write success\n");
        	}*/
	} else {
		printf("THIS IS NOT RGB IMAGE. This format is not supported\n");
		return -2;
	}
	
	return 0;
}

