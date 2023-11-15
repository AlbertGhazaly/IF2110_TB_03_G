#include <stdio.h>
#include "datetime.h"

int GetMaxDay(int M, int Y)
{
    if (M % 2 == 1) {
        return (M < 8) ? 31 : 30;
    }
    if (M != 2){
        return (M < 7) ? 30 : 31;
    }
    if (Y % 400 == 0) {
        return 29;
    }
    if (Y % 100 == 0) {
        return 28;
    }
    if (Y % 4 == 0) {
        return 29;
    }
    return 28;
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s)
{
    int maxday = GetMaxDay (M, Y);
    return (D>=1&&D<=maxday)&&(M>=1&&M<=12)&&(Y>=1900&&Y<=2030)&&(h>=0 && h<24)&&(m>=0 && m<60)&&(s>=0 && s<60);
}

void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss)
{
    TIME T;
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
    CreateTime(&T, hh, mm, ss);
    Time(*D) = T;
}

void BacaDATETIME(DATETIME *D)
{ 
    int DD, MM, YY, hh, mm, ss;
    scanf("%d %d %d %d %d %d", &DD, &MM, &YY, &hh, &mm, &ss);
    while(!IsDATETIMEValid(DD,MM,YY,hh,mm,ss))
    {
        printf("DATETIME tidak valid\n");
        scanf("%d %d %d %d %d %d", &DD, &MM, &YY, &hh, &mm, &ss);
    }
    CreateDATETIME(D, DD, MM, YY, hh, mm, ss);
}

void TulisDATETIME(DATETIME D)
{
    int DD = Day(D);
    int MM = Month(D);
    int YY = Year(D);
    int hh = Hour(Time(D));
    int mm = Minute(Time(D));
    int ss = Second(Time(D));
    printf("%02d/%02d/%d %02d:%02d:%02d", DD, MM, YY, hh, mm, ss);
}

boolean DEQ(DATETIME D1, DATETIME D2)
{
    return (Day(D1)==Day(D2)) && (Month(D1)==Month(D2)) && (Year(D1)==Year(D2)) &&(Hour(Time(D1))==Hour(Time(D2))) && (Minute(Time(D1))==Minute(Time(D2))&& (Second(Time(D1))==Second(Time(D2))));
}

boolean DNEQ(DATETIME D1, DATETIME D2)
{
    return (Day(D1)!=Day(D2)) || (Month(D1)!=Month(D2)) || (Year(D1)!=Year(D2)) || (Hour(Time(D1))!=Hour(Time(D2))) || (Minute(Time(D1))!=Minute(Time(D2)) || (Second(Time(D1)) != Second(Time(D2))));
}

boolean DLT(DATETIME D1, DATETIME D2)
{
    if (Year(D1) < Year(D2))
    {
        return true;
    }
    else if (Year(D1) > Year(D2))
    {
        return false;
    }
    else
    {
        if(Month(D1)<Month(D2))
        {
            return true;
        }
        else if(Month(D1)>Month(D2))
        {
            return false;
        }
        else
        {
            if(Day(D1)<Day(D2))
            {
                return true;
            }
            else if (Day(D1)>Day(D2))
            {
                return false;
            }
            else
            {
                if (TIMEToDetik(Time(D1))< TIMEToDetik(Time(D2)))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

boolean DGT(DATETIME D1, DATETIME D2)
{
    if (Year(D1) < Year(D2))
    {
        return false;
    }
    else if (Year(D1) > Year(D2))
    {
        return true;
    }
    else
    {
        if(Month(D1)<Month(D2))
        {
            return false;
        }
        else if(Month(D1)>Month(D2))
        {
            return true;
        }
        else
        {
            if(Day(D1)<Day(D2))
            {
                return false;
            }
            else if (Day(D1)>Day(D2))
            {
                return true;
            }
            else
            {
                if (TIMEToDetik(Time(D1))>TIMEToDetik(Time(D2)))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

DATETIME DATETIMENextNDetik(DATETIME D, int N)
{
    long s;
    s = TIMEToDetik(Time(D));
    s += N;
    if (s >= 86400){
        Day(D) += floor(s/86400);
        s %= 86400;
        while (Day(D) > GetMaxDay(Month(D), Year(D))){
            Day(D) -= GetMaxDay(Month(D), Year(D));
            Month(D) += 1;
            if (Month(D) > 12){
                Year(D) += 1;
                Month(D) -= 12;
            }
        }
    }
    Time(D) = DetikToTIME(s);
    return D;
}

DATETIME DATETIMEPrevNDetik(DATETIME D, int N)
{
    long s;
    s = TIMEToDetik(Time(D));
    s -= N;
    if (s<0){
        Day(D) += floor(s/86400);
        s %= 86400;
        if (s < 0){
            Day(D) -= 1;
            s += 86400;
        } 
        while (Day(D) < 1){
            if (Month(D) == 1){
                Year(D) -= 1;
                Month(D) = 12;
            } else {
                Month(D) -= 1;
            }
            Day(D) += GetMaxDay(Month(D), Year(D));
        }
    }
    Time(D) = DetikToTIME(s);
    return D;
}

long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh)
{
    int DayAw = 0, DayAkh = 0;
    int i;
    // int selisih_hari = 0;
    for (i=1; i<Year(DAkh); i++) {
        if (i % 400 == 0) {
            DayAkh += 366;
        } else if (i % 100 == 0) {
            DayAkh += 355;
        } else if (i % 4 == 0) {
            DayAkh += 366;
        } else {
            DayAkh += 365;
        }
    }
    for (i=1; i<Month(DAkh); i++) {
        DayAkh += GetMaxDay(i,Year(DAkh));
    }
    DayAkh += Day(DAkh);
    for (i=1; i<Year(DAw); i++) {
        if (i % 400 == 0) {
            DayAw += 366;
        } else if (i % 100 == 0) {
            DayAw += 355;
        } else if (i % 4 == 0) {
            DayAw += 366;
        } else {
            DayAw += 365;
        }
    }
    for (i=1; i<Month(DAw); i++) {
        DayAw += GetMaxDay(i,Year(DAw));
    }
    DayAw += Day(DAw);

    return (DayAkh - DayAw) * 86400 + TIMEToDetik(Time(DAkh)) - TIMEToDetik(Time(DAw));
}

