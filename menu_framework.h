/**
 * @file menu_framework.h
 * @brief
 * @details
 * @mainpage
 */
#ifndef __MENU_FRAMEWORK_H__
#define __MENU_FRAMEWORK_H__

#include "klist.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MENU_LANG_COUNT 2
#define MENU_CHAR_COUNT 32
#define MENU_STR_LENGTH (MENU_CHAR_COUNT + 1)

#define MENU_MAX_LINES 6

#define LANGUAGE_INDEX ctrl_para.system.language

struct menu_item;

typedef struct menu_item
{
    struct list_head list;
    int index;
    wchar_t text[MENU_STR_LENGTH];
    int (*func)(menu_item* pthis, int todo);
} menu_item_t;

typedef struct menu_head
{
    struct list_head list;
    struct list_head item_list;
    struct list_head* cur_item;
    int count;
    int show_pos;
    int selected_index;
    int grade;
} menu_head_t;

typedef struct menu_content
{
    wchar_t text[MENU_LANG_COUNT][MENU_STR_LENGTH];
    int (*func)(menu_item_t* pthis, int todo);
} menu_content_t;

typedef enum {
    MENU_REFRESH = 1000,
    MENU_TRIGGER,
    MENU_UP,
    MENU_DOWN,
    MENU_LEFT,
    MENU_RIGHT,
    MENU_SELECT,
    MENU_ENTER,
    MENU_BACK,
} menu_todo_t;

int Menu_DisplayInit(void);
int Menu_DisplayOpen(void);
int Menu_DisplayClose(void);

int AddMenuItem(const menu_content_t* menuct);
void ShowCurMenu(void);
void ShowCurLine(void);

int NewMenu(void);
int DeletMenu(void);

void Menu_RollUp(void);
void Menu_RollDown(void);
void Menu_ExeFunc(int arg);

int ApendParaStr(wchar_t* gram, const wchar_t* str);
int ApendStr2(wchar_t* gram, const wchar_t* str);

wchar_t* NumToString(uint16_t num);
wchar_t* NumToStringWithSymbol(int num);

#ifdef __cplusplus
}
#endif
#endif