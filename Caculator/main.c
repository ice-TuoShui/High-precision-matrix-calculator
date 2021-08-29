#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.c"
#include "function.c"
#include "realnumber.c"
#include "matrix.c"
#include "history.c"
#include "recognize.c"

void change();

int main()
{
    init_his();
    char s[4];
    int ii;
    printf("高精度计算器 !!! rua !!!\n");
    printf("---本程序使用 65001（utf-8） 编码 \n");//乱码问题，请在终端输入 chcp 65001。再打开本程序
    while (1)
    {
        char choice[100];
        printf("\n********************************************\n");
        printf("1.计算算式（支持实数与矩阵杂糅）:\n");
        printf("2.计算矩阵行列式:\n");
        printf("3.计算矩阵的秩:\n");
        printf("4.求解多元一次方程组:\n");
        printf("5.修改配置:\n");
        printf("6.输出所有历史:\n");
        printf("7.清空所有历史:\n");
        printf("8.退出:\n");
        printf("9.强制退出:\n");
        printf("输入文件为\"in.txt\",输出文件为\"out.txt\"\n");
        printf("********************************************\n");
        printf("输入您的选择: ");
        scanf("%s", choice);
        switch (choice[0])
        {
        case '1':
            rp = fopen("in.txt", "r");
            wp = fopen("out.txt", "w+");
            if (!recognize())
            {
                printf("\n果咩(｡í _ ì｡)！实在是识别不出来你的输入.\n");
            }
            else
            {
                printf("\n计算结果已记录，本程序会自动识别'a'这个字母作为这次的计算结果的！\n");
            }
            fclose(rp);
            fclose(wp);
            break;
        case '2':
            rp = fopen("in.txt", "r");
            wp = fopen("out.txt", "w+");
            printf("请输入一个矩阵:\n");
            if (!det())
            {
                printf("\n果咩(｡í _ ì｡)！实在是识别不出来你的输入.\n");
            }
            else
            {
                printf("\n计算结果已记录，结果可用于 \"1.计算算式\" 当中哦!\n");
            }
            fclose(rp);
            fclose(wp);
            break;
        case '3':
            rp = fopen("in.txt", "r");
            wp = fopen("out.txt", "w+");
            printf("请输入一个矩阵:\n");
            if (!R())
            {
                printf("\n果咩(｡í _ ì｡)！实在是识别不出来你的输入.\n");
            }
            else
            {
                printf("\n计算结果已记录，结果可用于 \"1.计算算式\" 当中哦!\n");
            }
            fclose(rp);
            fclose(wp);
            break;
        case '4':
            /*
            rp = fopen("in.txt", "r");
            wp = fopen("out.txt", "w+");
            printf("请输入一个线性方程组矩阵:\n");
            if (!equation())
            {
                printf("\n果咩(｡í _ ì｡)！实在是识别不出来你的输入.\n");
            }
            else
            {
                printf("\n计算结果已记录，结果可用于 \"1.计算算式\" 当中哦!\n");
            }
            fclose(rp);
            fclose(wp);
            break;
            */
            printf("本功能还在调试阶段！对不起啦！先使用其他功能吧！\n");
            break;
        case '5':
            printf("当前配置：\n");
            printf("1.精度(保留小数点后的位数):%d\n", Acc);
            printf("2.精度保留(开启 1 关闭 0):%d\n", Acc_f);
            printf("3.模式选择(性能模式 1 精确模式 0):%d\n", pattern);
            printf("4.最大符号个数:%lld\n", Max_char);
            printf("5.最大矩阵中数字个数:%lld\n", Max_number);
            printf("6.最大实数长度:%lld\n", Max_rn);
            printf("7.最大历史记录个数:%lld\n", Max_history);
            printf("8.读入方式(0 用户直接写入,1 读取文件):%d\n", reader);
            printf("9.写出方式(0 输出屏幕,1 写入文件):%d\n", writer);
            printf("0.返回\n");
            printf("选择你要修改的配置: ");
            change();
            break;
        case '6':
            wp = fopen("out.txt", "w+");
            if (!writer)
                for (ii = 0; ii < tail_his; ii++)
                {
                    printf("%d: ", ii + 1);
                    print_sta(his[ii]);
                }
            if (writer)
            {
                for (ii = 0; ii < tail_his; ii++)
                {
                    fprintf(wp, "%d: ", ii + 1);
                    fprint_sta(his[ii]);
                }
                printf("已经写入文件了哦！\n");
            }
            if (!tail_his)
                printf("暂无历史记录哦!\n");
            fclose(wp);
            break;
        case '7':
            free_his();
            printf("历史记录已清空了哦!\n");
            break;
        case '8':
            free_his();
            return 0;
        default:
            printf("没有别的选项啦！\n");
        };
    }
    return 0;
}

void change()
{
    char choice[100];
    long long sb;
    int fff = 0;
    while (1)
    {
        scanf("%s", choice);
        switch (choice[0])
        {
        case '1':
            printf("输入Acc修改值(应为大等于0的整数)：");
            scanf("%lld", &sb);
            if (sb < 0)
            {
                printf("Acc的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Acc = sb;
            }
            break;
        case '2':
            printf("输入Acc_f修改值(应为0或1)：");
            scanf("%lld", &sb);
            if (sb != 1 && sb != 0)
            {
                printf("Acc_f的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Acc_f = sb;
            }
            break;
        case '3':
            printf("输入pattern修改值(应为0或1)：");
            scanf("%lld", &sb);
            if (sb != 1 && sb != 0)
            {
                printf("pattern的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                pattern = sb;
            }
            break;
        case '4':
            printf("输入Max_char修改值(应为不小于10的正整数)：");
            scanf("%lld", &sb);
            if (sb < 10)
            {
                printf("Max_char的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Max_char = sb;
            }
            break;
        case '5':
            printf("输入Max_number修改值(应为不小于10的正整数)：");
            scanf("%lld", &sb);
            if (sb < 10)
            {
                printf("Max_number的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Max_number = sb;
            }
            break;
        case '6':
            printf("输入Max_rn修改值(应为不小于10的正整数)：");
            scanf("%lld", &sb);
            if (sb < 10)
            {
                printf("Max_rn的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Max_rn = sb;
            }
            break;
        case '7':
            printf("输入Max_history修改值(应为不小于10的正整数)：");
            scanf("%lld", &sb);
            if (sb < 10)
            {
                printf("Max_history的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                Max_history = sb;
            }
            break;
        case '8':
            printf("输入reader修改值(应为0或1)：");
            scanf("%lld", &sb);
            if (sb != 1 && sb != 0)
            {
                printf("reader的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                reader = sb;
            }
            break;
        case '9':
            printf("输入writer修改值(应为0或1)：");
            scanf("%lld", &sb);
            if (sb != 1 && sb != 0)
            {
                printf("writer的范围错误，修改失败！\n");
            }
            else
            {
                printf("修改成功啦！\n");
                writer = sb;
            }
            break;
        default:
            fff = 1;
        }
        if (fff)
            break;
        else
            printf("选择你要修改的配置: ");
    }
}
