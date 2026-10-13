/*
 * static_model.c
 *
 * automatically generated from empelas_mu.icd
 */
#include "static_model.h"

static void initializeValues();

extern DataSet iedModelds_MU01_LLN0_PhsMeas1;
extern DataSet iedModelds_MU01_LLN0_dsEventos;


extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda0;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda1;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda2;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda3;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda4;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda5;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda6;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda7;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda8;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda9;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda10;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda11;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda12;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda13;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda14;
extern DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda15;

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda0 = {
  "MU01",
  false,
  "TCTR1$MX$Amp$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda1
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda1 = {
  "MU01",
  false,
  "TCTR1$MX$Amp$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda2
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda2 = {
  "MU01",
  false,
  "TCTR2$MX$Amp$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda3
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda3 = {
  "MU01",
  false,
  "TCTR2$MX$Amp$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda4
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda4 = {
  "MU01",
  false,
  "TCTR3$MX$Amp$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda5
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda5 = {
  "MU01",
  false,
  "TCTR3$MX$Amp$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda6
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda6 = {
  "MU01",
  false,
  "TCTR4$MX$Amp$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda7
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda7 = {
  "MU01",
  false,
  "TCTR4$MX$Amp$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda8
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda8 = {
  "MU01",
  false,
  "TVTR1$MX$Vol$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda9
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda9 = {
  "MU01",
  false,
  "TVTR1$MX$Vol$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda10
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda10 = {
  "MU01",
  false,
  "TVTR2$MX$Vol$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda11
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda11 = {
  "MU01",
  false,
  "TVTR2$MX$Vol$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda12
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda12 = {
  "MU01",
  false,
  "TVTR3$MX$Vol$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda13
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda13 = {
  "MU01",
  false,
  "TVTR3$MX$Vol$q", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda14
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda14 = {
  "MU01",
  false,
  "TVTR4$MX$Vol$instMag$i", 
  -1,
  NULL,
  NULL,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda15
};

DataSetEntry iedModelds_MU01_LLN0_PhsMeas1_fcda15 = {
  "MU01",
  false,
  "TVTR4$MX$Vol$q", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_MU01_LLN0_PhsMeas1 = {
  "MU01",
  "LLN0$PhsMeas1",
  16,
  &iedModelds_MU01_LLN0_PhsMeas1_fcda0,
  &iedModelds_MU01_LLN0_dsEventos
};

extern DataSetEntry iedModelds_MU01_LLN0_dsEventos_fcda0;

DataSetEntry iedModelds_MU01_LLN0_dsEventos_fcda0 = {
  "MU01",
  false,
  "FLTGGIO1$ST$SPCSO1", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_MU01_LLN0_dsEventos = {
  "MU01",
  "LLN0$dsEventos",
  1,
  &iedModelds_MU01_LLN0_dsEventos_fcda0,
  NULL
};

LogicalDevice iedModel_MU01 = {
    LogicalDeviceModelType,
    "MU01",
    (ModelNode*) &iedModel,
    NULL,
    (ModelNode*) &iedModel_MU01_LLN0,
    NULL
};

LogicalNode iedModel_MU01_LLN0 = {
    LogicalNodeModelType,
    "LLN0",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_LPHD1,
    (ModelNode*) &iedModel_MU01_LLN0_Mod,
};

DataObject iedModel_MU01_LLN0_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_MU01_LLN0,
    (ModelNode*) &iedModel_MU01_LLN0_Beh,
    (ModelNode*) &iedModel_MU01_LLN0_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_LLN0_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_LLN0_Mod,
    (ModelNode*) &iedModel_MU01_LLN0_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_LLN0_Mod,
    (ModelNode*) &iedModel_MU01_LLN0_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_LLN0_Mod,
    (ModelNode*) &iedModel_MU01_LLN0_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MU01_LLN0_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LLN0_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_LLN0,
    (ModelNode*) &iedModel_MU01_LLN0_Health,
    (ModelNode*) &iedModel_MU01_LLN0_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_LLN0_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_LLN0_Beh,
    (ModelNode*) &iedModel_MU01_LLN0_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_LLN0_Beh,
    (ModelNode*) &iedModel_MU01_LLN0_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_LLN0_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LLN0_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MU01_LLN0,
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt,
    (ModelNode*) &iedModel_MU01_LLN0_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_LLN0_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_LLN0_Health,
    (ModelNode*) &iedModel_MU01_LLN0_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_LLN0_Health,
    (ModelNode*) &iedModel_MU01_LLN0_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_LLN0_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LLN0_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MU01_LLN0,
    NULL,
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MU01_LLN0_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt,
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt,
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt,
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LLN0_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MU01_LLN0_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_LPHD1 = {
    LogicalNodeModelType,
    "LPHD1",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TCTR1,
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt,
};

DataObject iedModel_MU01_LPHD1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MU01_LPHD1,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyNam,
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MU01_LPHD1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MU01_LPHD1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LPHD1_PhyNam = {
    DataObjectModelType,
    "PhyNam",
    (ModelNode*) &iedModel_MU01_LPHD1,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyNam_vendor,
    0,
    -1
};

DataAttribute iedModel_MU01_LPHD1_PhyNam_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MU01_LPHD1_PhyNam,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyNam_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_PhyNam_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_MU01_LPHD1_PhyNam,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LPHD1_PhyHealth = {
    DataObjectModelType,
    "PhyHealth",
    (ModelNode*) &iedModel_MU01_LPHD1,
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_LPHD1_PhyHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_PhyHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_PhyHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_LPHD1_PhyHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_LPHD1_Proxy = {
    DataObjectModelType,
    "Proxy",
    (ModelNode*) &iedModel_MU01_LPHD1,
    NULL,
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_LPHD1_Proxy_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy,
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_Proxy_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy,
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_LPHD1_Proxy_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_LPHD1_Proxy,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TCTR1 = {
    LogicalNodeModelType,
    "TCTR1",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TCTR2,
    (ModelNode*) &iedModel_MU01_TCTR1_Beh,
};

DataObject iedModel_MU01_TCTR1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TCTR1,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp,
    (ModelNode*) &iedModel_MU01_TCTR1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TCTR1_Beh,
    (ModelNode*) &iedModel_MU01_TCTR1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR1_Beh,
    (ModelNode*) &iedModel_MU01_TCTR1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TCTR1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TCTR1_Amp = {
    DataObjectModelType,
    "Amp",
    (ModelNode*) &iedModel_MU01_TCTR1,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR1_Amp_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_q,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Amp_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Amp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Amp_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Amp_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_sVC,
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR1_Amp_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TCTR1_Amp_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TCTR2 = {
    LogicalNodeModelType,
    "TCTR2",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TCTR3,
    (ModelNode*) &iedModel_MU01_TCTR2_Beh,
};

DataObject iedModel_MU01_TCTR2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TCTR2,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp,
    (ModelNode*) &iedModel_MU01_TCTR2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TCTR2_Beh,
    (ModelNode*) &iedModel_MU01_TCTR2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR2_Beh,
    (ModelNode*) &iedModel_MU01_TCTR2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TCTR2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TCTR2_Amp = {
    DataObjectModelType,
    "Amp",
    (ModelNode*) &iedModel_MU01_TCTR2,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR2_Amp_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_q,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Amp_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Amp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Amp_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Amp_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_sVC,
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR2_Amp_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TCTR2_Amp_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TCTR3 = {
    LogicalNodeModelType,
    "TCTR3",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TCTR4,
    (ModelNode*) &iedModel_MU01_TCTR3_Beh,
};

DataObject iedModel_MU01_TCTR3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TCTR3,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp,
    (ModelNode*) &iedModel_MU01_TCTR3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TCTR3_Beh,
    (ModelNode*) &iedModel_MU01_TCTR3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR3_Beh,
    (ModelNode*) &iedModel_MU01_TCTR3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TCTR3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TCTR3_Amp = {
    DataObjectModelType,
    "Amp",
    (ModelNode*) &iedModel_MU01_TCTR3,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR3_Amp_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_q,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Amp_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Amp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Amp_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Amp_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_sVC,
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR3_Amp_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TCTR3_Amp_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TCTR4 = {
    LogicalNodeModelType,
    "TCTR4",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TVTR1,
    (ModelNode*) &iedModel_MU01_TCTR4_Beh,
};

DataObject iedModel_MU01_TCTR4_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TCTR4,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp,
    (ModelNode*) &iedModel_MU01_TCTR4_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR4_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TCTR4_Beh,
    (ModelNode*) &iedModel_MU01_TCTR4_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR4_Beh,
    (ModelNode*) &iedModel_MU01_TCTR4_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TCTR4_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TCTR4_Amp = {
    DataObjectModelType,
    "Amp",
    (ModelNode*) &iedModel_MU01_TCTR4,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TCTR4_Amp_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_q,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Amp_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Amp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Amp_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp,
    NULL,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Amp_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_sVC,
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TCTR4_Amp_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TCTR4_Amp_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TVTR1 = {
    LogicalNodeModelType,
    "TVTR1",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TVTR2,
    (ModelNode*) &iedModel_MU01_TVTR1_Beh,
};

DataObject iedModel_MU01_TVTR1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TVTR1,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol,
    (ModelNode*) &iedModel_MU01_TVTR1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TVTR1_Beh,
    (ModelNode*) &iedModel_MU01_TVTR1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR1_Beh,
    (ModelNode*) &iedModel_MU01_TVTR1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TVTR1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TVTR1_Vol = {
    DataObjectModelType,
    "Vol",
    (ModelNode*) &iedModel_MU01_TVTR1,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR1_Vol_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_q,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Vol_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Vol_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Vol_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Vol_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_sVC,
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR1_Vol_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TVTR1_Vol_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TVTR2 = {
    LogicalNodeModelType,
    "TVTR2",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TVTR3,
    (ModelNode*) &iedModel_MU01_TVTR2_Beh,
};

DataObject iedModel_MU01_TVTR2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TVTR2,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol,
    (ModelNode*) &iedModel_MU01_TVTR2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TVTR2_Beh,
    (ModelNode*) &iedModel_MU01_TVTR2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR2_Beh,
    (ModelNode*) &iedModel_MU01_TVTR2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TVTR2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TVTR2_Vol = {
    DataObjectModelType,
    "Vol",
    (ModelNode*) &iedModel_MU01_TVTR2,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR2_Vol_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_q,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Vol_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Vol_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Vol_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Vol_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_sVC,
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR2_Vol_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TVTR2_Vol_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TVTR3 = {
    LogicalNodeModelType,
    "TVTR3",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_TVTR4,
    (ModelNode*) &iedModel_MU01_TVTR3_Beh,
};

DataObject iedModel_MU01_TVTR3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TVTR3,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol,
    (ModelNode*) &iedModel_MU01_TVTR3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TVTR3_Beh,
    (ModelNode*) &iedModel_MU01_TVTR3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR3_Beh,
    (ModelNode*) &iedModel_MU01_TVTR3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TVTR3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TVTR3_Vol = {
    DataObjectModelType,
    "Vol",
    (ModelNode*) &iedModel_MU01_TVTR3,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR3_Vol_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_q,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Vol_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Vol_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Vol_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Vol_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_sVC,
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR3_Vol_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TVTR3_Vol_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_TVTR4 = {
    LogicalNodeModelType,
    "TVTR4",
    (ModelNode*) &iedModel_MU01,
    (ModelNode*) &iedModel_MU01_FLTGGIO1,
    (ModelNode*) &iedModel_MU01_TVTR4_Beh,
};

DataObject iedModel_MU01_TVTR4_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_TVTR4,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol,
    (ModelNode*) &iedModel_MU01_TVTR4_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR4_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_TVTR4_Beh,
    (ModelNode*) &iedModel_MU01_TVTR4_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR4_Beh,
    (ModelNode*) &iedModel_MU01_TVTR4_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_TVTR4_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_TVTR4_Vol = {
    DataObjectModelType,
    "Vol",
    (ModelNode*) &iedModel_MU01_TVTR4,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_instMag,
    0,
    -1
};

DataAttribute iedModel_MU01_TVTR4_Vol_instMag = {
    DataAttributeModelType,
    "instMag",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_q,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_instMag_i,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Vol_instMag_i = {
    DataAttributeModelType,
    "i",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_instMag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_INT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Vol_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_sVC,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Vol_sVC = {
    DataAttributeModelType,
    "sVC",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol,
    NULL,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_sVC_scaleFactor,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Vol_sVC_scaleFactor = {
    DataAttributeModelType,
    "scaleFactor",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_sVC,
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_sVC_offset,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_TVTR4_Vol_sVC_offset = {
    DataAttributeModelType,
    "offset",
    (ModelNode*) &iedModel_MU01_TVTR4_Vol_sVC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_FLOAT32,
    0,
    NULL,
    0};

LogicalNode iedModel_MU01_FLTGGIO1 = {
    LogicalNodeModelType,
    "FLTGGIO1",
    (ModelNode*) &iedModel_MU01,
    NULL,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh,
};

DataObject iedModel_MU01_FLTGGIO1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MU01_FLTGGIO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_FLTGGIO1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_FLTGGIO1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MU01_FLTGGIO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_FLTGGIO1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MU01_FLTGGIO1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MU01_FLTGGIO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MU01_FLTGGIO1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MU01_FLTGGIO1_SPCSO1 = {
    DataObjectModelType,
    "SPCSO1",
    (ModelNode*) &iedModel_MU01_FLTGGIO1,
    NULL,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_stVal,
    0,
    -1
};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1,
    NULL,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_ctlNum,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_MU01_FLTGGIO1_SPCSO1_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_MU01_FLTGGIO1_SPCSO1_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

extern ReportControlBlock iedModel_MU01_LLN0_report0;
extern ReportControlBlock iedModel_MU01_LLN0_report1;

ReportControlBlock iedModel_MU01_LLN0_report0 = {&iedModel_MU01_LLN0, "brcbEventos01", "EmpElas_MU_Eventos", true, "dsEventos", 1, 19, 255, 50, 0, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_MU01_LLN0_report1};
ReportControlBlock iedModel_MU01_LLN0_report1 = {&iedModel_MU01_LLN0, "brcbEventos02", "EmpElas_MU_Eventos", true, "dsEventos", 1, 19, 255, 50, 0, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, NULL};

extern SVControlBlock iedModel_MU01_LLN0_smv0;

static PhyComAddress iedModel_MU01_LLN0_smv0_address = {
  4,
  0,
  16384,
  {0x1, 0xc, 0xcd, 0x4, 0x0, 0x1}
};

SVControlBlock iedModel_MU01_LLN0_smv0 = {&iedModel_MU01_LLN0, "MSVCB01", "EmpElas_MU01", "PhsMeas1", 2, 0, 80, 1, &iedModel_MU01_LLN0_smv0_address, false, 1, NULL};






IedModel iedModel = {
    "EmpElas_MU",
    &iedModel_MU01,
    &iedModelds_MU01_LLN0_PhsMeas1,
    &iedModel_MU01_LLN0_report0,
    NULL,
    &iedModel_MU01_LLN0_smv0,
    NULL,
    NULL,
    NULL,
    initializeValues
};

static void
initializeValues()
{

iedModel_MU01_TCTR1_Amp_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.001);

iedModel_MU01_TCTR1_Amp_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TCTR2_Amp_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.001);

iedModel_MU01_TCTR2_Amp_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TCTR3_Amp_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.001);

iedModel_MU01_TCTR3_Amp_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TCTR4_Amp_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.001);

iedModel_MU01_TCTR4_Amp_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TVTR1_Vol_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.01);

iedModel_MU01_TVTR1_Vol_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TVTR2_Vol_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.01);

iedModel_MU01_TVTR2_Vol_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TVTR3_Vol_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.01);

iedModel_MU01_TVTR3_Vol_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_TVTR4_Vol_sVC_scaleFactor.mmsValue = MmsValue_newFloat(0.01);

iedModel_MU01_TVTR4_Vol_sVC_offset.mmsValue = MmsValue_newFloat(0.0);

iedModel_MU01_FLTGGIO1_NamPlt_d.mmsValue = MmsValue_newVisibleString("Arvore na linha: falta fase-terra na fase A (simulacao didatica)");

iedModel_MU01_FLTGGIO1_SPCSO1_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(1);
}
