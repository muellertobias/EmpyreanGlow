#include <colormaps.h>

constant unsigned MAX_ITERS = 256;
constant unsigned NUM_COLORS = 257; // 257 colors are there in spectrum map defined in colormaps.h


int mandelbrot(float2 c)
{
    float2 z = (float2)(0.0f, 0.0f);
	float2 z_p = z;
	unsigned int iterations = 0;

	while (dot(z, z) <= 4 && iterations < MAX_ITERS)
	{
		z_p = z;
		z.s0 = z_p.s0 * z_p.s0 - z_p.s1 * z_p.s1 + c.s0;
		z.s1 = 2 * z_p.s0 * z_p.s1 + c.s1;

		++iterations;
	}

	return iterations;
}

kernel
void fractal(write_only image2d_t out, int sizeX, int sizeY,
             float scaleX, float scaleY, float moveX, float moveY)
{
    const int gx = get_global_id(0);
    const int gy = get_global_id(1);

    float h0 = (sizeX / 2.0f);
    float h1 = (sizeY / 2.0f);

    float2 scale     = (float2)(scaleX, scaleY);
    float2 translate = (float2)(moveX, moveY);
    float2 npos      = (float2)((gx - h0) / h0, (gy - h1) / h1);

    npos = npos * scale + translate;

    if (gx < sizeX && gy < sizeY) 
	{
        int iteration   = mandelbrot(npos);
        int colorIndex  = iteration % NUM_COLORS;
        write_imagef(out, (int2)(gx, gy), SPECTRUM[NUM_COLORS - 1 - colorIndex]);
    }
}
