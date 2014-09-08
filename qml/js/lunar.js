/*********************|数据定义区|********************/
/* 公历每月1号前面的天数(平年) */
var sunMonthDayOffset = [0,31,59,90,120,151,181,212,243,273,304,334];

/* 默认的农历中文月份名称 */
var lunarMonthName = ["腊","正","二","三", "四","五","六","七", "八","九","十","冬"];
/* 农历月份中每天的基本名称 */
var lunarDayName = [
            "三十","初一","初二","初三","初四","初五","初六","初七","初八","初九",
            "初十","十一","十二","十三","十四","十五","十六","十七","十八","十九",
            "二十","廿一","廿二","廿三","廿四","廿五","廿六","廿七","廿八","廿九"
        ];
/*天干 */
var nature = ["癸","甲","乙","丙","丁","戊","己","庚","辛","壬"];
/*地支 */
var earth = ["亥","子","丑","寅","卯","辰","巳","午","未","申","酉","戌"];
/* 属相名 */
var animal = [ "猪","鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗" ];

/**
 * 农历数据记录从1900年到2099年每年的正月初一的公历日期、闰月和大小月分配
 * 数据说明：例如1900年的数据“0x1319296D”，第一位1是正月的公历月份，第二
 * 位和第三位的组合31是正月的公历日期，第四位9是闰月的所在月（即闰八月，
 * 如果是0则表示没有闰月），最后四位296D表示指定农历年的大小月排列（十六进
 * 制转二进制，转成二进制后，第一个数字1作为分隔符，在后面的数字中，0表示
 * 小月，1表示大月）
 */
var lunarData = [
            0x1319296D, 0x219014AE, 0x20801A57, 0x12962A4D, 0x21601D26, 0x20401D95, 0x12552D55,
            0x2130156A, 0x202019AD, 0x1223295D, //1900-1909
            0x210014AE, 0x1307349B, 0x21801A4D, 0x20601D25, 0x12663AA5, 0x21401B54, 0x20301D6A,
            0x123332DA, 0x2110195B, 0x20182937, //1910-1919
            0x22001497, 0x20801A4B, 0x1286364B, 0x216016A5, 0x205016D4, 0x124535B5, 0x213012B6,
            0x20201957, 0x1233292F, 0x21001497, //1920-1929
            0x13072C96, 0x21701D4A, 0x20601EA5, 0x12662DA9, 0x214015AD, 0x204012B6, 0x1244326E,
            0x2110192E, 0x1318392D, 0x21901C95, //1930-1939
            0x20801D4A, 0x12773B4A, 0x21501B55, 0x2050156A, 0x1255355B, 0x2130125D, 0x2020192D,
            0x1223392B, 0x21001A95, 0x12983695, //1940-1949
            0x217016CA, 0x20601B55, 0x12762AB5, 0x214014DA, 0x20301A5B, 0x12442A57, 0x2120152B,
            0x1319352A, 0x21801E95, 0x208016AA, //1950-1959
            0x128735AA, 0x21501AB5, 0x205014B6, 0x125534AE, 0x21301A57, 0x20201526, 0x12143D26,
            0x20901D95, 0x13082B55, 0x2170156A, //1960-1969
            0x2060196D, 0x1276295D, 0x215014AD, 0x20301A4D, 0x12353A4D, 0x21101D25, 0x13193AA5,
            0x21801B54, 0x20701B6A, 0x128732DA, //1970-1979
            0x2160195B, 0x2050149B, 0x12553497, 0x21301A4B, 0x202B364B, 0x220016A5, 0x209016D4,
            0x129735B4, 0x21701AB6, 0x20601957, //1980-1989
            0x1276292F, 0x21501497, 0x2040164B, 0x12342D4A, 0x21001EA5, 0x13192D65, 0x219015AC,
            0x20701AB6, 0x1286326D, 0x2160192E, //1990-1999
            0x20501C96, 0x12453A95, 0x21201D4A, 0x20101DA5, 0x12232B55, 0x2090156A, 0x1298355B,
            0x2180125D, 0x2070192D, 0x1266392B, //2000-2009
            0x21401A95, 0x20301B4A, 0x123536AA, 0x21001AD5, 0x131A2AB5, 0x219014BA, 0x20801A5B,
            0x12872A57, 0x2160152B, 0x20501A93, //2010-2019
            0x12552E95, 0x212016AA, 0x20101AD5, 0x122329B5, 0x210014B6, 0x129734AE, 0x21701A4E,
            0x20601D26, 0x12663D26, 0x21301D53, //2020-2029
            0x203015AA, 0x12342D6A, 0x2110196D, 0x131C295D, 0x219014AD, 0x20801A4D, 0x12873A4B,
            0x21501D25, 0x20401D52, 0x12463B54, //2030-2039
            0x21201B5A, 0x2010156D, 0x1223295B, 0x2100149B, 0x13083497, 0x21701A4B, 0x20601AA5,
            0x126636A5, 0x214016D2, 0x20201ADA, //2040-2049
            0x12342AB6, 0x21101937, 0x2019292F, 0x21901497, 0x2080164B, 0x12872D4A, 0x21501EA5,
            0x204016B2, 0x1245356C, 0x21201AAE, //2050-2059
            0x2020192E, 0x1214392E, 0x20901C96, 0x12983A95, 0x21701D4A, 0x20501DA5, 0x12662B55,
            0x2140156A, 0x20301A6D, 0x12352A5D, //2060-2069
            0x2110152D, 0x1319352B, 0x21901A95, 0x20701B4A, 0x127736AA, 0x21501AD5, 0x2050155A,
            0x124534BA, 0x21201A5B, 0x2020152B, //2070-2079
            0x12243527, 0x20901693, 0x12982E53, 0x217016AA, 0x20601AD5, 0x126629B5, 0x214014B6,
            0x20301A57, 0x12452A4E, 0x21001D26, //2080-2089
            0x13093D26, 0x21801D52, 0x20701DAA, 0x12772D6A, 0x2150156D, 0x205014AE, 0x1255349D,
            0x21201A4D, 0x20101D15, 0x12133B25, //2090-2099
        ];

/*********************|方法|********************/
/* 这个里面的对象包含三个元素{y:年份, m:月份, d:月中的天}
/* 平润年 */
function isLeapYear(y) {
    return (!((y)%400) || (!((y)%4) && ((y)%100)));
}

/* 获取太阳历中某年某月某天是今年的第几天, 返回1-366 */
function daysOfSunYear(sd) {
    return (sunMonthDayOffset[sd.m - 1] + sd.d + (isLeapYear(sd.y) && (sd.m > 2)));
}


/*获取中文月份名 */
function monthNameInYear(m) {
    return lunarMonthName[m % 12];
}

/* 获取农历天数名 */
function dayNameInMonth(d) {
    return lunarDayName[d % 30];
}

/* 解析农历数据的一些方法 */
//根据年份获取农历数据
function getLunarData(y) {
    return lunarData[y - 1900];
}

//根据年份获取农历正月初一所在的太阳历月份
function lunarSpringInSunMonth(y) {
    return getLunarData(y) >> 28;
}

//获取农历正月初一所在的太阳历月份中的具体日子
function lunarSpringInSunDay(y) {
    var ld = getLunarData(y);
    return ((ld >> 20) & 0xf) + ((ld >> 24) & 0xf) * 10;
}

/**
 * 获取润月的索引值
 * 这个索引值为0表示没有润月
 * 不是零的时候，表示的是大小月数据的索引。
 */
function lunarLeapMonthIndex(y) {
    return (getLunarData(y) >> 16) & 0xf;
}

function lunarLeapMonth(y) {
    //获取润几月
    var tmp = lunarLeapMonthIndex(y);
    return tmp ? (tmp - 1) : 0;
}

function lunarMonths(y) {
    //返回这一年有多少个农历月
    return 12 + (lunarLeapMonthIndex(y) > 0);
}

/* 判断是否减去一年,以春节为分割 */
function isMinus(sd) {
    return (sd.m <= lunarSpringInSunMonth(sd.y)) && (sd.d < lunarSpringInSunDay(sd.y));
}

/* 获取大小月 */
function getLunarBLArray(y) {
    var arraySize = lunarMonths(y);
    var BLData=getLunarData(y) & 0x1fff;
    var arr = [];
    for(var i=0;i<arraySize;++i){
        arr[i] = ((BLData >> ( arraySize - i - 1)) & 1)+ 29;
    }
    return arr;
}

/* 阳历转阴历 ,传入阳历日期，大小月以及润月*/
function sun2Lunar(sd, bl, lm) {
    // 检测数据的有效性,只要检测下限就可以了
    var pLD = {};
    if(sd.y === 1900 && sd.m === 1 && sd.d < 31)
        return null;
    // 进行必要的数据转化，使得LunurDate 中保存的是春节的日期
    pLD.y = sd.y;
    pLD.m = lunarSpringInSunMonth(sd.y);
    pLD.d = lunarSpringInSunDay(sd.y);
    var offset=daysOfSunYear(sd) - daysOfSunYear(pLD);
    
    var countDays=0;
    var i = 0;
    if(offset<0){
        --pLD.y;
        countDays = offset+ (lunarData(pLD.y) & 1 ? 30 : 29);
        pLD.m = lunarMonths(pLD.y)-(countDays<0)-(lunarLeapMonthIndex(pLD.y) > 0);
        pLD.d= ((countDays<0) ? (getLunarData(pLD.y) & 2 ? 30 : 29) : 0) + countDays + 1;
    }else{
        for(;i<bl.length;++i){
            countDays += bl[i];
            if(countDays>offset)
                break;
        }
        pLD.d = offset+bl[i]-countDays+1;
        pLD.m = i+(lm === 0);
    }
    return pLD;
}

/*********************| 一个外部接口，通过字符串获取农历 |****************/
function lunarStr(dateNum) {
    var sd = {};
    sd.y = parseInt(dateNum / 10000);
    sd.m = parseInt((dateNum % 10000) / 100);
    sd.d = parseInt(dateNum % 100);
    var tmp =(sd.y - 3 - isMinus(sd)); 
    var ea = tmp % 12;
    var ret = nature[tmp % 10] + earth[ea] + "年[" + animal[ea] + "] ";
    var lm = lunarLeapMonth(sd.y);
    var bl = getLunarBLArray(sd.y);
    var ld = sun2Lunar(sd, bl, lm);
    if (lm) {
        if (ld.m < lm) {
            ret += monthNameInYear(ld.m + 1) + "月";
        } else if (ld.m > lm) {
            ret += monthNameInYear(ld.m) + "月";
        } else {
            ret += "[润]" + monthNameInYear(ld.m) + "月";
        }
    } else {
        ret += monthNameInYear(ld.m) + "月";
    }
    ret += dayNameInMonth(ld.d);
    return ret;
}
