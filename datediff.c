#include<stdio.h>
 
const int monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

inline isLeapYear(int yr) {
    return (
        (yr%4 == 0 && yr%100 != 0) || (yr%400 == 0)
    );
} 

inline int stackYear(int y1, int y2) {
    int daysDiff = 0;
    
    while (
        (y2<y1) && (
            y2 = (
                (y2) && (
                    daysDiff += (
                        (isLeapYear(y2)) ?
                            (366) : (365)
                    )
                ) , y2+1
            )
        )
    );

    return daysDiff;
}

inline int stackMonth(int m, int leap) {
    int stack = 0;
    
    while (
        (m>1) && (
            m = (
                stack += monthDays[m-1], (
                    (m==2 && leap) && (
                        stack++
                    )
                ) , m-1
            ) , 1
        )
    ); 
    return stack; 
}

int main() {
    int y,m,d;
    const int yy = 2018, mm = 1, dd = 1;
    
    int end = 0;
    int status = 0;

    int daysDiff;
    int y1,y2,m1,m2,d1,d2;
    
    // status machine 
    while (
        (!end) && (
            status = (
                (status == 0) ? (
                    puts("输入日期 (yyyy-mm-dd): "),
                    scanf("%d-%d-%d",&y,&m,&d),
                    1
                ) : (status == 1) ? (
                    (
                        (y==0) || (
                            !isLeapYear(y) && (m==2 && d>=29)
                        ) || (
                            !(m>=1 && m<=12) 
                        ) || (
                            d<=0 || d>monthDays[m]
                        )
                    ) ? (2) : (3)
                ) : (status == 2) ? (
                    puts("丢雷楼某！你输入的是什么狗屎！"), 
                    puts("滚回去重来一遍！"),
                    0
                ) : (status == 3) ? (
                    puts("日期验证通过！"),
                    puts("现在开始计算！"),
                    4
                ) : (status == 4) ? (
                    (
                        daysDiff = 0
                    ) , (
                        (
                            (y>yy) ? (
                                1 
                            ) : (y==yy) ? (
                                (m>mm) ? (
                                    1
                                ) : (m==mm) ? (
                                    (d>dd) ? (
                                        1
                                    ) : (
                                        0
                                    )
                                ) : (
                                    0
                                )
                            ) : (
                                0
                            )
                        ) ? (
                            y1 = y, y2 = yy,
                            m1 = m, m2 = mm,
                            d1 = d, d2 = dd
                        ) : (
                            y1 = yy, y2 = y, 
                            m1 = mm, m2 = m, 
                            d1 = dd, d2 = d
                        )
                    ) , (
                        daysDiff += (
                            + stackYear(y1,y2)
                            + stackMonth(m1,isLeapYear(y1))
                            - stackMonth(m2,isLeapYear(y2))
                            + d1
                            - d2
                        )
                    ) , (
                        printf("两日期相差：%d天",daysDiff),
                        end = 1
                    )
                ) : (
                    //fuck you
                    end = 1 
                )
            )
        , 1)
    );
} 
