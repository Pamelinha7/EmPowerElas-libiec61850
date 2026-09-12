/*
 * static_model.c
 *
 * automatically generated from empelas_ctrl.icd
 */
#include "static_model.h"

static void initializeValues();



LogicalDevice iedModel_VAO = {
    LogicalDeviceModelType,
    "VAO",
    (ModelNode*) &iedModel,
    NULL,
    (ModelNode*) &iedModel_VAO_LLN0,
    NULL
};

LogicalNode iedModel_VAO_LLN0 = {
    LogicalNodeModelType,
    "LLN0",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LLN0_Mod,
};

DataObject iedModel_VAO_LLN0_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_LLN0,
    (ModelNode*) &iedModel_VAO_LLN0_Beh,
    (ModelNode*) &iedModel_VAO_LLN0_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LLN0_Mod,
    (ModelNode*) &iedModel_VAO_LLN0_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LLN0_Mod,
    (ModelNode*) &iedModel_VAO_LLN0_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LLN0_Mod,
    (ModelNode*) &iedModel_VAO_LLN0_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LLN0_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LLN0_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_LLN0,
    (ModelNode*) &iedModel_VAO_LLN0_Health,
    (ModelNode*) &iedModel_VAO_LLN0_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LLN0_Beh,
    (ModelNode*) &iedModel_VAO_LLN0_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LLN0_Beh,
    (ModelNode*) &iedModel_VAO_LLN0_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LLN0_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LLN0_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_LLN0,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    (ModelNode*) &iedModel_VAO_LLN0_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LLN0_Health,
    (ModelNode*) &iedModel_VAO_LLN0_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LLN0_Health,
    (ModelNode*) &iedModel_VAO_LLN0_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LLN0_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LLN0_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_LLN0,
    (ModelNode*) &iedModel_VAO_LLN0_Diag,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_LLN0_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LLN0_Diag = {
    DataObjectModelType,
    "Diag",
    (ModelNode*) &iedModel_VAO_LLN0,
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs,
    (ModelNode*) &iedModel_VAO_LLN0_Diag_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_Diag_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LLN0_Diag,
    (ModelNode*) &iedModel_VAO_LLN0_Diag_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Diag_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LLN0_Diag,
    (ModelNode*) &iedModel_VAO_LLN0_Diag_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Diag_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LLN0_Diag,
    (ModelNode*) &iedModel_VAO_LLN0_Diag_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_Diag_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LLN0_Diag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LLN0_LEDRs = {
    DataObjectModelType,
    "LEDRs",
    (ModelNode*) &iedModel_VAO_LLN0,
    NULL,
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LLN0_LEDRs_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs,
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_LEDRs_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs,
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_LEDRs_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs,
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LLN0_LEDRs_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LLN0_LEDRs,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_LPHD1 = {
    LogicalNodeModelType,
    "LPHD1",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
};

DataObject iedModel_VAO_LPHD1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyNam,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_LPHD1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_PhyNam = {
    DataObjectModelType,
    "PhyNam",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyNam_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_PhyNam_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_LPHD1_PhyNam,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyNam_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_PhyNam_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_VAO_LPHD1_PhyNam,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_PhyHealth = {
    DataObjectModelType,
    "PhyHealth",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_PhyHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_PhyHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_PhyHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LPHD1_PhyHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_OutOv = {
    DataObjectModelType,
    "OutOv",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy,
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_OutOv_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv,
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_OutOv_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv,
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_OutOv_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv,
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_OutOv_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LPHD1_OutOv,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_Proxy = {
    DataObjectModelType,
    "Proxy",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh,
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_Proxy_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy,
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Proxy_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy,
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Proxy_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy,
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Proxy_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LPHD1_Proxy,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_OpTmh = {
    DataObjectModelType,
    "OpTmh",
    (ModelNode*) &iedModel_VAO_LPHD1,
    (ModelNode*) &iedModel_VAO_LPHD1_Sim,
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_OpTmh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh,
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_OpTmh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh,
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_OpTmh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LPHD1_OpTmh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LPHD1_Sim = {
    DataObjectModelType,
    "Sim",
    (ModelNode*) &iedModel_VAO_LPHD1,
    NULL,
    (ModelNode*) &iedModel_VAO_LPHD1_Sim_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LPHD1_Sim_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LPHD1_Sim,
    (ModelNode*) &iedModel_VAO_LPHD1_Sim_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Sim_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LPHD1_Sim,
    (ModelNode*) &iedModel_VAO_LPHD1_Sim_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Sim_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LPHD1_Sim,
    (ModelNode*) &iedModel_VAO_LPHD1_Sim_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LPHD1_Sim_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LPHD1_Sim,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_LGOS1 = {
    LogicalNodeModelType,
    "LGOS1",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LGOS1_Beh,
};

DataObject iedModel_VAO_LGOS1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_Health,
    (ModelNode*) &iedModel_VAO_LGOS1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_Beh,
    (ModelNode*) &iedModel_VAO_LGOS1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_Beh,
    (ModelNode*) &iedModel_VAO_LGOS1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_GoCBRef,
    (ModelNode*) &iedModel_VAO_LGOS1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_Health,
    (ModelNode*) &iedModel_VAO_LGOS1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_Health,
    (ModelNode*) &iedModel_VAO_LGOS1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_GoCBRef = {
    DataObjectModelType,
    "GoCBRef",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_St,
    (ModelNode*) &iedModel_VAO_LGOS1_GoCBRef_setSrcRef,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_GoCBRef_setSrcRef = {
    DataAttributeModelType,
    "setSrcRef",
    (ModelNode*) &iedModel_VAO_LGOS1_GoCBRef,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_SP,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_St = {
    DataObjectModelType,
    "St",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom,
    (ModelNode*) &iedModel_VAO_LGOS1_St_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_St_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_St,
    (ModelNode*) &iedModel_VAO_LGOS1_St_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_St_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_St,
    (ModelNode*) &iedModel_VAO_LGOS1_St_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_St_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_St,
    (ModelNode*) &iedModel_VAO_LGOS1_St_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_St_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LGOS1_St,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_NdsCom = {
    DataObjectModelType,
    "NdsCom",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt,
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_NdsCom_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom,
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_NdsCom_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom,
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_NdsCom_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom,
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_NdsCom_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LGOS1_NdsCom,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_SimSt = {
    DataObjectModelType,
    "SimSt",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_SimSt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt,
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_SimSt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt,
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_SimSt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt,
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_SimSt_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_LGOS1_SimSt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_ConfRevNum = {
    DataObjectModelType,
    "ConfRevNum",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_ConfRevNum_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_ConfRevNum_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_ConfRevNum_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_ConfRevNum,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_RxConfRevNum = {
    DataObjectModelType,
    "RxConfRevNum",
    (ModelNode*) &iedModel_VAO_LGOS1,
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum,
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_RxConfRevNum_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_RxConfRevNum_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum,
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_RxConfRevNum_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_RxConfRevNum,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LGOS1_LastStNum = {
    DataObjectModelType,
    "LastStNum",
    (ModelNode*) &iedModel_VAO_LGOS1,
    NULL,
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LGOS1_LastStNum_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum,
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_LastStNum_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum,
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LGOS1_LastStNum_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LGOS1_LastStNum,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_LTRK1 = {
    LogicalNodeModelType,
    "LTRK1",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_LTRK1_Beh,
};

DataObject iedModel_VAO_LTRK1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LTRK1_Health,
    (ModelNode*) &iedModel_VAO_LTRK1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LTRK1_Beh,
    (ModelNode*) &iedModel_VAO_LTRK1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LTRK1_Beh,
    (ModelNode*) &iedModel_VAO_LTRK1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LTRK1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_LTRK1_Health,
    (ModelNode*) &iedModel_VAO_LTRK1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_LTRK1_Health,
    (ModelNode*) &iedModel_VAO_LTRK1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LTRK1_GenTrk = {
    DataObjectModelType,
    "GenTrk",
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_objRef,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_GenTrk_objRef = {
    DataAttributeModelType,
    "objRef",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_serviceType,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_serviceType = {
    DataAttributeModelType,
    "serviceType",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_errorCode,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_errorCode = {
    DataAttributeModelType,
    "errorCode",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_rptID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_rptID = {
    DataAttributeModelType,
    "rptID",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_rptEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_rptEna = {
    DataAttributeModelType,
    "rptEna",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_resv,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_resv = {
    DataAttributeModelType,
    "resv",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_datSet,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_datSet = {
    DataAttributeModelType,
    "datSet",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_confRev,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_confRev = {
    DataAttributeModelType,
    "confRev",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_optFlds,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_optFlds = {
    DataAttributeModelType,
    "optFlds",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_bufTm,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OPTFLDS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_bufTm = {
    DataAttributeModelType,
    "bufTm",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_sqNum,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_sqNum = {
    DataAttributeModelType,
    "sqNum",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_trgOps,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT16U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_trgOps = {
    DataAttributeModelType,
    "trgOps",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_intgPd,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TRGOPS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_intgPd = {
    DataAttributeModelType,
    "intgPd",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_gi,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_gi = {
    DataAttributeModelType,
    "gi",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_purgeBuf,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_purgeBuf = {
    DataAttributeModelType,
    "purgeBuf",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_entryID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_entryID = {
    DataAttributeModelType,
    "entryID",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_timeOfEntry,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_timeOfEntry = {
    DataAttributeModelType,
    "timeOfEntry",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_goEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_goEna = {
    DataAttributeModelType,
    "goEna",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_goID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_goID = {
    DataAttributeModelType,
    "goID",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_ndsCom,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_ndsCom = {
    DataAttributeModelType,
    "ndsCom",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk_dstAddress,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GenTrk_dstAddress = {
    DataAttributeModelType,
    "dstAddress",
    (ModelNode*) &iedModel_VAO_LTRK1_GenTrk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LTRK1_UrcbTrk = {
    DataObjectModelType,
    "UrcbTrk",
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_objRef,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_objRef = {
    DataAttributeModelType,
    "objRef",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_serviceType,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_serviceType = {
    DataAttributeModelType,
    "serviceType",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_errorCode,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_errorCode = {
    DataAttributeModelType,
    "errorCode",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_rptID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_rptID = {
    DataAttributeModelType,
    "rptID",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_rptEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_rptEna = {
    DataAttributeModelType,
    "rptEna",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_resv,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_resv = {
    DataAttributeModelType,
    "resv",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_datSet,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_datSet = {
    DataAttributeModelType,
    "datSet",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_confRev,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_confRev = {
    DataAttributeModelType,
    "confRev",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_optFlds,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_optFlds = {
    DataAttributeModelType,
    "optFlds",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_bufTm,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OPTFLDS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_bufTm = {
    DataAttributeModelType,
    "bufTm",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_sqNum,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_sqNum = {
    DataAttributeModelType,
    "sqNum",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_trgOps,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT16U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_trgOps = {
    DataAttributeModelType,
    "trgOps",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_intgPd,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TRGOPS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_intgPd = {
    DataAttributeModelType,
    "intgPd",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_gi,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_gi = {
    DataAttributeModelType,
    "gi",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_purgeBuf,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_purgeBuf = {
    DataAttributeModelType,
    "purgeBuf",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_entryID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_entryID = {
    DataAttributeModelType,
    "entryID",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_timeOfEntry,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_timeOfEntry = {
    DataAttributeModelType,
    "timeOfEntry",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_goEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_goEna = {
    DataAttributeModelType,
    "goEna",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_goID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_goID = {
    DataAttributeModelType,
    "goID",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_ndsCom,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_ndsCom = {
    DataAttributeModelType,
    "ndsCom",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk_dstAddress,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_UrcbTrk_dstAddress = {
    DataAttributeModelType,
    "dstAddress",
    (ModelNode*) &iedModel_VAO_LTRK1_UrcbTrk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LTRK1_BrcbTrk = {
    DataObjectModelType,
    "BrcbTrk",
    (ModelNode*) &iedModel_VAO_LTRK1,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_objRef,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_objRef = {
    DataAttributeModelType,
    "objRef",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_serviceType,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_serviceType = {
    DataAttributeModelType,
    "serviceType",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_errorCode,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_errorCode = {
    DataAttributeModelType,
    "errorCode",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_rptID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_rptID = {
    DataAttributeModelType,
    "rptID",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_rptEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_rptEna = {
    DataAttributeModelType,
    "rptEna",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_resv,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_resv = {
    DataAttributeModelType,
    "resv",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_datSet,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_datSet = {
    DataAttributeModelType,
    "datSet",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_confRev,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_confRev = {
    DataAttributeModelType,
    "confRev",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_optFlds,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_optFlds = {
    DataAttributeModelType,
    "optFlds",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_bufTm,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OPTFLDS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_bufTm = {
    DataAttributeModelType,
    "bufTm",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_sqNum,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_sqNum = {
    DataAttributeModelType,
    "sqNum",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_trgOps,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT16U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_trgOps = {
    DataAttributeModelType,
    "trgOps",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_intgPd,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TRGOPS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_intgPd = {
    DataAttributeModelType,
    "intgPd",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_gi,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_gi = {
    DataAttributeModelType,
    "gi",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_purgeBuf,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_purgeBuf = {
    DataAttributeModelType,
    "purgeBuf",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_entryID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_entryID = {
    DataAttributeModelType,
    "entryID",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_timeOfEntry,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_timeOfEntry = {
    DataAttributeModelType,
    "timeOfEntry",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_goEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_goEna = {
    DataAttributeModelType,
    "goEna",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_goID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_goID = {
    DataAttributeModelType,
    "goID",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_ndsCom,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_ndsCom = {
    DataAttributeModelType,
    "ndsCom",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk_dstAddress,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_BrcbTrk_dstAddress = {
    DataAttributeModelType,
    "dstAddress",
    (ModelNode*) &iedModel_VAO_LTRK1_BrcbTrk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataObject iedModel_VAO_LTRK1_GocbTrk = {
    DataObjectModelType,
    "GocbTrk",
    (ModelNode*) &iedModel_VAO_LTRK1,
    NULL,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_objRef,
    0,
    -1
};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_objRef = {
    DataAttributeModelType,
    "objRef",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_serviceType,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_serviceType = {
    DataAttributeModelType,
    "serviceType",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_errorCode,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_errorCode = {
    DataAttributeModelType,
    "errorCode",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_rptID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_rptID = {
    DataAttributeModelType,
    "rptID",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_rptEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_rptEna = {
    DataAttributeModelType,
    "rptEna",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_resv,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_resv = {
    DataAttributeModelType,
    "resv",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_datSet,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_datSet = {
    DataAttributeModelType,
    "datSet",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_confRev,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_confRev = {
    DataAttributeModelType,
    "confRev",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_optFlds,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_optFlds = {
    DataAttributeModelType,
    "optFlds",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_bufTm,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OPTFLDS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_bufTm = {
    DataAttributeModelType,
    "bufTm",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_sqNum,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_sqNum = {
    DataAttributeModelType,
    "sqNum",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_trgOps,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT16U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_trgOps = {
    DataAttributeModelType,
    "trgOps",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_intgPd,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TRGOPS,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_intgPd = {
    DataAttributeModelType,
    "intgPd",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_gi,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_gi = {
    DataAttributeModelType,
    "gi",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_purgeBuf,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_purgeBuf = {
    DataAttributeModelType,
    "purgeBuf",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_entryID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_entryID = {
    DataAttributeModelType,
    "entryID",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_timeOfEntry,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_timeOfEntry = {
    DataAttributeModelType,
    "timeOfEntry",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_goEna,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_goEna = {
    DataAttributeModelType,
    "goEna",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_goID,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_goID = {
    DataAttributeModelType,
    "goID",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_ndsCom,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_VISIBLE_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_ndsCom = {
    DataAttributeModelType,
    "ndsCom",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk_dstAddress,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_LTRK1_GocbTrk_dstAddress = {
    DataAttributeModelType,
    "dstAddress",
    (ModelNode*) &iedModel_VAO_LTRK1_GocbTrk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XSWI1 = {
    LogicalNodeModelType,
    "XSWI1",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI1_EEName,
};

DataObject iedModel_VAO_XSWI1_EEName = {
    DataObjectModelType,
    "EEName",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI1_EEName_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_EEName_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI1_EEName,
    (ModelNode*) &iedModel_VAO_XSWI1_EEName_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_EEName_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_VAO_XSWI1_EEName,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XSWI1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_SwOpCap = {
    DataObjectModelType,
    "SwOpCap",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Loc,
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_SwOpCap_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_SwOpCap_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_SwOpCap_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_SwOpCap,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI1_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Loc,
    (ModelNode*) &iedModel_VAO_XSWI1_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Loc,
    (ModelNode*) &iedModel_VAO_XSWI1_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Loc,
    (ModelNode*) &iedModel_VAO_XSWI1_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_LocKey = {
    DataObjectModelType,
    "LocKey",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_LocKey_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocKey_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocKey_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocKey_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_LocKey,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_EEHealth = {
    DataObjectModelType,
    "EEHealth",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Blk,
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_EEHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_EEHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_EEHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_EEHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Blk = {
    DataObjectModelType,
    "Blk",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Beh,
    (ModelNode*) &iedModel_VAO_XSWI1_Blk_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Blk_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Blk,
    (ModelNode*) &iedModel_VAO_XSWI1_Blk_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Blk_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Blk,
    (ModelNode*) &iedModel_VAO_XSWI1_Blk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Blk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Blk,
    (ModelNode*) &iedModel_VAO_XSWI1_Blk_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Blk_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_Blk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Health,
    (ModelNode*) &iedModel_VAO_XSWI1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Beh,
    (ModelNode*) &iedModel_VAO_XSWI1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Beh,
    (ModelNode*) &iedModel_VAO_XSWI1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Health,
    (ModelNode*) &iedModel_VAO_XSWI1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Health,
    (ModelNode*) &iedModel_VAO_XSWI1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_LocSta = {
    DataObjectModelType,
    "LocSta",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_LocSta_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_LocSta_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI1_LocSta_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI1_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_Mod,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkRef,
    (ModelNode*) &iedModel_VAO_XSWI1_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_Mod,
    (ModelNode*) &iedModel_VAO_XSWI1_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_Mod,
    (ModelNode*) &iedModel_VAO_XSWI1_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_Mod,
    (ModelNode*) &iedModel_VAO_XSWI1_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI1_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_BlkRef = {
    DataObjectModelType,
    "BlkRef",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI1_BlkRef_setSrcRef,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_BlkRef_setSrcRef = {
    DataAttributeModelType,
    "setSrcRef",
    (ModelNode*) &iedModel_VAO_XSWI1_BlkRef,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_SP,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XSWI1,
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI1_SwTyp = {
    DataObjectModelType,
    "SwTyp",
    (ModelNode*) &iedModel_VAO_XSWI1,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI1_SwTyp_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_SwTyp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI1_SwTyp_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI1_SwTyp,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XSWI2 = {
    LogicalNodeModelType,
    "XSWI2",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI2_EEName,
};

DataObject iedModel_VAO_XSWI2_EEName = {
    DataObjectModelType,
    "EEName",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI2_EEName_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_EEName_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI2_EEName,
    (ModelNode*) &iedModel_VAO_XSWI2_EEName_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_EEName_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_VAO_XSWI2_EEName,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XSWI2_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_SwOpCap = {
    DataObjectModelType,
    "SwOpCap",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Loc,
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_SwOpCap_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_SwOpCap_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_SwOpCap_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_SwOpCap,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI2_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Loc,
    (ModelNode*) &iedModel_VAO_XSWI2_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Loc,
    (ModelNode*) &iedModel_VAO_XSWI2_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Loc,
    (ModelNode*) &iedModel_VAO_XSWI2_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_LocKey = {
    DataObjectModelType,
    "LocKey",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_LocKey_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocKey_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocKey_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocKey_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_LocKey,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_EEHealth = {
    DataObjectModelType,
    "EEHealth",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Blk,
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_EEHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_EEHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_EEHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_EEHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Blk = {
    DataObjectModelType,
    "Blk",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Beh,
    (ModelNode*) &iedModel_VAO_XSWI2_Blk_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Blk_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Blk,
    (ModelNode*) &iedModel_VAO_XSWI2_Blk_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Blk_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Blk,
    (ModelNode*) &iedModel_VAO_XSWI2_Blk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Blk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Blk,
    (ModelNode*) &iedModel_VAO_XSWI2_Blk_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Blk_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_Blk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Health,
    (ModelNode*) &iedModel_VAO_XSWI2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Beh,
    (ModelNode*) &iedModel_VAO_XSWI2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Beh,
    (ModelNode*) &iedModel_VAO_XSWI2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI2_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Health,
    (ModelNode*) &iedModel_VAO_XSWI2_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Health,
    (ModelNode*) &iedModel_VAO_XSWI2_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_LocSta = {
    DataObjectModelType,
    "LocSta",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_LocSta_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_LocSta_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI2_LocSta_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI2_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_Mod,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkRef,
    (ModelNode*) &iedModel_VAO_XSWI2_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_Mod,
    (ModelNode*) &iedModel_VAO_XSWI2_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_Mod,
    (ModelNode*) &iedModel_VAO_XSWI2_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_Mod,
    (ModelNode*) &iedModel_VAO_XSWI2_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI2_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_BlkRef = {
    DataObjectModelType,
    "BlkRef",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI2_BlkRef_setSrcRef,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_BlkRef_setSrcRef = {
    DataAttributeModelType,
    "setSrcRef",
    (ModelNode*) &iedModel_VAO_XSWI2_BlkRef,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_SP,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XSWI2,
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI2_SwTyp = {
    DataObjectModelType,
    "SwTyp",
    (ModelNode*) &iedModel_VAO_XSWI2,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI2_SwTyp_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_SwTyp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI2_SwTyp_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI2_SwTyp,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XSWI3 = {
    LogicalNodeModelType,
    "XSWI3",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XSWI3_EEName,
};

DataObject iedModel_VAO_XSWI3_EEName = {
    DataObjectModelType,
    "EEName",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI3_EEName_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_EEName_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI3_EEName,
    (ModelNode*) &iedModel_VAO_XSWI3_EEName_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_EEName_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_VAO_XSWI3_EEName,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XSWI3_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_SwOpCap = {
    DataObjectModelType,
    "SwOpCap",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Loc,
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_SwOpCap_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_SwOpCap_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap,
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_SwOpCap_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_SwOpCap,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI3_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Loc,
    (ModelNode*) &iedModel_VAO_XSWI3_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Loc,
    (ModelNode*) &iedModel_VAO_XSWI3_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Loc,
    (ModelNode*) &iedModel_VAO_XSWI3_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_LocKey = {
    DataObjectModelType,
    "LocKey",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_LocKey_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocKey_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocKey_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey,
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocKey_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_LocKey,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_EEHealth = {
    DataObjectModelType,
    "EEHealth",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Blk,
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_EEHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_EEHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth,
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_EEHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_EEHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Blk = {
    DataObjectModelType,
    "Blk",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Beh,
    (ModelNode*) &iedModel_VAO_XSWI3_Blk_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Blk_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Blk,
    (ModelNode*) &iedModel_VAO_XSWI3_Blk_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Blk_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Blk,
    (ModelNode*) &iedModel_VAO_XSWI3_Blk_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Blk_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Blk,
    (ModelNode*) &iedModel_VAO_XSWI3_Blk_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Blk_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_Blk,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Health,
    (ModelNode*) &iedModel_VAO_XSWI3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Beh,
    (ModelNode*) &iedModel_VAO_XSWI3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Beh,
    (ModelNode*) &iedModel_VAO_XSWI3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI3_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Health,
    (ModelNode*) &iedModel_VAO_XSWI3_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Health,
    (ModelNode*) &iedModel_VAO_XSWI3_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_LocSta = {
    DataObjectModelType,
    "LocSta",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_LocSta_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_LocSta_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI3_LocSta_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI3_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_Mod,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkRef,
    (ModelNode*) &iedModel_VAO_XSWI3_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_Mod,
    (ModelNode*) &iedModel_VAO_XSWI3_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_Mod,
    (ModelNode*) &iedModel_VAO_XSWI3_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_Mod,
    (ModelNode*) &iedModel_VAO_XSWI3_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XSWI3_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_BlkRef = {
    DataObjectModelType,
    "BlkRef",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI3_BlkRef_setSrcRef,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_BlkRef_setSrcRef = {
    DataAttributeModelType,
    "setSrcRef",
    (ModelNode*) &iedModel_VAO_XSWI3_BlkRef,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_SP,
    IEC61850_VISIBLE_STRING_129,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XSWI3,
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt,
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XSWI3_SwTyp = {
    DataObjectModelType,
    "SwTyp",
    (ModelNode*) &iedModel_VAO_XSWI3,
    NULL,
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XSWI3_SwTyp_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_SwTyp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp,
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XSWI3_SwTyp_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XSWI3_SwTyp,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XCBR1 = {
    LogicalNodeModelType,
    "XCBR1",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
};

DataObject iedModel_VAO_XCBR1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_Loc,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XCBR1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR1_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Loc,
    (ModelNode*) &iedModel_VAO_XCBR1_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_Loc,
    (ModelNode*) &iedModel_VAO_XCBR1_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_Loc,
    (ModelNode*) &iedModel_VAO_XCBR1_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR1_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_Beh,
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_Health,
    (ModelNode*) &iedModel_VAO_XCBR1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Beh,
    (ModelNode*) &iedModel_VAO_XCBR1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_Beh,
    (ModelNode*) &iedModel_VAO_XCBR1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_Mod,
    (ModelNode*) &iedModel_VAO_XCBR1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Health,
    (ModelNode*) &iedModel_VAO_XCBR1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_Health,
    (ModelNode*) &iedModel_VAO_XCBR1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    (ModelNode*) &iedModel_VAO_XCBR1_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Mod,
    (ModelNode*) &iedModel_VAO_XCBR1_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_Mod,
    (ModelNode*) &iedModel_VAO_XCBR1_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_Mod,
    (ModelNode*) &iedModel_VAO_XCBR1_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR1_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR1_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XCBR1,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR1_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XCBR1,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR1_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR1_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR1_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XCBR2 = {
    LogicalNodeModelType,
    "XCBR2",
    (ModelNode*) &iedModel_VAO,
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
};

DataObject iedModel_VAO_XCBR2_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_Loc,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XCBR2_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR2_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Loc,
    (ModelNode*) &iedModel_VAO_XCBR2_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_Loc,
    (ModelNode*) &iedModel_VAO_XCBR2_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_Loc,
    (ModelNode*) &iedModel_VAO_XCBR2_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR2_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_Beh,
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_Health,
    (ModelNode*) &iedModel_VAO_XCBR2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Beh,
    (ModelNode*) &iedModel_VAO_XCBR2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_Beh,
    (ModelNode*) &iedModel_VAO_XCBR2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_Mod,
    (ModelNode*) &iedModel_VAO_XCBR2_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Health,
    (ModelNode*) &iedModel_VAO_XCBR2_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_Health,
    (ModelNode*) &iedModel_VAO_XCBR2_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    (ModelNode*) &iedModel_VAO_XCBR2_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Mod,
    (ModelNode*) &iedModel_VAO_XCBR2_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_Mod,
    (ModelNode*) &iedModel_VAO_XCBR2_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_Mod,
    (ModelNode*) &iedModel_VAO_XCBR2_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR2_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR2_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XCBR2,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR2_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XCBR2,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR2_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR2_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR2_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

LogicalNode iedModel_VAO_XCBR3 = {
    LogicalNodeModelType,
    "XCBR3",
    (ModelNode*) &iedModel_VAO,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
};

DataObject iedModel_VAO_XCBR3_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_Loc,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_VAO_XCBR3_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_Loc = {
    DataObjectModelType,
    "Loc",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR3_Loc_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_Loc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Loc,
    (ModelNode*) &iedModel_VAO_XCBR3_Loc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Loc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_Loc,
    (ModelNode*) &iedModel_VAO_XCBR3_Loc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Loc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_Loc,
    (ModelNode*) &iedModel_VAO_XCBR3_Loc_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Loc_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR3_Loc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_OpCnt = {
    DataObjectModelType,
    "OpCnt",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_Beh,
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_OpCnt_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_OpCnt_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt,
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_OpCnt_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_OpCnt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_Health,
    (ModelNode*) &iedModel_VAO_XCBR3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Beh,
    (ModelNode*) &iedModel_VAO_XCBR3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_Beh,
    (ModelNode*) &iedModel_VAO_XCBR3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_Mod,
    (ModelNode*) &iedModel_VAO_XCBR3_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Health,
    (ModelNode*) &iedModel_VAO_XCBR3_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_Health,
    (ModelNode*) &iedModel_VAO_XCBR3_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    (ModelNode*) &iedModel_VAO_XCBR3_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Mod,
    (ModelNode*) &iedModel_VAO_XCBR3_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_Mod,
    (ModelNode*) &iedModel_VAO_XCBR3_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_Mod,
    (ModelNode*) &iedModel_VAO_XCBR3_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR3_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR3_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_BlkOpn = {
    DataObjectModelType,
    "BlkOpn",
    (ModelNode*) &iedModel_VAO_XCBR3,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkOpn_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkOpn_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_VAO_XCBR3_BlkCls = {
    DataObjectModelType,
    "BlkCls",
    (ModelNode*) &iedModel_VAO_XCBR3,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_stVal,
    0,
    -1
};

DataAttribute iedModel_VAO_XCBR3_BlkCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls,
    NULL,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_ctlNum,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_origin,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_VAO_XCBR3_BlkCls_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_VAO_XCBR3_BlkCls_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};









IedModel iedModel = {
    "EmpElas_CTRL",
    &iedModel_VAO,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    initializeValues
};

static void
initializeValues()
{
}
