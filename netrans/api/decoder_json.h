/*
 * decoder_json.h
 *
 *  Created on: Jan 5, 2017
 *      Author: wyd
 */

#ifndef API_DECODER_JSON_H_
#define API_DECODER_JSON_H_
#include <wchar.h>
#include"rapidjson/encodings.h"
#include"rapidjson/document.h"
using rapidjson::GenericStringRef;
namespace huawei{
namespace eai{
typedef rapidjson::GenericDocument<rapidjson::UTF16LE<wchar_t> > eai_wdocument;
typedef rapidjson::GenericValue<rapidjson::UTF16LE<wchar_t> > eai_wvalue;
//wchar verson of lables
#define EAIT_JSON_SENT_WLABEL               L"sent"
#define EAIT_JSON_SRC_SIDE_WLABEL           L"src"
#define EAIT_JSON_START_WLABEL              L"start"
#define EAIT_JSON_END_WLABEL                L"end"
#define EAIT_JSON_LENGTH_WLABEL             L"length"
#define EAIT_JSON_TOK_TYPE_WLABEL           L"tok_type"
#define EAIT_JSON_TGT_LIST_WLABEL           L"tgt_list"
#define EAIT_JSON_TGT_WLABEL                L"tgt"
#define EAIT_JSON_TGT_PROB_WLABEL           L"prob"
#define EAIT_JSON_WID_WLABEL                L"id"
#define EAIT_JSON_DICT_RULES_WLABEL         L"dict_rules"
#define EAIT_JSON_MEM_RULES_WLABEL          L"mem_rules"//deprecated
#define EAIT_JSON_TGT_TRANSLIT_WLABEL       L"trans_literal"
#define EAIT_JSON_TGT_SENT_WLABEL           L"tgt_sent"
#define EAIT_JSON_NE_LIST_WLABEL            L"ne_list"
#define EAIT_JSON_TERM_LIST_WLABEL          L"term_list"
#define EAIT_JSON_NE_TYPE_WLABEL            L"ne_type"

static const wchar_t* EAIT_JSON_NE_TYPE_WDAIT = L"DATE";
static const wchar_t* EAIT_JSON_NE_TYPE_WTIME = L"TIME";
static const wchar_t* EAIT_JSON_NE_TYPE_WCURRENCY = L"CURRENCY";
static const wchar_t* EAIT_JSON_NE_TYPE_WLCW = L"LCW";
static const wchar_t* EAIT_JSON_NE_TYPE_WNON_TRANS = L"NON_TRANS";

static const wchar_t* EAIT_JSON_TGT_TRANSLIT_SKIP = L"##SKIP##";
static const int EAIT_JSON_TGT_TRANSLIT_SKIP_LEN = (8 * sizeof(wchar_t));

static const char* EAI_TRANS_LANG_ZH = "zh";
static const char* EAI_TRANS_LANG_EN = "en";

static const char* EAIT_JSON_DEFAULT_ENCODING = "UTF-8";
static const char EAIT_JSON_DEFAULT_WORD_SEP = ' ';
static const wchar_t EAIT_JSON_DEFAULT_WORD_WSEP = L' ';
static const wchar_t* EAIT_JSON_DEFAULT_WORD_WSEPSTR = L" ";
static const int EAIT_JSON_BUF_SIZE = (1024*128);//128K
static const int EAIT_JSON_BUF_BLOCK_SIZE = 1024;
}
}


#endif /* API_DECODER_JSON_H_ */
