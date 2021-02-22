/**
 * @file menu.cpp
 * @brief
 * @details
 * @mainpage
 */
#include "menu.h"
#include "ctrl.h"
#include "menu_framework.h"

/**************************************************************************************************
 * @seg
 **************************************************************************************************/
typedef struct
{
    struct timespec open;
    struct timespec back;
    struct timespec enter;
    struct timespec up_down;
    struct timespec left_right;
    struct timespec num;
} menu_time_snap_t;

/**************************************************************************************************
 * @seg
 **************************************************************************************************/
int func_Back(menu_item* pthis, int todo);

int func_SerialPort(menu_item* pthis, int todo);
int func_Protocol(menu_item* pthis, int todo);
int func_Address(menu_item* pthis, int todo);
int func_AddressFix(menu_item* pthis, int todo);
int func_Baudrate(menu_item* pthis, int todo);
int func_SpeedGrade(menu_item* pthis, int todo);
int func_SpeedByZoom(menu_item* pthis, int todo);
int func_Rs485(menu_item* pthis, int todo);

int func_Ptz(menu_item* pthis, int todo);
int func_Dzoom(menu_item* pthis, int todo);
int func_FocusMode(menu_item* pthis, int todo);
int func_AFSense(menu_item* pthis, int todo);
int func_RemoteSpeed(menu_item* pthis, int todo);
int func_ReloadPreset1(menu_item* pthis, int todo);
int func_Installation(menu_item* pthis, int todo);
int func_PanReverse(menu_item* pthis, int todo);
int func_TiltReverse(menu_item* pthis, int todo);

int func_Exposure(menu_item* pthis, int todo);
int func_ExpMode(menu_item* pthis, int todo);
int func_ExpShutter(menu_item* pthis, int todo);
int func_ExpGain(menu_item* pthis, int todo);
int func_ExpComp(menu_item* pthis, int todo);
int func_ExpBacklight(menu_item* pthis, int todo);

int func_WhiteBalance(menu_item* pthis, int todo);
int func_WbMode(menu_item* pthis, int todo);
int func_WbRgain(menu_item* pthis, int todo);
int func_WbBgain(menu_item* pthis, int todo);
int func_WbTrigger(menu_item* pthis, int todo);
int func_WbAutoCorrection(menu_item* pthis, int todo);
int func_WbManualCorrection(menu_item* pthis, int todo);

int func_Image(menu_item* pthis, int todo);
int func_Image2DNr(menu_item* pthis, int todo);
int func_Image3DNr(menu_item* pthis, int todo);
int func_ImageBright(menu_item* pthis, int todo);
int func_ImageContrast(menu_item* pthis, int todo);
int func_ImageColorGain(menu_item* pthis, int todo);
int func_ImageSharpness(menu_item* pthis, int todo);
int func_ImageHUE(menu_item* pthis, int todo);
int func_ImageGamma(menu_item* pthis, int todo);
int func_ImageWDR(menu_item* pthis, int todo);
int func_ImageDeFlicker(menu_item* pthis, int todo);
int func_ImageFlip(menu_item* pthis, int todo);
int func_ImageMirror(menu_item* pthis, int todo);

int func_System(menu_item* pthis, int todo);
int func_Language(menu_item* pthis, int todo);
int func_Version(menu_item* pthis, int todo);
int func_ResetDevice(menu_item* pthis, int todo);

int func_HideMenu(menu_item* pthis, int todo);
int func_LensRevis(menu_item* pthis, int todo);
int func_Aging(menu_item* pthis, int todo);

int func_PtzAdvance(menu_item* pthis, int todo);
int func_ZoomSpeed(menu_item* pthis, int todo);
int func_FocusSpeed(menu_item* pthis, int todo);
int func_PanAcc(menu_item* pthis, int todo);
int func_PanDec(menu_item* pthis, int todo);
int func_PanBrake(menu_item* pthis, int todo);
int func_TiltAcc(menu_item* pthis, int todo);
int func_TiltDec(menu_item* pthis, int todo);
int func_TiltBrake(menu_item* pthis, int todo);

int func_CtrlVersion(menu_item* pthis, int todo);
int func_McuVersion(menu_item* pthis, int todo);

int func_ResetImage(menu_item* pthis, int todo);
int func_CompleteReset(menu_item* pthis, int todo);

menu_content_t menu_main[] = {
    {L"SerialPort>", L"串口>", func_SerialPort}, {L"PTZ>", L"云台>", func_Ptz},       {L"Exposure>", L"曝光>", func_Exposure}, {L"White Balance>", L"白平衡>", func_WhiteBalance},
    {L"Image>", L"图像>", func_Image},           {L"System>", L"系统>", func_System}, {L"Exit", L"退出", func_Back},
};

menu_content_t menu_serialport[] = {
    {L"Protocol:", L"协议:", func_Protocol},
    {L"Address:", L"地址:", func_Address},
    {L"Address Fixed:", L"地址固定:", func_AddressFix},
    {L"Baud Rate:", L"波特率:", func_Baudrate},
    {L"Speed Grade:", L"速度等级:", func_SpeedGrade},
    {L"Speed By Zoom:", L"速度限制:", func_SpeedByZoom},
    {L"RS-485:", L"RS-485:", func_Rs485},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_ptz[] = {
    // {L"DZoom:", L"数字变倍:", func_Dzoom},
    // if(!ctrl_status.fx)
    // {
    {L"Focus Mode:", L"聚焦模式:", func_FocusMode},
    {L"AF Sensitivity:", L"聚焦灵敏度:", func_AFSense},
    // }
    {L"Remote Speed:", L"遥控速度:", func_RemoteSpeed},
    {L"Installation:", L"安装方式:", func_Installation},
    {L"Reload Preset 1:", L"看守位:", func_ReloadPreset1},
    {L"PAN Reverse:", L"PAN反向:", func_PanReverse},
    {L"TILT Reverse:", L"TILT反向:", func_TiltReverse},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_exposure[] = {
    {L"AE Mode:", L"模式:", func_ExpMode},          {L"Shutter:", L"快门速度:", func_ExpShutter},     {L"Gain:", L"增益:", func_ExpGain},
    {L"Compensation:", L"曝光补偿:", func_ExpComp}, {L"Backlight:", L"背光补偿:", func_ExpBacklight}, {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_wb[] = {
    {L"WB Mode:", L"模式:", func_WbMode},
    {L"Rgain:", L"红增益:", func_WbRgain},
    {L"Bgain:", L"蓝增益:", func_WbBgain},
    {L"Trigger>", L"触发:", func_WbTrigger},
    // {L"Automatic Correction:", L"自动校正:", func_WbAutoCorrection},
    // {L"Manual Correction>", L"手动校正>", func_WbManualCorrection},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_image[] = {
    // {L"2D NR:", L"2D降噪:", func_Image2DNr},
    {L"3D NR:", L"3D降噪:", func_Image3DNr},
    {L"Bright:", L"亮度:", func_ImageBright},
    {L"Contrast:", L"对比度:", func_ImageContrast},
    {L"Color Gain:", L"饱和度:", func_ImageColorGain},
    {L"Sharpness:", L"清晰度>", func_ImageSharpness},
    {L"HUE:", L"色调>", func_ImageHUE},
    {L"Gamma:", L"伽马>", func_ImageGamma},
    // {L"WDR:", L"宽动态>", func_ImageWDR},
    {L"De-Flicker:", L"抗闪烁:", func_ImageDeFlicker},
    {L"Flip:", L"翻转:", func_ImageFlip},
    {L"Mirror:", L"镜像:", func_ImageMirror},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_system[] = {
    {L"Language:", L"语言:", func_Language},
    {L"Version:", L"版本信息:", func_Version},
    {L"Reset Device>", L"重置设备>", func_ResetDevice},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_reset[] = {
    {L"Reset Image>", L"重置图像>", func_ResetImage},
    {L"Complete Reset>", L"完全重置>", func_CompleteReset},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_hide[] = {
    {L"lens revise>", L"镜头校正>", func_LensRevis},
    {L"aging:", L"老化:", func_Aging},
    {L"ptz>", L"云台>", func_PtzAdvance},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_info_advance[] = {
    {L"ctrl version:", L"控制版本:", func_CtrlVersion},
    {L"mcu version:", L"单片机版本:", func_McuVersion},
    {L"Back>", L"返回>", func_Back},
};

menu_content_t menu_ptz_advance[] = {
    {L"Zoom Speed:", L"Zoom速度:", func_ZoomSpeed}, {L"Focus Speed:", L"Focus速度:", func_FocusSpeed},  {L"Pan Acc:", L"Pan加速度:", func_PanAcc},
    {L"Pan Dec:", L"Pan减速度:", func_PanDec},      {L"Pan Brake:", L"Pan刹车速度:", func_PanBrake},    {L"Tilt Acc:", L"Tilt加速度:", func_TiltAcc},
    {L"Tilt Dec:", L"Tilt减速度:", func_TiltDec},   {L"Tilt Brake:", L"Tilt刹车速度:", func_TiltBrake}, {L"Back>", L"返回>", func_Back},
};

#define ONOFF_COUNT 2
const wchar_t* strOnoff[MENU_LANG_COUNT][ONOFF_COUNT] = {
    {L"OFF", L"ON"},
    {L"关", L"开"},
};

static system_language_t LanguageBackup = system_language_english;
static menu_time_snap_t menu_time_snap;

/**
 * @brief 获取当前菜单状态
 */
int IsMenuOpen(void)
{
    return ctrl_status.menu;
}
/**
 * @brief 菜单初始化
 * @detail
 *
 * @param
 * @return
 *   @retval
 */
int MenuInit(void)
{
    Menu_DisplayInit();

    memset(&menu_time_snap, 0, sizeof(menu_time_snap_t));

// #define TEST
#ifdef TEST
    MenuOpen();

    int flag = 0;
    int value = 0;
    while (1)
    {
        char ch = getchar();
        switch (ch)
        {
            case 27: flag = 1; break;
            case 91: flag = 2; break;
            case 65:
                flag = 3;
                value = -1;
                break;
            case 66:
                flag = 3;
                value = -2;
                break;
            case 67:
                flag = 3;
                value = -3;
                break;
            case 68:
                flag = 3;
                value = -4;
                break;
            case 10:
                if (flag == 0)
                {
                    MenuEnter();
                }
                else if (flag == 1)
                {
                    LOG_INFO("input:%d", ch);
                }
                else if (flag == 3)
                {
                    switch (value)
                    {
                        case -1: MenuUp(); break;
                        case -2: MenuDown(); break;
                        case -3: MenuRight(); break;
                        case -4: MenuLeft(); break;
                        default: LOG_INFO("input:%d", ch); break;
                    }
                }
                flag = 0;
                value = 0;
                break;

            default: flag = 0; break;
        }
    }
#endif

    return 0;
}

#define TIME_INTERVAL_MENU_OPEN 1000
#define TIME_INTERVAL_MENU_CLOSE 500
#define TIME_INTERVAL_MENU_BACK 500
#define TIME_INTERVAL_MENU_ENTER 500
#define TIME_INTERVAL_MENU_UP_DOWN 200
#define TIME_INTERVAL_MENU_LEFT_RIGHT 400
#define TIME_INTERVAL_MENU_NUM 500

/**
 * @brief 退出菜单时
 */
void MenuExitEvent(void)
{
    ctrl_status.menu = off;
    ctrl_serialport_protocol_set(ctrl_para.serial.protocol);
    ctrl_serialport_baudrate_set(ctrl_para.serial.baudrate);
    ctrl_serialport_rs485_set(ctrl_para.serial.rs485);
    ctrl_ptz_pan_set_accdec(ctrl_para.ptz.pan.acc_cur, ctrl_para.ptz.pan.dec_cur);
    ctrl_ptz_pan_set_brake(ctrl_para.ptz.pan.brake_cur);
    ctrl_ptz_tilt_set_accdec(ctrl_para.ptz.pan.acc_cur, ctrl_para.ptz.pan.dec_cur);
    ctrl_ptz_tilt_set_brake(ctrl_para.ptz.tilt.brake_cur);
    ctrl_aging_init();
    Ctrl_SaveConfig();
    usleep(500000);
    mcu_clear_input_buffer();
}

/**
 * @brief
 */
int MenuOpen(void)
{
    if (!check_time_interval(&menu_time_snap.open, TIME_INTERVAL_MENU_OPEN))
    {
        return 1;
    }

    if (ctrl_status.menu != off)
    {
        MenuBack();
        return 0;
    }

    ctrl_status.menu = on;

    LanguageBackup = LANGUAGE_INDEX;
    Menu_DisplayOpen();
    NewMenu();

    int count = sizeof(menu_main) / sizeof(menu_content_t);
    for (int i = 0; i < count; i++)
    {
        if (AddMenuItem(&menu_main[i]))
            return -1;
    }

    ShowCurMenu();

    return 0;
}

int MenuClose(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }

    Menu_DisplayClose();
    while (!DeletMenu())
        ;

    MenuExitEvent();
    return 0;
}

void MenuBack(void)
{
    if (ctrl_status.menu != on)
    {
        return;
    }

    if (!check_time_interval(&menu_time_snap.back, TIME_INTERVAL_MENU_BACK))
    {
        return;
    }

    if (DeletMenu())
    {
        Menu_DisplayClose();
        MenuExitEvent();
    }
    else if (LanguageBackup != LANGUAGE_INDEX)
    {
        LanguageBackup = LANGUAGE_INDEX;
        while (!DeletMenu())
            ;
        NewMenu();
        int count = sizeof(menu_main) / sizeof(menu_content_t);
        for (int i = 0; i < count; i++)
        {
            if (AddMenuItem(&menu_main[i]))
                return;
        }
        ShowCurMenu();
    }
    else
    {
        ShowCurMenu();
    }
}

int MenuUp(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }

    if (!check_time_interval(&menu_time_snap.up_down, TIME_INTERVAL_MENU_UP_DOWN))
    {
        return 1;
    }

    Menu_RollUp();
    LOG_INFO("Menu Up");
    return 0;
}

int MenuDown(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }
    if (!check_time_interval(&menu_time_snap.up_down, TIME_INTERVAL_MENU_UP_DOWN))
    {
        return 1;
    }

    Menu_RollDown();

    LOG_INFO("Menu Down");
    return 0;
}

int MenuLeft(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }

    if (!check_time_interval(&menu_time_snap.left_right, TIME_INTERVAL_MENU_LEFT_RIGHT))
    {
        return 1;
    }

    Menu_ExeFunc(MENU_LEFT);
    ShowCurMenu();
    LOG_INFO("Menu Left");
    return 0;
}

int MenuRight(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }
    if (!check_time_interval(&menu_time_snap.left_right, TIME_INTERVAL_MENU_LEFT_RIGHT))
    {
        return 1;
    }

    Menu_ExeFunc(MENU_RIGHT);
    ShowCurMenu();
    LOG_INFO("Menu Right");
    return 0;
}

int MenuEnter(void)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }
    if (!check_time_interval(&menu_time_snap.enter, TIME_INTERVAL_MENU_ENTER))
    {
        return 1;
    }

    Menu_ExeFunc(MENU_ENTER);
    LOG_INFO("Menu Enter");
    return 0;
}

int MenuNum(int num)
{
    if (ctrl_status.menu != on)
    {
        return -1;
    }
    if (!check_time_interval(&menu_time_snap.num, TIME_INTERVAL_MENU_NUM))
    {
        return 1;
    }
    Menu_ExeFunc(num);
    LOG_INFO("Menu Num:%d", num);
    return 0;
}

/**************************************************************************************************
 * @seg
 **************************************************************************************************/
int func_Back(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER: MenuBack(); break;
    }
    return 0;
};

int func_SerialPort(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            // int count = sizeof(menu_serialport) / sizeof(struct menu_content);
            // for (int i = 0; i < count; i++)
            // {
            //     if (AddMenuItem(&menu_serialport[i]))
            //         return 1;
            // }
            AddMenuItem(&menu_serialport[0]);
            AddMenuItem(&menu_serialport[1]);
            AddMenuItem(&menu_serialport[2]);
            AddMenuItem(&menu_serialport[3]);
            AddMenuItem(&menu_serialport[4]);
            AddMenuItem(&menu_serialport[5]);
            if (ctrl_status.rs485_exist)
                AddMenuItem(&menu_serialport[6]);
            AddMenuItem(&menu_serialport[7]);
            ShowCurMenu();
            break;
    }

    return 0;
}

int func_Protocol(menu_item* pthis, int todo)
{
#define PROTOCOL_COUNT serial_protocol_butt

    const wchar_t* str[MENU_LANG_COUNT][PROTOCOL_COUNT] = {
        {L"Auto", L"VISCA", L"Pelco D", L"Pelco P"},
        {L"自动", L"VISCA", L"Pelco D", L"Pelco P"},
    };

    int protocol;

    switch (todo)
    {
        case MENU_REFRESH:
            protocol = ctrl_para.serial.protocol;
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][protocol]);
            break;

        case MENU_RIGHT:
            protocol = ctrl_para.serial.protocol;
            if (++protocol > serial_protocol_pelco_p)
                protocol = serial_protocol_auto;
            ctrl_para.serial.protocol = (serial_protocol_t)protocol;
            break;

        case MENU_LEFT:
            protocol = ctrl_para.serial.protocol;
            if (--protocol < serial_protocol_auto)
                protocol = serial_protocol_pelco_p;
            ctrl_para.serial.protocol = (serial_protocol_t)protocol;
            break;
    }
    return 0;
}

int func_Address(menu_item* pthis, int todo)
{
#define ADDRESS_MIN ctrl_para.serial.address.value[ctrl_para.serial.protocol].min
#define ADDRESS_MAX ctrl_para.serial.address.value[ctrl_para.serial.protocol].max
#define ADDRESS_CUR ctrl_para.serial.address.value[ctrl_para.serial.protocol].cur

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(ADDRESS_CUR)); break;

        case MENU_RIGHT:
            if (++ADDRESS_CUR > ADDRESS_MAX)
                ADDRESS_CUR = ADDRESS_MIN;
            break;

        case MENU_LEFT:
            if (--ADDRESS_CUR < ADDRESS_MIN)
                ADDRESS_CUR = ADDRESS_MAX;
            break;
    }
    return 0;
}

int func_AddressFix(menu_item* pthis, int todo)
{
#define ADDRESS_FIXED ctrl_para.serial.address_fixed

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][ADDRESS_FIXED]); break;

        case MENU_LEFT:
        case MENU_RIGHT: ADDRESS_FIXED = ADDRESS_FIXED == on ? off : on; break;
    }
    return 0;
}

int func_Baudrate(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][serial_baudrate_butt] = {
        {L"2400", L"4800", L"9600", L"19200", L"38400", L"115200"},
        {L"2400", L"4800", L"9600", L"19200", L"38400", L"115200"},
    };

    int tmp;
    switch (todo)
    {
        case MENU_REFRESH:
            tmp = ctrl_para.serial.baudrate;
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][tmp]);
            break;

        case MENU_RIGHT:
            tmp = ctrl_para.serial.baudrate;
            if (++tmp > serial_baudrate_115200)
                tmp = serial_baudrate_2400;
            ctrl_para.serial.baudrate = (serial_baudrate_t)tmp;
            break;

        case MENU_LEFT:
            tmp = ctrl_para.serial.baudrate;
            if (--tmp < serial_baudrate_2400)
                tmp = serial_baudrate_115200;
            ctrl_para.serial.baudrate = (serial_baudrate_t)tmp;
            break;
    }
    return 0;
}

int func_SpeedGrade(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][serial_speed_grade_butt] = {
        {L"Standard", L"Expand"},
        {L"标准", L"扩展"},
    };

    int grade;
    switch (todo)
    {
        case MENU_REFRESH:
            grade = ctrl_para.serial.speed_grade;
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][grade]);
            break;

        case MENU_RIGHT:
            grade = ctrl_para.serial.speed_grade;
            if (++grade > serial_speed_grade_exp)
                grade = serial_speed_grade_std;
            ctrl_para.serial.speed_grade = (serial_speed_grade_t)grade;
            break;

        case MENU_LEFT:
            grade = ctrl_para.serial.speed_grade;
            if (--grade < serial_speed_grade_std)
                grade = serial_speed_grade_exp;
            ctrl_para.serial.speed_grade = (serial_speed_grade_t)grade;
            break;
    }
    return 0;
}

int func_SpeedByZoom(menu_item* pthis, int todo)
{
#define SPEED_BY_ZOOM ctrl_para.serial.speed_by_zoom

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][SPEED_BY_ZOOM]); break;

        case MENU_LEFT:
        case MENU_RIGHT: SPEED_BY_ZOOM = SPEED_BY_ZOOM == on ? off : on; break;
    }
    return 0;
}

int func_Rs485(menu_item* pthis, int todo)
{
#define RS485 ctrl_para.serial.rs485

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][RS485]); break;

        case MENU_LEFT:
        case MENU_RIGHT: RS485 = RS485 == on ? off : on; break;
    }
    return 0;
}

int func_Ptz(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            int count = sizeof(menu_ptz) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (ctrl_status.fx)
                {
                    if (i == 0 || i == 1)
                    {
                        continue;
                    }
                }
                if (AddMenuItem(&menu_ptz[i]))
                    return 1;
            }
            ShowCurMenu();
            break;
    }

    return 0;
}

int func_Dzoom(menu_item* pthis, int todo)
{
    onoff_t onoff;

    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_ptz_dzoom_get_onoff(&onoff);
            ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][onoff]);
            break;

        case MENU_LEFT:
        case MENU_RIGHT:
            ctrl_ptz_dzoom_get_onoff(&onoff);
            onoff = onoff == on ? off : on;
            ctrl_ptz_dzoom_set(onoff);
            break;
    }
    return 0;
}

int func_FocusMode(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][ptz_focus_butt] = {
        {L"Auto", L"Mannual", L"PTZ Trigger"},
        {L"自动", L"手动", L"PTZ触发"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_ptz_focus_mode_get(&ctrl_para.ptz.focus_mode.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.ptz.focus_mode.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.ptz.focus_mode);
            ctrl_ptz_focus_mode_set(ctrl_para.ptz.focus_mode.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.ptz.focus_mode);
            ctrl_ptz_focus_mode_set(ctrl_para.ptz.focus_mode.cur);

            break;
    }
    return 0;
}
int func_AFSense(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][ptz_af_sense_butt] = {
        {L"Normal", L"Low", L"High"},
        {L"正常", L"低", L"高"},
    };
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_ptz_af_sense_get(&ctrl_para.ptz.af_sense.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.ptz.af_sense.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.ptz.af_sense);
            ctrl_ptz_af_sense_set(ctrl_para.ptz.af_sense.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.ptz.af_sense);
            ctrl_ptz_af_sense_set(ctrl_para.ptz.af_sense.cur);

            break;
    }
    return 0;
}
int func_RemoteSpeed(menu_item* pthis, int todo)
{
#define SPEED_CUR ctrl_para.ptz.remote_speed.cur

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(SPEED_CUR)); break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.ptz.remote_speed);
            ctrl_ptz_speed_set(SPEED_CUR);
            ctrl_ptz_update_pt_speed();
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.ptz.remote_speed);
            ctrl_ptz_speed_set(SPEED_CUR);
            ctrl_ptz_update_pt_speed();
            break;
    }
    return 0;
}

int func_ReloadPreset1(menu_item* pthis, int todo)
{
#define RELOAD_PRESET1 ctrl_para.ptz.reload_preset1

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][RELOAD_PRESET1]); break;

        case MENU_LEFT:
        case MENU_RIGHT:
            onoff_toggle(&RELOAD_PRESET1);
            ctrl_ptz_reload_preset1_set(RELOAD_PRESET1);
            break;
    }
    return 0;
}

int func_Installation(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][ptz_install_butt] = {
        {L"Dail", L"Normal", L"Flip"},
        {L"拨码", L"正装", L"倒装"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            if (ctrl_para.ptz.install.cur == ptz_install_dail)
            {
                int index;
                wchar_t strPara[20] = {0};
                if (IS_DAIL_FLIP_ON())
                    index = 2;
                else
                    index = 1;
                wcscat(strPara, str[LANGUAGE_INDEX][0]);
                wcscat(strPara, L"(");
                wcscat(strPara, str[LANGUAGE_INDEX][index]);
                wcscat(strPara, L")");
                swprintf(strPara, 20, L"%ls(%ls)", str[LANGUAGE_INDEX][0], str[LANGUAGE_INDEX][index]);
                ApendParaStr(pthis->text, strPara);
            }
            else
            {
                ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.ptz.install.cur]);
            }
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.ptz.install);
            ctrl_ptz_installation_set(ctrl_para.ptz.install.cur);
            break;
        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.ptz.install);
            ctrl_ptz_installation_set(ctrl_para.ptz.install.cur);
            break;
    }
    return 0;
}

int func_PanReverse(menu_item* pthis, int todo)
{
#define PAN_REVERSE ctrl_para.ptz.pan_reverse

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][PAN_REVERSE]); break;

        case MENU_LEFT:
        case MENU_RIGHT: onoff_toggle(&PAN_REVERSE); break;
    }
    return 0;
}

int func_TiltReverse(menu_item* pthis, int todo)
{
#define TILT_REVERSE ctrl_para.ptz.tilt_reverse

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][TILT_REVERSE]); break;

        case MENU_LEFT:
        case MENU_RIGHT: onoff_toggle(&TILT_REVERSE); break;
    }
    return 0;
}

int func_Exposure(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
        case MENU_TRIGGER: break;

        case MENU_RIGHT:
        case MENU_ENTER:
            ctrl_exp_mode_get(&ctrl_para.exposure.mode.cur);
            LOG_INFO("Enter Exposure");
            NewMenu();

            switch (ctrl_para.exposure.mode.cur)
            {
                case ctrl_exp_mode_manual:
                    AddMenuItem(&menu_exposure[0]);
                    AddMenuItem(&menu_exposure[1]);
                    AddMenuItem(&menu_exposure[2]);
                    AddMenuItem(&menu_exposure[5]);
                    break;

                case ctrl_exp_mode_shutter_pri:
                    AddMenuItem(&menu_exposure[0]);
                    AddMenuItem(&menu_exposure[1]);
                    AddMenuItem(&menu_exposure[5]);
                    break;

                case ctrl_exp_mode_auto:
                default:
                    AddMenuItem(&menu_exposure[0]);
                    AddMenuItem(&menu_exposure[3]);
                    AddMenuItem(&menu_exposure[4]);
                    AddMenuItem(&menu_exposure[5]);
                    break;
            }
            ShowCurMenu();
            break;

        case MENU_LEFT:
        case MENU_BACK: break;
    }

    return 0;
}

int func_ExpMode(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][ctrl_exp_mode_butt] = {
        {
            L"Auto",
            L"Manual",
            L"Shutter Pri",
            L"Iris Pri",
            L"Gain Pri",
        },
        {L"自动", L"手动", L"快门优先", L"光圈优先", L"增益优先"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_exp_mode_get(&ctrl_para.exposure.mode.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.exposure.mode.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.exposure.mode);
            ctrl_exp_mode_set(ctrl_para.exposure.mode.cur);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.exposure.mode);
            ctrl_exp_mode_set(ctrl_para.exposure.mode.cur);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;

        case MENU_BACK: break;
    }
    return 0;
}

int func_ExpShutter(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_exp_shutter_get(&ctrl_para.exposure.shutter.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.exposure.shutter.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.exposure.shutter);
            ctrl_exp_shutter_set(ctrl_para.exposure.shutter.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.exposure.shutter);
            ctrl_exp_shutter_set(ctrl_para.exposure.shutter.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}
int func_ExpGain(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_exp_gain_get(&ctrl_para.exposure.gain.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.exposure.gain.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.exposure.gain);
            ctrl_exp_gain_set(ctrl_para.exposure.gain.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.exposure.gain);
            ctrl_exp_gain_set(ctrl_para.exposure.gain.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}

int func_ExpComp(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_exp_compensation_get(&ctrl_para.exposure.compensation.cur);
            ApendParaStr(pthis->text, NumToStringWithSymbol((ctrl_para.exposure.compensation.cur - 128) / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.exposure.compensation);
            ctrl_exp_compensation_set(ctrl_para.exposure.compensation.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.exposure.compensation);
            ctrl_exp_compensation_set(ctrl_para.exposure.compensation.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}
int func_ExpBacklight(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_exp_backlight_get(&ctrl_para.exposure.backlight);
            ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][ctrl_para.exposure.backlight]);
            break;

        case MENU_LEFT:
        case MENU_RIGHT:
            onoff_toggle(&ctrl_para.exposure.backlight);
            ctrl_exp_backlight_set(ctrl_para.exposure.backlight);
            break;
    }
    return 0;
}

int func_WhiteBalance(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
        case MENU_TRIGGER: break;

        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            ctrl_wb_mode_get(&ctrl_para.wb.mode.cur);
            switch (ctrl_para.wb.mode.cur)
            {
                case ctrl_wb_mode_onepush:
                    AddMenuItem(&menu_wb[0]);
                    AddMenuItem(&menu_wb[3]);
                    // AddMenuItem(&menu_wb[4]);
                    // AddMenuItem(&menu_wb[5]);
                    AddMenuItem(&menu_wb[4]);
                    break;

                case ctrl_wb_mode_manual:
                    AddMenuItem(&menu_wb[0]);
                    AddMenuItem(&menu_wb[1]);
                    AddMenuItem(&menu_wb[2]);
                    // AddMenuItem(&menu_wb[5]);
                    AddMenuItem(&menu_wb[4]);
                    break;

                case ctrl_wb_mode_auto:
                default:
                    AddMenuItem(&menu_wb[0]);
                    // AddMenuItem(&menu_wb[4]);
                    // AddMenuItem(&menu_wb[5]);
                    AddMenuItem(&menu_wb[4]);
                    break;
            }
            ShowCurMenu();
            break;

        case MENU_LEFT:
        case MENU_BACK: break;
    }
    return 0;
}

int func_WbMode(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][ctrl_wb_mode_butt] = {
        {L"Auto", L"Manual", L"Indoor", L"OutDoor", L"OnePush", L"ATW", L"OutDoor Auto", L"SodiumLamp Auto", L"SodiumLamp", L"SodiumLamp OutDoor Auto"},
        {L"自动", L"手动", L"室内", L"室外", L"键控", L"自动跟踪", L"室外自动", L"钠灯自动", L"钠灯", L"室外钠灯自动"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_wb_mode_get(&ctrl_para.wb.mode.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.wb.mode.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.wb.mode);
            ctrl_wb_mode_set((ctrl_wb_mode_t)ctrl_para.wb.mode.cur);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.wb.mode);
            ctrl_wb_mode_set((ctrl_wb_mode_t)ctrl_para.wb.mode.cur);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;

        case MENU_BACK: break;
    }

    return 0;
}

int func_WbRgain(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_wb_rgain_get(&ctrl_para.wb.rgain.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.wb.rgain.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.wb.rgain);
            ctrl_wb_rgain_set(ctrl_para.wb.rgain.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.wb.rgain);
            ctrl_wb_rgain_set(ctrl_para.wb.rgain.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}

int func_WbBgain(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            ctrl_wb_bgain_get(&ctrl_para.wb.bgain.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.wb.bgain.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.wb.bgain);
            ctrl_wb_bgain_set(ctrl_para.wb.bgain.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.wb.bgain);
            ctrl_wb_bgain_set(ctrl_para.wb.bgain.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}

void Menu_ShowProgress(menu_item* pthis, int num)
{
    while (num--)
    {
        ApendStr2(pthis->text, L">  ");
        ShowCurLine();
        usleep(1000 * 300);
        ApendStr2(pthis->text, L">> ");
        ShowCurLine();
        usleep(1000 * 300);
        ApendStr2(pthis->text, L">>>");
        ShowCurLine();
        usleep(1000 * 300);
        ApendStr2(pthis->text, L"   ");
        ShowCurLine();
    }
}

int func_WbTrigger(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            ctrl_wb_trigger();
            Menu_ShowProgress(pthis, 1);
            break;
    }
    return 0;
}

int func_WbAutoCorrection(menu_item* pthis, int todo)
{
    // static int mode = 0;

    // switch (todo)
    // {
    //     case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][mode]); break;

    //     case MENU_LEFT:
    //     case MENU_RIGHT:
    //         if (mode == 0)
    //             mode = 1;
    //         else
    //             mode = 0;
    //         break;

    //     case MENU_BACK: break;
    // }
    return 0;
}

int func_WbManualCorrection(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER: Menu_ShowProgress(pthis, 1); mcu_clear_input_buffer();
    }
    return 0;
}

int func_Image(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            int count = sizeof(menu_image) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (AddMenuItem(&menu_image[i]))
                    return 1;
            }
            ShowCurMenu();
            break;
    }

    return 0;
}

int func_Image2DNr(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_2dnr_get(&ctrl_para.image.nr2d.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.nr2d.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.nr2d);
            image_2dnr_set(ctrl_para.image.nr2d.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.nr2d);
            image_2dnr_set(ctrl_para.image.nr2d.cur);
            break;
    }

    return 0;
}
int func_Image3DNr(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_3dnr_get(&ctrl_para.image.nr3d.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.nr3d.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.nr3d);
            image_3dnr_set(ctrl_para.image.nr3d.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.nr3d);
            image_3dnr_set(ctrl_para.image.nr3d.cur);
            break;
    }

    return 0;
}

int func_ImageBright(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_bright_get(&ctrl_para.image.bright.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.bright.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.bright);
            image_bright_set(ctrl_para.image.bright.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.bright);
            image_bright_set(ctrl_para.image.bright.cur);
            break;

        case MENU_BACK: break;
    }
    return 0;
}

int func_ImageContrast(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_contrast_get(&ctrl_para.image.contrast.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.contrast.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.contrast);
            image_contrast_set(ctrl_para.image.contrast.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.contrast);
            image_contrast_set(ctrl_para.image.contrast.cur);
            break;
    }

    return 0;
}
int func_ImageColorGain(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_saturation_get(&ctrl_para.image.saturation.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.saturation.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.saturation);
            image_saturation_set(ctrl_para.image.saturation.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.saturation);
            image_saturation_set(ctrl_para.image.saturation.cur);
            break;
    }

    return 0;
}

int func_ImageSharpness(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_sharpness_get(&ctrl_para.image.sharpness.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.sharpness.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.sharpness);
            image_sharpness_set(ctrl_para.image.sharpness.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.sharpness);
            image_sharpness_set(ctrl_para.image.sharpness.cur);
            break;
    }

    return 0;
}

int func_ImageHUE(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_hue_get(&ctrl_para.image.hue.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.hue.cur / 16));
            break;

        case MENU_LEFT:
            s32var_sub_16_cycle(&ctrl_para.image.hue);
            image_hue_set(ctrl_para.image.hue.cur);
            break;

        case MENU_RIGHT:
            s32var_add_16_cycle(&ctrl_para.image.hue);
            image_hue_set(ctrl_para.image.hue.cur);
            break;
    }

    return 0;
}

int func_ImageGamma(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_gamma_get(&ctrl_para.image.gamma.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.gamma.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.image.gamma);
            image_gamma_set(ctrl_para.image.gamma.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.image.gamma);
            image_gamma_set(ctrl_para.image.gamma.cur);
            break;
    }

    return 0;
}
int func_ImageWDR(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH:
            image_wdr_get(&ctrl_para.image.wdr.cur);
            ApendParaStr(pthis->text, NumToString(ctrl_para.image.wdr.cur));
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.image.wdr);
            image_wdr_set(ctrl_para.image.wdr.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.image.wdr);
            image_wdr_set(ctrl_para.image.wdr.cur);
            break;
    }

    return 0;
}

int func_ImageEffect(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][image_effect_butt] = {
        {L"Normal", L"Black&White"},
        {L"正常", L"黑白"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            image_effect_get(&ctrl_para.image.effect.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.image.effect.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.image.effect);
            image_effect_set(ctrl_para.image.effect.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.image.effect);
            image_effect_set(ctrl_para.image.effect.cur);
            break;
    }
    return 0;
}

int func_ImageDeFlicker(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][image_deflicker_butt] = {
        {L"OFF", L"50Hz", L"60Hz"},
        {L"关", L"50Hz", L"60Hz"},
    };

    switch (todo)
    {
        case MENU_REFRESH:
            image_deflicker_get(&ctrl_para.image.deflicker.cur);
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][ctrl_para.image.deflicker.cur]);
            break;

        case MENU_LEFT:
            s32var_sub_cycle(&ctrl_para.image.deflicker);
            image_deflicker_set(ctrl_para.image.deflicker.cur);
            break;

        case MENU_RIGHT:
            s32var_add_cycle(&ctrl_para.image.deflicker);
            image_deflicker_set(ctrl_para.image.deflicker.cur);
            break;
    }

    return 0;
}

int func_ImageFlip(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][ctrl_para.image.flip]); break;

        case MENU_LEFT:
        case MENU_RIGHT:
            onoff_toggle(&ctrl_para.image.flip);
            image_flip_set(ctrl_para.image.flip);
            break;
    }

    return 0;
}

int func_ImageMirror(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][ctrl_para.image.mirror]); break;

        case MENU_LEFT:
        case MENU_RIGHT:
            onoff_toggle(&ctrl_para.image.mirror);
            image_mirror_set(ctrl_para.image.mirror);
            break;
    }

    return 0;
}

int func_System(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            int count = sizeof(menu_system) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (AddMenuItem(&menu_system[i]))
                    return 1;
            }
            ShowCurMenu();
            break;
    }

    return 0;
}

int func_Language(menu_item* pthis, int todo)
{
    const wchar_t* str[MENU_LANG_COUNT][system_language_butt] = {
        {L"English", L"简体中文"},
        {L"English", L"简体中文"},
    };

    int language;
    switch (todo)
    {
        case MENU_REFRESH:
            language = ctrl_para.system.language;
            ApendParaStr(pthis->text, str[LANGUAGE_INDEX][language]);
            break;

        case MENU_RIGHT:
            language = ctrl_para.system.language;
            if (++language > system_language_zh_cn)
                language = system_language_english;
            ctrl_system_language_set((system_language_t)language);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;

        case MENU_LEFT:
            language = ctrl_para.system.language;
            if (--language < system_language_english)
                language = system_language_zh_cn;
            ctrl_system_language_set((system_language_t)language);
            DeletMenu();
            Menu_ExeFunc(MENU_ENTER);
            break;
    }
    return 0;
}

int func_LensRevis(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            ctrl_ptz_lens_revise();
            Menu_ShowProgress(pthis, 1);
            mcu_clear_input_buffer();
            break;
    }
    return 0;
}

int func_Aging(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, strOnoff[LANGUAGE_INDEX][ctrl_para.system.aging]); break;

        case MENU_LEFT:
        case MENU_RIGHT: onoff_toggle(&ctrl_para.system.aging); break;
    }

    return 0;
}

int func_PtzAdvance(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            int count = sizeof(menu_ptz_advance) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (ctrl_status.fx)
                {
                    if (i == 0 || i == 1)
                    {
                        continue;
                    }
                }
                if (AddMenuItem(&menu_ptz_advance[i]))
                    return 1;
            }
            ShowCurMenu();
            break;
    }

    return 0;
}
int func_ZoomSpeed(menu_item* pthis, int todo)
{
#define ZOOM_SPEED_CUR ctrl_para.ptz.zoom_speed.cur

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(ZOOM_SPEED_CUR)); break;

        case MENU_LEFT: s32var_sub_cycle(&ctrl_para.ptz.zoom_speed); break;

        case MENU_RIGHT: s32var_add_cycle(&ctrl_para.ptz.zoom_speed); break;
    }
    return 0;
}
int func_FocusSpeed(menu_item* pthis, int todo)
{
#define FOCUS_SPEED_CUR ctrl_para.ptz.focus_speed.cur

    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(FOCUS_SPEED_CUR)); break;

        case MENU_LEFT: s32var_sub_cycle(&ctrl_para.ptz.focus_speed); break;

        case MENU_RIGHT: s32var_add_cycle(&ctrl_para.ptz.focus_speed); break;
    }
    return 0;
}
int func_PanAcc(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.pan;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->acc_cur)); break;

        case MENU_LEFT:
            if (--p_para->acc_cur < p_para->acc_min)
                p_para->acc_cur = p_para->acc_max;
            ctrl_ptz_pan_set_accdec(p_para->acc_cur, p_para->dec_cur);
            break;

        case MENU_RIGHT:
            if (++p_para->acc_cur > p_para->acc_max)
                p_para->acc_cur = p_para->acc_min;
            ctrl_ptz_pan_set_accdec(p_para->acc_cur, p_para->dec_cur);
            break;
    }
    return 0;
}
int func_PanDec(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.pan;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->dec_cur)); break;

        case MENU_LEFT:
            if (--p_para->dec_cur < p_para->dec_min)
                p_para->dec_cur = p_para->dec_max;
            ctrl_ptz_pan_set_accdec(p_para->acc_cur, p_para->dec_cur);
            break;

        case MENU_RIGHT:
            if (++p_para->dec_cur > p_para->dec_max)
                p_para->dec_cur = p_para->dec_min;
            ctrl_ptz_pan_set_accdec(p_para->acc_cur, p_para->dec_cur);
            break;
    }
    return 0;
}
int func_PanBrake(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.pan;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->brake_cur)); break;

        case MENU_LEFT:
            if (--p_para->brake_cur < p_para->brake_min)
                p_para->brake_cur = p_para->brake_max;
            break;

        case MENU_RIGHT:
            if (++p_para->brake_cur > p_para->brake_max)
                p_para->brake_cur = p_para->brake_min;
            break;
    }
    return 0;
}
int func_TiltAcc(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.tilt;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->acc_cur)); break;

        case MENU_LEFT:
            if (--p_para->acc_cur < p_para->acc_min)
                p_para->acc_cur = p_para->acc_max;
            break;

        case MENU_RIGHT:
            if (++p_para->acc_cur > p_para->acc_max)
                p_para->acc_cur = p_para->acc_min;
            break;
    }
    return 0;
}
int func_TiltDec(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.tilt;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->dec_cur)); break;

        case MENU_LEFT:
            if (--p_para->dec_cur < p_para->dec_min)
                p_para->dec_cur = p_para->dec_max;
            break;

        case MENU_RIGHT:
            if (++p_para->dec_cur > p_para->dec_max)
                p_para->dec_cur = p_para->dec_min;
            break;
    }
    return 0;
}
int func_TiltBrake(menu_item* pthis, int todo)
{
    motor_para_t* p_para = &ctrl_para.ptz.tilt;
    switch (todo)
    {
        case MENU_REFRESH: ApendParaStr(pthis->text, NumToString(p_para->brake_cur)); break;

        case MENU_LEFT:
            if (--p_para->brake_cur < p_para->brake_min)
                p_para->brake_cur = p_para->brake_max;
            break;

        case MENU_RIGHT:
            if (++p_para->brake_cur > p_para->brake_max)
                p_para->brake_cur = p_para->brake_min;
            break;
    }
    return 0;
}

int func_Version(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH: {
            version_t ver;
            wchar_t str[10] = {0};
            if (ctrl_api.system_req == NULL || ctrl_api.get_version(&ver))
            {
                LOG_ERROR("get_version api not found or failed!");
                wcscat(str, L"V0.0.0");
            }
            else
            {
                wcscat(str, L"V0.0.0");
                swprintf(str, 9, L"V%d.%d.%d", ver.major, ver.minor, ver.revise);
            }
            ApendStr2(pthis->text, str);
        }
        break;

        case 7: {
            NewMenu();
            int count = sizeof(menu_hide) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (AddMenuItem(&menu_hide[i]))
                    return 1;
            }
            ShowCurMenu();
        }
        break;

        case 0: {
            NewMenu();
            int count = sizeof(menu_info_advance) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (AddMenuItem(&menu_info_advance[i]))
                    return 1;
            }
            ShowCurMenu();
        }
        break;
    }
    return 0;
}

int func_ResetDevice(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            NewMenu();
            int count = sizeof(menu_reset) / sizeof(struct menu_content);
            for (int i = 0; i < count; i++)
            {
                if (AddMenuItem(&menu_reset[i]))
                    return 1;
            }
            ShowCurMenu();
            break;
    }

    return 0;
}

int func_CtrlVersion(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_REFRESH: {
            ApendStr2(pthis->text, CTRL_VER_STR);
        }
        break;
    }
    return 0;
}


int func_McuVersion(menu_item* pthis, int todo)
{
    wchar_t buf[10] = L"";
    switch (todo)
    {
        case MENU_REFRESH: {
            swprintf(buf, 10, L"%d", ctrl_status.mcu_release);
            ApendStr2(pthis->text, buf);
        }
        break;
    }
    return 0;
}

int func_ResetImage(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            load_isp_default();
            Menu_ShowProgress(pthis, 1);
            mcu_clear_input_buffer();
            break;
    }
    return 0;
}
int func_CompleteReset(menu_item* pthis, int todo)
{
    switch (todo)
    {
        case MENU_RIGHT:
        case MENU_ENTER:
            Menu_ShowProgress(pthis, 1);
            Ctrl_FullResetDevice();
            usleep(500000);
            mcu_clear_input_buffer();
            break;
    }
    return 0;
}