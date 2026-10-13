/*
 * static_model.c
 *
 * automatically generated from empelas_prot.icd
 */
#include "static_model.h"

static void initializeValues();

extern DataSet iedModelds_MEDPROT_LLN0_dsTrip;
extern DataSet iedModelds_MEDPROT_LLN0_dsCmd;
extern DataSet iedModelds_MEDPROT_LLN0_dsEventos;


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
  &iedModelds_MEDPROT_LLN0_dsCmd
};

extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda0;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda1;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda2;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda3;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda4;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda5;

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda0 = {
  "MEDPROT",
  false,
  "CSWI1$ST$OpOpn$general", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda1
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda1 = {
  "MEDPROT",
  false,
  "CSWI1$ST$OpCls$general", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda2
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda2 = {
  "MEDPROT",
  false,
  "CSWI2$ST$OpOpn$general", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda3
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda3 = {
  "MEDPROT",
  false,
  "CSWI2$ST$OpCls$general", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda4
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda4 = {
  "MEDPROT",
  false,
  "CSWI3$ST$OpOpn$general", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda5
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsCmd_fcda5 = {
  "MEDPROT",
  false,
  "CSWI3$ST$OpCls$general", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_MEDPROT_LLN0_dsCmd = {
  "MEDPROT",
  "LLN0$dsCmd",
  6,
  &iedModelds_MEDPROT_LLN0_dsCmd_fcda0,
  &iedModelds_MEDPROT_LLN0_dsEventos
};

extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda0;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda1;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda2;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda3;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda4;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda5;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda6;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda7;
extern DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda8;

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda0 = {
  "MEDPROT",
  false,
  "PTOC1$ST$Str", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda1
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda1 = {
  "MEDPROT",
  false,
  "PTOC1$ST$Op", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda2
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda2 = {
  "MEDPROT",
  false,
  "PTRC1$ST$Tr", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda3
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda3 = {
  "MEDPROT",
  false,
  "CSWI1$ST$Pos", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda4
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda4 = {
  "MEDPROT",
  false,
  "CSWI2$ST$Pos", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda5
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda5 = {
  "MEDPROT",
  false,
  "CSWI3$ST$Pos", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda6
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda6 = {
  "MEDPROT",
  false,
  "CILO1$ST$EnaOpn", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda7
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda7 = {
  "MEDPROT",
  false,
  "CILO2$ST$EnaOpn", 
  -1,
  NULL,
  NULL,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda8
};

DataSetEntry iedModelds_MEDPROT_LLN0_dsEventos_fcda8 = {
  "MEDPROT",
  false,
  "CILO3$ST$EnaOpn", 
  -1,
  NULL,
  NULL,
  NULL
};

DataSet iedModelds_MEDPROT_LLN0_dsEventos = {
  "MEDPROT",
  "LLN0$dsEventos",
  9,
  &iedModelds_MEDPROT_LLN0_dsEventos_fcda0,
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
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
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

LogicalNode iedModel_MEDPROT_CSWI1 = {
    LogicalNodeModelType,
    "CSWI1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh,
};

DataObject iedModel_MEDPROT_CSWI1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI1_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_origin,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI1_OpOpn = {
    DataObjectModelType,
    "OpOpn",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_OpOpn_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_OpOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_OpOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI1_OpCls = {
    DataObjectModelType,
    "OpCls",
    (ModelNode*) &iedModel_MEDPROT_CSWI1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI1_OpCls_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_OpCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI1_OpCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI1_OpCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_CILO1 = {
    LogicalNodeModelType,
    "CILO1",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh,
};

DataObject iedModel_MEDPROT_CILO1_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO1_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO1_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO1_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO1_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO1_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO1_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CILO1_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO1_EnaOpn = {
    DataObjectModelType,
    "EnaOpn",
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO1_EnaOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_EnaOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_EnaOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO1_EnaCls = {
    DataObjectModelType,
    "EnaCls",
    (ModelNode*) &iedModel_MEDPROT_CILO1,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO1_EnaCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_EnaCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO1_EnaCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO1_EnaCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_CSWI2 = {
    LogicalNodeModelType,
    "CSWI2",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh,
};

DataObject iedModel_MEDPROT_CSWI2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI2_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI2_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI2_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_origin,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI2_OpOpn = {
    DataObjectModelType,
    "OpOpn",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_OpOpn_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_OpOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_OpOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI2_OpCls = {
    DataObjectModelType,
    "OpCls",
    (ModelNode*) &iedModel_MEDPROT_CSWI2,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI2_OpCls_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_OpCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI2_OpCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI2_OpCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_CILO2 = {
    LogicalNodeModelType,
    "CILO2",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh,
};

DataObject iedModel_MEDPROT_CILO2_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO2_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO2_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO2_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO2_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO2_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO2_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CILO2_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO2_EnaOpn = {
    DataObjectModelType,
    "EnaOpn",
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO2_EnaOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_EnaOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_EnaOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO2_EnaCls = {
    DataObjectModelType,
    "EnaCls",
    (ModelNode*) &iedModel_MEDPROT_CILO2,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO2_EnaCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_EnaCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO2_EnaCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO2_EnaCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_CSWI3 = {
    LogicalNodeModelType,
    "CSWI3",
    (ModelNode*) &iedModel_MEDPROT,
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh,
};

DataObject iedModel_MEDPROT_CSWI3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI3_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI3_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI3_Pos = {
    DataObjectModelType,
    "Pos",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_CODEDENUM,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_ctlModel,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_ctlModel = {
    DataAttributeModelType,
    "ctlModel",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    NULL,
    0,
    -1,
    IEC61850_FC_CF,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper = {
    DataAttributeModelType,
    "Oper",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_ctlVal,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_ctlVal = {
    DataAttributeModelType,
    "ctlVal",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_origin,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CODEDENUM,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_origin = {
    DataAttributeModelType,
    "origin",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_ctlNum,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_origin_orCat,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CONSTRUCTED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_origin_orCat = {
    DataAttributeModelType,
    "orCat",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_origin,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_origin_orIdent,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_ENUMERATED,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_origin_orIdent = {
    DataAttributeModelType,
    "orIdent",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_origin,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_OCTET_STRING_64,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_ctlNum = {
    DataAttributeModelType,
    "ctlNum",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_T,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_INT8U,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_T = {
    DataAttributeModelType,
    "T",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_Test,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_Test = {
    DataAttributeModelType,
    "Test",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper_Check,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_BOOLEAN,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_Pos_Oper_Check = {
    DataAttributeModelType,
    "Check",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_Pos_Oper,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_CO,
    IEC61850_CHECK,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI3_OpOpn = {
    DataObjectModelType,
    "OpOpn",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_OpOpn_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_OpOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_OpOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CSWI3_OpCls = {
    DataObjectModelType,
    "OpCls",
    (ModelNode*) &iedModel_MEDPROT_CSWI3,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls_general,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CSWI3_OpCls_general = {
    DataAttributeModelType,
    "general",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_OpCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls,
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CSWI3_OpCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CSWI3_OpCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

LogicalNode iedModel_MEDPROT_CILO3 = {
    LogicalNodeModelType,
    "CILO3",
    (ModelNode*) &iedModel_MEDPROT,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh,
};

DataObject iedModel_MEDPROT_CILO3_Beh = {
    DataObjectModelType,
    "Beh",
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO3_Beh_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_Beh_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_Beh_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Beh,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO3_Health = {
    DataObjectModelType,
    "Health",
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO3_Health_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_ENUMERATED,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_Health_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health,
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_Health_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO3_Health,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO3_NamPlt = {
    DataObjectModelType,
    "NamPlt",
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt_vendor,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO3_NamPlt_vendor = {
    DataAttributeModelType,
    "vendor",
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt_swRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_NamPlt_swRev = {
    DataAttributeModelType,
    "swRev",
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt_d,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_NamPlt_d = {
    DataAttributeModelType,
    "d",
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt_configRev,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_NamPlt_configRev = {
    DataAttributeModelType,
    "configRev",
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt_lnNs,
    NULL,
    0,
    -1,
    IEC61850_FC_DC,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_NamPlt_lnNs = {
    DataAttributeModelType,
    "lnNs",
    (ModelNode*) &iedModel_MEDPROT_CILO3_NamPlt,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_EX,
    IEC61850_VISIBLE_STRING_255,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO3_EnaOpn = {
    DataObjectModelType,
    "EnaOpn",
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO3_EnaOpn_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_EnaOpn_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_EnaOpn_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaOpn,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

DataObject iedModel_MEDPROT_CILO3_EnaCls = {
    DataObjectModelType,
    "EnaCls",
    (ModelNode*) &iedModel_MEDPROT_CILO3,
    NULL,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls_stVal,
    0,
    -1
};

DataAttribute iedModel_MEDPROT_CILO3_EnaCls_stVal = {
    DataAttributeModelType,
    "stVal",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls_q,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_BOOLEAN,
    0 + TRG_OPT_DATA_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_EnaCls_q = {
    DataAttributeModelType,
    "q",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls,
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls_t,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_QUALITY,
    0 + TRG_OPT_QUALITY_CHANGED,
    NULL,
    0};

DataAttribute iedModel_MEDPROT_CILO3_EnaCls_t = {
    DataAttributeModelType,
    "t",
    (ModelNode*) &iedModel_MEDPROT_CILO3_EnaCls,
    NULL,
    NULL,
    0,
    -1,
    IEC61850_FC_ST,
    IEC61850_TIMESTAMP,
    0,
    NULL,
    0};

extern ReportControlBlock iedModel_MEDPROT_LLN0_report0;
extern ReportControlBlock iedModel_MEDPROT_LLN0_report1;

ReportControlBlock iedModel_MEDPROT_LLN0_report0 = {&iedModel_MEDPROT_LLN0, "brcbEventos01", "EmpElas_PROT_Eventos", true, "dsEventos", 1, 19, 255, 50, 0, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, &iedModel_MEDPROT_LLN0_report1};
ReportControlBlock iedModel_MEDPROT_LLN0_report1 = {&iedModel_MEDPROT_LLN0, "brcbEventos02", "EmpElas_PROT_Eventos", true, "dsEventos", 1, 19, 255, 50, 0, {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, NULL};


extern GSEControlBlock iedModel_MEDPROT_LLN0_gse0;
extern GSEControlBlock iedModel_MEDPROT_LLN0_gse1;

static PhyComAddress iedModel_MEDPROT_LLN0_gse0_address = {
  4,
  0,
  4097,
  {0x1, 0xc, 0xcd, 0x1, 0x0, 0x1}
};

GSEControlBlock iedModel_MEDPROT_LLN0_gse0 = {&iedModel_MEDPROT_LLN0, "gcbTrip", "EmpElasTrip", "dsTrip", 1, false, &iedModel_MEDPROT_LLN0_gse0_address, 10, 1000, &iedModel_MEDPROT_LLN0_gse1};

static PhyComAddress iedModel_MEDPROT_LLN0_gse1_address = {
  4,
  0,
  4099,
  {0x1, 0xc, 0xcd, 0x1, 0x0, 0x3}
};

GSEControlBlock iedModel_MEDPROT_LLN0_gse1 = {&iedModel_MEDPROT_LLN0, "gcbCmd", "EmpElasCmd", "dsCmd", 1, false, &iedModel_MEDPROT_LLN0_gse1_address, 10, 1000, NULL};





IedModel iedModel = {
    "EmpElas_PROT",
    &iedModel_MEDPROT,
    &iedModelds_MEDPROT_LLN0_dsTrip,
    &iedModel_MEDPROT_LLN0_report0,
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

iedModel_MEDPROT_CSWI1_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI1_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI1_NamPlt_d.mmsValue = MmsValue_newVisibleString("Comando da chave 1: libera pelo CILO1 e envia por GOOSE (gcbCmd)");

iedModel_MEDPROT_CSWI1_Pos_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO1_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO1_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO1_NamPlt_d.mmsValue = MmsValue_newVisibleString("Intertravamento da chave 1: so manobra com o disjuntor 1 aberto");

iedModel_MEDPROT_CSWI2_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI2_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI2_NamPlt_d.mmsValue = MmsValue_newVisibleString("Comando da chave 2: libera pelo CILO2 e envia por GOOSE (gcbCmd)");

iedModel_MEDPROT_CSWI2_Pos_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO2_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO2_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO2_NamPlt_d.mmsValue = MmsValue_newVisibleString("Intertravamento da chave 2: so manobra com o disjuntor 2 aberto");

iedModel_MEDPROT_CSWI3_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI3_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CSWI3_NamPlt_d.mmsValue = MmsValue_newVisibleString("Comando da chave 3: libera pelo CILO3 e envia por GOOSE (gcbCmd)");

iedModel_MEDPROT_CSWI3_Pos_ctlModel.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO3_Beh_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO3_Health_stVal.mmsValue = MmsValue_newIntegerFromInt32(1);

iedModel_MEDPROT_CILO3_NamPlt_d.mmsValue = MmsValue_newVisibleString("Intertravamento da chave 3: so manobra com o disjuntor 3 aberto");
}
