//
//  asMany.c
//  liuprogram
//
//  Created by 向日葵会下雨 on H27/10/01.
//  Copyright © 平成27年 向日葵会下雨. All rights reserved.
//

#include "asMany.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i,k;
    int x[1000];//y[1000],w[1000],h[1000];
    scanf("%d",&k);
    printf("%d",k);
    for(i=0;i<k;i++){
        scanf("%d",&x[i]);
        printf("%d",x[i]);
    }
}