%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #define true 1
    #define false 0
    #define bool int
    
    #define TXMAX 100 //符号表容量
    #define AL 10 //标识符最长长度
    #define LEVMAX 5 //嵌套深度
    #define AMAX 2047 //地址上界
    #define STACKSIZE 500 //栈元素上界
    #define CXMAX 200 //最多的pcode条数

    enum object {
        constant, 
        variable, 
        procedure
    };

    enum vartype {
        inttype,
        booltype,
        chartype
    };

    /* 符号表结构 */
    struct table1 {
        char name[AL]; /* 名字 */
        enum object kind;  /* 类型：const，var，procedure */
        int val; /* 数值，仅const使用 */
        int level;
        int adr; /* 地址，仅const不使用 */
        int size;
        enum vartype type; /* var的具体类型 */
    } table[TXMAX];

    enum fct {lit, opr, lod, sto, cal, ini, jmp, jpc, jpe, ext, blo, fre};

    struct instruction {
        enum fct f;
        int l;
        int a;
    } code[CXMAX];

    int tx; //符号表当前尾指针
    int cx; // pcode索引
    int lev; // 层次记录
    int leveltable[5]; // 嵌套索引表
    char id[AL];
    int num;
    bool listswitch;   /* 显示虚拟机代码与否 */
    bool tableswitch;  /* 显示符号表与否 */
    bool stackswitch;  /* 显示栈信息与否 */

    FILE* fin;      /* 输入源文件 */
    FILE* ftable;   /* 输出符号表 */
    FILE* fcode;    /* 输出虚拟机代码 */
    FILE* foutput;  /* 输出出错示意（如有错） */
    FILE* fresult;  /* 输出执行结果 */
    FILE* fstack;   /* 输出每一步栈的结果 */
    int err; // 程序中的错误个数
    extern int line;

    char varType[10]; //判断当前id是整形还是布尔类型还是字符类型

    void init();
    void enter(enum vartype t, enum object k);
    int position(char* s);
    void setdx(int n);
    void gen(enum fct x, int y, int z);
    void listall();
    void displaytable();
    void interpret();
    int base(int l, int *s, int b);
    
    int yylex();
    void yyerror(const char *s);
    void redirectInput(FILE *fin);

    #define YYERROR_VERBOSE 1
%}

%union {
    char *ident;
    int number;
}

%token PLUS MINUS TIMES SLASH LES LEQ GTR GEQ EQL NEQ BECOMES OR AND NOT
%token SEMICOLON LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA
%token IF ELSE WHILE WRITE READ INT BOOL CONST CHAR
%token SELFADD SELFMIUNS REPEAT UNTIL XOR MOD ODD TRUE FALSE
%token CALL DO FUNC EXIT FOR
%token <ident> IDENT
%token <number> NUMBER
%token <ident> CHARACTER

%type <number> ident
%type <number> vardecls vardecl varlist vardef
%type <number> get_table_addr get_code_addr
%type <number> elsestm
%type <number> for2
%type <number> term factor expression idornum

%nonassoc IFX
%nonassoc ELSE

%%

program:
    mainblock
    ;

mainblock:
    LBRACE
    {
        $<number>$ = cx;
        gen(jmp, 0, 0);
    }
    constdecl vardecls
    {
        setdx($4);
    }    
    procdecls
    {
        code[$<number>2].a = cx;
        gen(ini, 0, $4 + 3);
        printf("mainblock:\n");
        displaytable();
    }
    statements
    RBRACE
    {
        gen(opr, 0, 0);
    }
	;

blockstm:
    LBRACE
    inc_level
    {
        leveltable[lev] = tx;
        gen(blo, 0, 0);
    }
    constdecl vardecls
    {
        setdx($5);
        gen(ini, 0, $5 + 3);
        printf("blockstm:\n");
        displaytable();
    }
    statements
    {
        gen(fre, 0, 0);
    }
    RBRACE
    {
        tx = leveltable[lev];
    }
    dec_level;
    ;

/*  常量声明 */
constdecl: 
    CONST constlist SEMICOLON
    | CONST constlist  
    {
        yyerror("Miss SEMICOLON");  //错误处理，常量声明缺少结尾分号
    }
    |
    ;

/* 常量声明列表 */
constlist: 
    constdef 
    | constlist COMMA constdef 
    ;

/* 单个常量 */
constdef:
    IDENT BECOMES NUMBER
    {        
        strcpy(id, $1);   
        num = $3;
        enter(inttype, constant);
    }
    ;

vardecls:
    vardecls vardecl 
    {
        $$ = $1 + $2;
    }
    |
    {
        $$ = 0;
    }
    ;

/*  变量声明 */
vardecl: 
    type varlist SEMICOLON
    {
        $$ = $2;         /* 传递变量声明的个数 */
    }
    | type varlist  
    {
        $$ = $2;         
        yyerror("Miss SEMICOLON");  //错误处理，变量声明缺少结尾分号
    }
    ;

type:
    INT
    {
        strcpy(varType, "int");
    }
    | BOOL
    {
        strcpy(varType, "bool");
    }
    | CHAR
    {
        strcpy(varType, "char");
    }
    ;

/* 变量声明列表 */
varlist: 
    vardef 
    {
        $$ = $1;
    }
    | varlist COMMA vardef 
    {
        $$ = $1 + $3;  /* 变量声明的个数相加 */
    }
    | error {/*错误处理*/} 
    ;

/* 单个变量 */
vardef: 
    IDENT 
    {
        strcpy(id, $1);
        if (!strcmp(varType, "int")) 
            enter(inttype, variable); 
        else if(!strcmp(varType, "bool"))
            enter(booltype, variable);
        else if(!strcmp(varType, "char"))
            enter(chartype, variable);
        $$ = 1;
    }
    ;

/* 函数 */
procdecls: 
    procdecls procdecl
    |
    ;

procdecl:
    FUNC IDENT LPAREN RPAREN 
    {
        strcpy(id, $2);
        enter(-1, procedure);
    }
    procbody
    ;

procbody:
    LBRACE
    inc_level
    {
        leveltable[lev] = tx;
    }
    get_table_addr
    constdecl vardecls
    {
        setdx($6);
        table[$4].adr = cx;
        table[$4].size = $6 + 3;
        gen(ini, 0, $6 + 3);
        printf("procbody:\n");        
        displaytable();
    }
    statements
    {
        gen(opr, 0, 0);
    }
    RBRACE
    {
        tx = leveltable[lev];
    }
    dec_level;
    ;

/*  语句 */
statements:
    statements statement
    |
    ;

statement:
    assignmentstm
    | readstm 
    | writestm 
    | exitstm
    | selfaddminus SEMICOLON
    | ifstm
    | whilestm
    | blockstm
    | callstm
    | dowhilestm
    | repeatstm
    | forstm
    | error {/*错误处理*/}
    ;

/*  赋值语句 */
assignmentstm: 
    ident BECOMES expression SEMICOLON
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == inttype)
            gen(sto, lev - table[$1].level, table[$1].adr);
        else
            yyerror("Symbol should be a variable and type should be int");
    }
    | ident BECOMES trueorfalse SEMICOLON
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == booltype) 
            gen(sto, lev - table[$1].level, table[$1].adr);
        else
            yyerror("Symbol should be a variable and type should be bool");
    }
    | ident BECOMES character SEMICOLON
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == variable && table[$1].type == chartype) 
            gen(sto, lev - table[$1].level, table[$1].adr);
        else
            yyerror("Symbol should be a variable and type should be char");
    } 
    ;

/* 读语句 */
readstm: 
    READ LPAREN readvarlist RPAREN SEMICOLON
    ;

/* 一个或多个读语句的变量 */
readvarlist: 
    readvar 
    | readvarlist COMMA readvar 
    ;

/* 读语句变量 */
readvar: 
    ident 
    {
        if (table[$1].kind == variable && table[$1].type == inttype) {
            gen(opr, 0, 16);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
        else if (table[$1].kind == variable && table[$1].type == chartype) {
            gen(opr, 0, 17);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
        else {
            yyerror("Can only read int or char variable");
        }
    }
    ;

/* 写语句 */
writestm: 
    WRITE LPAREN writeexplist RPAREN SEMICOLON
    ; 

/* 一个或多个写语句的表达式 */
writeexplist:
    expression
    {
        if ($1 == 1) {  //字符
            gen(opr, 0, 23);
            gen(opr, 0, 15);
        }
        else {  // 整数
            gen(opr, 0, 14);
            gen(opr, 0, 15);
        }
    }
    | writeexplist COMMA expression
    {
        if ($3 == 1) {  //　字符
            gen(opr, 0, 23);
            gen(opr, 0, 15);
        }
        else {  // 整数
            gen(opr, 0, 14);
            gen(opr, 0, 15);
        }
    }
    ;

exitstm:  
    EXIT SEMICOLON
    {
        gen(ext, 0, 0);
    }
    ;

/*  自增自减语句 */
selfaddminus: 
    ident SELFADD 
    { 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == constant) 
            yyerror("Constant cannot selfadd");
        else if (table[$1].kind == variable && table[$1].type != inttype) 
            yyerror("Only int variable can selfadd");
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            gen(lod, lev - table[$1].level, table[$1].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 2);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
    }
    | ident SELFMIUNS 
    {
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == constant) 
            yyerror("Constant cannot selfminus");
        else if (table[$1].kind == variable && table[$1].type != inttype) 
            yyerror("Only int variable can selfminus");
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            gen(lod, lev - table[$1].level, table[$1].adr);
            gen(lit, 0, 1);
            gen(opr, 0, 3);
            gen(sto, lev - table[$1].level, table[$1].adr);
        }
    }
    ;

/* 条件语句 */
ifstm:
    IF LPAREN bexpr RPAREN get_code_addr
    {
        gen(jpc, 0, 0);
    }
    statement elsestm 
    {
        code[$5].a = $8; //回填，不满足条件时跳到哪里
    }
    ;

elsestm:
    ELSE get_code_addr 
    {
        gen(jmp, 0, 0); //满足if条件的直接jmp走
    } 
    statement 
    {
        $$ = $2 + 1; //jmp的后一条指令位置
        code[$2].a = cx; //回填，满足if条件的跳到哪里
    }
    | %prec IFX
    {
        $$ = cx;
    }
    ;

whilestm:
    WHILE get_code_addr LPAREN bexpr RPAREN get_code_addr
    {
        gen(jpc, 0, 0);
    }
    statement
    {
        gen(jmp, 0, $2);
        code[$6].a = cx;
    }
    ;

dowhilestm:
    DO get_code_addr statement get_code_addr
    WHILE LPAREN bexpr get_code_addr
    {
        gen(jpe, 0, $2);
    }
    RPAREN SEMICOLON
    ;      

repeatstm:
    REPEAT get_code_addr statement get_code_addr
    UNTIL LPAREN bexpr get_code_addr
    {
        gen(jpc, 0, $2);
    }
    RPAREN SEMICOLON
    ;

forstm:
    FOR LPAREN for1 get_code_addr for2 
    {
        if ($5 == 1)
            gen(lit, 0, 1);
    }
    SEMICOLON get_code_addr
    {
        gen(jpe, 0, 0);
        gen(jmp, 0, 0);
    } 
    get_code_addr for3 RPAREN
    {
        gen(jmp, 0, $4);
    } 
    get_code_addr
    statement
    {
        gen(jmp, 0, $10);
        code[$8].a = $14;
        code[$8 + 1].a = cx;
    }
    ;

for1:
    assignmentstm
    | SEMICOLON
    ;

for2:
    bexpr
    {
        $$ = 0; 
    }
    |
    {
        $$ = 1; //无条件
    }
    ;

for3:
    selfaddminus
    |
    ;

callstm:
    CALL ident SEMICOLON
    {
        if ($2 == 0)
            yyerror("Call symbol does not exist");
        else if (table[$2].kind != procedure)
            yyerror("Call symbol should be a procedure");
        else
            gen(cal, lev - table[$2].level, table[$2].adr);    
    }
    ;

/* 布尔表达式 */
bexpr:
    bexpr OR bterm 
    {
        gen(opr, 0, 22);
    }
    | bterm
    ;

bterm:
    bterm AND bfactor 
    {
        gen(opr, 0, 21);
    }
    | bfactor
    ;

bfactor:
    ident 
    { 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[$1].kind == constant)
            gen(lit, 0, table[$1].val);
        else if (table[$1].kind == variable)
            gen(lod, lev - table[$1].level, table[$1].adr);
    }   
    | trueorfalse
    | NOT bfactor 
    {
        gen(opr, 0, 20);
    }
    | ODD idornum 
    {
        gen(opr, 0, 6);
    }
    | LPAREN bexpr RPAREN 
    | rel
    ;

rel:
    idornum EQL expression 
    {
        gen(opr, 0, 8);
    }
    | idornum NEQ expression 
    {
        gen(opr, 0, 9);
    }
    | idornum LES expression 
    {
        gen(opr, 0, 10);
    }
    | idornum LEQ expression 
    {
        gen(opr, 0, 13);
    }
    | idornum GTR expression 
    {
        gen(opr, 0, 12);
    }
    | idornum GEQ expression 
    {
        gen(opr, 0, 11);
    }
    ;

idornum:
    ident
    { 
        if ($1 == 0)
            yyerror("Symbol does not exist");
        else if (table[$1].kind == procedure)
            yyerror("Symbol should not be a procedure");
        else if (table[$1].kind == constant) {
            $$ = 0;
            gen(lit, 0, table[$1].val);
        }
        else if (table[$1].kind == variable && table[$1].type == inttype) {
            $$ = 0; 
            gen(lod, lev - table[$1].level, table[$1].adr);
        }
        else if (table[$1].kind == variable && table[$1].type == booltype) {
            $$ = 0; 
            gen(lod, lev - table[$1].level, table[$1].adr);
        }
        else if (table[$1].kind == variable && table[$1].type == chartype) {
            $$ = 1;
            gen(lod, lev - table[$1].level, table[$1].adr);
        }
    }   
    | NUMBER 
    {
        $$ = 0;
        gen(lit, 0, $1);
    }
    ;

trueorfalse:
    TRUE
    {
        gen(lit, 0, 1);
    }
    |
    FALSE
    {
        gen(lit, 0, 0);
    }
    ;

character:
    CHARACTER
    {
        gen(lit, 0, $1[1]);
    }
    ;

/* 算术表达式 */
expression: 
    PLUS term 
    {
        $$ = 0;
    }
    | MINUS term
    {
        $$ = 0;
        gen(opr, 0, 1);
    }
    | term    
    {
        $$ = $1;
    }         
    | expression PLUS term
    {
        $$ = 0;
        gen(opr, 0, 2);
    }
    | expression MINUS term
    {
        $$ = 0;
        gen(opr, 0, 3);
    }
    ;

/* 项 */
term: 
    factor
    {
        $$ = $1;
    }
    | term TIMES factor
    {
        $$ = 0;
        gen(opr, 0, 4);
    }
    | term SLASH factor
    {
        $$ = 0;
        gen(opr, 0, 5);
    }  
    | term MOD factor
    {
        $$ = 0;
        gen(opr, 0, 18);
    }
    | term XOR factor
    {
        $$ = 0;
        gen(opr, 0, 19);
    }
    ;

/* 因子 */
factor: 
    idornum
    {
        $$ = $1;
    }
    | LPAREN expression RPAREN 
    {
        $$ = 0;
    }
    ;

ident: 
    IDENT 
    {
        $$ = position($1); 
    }
    ;

get_table_addr:
    {
        $$ = tx;
    } 
    ;

get_code_addr:
    {
        $$ = cx;
    }
    ;

inc_level:
    {
        lev++;               
        if (lev > LEVMAX)   /* 嵌套层数过多 */
            yyerror("Lev is too big");    
    }
    ;

dec_level:
    {
        lev--;
    }
    ;

%%

void yyerror(const char *s) {
    err++;
    printf("%s in line %d\n", s, line);
    fprintf(foutput, "%s in line %d\n", s, line);
}

void init() {
    tx = 0;
    cx = 0;
    lev = 0;   
    leveltable[0] = 0;
    num = 0;
    err = 0;
}

/* 在符号表中加入一项 */
void enter(enum vartype t, enum object k) {
    tx = tx + 1;
    strcpy(table[tx].name, id);
    table[tx].kind = k;
    switch(k) {
    case constant:
        table[tx].val = num;
        break;
    case variable:
        table[tx].level = lev;
        table[tx].type = t;
        break;
    case procedure:
        table[tx].level = lev;
        break;
    }
}

/* 查找标识符在符号表中的位置 */
int position(char id[]) {
    int i;
    strcpy(table[0].name, id);
    i = tx;
    while (strcmp(table[i].name,id) != 0) {
        i--;
    }
    return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        table[tx - i + 1].adr = n - i + 3;
    }
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z) {
    if (cx >= CXMAX) {
        printf("Program is too long!\n"); /* 生成的虚拟机代码程序过长 */
        exit(1);
    }
    if (z >= AMAX) {
        printf("Displacement address is too big!\n"); /* 地址偏移越界 */
        exit(1);
    }
    code[cx].f = x;
    code[cx].l = y;
    code[cx].a = z;
    cx++;
}

/* 输出所有目标代码  */
void listall() {
    int i;
    char name[][5] = {
        {"lit"}, {"opr"}, {"lod"}, {"sto"}, {"cal"}, {"int"}, 
        {"jmp"}, {"jpc"}, {"jpe"}, {"ext"}, {"blo"}, {"fre"}
    };
    if (listswitch) {
        for (i = 0; i < cx; i++) {
            printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
            fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
        }
        printf("\n");
    }
}

/* 输出符号表 */
void displaytable() {
    int i;
    if (tableswitch) {
        for (i = 1; i <= tx; i++) {
            switch (table[i].kind)
            {
            case constant:
                printf("    %d const %s ", i, table[i].name);
                printf("val=%d\n", table[i].val);
                fprintf(ftable, "    %d const %s ", i, table[i].name);
                fprintf(ftable, "val=%d\n", table[i].val);
                break;
            case variable:
                printf("    %d var   %s ", i, table[i].name);
                printf("lev=%d addr=%d type=%d \n", table[i].level, table[i].adr,  table[i].type);
                fprintf(ftable, "    %d var   %s ", i, table[i].name);
                fprintf(ftable, "lev=%d addr=%d\n", table[i].level, table[i].adr);
                break;
            case procedure:
                printf("    %d proc  %s ", i, table[i].name);
                printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                fprintf(ftable,"    %d proc  %s ", i, table[i].name);
                fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
                break;
            }
        }
        printf("\n");
        fprintf(ftable, "\n");
    }
}

void printstack(int t, int p, int *s) {
    int i;
    if (stackswitch) {
        fprintf(fstack, "pcode %2d: |", p);
        for (i = 1; i <= t; i++)
            fprintf(fstack, " %2d |", s[i]);
        fprintf(fstack, "%s", "\n");
    }
}

/* 解释程序 */
void interpret() {
	int p = 0; /* 指令指针 */
    int b = 1; /* 指令基址 */
    int t = 0; /* 栈顶指针 */
    struct instruction i; /* 存放当前指令 */
    int s[STACKSIZE]; /* 栈 */

	printf("Start CX interpret\n");
 	fprintf(fresult,"Start CX interpret\n");
	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	s[3] = 0;
	do {
		i = code[p];  /* 读当前指令 */
        p = p + 1;
        switch (i.f)
        {
        case lit: /* 将常量a的值取到栈顶 */
            t = t + 1;
            s[t] = i.a;
            printstack(t, p, s);
            break;
        case opr: /* 数学、逻辑运算 */
            switch(i.a) {
            case 0:  /* 函数调用结束后返回 */
                t = b - 1;
                p = s[t + 3];
                b = s[t + 2];
                break;
            case 1: /* 栈顶元素取反 */
                s[t] = -s[t];
                break;
            case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
                t = t - 1;
                s[t] = s[t] + s[t + 1];
                break;
            case 3:/* 次栈顶项减去栈顶项 */
                t = t - 1;
                s[t] = s[t] - s[t + 1];
                break;
            case 4:/* 次栈顶项乘以栈顶项 */
                t = t - 1;
                s[t] = s[t] * s[t + 1];
                break;
            case 5:/* 次栈顶项除以栈顶项 */
                t = t - 1;
                s[t] = s[t] / s[t + 1];
                break;
            case 6:/* 栈顶元素的奇偶判断 */
                s[t] = s[t] % 2;
                break;
            case 8:/* 次栈顶项与栈顶项是否相等 */
                t = t - 1;
                s[t] = (s[t] == s[t + 1]);
                break;
            case 9:/* 次栈顶项与栈顶项是否不等 */
                t = t - 1;
                s[t] = (s[t] != s[t + 1]);
                break;
            case 10:/* 次栈顶项是否小于栈顶项 */
                t = t - 1;
                s[t] = (s[t] < s[t + 1]);
                break;
            case 11:/* 次栈顶项是否大于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] >= s[t + 1]);
                break;
            case 12:/* 次栈顶项是否大于栈顶项 */
                t = t - 1;
                s[t] = (s[t] > s[t + 1]);
                break;
            case 13: /* 次栈顶项是否小于等于栈顶项 */
                t = t - 1;
                s[t] = (s[t] <= s[t + 1]);
                break;
            case 14:/* 栈顶值输出 */
                printf("%d", s[t]);
                fprintf(fresult, "%d", s[t]);
                t = t - 1;
                break;
            case 15:/* 输出换行符 */
                printf("\n");
                fprintf(fresult,"\n");
                break;
            case 16:/* 读入一个数置于栈顶 */
                t = t + 1;
                printf("input a number: ");
                fprintf(fresult, "input a number: ");
                scanf("%d", &(s[t]));
                getchar();
                fprintf(fresult, "%d\n", s[t]);           
                break;
            case 17:/* 读入一个字符置于栈顶 */
                {
                    char ch;
                    t = t + 1;
                    printf("input a character: ");
                    fprintf(fresult, "input a character: ");
                    scanf("%c", &ch);
                    getchar();
                    s[t] = ch;
                    fprintf(fresult, "%c\n", s[t]);           
                    break;
                }
                
            case 18:/* 次栈顶项求余栈顶项 */ 
                t = t - 1;
                s[t] = s[t] % s[t + 1];
                break;
            case 19:/* 次栈顶项异或栈顶项 */
                t = t - 1;
                s[t] = s[t] ^ s[t + 1];
                break;
            case 20:/* 栈顶的值取not */
                s[t] = !s[t];
                break;
            case 21:/* 次栈顶项and栈顶项 */
                t = t - 1;
                s[t] = s[t] && s[t + 1];
                break;
            case 22:/* 次栈顶项or栈顶项 */
                t = t - 1;
                s[t] = s[t] || s[t + 1];
                break;
            case 23:/* 栈顶字符输出 */
                printf("%c", s[t]);
                fprintf(fresult, "%c", s[t]);
                t = t - 1;
                break;
            }
            printstack(t, p, s);
            break;	
        case lod: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
            t = t + 1;
            s[t] = s[base(i.l, s, b) + i.a];
            printstack(t, p, s);            
            break;
        case sto: /* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
            s[base(i.l, s, b) + i.a] = s[t];
            t = t - 1;
            printstack(t, p, s);
            break;
        case cal: /* 调用子过程 */
            s[t + 1] = base(i.l, s, b); /* 将父过程基地址入栈，即建立静态链 */
            s[t + 2] = b; /* 将本过程基地址入栈，即建立动态链 */
            s[t + 3] = p; /* 将当前指令指针入栈，即保存返回地址 */
            b = t + 1;  /* 改变基地址指针值为新过程的基地址 */
            p = i.a;  /* 跳转 */
            printstack(t, p, s);
            break;
        case ini: /* 在数据栈中为被调用的过程开辟a个单元的数据区 */
            t = t + i.a;
            printstack(t, p, s);
            break;
        case jmp: /* 直接跳转 */
            p = i.a;
            printstack(t, p, s);
            break;
        case jpc: /* 如果栈顶等于0条件跳转 */
            if (s[t] == 0)
                p = i.a;
            t = t - 1;
            printstack(t, p, s);
            break;
        case jpe: /* 如果栈顶等于1条件跳转 */
            if (s[t]) 
                p = i.a;
            t = t - 1;
            printstack(t, p, s);
            break;
        case ext:
            p = 0;
            printstack(t, p, s);
            break;
        case blo: //不改变p
            s[t + 1] = base(i.l, s, b);
            s[t + 2] = b;
            b = t + 1;
            printstack(t, p, s);
            break;
        case fre: //不改变p
            t = b - 1;
            b = s[t + 2];
            printstack(t, p, s);
            break;
        }
    } while (p != 0);
    printf("End CX interpret\n");
    fprintf(fresult, "End CX interpret\n");
}

/* 通过过程基址求上ｌ层过程的基址 */
int base(int l, int s[], int b) {
    int b1 = b;
    while (l > 0) {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}

int main(int argc, char *argv[]) {
    int i;
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-c") == 0) {  /* 是否输出虚拟机代码 */
                listswitch = true;
            } else if (strcmp(argv[i], "-t") == 0) {  /* 是否输出符号表 */
                tableswitch = true;
            } else if (strcmp(argv[i], "-s") == 0) {  /* 是否输出栈信息 */
                stackswitch = true;
            } 
        }
    }
    if ((fin = fopen(argv[argc - 1], "r")) == NULL) {
        printf("Can't open the input file!\n");
        exit(1);
    }
    if ((foutput = fopen("foutput.txt", "w")) == NULL) {
        printf("Can't open the output file!\n");
        exit(1);
    }
    if ((ftable = fopen("ftable.txt", "w")) == NULL) {
        printf("Can't open ftable.txt file!\n");
        exit(1);
    }

    redirectInput(fin);
    init();
    yyparse();

    if (err == 0) {
        printf("\n===Parsing success!===\n\n");
        fprintf(foutput, "\n===Parsing success!===\n");
        if ((fcode = fopen("fcode.txt", "w")) == NULL) {
            printf("Can't open fcode.txt file!\n");
            exit(1);
        }
        if ((fresult = fopen("fresult.txt", "w")) == NULL) {
            printf("Can't open fresult.txt file!\n");
            exit(1);
        }
        if ((fstack = fopen("fstack.txt", "w")) == NULL) {
            printf("Can't open fresult.txt file!\n");
            exit(1);
        }

        listall();  /* 输出所有代码 */
        fclose(fcode);

        interpret();  /* 调用解释执行程序 */
        fclose(fresult);
        fclose(fstack);
    } else {
        printf("%d errors in CX program\n", err);
        fprintf(foutput, "%d errors in CX program\n", err);
    }

    fclose(ftable);
    fclose(foutput);
    fclose(fin);
    return 0;
}
