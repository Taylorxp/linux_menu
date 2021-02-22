/**
 * @file menu_framework.c
 * @brief
 * @details
 * @mainpage
 */
#include "menu_framework.h"
#include "ctrl.h"
#include <string.h>
#include <wchar.h>

#define FONT_COLOR_WHITE 0xFFFF
#define FONT_COLOR_RED 0xF800

static LIST_HEAD(MenuHead);

/**
 * @brief Menu
 */
int Menu_DisplayInit(void)
{
    menu_api.menu_display_init();
    return 0;
}

/**
 * @brief
 */

int Menu_Clear(void)
{
    menu_api.menu_clear();
    return 0;
}

/**
 * @brief
 */
int Menu_Refresh(void)
{
    menu_api.menu_refresh();
    return 0;
}

/**
 * @brief
 */
int Menu_DisplayOpen(void)
{
    menu_api.menu_display_open();
    return 0;
}
/**
 * @brief
 */
int Menu_DisplayClose(void)
{
    menu_api.menu_display_close();
    return 0;
}

/**
 * @brief
 */
int Menu_ShowString(wchar_t* str, int x, int y, uint16_t color)
{
    menu_api.menu_show_string(str, x, y, color);
    return 0;
}

/***************************************************************************************************
 * Description:  创建列表
 ***************************************************************************************************/
int NewMenu(void)
{
    menu_head_t* head;
    menu_head_t* menu_list;
    int grade;

    if (list_empty(&MenuHead))
    {
        grade = 0;
    }
    else
    {
        menu_list = list_first_entry(&MenuHead, menu_head_t, list);
        grade = menu_list->grade + 1;
    }

    /* 列表 */
    head = (menu_head_t*)malloc(sizeof(menu_head_t));
    if (head == NULL)
        return 1;

    head->item_list.prev = &head->item_list;
    head->item_list.next = &head->item_list;
    head->cur_item = NULL;
    head->count = 0;
    head->selected_index = 0;
    head->show_pos = 0;
    head->grade = grade;
    list_add(&head->list, &MenuHead);

    return 0;
}

/***************************************************************************************************
 * Description:  删除当前的列表
 ***************************************************************************************************/
int DeletMenu(void)
{
    menu_head_t* menu_list;
    struct list_head *it, *temp;
    menu_item_t* item;

    if (list_empty(&MenuHead))
        return 1;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    list_for_each_safe(it, temp, &menu_list->item_list)
    {
        item = list_entry(it, menu_item_t, list);
        list_del(it);
        free(item);
    }

    list_del(MenuHead.next);
    free(menu_list);

    if (list_empty(&MenuHead))
        return 1;

    return 0;
}

/***************************************************************************************************
 * Description:  添加一个节点
 ***************************************************************************************************/
int AddMenuItem(const menu_content_t* menuct)
{
    menu_head_t* menu_list;
    menu_item_t* item;

    uint8_t index;

    if (menuct == NULL)
        return 1;

    if (list_empty(&MenuHead))
        return 1;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    /* 分配内存 */
    item = (menu_item_t*)malloc(sizeof(menu_item_t));
    if (item == NULL)
        return 1;
    memset(item, 0, sizeof(menu_item_t));

    /* 计算新节点的序列号 */
    if (list_empty(&menu_list->item_list))
    {
        index = 0;
        menu_list->cur_item = &item->list;
    }
    else
    {
        menu_item_t* temp;
        temp = list_last_entry(&menu_list->item_list, menu_item_t, list);
        index = temp->index + 1;
    }

    /* 填充数据 */
    item->index = index;
    int flag = 0;
    for (int i = 0; i < MENU_CHAR_COUNT; i++)
    {
        if (flag == 0 && menuct->text[LANGUAGE_INDEX][i] != '\0')
        {
            item->text[i] = menuct->text[LANGUAGE_INDEX][i];
        }
        else
        {
            flag = 1;
            item->text[i] = L' ';
        }
    }
    // wcscpy(item->text, menuct->text[LANGUAGE_INDEX]);

    item->func = menuct->func;

    // LOG_INFO("NEW NODE:%ls", menuct->text[LANGUAGE_INDEX]);

    list_add_tail(&item->list, &menu_list->item_list);
    menu_list->count++;
    return 0;
}

/***************************************************************************************************
 * Description:  显示菜单
 ***************************************************************************************************/
void ShowCurMenu(void)
{
    menu_head_t* menu_list;
    struct list_head* it;
    menu_item_t* item;
    uint8_t count = 0;

    if (list_empty(&MenuHead))
        return;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return;

    // LOG_INFO("grade:%d, show_pos:%d, selected:%d", menu_list->grade, menu_list->show_pos, menu_list->selected_index);

    Menu_Clear();

    list_for_each(it, &menu_list->item_list)
    {
        // LOG_INFO("count:%d", count);

        /* 显示数据 */
        item = list_entry(it, menu_item_t, list);
        if (item->index < menu_list->show_pos)
        {
            // LOG_INFO("continue");
            continue;
        }

        if (item->func != NULL)
            item->func(item, MENU_REFRESH);

        if (&item->list == menu_list->cur_item)
        {
            menu_list->selected_index = item->index;
            Menu_ShowString(item->text, 0, count, FONT_COLOR_RED);
        }
        else
        {
            Menu_ShowString(item->text, 0, count, FONT_COLOR_WHITE);
        }

        if (++count >= MENU_MAX_LINES)
            break;
    }

    Menu_Refresh();
}

/***************************************************************************************************
 * Description:  显示当前行
 ***************************************************************************************************/
void ShowCurLine(void)
{
    menu_head_t* menu_list;
    menu_item_t* item;

    if (list_empty(&MenuHead))
        return;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return;
    item = list_entry(menu_list->cur_item, menu_item_t, list);

    if (item->func != NULL)
        item->func(item, MENU_REFRESH);
    Menu_ShowString(item->text, 0, menu_list->selected_index - menu_list->show_pos, FONT_COLOR_RED);
    Menu_Refresh();
}

/***************************************************************************************************
 * Description:  获取当前菜单指定行的文本buffer地址
 ***************************************************************************************************/
wchar_t* GetMenuCurLineText(int line)
{
    menu_head_t* menu_list;
    menu_item_t* item;
    struct list_head* it;

    if (list_empty(&MenuHead))
        return NULL;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return NULL;

    if (line == -1)
    {
        item = list_entry(menu_list->cur_item, menu_item_t, list);
        return item->text;
    }
    else
    {
        list_for_each(it, &menu_list->item_list)
        {
            /* 显示数据 */
            item = list_entry(it, menu_item_t, list);

            if (item->index == line)
                return item->text;
        }
        return NULL;
    }
    return NULL;
}

/***************************************************************************************************
 * Description:  当前列表向上滚动
 ***************************************************************************************************/
void Menu_RollUp(void)
{
    menu_head_t* menu_list;
    menu_item_t* item;
    int cycle_flag = 0;

    if (list_empty(&MenuHead))
        return;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return;

    menu_list->cur_item = menu_list->cur_item->prev;
    if (menu_list->cur_item == &menu_list->item_list)
    {
        menu_list->cur_item = menu_list->cur_item->prev;
        cycle_flag = 1;
    }

    item = list_entry(menu_list->cur_item, menu_item_t, list);
    menu_list->selected_index = item->index;

    if (menu_list->count > MENU_MAX_LINES)
    {
        if (cycle_flag)
            menu_list->show_pos = menu_list->count - MENU_MAX_LINES;
        else if (menu_list->show_pos > menu_list->selected_index)
            menu_list->show_pos = menu_list->selected_index;
    }
    else
    {
        menu_list->show_pos = 0;
    }

    ShowCurMenu();
    // LOG_INFO("sel_line:%d", menu_list->selected_index);
}

/***************************************************************************************************
 * Description:  当前列表向下滚动
 ***************************************************************************************************/
void Menu_RollDown(void)
{
    menu_head_t* menu_list;
    menu_item_t* item;
    int cycle_flag = 0;

    if (list_empty(&MenuHead))
        return;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return;

    menu_list->cur_item = menu_list->cur_item->next;
    if (menu_list->cur_item == &menu_list->item_list)
    {
        menu_list->cur_item = menu_list->cur_item->next;
        cycle_flag = 1;
    }

    item = list_entry(menu_list->cur_item, menu_item_t, list);
    menu_list->selected_index = item->index;

    if (menu_list->count > MENU_MAX_LINES)
    {
        if (cycle_flag)
            menu_list->show_pos = 0;
        else if (menu_list->show_pos + MENU_MAX_LINES <= menu_list->selected_index)
            menu_list->show_pos = menu_list->selected_index - MENU_MAX_LINES + 1;
    }
    else
    {
        menu_list->show_pos = 0;
    }

    ShowCurMenu();
    // LOG_INFO("sel_line:%d", menu_list->selected_index);
}

/***************************************************************************************************
 * Description:  指令列表程序
 ***************************************************************************************************/
void Menu_ExeFunc(int arg)
{
    menu_head_t* menu_list;
    menu_item_t* item;

    if (list_empty(&MenuHead))
        return;
    menu_list = list_first_entry(&MenuHead, menu_head_t, list);

    if (list_empty(&menu_list->item_list))
        return;
    item = list_entry(menu_list->cur_item, menu_item_t, list);

    if (item->func != NULL)
        item->func(item, arg);
}

/**
 * @brief 获取字符宽度
 * @detail
 *
 * @param
 * @return
 *   @retval
 */
int GetWCharWidth(wchar_t ch)
{
    int width = 0;
    /** ASCII 字符 */
    if (ch >= 32 && ch <= 128)
        width += 1;
    /** 中文字符 */
    else if (ch >= 0x4E00 && ch <= 0x9FA5)
        width += 2;
    else
        LOG_WARN("known charactor:%08X", ch);

    return width;
}

/**
 * @brief
 * @detail
 *
 * @param
 * @return
 *   @retval
 */
int ApendParaStr(wchar_t* gram, const wchar_t* str)
{
    // LOG_INFO("STR: %ls\n", gram);

    /** 计算要参数字符宽度及个数 */
    int para_width = 0;
    int para_count = 0;
    const wchar_t* tmp = str;
    while (*tmp != '\0')
    {
        para_width += GetWCharWidth(*tmp++);
        para_count++;
    }

    /** 填充参数 */
    int flag = 0;
    int head_width = 0;
    int head_count = 0;
    for (int i = 0; i < MENU_CHAR_COUNT; i++)
    {
        if (flag)
        {
            gram[i] = L' ';
        }
        else
        {
            if (gram[i] == L':' || gram[i] == L'>')
            {
                flag = 1;
                head_width++;
            }
            else
            {
                head_width += GetWCharWidth(gram[i]);
            }
            head_count++;
        }
    }

    int pos = head_count + (MENU_CHAR_COUNT - para_width - head_width) - 2;
    gram[pos] = L'<';
    pos++;

    wcscpy(&gram[pos], str);
    pos += para_count;

    gram[pos] = L'>';

    return 0;
}

int ApendStr2(wchar_t* gram, const wchar_t* str)
{
    // LOG_INFO("STR: %ls\n", gram);

    /** 计算要参数字符宽度及个数 */
    int para_width = 0;
    int para_count = 0;
    const wchar_t* tmp = str;
    while (*tmp != '\0')
    {
        para_width += GetWCharWidth(*tmp++);
        para_count++;
    }

    /** 填充参数 */
    int flag = 0;
    int head_width = 0;
    int head_count = 0;
    for (int i = 0; i < MENU_CHAR_COUNT; i++)
    {
        if (flag)
        {
            gram[i] = L' ';
        }
        else
        {
            if (gram[i] == L':' || gram[i] == L'>')
            {
                flag = 1;
                head_width++;
            }
            else
            {
                head_width += GetWCharWidth(gram[i]);
            }
            head_count++;
        }
    }

    wcscpy(&gram[head_count + (MENU_CHAR_COUNT - para_width - head_width)], str);

    return 0;
}

/***************************************************************************************************
 * Description: 把小于1000的数字转换为字符，右对齐
 **************************************************************************************************/
wchar_t* NumToString(uint16_t num)
{
    static wchar_t buffer[4] = {'\0', '\0', '\0', '\0'};
    memset(buffer, 0, sizeof(buffer));
    if (num < 10)
    {
        buffer[0] = num + L'0';
    }
    else if (num < 100)
    {
        buffer[0] = num / 10 + L'0';
        buffer[1] = num % 10 + L'0';
    }
    else
    {
        buffer[0] = num / 100 + L'0';
        buffer[1] = num % 100 / 10 + L'0';
        buffer[2] = num % 100 % 10 + L'0';
    }
    return buffer;
}
/* 带正负号 */
wchar_t* NumToStringWithSymbol(int num)
{
    static wchar_t buffer[5] = {'\0', '\0', '\0', '\0', '\0'};
    int index = 0;

    memset(buffer, 0, sizeof(buffer));
    if (num != 0)
    {
        if (num > 0)
            buffer[index] = L'+';
        else
            buffer[index] = L'-';
        index++;
        num = abs(num);
    }

    if (num < 10)
    {
        buffer[index + 0] = num + L'0';
    }
    else if (num < 100)
    {
        buffer[index + 0] = num / 10 + L'0';
        buffer[index + 1] = num % 10 + L'0';
    }
    else
    {
        buffer[index + 0] = num / 100 + L'0';
        buffer[index + 1] = num % 100 / 10 + L'0';
        buffer[index + 2] = num % 100 % 10 + L'0';
    }
    return buffer;
}