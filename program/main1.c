#include <stdio.h>
#include <stdlib.h>

int main()
{
     FILE *fIn =fopen("lena_color.bmp","rb");
     FILE *fOut = fopen("lena_color_b1.bmp","wb");

     unsigned char imgHeader[54];
     unsigned char colorTable[1024];

     if(fIn ==NULL)
     {
         printf("Unable to open file \n");
     }

     for(int i =0;i<54;i++)
     {
         imgHeader[i] = getc(fIn);
     }
     fwrite(imgHeader,sizeof(unsigned char),54,fOut);

     int height = *(int*)&imgHeader[22];
     int width  = *(int*)&imgHeader[18];
     int bitDepth = *(int*)&imgHeader[28];

     if(bitDepth <=8)
     {
         fread(colorTable,sizeof(unsigned char),1024,fIn);
         fwrite(colorTable, sizeof(unsigned char),1024,fOut);

     }

     int imgSize =  height * width;

     unsigned char buffer[imgSize][3];
     unsigned char output_buffer[imgSize][3];

     for(int i =0;i<imgSize;i++)
     {
         //buffer[i][4] = getc(fIn);
         //buffer[i][3] = getc(fIn);
         buffer[i][2] = getc(fIn);
         buffer[i][1] = getc(fIn);
         buffer[i][0] = getc(fIn);
     }
     float kernel[5][5] = {{1.0/25.0, 1.0/25.0,1.0/25.0,1.0/25.0,1.0/25.0},
                           {1.0/25.0, 1.0/25.0,1.0/25.0,1.0/25.0,1.0/25.0},
                           {1.0/25.0, 1.0/25.0,1.0/25.0,1.0/25.0,1.0/25.0},
                           {1.0/25.0, 1.0/25.0,1.0/25.0,1.0/25.0,1.0/25.0},
                           {1.0/25.0, 1.0/25.0,1.0/25.0,1.0/25.0,1.0/25.0}
                            };

    for(int x =1 ;x<height-1;x++)
    {
        for(int y =1;y<width -1;y++)
        {
            float sum0 = 0.0;
            float sum1 = 0.0;
            float sum2 = 0.0;
            //float sum3 = 0.0;
            //float sum4 = 0.0;
            for(int i =-1;i<=3;i++)
            {
                for(int j=-1;j<=3;j++)
                {
                    sum0  = sum0 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][0];
                    sum1  = sum1 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][1];
                    sum2  = sum2 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][2];
                    //sum3  = sum3 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][3];
                    //sum4  = sum4 + (float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)][4];

                }
            }

            output_buffer[(x)*width+(y)][0] =  sum0;
            output_buffer[(x)*width+(y)][1] =  sum1;
            output_buffer[(x)*width+(y)][2] =  sum2;
            //output_buffer[(x)*width+(y)][3] =  sum3;
            //output_buffer[(x)*width+(y)][4] =  sum4;
        }
    }

    for(int i =0;i<imgSize;i++)
    {
        //putc(output_buffer[i][4],fOut);
        //putc(output_buffer[i][3],fOut);
        putc(output_buffer[i][2],fOut);
        putc(output_buffer[i][1],fOut);
        putc(output_buffer[i][0],fOut);
    }

    fclose(fOut);
    fclose(fIn);
    return 0;
}


