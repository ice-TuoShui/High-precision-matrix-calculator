typedef struct stack 
{
    rn *a;//实数
    mat *A;//矩阵
    int typ; // 0实数、1矩阵
} stack;

long long Max_history=100000;
stack **his;
int tail_his;//当前历史记录个数

/**************************************************************************
函数名：历史记录初始化
描述:为数组his申请空间
**************************************************************************/
int init_his(){
    tail_his=0;
    his=(stack **)malloc(sizeof(stack *)*Max_history);
}

/**************************************************************************
函数名：删除历史记录
描述:数组his释放空间
**************************************************************************/
void free_his(){
    int i;
    for(i=0;i<tail_his;i++){
        if(his[i]->typ)
            freeall_mat(his[i]->A);
        else freeall_rn(his[i]->a);
        free(his[i]);
    }
    if(his)free(his);
    his=0;
    tail_his =0;
}

/**************************************************************************
函数名：复制stack
描述:输入stack a，b 将b的值赋给a.(a已申请空间)
**************************************************************************/
void copy_sta(stack *a,stack *b){
    a->typ=b->typ;
    if(a->typ){
        a->A=(mat*)malloc(sizeof(mat));
        copy_mat(b->A,a->A);

    }
    else {
        a->a=(rn*)malloc(sizeof(rn));
        copy_rn(a->a,b->a);
        }
}

/**************************************************************************
函数名：打印stack
描述:打印stack
**************************************************************************/
void print_sta(stack *a){
    if(a->typ)print_mat(a->A);
    else print_rn(a->a);
    printf("\n");
    
}

/**************************************************************************
函数名：打印stack到文件
描述:打印stack
**************************************************************************/
void fprint_sta(stack *a){
    if(a->typ)fprint_mat(a->A);
    else fprint_rn(a->a);
    fprintf(wp,"\n");
}