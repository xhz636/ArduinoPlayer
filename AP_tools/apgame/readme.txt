====================游戏ROM编译器说明====================
游戏源文件[.txt]以重定向的方式输入apgc.exe
源文件最后需要有一行空行（即最后以回车结尾）
编译生产的"a.apg"即为游戏ROM文件
=========================================================

====================Arduino Player的SD卡内游戏文件说明====================
游戏以文件夹形式保存，所有文件命名格式需为8.3格式，且不能为中文
文件夹名即为游戏名
"[游戏名]"文件夹内包含
文件：
1.游戏ROM:以"game.apg"命名
2.游戏图标：以"icon.api"命名
3.游戏帮助：以"help.txt"命名
4.游戏记录：以"save.aps"命名，且初始内容为空，游戏中会自动进行记录
5.游戏简介：以"name.txt"命名
文件夹：
1.游戏地图：以"map"命名，内包含所有游戏地图，地图文件以"[数字].map"命名，其中数字从1开始顺序增大
==========================================================================

====================游戏源文件格式说明====================
备注:[]代表名称 ...代表语句 <>为必需
<data segment>          //数据段
    data declare...     //声明变量
<data ends>             //数据段结束

<code segment>          //代码段

[main] <proc>           //函数
    code statement...   //代码
[sign]<:>               //标号
    code statement...   //代码
    <ret>               //return
[main] <endp>           //函数结束

[fun1] <proc>           //同上
    code statement...
    <ret>
[fun1] <endp>

...

<code ends>             //代码段结束

<end> [main]            //声明主函数
==========================================================

====================游戏源文件语法说明====================
指令：
备注:num为数值(类型为16位int),var为16位int变量,sign为标记,proc为函数名
操作码  操作数          注释
dtc     char    int     int转换为unsigned char
ctd     int     char    unsigned char转换为int
atp     str1    string  str1 = string
mov     var     num     var = num
mov     var1    var2    var1 = var2
add     var     num     var += num
add     var1    var2    var1 += var2
sub     var     num     var -=num
sub     var1    var2    var1 -=var2
mul     var     num     var *= num
mul     var1    var2    var1 *= var2
div     var     num     var /= num
div     var1    var2    var1 /= var2
mod     var     num     var %= num
mod     var1    var2    var1 %= var2
shl     var     num     var <<= num
shl     var1    var2    var1 <<= var2
shr     var     num     var >>= num
shr     var1    var2    var1 >>= var2
and     var     num     var &= num
and     var1    var2    var1 &= var2
or      var     num     var |= num
or      var1    var2    var1 |= var2
xor     var     num     var ^= num
xor     var1    var2    var1 ^= var2
cmp     var     num     var - num
cmp     var1    var2    var1 - var2
not     var             var = ~var
inc     var             var++
dec     var             var--
jmp     sign            跳转至sign
je      sign            相等跳转
jne     sign            不相等跳转
jg      sign            大于跳转
jge     sign            大于等于跳转
jl      sign            小于跳转
jle     sign            小于等于跳转
call    proc            调用函数proc
ret                     函数返回

系统函数调用：
函数名          参数列表（用空格隔开,前面有->代表返回值）
//注释

btnPress        pin         ->pressed
//判断按钮

fillScr         color_r     color_g     color_b
//全屏填充

setColor        color_r     color_g     color_b
//设置颜色

drawPixel       point_x1    point_y1
//画点

drawLine        point_x1    point_y1    point_x2    point_y2
//画线

drawRect        point_x1    point_y1    point_x2    point_y2
//无填充色矩形

drawCircle      point_x1    point_y1    point_radius
//无填充色圆

fillRect        point_x1    point_y1    point_x2    point_y2
//填充矩形

fillCircle      point_x1    point_y1    point_radius
//填充圆

delay           time_delay
//延时等待

showAscii       point_x1    point_y1    ascii       color_r     color_g     color_b     dot
//显示ASCII

showEnglish     point_x1    point_y1    english     color_r     color_g     color_b     dot
//显示ASCII句子

showHZ          point_x1    point_y1    hz          color_r     color_g     color_b     dot
//显示汉字

showChinese     point_x1    point_y1    chinese     color_r     color_g     color_b     dot
//显示中文句子

openMap         map_index
//打开地图文件

mapSeek         map_offset
//以绝对位置移动文件句柄

mapPosition     ->map_position
//获取句柄，并赋值给变量

mapRead         ->map_read
//读取文件1byte,并赋值给变量

mapSize         ->map_size
//获取文件大小，并赋值给变量

closeMap
//关闭地图

getMapAmount    ->map_amount
//计算地图数量

getMapFlag      map_x       map_y       ->map_xy_flag
//获取地图坐标信息

setMapFlag      map_x       map_y       map_xy_flag
//修改地图坐标信息

numPrintf       num         str1
//将数字转换为字符串

setString       str1        index1      ascii
//修改字符串中的一个字符

strcpy          str1        str2
//字符串复制

strcat          str1        str2
//字符串连接

strcmp          str1        str2        ->str_cmp
//字符串比较，并将结果赋值给变量

strlen          str1        ->str_len
//将字符串长度赋值给变量

updateSave      all         win         lose
//更新游戏记录

updateMap       map_index
//游戏过关

exitGame
//退出游戏
==========================================================

====================游戏源文件变量说明====================
备注：int类型变量均为16位
系统默认全局变量包括：
int pin                 判断的按钮引脚
int pressed             按钮判断结果

int color_r             \
int color_g              >颜色分量
int color_b             /

int point_x1            \
int point_y1             \
int point_x2              >绘图坐标参数
int point_y2             /
int point_radius        /

int time_delay          延时时间

unsigned char ascii     \
char* english            \
char* hz                 /需要显示的信息
char* chinese           /
int dot                 字号

int map_index           地图标号
int map_offset          地图文件偏移
int map_position        当前地图文件偏移
unsigned char map_read  读取的地图文件数据
int map_size            地图文件大小
int map_amount          地图数量

unsigned char map_flag[22][17]
                        地图信息记录
int map_x               地图x坐标
int map_y               地图y坐标
unsigned char map_xy_flag
                        地图信息

int num                 数字
char* str1              \
char* str2              /字符串
int str_cmp             字符串比较结果
int str_len             字符串长度

int all                 \
int win                  >游戏记录数据
int lose                /

int index1              \
int index2              /临时存储数组偏移

游戏自建全局变量说明：
需要自建全局变量请在data segment中进行声明，格式为：
[变量名]    [变量类型][[数组元素个数]]        [初值]
变量类型包括:unsigned_char, int, string
备注：
unsigned_char不超过32个
int不超过64个
string不超过4个(char[64]数组)
==========================================================

====================游戏编程注意事项说明====================
栈区大小:1KB
游戏文件大小:<64KB
编程中如果使用递归等，请注意栈区的限制，避免堆栈溢出，导致游戏崩溃，甚至Arduino Player崩溃
============================================================
