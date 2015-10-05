//
//  main.c
//  liuprogram
//
//  Created by 向日葵会下雨 on H27/10/01.
//  Copyright © 平成27年 向日葵会下雨. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef Boolean
#define Boolean int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE  
#define FALSE 0
#endif

Boolean LineAndLine( int A1x, int A1y, int A2x, int A2y, int B1x, int B1y, int B2x, int B2y ){
    {
        const int baseX = B2x - B1x;
        const int baseY = B2y - B1y;
        const int sub1X = A1x - B1x;
        const int sub1Y = A1y - B1y;
        const int sub2X = A2x - B1x;
        const int sub2Y = A2y - B1y;
        
        const int bs1 = baseX * sub1Y - baseY * sub1X;
        const int bs2 = baseX * sub2Y - baseY * sub2X;
        const int re = bs1 * bs2;
        if( re > 0 ){
            return FALSE;
        }
    }
    {
        const int baseX = A2x - A1x;
        const int baseY = A2y - A1y;
        const int sub1X = B1x - A1x;
        const int sub1Y = B1y - A1y;
        const int sub2X = B2x - A1x;
        const int sub2Y = B2y - A1y;
        
        const int bs1 = baseX * sub1Y - baseY * sub1X;
        const int bs2 = baseX * sub2Y - baseY * sub2X;
        const int re = bs1 * bs2;
        if( re > 0 ){
            return FALSE;
        }
    }
    return TRUE;
}

Boolean RectAndLine( int x, int y, int w, int h, int x1, int y1, int x2, int y2 ){
    if( LineAndLine( x, y, x+w, y, x1, y1, x2, y2 ) ){ return TRUE; 	}
    if( LineAndLine( x, y, x, y-h, x1, y1, x2, y2 ) ){ return TRUE; }
    if( LineAndLine( x+w, y, x+w, y-h, x1, y1, x2, y2 ) ){ return TRUE; }
    if( LineAndLine( x, y-h, x+w, y-h, x1, y1, x2, y2 ) ){ return TRUE; }
    
    return FALSE;
}

int main(void) {
    int i,j,p,k;
    int x1,x2,y1,y2,point1=0,point2=0,special1=0,special2=0;
    int wide=0,heigh=0,wide1=0,heigh1=0;
    int counts=2;  // 通過した長方形の数を数える
    int basic=2;//長方形が二つ以上の場合は少なくとも二つの長方形を通過する
    int x[1000],y[1000],w[1000],h[1000];
    printf("長方形の個数を入力してください：");
    scanf("%d",&k);
    if(k<=2 && k>0) printf("通過する長方形の数は%d個です",k);//二個以下の場合の出力
    else if(k>2){//三つ以上の長方形が入力された場合
        printf("これから%d個の長方形を入力するね\n",k);
        for(i=0;i<k;i++){
            printf("%d個目の長方形の左上の座標と幅、高さを入力：",i+1);
            scanf("%d",&x[i]);
            scanf("%d",&y[i]);
            scanf("%d",&w[i]);
            scanf("%d",&h[i]);
            printf("x[%d]=%d,y[%d]=%d,w[%d]=%d,h[%d]=%d\n",i,x[i],i,y[i],i,w[i],i,h[i]);
        }
        for(i=0;i<k;i++){
            for(p=i+1;p<k;p++){
                for(wide=0;wide<=w[i];wide++){
                    x1=x[i]+wide;//a長方形を囲んだ点のx軸を決める
                    for(heigh=0;heigh<=h[i];heigh++){
                        y1=y[i]-heigh;//a長方形を囲んだ点のy軸を決める
                        for(wide1=0;wide1<=w[p];wide1++){
                            x2=x[p]+wide1;//b長方形を囲んだ点のx軸を決める
                            for(heigh1=0;heigh1<=h[p];heigh1++){
                                y2=y[p]-heigh1;//b長方形を囲んだ点のy軸を決める
                                
                                if(x1==x2 && y1!=y2){//2点で直線を決めるときの例外状況
                                    special1=x1;
                                    point1=0;
                                    point2=x1;
                                    special2=10000;
                                }
                                if(y1==y2 && x1!=x2){
                                    special1=0;
                                    point1=y1;
                                    point2=10000;
                                    special2=y1;
                                }
                                if(x1==x2 && y1==y2) break;
                                if(x1!=x2 && y1!=y2){//2点で直線を決めて、x軸とy軸の点に当てはめることによって、線分を決める
                                    point1=y1-x1*((y2-y1)/(x2-x1));
                                    point2=x1-y1*((x2-x1)/(y2-y1));
                                }
                                counts=2;
                                for(j=0;j<k ;j++){
                                    if(j!=i && j!=p){//繋いだ二つの長方形以外の長方形を試す
                                        if (RectAndLine(x[j],y[j],w[j],h[j],special1,point1,point2,special2) == TRUE){
                                            counts++;
                                            //printf("%d個の長方形通過した\n",counts);
                                            if(counts>basic){
                                                basic=counts;
                                            
                                            }
                                            if(basic==k) goto result;//計算量を減らすために、全ての長方形を通過できる結果が出れば計算終了にする
                                        }
                                    }
                                }
                
                            }
                        }
                    }
                }
            }
        }
        
    result: printf("通過した長方形の数は%d個です",basic);
        
    }
    else printf("せめてひとつください！");//k<0の場合の出力
    
}
