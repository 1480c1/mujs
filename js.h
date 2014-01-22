#ifndef js_h
#define js_h

/* noreturn is a GCC extension */
#ifdef __GNUC__
#define JS_NORETURN __attribute__((noreturn))
#else
#ifdef _MSC_VER
#define JS_NORETURN __declspec(noreturn)
#else
#define JS_NORETURN
#endif
#endif

/* GCC can do type checking of printf strings */
#ifdef __printflike
#define JS_PRINTFLIKE __printflike
#else
#if __GNUC__ > 2 || __GNUC__ == 2 && __GNUC_MINOR__ >= 7
#define JS_PRINTFLIKE(fmtarg, firstvararg) \
	__attribute__((__format__ (__printf__, fmtarg, firstvararg)))
#else
#define JS_PRINTFLIKE(fmtarg, firstvararg)
#endif
#endif

typedef struct js_State js_State;

typedef int (*js_CFunction)(js_State *J, int argc);

/* Basic functions */
js_State *js_newstate(void);
void js_freestate(js_State *J);
int js_dostring(js_State *J, const char *source, int report);
int js_dofile(js_State *J, const char *filename);
void js_gc(js_State *J, int report);

/* RegExp flags */
enum {
	JS_REGEXP_G = 1,
	JS_REGEXP_I = 2,
	JS_REGEXP_M = 4,
};

/* Hint to ToPrimitive() */
enum {
	JS_HNONE,
	JS_HNUMBER,
	JS_HSTRING
};

/* Property attribute flags */
enum {
	JS_READONLY = 1,
	JS_DONTENUM = 2,
	JS_DONTDELETE = 4,
};

void js_newerror(js_State *J, const char *message);
void js_newevalerror(js_State *J, const char *message);
void js_newrangeerror(js_State *J, const char *message);
void js_newreferenceerror(js_State *J, const char *message);
void js_newsyntaxerror(js_State *J, const char *message);
void js_newtypeerror(js_State *J, const char *message);
void js_newurierror(js_State *J, const char *message);

JS_NORETURN void js_error(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_evalerror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_rangeerror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_referenceerror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_syntaxerror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_typeerror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_urierror(js_State *J, const char *fmt, ...) JS_PRINTFLIKE(2,3);
JS_NORETURN void js_throw(js_State *J);

void js_loadstring(js_State *J, const char *filename, const char *source);
void js_loadfile(js_State *J, const char *filename);

void js_call(js_State *J, int n);
void js_construct(js_State *J, int n);

void js_getglobal(js_State *J, const char *name);
void js_setglobal(js_State *J, const char *name);

void js_getownproperty(js_State *J, int idx, const char *name);
void js_getproperty(js_State *J, int idx, const char *name);
void js_setproperty(js_State *J, int idx, const char *name);
void js_cfgproperty(js_State *J, int idx, const char *name, int atts);
void js_delproperty(js_State *J, int idx, const char *name);
int js_nextproperty(js_State *J, int idx);

void js_pushglobal(js_State *J);
void js_pushundefined(js_State *J);
void js_pushnull(js_State *J);
void js_pushboolean(js_State *J, int v);
void js_pushnumber(js_State *J, double v);
void js_pushstring(js_State *J, const char *v);
void js_pushliteral(js_State *J, const char *v);

void js_newobject(js_State *J);
void js_newarray(js_State *J);
void js_newboolean(js_State *J, int v);
void js_newnumber(js_State *J, double v);
void js_newstring(js_State *J, const char *v);
void js_newerror(js_State *J, const char *message);
void js_newcfunction(js_State *J, js_CFunction fun, int length);
void js_newcconstructor(js_State *J, js_CFunction fun, js_CFunction con);

int js_isundefined(js_State *J, int idx);
int js_isnull(js_State *J, int idx);
int js_isboolean(js_State *J, int idx);
int js_isnumber(js_State *J, int idx);
int js_isstring(js_State *J, int idx);
int js_isprimitive(js_State *J, int idx);
int js_isobject(js_State *J, int idx);
int js_iscallable(js_State *J, int idx);

int js_toboolean(js_State *J, int idx);
double js_tonumber(js_State *J, int idx);
const char *js_tostring(js_State *J, int idx);

double js_tointeger(js_State *J, int idx);
int js_toint32(js_State *J, int idx);
unsigned int js_touint32(js_State *J, int idx);
short js_toint16(js_State *J, int idx);
unsigned short js_touint16(js_State *J, int idx);

int js_gettop(js_State *J);
void js_settop(js_State *J, int idx);
void js_pop(js_State *J, int n);
void js_rot(js_State *J, int n);
void js_copy(js_State *J, int idx);
void js_remove(js_State *J, int idx);
void js_insert(js_State *J, int idx);
void js_replace(js_State* J, int idx);

void js_concat(js_State *J);
int js_compare(js_State *J);
int js_equal(js_State *J);
int js_strictequal(js_State *J);

#endif
