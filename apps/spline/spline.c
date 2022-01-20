#include <spline.h>

u16 linear(u16 xArr[], u16 yArr[], u8 n, u16 x)
{
    int j;
    int y;
    double xajp1;
    double xaj;
    double yajp1;
    double yaj;

    //如果是左边外插
    if (x <= xArr[0])
    {
        j = 0;
    }
    //如果是右边外插
    else if (x >= xArr[n - 1])
    {
        j = n - 2;
    }
    //内插
    else
    {
        for (j = 1; j < n; j++)
        {
            //找到所在的分段
            if (x <= xArr[j])
            {
                j--;
                break;
            }
        }
    }
    xajp1 = (double)xArr[j + 1];
    xaj = (double)xArr[j];
    yajp1 = (double)yArr[j + 1];
    yaj = (double)yArr[j];
    y = (u16)(0.5 + yaj * ((x - xajp1) / (xaj - xajp1)) + yajp1 * ((x - xaj) / (xajp1 - xaj)));
    return y;
}