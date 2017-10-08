#ifndef DATADEF_H
#define DATADEF_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <QString>

#define UNDEPRESS "[bar] Press 1"
#define CALCPRESS "[bar] Press 2"
#define OVERPRESS "[bar] Press 3"

#define _SERIALCMD_MCU_CHECKSTART_          0X8200
#define _SERIALCMD_MCU_CHECKSTATE_          0X8202
#define _SERIALCMD_MCU_CHECKRESUALT_        0X8203

#define _SERIALCMD_MCU_START_               0X8300
#define _SERIALCMD_MCU_NAOH_                0X8301
#define _SERIALCMD_MCU_STOP_                0X8302
#define _SERIALCMD_MCU_ASK_                 0X8303
#define _SERIALCMD_MCU_ZHENGLIU             0X8304
#define _SERIALCMD_MCU_PAUSE_               0X8305
#define _SERIALCMD_MCU_RENEW_               0X8306

#define _SERIALCMD_MCU_DEBUG_COLORS_        0X8701

#define _SERIALCMD_MCU_CLEAN_STOP_          0X8500
#define _SERIALCMD_MCU_CLEAN_JIESHOUBEI_    0X8501
#define _SERIALCMD_MCU_CLEAN_XIAOHUA_       0X8502
#define _SERIALCMD_MCU_CLEAN_HUANSUAN_      0X8503
#define _SERIALCMD_MCU_CLEAN_JIANGUAN_      0X8504
#define _SERIALCMD_MCU_CLEAN_PENGSUAN_      0X8505
#define _SERIALCMD_MCU_CLEAN_AUTO_          0X8506


#define _SERIALCMD_MCU_STATE_   0X8801

#define _SERIALCMD_MCU_STATEPENGSUAN_     0X01
#define _SERIALCMD_MCU_STATEXISHISHUI_    0X02
#define _SERIALCMD_MCU_STATENAOH_         0X03
#define _SERIALCMD_MCU_STATEZHENGLIU_     0X04
#define _SERIALCMD_MCU_STATEDIDING_       0X05
#define _SERIALCMD_MCU_STATEPAIFEI_       0X06
#define _SERIALCMD_MCU_STATEEND_          0X08

#define _SERIALCMD_PC_START_    0X0300
#define _SERIALCMD_PC_NAOH_     0X0301
#define _SERIALCMD_PC_STOP_     0X0302
#define _SERIALCMD_PC_ASK_      0X0303
#define _SERIALCMD_PC_ZHENGLIU  0X0304

enum SAMPLETYPE{
    _enumEmpty,  //0
    _enumSample
};

enum SAMPLENUMBERTYPE{
    _enum_Sampleml,    //0
    _enum_Sampleg
};

enum RESUALTTYPE{
    _enum_Resualtml,   //0
    _enum_Nitrongen,
    _enum_XPreotein,
    _enum_mgNkg,
    _enum_mgNg,
    _enum_mgNH3kg,
    _enum_mgN,
    _enum_mgNml,
    _enum_mgN100ml,
    _enum_XRecovery,
    _enum_mgPreotein,
    _enum_mgN100g,
    _enum_gNkg,
};

struct TestData{
    QString     m_strName;
    QString     m_strpihao;
    SAMPLETYPE  m_enumSampleType;
    float       m_fSampleNumber;
    SAMPLENUMBERTYPE    m_enumSampleNumberType;
    RESUALTTYPE m_enumResualtType;
    float       m_fEmptyvolum;
    float       m_fdiding;
    QString     m_strNote;
};

struct TestMethod{
    QString m_name;
    qint64 m_id;
    qint64 m_pici;
    qint64  m_ipengsuan;
    qint64  m_ixishishui;
    qint64  m_ijian;
    qint64  m_izhengliu;
    qint64  m_imls;
    qint64  m_ididing;
    qint64  m_ijiajian;
    qint64  m_izhengqi;
    qint64  m_ixiaohuaguan;
    qint64  m_ijieshoubei;
    qint64  m_ilengningshui;
    qint64  m_idanbaixishu;
};

struct MachineSetting{
QString     m_strfdingbiaoqishu;
QString     m_strbprinter;
QString     m_strbzijian;
QString     m_strblengningshui;
QString     m_strbhuansuan;
QString     m_strffangfaxishu;
QString     m_strfzhusaibeng;
};

#endif // DATADEF_H
