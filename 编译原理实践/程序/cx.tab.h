/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PLUS = 258,
     MINUS = 259,
     TIMES = 260,
     SLASH = 261,
     LES = 262,
     LEQ = 263,
     GTR = 264,
     GEQ = 265,
     EQL = 266,
     NEQ = 267,
     BECOMES = 268,
     OR = 269,
     AND = 270,
     NOT = 271,
     SEMICOLON = 272,
     LPAREN = 273,
     RPAREN = 274,
     LBRACKET = 275,
     RBRACKET = 276,
     LBRACE = 277,
     RBRACE = 278,
     COMMA = 279,
     IF = 280,
     ELSE = 281,
     WHILE = 282,
     WRITE = 283,
     READ = 284,
     INT = 285,
     BOOL = 286,
     CONST = 287,
     CHAR = 288,
     SELFADD = 289,
     SELFMIUNS = 290,
     REPEAT = 291,
     UNTIL = 292,
     XOR = 293,
     MOD = 294,
     ODD = 295,
     TRUE = 296,
     FALSE = 297,
     CALL = 298,
     DO = 299,
     FUNC = 300,
     EXIT = 301,
     FOR = 302,
     IDENT = 303,
     NUMBER = 304,
     CHARACTER = 305,
     IFX = 306
   };
#endif
/* Tokens.  */
#define PLUS 258
#define MINUS 259
#define TIMES 260
#define SLASH 261
#define LES 262
#define LEQ 263
#define GTR 264
#define GEQ 265
#define EQL 266
#define NEQ 267
#define BECOMES 268
#define OR 269
#define AND 270
#define NOT 271
#define SEMICOLON 272
#define LPAREN 273
#define RPAREN 274
#define LBRACKET 275
#define RBRACKET 276
#define LBRACE 277
#define RBRACE 278
#define COMMA 279
#define IF 280
#define ELSE 281
#define WHILE 282
#define WRITE 283
#define READ 284
#define INT 285
#define BOOL 286
#define CONST 287
#define CHAR 288
#define SELFADD 289
#define SELFMIUNS 290
#define REPEAT 291
#define UNTIL 292
#define XOR 293
#define MOD 294
#define ODD 295
#define TRUE 296
#define FALSE 297
#define CALL 298
#define DO 299
#define FUNC 300
#define EXIT 301
#define FOR 302
#define IDENT 303
#define NUMBER 304
#define CHARACTER 305
#define IFX 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 86 "cx.y"
{
    char *ident;
    int number;
}
/* Line 1529 of yacc.c.  */
#line 156 "cx.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

