====================��ϷROM������˵��====================
��ϷԴ�ļ�[.txt]���ض���ķ�ʽ����apgc.exe
Դ�ļ������Ҫ��һ�п��У�������Իس���β��
����������"a.apg"��Ϊ��ϷROM�ļ�
=========================================================

====================Arduino Player��SD������Ϸ�ļ�˵��====================
��Ϸ���ļ�����ʽ���棬�����ļ�������ʽ��Ϊ8.3��ʽ���Ҳ���Ϊ����
�ļ�������Ϊ��Ϸ��
"[��Ϸ��]"�ļ����ڰ���
�ļ���
1.��ϷROM:��"game.apg"����
2.��Ϸͼ�꣺��"icon.api"����
3.��Ϸ��������"help.txt"����
4.��Ϸ��¼����"save.aps"�������ҳ�ʼ����Ϊ�գ���Ϸ�л��Զ����м�¼
5.��Ϸ��飺��"name.txt"����
�ļ��У�
1.��Ϸ��ͼ����"map"�������ڰ���������Ϸ��ͼ����ͼ�ļ���"[����].map"�������������ִ�1��ʼ˳������
==========================================================================

====================��ϷԴ�ļ���ʽ˵��====================
��ע:[]�������� ...������� <>Ϊ����
<data segment>          //���ݶ�
    data declare...     //��������
<data ends>             //���ݶν���

<code segment>          //�����

[main] <proc>           //����
    code statement...   //����
[sign]<:>               //���
    code statement...   //����
    <ret>               //return
[main] <endp>           //��������

[fun1] <proc>           //ͬ��
    code statement...
    <ret>
[fun1] <endp>

...

<code ends>             //����ν���

<end> [main]            //����������
==========================================================

====================��ϷԴ�ļ��﷨˵��====================
ָ�
��ע:numΪ��ֵ(����Ϊ16λint),varΪ16λint����,signΪ���,procΪ������
������  ������          ע��
dtc     char    int     intת��Ϊunsigned char
ctd     int     char    unsigned charת��Ϊint
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
jmp     sign            ��ת��sign
je      sign            �����ת
jne     sign            �������ת
jg      sign            ������ת
jge     sign            ���ڵ�����ת
jl      sign            С����ת
jle     sign            С�ڵ�����ת
call    proc            ���ú���proc
ret                     ��������

ϵͳ�������ã�
������          �����б��ÿո����,ǰ����->������ֵ��
//ע��

btnPress        pin         ->pressed
//�жϰ�ť

fillScr         color_r     color_g     color_b
//ȫ�����

setColor        color_r     color_g     color_b
//������ɫ

drawPixel       point_x1    point_y1
//����

drawLine        point_x1    point_y1    point_x2    point_y2
//����

drawRect        point_x1    point_y1    point_x2    point_y2
//�����ɫ����

drawCircle      point_x1    point_y1    point_radius
//�����ɫԲ

fillRect        point_x1    point_y1    point_x2    point_y2
//������

fillCircle      point_x1    point_y1    point_radius
//���Բ

delay           time_delay
//��ʱ�ȴ�

showAscii       point_x1    point_y1    ascii       color_r     color_g     color_b     dot
//��ʾASCII

showEnglish     point_x1    point_y1    english     color_r     color_g     color_b     dot
//��ʾASCII����

showHZ          point_x1    point_y1    hz          color_r     color_g     color_b     dot
//��ʾ����

showChinese     point_x1    point_y1    chinese     color_r     color_g     color_b     dot
//��ʾ���ľ���

openMap         map_index
//�򿪵�ͼ�ļ�

mapSeek         map_offset
//�Ծ���λ���ƶ��ļ����

mapPosition     ->map_position
//��ȡ���������ֵ������

mapRead         ->map_read
//��ȡ�ļ�1byte,����ֵ������

mapSize         ->map_size
//��ȡ�ļ���С������ֵ������

closeMap
//�رյ�ͼ

getMapAmount    ->map_amount
//�����ͼ����

getMapFlag      map_x       map_y       ->map_xy_flag
//��ȡ��ͼ������Ϣ

setMapFlag      map_x       map_y       map_xy_flag
//�޸ĵ�ͼ������Ϣ

numPrintf       num         str1
//������ת��Ϊ�ַ���

setString       str1        index1      ascii
//�޸��ַ����е�һ���ַ�

strcpy          str1        str2
//�ַ�������

strcat          str1        str2
//�ַ�������

strcmp          str1        str2        ->str_cmp
//�ַ����Ƚϣ����������ֵ������

strlen          str1        ->str_len
//���ַ������ȸ�ֵ������

updateSave      all         win         lose
//������Ϸ��¼

updateMap       map_index
//��Ϸ����

exitGame
//�˳���Ϸ
==========================================================

====================��ϷԴ�ļ�����˵��====================
��ע��int���ͱ�����Ϊ16λ
ϵͳĬ��ȫ�ֱ���������
int pin                 �жϵİ�ť����
int pressed             ��ť�жϽ��

int color_r             \
int color_g              >��ɫ����
int color_b             /

int point_x1            \
int point_y1             \
int point_x2              >��ͼ�������
int point_y2             /
int point_radius        /

int time_delay          ��ʱʱ��

unsigned char ascii     \
char* english            \
char* hz                 /��Ҫ��ʾ����Ϣ
char* chinese           /
int dot                 �ֺ�

int map_index           ��ͼ���
int map_offset          ��ͼ�ļ�ƫ��
int map_position        ��ǰ��ͼ�ļ�ƫ��
unsigned char map_read  ��ȡ�ĵ�ͼ�ļ�����
int map_size            ��ͼ�ļ���С
int map_amount          ��ͼ����

unsigned char map_flag[22][17]
                        ��ͼ��Ϣ��¼
int map_x               ��ͼx����
int map_y               ��ͼy����
unsigned char map_xy_flag
                        ��ͼ��Ϣ

int num                 ����
char* str1              \
char* str2              /�ַ���
int str_cmp             �ַ����ȽϽ��
int str_len             �ַ�������

int all                 \
int win                  >��Ϸ��¼����
int lose                /

int index1              \
int index2              /��ʱ�洢����ƫ��

��Ϸ�Խ�ȫ�ֱ���˵����
��Ҫ�Խ�ȫ�ֱ�������data segment�н�����������ʽΪ��
[������]    [��������][[����Ԫ�ظ���]]        [��ֵ]
�������Ͱ���:unsigned_char, int, string
��ע��
unsigned_char������32��
int������64��
string������4��(char[64]����)
==========================================================

====================��Ϸ���ע������˵��====================
ջ����С:1KB
��Ϸ�ļ���С:<64KB
��������ʹ�õݹ�ȣ���ע��ջ�������ƣ������ջ�����������Ϸ����������Arduino Player����
============================================================
