﻿// -----------------------------------------------------------------------------------------
// NVEnc by rigaya
// -----------------------------------------------------------------------------------------
// The MIT License
//
// Copyright (c) 2014-2016 rigaya
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// ------------------------------------------------------------------------------------------

#pragma once

#include <tchar.h>
#include <limits.h>
#include <vector>
#include "rgy_osdep.h"
#pragma warning (push)
#pragma warning (disable: 4819)
#pragma warning (disable: 4201)
#include "dynlink_cuviddec.h"
#include <npp.h>
#pragma warning (pop)
#include "nvEncodeAPI.h"
#include "NVEncoderPerf.h"
#include "rgy_util.h"
#include "convert_csp.h"

using std::vector;

static const int   FILTER_DEFAULT_DELOGO_DEPTH = 128;
static const int   FILTER_DEFAULT_UNSHARP_RADIUS = 3;
static const float FILTER_DEFAULT_UNSHARP_WEIGHT = 0.5f;
static const float FILTER_DEFAULT_UNSHARP_THRESHOLD = 10.0f;
static const float FILTER_DEFAULT_EDGELEVEL_STRENGTH = 5.0f;
static const float FILTER_DEFAULT_EDGELEVEL_THRESHOLD = 20.0f;
static const float FILTER_DEFAULT_EDGELEVEL_BLACK = 0.0f;
static const float FILTER_DEFAULT_EDGELEVEL_WHITE = 0.0f;
static const int   FILTER_DEFAULT_KNN_RADIUS = 3;
static const float FILTER_DEFAULT_KNN_STRENGTH = 0.08f;
static const float FILTER_DEFAULT_KNN_LERPC = 0.20f;
static const float FILTER_DEFAULT_KNN_WEIGHT_THRESHOLD = 0.01f;
static const float FILTER_DEFAULT_KNN_LERPC_THRESHOLD = 0.80f;
static const float FILTER_DEFAULT_PMD_STRENGTH = 100.0f;
static const float FILTER_DEFAULT_PMD_THRESHOLD = 100.0f;
static const int   FILTER_DEFAULT_PMD_APPLY_COUNT = 2;
static const bool  FILTER_DEFAULT_PMD_USE_EXP = true;
static const int   FILTER_DEFAULT_DEBAND_RANGE = 15;
static const int   FILTER_DEFAULT_DEBAND_THRE_Y = 15;
static const int   FILTER_DEFAULT_DEBAND_THRE_CB = 15;
static const int   FILTER_DEFAULT_DEBAND_THRE_CR = 15;
static const int   FILTER_DEFAULT_DEBAND_DITHER_Y = 15;
static const int   FILTER_DEFAULT_DEBAND_DITHER_C = 15;
static const int   FILTER_DEFAULT_DEBAND_MODE = 1;
static const int   FILTER_DEFAULT_DEBAND_SEED = 1234;
static const bool  FILTER_DEFAULT_DEBAND_BLUR_FIRST = false;
static const bool  FILTER_DEFAULT_DEBAND_RAND_EACH_FRAME = false;

static const int   FILTER_DEFAULT_AFS_CLIP_TB = 16;
static const int   FILTER_DEFAULT_AFS_CLIP_LR = 32;
static const int   FILTER_DEFAULT_AFS_TB_ORDER = 0;
static const int   FILTER_DEFAULT_AFS_METHOD_SWITCH = 0;
static const int   FILTER_DEFAULT_AFS_COEFF_SHIFT = 192;
static const int   FILTER_DEFAULT_AFS_THRE_SHIFT = 128;
static const int   FILTER_DEFAULT_AFS_THRE_DEINT = 48;
static const int   FILTER_DEFAULT_AFS_THRE_YMOTION = 112;
static const int   FILTER_DEFAULT_AFS_THRE_CMOTION = 224;
static const int   FILTER_DEFAULT_AFS_ANALYZE = 3;
static const bool  FILTER_DEFAULT_AFS_SHIFT = true;
static const bool  FILTER_DEFAULT_AFS_DROP = false;
static const bool  FILTER_DEFAULT_AFS_SMOOTH = false;
static const bool  FILTER_DEFAULT_AFS_FORCE24 = false;
static const bool  FILTER_DEFAULT_AFS_TUNE = false;
static const bool  FILTER_DEFAULT_AFS_RFF = false;
static const bool  FILTER_DEFAULT_AFS_TIMECODE = false;
static const bool  FILTER_DEFAULT_AFS_LOG = false;

static const float FILTER_DEFAULT_TWEAK_BRIGHTNESS = 0.0f;
static const float FILTER_DEFAULT_TWEAK_CONTRAST = 1.0f;
static const float FILTER_DEFAULT_TWEAK_GAMMA = 1.0f;
static const float FILTER_DEFAULT_TWEAK_SATURATION = 1.0f;
static const float FILTER_DEFAULT_TWEAK_HUE = 0.0f;

static const int MAX_DECODE_FRAMES = 16;

static const int BITSTREAM_BUFFER_SIZE =  4 * 1024 * 1024;
static const int OUTPUT_BUF_SIZE       = 16 * 1024 * 1024;

static const int DEFAULT_GOP_LENGTH  = 0;
static const int DEFAULT_B_FRAMES_H264 = 3;
static const int DEFAULT_B_FRAMES_HEVC = 0;
static const int DEFAULT_REF_FRAMES  = 3;
static const int DEFAULT_NUM_SLICES  = 1;
static const int DEFAUTL_QP_I        = 20;
static const int DEFAULT_QP_P        = 23;
static const int DEFAULT_QP_B        = 25;
static const int DEFAULT_AVG_BITRATE = 7500000;
static const int DEFAULT_MAX_BITRATE = 17500000;
static const int DEFAULT_OUTPUT_BUF  = 8;
static const int DEFAULT_LOOKAHEAD   = 16;
static const int DEFAULT_IGNORE_DECODE_ERROR = 10;

static const int DEFAULT_CUDA_SCHEDULE = CU_CTX_SCHED_AUTO;

const int RGY_DEFAULT_PERF_MONITOR_INTERVAL = 500;

static const uint32_t PIPELINE_DEPTH = 4;
static const int MAX_FILTER_OUTPUT = 2;

enum {
    NV_ENC_AVCUVID_NATIVE = 0,
    NV_ENC_AVCUVID_CUDA,
};

typedef struct {
    GUID id;
    TCHAR *desc;
    unsigned int value;
} guid_desc;

const guid_desc h264_profile_names[] = {
    { NV_ENC_CODEC_PROFILE_AUTOSELECT_GUID, _T("auto"),      0 },
    { NV_ENC_H264_PROFILE_BASELINE_GUID,    _T("baseline"), 66 },
    { NV_ENC_H264_PROFILE_MAIN_GUID,        _T("main"),     77 },
    { NV_ENC_H264_PROFILE_HIGH_GUID,        _T("high"),    100 },
    { NV_ENC_H264_PROFILE_HIGH_444_GUID,    _T("high444"), 244 },
    //{ NV_ENC_H264_PROFILE_STEREO_GUID,   _T("Stereo"),  128 }
};

enum {
    NV_ENC_PROFILE_HEVC_MAIN = 0,
    NV_ENC_PROFILE_HEVC_MAIN10 = 1,
    NV_ENC_PROFILE_HEVC_MAIN444 = 2
};

const guid_desc h265_profile_names[] = {
    //{ NV_ENC_CODEC_PROFILE_AUTOSELECT_GUID, _T("auto"),                     0 },
    { NV_ENC_HEVC_PROFILE_MAIN_GUID,        _T("main"),    NV_ENC_PROFILE_HEVC_MAIN },
    { NV_ENC_HEVC_PROFILE_MAIN10_GUID,      _T("main10"),  NV_ENC_PROFILE_HEVC_MAIN10 },
    { NV_ENC_HEVC_PROFILE_FREXT_GUID,       _T("main444"), NV_ENC_PROFILE_HEVC_MAIN444 },
    //{ NV_ENC_HEVC_PROFILE_HIGH_GUID, _T("High"), NV_ENC_TIER_HEVC_HIGH },
};

const CX_DESC h265_tier_names[] = {
    { _T("main"),  NV_ENC_TIER_HEVC_MAIN },
    { _T("high"),  NV_ENC_TIER_HEVC_HIGH },
};

enum {
    NVENC_PRESET_DEFAULT = 0,
    NVENC_PRESET_HP,
    NVENC_PRESET_HQ,
    NVENC_PRESET_BD,
    NVENC_PRESET_LL,
    NVENC_PRESET_LL_HP,
    NVENC_PRESET_LL_HQ
};

const guid_desc list_nvenc_preset_names[] = {
    { NV_ENC_PRESET_DEFAULT_GUID,              _T("default"),                 NVENC_PRESET_DEFAULT },
    { NV_ENC_PRESET_HP_GUID,                   _T("performance"),             NVENC_PRESET_HP },
    { NV_ENC_PRESET_HQ_GUID,                   _T("quality"),                 NVENC_PRESET_HQ },
    //{ NV_ENC_PRESET_BD_GUID,                   _T("bluray"),                  NVENC_PRESET_BD },
    { NV_ENC_PRESET_LOW_LATENCY_DEFAULT_GUID,  _T("lowlatency"),              NVENC_PRESET_LL },
    { NV_ENC_PRESET_LOW_LATENCY_HP_GUID,       _T("lowlatency-performance"),  NVENC_PRESET_LL_HP },
    { NV_ENC_PRESET_LOW_LATENCY_HQ_GUID,       _T("lowlatency-quality"),      NVENC_PRESET_LL_HQ },
};

const guid_desc list_nvenc_codecs[] = {
    { NV_ENC_CODEC_H264_GUID, _T("H.264/AVC"),  NV_ENC_H264 },
    { NV_ENC_CODEC_HEVC_GUID, _T("H.265/HEVC"), NV_ENC_HEVC },
};
const CX_DESC list_nvenc_codecs_for_opt[] = {
    { _T("h264"), NV_ENC_H264 },
    { _T("avc"),  NV_ENC_H264 },
    { _T("hevc"), NV_ENC_HEVC },
    { _T("h265"), NV_ENC_HEVC },
    { NULL, NULL }
};

const CX_DESC list_avc_level[] = {
    { _T("auto"), 0   },
    { _T("1"),    10  },
    { _T("1b"),   9   },
    { _T("1.1"),  11  },
    { _T("1.2"),  12  },
    { _T("1.3"),  13  },
    { _T("2"),    20  },
    { _T("2.1"),  21  },
    { _T("2.2"),  22  },
    { _T("3"),    30  },
    { _T("3.1"),  31  },
    { _T("3.2"),  32  },
    { _T("4"),    40  },
    { _T("4.1"),  41  },
    { _T("4.2"),  42  },
    { _T("5"),    50  },
    { _T("5.1"),  51  },
    { _T("5.2"),  52  },
    { NULL, NULL }
};

const CX_DESC list_hevc_level[] = {
    { _T("auto"), 0   },
    { _T("1"),    NV_ENC_LEVEL_HEVC_1   },
    { _T("2"),    NV_ENC_LEVEL_HEVC_2   },
    { _T("2.1"),  NV_ENC_LEVEL_HEVC_21  },
    { _T("3"),    NV_ENC_LEVEL_HEVC_3   },
    { _T("3.1"),  NV_ENC_LEVEL_HEVC_31  },
    { _T("4"),    NV_ENC_LEVEL_HEVC_4   },
    { _T("4.1"),  NV_ENC_LEVEL_HEVC_41  },
    { _T("5"),    NV_ENC_LEVEL_HEVC_5   },
    { _T("5.1"),  NV_ENC_LEVEL_HEVC_51  },
    { _T("5.2"),  NV_ENC_LEVEL_HEVC_52  },
    { _T("6"),    NV_ENC_LEVEL_HEVC_6   },
    { _T("6.1"),  NV_ENC_LEVEL_HEVC_61  },
    { _T("6.2"),  NV_ENC_LEVEL_HEVC_62  },
    { NULL, NULL }
};

const CX_DESC list_hevc_cu_size[] = {
    { _T("auto"), NV_ENC_HEVC_CUSIZE_AUTOSELECT },
    { _T("8"),    NV_ENC_HEVC_CUSIZE_8x8        },
    { _T("16"),   NV_ENC_HEVC_CUSIZE_16x16      },
    { _T("32"),   NV_ENC_HEVC_CUSIZE_32x32      },
    { _T("64"),   NV_ENC_HEVC_CUSIZE_64x64      },
    { NULL, NULL }
};

const int COLOR_VALUE_AUTO = INT_MAX;
const int HD_HEIGHT_THRESHOLD = 720;
const int HD_INDEX = 2;
const int SD_INDEX = 3;
const CX_DESC list_colorprim[] = {
    { _T("undef"),     2  },
    { _T("auto"),      COLOR_VALUE_AUTO },
    { _T("bt709"),     1  },
    { _T("smpte170m"), 6  },
    { _T("bt470m"),    4  },
    { _T("bt470bg"),   5  },
    { _T("smpte240m"), 7  },
    { _T("film"),      8  },
    { _T("bt2020"),    9  },
    { NULL, NULL }
};
const CX_DESC list_transfer[] = {
    { _T("undef"),         2  },
    { _T("auto"),          COLOR_VALUE_AUTO },
    { _T("bt709"),         1  },
    { _T("smpte170m"),     6  },
    { _T("bt470m"),        4  },
    { _T("bt470bg"),       5  },
    { _T("smpte240m"),     7  },
    { _T("linear"),        8  },
    { _T("log100"),        9  },
    { _T("log316"),        10 },
    { _T("iec61966-2-4"),  11 },
    { _T("bt1361e"),       12 },
    { _T("iec61966-2-1"),  13 },
    { _T("bt2020-10"),     14 },
    { _T("bt2020-12"),     15 },
    { _T("smpte2084"),     16 },
    { _T("smpte428"),      17 },
    { _T("arib-srd-b67"),  18 },
    { NULL, NULL }
};
const CX_DESC list_colormatrix[] = {
    { _T("undef"),     2  },
    { _T("auto"),      COLOR_VALUE_AUTO },
    { _T("bt709"),     1  },
    { _T("smpte170m"), 6  },
    { _T("bt470bg"),   5  },
    { _T("smpte240m"), 7  },
    { _T("YCgCo"),     8  },
    { _T("fcc"),       4  },
    { _T("GBR"),       0  },
    { _T("bt2020nc"),  9  },
    { _T("bt2020c"),   10 },
    { NULL, NULL }
};
const CX_DESC list_videoformat[] = {
    { _T("undef"),     5  },
    { _T("ntsc"),      2  },
    { _T("component"), 0  },
    { _T("pal"),       1  },
    { _T("secam"),     3  },
    { _T("mac"),       4  },
    { NULL, NULL }
};
const CX_DESC list_chromaloc[] = {
    { _T("0"), 0 },
    { _T("1"), 1 },
    { _T("2"), 2 },
    { _T("3"), 3 },
    { _T("4"), 4 },
    { _T("5"), 5 },
    { NULL, NULL }
};

const CX_DESC nvenc_interface_names[] = {
    { _T("CUDA"),      NV_ENC_CUDA },
    { _T("DirectX9"),  NV_ENC_DX9  },
    { _T("DirectX10"), NV_ENC_DX10 },
    { _T("DirectX11"), NV_ENC_DX11 },
    { NULL, NULL }
};

const CX_DESC list_mv_presicion[] = {
    { _T("auto"),     NV_ENC_MV_PRECISION_DEFAULT     },
    { _T("full-pel"), NV_ENC_MV_PRECISION_FULL_PEL    },
    { _T("half-pel"), NV_ENC_MV_PRECISION_HALF_PEL    },
    { _T("Q-pel"),    NV_ENC_MV_PRECISION_QUARTER_PEL },
    { NULL, NULL }
};

const CX_DESC list_mv_presicion_ja[] = {
    { _T("自動"),        NV_ENC_MV_PRECISION_DEFAULT     },
    { _T("1画素精度"),   NV_ENC_MV_PRECISION_FULL_PEL    },
    { _T("1/2画素精度"), NV_ENC_MV_PRECISION_HALF_PEL    },
    { _T("1/4画素精度"), NV_ENC_MV_PRECISION_QUARTER_PEL },
    { NULL, NULL }
};

const CX_DESC list_nvenc_rc_method[] = {
    { _T("CQP - 固定量子化量"),                     NV_ENC_PARAMS_RC_CONSTQP   },
    { _T("CBR - 固定ビットレート"),                 NV_ENC_PARAMS_RC_CBR       },
    { _T("CBR - 固定ビットレート (高品質)"),        NV_ENC_PARAMS_RC_CBR_HQ    },
    { _T("VBR - 可変ビットレート"),                 NV_ENC_PARAMS_RC_VBR       },
    { _T("VBR - 可変ビットレート (高品質)"),        NV_ENC_PARAMS_RC_VBR_HQ    },
    { NULL, NULL }
};

const CX_DESC list_nvenc_rc_method_en[] = {
    { _T("CQP"),                          NV_ENC_PARAMS_RC_CONSTQP   },
    { _T("CBR"),                          NV_ENC_PARAMS_RC_CBR       },
    { _T("CBRHQ"),                        NV_ENC_PARAMS_RC_CBR_HQ    },
    { _T("VBR"),                          NV_ENC_PARAMS_RC_VBR       },
    { _T("VBRHQ"),                        NV_ENC_PARAMS_RC_VBR_HQ    },
    { NULL, NULL }
};
const CX_DESC list_entropy_coding[] = {
    //{ _T("auto"),  NV_ENC_H264_ENTROPY_CODING_MODE_AUTOSELECT },
    { _T("cabac"), NV_ENC_H264_ENTROPY_CODING_MODE_CABAC      },
    { _T("cavlc"), NV_ENC_H264_ENTROPY_CODING_MODE_CAVLC      },
    { NULL, NULL }
};

const CX_DESC list_bdirect[] = {
    { _T("auto"),     NV_ENC_H264_BDIRECT_MODE_AUTOSELECT },
    { _T("disabled"), NV_ENC_H264_BDIRECT_MODE_DISABLE    },
    { _T("temporal"), NV_ENC_H264_BDIRECT_MODE_TEMPORAL   },
    { _T("spatial"),  NV_ENC_H264_BDIRECT_MODE_SPATIAL    },
    { NULL, NULL }
};

const CX_DESC list_bref_mode[] = {
    { _T("disabled"), NV_ENC_BFRAME_REF_MODE_DISABLED },
    { _T("each"),     NV_ENC_BFRAME_REF_MODE_EACH },
    { _T("middle"),   NV_ENC_BFRAME_REF_MODE_MIDDLE },
    { NULL, NULL }
};

const CX_DESC list_fmo[] = {
    { _T("auto"),     NV_ENC_H264_FMO_AUTOSELECT },
    { _T("enabled"),  NV_ENC_H264_FMO_ENABLE     },
    { _T("disabled"), NV_ENC_H264_FMO_DISABLE    },
    { NULL, NULL }
};
const CX_DESC list_adapt_transform[] = {
    { _T("auto"),     NV_ENC_H264_ADAPTIVE_TRANSFORM_AUTOSELECT },
    { _T("disabled"), NV_ENC_H264_ADAPTIVE_TRANSFORM_DISABLE    },
    { _T("enabled"),  NV_ENC_H264_ADAPTIVE_TRANSFORM_ENABLE     },
    { NULL, NULL }
};
const CX_DESC list_bitdepth[] = {
    { _T("8bit"),    0 },
    { _T("10bit"),   2 },
    { NULL, NULL }
};

enum : uint32_t {
    NV_ENC_AQ_DISABLED = 0x00,
    NV_ENC_AQ_SPATIAL  = 0x01,
    NV_ENC_AQ_TEMPORAL = 0x02,
    NV_ENC_AQ_BOTH     = NV_ENC_AQ_SPATIAL | NV_ENC_AQ_TEMPORAL,
};
const CX_DESC list_aq[] = {
    { _T("disabled"), NV_ENC_AQ_DISABLED },
    { _T("spatial"),  NV_ENC_AQ_SPATIAL },
    { _T("temporal"), NV_ENC_AQ_TEMPORAL },
    { _T("both"),     NV_ENC_AQ_BOTH },
    { NULL, NULL }
};
#if 0
const CX_DESC list_preset[] = {
    { _T("fast"),    NV_ENC_PRESET_HP      },
    { _T("default"), NV_ENC_PRESET_DEFAULT },
    { _T("best"),    NV_ENC_PRESET_HQ      },
    { _T("bluray"),  NV_ENC_PRESET_BD      },
    { NULL, NULL }
};
const CX_DESC list_preset_ja[] = {
    { _T("高速"),   NV_ENC_PRESET_HP       },
    { _T("標準"),   NV_ENC_PRESET_DEFAULT  },
    { _T("高品質"), NV_ENC_PRESET_HQ       },
    { _T("Bluray"), NV_ENC_PRESET_BD       },
    { NULL, NULL }
};
#endif

const CX_DESC list_deinterlace[] = {
    { _T("none"),     cudaVideoDeinterlaceMode_Weave    },
    { _T("bob"),      cudaVideoDeinterlaceMode_Bob      },
    { _T("adaptive"), cudaVideoDeinterlaceMode_Adaptive },
    { _T("normal"),   cudaVideoDeinterlaceMode_Adaptive },
    { NULL, 0 }
};

enum {
    NPPI_INTER_MAX = NPPI_INTER_LANCZOS3_ADVANCED,
    RESIZE_CUDA_TEXTURE_BILINEAR,
    RESIZE_CUDA_SPLINE36,
};

const CX_DESC list_nppi_resize[] = {
    { _T("default"),       NPPI_INTER_UNDEFINED },
#if !defined(_M_IX86) || FOR_AUO
    { _T("nn"),            NPPI_INTER_NN },
    { _T("npp_linear"),    NPPI_INTER_LINEAR },
    { _T("cubic"),         NPPI_INTER_CUBIC },
    { _T("cubic_bspline"), NPPI_INTER_CUBIC2P_BSPLINE },
    { _T("cubic_catmull"), NPPI_INTER_CUBIC2P_CATMULLROM },
    { _T("cubic_b05c03"),  NPPI_INTER_CUBIC2P_B05C03 },
    { _T("super"),         NPPI_INTER_SUPER },
    { _T("lanczos"),       NPPI_INTER_LANCZOS },
#endif
    //{ _T("lanczons3"),     NPPI_INTER_LANCZOS3_ADVANCED },
    { _T("bilinear"),      RESIZE_CUDA_TEXTURE_BILINEAR },
    { _T("spline36"),      RESIZE_CUDA_SPLINE36 },
    { NULL, NULL }
};

const CX_DESC list_nppi_resize_help[] = {
    { _T("default"),       NPPI_INTER_UNDEFINED },
    { _T("nn"),            NPPI_INTER_NN },
    { _T("npp_linear"),    NPPI_INTER_LINEAR },
    { _T("cubic"),         NPPI_INTER_CUBIC },
    //{ _T("cubic_bspline"), NPPI_INTER_CUBIC2P_BSPLINE },
    //{ _T("cubic_catmull"), NPPI_INTER_CUBIC2P_CATMULLROM },
    //{ _T("cubic_b05c03"),  NPPI_INTER_CUBIC2P_B05C03 },
    { _T("super"),         NPPI_INTER_SUPER },
    { _T("lanczos"),       NPPI_INTER_LANCZOS },
    //{ _T("lanczons3"),     NPPI_INTER_LANCZOS3_ADVANCED },
    { _T("bilinear"),      RESIZE_CUDA_TEXTURE_BILINEAR },
    { _T("spline36"),      RESIZE_CUDA_SPLINE36 },
    { NULL, NULL }
};


const CX_DESC list_vpp_denoise[] = {
    { _T("none"), 0 },
    { _T("knn"),  1 },
    { _T("pmd"),  2 },
    { NULL, NULL }
};

const CX_DESC list_vpp_detail_enahance[] = {
    { _T("none"),       0 },
    { _T("unsharp"),    1 },
    { _T("edgelevel"),  2 },
    { NULL, NULL }
};

const CX_DESC list_vpp_deband[] ={
    { _T("0 - 1点参照"),  0 },
    { _T("1 - 2点参照"),  1 },
    { _T("2 - 4点参照"),  2 },
    { NULL, NULL }
};

const CX_DESC list_nppi_gauss[] = {
    { _T("disabled"), 0 },
    { _T("3"), NPP_MASK_SIZE_3_X_3 },
    { _T("5"), NPP_MASK_SIZE_5_X_5 },
    { _T("7"), NPP_MASK_SIZE_7_X_7 },
    { NULL, NULL }
};

const CX_DESC list_cuvid_mode[] = {
    { _T("native"), NV_ENC_AVCUVID_NATIVE },
    { _T("cuda"),   NV_ENC_AVCUVID_CUDA   },
    { NULL, NULL }
};

const CX_DESC list_cuda_schedule[] = {
    { _T("auto"),  CU_CTX_SCHED_AUTO },
    { _T("spin"),  CU_CTX_SCHED_SPIN },
    { _T("yield"), CU_CTX_SCHED_YIELD },
    { _T("sync"),  CU_CTX_SCHED_BLOCKING_SYNC },
    { NULL, NULL }
};

template<size_t count>
static const TCHAR *get_name_from_guid(GUID guid, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (0 == memcmp(&desc[i].id, &guid, sizeof(GUID))) {
            return desc[i].desc;
        }
    }
    return _T("Unknown");
};

template<size_t count>
static const TCHAR *get_name_from_value(int value, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if ((int)desc[i].value == value) {
            return desc[i].desc;
        }
    }
    return _T("Unknown");
};

template<size_t count>
static int get_value_from_guid(GUID guid, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (0 == memcmp(&desc[i].id, &guid, sizeof(GUID))) {
            return desc[i].value;
        }
    }
    return 0;
};

template<size_t count>
static GUID get_guid_from_value(int value, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (desc[i].value == (uint32_t)value) {
            return desc[i].id;
        }
    }
    return GUID{ 0 };
};

template<size_t count>
static GUID get_guid_from_name(const TCHAR *name, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (0 == _tcsicmp(name, desc[i].desc)) {
            return desc[i].id;
        }
    }
    return GUID{ 0 };
};

template<size_t count>
static int get_value_from_name(const TCHAR *name, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (0 == _tcsicmp(name, desc[i].desc)) {
            return desc[i].value;
        }
    }
    return -1;
};

template<size_t count>
static int get_index_from_value(int value, const guid_desc (&desc)[count]) {
    for (int i = 0; i < count; i++) {
        if (desc[i].value == (uint32_t)value) {
            return i;
        }
    }
    return -1;
};

static inline bool is_interlaced(NV_ENC_PIC_STRUCT pic_struct) {
    return pic_struct != NV_ENC_PIC_STRUCT_FRAME;
}

typedef struct NVEncCap {
    int id;            //feature ID
    const TCHAR *name; //feature名
    bool isBool;       //値がtrue/falseの値
    int value;         //featureの制限値
} NVEncCap;

//指定したIDのfeatureの値を取得する
static int get_value(int id, const std::vector<NVEncCap>& capList) {
    for (auto cap_info : capList) {
        if (cap_info.id == id)
            return cap_info.value;
    }
    return 0;
}

struct VppDelogo {
    bool enable;
    tstring logoFilePath;  //ロゴファイル名
    tstring logoSelect;    //ロゴの名前
    int posX, posY; //位置オフセット
    int depth;      //透明度深度
    int Y, Cb, Cr;  //(輝度・色差)オフセット
    int mode;
    bool autoFade;
    bool autoNR;
    int NRArea;
    int NRValue;
    bool log;

    VppDelogo();
    bool operator==(const VppDelogo& x) const;
    bool operator!=(const VppDelogo& x) const;
};

struct VppUnsharp {
    bool  enable;
    int   radius;
    float weight;
    float threshold;

    VppUnsharp();
    bool operator==(const VppUnsharp& x) const;
    bool operator!=(const VppUnsharp& x) const;
};

struct VppEdgelevel {
    bool  enable;
    float strength;
    float threshold;
    float black;
    float white;

    VppEdgelevel();
    bool operator==(const VppEdgelevel& x) const;
    bool operator!=(const VppEdgelevel& x) const;
};

struct VppKnn {
    bool  enable;
    int   radius;
    float strength;
    float lerpC;
    float weight_threshold;
    float lerp_threshold;

    VppKnn();
    bool operator==(const VppKnn& x) const;
    bool operator!=(const VppKnn& x) const;
};

struct VppPmd {
    bool  enable;
    float strength;
    float threshold;
    int   applyCount;
    bool  useExp;

    VppPmd();
    bool operator==(const VppPmd& x) const;
    bool operator!=(const VppPmd& x) const;
};

struct VppDeband {
    bool enable;
    int range;
    int threY;
    int threCb;
    int threCr;
    int ditherY;
    int ditherC;
    int sample;
    int seed;
    bool blurFirst;
    bool randEachFrame;

    VppDeband();
    bool operator==(const VppDeband& x) const;
    bool operator!=(const VppDeband& x) const;
};

struct VppTweak {
    bool  enable;
    float brightness; // -1.0 - 1.0 (0.0)
    float contrast;   // -2.0 - 2.0 (1.0)
    float gamma;      //  0.1 - 10.0 (1.0)
    float saturation; //  0.0 - 3.0 (1.0)
    float hue;        // -180 - 180 (0.0)

    VppTweak();
    bool operator==(const VppTweak& x) const;
    bool operator!=(const VppTweak& x) const;
};

typedef struct {
    int top, bottom, left, right;
} AFS_SCAN_CLIP;

static inline AFS_SCAN_CLIP scan_clip(int top, int bottom, int left, int right) {
    AFS_SCAN_CLIP clip;
    clip.top = top;
    clip.bottom = bottom;
    clip.left = left;
    clip.right = right;
    return clip;
}

struct VppAfs {
    bool enable;
    int tb_order;
    AFS_SCAN_CLIP clip;    //上下左右
    int method_switch;     //切替点
    int coeff_shift;       //判定比
    int thre_shift;        //縞(ｼﾌﾄ)
    int thre_deint;        //縞(解除)
    int thre_Ymotion;      //Y動き
    int thre_Cmotion;      //C動き
    int analyze;           //解除Lv
    bool shift;            //フィールドシフト
    bool drop;             //間引き
    bool smooth;           //スムージング
    bool force24;          //24fps化
    bool tune;             //調整モード
    bool rff;              //rffフラグを認識して調整
    bool timecode;         //timecode出力
    bool log;              //log出力

    VppAfs();
    bool operator==(const VppAfs& x) const;
    bool operator!=(const VppAfs& x) const;

    void check();
};

struct VppPad {
    bool enable;
    int left, top, right, bottom;

    VppPad();
    bool operator==(const VppPad& x) const;
    bool operator!=(const VppPad& x) const;
};

enum {
    AFS_PRESET_DEFAULT = 0,
    AFS_PRESET_TRIPLE,        //動き重視
    AFS_PRESET_DOUBLE,        //二重化
    AFS_PRESET_ANIME,                     //映画/アニメ
    AFS_PRESET_CINEMA = AFS_PRESET_ANIME, //映画/アニメ
    AFS_PRESET_MIN_AFTERIMG,              //残像最小化
    AFS_PRESET_FORCE24_SD,                //24fps固定
    AFS_PRESET_FORCE24_HD,                //24fps固定 (HD)
    AFS_PRESET_FORCE30,                   //30fps固定
};

const CX_DESC list_afs_preset[] = {
    { _T("default"),      AFS_PRESET_DEFAULT },
    { _T("triple"),       AFS_PRESET_TRIPLE },
    { _T("double"),       AFS_PRESET_DOUBLE },
    { _T("anime/cinema"), AFS_PRESET_ANIME },
    { _T("anime"),        AFS_PRESET_ANIME },
    { _T("cinema"),       AFS_PRESET_CINEMA },
    { _T("min_afterimg"), AFS_PRESET_MIN_AFTERIMG },
    { _T("24fps"),        AFS_PRESET_FORCE24_HD },
    { _T("24fps_sd"),     AFS_PRESET_FORCE24_SD },
    { _T("30fps"),        AFS_PRESET_FORCE30 },
    { NULL, NULL }
};

struct VppParam {
    bool bCheckPerformance;
    cudaVideoDeinterlaceMode deinterlace;
    int                      resizeInterp;
    NppiMaskSize             gaussMaskSize;

    VppDelogo delogo;
    VppUnsharp unsharp;
    VppEdgelevel edgelevel;
    VppKnn knn;
    VppPmd pmd;
    VppDeband deband;
    VppAfs afs;
    VppTweak tweak;
    VppPad pad;
    bool rff;

    VppParam();
};

struct InEncodeVideoParam {
    VideoInfo input;              //入力する動画の情報
    tstring inputFilename;        //入力ファイル名
    tstring outputFilename;       //出力ファイル名
    tstring sAVMuxOutputFormat;   //出力フォーマット
    int preset;                   //出力プリセット
    int deviceID;                 //使用するGPUのID
    int nHWDecType;               //
    int par[2];                   //使用されていません
    NV_ENC_CONFIG encConfig;      //エンコード設定
    int codec;                    //出力コーデック
    int bluray;                   //bluray出力
    int yuv444;                   //YUV444出力
    int lossless;                 //ロスレス出力
    std::string sMaxCll;
    std::string sMasterDisplay;
    tstring logfile;              //ログ出力先
    int loglevel;                 //ログ出力レベル
    int nOutputBufSizeMB;         //出力バッファサイズ
    tstring sFramePosListLog;     //framePosList出力先
    float fSeekSec;               //指定された秒数分先頭を飛ばす
    int nSubtitleSelectCount;
    int *pSubtitleSelect;
    int nAudioSourceCount;
    TCHAR **ppAudioSourceList;
    int nAudioSelectCount; //pAudioSelectの数
    sAudioSelect **ppAudioSelectList;
    int nAudioResampler;
    int nAVDemuxAnalyzeSec;
    int nAVMux;                       //RGY_MUX_xxx
    int nVideoTrack;
    int nVideoStreamId;
    int nTrimCount;
    sTrim *pTrimList;
    bool bCopyChapter;
    bool keyOnChapter;
    bool caption2ass;
    int nOutputThread;
    int nAudioThread;
    int nInputThread;
    int nAudioIgnoreDecodeError;
    muxOptList *pMuxOpt;
    tstring sChapterFile;
    tstring keyFile;
    TCHAR *pMuxVidTsLogFile;
    TCHAR *pAVInputFormat;
    RGYAVSync nAVSyncMode;     //avsyncの方法 (NV_AVSYNC_xxx)
    int nProcSpeedLimit;      //処理速度制限 (0で制限なし)
    VppParam vpp;                 //vpp
    int nWeightP;
    int64_t nPerfMonitorSelect;
    int64_t nPerfMonitorSelectMatplot;
    int     nPerfMonitorInterval;
    int     nCudaSchedule;
    void *pPrivatePrm;

    InEncodeVideoParam();
};

NV_ENC_CONFIG DefaultParam();
NV_ENC_CODEC_CONFIG DefaultParamH264();
NV_ENC_CODEC_CONFIG DefaultParamHEVC();
