/*
Copyright (C) 2000-2014 Javier O'Hara

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef DIA2CODE_H
#define DIA2CODE_H

#include "config.h"

#include <list>
#include <string>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/* for mkdir and mode_t */
#include <sys/types.h>
#include <sys/stat.h>

/* libxml[2] headers */
#include <libxml/parser.h>
#include <libxml/tree.h>

#ifdef DSO
#include <dlfcn.h>
#define MODULE_DIR ".dia2code"
#define DSO_PREFIX "generate_code_"
#define DSO_SUFFIX ".so"
#endif

#define kind_str(A)   ((A)=='1'?"in":((A)=='2'?"in/out":((A)=='3'?"out":"???")))

/* Auxiliary define for the emit/print functions  */
#define var_arg_to_str(first_arg) \
    va_list vargu; \
    char str[LARGE_BUFFER]; \
    va_start (vargu, first_arg); \
    vsnprintf (str, LARGE_BUFFER, first_arg, vargu); \
    va_end (vargu)

/* constants for scope / visibilities */
#define D2C_PUBLIC      '0'
#define D2C_PRIVATE     '1'
#define D2C_PROTECTED   '2'

#define DBG_DIAGRAM    2
#define DBG_FNCCALL    4
#define DBG_SOURCE     5
#define DBG_GENCODE    6
#define DBG_CORE       8

#define SMALL_BUFFER    80
#define BIG_BUFFER     512
#define LARGE_BUFFER  4096
#define HUGE_BUFFER  16384

struct umlattribute {
    char name[SMALL_BUFFER];
    char value[SMALL_BUFFER];
    char type [SMALL_BUFFER];
    char comment [LARGE_BUFFER];
    char visibility;
    char isabstract;
    char isstatic;
    char isconstant;
    char kind;
    char diaoid[10];
};
typedef struct umlattribute umlattribute;

struct umlattrnode {
    umlattribute key;
    struct umlattrnode *next;
};

typedef struct umlattrnode umlattrnode;
typedef umlattrnode *umlattrlist;

struct umloperation {
    umlattribute attr;
    umlattrlist parameters;
    char *implementation; /* the previous source code of the method - parsed from existing file */
};
typedef struct umloperation umloperation;

struct umlopnode {
    umloperation key;
    struct umlopnode *next;
};
typedef struct umlopnode umlopnode;

typedef umlopnode *umloplist;

struct umltemplate {
    char name[SMALL_BUFFER];
    char type[SMALL_BUFFER];
};
typedef struct umltemplate umltemplate;

struct umltemplatenode {
        umltemplate key;
        struct umltemplatenode *next;
};
typedef struct umltemplatenode umltemplatenode;

typedef umltemplatenode *umltemplatelist;

struct geometry {
    float pos_x;
    float pos_y;
    float width;
    float height;
};
typedef struct geometry geometry;

struct umlpackage {
    char id[SMALL_BUFFER];
    char name[SMALL_BUFFER];
    geometry geom;
    struct umlpackage * parent;
    char *directory;
};
typedef struct umlpackage umlpackage;

struct umlpackagenode {
    umlpackage *key;
    struct umlpackagenode * next;
};
typedef struct umlpackagenode umlpackagenode;

typedef umlpackagenode * umlpackagelist;

struct umlclass {
    char id[SMALL_BUFFER];
    char name[SMALL_BUFFER];
    char stereotype[SMALL_BUFFER];
    char comment[LARGE_BUFFER];
    int isabstract;
    umlattrlist attributes;
    umloplist operations;
    umltemplatelist templates;
    umlpackage * package;
    geometry geom;
};
typedef struct umlclass umlclass;

struct umlassocnode {
    umlclass * key;
    char name[SMALL_BUFFER];
    char composite;
    struct umlassocnode * next;
    char multiplicity[10]; /* association can declare multiplicity */
};
typedef struct umlassocnode umlassocnode;

typedef umlassocnode * umlassoclist;

struct umlclassnode {
    umlclass * key;
    struct umlclassnode * parents;
    struct umlassocnode * associations;
    struct umlclassnode * dependencies;
    struct umlclassnode * next;
};
typedef struct umlclassnode umlclassnode;

typedef umlclassnode * umlclasslist;

void debug_setlevel( int newlevel );
void debug( int level, char *fmt, ... );

char *strtoupper(char *s);
char *strtolower(char *s);
char *strtoupperfirst(char *s);
std::list <std::string> parse_class_names (const char *s);
int is_present(std::list <std::string> list, const char *name);
umlclasslist find_by_name(umlclasslist list, const char * name);

int is_enum_stereo (char * stereo);
int is_struct_stereo (char * stereo);
int is_typedef_stereo (char * stereo);
int is_const_stereo (char * stereo);

umlattrlist copy_attributes(umlattrlist src);

void * my_malloc( size_t size );

#define NEW(c) ((c*)my_malloc(sizeof(c)))

umlpackagelist make_package_list( umlpackage * package);

extern char *body_file_ext;  /* Set by switch "-bext". Language specific
                                default applies when NULL.  */

/* Returns a string consisting of (indentlevel *
   number_of_spaces_for_one_indentation) spaces.  */
void d2c_indentate(FILE *f);
int d2c_directprintf(FILE *f, char *fmt, ...);

/**
 * Output target files:
 * All backends would use `spec', but not all backends require `body'.
 * Hence not all backends need the {e,p}{body,both} functions below.
*/
extern FILE *body;

extern int d2c_indentposition;

void dia2code_initializations();

/* Emitters for file output  */
void emit  (char *msg, ...);  /* print verbatim to spec */
void ebody (char *msg, ...);  /* print verbatim to body (e stands for emit) */
void eboth (char *msg, ...);  /* print verbatim to both spec and body */
void print (char *msg, ...);  /* print with leading indentation to spec */
void pbody (char *msg, ...);  /* print with leading indentation to body */
void pboth (char *msg, ...);  /* print with leading indentation to both */

#define NEW_AUTO_INDENT 1
#ifdef NEW_AUTO_INDENT
#define d2c_fprintf _d2c_fprintf
#define d2c_fputs _d2c_fputs
#define d2c_fputc _d2c_fputc
#else
#define d2c_fprintf d2c_directprintf
#define d2c_fputs fputs
#define d2c_fputc fputc
#endif

void d2c_indent();
void d2c_outdent();
int _d2c_fputs(const char *s, FILE *f);
int _d2c_fputc(int c, FILE *f);
int _d2c_fprintf(FILE *f, char *fmt, ...);
/* void d2c_set_braces(char *open, char *close); */
void d2c_open_brace(FILE *outfile, char *suffix);
void d2c_close_brace(FILE *outfile, char *suffix);
void d2c_parse_impl(FILE *f, char *cmt_start, char *cmt_end);
void d2c_dump_impl(FILE *f, char *section, char *name);
void d2c_deprecate_impl(FILE *f, char *comment_start, char *comment_end);
char *d2c_operation_mangle_name(umloperation *op);
void d2c_shift_code();
void d2c_unshift_code();

char *find_diaoid( const char *buf, char **newpos  );
int d2c_backup(char *filename);
void d2c_log( int level, char * msg );

#define TAG fprintf(stderr, "%s %d\n", __FILE__, __LINE__);

struct param_list
{
  char *name;
  char *value;
  struct param_list *next;
};

typedef struct param_list param_list;

void param_list_destroy();
param_list * d2c_parameter_add(char *name, char *value);
param_list * d2c_parameter_set(char *name, char *value);
char * d2c_parameter_value(char *name);
param_list *d2c_parameter_find(char *name);

extern int indent_count;
extern int indent_open_brace_on_newline;
extern int generate_backup;

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
