FILE *rp;
FILE *wp;
int reader=0;//0 用户直接写入,1 读取文件
int writer=0;//0 输出屏幕,1 写入文件

/**************************************************************************
函数名：读取字符
描述:根据转态选择从文件or用户直接写入，来读取字符
**************************************************************************/
char gc()
{
        char a;
        if(!reader)
        a=getchar();
        else 
        fscanf(rp,"%c",&a);
        return a;

}


