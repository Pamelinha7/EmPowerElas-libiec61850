/*
 * static_model.c
 *
 * automatically generated from empelas_prot.icd
 */
#include "static_model.h"

static void initializeValues();

extern DataSet iedModelds_MEDPROT_LLN0_dsTrip;


extern DataSetEntry iedModelds_MEDPROT_LLN0_dsTrip_fcda0;

DataSetEntry iedModelds_MEDPROT_LLN0_dsTrip_fcda0 = {
  "MEDPROT",
  false,
  "PTRC1$ST$Tr$general", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_MEDPROT_LLN0_dsTrip = {
  "MEDPROT",
  "LLN0$dsTrip",
  1,
  &iedModelds_MEDPROT_LLN0_dsTrip_fcda0,
  NULL
};

LogicalDevice iedModel_MEDPROT = {
    LogicalDeviceModelType,
    "MEDPROT",
    (ModelNode*) &iedModel,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    NULL
};

LogicalNode iedModel_MEDPROT_LLN0 = {
    LogicalNodeModelType,
    "LLN0",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod,
};

DataObject iedModel_MEDPROT_LLN0_Mod = {
    DataObjectModelType,
    "Mod",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_Mod_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Mod_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Mod_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Mod_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Mod,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LLN0_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LLN0_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LLN0_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_LLN0_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LLN0_Diag = {
    DataObjectModelType,
    "Diag",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_Diag_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Diag_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Diag_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag,
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_Diag_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LLN0_Diag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LLN0_LEDRs = {
    DataObjectModelType,
    "LEDRs",
    (ModelNode*) &iedModel_MEDPROT_LLN0,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LLN0_LEDRs_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs,
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_LEDRs_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs,
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_LEDRs_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs,
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LLN0_LEDRs_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LLN0_LEDRs,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_LPHD1 = {
    LogicalNodeModelType,
    "LPHD1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_LTIM1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
};

DataObject iedModel_MEDPROT_LPHD1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyNam,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_PhyNam = {
    DataObjectModelType,
    "PhyNam",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyNam_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_PhyNam_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyNam,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyNam_model,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_PhyNam_model = {
    DataAttributeModelType,
    "model",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyNam,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_PhyHealth = {
    DataObjectModelType,
    "PhyHealth",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_PhyHealth_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_PhyHealth_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_PhyHealth_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_PhyHealth,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_OutOv = {
    DataObjectModelType,
    "OutOv",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_OutOv_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_OutOv_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_OutOv_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_OutOv_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OutOv,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_Proxy = {
    DataObjectModelType,
    "Proxy",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_Proxy_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Proxy_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Proxy_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Proxy_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Proxy,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_OpTmh = {
    DataObjectModelType,
    "OpTmh",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_OpTmh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_OpTmh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_OpTmh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_OpTmh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LPHD1_Sim = {
    DataObjectModelType,
    "Sim",
    (ModelNode*) &iedModel_MEDPROT_LPHD1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LPHD1_Sim_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Sim_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Sim_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim,
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LPHD1_Sim_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LPHD1_Sim,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_LTIM1 = {
    LogicalNodeModelType,
    "LTIM1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_LTMS1,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh,
};

DataObject iedModel_MEDPROT_LTIM1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_LTIM1,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTIM1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LTIM1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_LTIM1,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTIM1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LTIM1_TmDT = {
    DataObjectModelType,
    "TmDT",
    (ModelNode*) &iedModel_MEDPROT_LTIM1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTIM1_TmDT_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_TmDT_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_TmDT_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT,
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTIM1_TmDT_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_LTIM1_TmDT,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_LTMS1 = {
    LogicalNodeModelType,
    "LTMS1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc,
};

DataObject iedModel_MEDPROT_LTMS1_TmSrc = {
    DataObjectModelType,
    "TmSrc",
    (ModelNode*) &iedModel_MEDPROT_LTMS1,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrc_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrc_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrc_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrc,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LTMS1_TmSrcTyp = {
    DataObjectModelType,
    "TmSrcTyp",
    (ModelNode*) &iedModel_MEDPROT_LTMS1,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrcTyp_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_INT8U,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrcTyp_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_TmSrcTyp_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_TmSrcTyp,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_LTMS1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_LTMS1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_LTMS1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh,
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_LTMS1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_LTMS1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_MMXU1 = {
    LogicalNodeModelType,
    "MMXU1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_PTOC1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
};

DataObject iedModel_MEDPROT_MMXU1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_A = {
    DataObjectModelType,
    "A",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA,
    0,
    -1
};

DataObject iedModel_MEDPROT_MMXU1_A_phsA = {
    DataObjectModelType,
    "phsA",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsA_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsA_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsA_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsA_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsA_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsA,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_A_phsB = {
    DataObjectModelType,
    "phsB",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsB_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsB_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsB_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsB_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsB_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsB,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_A_phsC = {
    DataObjectModelType,
    "phsC",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsC_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsC_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsC_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsC_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_phsC_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_phsC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_A_neut = {
    DataObjectModelType,
    "neut",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_A_neut_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_neut_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_neut_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_neut_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_A_neut_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_A_neut,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PhV = {
    DataObjectModelType,
    "PhV",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA,
    0,
    -1
};

DataObject iedModel_MEDPROT_MMXU1_PhV_phsA = {
    DataObjectModelType,
    "phsA",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsA_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsA_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsA_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsA_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsA_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsA,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PhV_phsB = {
    DataObjectModelType,
    "phsB",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsB_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsB_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsB_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsB_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsB_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsB,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PhV_phsC = {
    DataObjectModelType,
    "phsC",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsC_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsC_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsC_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsC_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_phsC_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_phsC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PhV_neut = {
    DataObjectModelType,
    "neut",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_neut_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_neut_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_neut_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_neut_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PhV_neut_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PhV_neut,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PPV = {
    DataObjectModelType,
    "PPV",
    (ModelNode*) &iedModel_MEDPROT_MMXU1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB,
    0,
    -1
};

DataObject iedModel_MEDPROT_MMXU1_PPV_phsAB = {
    DataObjectModelType,
    "phsAB",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsAB_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsAB_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsAB,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PPV_phsBC = {
    DataObjectModelType,
    "phsBC",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsBC_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsBC_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsBC,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_MMXU1_PPV_phsCA = {
    DataObjectModelType,
    "phsCA",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal = {
    DataAttributeModelType,
    "cVal",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_q,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal_mag,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal_mag = {
    DataAttributeModelType,
    "mag",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal_mag_f,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_CONSTRUCTED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal_mag_f = {
    DataAttributeModelType,
    "f",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_cVal_mag,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_FLOAT32,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsCA_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA,
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA_t,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_MMXU1_PPV_phsCA_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_MMXU1_PPV_phsCA,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_MX,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_PTOC1 = {
    LogicalNodeModelType,
    "PTOC1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_PTRC1,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh,
};

DataObject iedModel_MEDPROT_PTOC1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_PTOC1,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTOC1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_PTOC1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_PTOC1,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTOC1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_PTOC1_Str = {
    DataObjectModelType,
    "Str",
    (ModelNode*) &iedModel_MEDPROT_PTOC1,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTOC1_Str_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_dirGeneral,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_dirGeneral = {
    DataAttributeModelType,
    "dirGeneral",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_phsA,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_phsA = {
    DataAttributeModelType,
    "phsA",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_dirPhsA,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_dirPhsA = {
    DataAttributeModelType,
    "dirPhsA",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_phsB,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_phsB = {
    DataAttributeModelType,
    "phsB",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_dirPhsB,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_dirPhsB = {
    DataAttributeModelType,
    "dirPhsB",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_phsC,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_phsC = {
    DataAttributeModelType,
    "phsC",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_dirPhsC,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_dirPhsC = {
    DataAttributeModelType,
    "dirPhsC",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Str_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Str,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_PTOC1_Op = {
    DataObjectModelType,
    "Op",
    (ModelNode*) &iedModel_MEDPROT_PTOC1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTOC1_Op_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_phsA,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Op_phsA = {
    DataAttributeModelType,
    "phsA",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_phsB,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Op_phsB = {
    DataAttributeModelType,
    "phsB",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_phsC,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Op_phsC = {
    DataAttributeModelType,
    "phsC",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Op_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTOC1_Op_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTOC1_Op,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_PTRC1 = {
    LogicalNodeModelType,
    "PTRC1",
    (ModelNode*) &iedModel_MEDPROT,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh,
};

DataObject iedModel_MEDPROT_PTRC1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_PTRC1,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTRC1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_PTRC1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_PTRC1,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTRC1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_PTRC1_Tr = {
    DataObjectModelType,
    "Tr",
    (ModelNode*) &iedModel_MEDPROT_PTRC1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_PTRC1_Tr_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Tr_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr,
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_PTRC1_Tr_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_PTRC1_Tr,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};




extern GSEControlBlock iedModel_MEDPROT_LLN0_gse0;

static PhyComAddress iedModel_MEDPROT_LLN0_gse0_address = {
  4,
  0,
  4097,
  {0x1, 0xc, 0xcd, 0x1, 0x0, 0x1}
};

GSEControlBlock iedModel_MEDPROT_LLN0_gse0 = {&iedModel_MEDPROT_LLN0, "gcbTrip", "EmpElasTrip", "dsTrip", 1, false, &iedModel_MEDPROT_LLN0_gse0_address, 10, 1000, NULL};





IedModel iedModel = {
    "EmpElas_PROT",
    &iedModel_MEDPROT,
    &iedModelds_MEDPROT_LLN0_dsTrip,
    NULL,
    &iedModel_MEDPROT_LLN0_gse0,
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
