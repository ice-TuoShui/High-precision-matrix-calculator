typedef struct matrix
{
    int row; //行
    int col; //列
    rn ***m;
} mat;

int count; //统计行交换次数

/**************************************************************************
函数名：申请mat空间
描述:输入指针A,行列数，为A申请row*col空间,(A已申请mat空间)
**************************************************************************/
int build_mat(mat *A, int row, int col)
{
    A->m = (rn ***)malloc(sizeof(rn **) * row);
    A->row = row;
    A->col = col;
    if (!A->m)
        return 0;
    int i, j;
    for (i = 0; i < row; i++)
    {
        A->m[i] = (rn **)malloc(sizeof(rn *) * col);
        for (j = 0; j < col; j++)
        {
            A->m[i][j] = 0;
        }
        if (!A->m[i])
            return 0;
    }
    return 1;
}

/**************************************************************************
函数名：释放mat空间
描述:输入指针A,释放A->m的空间
**************************************************************************/
void free_mat(mat *A)
{
    if (!A)
        return;
    int i, j;
    for (i = 0; i < A->row; i++)
    {
        for (j = 0; j < A->col; j++)
            freeall_rn(A->m[i][j]);
        free(A->m[i]);
        A->m[i] = 0;
    }
    free(A->m);
    A->m = 0;
}

/**************************************************************************
函数名：释放mat空间
描述:输入指针A,释放A的空间
**************************************************************************/
void freeall_mat(mat *A)
{
    if (!A)
        return;
    int i, j;
    if (A->m)
    {
        for (i = 0; i < A->row; i++)
        {
            for (j = 0; j < A->col; j++)
                freeall_rn(A->m[i][j]);
            if (A->m[i])
                free(A->m[i]);
            A->m[i] = 0;
        }
        free(A->m);
    }
    A->m = 0;
    free(A);
    A = 0;
}

/**************************************************************************
函数名：构造零矩阵
描述:输入行row，列col。返回零矩阵
**************************************************************************/
mat *zero_mat(int row, int col)
{
    mat *A = (mat *)malloc(sizeof(mat));
    build_mat(A, row, col);
    rn *a = (rn *)malloc(sizeof(rn));
    as_rn(a, "0");
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            A->m[i][j] = (rn *)malloc(sizeof(rn));
            copy_rn(A->m[i][j], a);
        }
    }
    freeall_rn(a);
    return A;
}

/**************************************************************************
函数名：构造单位矩阵
描述:输入n。返回n阶单位矩阵
**************************************************************************/
mat *uni_mat(int n)
{
    mat *A = zero_mat(n, n);
    rn *a = (rn *)malloc(sizeof(rn));
    as_rn(a, "1");
    int i;
    for (i = 0; i < n; i++)
    {
        free_rn(A->m[i][i]);
        copy_rn(A->m[i][i], a);
    }
    freeall_rn(a);
    return A;
}

/**************************************************************************
函数名：判断零矩阵
描述:输入矩阵A。若A为零矩阵返回0，否则返回1
**************************************************************************/
int judzero_mat(mat *A)
{
    rn *a = (rn *)malloc(sizeof(rn));
    as_rn(a, "0");
    int i, j;
    for (i = 0; i < A->row; i++)
        for (j = 0; j < A->col; j++)
            if (cmp_rn(A->m[i][j], a))
            {
                freeall_rn(a);
                return 0;
            }
    freeall_rn(a);
    return 1;
}

/**************************************************************************
函数名：矩阵打印
描述:输入指针A,打印A
**************************************************************************/
void print_mat(mat *m)
{
    int i, j, n = m->row;
    for (i = 0; i < m->row; i++)
    {
        for (j = 0; j < m->col; j++)
        {
            print_rn(m->m[i][j]);
            if (i != m->row - 1 || j != m->col - 1)
                printf(",");
        }
        printf("\n");
    }
}

/**************************************************************************
函数名：矩阵打印到文件
描述:输入指针A,打印A
**************************************************************************/
void fprint_mat(mat *m)
{
    int i, j, n = m->row;
    for (i = 0; i < m->row; i++)
    {
        for (j = 0; j < m->col; j++)
        {
            fprint_rn(m->m[i][j]);
            if (i != m->row - 1 || j != m->col - 1)
                fprintf(wp, ",");
        }
        fprintf(wp, "\n");
    }
}

/**************************************************************************
函数名：矩阵行交换
描述:输入指针A,实数b,c,交换b+1，c+1行
**************************************************************************/
void swap_mat_row(mat *A, int b, int c)
{
    if (b >= A->row || c >= A->row)
        return;
    rn **n;
    n = A->m[b];
    A->m[b] = A->m[c];
    A->m[c] = n;
}

/**************************************************************************
函数名：矩阵行倍乘
描述:输入指针A,整型b,实数c,b+1行*c,(不销毁c)
**************************************************************************/
void nm_mat_row(mat *A, int b, rn *c)
{
    if (b >= A->row)
        return;
    rn *d = 0;
    int j;
    for (j = 0; j < A->col; j++)
    {
        d = (rn *)malloc(sizeof(rn));
        copy_rn(d, c);
        A->m[b][j] = mul_rn(A->m[b][j], d);
    }
}

/**************************************************************************
函数名：矩阵行倍加
描述:输入指针A,整型b，d,实数c,d+1行+b+1行*c，(不销毁c)
**************************************************************************/
void na_mat_row(mat *A, int b, rn *c, int d)
{
    if (b >= A->row || d >= A->row)
        return;
    rn *e = 0;
    rn *f = 0;
    int j;
    for (j = 0; j < A->col; j++)
    {
        e = (rn *)malloc(sizeof(rn));
        copy_rn(e, c);
        f = (rn *)malloc(sizeof(rn));
        copy_rn(f, A->m[b][j]);
        e = mul_rn(f, e);
        A->m[d][j] = add_rn(A->m[d][j], e);
    }
}

/**************************************************************************
函数名：矩阵列交换
描述:输入指针A,整型b,c. b+1列与c+1列交换
**************************************************************************/
void swap_mat_col(mat *A, int b, int c)
{
    if (b >= A->col || c >= A->col)
        return;
    int i;
    for (i = 0; i < A->row; i++)
    {
        swap_rn(&A->m[i][b], &A->m[i][c]);
    }
}

/**************************************************************************
函数名：矩阵列倍乘
描述:输入指针A,整型b,实数c. b+1列*c
**************************************************************************/
void nm_mat_col(mat *A, int b, rn *c)
{
    if (b >= A->col)
        return;
    rn *d = 0;
    int i;
    for (i = 0; i < A->row; i++)
    {
        d = (rn *)malloc(sizeof(rn));
        copy_rn(d, c);
        A->m[i][b] = mul_rn(A->m[i][b], d);
    }
}

/**************************************************************************
函数名：矩阵列数乘
描述:输入指针A,整型b,d 实数c. d+1列+b+1列*c
**************************************************************************/
void na_mat_col(mat *A, int b, rn *c, int d)
{
    if (b >= A->col || d >= A->col)
        return;
    rn *e = 0;
    rn *f = 0;
    int i;
    for (i = 0; i < A->row; i++)
    {
        e = (rn *)malloc(sizeof(rn));
        copy_rn(e, c);
        f = (rn *)malloc(sizeof(rn));
        copy_rn(f, A->m[i][b]);
        e = mul_rn(f, e);
        A->m[i][d] = add_rn(A->m[i][d], e);
    }
}

/**************************************************************************
函数名：矩阵复制
描述:输入指针a，b.将a的值赋给b,b已申请空间,b已清空m空间
**************************************************************************/
void copy_mat(mat *a, mat *b)
{
    build_mat(b, a->row, a->col);
    int i, j;
    for (i = 0; i < a->row; i++)
    {
        for (j = 0; j < a->col; j++)
        {
            b->m[i][j] = (rn *)malloc(sizeof(rn));
            copy_rn(b->m[i][j], a->m[i][j]);
        }
    }
}

/**************************************************************************
函数名：矩阵按列分割
描述:输入矩阵A，返回A的a+1列到b+1列（不销毁A），若范围错误，返回0；
**************************************************************************/
mat *division_mat_col(mat *A, int a, int b)
{
    if (a < 0 || a > A->col - 1)
        return 0;
    if (b < 0 || b > A->col - 1)
        return 0;
    mat *B = (mat *)malloc(sizeof(mat));
    build_mat(B, A->row, b - a + 1);
    int i, j;
    for (i = 0; i < A->row; i++)
    {
        for (j = 0; j < B->col; j++)
        {
            B->m[i][j] = (rn *)malloc(sizeof(rn));
            copy_rn(B->m[i][j], A->m[i][j + a]);
        }
    }
    return B;
}

/**************************************************************************
函数名：矩阵求逆
描述:输入指针方阵A，返回A的逆（销毁A）,若逆不可求，返回0
**************************************************************************/
mat *inv_mat(mat *m)
{
    if (m->row != m->col)
    {
        return NULL;
    }
    rn *temp = 0;
    rn *a = 0;
    rn *b = 0;
    int i, r, j;
    mat *tem = 0;
    mat *rst = 0;
    tem = uni_mat(m->row);
    rst = (mat *)malloc(sizeof(mat));
    copy_mat(m, rst);

    for (i = 0; i < m->row; i++)
    {
        r = i;
        for (j = i + 1; j < m->col; j++)
        {
            if (cmp_rn(rst->m[j][i], rst->m[r][i]) > 0)
            {
                r = j;
            }
        }
        if (r != i)
        {
            swap_mat_row(rst, i, r);
            swap_mat_row(tem, i, r);
        }
        if (judzero_rn(rst->m[i][i]))
        {
            return NULL;
        }
        for (j = i + 1; j < m->row; j++)
            if (!judzero_rn(rst->m[j][i]))
            {
                a = (rn *)malloc(sizeof(rn));
                b = (rn *)malloc(sizeof(rn));
                copy_rn(a, rst->m[j][i]);
                copy_rn(b, rst->m[i][i]);
                temp = div_rn(a, b);
                temp->sym = temp->sym ? 0 : 1;
                na_mat_row(rst, i, temp, j);
                na_mat_row(tem, i, temp, j);
                freeall_rn(temp);
            }
    }
    if (judzero_rn(rst->m[tem->row - 1][tem->col - 1]))
    {
        return NULL;
    }
    for (j = tem->col - 1; j >= 0; j--)
    {
        a = (rn *)malloc(sizeof(rn));
        b = (rn *)malloc(sizeof(rn));
        as_rn(a, "1");
        copy_rn(b, rst->m[j][j]);
        temp = div_rn(a, b);
        nm_mat_row(tem, j, temp);
        nm_mat_row(rst, j, temp);
        freeall_rn(temp);
    }
    for (i = tem->col - 1; i > 0; i--)
    {
        for (j = i; j > 0; j--)
            if (!judzero_rn(rst->m[j - 1][i]))
            {
                temp = (rn *)malloc(sizeof(rn));
                copy_rn(temp, rst->m[j - 1][i]);
                temp->sym = temp->sym ? 0 : 1;
                na_mat_row(tem, i, temp, j - 1);
                freeall_rn(temp);
            }
    }
    freeall_mat(rst);
    freeall_mat(m);
    return tem;
}

/**************************************************************************
函数名：矩阵加法
描述:输入矩阵A，B.返回A+B（销毁A,B）,如果不是同型矩阵，返回0
**************************************************************************/
mat *add_mat(mat *a, mat *b)
{
    if (a->row == b->row && a->col == b->col)
    {
        int i, j;
        mat *c;
        rn *d;
        rn *e;
        c = (mat *)malloc(sizeof(mat));
        build_mat(c, a->row, a->col);
        for (i = 0; i < a->row; i++)
            for (j = 0; j < a->col; j++)
            {
                d = (rn *)malloc(sizeof(rn));
                e = (rn *)malloc(sizeof(rn));
                copy_rn(d, a->m[i][j]);
                copy_rn(e, b->m[i][j]);
                c->m[i][j] = add_rn(e, d);
            }
        freeall_mat(a);
        freeall_mat(b);
        return c;
    }
    else
    {
        freeall_mat(a);
        freeall_mat(b);
        return NULL;
    }
}

/**************************************************************************
函数名：矩阵减法
描述:输入矩阵A，B.返回A-B（销毁A,B）
**************************************************************************/
mat *sub_mat(mat *a, mat *b)
{
    if (a->row == b->row && a->col == b->col)
    {
        int i, j;
        mat *c;
        rn *d;
        rn *e;
        c = (mat *)malloc(sizeof(mat));
        build_mat(c, a->row, a->col);
        for (i = 0; i < a->row; i++)
            for (j = 0; j < a->col; j++)
            {
                d = (rn *)malloc(sizeof(rn));
                e = (rn *)malloc(sizeof(rn));
                copy_rn(d, a->m[i][j]);
                copy_rn(e, b->m[i][j]);
                c->m[i][j] = sub_rn(d, e);
            }
        freeall_mat(a);
        freeall_mat(b);
        return c;
    }
    else
    {
        freeall_mat(a);
        freeall_mat(b);
        return NULL;
    }
}

/**************************************************************************
函数名：矩阵乘法
描述:输入矩阵A，B.返回A*B（销毁A,B），行列不同返回0
**************************************************************************/
mat *mul_mat(mat *a, mat *b)
{
    if (a->col == b->row)
    {
        int i, j, k;
        mat *c;
        rn *d;
        rn *e;
        c = zero_mat(a->row, b->col);
        for (i = 0; i < a->row; i++)
        {
            for (j = 0; j < b->col; j++)
            {
                for (k = 0; k < a->col; k++)
                {
                    d = (rn *)malloc(sizeof(rn));
                    e = (rn *)malloc(sizeof(rn));
                    copy_rn(d, a->m[i][k]);
                    copy_rn(e, b->m[k][j]);
                    e = mul_rn(d, e);
                    c->m[i][j] = add_rn(c->m[i][j], e);
                }
            }
        }
        freeall_mat(a);
        freeall_mat(b);
        return c;
    }
    else
    {
        freeall_mat(a);
        freeall_mat(b);
        return NULL;
    }
}

/**************************************************************************
函数名：矩阵转置
描述:输入矩阵m.返回m^T。（不销毁m）
**************************************************************************/
mat *T_mat(mat *m)
{
    mat *tem;
    tem = (mat *)malloc(sizeof(mat));
    build_mat(tem, m->col, m->row);
    int i, j;
    for (i = 0; i < m->row; i++)
    {
        for (j = 0; j < m->col; j++)
        {
            tem->m[j][i] = (rn *)malloc(sizeof(rn));
            copy_rn(tem->m[j][i], m->m[i][j]);
        }
    }
    return tem;
}

/**************************************************************************
函数名：化行阶梯型矩阵
描述:输入矩阵m.返回m的化行阶梯型矩阵（销毁A）
**************************************************************************/
mat *Ladder_mat_row(mat *m)
{
    rn *temp = 0;
    rn *a = 0;
    rn *b = 0;
    int i, r, j;
    mat *rst = 0;
    rst = (mat *)malloc(sizeof(mat));
    copy_mat(m, rst);
    for (i = 0; i < m->row; i++)
    {
        r = i;
        for (j = i + 1; j < m->col; j++)
        {
            if (cmp_rn(rst->m[j][i], rst->m[r][i]) > 0)
            {
                r = j;
            }
        }
        if (r != i)
        {
            swap_mat_row(rst, i, r);
            count++;
        }
        if (judzero_rn(rst->m[i][i]))
        {
            continue;
        }
        for (j = i + 1; j < m->row; j++)
            if (!judzero_rn(rst->m[j][i]))
            {
                a = (rn *)malloc(sizeof(rn));
                b = (rn *)malloc(sizeof(rn));
                copy_rn(a, rst->m[j][i]);
                copy_rn(b, rst->m[i][i]);
                temp = div_rn(a, b);
                temp->sym = temp->sym ? 0 : 1;
                na_mat_row(rst, i, temp, j);
                freeall_rn(temp);
            }
    }
    freeall_mat(m);
    return rst;
}

/**************************************************************************
函数名：矩阵行列式
描述:输入矩阵m.返回 |m| 。（不销毁m）若不可求，返回0
**************************************************************************/
rn *det_mat(mat *m)
{
    count = 0;
    if (m->row != m->col)
        return 0;
    pattern = 1;
    mat *tem = (mat *)malloc(sizeof(mat));
    copy_mat(m, tem);
    int i;
    rn *r = (rn *)malloc(sizeof(rn));
    rn *e;
    as_rn(r, "1");
    tem = Ladder_mat_row(tem);
    for (i = 0; i < tem->row; i++)
    {
        e = (rn *)malloc(sizeof(rn));
        copy_rn(e, tem->m[i][i]);
        r = mul_rn(r, e);
    }
    freeall_mat(tem);
    pattern = 0;
    if (count % 2)
        r->sym = r->sym ? 0 : 1;
    return r;
}

/**************************************************************************
函数名：矩阵快速幂
描述:输入矩阵m.实数b。返回 m^b 。（销毁m,b）
**************************************************************************/
mat *pow_mat(mat *m, rn *b)
{
    if (m->col != m->row || (judzero_mat(m) && !judzero_rn(b)))
    {
        freeall_rn(b);
        return m;
    }
    pattern = 1;
    fr = 1;
    rn *d = (rn *)malloc(sizeof(rn));
    rn *g = (rn *)malloc(sizeof(rn));
    rn *e;
    as_rn(d, "0.5");
    copy_rn(g, b);
    if (!judint_rn(g))
        g = int_rn(g);
    mat *result;
    mat *base;
    mat *f;
    base = (mat *)malloc(sizeof(mat));
    build_mat(base, m->row, m->col);
    copy_mat(m, base);
    result = uni_mat(m->col);
    while (!judzero_rn(g))
    {
        e = mul_rn(g, d);
        swap_rn(&e, &g);
        freeall_rn(e);
        if (!judint_rn(g))
        {
            f = (mat *)malloc(sizeof(mat));
            copy_mat(base, f);
            result = mul_mat(f, result);
            g = int_rn(g);
        }
        f = (mat *)malloc(sizeof(mat));
        copy_mat(base, f);
        base = mul_mat(base, f);
    }
    freeall_mat(base);
    freeall_mat(m);
    freeall_rn(b);
    freeall_rn(d);
    freeall_rn(g);
    fr = 0;
    pattern = 0;
    return result;
}

/**************************************************************************
函数名：求秩
描述:输入矩阵m.返回m的秩(不销毁m)
**************************************************************************/
rn *R_mat(mat *m)
{
    mat *tem;
    tem = (mat *)malloc(sizeof(mat));
    build_mat(tem, m->row, m->col);
    copy_mat(m, tem);
    tem = Ladder_mat_row(tem);
    int i, j;
    for (i = m->row - 1; i >= 0; i--)
        for (j = i; j < m->col; j++)
            if (!judzero2_rn(tem->m[i][j]))
            {
                free_mat(tem);
                rn *d = transf_int_rn(i+1);
                return d;
            }
    free_mat(tem);
    rn *d = transf_int_rn(i+1);
    return d;
}

/**************************************************************************
函数名：高斯消元
描述:输入增广矩阵A，返回方程的解（销毁A）,无解返回0
**************************************************************************/
mat *solve(mat *m)
{
    mat *A, *b, *X;
    A = division_mat_col(m, 0, m->col - 2);
    b = division_mat_col(m, m->col - 1, m->col - 1);
    rn *ra, *rt;
    ra = R_mat(A);
    rt = R_mat(m);
    int i = !cmp_rn(ra, rt);
    freeall_rn(ra);
    freeall_rn(rt);
    if (i)
    {
        freeall_mat(m);
        freeall_mat(A);
        freeall_mat(b);
        return NULL;
    }
    else
    {
        A = inv_mat(A);
        X = mul_mat(A, b);
        freeall_mat(m);
        return X;
    }
}

/**************************************************************************
函数名：实数乘矩阵
描述:输入矩阵A，输入实数a，返回矩阵 a*A,销毁a,A
**************************************************************************/
mat *mul_mat_rn(mat *A, rn *a)
{
    mat *B = (mat *)malloc(sizeof(mat));
    copy_mat(A, B);
    int i, j;
    rn *b;
    for (i = 0; i < A->row; i++)
    {
        for (j = 0; j < A->col; j++)
        {
            b = (rn *)malloc(sizeof(rn));
            copy_rn(b, a);
            B->m[i][j] = mul_rn(B->m[i][j], b);
        }
    }
    freeall_rn(a);
    freeall_mat(A);
    return B;
}

/**************************************************************************
函数名：矩阵除以实数
描述:输入矩阵A，输入实数a，返回矩阵 A/a,销毁a,A
**************************************************************************/
mat *div_mat_rn(mat *A, rn *a)
{
    mat *B = (mat *)malloc(sizeof(mat));
    copy_mat(A, B);
    int i, j;
    rn *b;
    for (i = 0; i < A->row; i++)
    {
        for (j = 0; j < A->col; j++)
        {
            b = (rn *)malloc(sizeof(rn));
            copy_rn(b, a);
            B->m[i][j] = div_rn(B->m[i][j], b);
        }
    }
    freeall_rn(a);
    freeall_mat(A);
    return B;
}
