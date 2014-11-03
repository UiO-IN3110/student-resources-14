#include <stdio.h>
#include <stdlib.h>
#include "simple-jpeg/import_export_jpeg.h"

// Format of the image
typedef struct {
    int n,m;            // Dimensions
    float** image_data; // Data values
} image;


// Function to define
void allocate_image(image *u, int m, int n);
void deallocate_image(image *u);
void convert_jpeg_to_image(const unsigned char* image_chars, image *u);
void convert_image_to_jpeg(const image *u, unsigned char* image_chars);
void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters);


void allocate_image(image *u, int m, int n)
{
    int i;

    (*u).m = m; (*u).n = n;

    float ** image_data = (float**) malloc(m*sizeof(float*));
    for (i=0; i<m; i++)
    {
        image_data[i] = (float*) malloc(n*sizeof(float));
    }
    (*u).image_data = image_data;

    return;
}

void deallocate_image(image *u)
{
    int i;

    for (i=0; i<(*u).m; i++)
    {
        free((*u).image_data[i]);
    }
    free((*u).image_data);

    return;
}

void convert_jpeg_to_image(const unsigned char* image_chars, image *u)
{
    int i; int j;
    int m = (*u).m; int n = (*u).n;

    float ** data = (*u).image_data;

    for (i=0; i<m; i++)
    {
        for (j=0; j<n; j++)
        {
            data[i][j] = (float) image_chars[j+i*n];
        }
    }
    (*u).image_data = data;

    return;
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars)
{
    int i; int j;
    int m = (*u).m; int n= (*u).n;

    float ** data = (*u).image_data;

    for (i=0; i<m; i++)
    {
        for (j=0; j<n; j++)
        {
            image_chars[j+i*n] = (unsigned char) data[i][j];
        }
    }

    return;
}

void iso_diffusion_denoising(image *x, image *y,
        float kappa, int iters)
{
    /* Function of removing noise from pictures
     *
     * image x      :   input picture
     * image y      :   help picture of same size
     * float kappa  :   denoising constant
     * int iters    :   number of itereations
     */

    // Initialize local variables
    int i; int j; int iter;
    float ** tmp;
    int m = (*x).m; int n = (*x).n;
    float ** data0 = (*x).image_data;
    float ** data1 = (*y).image_data;

    // Fill top and bottom edge
    for (i=0; i<m; i++)
    {
        data1[i][0] = data0[i][0];
        data1[i][n-1] = data0[i][n-1];
    }

    // Fill left and right edges
    for (i=1; i<n-1; i++) // skip corners
    {
        data1[0][i] = data0[0][i];
        data1[m-1][i] = data0[m-1][i];
    }

    for (iter=0; iter<iters; iter++)
    {
        // Fill interior
        for (i=1; i<m-1; i++)
        {
            for (j=1; j<n-1; j++)
            {
                data1[i][j] = data0[i][j] +kappa*(data0[i-1][j]
                        +data0[i][j-1] -4*data0[i][j] +data0[i][j+1]
                        +data0[i+1][j]);
            }
        }

        // Swap links between data0 and data1
        tmp = data0;
        data0 = data1;
        data1 = tmp;
    }

    (*x).image_data = data0;
    (*y).image_data = data1;

    return;
}


int main(int argc, char *argv[])
{
    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    /* read from command line: kappa, iters, input_jpeg_filename, output_jpeg_filename */
    kappa = atof(argv[1]);
    iters = atoi(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

    allocate_image (&u, m, n);
    allocate_image (&u_bar, m, n);

    convert_jpeg_to_image (image_chars, &u);
    iso_diffusion_denoising (&u, &u_bar, kappa, iters);
    convert_image_to_jpeg (&u, image_chars);

    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image (&u);
    deallocate_image (&u_bar);

    return 0;
}
