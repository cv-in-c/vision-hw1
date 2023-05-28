#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    if(x<0)
    x=0;
    else if(x>=im.w)
    x=im.w-1;
    if(y<0)
    y=0;
    else if(y>=im.h)
    y=im.h-1;
    int p= x + y*im.w +c*im.w*im.h;
    return im.data[p];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if(x<0||x>im.w||y<0||y>im.h||c<0||c>im.c)
    return;
    int k= x + y*im.w + c*im.w*im.h;
    im.data[k]=v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    int k=im.w*im.h*im.c;
    for(int i=0;i<k;i++)
    copy.data[i]=im.data[i];
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int i=0; i<im.w*im.h:i++){
        float r = im.data[i];
        float g = im.data[i+im.h*im.w];
        float b = im.data[i+2*im.h*im.w];
        float y = (0.299*r + 0.587*g + 0.144*b);
        gray.data[i]=y;
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    for(int i=0;i<im.w;i++){
        for(int j=0;j<im.h;j++){
            int k = i + j*im.w + c*im.h*im.w;
            im.data[k]+=v;
        }
    }
}

void clamp_image(image im)
{
    for(int i=0;i<im.h*im.w*im.c;i++){
        if(im.data[i]<0)
        im.data[i]=0;
        else if(im.data[i]>1)
        im.data[i]=1;
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    for(int i=0;i<im.h*im.w;i++)
    {
        float r=im.data[i];
        float g =im.data[i + im.h*im.w];
        float b=im.data[i + 2*im.h*im.w];
        float v = three_way_max(r,g,b);
        float m = three_way_min(r,g,b);
        float c= v-m;
        float s,h,h1=0;
        if(r==0&&g==0&&b==0)
        s=0;
        else
        s=c/v;

        if (c==0)
        h1 = 0;
        else if(v==r)
        h1=(g-b)/c;
        else if(v==g) 
        h1=(g-b)/c +2;
        else if(v==b)
        h1=(r-g)/c +4;
        
        if(h1<0)
        h=(h1/6)+1;
        else
        h=(h1/6);
        im.data[i] = h;
        im.data[i + im.h*im.w]=s;
        im.data[i + 2*im.h*im.w]=v;
    }
}

void hsv_to_rgb(image im)
{
    for(int i=0;i<im.h*im.w;i++)
    {
        float h=im.data[i];
        float s =im.data[i + im.h*im.w];
        float v=im.data[i + 2*im.h*im.w];
        float hueSector, hueFraction, p, q, t, r, g, b;
        hueSector = floor(h * 6);
    hueFraction = (h * 6) - hueSector;
    p = v * (1 - s);
    q = v * (1 - hueFraction * s);
    t = v * (1 - (1 - hueFraction) * s);
    
    switch ((int)hueSector) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
        break;
    }
     r=im.data[i];
     g =im.data[i + im.h*im.w];
     b=im.data[i + 2*im.h*im.w];
}
}