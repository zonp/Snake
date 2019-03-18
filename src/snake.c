//
// Created by nelsonsun on 19-3-18.
//

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Map.h"

int main()
{
    /** 初始化地图 **/
    initMap();
    /** 显示地图 **/
    map.show();

    clearMap();
    return 0;
}
