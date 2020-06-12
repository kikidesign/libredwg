/*****************************************************************************/
/*  LibreDWG - free implementation of the DWG file format                    */
/*                                                                           */
/*  Copyright (C) 2009-2010,2018-2020 Free Software Foundation, Inc.         */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 3 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

/*
 * dwg.h: main public header file (the other variant is dwg_api.h)
 *
 * written by Felipe Castro
 * modified by Felipe Corrêa da Silva Sances
 * modified by Rodrigo Rodrigues da Silva
 * modified by Till Heuschmann
 * modified by Reini Urban
 */

#ifndef DWG_H
#define DWG_H

#define LIBREDWG_VERSION_MAJOR 0
#define LIBREDWG_VERSION_MINOR 10
#define LIBREDWG_VERSION       ((LIBREDWG_VERSION_MAJOR * 100) + LIBREDWG_VERSION_MINOR)
#define LIBREDWG_SO_VERSION    0:10:0

/* for uint64_t, but not in swig */
#ifndef SWIGIMPORTED
#  include <stdint.h>
#  include <inttypes.h>

/* wchar for R2007+ support
 * But we need the win32 UTF-16 variant, not UTF-32.
 * i.e. only on Windows, AIX, Solaris
 */
# if defined(HAVE_WCHAR_H) && defined(SIZEOF_WCHAR_T) && SIZEOF_WCHAR_T == 2
#  include <wchar.h>
#  define HAVE_NATIVE_WCHAR2
#  define DWGCHAR wchar_t
#  define dwg_wchar_t wchar_t
# endif
#endif

#ifndef EXPORT
# ifdef SWIG
#  define EXPORT extern
# elif defined(_WIN32) && defined(ENABLE_SHARED)
#  ifdef DLL_EXPORT
#    define EXPORT  __declspec(dllexport)
#  else
#    define EXPORT  __declspec(dllimport)
#  endif
# elif defined(__clang__) || defined(__clang) || \
        (defined( __GNUC__) && ((__GNUC__ * 100) + __GNUC_MINOR__) >= 303)
#  define EXPORT __attribute__((visibility("default")))
# else
#  define EXPORT
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BITCODE_DOUBLE double

/* The FORMAT_* are for logging only */
typedef unsigned char BITCODE_RC;
#ifdef _WIN32
# define FORMAT_RC "0x%2x"
#else
# define FORMAT_RC "0x%hhx"
#endif
#define FORMAT_RCd "%d"
#define FORMAT_RCu "%u"
#define FORMAT_RCx "0x%x"
typedef signed char BITCODE_RCd;
typedef unsigned char BITCODE_RCu;
typedef unsigned char BITCODE_RCx;
typedef unsigned char BITCODE_B;
#define FORMAT_B "%d"
typedef unsigned char BITCODE_BB;
#define FORMAT_BB "%u"
/* Since R24 */
typedef unsigned char BITCODE_3B;
#define FORMAT_3B "%u"
//#ifdef HAVE_STDINT_H
//#define BITCODE_BS uint16_t
//#define BITCODE_RS uint16_t
//#define BITCODE_BL uint32_t
//#define BITCODE_RL uint32_t
//#define BITCODE_BLd int32_t
//#define BITCODE_RLd int32_t
typedef uint16_t BITCODE_BS;
typedef int16_t BITCODE_BSd;
typedef uint16_t BITCODE_BSx;
typedef uint16_t BITCODE_RS;
typedef uint16_t BITCODE_RSx;
typedef uint32_t BITCODE_BL;
typedef uint32_t BITCODE_BLx;
typedef int32_t BITCODE_BLd;
typedef uint32_t BITCODE_RL;
typedef uint32_t BITCODE_RLx;
typedef int32_t BITCODE_RLd;
/* e.g. old cygwin 64 vs 32 */
/*#else
# if defined(__WORDSIZE) && __WORDSIZE == 64
  typedef unsigned short int BITCODE_BS;
  typedef unsigned short int BITCODE_RS;
  typedef unsigned int BITCODE_BL;
  typedef unsigned int BITCODE_RL;
  typedef int BITCODE_BLd;
  typedef int BITCODE_RLd;
# else
  typedef unsigned short int BITCODE_BS;
  typedef unsigned short int BITCODE_RS;
  typedef unsigned long BITCODE_BL;
  typedef unsigned long BITCODE_RL;
  typedef long BITCODE_BLd;
  typedef long BITCODE_RLd;
# endif
#endif
*/
//#ifdef HAVE_INTTYPES_H
#define FORMAT_BS "%" PRIu16
#define FORMAT_BSd "%" PRId16
#define FORMAT_BSx "0x%" PRIx16
#define FORMAT_RS "%" PRIu16
#define FORMAT_RSx "0x%" PRIx16
#define FORMAT_BL "%" PRIu32
#define FORMAT_RL "%" PRIu32
#define FORMAT_BLd "%" PRId32
#define FORMAT_RLd "%" PRId32
#define FORMAT_RLx "0x%" PRIx32
#define FORMAT_BLX "%" PRIX32
#define FORMAT_BLx "0x%" PRIx32
/*#else
# define FORMAT_BS "%hu"
# define FORMAT_RS "%hu"
# define FORMAT_BL "%u"
# define FORMAT_RL "%u"
# define FORMAT_BLd "%d"
# define FORMAT_RLd "%d"
# define FORMAT_BLX "%X"
# define FORMAT_BLx "%x"
#endif
*/
typedef long BITCODE_MC;
#define FORMAT_MC  "%ld"
typedef unsigned long BITCODE_UMC;
#define FORMAT_UMC "%lu"
typedef BITCODE_BL BITCODE_MS;
#define FORMAT_MS FORMAT_BL
typedef BITCODE_DOUBLE BITCODE_RD;
#define FORMAT_RD "%f"
/* Since R2004 */
typedef uint64_t BITCODE_RLL;
typedef uint64_t BITCODE_BLL;
#define FORMAT_RLL "0x%" PRIx64
#define FORMAT_BLL "%" PRIu64
#ifndef HAVE_NATIVE_WCHAR2
  typedef BITCODE_RS dwg_wchar_t;
# define DWGCHAR dwg_wchar_t
#endif
typedef unsigned char* BITCODE_TF;
#define FORMAT_TF "\"%s\""
typedef char* BITCODE_TV;
#define FORMAT_TV "\"%s\""
#define BITCODE_T16 BITCODE_TV
#define FORMAT_T16 "\"%s\""
#define BITCODE_T32 BITCODE_TV
#define FORMAT_T32 "\"%s\""
#define BITCODE_TU32 BITCODE_TV
#define FORMAT_TU32 "\"%s\""
typedef BITCODE_DOUBLE BITCODE_BT;
#define FORMAT_BT "%f"
typedef BITCODE_DOUBLE BITCODE_DD;
#define FORMAT_DD "%f"
typedef BITCODE_DOUBLE BITCODE_BD;
#define FORMAT_BD "%f"
typedef BITCODE_RC BITCODE_4BITS;
#define FORMAT_4BITS "%1x"
/* double stored as string. ATEXT */
typedef BITCODE_TV BITCODE_D2T;
#define FORMAT_D2T "%s"

/* TODO: implement version dependent string parsing */
/* encode codepages/utf8 */
#define BITCODE_T  BITCODE_TV
#ifdef HAVE_NATIVE_WCHAR2
  typedef dwg_wchar_t* BITCODE_TU; /* native UCS-2 wchar_t */
# define FORMAT_TU "\"%ls\""
#else
  typedef BITCODE_RS* BITCODE_TU;  /* UCS-2 unicode text */
# define FORMAT_TU "\"%hn\""       /* will print garbage */
#endif

typedef struct _dwg_time_bll
{
  BITCODE_BL days;
  BITCODE_BL ms;
  BITCODE_BD value;
} Dwg_Bitcode_TimeBLL;

typedef struct _dwg_bitcode_2rd
{
  BITCODE_RD x;
  BITCODE_RD y;
} Dwg_Bitcode_2RD;

typedef struct _dwg_bitcode_2bd
{
  BITCODE_BD x;
  BITCODE_BD y;
} Dwg_Bitcode_2BD;

typedef struct _dwg_bitcode_3rd
{
  BITCODE_RD x;
  BITCODE_RD y;
  BITCODE_RD z;
} Dwg_Bitcode_3RD;

typedef struct _dwg_bitcode_3bd
{
  BITCODE_BD x;
  BITCODE_BD y;
  BITCODE_BD z;
} Dwg_Bitcode_3BD;

typedef Dwg_Bitcode_TimeBLL BITCODE_TIMEBLL;
typedef Dwg_Bitcode_TimeBLL BITCODE_TIMERLL;
/* #define FORMAT_TIMEBLL FORMAT_BL "." FORMAT_BL */
typedef Dwg_Bitcode_2RD  BITCODE_2RD;
typedef Dwg_Bitcode_2BD  BITCODE_2BD;
typedef Dwg_Bitcode_2BD  BITCODE_2DPOINT;
typedef Dwg_Bitcode_2BD  BITCODE_2BD_1;
typedef Dwg_Bitcode_3RD  BITCODE_3RD;
typedef Dwg_Bitcode_3BD  BITCODE_3BD;
typedef Dwg_Bitcode_3BD  BITCODE_3DPOINT;
typedef Dwg_Bitcode_3BD  BITCODE_3BD_1;
typedef Dwg_Bitcode_3BD  BITCODE_BE;
#define BITCODE_3DVECTOR BITCODE_3BD_1

typedef enum DWG_VERSION_TYPE
{
  R_INVALID,
  R_1_1,	/* MC0.0  MicroCAD Release 1.1 */
  R_1_2,	/* AC1.2  AutoCAD Release 1.2 */
  R_1_3,	/* AC1.3  AutoCAD Release 1.3 */
  R_1_4,	/* AC1.40 AutoCAD Release 1.4 */
  R_2_0,	/* AC1.50 AutoCAD Release 2.0 */
  R_2_1,	/* AC2.10 AutoCAD Release 2.10 */
  R_2_4,	/* AC1001 AutoCAD Release 2.4 */
  R_2_5,	/* AC1002 AutoCAD Release 2.5 */
  R_2_6,	/* AC1003 AutoCAD Release 2.6 */
  R_9,		/* AC1004 AutoCAD Release 9 */
  R_10,		/* AC1006 AutoCAD Release 10 */
  R_11,		/* AC1009 AutoCAD Release 11/12 (LT R1/R2) */
  R_13,		/* AC1012 AutoCAD Release 13 */
  R_13c3,	/* AC1013 AutoCAD Release 13C3 */
  R_14,		/* AC1014 AutoCAD Release 14 */
  R_2000,	/* AC1015 AutoCAD Release 2000 */
  R_2004,	/* AC1018 AutoCAD Release 2004 (includes versions AC1019/0x19 and AC1020/0x1a) */
  R_2007,	/* AC1021 AutoCAD Release 2007 */
  R_2010,	/* AC1024 AutoCAD Release 2010 */
  R_2013,	/* AC1027 AutoCAD Release 2013 */
  R_2018,	/* AC1032 AutoCAD Release 2018 */
  R_AFTER
} Dwg_Version_Type;
#define DWG_VERSIONS (int)(R_AFTER+1)

/**
 Object supertypes that exist in dwg-files.
 */
typedef enum DWG_OBJECT_SUPERTYPE
{
  DWG_SUPERTYPE_ENTITY, DWG_SUPERTYPE_OBJECT
} Dwg_Object_Supertype;

/**
 Object and Entity types that exist in dwg-files.
 */
typedef enum DWG_OBJECT_TYPE
{
  DWG_TYPE_UNUSED = 0x00,
  DWG_TYPE_TEXT = 0x01,
  DWG_TYPE_ATTRIB = 0x02,
  DWG_TYPE_ATTDEF = 0x03,
  DWG_TYPE_BLOCK = 0x04,
  DWG_TYPE_ENDBLK = 0x05,
  DWG_TYPE_SEQEND = 0x06,
  DWG_TYPE_INSERT = 0x07,
  DWG_TYPE_MINSERT = 0x08,
  /* DWG_TYPE_<UNKNOWN> = 0x09, */
  DWG_TYPE_VERTEX_2D = 0x0a,
  DWG_TYPE_VERTEX_3D = 0x0b,
  DWG_TYPE_VERTEX_MESH = 0x0c,
  DWG_TYPE_VERTEX_PFACE = 0x0d,
  DWG_TYPE_VERTEX_PFACE_FACE = 0x0e,
  DWG_TYPE_POLYLINE_2D = 0x0f,
  DWG_TYPE_POLYLINE_3D = 0x10,
  DWG_TYPE_ARC = 0x11,
  DWG_TYPE_CIRCLE = 0x12,
  DWG_TYPE_LINE = 0x13,
  DWG_TYPE_DIMENSION_ORDINATE = 0x14,
  DWG_TYPE_DIMENSION_LINEAR = 0x15,
  DWG_TYPE_DIMENSION_ALIGNED = 0x16,
  DWG_TYPE_DIMENSION_ANG3PT = 0x17,
  DWG_TYPE_DIMENSION_ANG2LN = 0x18,
  DWG_TYPE_DIMENSION_RADIUS = 0x19,
  DWG_TYPE_DIMENSION_DIAMETER = 0x1A,
  DWG_TYPE_POINT = 0x1b,
  DWG_TYPE__3DFACE = 0x1c,
  DWG_TYPE_POLYLINE_PFACE = 0x1d,
  DWG_TYPE_POLYLINE_MESH = 0x1e,
  DWG_TYPE_SOLID = 0x1f,
  DWG_TYPE_TRACE = 0x20,
  DWG_TYPE_SHAPE = 0x21,
  DWG_TYPE_VIEWPORT = 0x22,
  DWG_TYPE_ELLIPSE = 0x23,
  DWG_TYPE_SPLINE = 0x24,
  DWG_TYPE_REGION = 0x25,
  DWG_TYPE__3DSOLID = 0x26,
  DWG_TYPE_BODY = 0x27,
  DWG_TYPE_RAY = 0x28,
  DWG_TYPE_XLINE = 0x29,
  DWG_TYPE_DICTIONARY = 0x2a,
  DWG_TYPE_OLEFRAME = 0x2b,
  DWG_TYPE_MTEXT = 0x2c,
  DWG_TYPE_LEADER = 0x2d,
  DWG_TYPE_TOLERANCE = 0x2e,
  DWG_TYPE_MLINE = 0x2f,
  DWG_TYPE_BLOCK_CONTROL = 0x30,
  DWG_TYPE_BLOCK_HEADER = 0x31,
  DWG_TYPE_LAYER_CONTROL = 0x32,
  DWG_TYPE_LAYER = 0x33,
  DWG_TYPE_STYLE_CONTROL = 0x34,
  DWG_TYPE_STYLE = 0x35,
  /* DWG_TYPE_<UNKNOWN> = 0x36, */
  /* DWG_TYPE_<UNKNOWN> = 0x37, */
  DWG_TYPE_LTYPE_CONTROL = 0x38,
  DWG_TYPE_LTYPE = 0x39,
  /* DWG_TYPE_<UNKNOWN> = 0x3a, */
  /* DWG_TYPE_<UNKNOWN> = 0x3b, */
  DWG_TYPE_VIEW_CONTROL = 0x3c,
  DWG_TYPE_VIEW = 0x3d,
  DWG_TYPE_UCS_CONTROL = 0x3e,
  DWG_TYPE_UCS = 0x3f,
  DWG_TYPE_VPORT_CONTROL = 0x40,
  DWG_TYPE_VPORT = 0x41,
  DWG_TYPE_APPID_CONTROL = 0x42,
  DWG_TYPE_APPID = 0x43,
  DWG_TYPE_DIMSTYLE_CONTROL = 0x44,
  DWG_TYPE_DIMSTYLE = 0x45,
  DWG_TYPE_VPORT_ENTITY_CONTROL = 0x46,
  DWG_TYPE_VPORT_ENTITY_HEADER = 0x47,
  DWG_TYPE_GROUP = 0x48,
  DWG_TYPE_MLINESTYLE = 0x49,
  DWG_TYPE_OLE2FRAME = 0x4a,
  DWG_TYPE_DUMMY = 0x4b,
  DWG_TYPE_LONG_TRANSACTION = 0x4c,
  DWG_TYPE_LWPOLYLINE = 0x4d, /* ?? */
  DWG_TYPE_HATCH = 0x4e,
  DWG_TYPE_XRECORD = 0x4f,
  DWG_TYPE_PLACEHOLDER = 0x50,
  DWG_TYPE_VBA_PROJECT = 0x51,
  DWG_TYPE_LAYOUT = 0x52,

  DWG_TYPE_PROXY_ENTITY = 0x1f2, /* 498 */
  DWG_TYPE_PROXY_OBJECT = 0x1f3, /* 499 */

  /* non-fixed types > 500. not stored as type, but as fixedtype */

  DWG_TYPE_ACDSRECORD = 0x1ff + 1,
  DWG_TYPE_ACDSSCHEMA,
  DWG_TYPE_ACMECOMMANDHISTORY,
  DWG_TYPE_ACMESCOPE,
  DWG_TYPE_ACMESTATEMGR,
  DWG_TYPE_ACSH_BOX_CLASS,
  DWG_TYPE_ACSH_BREP_CLASS,
  DWG_TYPE_ACSH_CHAMFER_CLASS,
  DWG_TYPE_ACSH_EXTRUSION_CLASS,
  DWG_TYPE_ACSH_FILLET_CLASS,
  DWG_TYPE_ACSH_HISTORY_CLASS,
  DWG_TYPE_ACSH_LOFT_CLASS,
  DWG_TYPE_ACSH_PYRAMID_CLASS,
  DWG_TYPE_ACSH_REVOLVE_CLASS,
  DWG_TYPE_ACSH_SPHERE_CLASS,
  DWG_TYPE_ACSH_SWEEP_CLASS,
  DWG_TYPE_ACSH_TORUS_CLASS,
  DWG_TYPE_ACSH_WEDGE_CLASS,
  DWG_TYPE_ALDIMOBJECTCONTEXTDATA,
  DWG_TYPE_ARC_DIMENSION,
  DWG_TYPE_ASSOC2DCONSTRAINTGROUP,
  DWG_TYPE_ASSOCACTION,
  DWG_TYPE_ASSOCALIGNEDDIMACTIONBODY,
  DWG_TYPE_ASSOCDEPENDENCY,
  DWG_TYPE_ASSOCEXTRUDEDSURFACEACTIONBODY,
  DWG_TYPE_ASSOCGEOMDEPENDENCY,
  DWG_TYPE_ASSOCLOFTEDSURFACEACTIONBODY,
  DWG_TYPE_ASSOCNETWORK,
  DWG_TYPE_ASSOCOSNAPPOINTREFACTIONPARAM,
  DWG_TYPE_ASSOCPERSSUBENTMANAGER,
  DWG_TYPE_ASSOCPLANESURFACEACTIONBODY,
  DWG_TYPE_ASSOCREVOLVEDSURFACEACTIONBODY,
  DWG_TYPE_ASSOCSWEPTSURFACEACTIONBODY,
  DWG_TYPE_ASSOCVERTEXACTIONPARAM,
  DWG_TYPE_ATEXT,
  DWG_TYPE_BACKGROUND,
  DWG_TYPE_BLKREFOBJECTCONTEXTDATA,
  DWG_TYPE_BLOCKGRIPLOCATIONCOMPONENT,
  DWG_TYPE_BLOCKVISIBILITYPARAMETER,
  DWG_TYPE_BLOCKVISIBILITYGRIP,
  DWG_TYPE_CAMERA,
  DWG_TYPE_CELLSTYLEMAP,
  DWG_TYPE_CSACDOCUMENTOPTIONS,
  DWG_TYPE_CONTEXTDATAMANAGER,
  DWG_TYPE_CURVEPATH,
  DWG_TYPE_DATALINK,
  DWG_TYPE_DATATABLE,
  DWG_TYPE_DBCOLOR,
  DWG_TYPE_DETAILVIEWSTYLE,
  DWG_TYPE_DICTIONARYVAR,
  DWG_TYPE_DICTIONARYWDFLT,
  DWG_TYPE_DIMASSOC,
  DWG_TYPE_DYNAMICBLOCKPURGEPREVENTER,
  DWG_TYPE_EVALUATION_GRAPH,
  DWG_TYPE_EXTRUDEDSURFACE,
  DWG_TYPE_FCFOBJECTCONTEXTDATA,
  DWG_TYPE_FIELD,
  DWG_TYPE_FIELDLIST,
  DWG_TYPE_GEODATA,
  DWG_TYPE_GEOMAPIMAGE,
  DWG_TYPE_GEOPOSITIONMARKER,
  DWG_TYPE_HELIX,
  DWG_TYPE_IDBUFFER,
  DWG_TYPE_IMAGE,
  DWG_TYPE_IMAGEDEF,
  DWG_TYPE_IMAGEDEF_REACTOR,
  DWG_TYPE_LAYER_INDEX,
  DWG_TYPE_LAYERFILTER,
  DWG_TYPE_LAYOUTPRINTCONFIG,
  DWG_TYPE_LEADEROBJECTCONTEXTDATA,
  DWG_TYPE_LIGHT,
  DWG_TYPE_LIGHTLIST,
  DWG_TYPE_LOFTEDSURFACE,
  DWG_TYPE_MATERIAL,
  DWG_TYPE_MENTALRAYRENDERSETTINGS,
  DWG_TYPE_MESH,
  DWG_TYPE_MLEADEROBJECTCONTEXTDATA,
  DWG_TYPE_MLEADERSTYLE,
  DWG_TYPE_MOTIONPATH,
  DWG_TYPE_MTEXTATTRIBUTEOBJECTCONTEXTDATA,
  DWG_TYPE_MTEXTOBJECTCONTEXTDATA,
  DWG_TYPE_MULTILEADER,
  DWG_TYPE_NAVISWORKSMODEL,
  DWG_TYPE_NAVISWORKSMODELDEF,
  DWG_TYPE_NPOCOLLECTION,
  DWG_TYPE_NURBSURFACE,
  DWG_TYPE_OBJECT_PTR,
  DWG_TYPE_OBJECTCONTEXTDATA,
  DWG_TYPE_PERSUBENTMGR,
  DWG_TYPE_PLANESURFACE,
  DWG_TYPE_PLOTSETTINGS,
  DWG_TYPE_POINTCLOUD,
  DWG_TYPE_POINTPATH,
  DWG_TYPE_RAPIDRTRENDERENVIRONMENT,
  DWG_TYPE_RAPIDRTRENDERSETTINGS,
  DWG_TYPE_RASTERVARIABLES,
  DWG_TYPE_RENDERENVIRONMENT,
  DWG_TYPE_RENDERENTRY,
  DWG_TYPE_RENDERGLOBAL,
  DWG_TYPE_RENDERSETTINGS,
  DWG_TYPE_REVOLVEDSURFACE,
  DWG_TYPE_RTEXT,
  DWG_TYPE_SCALE,
  DWG_TYPE_SECTIONOBJECT,
  DWG_TYPE_SECTIONVIEWSTYLE,
  DWG_TYPE_SECTION_MANAGER,
  DWG_TYPE_SECTION_SETTINGS,
  DWG_TYPE_SORTENTSTABLE,
  DWG_TYPE_SPATIAL_FILTER,
  DWG_TYPE_SPATIAL_INDEX,
  DWG_TYPE_SUN,
  DWG_TYPE_SUNSTUDY,
  DWG_TYPE_SWEPTSURFACE,
  DWG_TYPE_TABLE,
  DWG_TYPE_TABLECONTENT,
  DWG_TYPE_TABLEGEOMETRY,
  DWG_TYPE_TABLESTYLE,
  DWG_TYPE_TEXTOBJECTCONTEXTDATA,
  DWG_TYPE_TVDEVICEPROPERTIES,
  DWG_TYPE_UNDERLAY, /* not separate DGN,DWF,PDF types */
  DWG_TYPE_UNDERLAYDEFINITION, /* not separate DGN,DWF,PDF types */
  DWG_TYPE_VISIBILITYGRIPENTITY,
  DWG_TYPE_VISIBILITYPARAMETERENTITY,
  DWG_TYPE_VISUALSTYLE,
  DWG_TYPE_WIPEOUT,
  DWG_TYPE_WIPEOUTVARIABLES,
  DWG_TYPE_XREFPANELOBJECT,
  // after 1.0 add new types here for binary compat

  DWG_TYPE_FREED       = 0xfffd,
  DWG_TYPE_UNKNOWN_ENT = 0xfffe,
  DWG_TYPE_UNKNOWN_OBJ = 0xffff,
} Dwg_Object_Type;

/**
 Error codes returned.
 */
typedef enum DWG_ERROR
{
  DWG_NOERR = 0,
  /* sorted by severity */
  DWG_ERR_WRONGCRC         = 1,
  DWG_ERR_NOTYETSUPPORTED  = 1 << 1, /* 2 */
  DWG_ERR_UNHANDLEDCLASS   = 1 << 2, /* 4 */
  DWG_ERR_INVALIDTYPE      = 1 << 3, /* 8 */
  DWG_ERR_INVALIDHANDLE    = 1 << 4, /* 16 */
  DWG_ERR_INVALIDEED       = 1 << 5, /* 32 */
  DWG_ERR_VALUEOUTOFBOUNDS = 1 << 6, /* 64 */
  /* -------- critical errors ------- */
  DWG_ERR_CLASSESNOTFOUND  = 1 << 7, /* 128 */
  DWG_ERR_SECTIONNOTFOUND  = 1 << 8, /* 256 */
  DWG_ERR_PAGENOTFOUND     = 1 << 9, /* 512 */
  DWG_ERR_INTERNALERROR    = 1 << 10,/* 1024 */
  DWG_ERR_INVALIDDWG       = 1 << 11,/* 2048 */
  DWG_ERR_IOERROR          = 1 << 12,/* 4096 */
  DWG_ERR_OUTOFMEM         = 1 << 13,/* 8192 */

} Dwg_Error;
#define DWG_ERR_CRITICAL DWG_ERR_CLASSESNOTFOUND

/**
   handles resolve absolute or relative indices to objects.

   code 2-5: represents the type of the relation: hard/soft, owner/id.

   code TYPEDOBJHANDLE:
    2 Soft owner,
    3 Hard owner,
    4 Soft pointer,
    5 Hard pointer

   code > 6: the handle is stored as an offset from some other handle.

   code OFFSETOBJHANDLE for soft owners or pointers:
    6 ref + 1,
    8 ref - 1,
    a ref + offset,
    c ref - offset

  See \ref Dwg_Handle
 */
typedef struct _dwg_handle
{
  BITCODE_RC code; /*!< OFFSETOBJHANDLE if > 6 */
  BITCODE_RC size;
  unsigned long value;
  BITCODE_B is_global; // to be freed or not
} Dwg_Handle;

#define FORMAT_H "%u.%u.%lX"
#define ARGS_H(hdl) (hdl).code, (hdl).size, (hdl).value
#define FORMAT_REF "(%u.%u.%lX) abs:%lX"
#define ARGS_REF(ref) (ref)->handleref.code, (ref)->handleref.size, \
    (ref)->handleref.value, (ref)->absolute_ref

/**
object references: obj is resolved by handleref (e.g. via
dwg_resolve_handleref) when reading a DWG to the respective \ref
Dwg_Object, and absolute_ref is resolved to the global
_dwg_struct::object_ref index. It is the same as the hex number in the
DXF handles.

Used as \ref Dwg_Object_Ref
*/
typedef struct _dwg_object_ref
{
  struct _dwg_object* obj;
  Dwg_Handle handleref;
  unsigned long absolute_ref;
} Dwg_Object_Ref;

typedef Dwg_Object_Ref* BITCODE_H;

typedef enum DWG_HDL_CODE
{
   DWG_HDL_OWNER   = 0,
   DWG_HDL_SOFTOWN = 2,
   DWG_HDL_HARDOWN = 3,
   DWG_HDL_SOFTPTR = 4, // can be relative
   DWG_HDL_HARDPTR = 5,
} Dwg_Hdl_Code;

/**
 CMC or ENC colors: color index or rgb value. layers are off when the index
 is negative.
 Used as \ref Dwg_Color
 */
typedef struct _dwg_color /* CmColor: R15 and earlier */
{
  BITCODE_BSd index;  /* <0: turned off. 0: BYBLOCK, 256: BYLAYER */
  BITCODE_BS flag;    /* 1: has name, 2: has book_name. */
  BITCODE_BS raw;     /* ENC only */
  BITCODE_BL rgb;     /* DXF 420 */
  unsigned method;    /* first byte of rgb:
                         0xc0 for ByLayer (also c3 and rgb of 0x100)
                         0xc1 for ByBlock (also c3 and rgb of 0)
                         0xc2 for entities (default), with names with an additional name flag RC,
                         0xc3 for truecolor,
                         0xc5 for foreground color
                         0xc8 for none (also c3 and rgb of 0x101)
                       */
  BITCODE_T  name;       /* DXF 430 */
  BITCODE_T  book_name;  /* DXF 430, DXF: "book_name$name" */
  // Entities only:
  BITCODE_H  handle;
  BITCODE_BB alpha_type; /* 0 BYLAYER, 1 BYBLOCK, 3 alpha */
  BITCODE_RC alpha;      /* DXF 440. 0-255 */
} Dwg_Color;

typedef Dwg_Color BITCODE_CMC;
typedef Dwg_Color BITCODE_CMTC; // truecolor even before r2004
typedef Dwg_Color BITCODE_ENC;

EXPORT const char* dwg_color_method_name (unsigned method);

/**
 ASCII or Unicode text in xdata \ref Dwg_Resbuf
 */
struct _dwg_binary_chunk
{
  short size;
  int  codepage;
  union {
    char *data;
    DWGCHAR *wdata;
  } u;
};

/**
 result buffers: xdata linked list of dxf group - value pairs.
 Used as \ref Dwg_Resbuf
 */
typedef struct _dwg_resbuf
{
  short type;
  union
  {
    double  pt[3];
    char    i8;
    short   i16;
    int     i32;
    BITCODE_BLL i64;
    double  dbl;
    unsigned char hdl[8];
    Dwg_Handle h;
    struct _dwg_binary_chunk str;
  } value;
  struct _dwg_resbuf *nextrb;
} Dwg_Resbuf;

/**
 \struct Dwg_Header_Variables
 DWG header variables for all versions.
 If uppercase related to the DXF HEADER $ name.

 \ref _dwg_header_variables
 */
typedef struct _dwg_header_variables {
  BITCODE_RL size;
  BITCODE_RL bitsize_hi;   /*!< r2010+ */
  BITCODE_RL bitsize;
  BITCODE_RC ACADMAINTVER; /*!< r13+ */
  BITCODE_BLL REQUIREDVERSIONS; /*!< r2013+ */
  BITCODE_TV DWGCODEPAGE;  /*!< r10+ */
  BITCODE_BD unknown_0; /* 412148564080.0 */
  BITCODE_BD unknown_1; /* 1.0 */
  BITCODE_BD unknown_2; /* 1.0 */
  BITCODE_BD unknown_3; /* 1.0 */
  BITCODE_TV unknown_text1; /* "" 4x pre 2007... */
  BITCODE_TV unknown_text2; /* "" */
  BITCODE_TV unknown_text3; /* "" */
  BITCODE_TV unknown_text4; /* "" */
  BITCODE_BL unknown_8; /* 24L */
  BITCODE_BL unknown_9; /* 0L */
  BITCODE_BS unknown_10; /* 0 r13-r14 */
  BITCODE_H VPORT_ENTITY_HEADER; /*!< r11-r2000 */
  BITCODE_B DIMASO;
  BITCODE_B DIMSHO;
  BITCODE_B DIMSAV; /* undocumented */
  BITCODE_B PLINEGEN;
  BITCODE_B ORTHOMODE;
  BITCODE_B REGENMODE;
  BITCODE_B FILLMODE;
  BITCODE_B QTEXTMODE;
  BITCODE_B PSLTSCALE;
  BITCODE_B LIMCHECK;
  BITCODE_B BLIPMODE;
  BITCODE_B unknown_11;
  BITCODE_B USRTIMER;
  BITCODE_B SKPOLY;
  BITCODE_B ANGDIR;
  BITCODE_B SPLFRAME;
  BITCODE_B ATTREQ;
  BITCODE_B ATTDIA;
  BITCODE_B MIRRTEXT;
  BITCODE_B WORLDVIEW;
  BITCODE_B WIREFRAME; /* Undocumented */
  BITCODE_B TILEMODE;
  BITCODE_B PLIMCHECK;
  BITCODE_B VISRETAIN;
  BITCODE_B DELOBJ;
  BITCODE_B DISPSILH;
  BITCODE_B PELLIPSE;
  BITCODE_BS SAVEIMAGES; //some r13 only
  BITCODE_BS PROXYGRAPHICS;
  BITCODE_BS MEASUREMENT; /* 0 English, 1 Metric. Stored as Section 4 */
  BITCODE_BS DRAGMODE;
  BITCODE_BS TREEDEPTH;
  BITCODE_BS LUNITS;
  BITCODE_BS LUPREC;
  BITCODE_BS AUNITS;
  BITCODE_BS AUPREC;
  BITCODE_BS OSMODE;
  BITCODE_BS ATTMODE;
  BITCODE_BS COORDS;
  BITCODE_BS PDMODE;
  BITCODE_BS PICKSTYLE;
  BITCODE_BL unknown_12;
  BITCODE_BL unknown_13;
  BITCODE_BL unknown_14;
  BITCODE_BS USERI1;
  BITCODE_BS USERI2;
  BITCODE_BS USERI3;
  BITCODE_BS USERI4;
  BITCODE_BS USERI5;
  BITCODE_BS SPLINESEGS;
  BITCODE_BS SURFU;
  BITCODE_BS SURFV;
  BITCODE_BS SURFTYPE;
  BITCODE_BS SURFTAB1;
  BITCODE_BS SURFTAB2;
  BITCODE_BS SPLINETYPE;
  BITCODE_BS SHADEDGE;
  BITCODE_BS SHADEDIF;
  BITCODE_BS UNITMODE;
  BITCODE_BS MAXACTVP;
  BITCODE_BS ISOLINES;
  BITCODE_BS CMLJUST;
  BITCODE_BS TEXTQLTY;
  BITCODE_BL unknown_14b;
  BITCODE_BD LTSCALE;
  BITCODE_BD TEXTSIZE;
  BITCODE_BD TRACEWID;
  BITCODE_BD SKETCHINC;
  BITCODE_BD FILLETRAD;
  BITCODE_BD THICKNESS;
  BITCODE_BD ANGBASE;
  BITCODE_BD PDSIZE;
  BITCODE_BD PLINEWID;
  BITCODE_BD USERR1;
  BITCODE_BD USERR2;
  BITCODE_BD USERR3;
  BITCODE_BD USERR4;
  BITCODE_BD USERR5;
  BITCODE_BD CHAMFERA;
  BITCODE_BD CHAMFERB;
  BITCODE_BD CHAMFERC;
  BITCODE_BD CHAMFERD;
  BITCODE_BD FACETRES;
  BITCODE_BD CMLSCALE;
  BITCODE_BD CELTSCALE;
  BITCODE_TV MENU;
  BITCODE_TIMEBLL TDCREATE;
  BITCODE_TIMEBLL TDUPDATE;
  BITCODE_TIMEBLL TDUCREATE;
  BITCODE_TIMEBLL TDUUPDATE;
  BITCODE_BL unknown_15;
  BITCODE_BL unknown_16;
  BITCODE_BL unknown_17;
  BITCODE_TIMEBLL TDINDWG;
  BITCODE_TIMEBLL TDUSRTIMER;
  BITCODE_CMC CECOLOR;
  //BITCODE_RS CECOLOR_idx; /* <r13 */
  BITCODE_BS HANDLING; /* <r14: default 1 */
  //BITCODE_RS HANDSEED_R11;
  BITCODE_H HANDSEED;
  BITCODE_H CLAYER;
  BITCODE_H TEXTSTYLE;
  BITCODE_H CELTYPE;
  BITCODE_H CMATERIAL;
  BITCODE_H DIMSTYLE;
  BITCODE_H CMLSTYLE;
  BITCODE_BD PSVPSCALE;
  BITCODE_3BD PINSBASE;
  BITCODE_3BD PEXTMIN;
  BITCODE_3BD PEXTMAX;
  BITCODE_2RD PLIMMIN;
  BITCODE_2RD PLIMMAX;
  BITCODE_BD  PELEVATION;
  BITCODE_3BD PUCSORG;
  BITCODE_3BD PUCSXDIR;
  BITCODE_3BD PUCSYDIR;
  BITCODE_H PUCSNAME;
  BITCODE_H PUCSBASE;
  BITCODE_H PUCSORTHOREF;
  BITCODE_BS PUCSORTHOVIEW;
  BITCODE_3BD PUCSORGTOP;
  BITCODE_3BD PUCSORGBOTTOM;
  BITCODE_3BD PUCSORGLEFT;
  BITCODE_3BD PUCSORGRIGHT;
  BITCODE_3BD PUCSORGFRONT;
  BITCODE_3BD PUCSORGBACK;
  BITCODE_3BD INSBASE;
  BITCODE_3BD EXTMIN;
  BITCODE_3BD EXTMAX;
  BITCODE_2RD LIMMIN;
  BITCODE_2RD LIMMAX;
  BITCODE_2RD VIEWCTR;  /* -r11 */
  BITCODE_BD ELEVATION;
  BITCODE_RD VIEWSIZE;  /* -r11 */
  BITCODE_RS SNAPMODE;  /* -r11 */
  BITCODE_2RD SNAPUNIT; /* -r11 */
  BITCODE_2RD SNAPBASE; /* -r11 */
  BITCODE_RD SNAPANG;   /* -r11 */
  BITCODE_RS SNAPSTYL;  /* -r11 */
  BITCODE_RS SNAPISOPAIR; /* -r11 */
  BITCODE_RS GRIDMODE;  /* -r11 */
  BITCODE_2RD GRIDUNIT; /* -r11 */
  BITCODE_3BD UCSORG;
  BITCODE_3BD UCSXDIR;
  BITCODE_3BD UCSYDIR;
  BITCODE_H UCSNAME;
  BITCODE_H UCSBASE;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_H UCSORTHOREF;
  BITCODE_3BD UCSORGTOP;
  BITCODE_3BD UCSORGBOTTOM;
  BITCODE_3BD UCSORGLEFT;
  BITCODE_3BD UCSORGRIGHT;
  BITCODE_3BD UCSORGFRONT;
  BITCODE_3BD UCSORGBACK;
  BITCODE_TV DIMPOST;
  BITCODE_TV DIMAPOST;
  BITCODE_B DIMTOL;
  BITCODE_B DIMLIM;
  BITCODE_B DIMTIH;
  BITCODE_B DIMTOH;
  BITCODE_B DIMSE1;
  BITCODE_B DIMSE2;
  BITCODE_B DIMALT;
  BITCODE_B DIMTOFL;
  BITCODE_B DIMSAH;
  BITCODE_B DIMTIX;
  BITCODE_B DIMSOXD;
  BITCODE_BS DIMALTD;   /*!< r13-r14 only RC */
  BITCODE_BS DIMZIN;    /*!< r13-r14 only RC */
  BITCODE_B DIMSD1;
  BITCODE_B DIMSD2;
  BITCODE_BS DIMTOLJ;   /*!< r13-r14 only RC */
  BITCODE_BS DIMJUST;   /*!< r13-r14 only RC */
  BITCODE_BS DIMFIT;    /*!< r13-r14 only RC */
  BITCODE_B DIMUPT;
  BITCODE_BS DIMTZIN;   /*!< r13-r14 only RC */
  BITCODE_BS DIMMALTZ;  /*!< r13-r14 only RC */
  BITCODE_BS DIMMALTTZ; /*!< r13-r14 only RC */
  BITCODE_BS DIMTAD;    /*!< r13-r14 only RC */
  BITCODE_BS DIMUNIT;
  BITCODE_BS DIMAUNIT;
  BITCODE_BS DIMDEC;
  BITCODE_BS DIMTDEC;
  BITCODE_BS DIMALTU;
  BITCODE_BS DIMALTTD;
  BITCODE_H DIMTXSTY;
  BITCODE_BD DIMSCALE;
  BITCODE_BD DIMASZ;
  BITCODE_BD DIMEXO;
  BITCODE_BD DIMDLI;
  BITCODE_BD DIMEXE;
  BITCODE_BD DIMRND;
  BITCODE_BD DIMDLE;
  BITCODE_BD DIMTP;
  BITCODE_BD DIMTM;
  BITCODE_BD DIMFXL;
  BITCODE_BD DIMJOGANG;
  BITCODE_BS DIMTFILL;
  BITCODE_CMC DIMTFILLCLR;
  BITCODE_BS DIMAZIN;
  BITCODE_BS DIMARCSYM;
  BITCODE_BD DIMTXT;
  BITCODE_BD DIMCEN;
  BITCODE_BD DIMTSZ;
  BITCODE_BD DIMALTF;
  BITCODE_BD DIMLFAC;
  BITCODE_BD DIMTVP;
  BITCODE_BD DIMTFAC;
  BITCODE_BD DIMGAP;
  BITCODE_T DIMPOST_T; /* preR13 => handle */
  BITCODE_T DIMAPOST_T;
  BITCODE_T DIMBLK_T;
  BITCODE_T DIMBLK1_T;
  BITCODE_T DIMBLK2_T;
  BITCODE_BD DIMALTRND;
  BITCODE_RS DIMCLRD_C; /* preR13 => CMC */
  BITCODE_RS DIMCLRE_C;
  BITCODE_RS DIMCLRT_C;
  BITCODE_CMC DIMCLRD;
  BITCODE_CMC DIMCLRE;
  BITCODE_CMC DIMCLRT;
  BITCODE_BS DIMADEC;   /*!< r2000+ ... */
  BITCODE_BS DIMFRAC;
  BITCODE_BS DIMLUNIT;
  BITCODE_BS DIMDSEP;
  BITCODE_BS DIMTMOVE;
  BITCODE_BS DIMALTZ;
  BITCODE_BS DIMALTTZ;
  BITCODE_BS DIMATFIT;
  BITCODE_B  DIMFXLON;  /*!< r2007+ */
  BITCODE_B  DIMTXTDIRECTION; /*!< r2010+ */
  BITCODE_BD DIMALTMZF; /*!< r2010+ */
  BITCODE_T  DIMALTMZS; /*!< r2010+ */
  BITCODE_BD DIMMZF;    /*!< r2010+ */
  BITCODE_T  DIMMZS;    /*!< r2010+ */
  /*BITCODE_H DIMTXSTY;*/  /*!< r2000+ */
  BITCODE_H DIMLDRBLK;  /*!< r2000+ */
  BITCODE_H DIMBLK;     /*!< r2000+ */
  BITCODE_H DIMBLK1;    /*!< r2000+ */
  BITCODE_H DIMBLK2;    /*!< r2000+ */
  BITCODE_H DIMLTYPE; /*!< r2007+ */
  BITCODE_H DIMLTEX1; /*!< r2007+ */
  BITCODE_H DIMLTEX2; /*!< r2007+ */
  BITCODE_BSd DIMLWD;  /*!< r2000+ */
  BITCODE_BSd DIMLWE;  /*!< r2000+ */
  BITCODE_H BLOCK_CONTROL_OBJECT;
  BITCODE_H LAYER_CONTROL_OBJECT;
  BITCODE_H STYLE_CONTROL_OBJECT;
  BITCODE_H LTYPE_CONTROL_OBJECT;
  BITCODE_H VIEW_CONTROL_OBJECT;
  BITCODE_H UCS_CONTROL_OBJECT;
  BITCODE_H VPORT_CONTROL_OBJECT;
  BITCODE_H APPID_CONTROL_OBJECT;
  BITCODE_H DIMSTYLE_CONTROL_OBJECT;
  BITCODE_H VPORT_ENTITY_CONTROL_OBJECT; /*!< r11-r2000 */
  BITCODE_H DICTIONARY_ACAD_GROUP;
  BITCODE_H DICTIONARY_ACAD_MLINESTYLE;
  BITCODE_H DICTIONARY_NAMED_OBJECT;
  BITCODE_BS TSTACKALIGN;           /*!< r2000+ */
  BITCODE_BS TSTACKSIZE;            /*!< r2000+ */
  BITCODE_TV HYPERLINKBASE;         /*!< r2000+ */
  BITCODE_TV STYLESHEET;            /*!< r2000+ */
  BITCODE_H DICTIONARY_LAYOUT;      /*!< r2000+ */
  BITCODE_H DICTIONARY_PLOTSETTINGS;   /*!< r2000+ */
  BITCODE_H DICTIONARY_PLOTSTYLENAME;  /*!< r2000+ */
  BITCODE_H DICTIONARY_MATERIAL;    /*!< r2004+ */
  BITCODE_H DICTIONARY_COLOR;       /*!< r2004+ */
  BITCODE_H DICTIONARY_VISUALSTYLE; /*!< r2007+ */
  BITCODE_H DICTIONARY_LIGHTLIST;   /*!< r2010+ ?? */
  BITCODE_H unknown_20;             /*!< r2013+ */
  BITCODE_BL FLAGS;
  BITCODE_BSd CELWEIGHT; /* = FLAGS & 0x1f, see dxf_cvt_lweight() DXF 370 (int16) */
  BITCODE_B  ENDCAPS;   /* = FLAGS & 0x60 */
  BITCODE_B  JOINSTYLE; /* = FLAGS & 0x180 */
  BITCODE_B  LWDISPLAY; /* = !(FLAGS & 0x200) */
  BITCODE_B  XEDIT;     /* = !(FLAGS & 0x400) */
  BITCODE_B  EXTNAMES;  /* = FLAGS & 0x800 */
  BITCODE_B  PSTYLEMODE; /* = FLAGS & 0x2000 */
  BITCODE_B  OLESTARTUP; /* = FLAGS & 0x4000 */
  BITCODE_BS INSUNITS;
  BITCODE_BS CEPSNTYPE;
  BITCODE_H CPSNID;
  BITCODE_TV FINGERPRINTGUID;
  BITCODE_TV VERSIONGUID;
  BITCODE_RC SORTENTS;
  BITCODE_RC INDEXCTL;
  BITCODE_RC HIDETEXT;
  BITCODE_RC XCLIPFRAME;
  BITCODE_RC DIMASSOC;
  BITCODE_RC HALOGAP;
  BITCODE_BS OBSCOLOR;
  BITCODE_BS INTERSECTIONCOLOR;
  BITCODE_RC OBSLTYPE;
  BITCODE_RC INTERSECTIONDISPLAY;
  BITCODE_TV PROJECTNAME;
  BITCODE_H BLOCK_RECORD_PSPACE;
  BITCODE_H BLOCK_RECORD_MSPACE;
  BITCODE_H LTYPE_BYLAYER;
  BITCODE_H LTYPE_BYBLOCK;
  BITCODE_H LTYPE_CONTINUOUS;
  BITCODE_B CAMERADISPLAY; /*!< r2007+ ... */
  BITCODE_BL unknown_21;
  BITCODE_BL unknown_22;
  BITCODE_BD unknown_23;
  BITCODE_BD STEPSPERSEC;
  BITCODE_BD STEPSIZE;
  BITCODE_BD _3DDWFPREC;
  BITCODE_BD LENSLENGTH;
  BITCODE_BD CAMERAHEIGHT;
  BITCODE_RC SOLIDHIST;
  BITCODE_RC SHOWHIST;
  BITCODE_BD PSOLWIDTH;
  BITCODE_BD PSOLHEIGHT;
  BITCODE_BD LOFTANG1;
  BITCODE_BD LOFTANG2;
  BITCODE_BD LOFTMAG1;
  BITCODE_BD LOFTMAG2;
  BITCODE_BS LOFTPARAM;
  BITCODE_RC LOFTNORMALS;
  BITCODE_BD LATITUDE;
  BITCODE_BD LONGITUDE;
  BITCODE_BD NORTHDIRECTION;
  BITCODE_BL TIMEZONE;
  BITCODE_RC LIGHTGLYPHDISPLAY;
  BITCODE_RC TILEMODELIGHTSYNCH;
  BITCODE_RC DWFFRAME;
  BITCODE_RC DGNFRAME;
  BITCODE_B REALWORLDSCALE;
  BITCODE_CMC INTERFERECOLOR;
  BITCODE_H INTERFEREOBJVS;
  BITCODE_H INTERFEREVPVS;
  BITCODE_H DRAGVS;
  BITCODE_RC CSHADOW;
  BITCODE_BD SHADOWPLANELOCATION;
  BITCODE_BS unknown_54; /*!< r14+ ... optional */
  BITCODE_BS unknown_55;
  BITCODE_BS unknown_56;
  BITCODE_BS unknown_57;
} Dwg_Header_Variables;

/* OBJECTS *******************************************************************/
/**
 UNUSED (0) entity. Unknown entities are stored as blob
 */
typedef int Dwg_Entity_UNUSED;

/** \ref Dwg_Entity_TEXT
 TEXT (1) entity
 */
typedef struct _dwg_entity_TEXT
{
  struct _dwg_object_entity *parent;

  BITCODE_RC dataflags;        /*!< r2000+ */
  BITCODE_RD elevation;        /*!< DXF 30 (z coord of 10), when dataflags & 1 */
  BITCODE_2DPOINT insertion_pt; /*!< DXF 10 */
  BITCODE_2DPOINT alignment_pt; /*!< DXF 11. optional, when dataflags & 2, i.e 72/73 != 0 */
  BITCODE_BE extrusion;       /*!< DXF 210. Default 0,0,1 */
  BITCODE_RD thickness;       /*!< DXF 39 */
  BITCODE_RD oblique_angle;   /*!< DXF 51 */
  BITCODE_RD rotation;        /*!< DXF 50 */
  BITCODE_RD height;          /*!< DXF 40 */
  BITCODE_RD width_factor;    /*!< DXF 41 */
  BITCODE_TV text_value;      /*!< DXF 1 */
  BITCODE_BS generation;      /*!< DXF 71 */
  BITCODE_BS horiz_alignment; /*!< DXF 72. options 0-5:
                                 0 = Left; 1= Center; 2 = Right; 3 = Aligned;
                                 4 = Middle; 5 = Fit */
  BITCODE_BS vert_alignment;  /*!< DXF 73. options 0-3:
                                 0 = Baseline; 1 = Bottom; 2 = Middle; 3 = Top */
  BITCODE_H style;
} Dwg_Entity_TEXT;

/** \ref Dwg_Entity_ATTRIB
 ATTRIB (2) entity
 */
typedef struct _dwg_entity_ATTRIB
{
  struct _dwg_object_entity *parent;

  BITCODE_BD elevation;
  BITCODE_2DPOINT insertion_pt;
  BITCODE_2DPOINT alignment_pt;
  BITCODE_BE extrusion;
  BITCODE_RD thickness;
  BITCODE_RD oblique_angle;
  BITCODE_RD rotation;
  BITCODE_RD height;
  BITCODE_RD width_factor;
  BITCODE_TV text_value;
  BITCODE_BS generation;
  BITCODE_BS horiz_alignment;
  BITCODE_BS vert_alignment;
  BITCODE_RC dataflags;
  BITCODE_RC class_version; /* R2010+ */
  BITCODE_RC type;    /* R2018+ */
  BITCODE_T tag;
  BITCODE_BS field_length; /* DXF 73 but unused */
  BITCODE_RC flags;
  BITCODE_B lock_position_flag;
  BITCODE_H style;
  BITCODE_H mtext_handles; /* R2018+ TODO */
  BITCODE_BS annotative_data_size; /* R2018+ */
  BITCODE_RC annotative_data_bytes;
  BITCODE_H  annotative_app;
  BITCODE_BS annotative_short;
} Dwg_Entity_ATTRIB;

/** \ref Dwg_Entity_ATTDEF
 ATTDEF (3) entity
 */
typedef struct _dwg_entity_ATTDEF
{
  struct _dwg_object_entity *parent;

  BITCODE_BD elevation;
  BITCODE_2DPOINT insertion_pt;
  BITCODE_2DPOINT alignment_pt;
  BITCODE_BE extrusion;
  BITCODE_RD thickness;
  BITCODE_RD oblique_angle;
  BITCODE_RD rotation;
  BITCODE_RD height;
  BITCODE_RD width_factor;
  BITCODE_TV default_value;
  BITCODE_BS generation;
  BITCODE_BS horiz_alignment;
  BITCODE_BS vert_alignment;
  BITCODE_RC dataflags;
  BITCODE_RC class_version; /* R2010+ */
  BITCODE_RC type;    /* R2018+ */
  BITCODE_T tag;
  BITCODE_BS field_length;
  BITCODE_RC flags;
  BITCODE_B lock_position_flag;
  BITCODE_H style;
  BITCODE_H mtext_handles; /* R2018+ TODO */
  BITCODE_BS annotative_data_size; /* R2018+ */
  BITCODE_RC annotative_data_bytes;
  BITCODE_H  annotative_app;
  BITCODE_BS annotative_short;

  BITCODE_RC attdef_class_version; /* R2010+ */
  BITCODE_T prompt;
} Dwg_Entity_ATTDEF;

/**
 BLOCK (4) entity
 */
typedef struct _dwg_entity_BLOCK
{
  struct _dwg_object_entity *parent;

  BITCODE_T name;
} Dwg_Entity_BLOCK;

/**
 ENDBLK (5) entity
 */
typedef struct _dwg_entity_ENDBLK
{
  struct _dwg_object_entity *parent;
} Dwg_Entity_ENDBLK;

/**
 SEQEND (6) entity
 */
typedef struct _dwg_entity_SEQEND
{
  struct _dwg_object_entity *parent;
} Dwg_Entity_SEQEND;

/**
 INSERT (7) entity
 */
typedef struct _dwg_entity_INSERT
{
  struct _dwg_object_entity *parent;

  BITCODE_3DPOINT   ins_pt;
  BITCODE_BB        scale_flag;
  BITCODE_3DPOINT   scale;
  BITCODE_BD        rotation;
  BITCODE_BE        extrusion;
  BITCODE_B         has_attribs;
  BITCODE_BL        num_owned;

  BITCODE_H   block_header;
  BITCODE_H   first_attrib;
  BITCODE_H   last_attrib;
  BITCODE_H*  attrib_handles;
  BITCODE_H   seqend;
} Dwg_Entity_INSERT;

/**
 MINSERT (8) entity
 */
typedef struct _dwg_entity_MINSERT
{
  struct _dwg_object_entity *parent;

  BITCODE_3DPOINT   ins_pt;
  BITCODE_BB        scale_flag;
  BITCODE_3DPOINT   scale;
  BITCODE_BD        rotation;
  BITCODE_BE        extrusion;
  BITCODE_B         has_attribs;
  BITCODE_BL        num_owned;

  BITCODE_BS        num_cols;
  BITCODE_BS        num_rows;
  BITCODE_BD        col_spacing;
  BITCODE_BD        row_spacing;

  BITCODE_H   block_header;
  BITCODE_H   first_attrib;
  BITCODE_H   last_attrib;
  BITCODE_H*  attrib_handles;
  BITCODE_H   seqend;
} Dwg_Entity_MINSERT;

/**
 VERTEX_2D (10) entity
 */
typedef struct _dwg_entity_VERTEX_2D
{
  struct _dwg_object_entity *parent;

  BITCODE_RC flag;
  BITCODE_3BD point;
  BITCODE_BD start_width;
  BITCODE_BD end_width;
  BITCODE_BL id; /* R2010+ */
  BITCODE_BD bulge;
  BITCODE_BD tangent_dir;
} Dwg_Entity_VERTEX_2D;

/**
 VERTEX_3D (11) entity
 */
typedef struct _dwg_entity_VERTEX_3D
{
  struct _dwg_object_entity *parent;

  BITCODE_RC flag;
  BITCODE_3BD point;
} Dwg_Entity_VERTEX_3D;

/**
 VERTEX_MESH (12) - same as VERTEX_3D entity
 */
typedef Dwg_Entity_VERTEX_3D Dwg_Entity_VERTEX_MESH;

/**
 VERTEX_PFACE (13) - same as VERTEX_3D entity
 */
typedef Dwg_Entity_VERTEX_3D Dwg_Entity_VERTEX_PFACE;

/**
 VERTEX_PFACE_FACE (14) entity
 */
typedef struct _dwg_entity_VERTEX_PFACE_FACE
{
  struct _dwg_object_entity *parent;

  BITCODE_RC flag;
  BITCODE_BS vertind[4];
} Dwg_Entity_VERTEX_PFACE_FACE;

#define COMMON_ENTITY_POLYLINE \
  struct _dwg_object_entity *parent; \
  BITCODE_B has_vertex; \
  BITCODE_BL num_owned; \
  BITCODE_H first_vertex; \
  BITCODE_H last_vertex; \
  BITCODE_H* vertex; \
  BITCODE_H seqend

/**
 2D POLYLINE (15) entity
 */
typedef struct _dwg_entity_POLYLINE_2D
{
  COMMON_ENTITY_POLYLINE;

  BITCODE_BS flag;        /* 1: closed, 2: curve_fit, 4: spline_fit, 8: 3d, 0x10: 3dmesh,
                             0x20: mesh_closed_in_n, 0x40: polyface_mesh, 0x80: ltype_continuous */
  BITCODE_BS curve_type;
  BITCODE_BD start_width;
  BITCODE_BD end_width;
  BITCODE_BT thickness;
  BITCODE_BD elevation;
  BITCODE_BE extrusion;
} Dwg_Entity_POLYLINE_2D;

/**
 3D POLYLINE (16) entity
 */
typedef struct _dwg_entity_POLYLINE_3D
{
  COMMON_ENTITY_POLYLINE;

  BITCODE_RC curve_type;
  BITCODE_RC flag;
} Dwg_Entity_POLYLINE_3D;

/**
 ARC (17) entity
 */
typedef struct _dwg_entity_ARC
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD center;
  BITCODE_BD radius;
  BITCODE_BT thickness;
  BITCODE_BE extrusion;
  BITCODE_BD start_angle;
  BITCODE_BD end_angle;
} Dwg_Entity_ARC;

/**
 CIRCLE (18) entity
 */
typedef struct _dwg_entity_CIRCLE
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD center;
  BITCODE_BD radius;
  BITCODE_BT thickness;
  BITCODE_BE extrusion;
} Dwg_Entity_CIRCLE;

/**
 LINE (19) entity
 */
typedef struct _dwg_entity_LINE
{
  struct _dwg_object_entity *parent;

  BITCODE_RC z_is_zero;
  BITCODE_3BD start;
  BITCODE_3BD end;
  BITCODE_BT thickness;
  BITCODE_BE extrusion;
} Dwg_Entity_LINE;

/**
 * Macro for common DIMENSION declaration
 *
 * flag 70: value & 31: 0-6 denote the type, + bitmask 32-128.
 * 0: linear, 1: aligned, 2: ang2ln, 3: diameter, 4: radius
 * 5: ang3pt, 6: ordinate.
 * 32: block (2) used by this dimension only.
 * 64: if set, ordinate is type X, else ordinate is type Y.
 * 128: non-default dimension text location
 */
#define DIMENSION_COMMON \
    struct _dwg_object_entity *parent; \
    BITCODE_RC class_version; /* R2010+ */ \
    BITCODE_T blockname; \
    BITCODE_BE extrusion; \
    BITCODE_3BD def_pt; \
    BITCODE_2RD text_midpt; \
    BITCODE_BD elevation; \
    BITCODE_RC flag; /* calculated, DXF only 70 */ \
    BITCODE_RC flag1; /* as in the DWG */ \
    BITCODE_T user_text; \
    BITCODE_BD text_rotation; \
    BITCODE_BD horiz_dir; \
    BITCODE_3BD ins_scale; \
    BITCODE_BD ins_rotation; \
    BITCODE_BS attachment; \
    BITCODE_BS lspace_style; \
    BITCODE_BD lspace_factor; \
    BITCODE_BD act_measurement; \
    BITCODE_B unknown; \
    BITCODE_B flip_arrow1; \
    BITCODE_B flip_arrow2; \
    BITCODE_2RD clone_ins_pt; \
    BITCODE_H dimstyle; \
    BITCODE_H block

typedef struct _dwg_DIMENSION_common
{
  DIMENSION_COMMON;
} Dwg_DIMENSION_common;

/**
 ordinate dimension - DIMENSION_ORDINATE (20) entity
 */
typedef struct _dwg_entity_DIMENSION_ORDINATE
{
  DIMENSION_COMMON;
  BITCODE_3BD feature_location_pt;
  BITCODE_3BD leader_endpt;
  BITCODE_RC flag2;
} Dwg_Entity_DIMENSION_ORDINATE;

/**
 linear dimension - DIMENSION_LINEAR (21) entity
 */
typedef struct _dwg_entity_DIMENSION_LINEAR
{
  DIMENSION_COMMON;
  BITCODE_3BD xline1_pt;
  BITCODE_3BD xline2_pt;
  BITCODE_BD oblique_angle;
  BITCODE_BD dim_rotation;
} Dwg_Entity_DIMENSION_LINEAR;

/**
 aligned dimension - DIMENSION_ALIGNED (22) entity
 */
typedef struct _dwg_entity_DIMENSION_ALIGNED
{
  DIMENSION_COMMON;
  BITCODE_3BD xline1_pt;
  BITCODE_3BD xline2_pt;
  BITCODE_BD oblique_angle;
} Dwg_Entity_DIMENSION_ALIGNED;

/**
 angular 3pt dimension - DIMENSION_ANG3PT (23) entity
 */
typedef struct _dwg_entity_DIMENSION_ANG3PT
{
  DIMENSION_COMMON;
  BITCODE_3BD xline1_pt;
  BITCODE_3BD xline2_pt;
  BITCODE_3BD center_pt;
} Dwg_Entity_DIMENSION_ANG3PT;

/**
 angular 2 line dimension - DIMENSION_ANG2LN (24) entity
 */
typedef struct _dwg_entity_DIMENSION_ANG2LN
{
  DIMENSION_COMMON;
  BITCODE_3BD xline1start_pt;
  BITCODE_3BD xline1end_pt;
  BITCODE_3BD xline2start_pt;
  BITCODE_3BD xline2end_pt;
} Dwg_Entity_DIMENSION_ANG2LN;

/**
 radius dimension - DIMENSION_RADIUS (25) entity
 */
typedef struct _dwg_entity_DIMENSION_RADIUS
{
  DIMENSION_COMMON;
  BITCODE_3BD first_arc_pt; /*!< DXF 15 */
  BITCODE_BD leader_len;    /*!< DXF 40 */
} Dwg_Entity_DIMENSION_RADIUS;

/**
 diameter dimension - DIMENSION_DIAMETER (26) entity
 */
typedef struct _dwg_entity_DIMENSION_DIAMETER
{
  DIMENSION_COMMON;
  BITCODE_3BD first_arc_pt; /*!< DXF 15 */
  BITCODE_BD leader_len;    /*!< DXF 40 */
} Dwg_Entity_DIMENSION_DIAMETER;

/**
 arc dimension - ARC_DIMENSION (varies) entity
 */
typedef struct _dwg_entity_ARC_DIMENSION
{
  DIMENSION_COMMON;
  BITCODE_3BD xline1_pt;	/* DXF 13 */
  BITCODE_3BD xline2_pt;	/* DXF 14 */
  BITCODE_3BD center_pt;	/* DXF 15 */
  BITCODE_B is_partial;		/* DXF 70 */
  BITCODE_BD arc_start_param;	/* DXF 41 */
  BITCODE_BD arc_end_param;	/* DXF 42 */
  BITCODE_B has_leader;		/* DXF 71 */
  BITCODE_3BD leader1_pt;	/* DXF 16 */
  BITCODE_3BD leader2_pt;	/* DXF 17 */
} Dwg_Entity_ARC_DIMENSION;

/**
 Struct for:  POINT (27)
 */
typedef struct _dwg_entity_POINT
{
  struct _dwg_object_entity *parent;

  BITCODE_BD x;
  BITCODE_BD y;
  BITCODE_BD z;
  BITCODE_BT thickness;
  BITCODE_BE extrusion;
  BITCODE_BD x_ang;
} Dwg_Entity_POINT;

/**
 Struct for:  3D FACE (28)
 */
typedef struct _dwg_entity_3DFACE
{
  struct _dwg_object_entity *parent;

  BITCODE_B has_no_flags;
  BITCODE_B z_is_zero;
  BITCODE_3BD corner1;
  BITCODE_3BD corner2;
  BITCODE_3BD corner3;
  BITCODE_3BD corner4;
  BITCODE_BS invis_flags;
} Dwg_Entity__3DFACE;

/**
 Struct for:  POLYLINE (PFACE) (29)
 */
typedef struct _dwg_entity_POLYLINE_PFACE
{
  COMMON_ENTITY_POLYLINE;

  BITCODE_BS numverts;
  BITCODE_BS numfaces;
} Dwg_Entity_POLYLINE_PFACE;

/**
 Struct for:  POLYLINE (MESH) (30)
 */
typedef struct _dwg_entity_POLYLINE_MESH
{
  COMMON_ENTITY_POLYLINE;

  BITCODE_BS flag;
  BITCODE_BS curve_type;
  BITCODE_BS num_m_verts;
  BITCODE_BS num_n_verts;
  BITCODE_BS m_density;
  BITCODE_BS n_density;
} Dwg_Entity_POLYLINE_MESH;

/**
 Struct for:  SOLID (31)
 */

typedef struct _dwg_entity_SOLID
{
  struct _dwg_object_entity *parent;

  BITCODE_BT thickness;
  BITCODE_BD elevation;
  BITCODE_2RD corner1;
  BITCODE_2RD corner2;
  BITCODE_2RD corner3;
  BITCODE_2RD corner4;
  BITCODE_BE extrusion;
} Dwg_Entity_SOLID;

/**
 Struct for:  TRACE (32)
 */

typedef struct _dwg_entity_TRACE
{
  struct _dwg_object_entity *parent;

  BITCODE_BT thickness;
  BITCODE_BD elevation;
  BITCODE_2RD corner1;
  BITCODE_2RD corner2;
  BITCODE_2RD corner3;
  BITCODE_2RD corner4;
  BITCODE_BE extrusion;
} Dwg_Entity_TRACE;

/**
 Struct for:  SHAPE (33)
 */

typedef struct _dwg_entity_SHAPE
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD ins_pt;
  BITCODE_BD scale;
  BITCODE_BD rotation;
  BITCODE_BD width_factor;
  BITCODE_BD oblique_angle;
  BITCODE_BD thickness;
  BITCODE_BS style_id;
  BITCODE_BE extrusion;
  BITCODE_H style;
} Dwg_Entity_SHAPE;

/**
 Struct for:  VIEWPORT ENTITY (34)
 */

typedef struct _dwg_entity_VIEWPORT
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD center;
  BITCODE_BD width;
  BITCODE_BD height;
  BITCODE_RS on_off; /* DXF 68, -1 should be accepted also */
  BITCODE_RS id;     /* DXF 69 */

  BITCODE_3BD view_target;
  BITCODE_3BD VIEWDIR;
  BITCODE_BD twist_angle;
  BITCODE_BD VIEWSIZE; // the height
  BITCODE_BD lens_length;
  BITCODE_BD front_clip_z;
  BITCODE_BD back_clip_z;
  BITCODE_BD SNAPANG;
  BITCODE_2RD VIEWCTR;
  BITCODE_2RD SNAPBASE;
  BITCODE_2RD SNAPUNIT;
  BITCODE_2RD GRIDUNIT;
  BITCODE_BS circle_zoom;
  BITCODE_BS grid_major;
  BITCODE_BL num_frozen_layers;
  BITCODE_BL status_flag;
  BITCODE_TV style_sheet;
  BITCODE_RC render_mode;
  BITCODE_B ucs_at_origin;
  BITCODE_B UCSVP;
  BITCODE_3BD ucsorg;
  BITCODE_3BD ucsxdir;
  BITCODE_3BD ucsydir;
  BITCODE_BD ucs_elevation;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_BS shadeplot_mode;
  BITCODE_B use_default_lights;
  BITCODE_RC default_lighting_type;
  BITCODE_BD brightness;
  BITCODE_BD contrast;
  BITCODE_CMC ambient_color;
  BITCODE_H vport_entity_header;
  BITCODE_H *frozen_layers;
  BITCODE_H clip_boundary;
  BITCODE_H named_ucs;
  BITCODE_H base_ucs;
  BITCODE_H background;
  BITCODE_H visualstyle;
  BITCODE_H shadeplot;
  BITCODE_H sun;
} Dwg_Entity_VIEWPORT;

/**
 ELLIPSE (35) entity
 */
typedef struct _dwg_entity_ELLIPSE
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD center;
  BITCODE_3BD sm_axis;
  BITCODE_BE extrusion;
  BITCODE_BD axis_ratio;
  BITCODE_BD start_angle;
  BITCODE_BD end_angle;
} Dwg_Entity_ELLIPSE;

/**
 spline - SPLINE (36) entity
 */
typedef struct _dwg_SPLINE_control_point
{
  struct _dwg_entity_SPLINE *parent;

  double x;
  double y;
  double z;
  double w;
} Dwg_SPLINE_control_point;

typedef struct _dwg_entity_SPLINE
{
  struct _dwg_object_entity *parent;

  BITCODE_RS flag; /* computed */
  BITCODE_BS scenario; /* 1 spline, 2 bezier */
  BITCODE_BS degree;
  BITCODE_BL splineflags1; /* 2013+: method fit points = 1, CV frame show = 2, closed = 4 */
  BITCODE_BL knotparam;    /* 2013+: Chord = 0, Square root = 1, Uniform = 2, Custom = 15 */
  BITCODE_BD fit_tol;
  BITCODE_3BD beg_tan_vec;
  BITCODE_3BD end_tan_vec;
  BITCODE_B closed_b; /* bit 0 of 70 */
  BITCODE_B periodic; /* bit 1 of 70 */
  BITCODE_B rational; /* bit 2 of 70 */
  BITCODE_B weighted; /* bit 4 of 70 */
  BITCODE_BD knot_tol;
  BITCODE_BD ctrl_tol;
  BITCODE_BS num_fit_pts;
  BITCODE_3DPOINT* fit_pts;
  BITCODE_BL num_knots;
  BITCODE_BD* knots;
  BITCODE_BL num_ctrl_pts;
  Dwg_SPLINE_control_point* ctrl_pts;
} Dwg_Entity_SPLINE;

/**
 3DSOLID (38) entity
 */
#define Dwg_Entity_3DSOLID Dwg_Entity__3DSOLID
typedef struct _dwg_3DSOLID_wire
{
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_RC type;
  BITCODE_BL selection_marker;
  BITCODE_BL color;
  BITCODE_BL acis_index;
  BITCODE_BL num_points;
  BITCODE_3BD* points;
  BITCODE_B transform_present;
  BITCODE_3BD axis_x;
  BITCODE_3BD axis_y;
  BITCODE_3BD axis_z;
  BITCODE_3BD translation;
  BITCODE_3BD scale;
  BITCODE_B has_rotation;
  BITCODE_B has_reflection;
  BITCODE_B has_shear;
} Dwg_3DSOLID_wire;

typedef struct _dwg_3DSOLID_silhouette
{
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_BL vp_id;
  BITCODE_3BD vp_target;
  BITCODE_3BD vp_dir_from_target;
  BITCODE_3BD vp_up_dir;
  BITCODE_B vp_perspective;
  BITCODE_B has_wires;
  BITCODE_BL num_wires;
  Dwg_3DSOLID_wire * wires;
} Dwg_3DSOLID_silhouette;

typedef struct _dwg_3DSOLID_material
{
  struct _dwg_entity_3DSOLID *parent;
  BITCODE_BL array_index;
  BITCODE_BL mat_absref;
  BITCODE_H  material_handle; /* code 5 */
} Dwg_3DSOLID_material;

#define _3DSOLID_FIELDS \
  BITCODE_B acis_empty; \
  BITCODE_B unknown; \
  BITCODE_BS version; \
  BITCODE_BL num_blocks; \
  BITCODE_BL* block_size; \
  char** encr_sat_data; \
  BITCODE_BL sab_size; \
  BITCODE_RC* acis_data; /* The decrypted SAT v1 or the SAB v2 stream */ \
  BITCODE_B wireframe_data_present; \
  BITCODE_B point_present; \
  BITCODE_3BD point; \
  BITCODE_BL isolines; /* i.e. wires */ \
  BITCODE_B isoline_present; /* ie. has_wires */ \
  BITCODE_BL num_wires; \
  Dwg_3DSOLID_wire * wires; \
  BITCODE_BL num_silhouettes; \
  Dwg_3DSOLID_silhouette * silhouettes; \
  BITCODE_B _dxf_sab_converted;  /* internally calculated */ \
  BITCODE_B acis_empty2; \
  struct _dwg_entity_3DSOLID* extra_acis_data; \
  BITCODE_BL num_materials; \
  Dwg_3DSOLID_material *materials; \
  BITCODE_B has_revision_guid; \
  BITCODE_RC revision_guid[38]; \
  BITCODE_BL revision_major; \
  BITCODE_BS revision_minor1; \
  BITCODE_BS revision_minor2; \
  BITCODE_RC revision_bytes[9]; \
  BITCODE_BL end_marker; \
  BITCODE_H history_id; \
  BITCODE_B acis_empty_bit

typedef struct _dwg_entity_3DSOLID
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
#if 0
  BITCODE_B acis_empty;  /*!< no DXF */
  BITCODE_B unknown;
  BITCODE_BS version;    /*!< DXF 70 Modeler format version =1*/
  BITCODE_BL num_blocks;
  BITCODE_BL* block_size;
  char** encr_sat_data;       /*!< DXF 1, the encrypted SAT data */
  BITCODE_RC*  acis_data;     /*!< decrypted SAT data */
  BITCODE_B wireframe_data_present;
  BITCODE_B point_present;
  BITCODE_3BD point;
  BITCODE_BL num_isolines;
  BITCODE_B isoline_present;
  BITCODE_BL num_wires;
  Dwg_3DSOLID_wire * wires;
  BITCODE_BL num_silhouettes;
  Dwg_3DSOLID_silhouette * silhouettes;
  BITCODE_B acis_empty2;
  struct _dwg_entity_3DSOLID* extra_acis_data;/* is it the best approach? */
  BITCODE_BL unknown_2007;
  BITCODE_H history_id;
  BITCODE_B acis_empty_bit;
#endif
} Dwg_Entity__3DSOLID;

/**
 REGION (37) entity
 */
typedef Dwg_Entity__3DSOLID Dwg_Entity_REGION;

/**
 BODY (39) entity
 */
typedef Dwg_Entity__3DSOLID Dwg_Entity_BODY;

/**
 ray - RAY (40) entity
 */
typedef struct _dwg_entity_RAY
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD point;   /*!< DXF 10 */
  BITCODE_3BD vector;  /*!< DXF 11 */
} Dwg_Entity_RAY;

/**
 XLINE (41) entity
 */
typedef Dwg_Entity_RAY Dwg_Entity_XLINE;

/**
 DICTIONARY (42)
 This structure is used for all the new tables.
 Beware: Keep same offsets as DICTIONARYWDFLT
 */
typedef struct _dwg_object_DICTIONARY
{
  struct _dwg_object_object *parent;

  BITCODE_BL numitems;    /*!< no DXF */
  BITCODE_BS cloning;     /*!< DXF 281 */
  BITCODE_RC hard_owner;  /*!< DXF 330 */
  BITCODE_T* texts;       /*!< DXF 3 */
  BITCODE_H* itemhandles; /*!< DXF 350/360, pairwise with texts */

  BITCODE_RC cloning_r14; /*!< r14 only */
} Dwg_Object_DICTIONARY;

/**
 OLEFRAME (43) entity
 (replaced by OLE2FRAME (74) later)
 */
typedef struct _dwg_entity_OLEFRAME
{
  struct _dwg_object_entity *parent;

  BITCODE_BS flag;
  BITCODE_BS mode;
  BITCODE_BL data_size;
  BITCODE_TF data;
} Dwg_Entity_OLEFRAME;

/**
 MTEXT (44) entity
 */
typedef struct _dwg_entity_MTEXT
{
  struct _dwg_object_entity *parent;

  BITCODE_3BD insertion_pt;/*!< DXF 10 */
  BITCODE_BE extrusion;   /*!< DXF 210 */
  BITCODE_3BD x_axis_dir;  /*!< DXF 1 */
  BITCODE_BD rect_height;  /*!< no DXF */
  BITCODE_BD rect_width;   /*!< DXF 41 */
  BITCODE_BD text_height;  /*!< DXF 40 */
  BITCODE_BS attachment;   /*!< DXF 71.
                             1 = Top left, 2 = Top center, 3 = Top
                             right, 4 = Middle left, 5 = Middle
                             center, 6 = Middle right, 7 = Bottom
                             left, 8 = Bottom center, 9 = Bottom
                             right */
  BITCODE_BS drawing_dir;  /*!< DXF 72.
                            1 = Left to right, 3 = Top to bottom,
                            5 = By style (the flow direction is inherited
                            from the associated text style) */
  BITCODE_BD extents_height; /*!< DXF 42 */
  BITCODE_BD extents_width;  /*!< DXF 43 */
  BITCODE_TV text;           /*!< DXF 1 */
  BITCODE_H style;           /*!< DXF 7 */
  BITCODE_BS linespace_style; /*!< DXF 73. r2000+ */
  BITCODE_BD linespace_factor;/*!< DXF 44. r2000+. Mtext line spacing factor (optional):
                               Percentage of default (3-on-5) line spacing to
                               be applied. Valid values range from 0.25 to 4.00 */
  BITCODE_B unknown_bit;
  BITCODE_BL bg_fill_flag;   /*!< DXF 90. r2004+
                               0 = Background fill off,
                               1 = Use background fill color,
                               2 = Use drawing window color as background fill color. */
  BITCODE_BL bg_fill_scale;  /*!< DXF 45. r2004+
                               margin around the text. */
  BITCODE_CMC bg_fill_color; /*!< DXF 63. r2004+. on bg_fill_flag==1 */
  BITCODE_BL bg_fill_trans;  /*!< DXF 441. r2004+. unused */
  BITCODE_B annotative;      /*!< r2018+: */
  BITCODE_BS class_version;
  BITCODE_B default_flag;
  BITCODE_H appid;
  BITCODE_BL column_type;    /*!< DXF 75 */
  BITCODE_BD column_width;   /*!< DXF 48 */
  BITCODE_BD gutter;         /*!< DXF 49 */
  BITCODE_B auto_height;     /*!< DXF 79 */
  BITCODE_B flow_reversed;   /*!< DXF 74 */
  BITCODE_BL num_column_heights;/*!< DXF 76 */
  BITCODE_BD *column_heights;/*!< DXF 50 */
} Dwg_Entity_MTEXT;

/**
 LEADER (45) entity
 */
typedef struct _dwg_entity_LEADER
{
  struct _dwg_object_entity *parent;

  BITCODE_B unknown_bit_1;  /* always seems to be zero */
  BITCODE_BS path_type;     /*< DXF(72) 0: line, 1: spline (oda bug) */
  BITCODE_BS annot_type;    /*< DXF(73) 0: text, 1: tol, 2: insert, 3 (def): none */
  BITCODE_BL num_points;    /*< DXF(76) */
  BITCODE_3DPOINT* points;
  BITCODE_3DPOINT origin;
  BITCODE_BE extrusion;
  BITCODE_3DPOINT x_direction;
  BITCODE_3DPOINT inspt_offset;
  BITCODE_3DPOINT endptproj; /* R_14-R_2007 ? */
  BITCODE_BD dimgap;         /* R_13-R_14 only */
  BITCODE_BD box_height;
  BITCODE_BD box_width;
  BITCODE_B hookline_dir;
  BITCODE_B arrowhead_on;
  BITCODE_BS arrowhead_type;
  BITCODE_BD dimasz;
  BITCODE_B unknown_bit_2;
  BITCODE_B unknown_bit_3;
  BITCODE_BS unknown_short_1;
  BITCODE_BS byblock_color;
  BITCODE_B hookline_on;
  BITCODE_B unknown_bit_5;
  BITCODE_H associated_annotation; /* DXF 340 Hard reference to associated annotation (mtext, tolerance, or insert entity) */
  BITCODE_H dimstyle;
} Dwg_Entity_LEADER;

/**
 TOLERANCE (46) entity
 */
typedef struct _dwg_entity_TOLERANCE
{
  struct _dwg_object_entity *parent;

  BITCODE_BS unknown_short;
  BITCODE_BD height;
  BITCODE_BD dimgap;
  BITCODE_3BD ins_pt;
  BITCODE_3BD x_direction;
  BITCODE_BE extrusion;
  BITCODE_T text_value;
  BITCODE_H dimstyle;
} Dwg_Entity_TOLERANCE;

/**
 MLINE (47) entity
 */
typedef struct _dwg_MLINE_line
{
  struct _dwg_MLINE_vertex *parent;
  BITCODE_BS num_segparms;
  BITCODE_BD * segparms;
  BITCODE_BS num_areafillparms;
  BITCODE_BD* areafillparms;
} Dwg_MLINE_line;

typedef struct _dwg_MLINE_vertex
{
  struct _dwg_entity_MLINE *parent;
  BITCODE_3BD vertex;
  BITCODE_3BD vertex_direction;
  BITCODE_3BD miter_direction;
  BITCODE_RC num_lines;
  Dwg_MLINE_line* lines;
} Dwg_MLINE_vertex;

typedef struct _dwg_entity_MLINE
{
  struct _dwg_object_entity *parent;

  BITCODE_BD scale;
  BITCODE_RC justification;
  BITCODE_3BD base_point;
  BITCODE_BE extrusion;
  BITCODE_BS flags;
  BITCODE_RC num_lines; /* Linesinstyle */
  BITCODE_BS num_verts;
  Dwg_MLINE_vertex* verts;
  BITCODE_H mlinestyle;
} Dwg_Entity_MLINE;

#define COMMON_TABLE_CONTROL_FIELDS  \
  struct _dwg_object_object *parent; \
  BITCODE_BS num_entries;            \
  BITCODE_H* entries;                \
  BITCODE_BL objid

// table entries may be imported from xref's
#define COMMON_TABLE_FIELDS(laytype)      \
  struct _dwg_object_object *parent;      \
  BITCODE_##laytype flag;                 \
  BITCODE_T  name;                        \
  BITCODE_RS used;                        \
  /* may be referenced by xref: */        \
  BITCODE_B  is_xref_ref;                 \
  /* is a xref reference: */              \
  BITCODE_BS is_xref_resolved; /* 0 or 256 */ \
  /* is dependent on xref: */             \
  BITCODE_B  is_xref_dep;                 \
  BITCODE_H  xref

/**
 BLOCK_CONTROL (48) object, table header
 */
typedef struct _dwg_object_BLOCK_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
  BITCODE_H model_space;
  BITCODE_H paper_space;
} Dwg_Object_BLOCK_CONTROL;

/**
 BLOCK_HEADER (49) object, table entry
 */
typedef struct _dwg_object_BLOCK_HEADER
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_BL __iterator;
  BITCODE_RC flag2; /* preR13 */
  BITCODE_RS flag3; /* preR13 */
  BITCODE_B anonymous;    /* flag 70 bit 1 */
  BITCODE_B hasattrs;     /* flag 70 bit 2 */
  BITCODE_B blkisxref;    /* flag 70 bit 3 */
  BITCODE_B xrefoverlaid; /* flag 70 bit 4 */
  BITCODE_B loaded_bit;   /* flag 70 bit 6 */
  BITCODE_BL num_owned;
  BITCODE_3DPOINT base_pt;
  BITCODE_TV xref_pname;
  BITCODE_RL num_inserts;
  BITCODE_TV description;
  BITCODE_BL preview_size; /* no DXF. BLL? */
  BITCODE_TF preview;      /* DXF 310. Called PreviewIcon */
  BITCODE_BS insert_units;
  BITCODE_B explodable;
  BITCODE_RC block_scaling;
  BITCODE_H block_entity;
  BITCODE_H first_entity;
  BITCODE_H last_entity;
  BITCODE_H* entities;
  BITCODE_H endblk_entity;
  BITCODE_H* inserts;
  BITCODE_H layout;
} Dwg_Object_BLOCK_HEADER;

/**
 LAYER_CONTROL (50) object, table header
 */
typedef struct _dwg_object_LAYER_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_LAYER_CONTROL;

/**
 LAYER (51) object, table entry
 */
typedef struct _dwg_object_LAYER
{
  COMMON_TABLE_FIELDS(BS);
  BITCODE_B frozen;
  BITCODE_B on;
  BITCODE_B frozen_in_new;
  BITCODE_B locked;
  BITCODE_B plotflag;
  BITCODE_RC linewt;
  BITCODE_CMC color;
  short      color_rs;    /* preR13, needs to be signed */
  BITCODE_RS ltype_rs;    /* preR13 */
  BITCODE_H plotstyle;    /* DXF 390 */
  BITCODE_H material;     /* DXF 347 */
  BITCODE_H ltype;        /* DXF 6 */
  BITCODE_H visualstyle;  /* DXF 348 */
} Dwg_Object_LAYER;

/**
 STYLE_CONTROL (52) object, table header
 */
typedef struct _dwg_object_STYLE_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_STYLE_CONTROL;

/**
 STYLE (53) object, table entry.
 TextStyleTableRecord. Some call it SHAPEFILE.
 */
typedef struct _dwg_object_STYLE
{
  /*<! flag DXF 70:
     1:  is_vertical
     2:  is_upsidedown
     4:  is_shape
     8:  underlined
     16: overlined (0x10)
     32: is_shx
     64: pre_loaded (0x40)
    128: is_backward (0x80)
    256: shape_loaded (0x100)
    512: is_striked (0x200)
 */
  COMMON_TABLE_FIELDS(RC);
  BITCODE_B is_shape;
  BITCODE_B is_vertical;
  BITCODE_BD text_size;
  BITCODE_BD width_factor;
  BITCODE_BD oblique_angle;
  BITCODE_RC generation;
  BITCODE_BD last_height;
  BITCODE_T font_file;
  BITCODE_T bigfont_file;
} Dwg_Object_STYLE;

/* 54 and 55 are UNKNOWN OBJECTS */

/**
 LTYPE_CONTROL (56) object, table header
 */
typedef struct _dwg_object_LTYPE_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
  BITCODE_H bylayer;
  BITCODE_H byblock;
} Dwg_Object_LTYPE_CONTROL;

/**
 LTYPE (57) object, table entry
 */

typedef struct _dwg_LTYPE_dash {
  struct _dwg_object_LTYPE *parent;
  BITCODE_BD length;
  BITCODE_BS complex_shapecode; /* on shape_flag 2: shape number.
                                   4: index into strings_area. */
  BITCODE_H style;
  BITCODE_RD x_offset;
  BITCODE_RD y_offset;
  BITCODE_BD scale;
  BITCODE_BD rotation;
  BITCODE_BS shape_flag; /* 1: text rotated 0, 2: complex_shapecode is index,
                            4: complex_shapecode is index into strings_area. */
  BITCODE_T  text;       /* DXF 9, only if shape_flag & 2. e.g. GAS_LINE */
} Dwg_LTYPE_dash;

typedef struct _dwg_object_LTYPE
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_TV description;
  BITCODE_BD pattern_len;
  BITCODE_RC alignment;
  BITCODE_RC num_dashes;
  Dwg_LTYPE_dash* dashes;
  BITCODE_RD* dashes_r11;
  BITCODE_B has_strings_area; /* if some shape_flag & 4 (ODA bug) */
  BITCODE_TF strings_area;
} Dwg_Object_LTYPE;

/* 58 and 59 are UNKNOWN OBJECTS */

/**
 VIEW_CONTROL (60) object, table header
 */
typedef struct _dwg_object_VIEW_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_VIEW_CONTROL;

/**
 VIEW (61) object, table entry
 */
typedef struct _dwg_object_VIEW
{
  COMMON_TABLE_FIELDS(RC);
  // AbstractViewTableRecord
  BITCODE_BD VIEWSIZE;
  BITCODE_BD view_width;
  BITCODE_BD aspect_ratio;
  // ViInfo
  BITCODE_2RD VIEWCTR;
  BITCODE_3BD view_target;
  BITCODE_3BD VIEWDIR;
  BITCODE_BD twist_angle;
  BITCODE_BD lens_length;
  BITCODE_BD front_clip_z;
  BITCODE_BD back_clip_z;
  BITCODE_4BITS VIEWMODE; // DXF 71. 0: perspective, 1: front_clip_on, 2: back_clip_on, 3: front_clip_at_eye_on
  BITCODE_RC render_mode;
  BITCODE_B use_default_lights;
  BITCODE_RC default_lightning_type;
  BITCODE_BD brightness;
  BITCODE_BD contrast;
  BITCODE_CMC ambient_color;
  // ViewTableRecord
  BITCODE_B is_pspace;
  BITCODE_B associated_ucs;
  BITCODE_3BD ucsorg;
  BITCODE_3BD ucsxdir;
  BITCODE_3BD ucsydir;
  BITCODE_BD ucs_elevation;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_B is_camera_plottable;
  BITCODE_H background;
  BITCODE_H visualstyle;
  BITCODE_H sun;
  BITCODE_H base_ucs;
  BITCODE_H named_ucs;
  BITCODE_H livesection;
} Dwg_Object_VIEW;

/**
 UCS_CONTROL (62) object, table header
 */
typedef struct _dwg_object_UCS_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_UCS_CONTROL;

/**
 UCS (63) object, table entry
 */
typedef struct _dwg_UCS_orthopts
{
  struct _dwg_object_UCS *parent;
  BITCODE_BS  type; // 71
  BITCODE_3BD pt;   // 13
} Dwg_UCS_orthopts;

typedef struct _dwg_object_UCS
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_3BD ucsorg;
  BITCODE_3BD ucsxdir;
  BITCODE_3BD ucsydir;
  BITCODE_BD ucs_elevation;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_H base_ucs;
  BITCODE_H named_ucs;
  BITCODE_BL num_orthopts; // missing in ODA docs
  Dwg_UCS_orthopts *orthopts;
} Dwg_Object_UCS;

/**
 VPORT_CONTROL (64) object, table header
 */
typedef struct _dwg_object_VPORT_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_VPORT_CONTROL;

/**
 VPORT (65) object, table entry
 */
typedef struct _dwg_object_VPORT
{
  COMMON_TABLE_FIELDS(RC);
  // AbstractViewTableRecord
  BITCODE_BD VIEWSIZE;     // really the view height
  BITCODE_BD view_width;   // in DWG r13+, needed to calc. aspect_ratio
  BITCODE_BD aspect_ratio; // DXF 41 = view_width / VIEWSIZE
  // ViInfo
  BITCODE_2RD VIEWCTR;
  BITCODE_3BD view_target;
  BITCODE_3BD VIEWDIR;
  BITCODE_BD view_twist;
  BITCODE_BD lens_length;
  BITCODE_BD front_clip_z;
  BITCODE_BD back_clip_z;
  BITCODE_4BITS VIEWMODE;
  BITCODE_RC render_mode;
  BITCODE_B use_default_lights;
  BITCODE_RC default_lightning_type;
  BITCODE_BD brightness;
  BITCODE_BD contrast;
  BITCODE_CMC ambient_color;
  // ViewportTableRecord
  BITCODE_2RD lower_left;
  BITCODE_2RD upper_right;
  BITCODE_B UCSFOLLOW;
  BITCODE_BS circle_zoom; /* circle sides: nr of tesselations */
  BITCODE_B FASTZOOM;
  BITCODE_RC UCSICON;     /* DXF 71:  0: icon_on, 1: icon_at_ucsorg */
  BITCODE_B GRIDMODE;     /* DXF 76: on or off */
  BITCODE_2RD GRIDUNIT;
  BITCODE_B SNAPMODE;     /* DXF 75: on or off */
  BITCODE_B SNAPSTYLE;
  BITCODE_BS SNAPISOPAIR;
  BITCODE_BD SNAPANG;
  BITCODE_2RD SNAPBASE;
  BITCODE_2RD SNAPUNIT;
  BITCODE_B ucs_at_origin;
  BITCODE_B UCSVP;
  BITCODE_3BD ucsorg;
  BITCODE_3BD ucsxdir;
  BITCODE_3BD ucsydir;
  BITCODE_BD ucs_elevation;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_BS grid_flags; /* bit 1: bound to limits, bit 2: adaptive */
  BITCODE_BS grid_major;
  BITCODE_H background;
  BITCODE_H visualstyle;
  BITCODE_H sun;
  BITCODE_H named_ucs;
  BITCODE_H base_ucs;
} Dwg_Object_VPORT;

/**
 APPID_CONTROL (66) object
 The table header of all registered applications
 */
typedef struct _dwg_object_APPID_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_APPID_CONTROL;

/**
 APPID (67) object
 The table entry of a registered application
 */
typedef struct _dwg_object_APPID
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_RC unknown;
} Dwg_Object_APPID;

/**
 DIMSTYLE_CONTROL (68) object
 The table header of all dimension styles
 */
typedef struct _dwg_object_DIMSTYLE_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
  BITCODE_RC num_morehandles; /* DXF 71 undocumented */
  BITCODE_H* morehandles;     /* DXF 340 */
} Dwg_Object_DIMSTYLE_CONTROL;

/**
 DIMSTYLE (69) object, table entry
 */
typedef struct _dwg_object_DIMSTYLE
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_B DIMTOL;
  BITCODE_B DIMLIM;
  BITCODE_B DIMTIH;
  BITCODE_B DIMTOH;
  BITCODE_B DIMSE1;
  BITCODE_B DIMSE2;
  BITCODE_B DIMALT;
  BITCODE_B DIMTOFL;
  BITCODE_B DIMSAH;
  BITCODE_B DIMTIX;
  BITCODE_B DIMSOXD;
  BITCODE_BS DIMALTD;   /*!< r13-r14 only RC */
  BITCODE_BS DIMZIN;    /*!< r13-r14 only RC */
  BITCODE_B DIMSD1;
  BITCODE_B DIMSD2;
  BITCODE_BS DIMTOLJ;   /*!< r13-r14 only RC */
  BITCODE_BS DIMJUST;   /*!< r13-r14 only RC */
  BITCODE_BS DIMFIT;    /*!< r13-r14 only RC */
  BITCODE_B DIMUPT;
  BITCODE_BS DIMTZIN;   /*!< r13-r14 only RC */
  BITCODE_BS DIMMALTZ;  /*!< r13-r14 only RC */
  BITCODE_BS DIMMALTTZ; /*!< r13-r14 only RC */
  BITCODE_BS DIMTAD;    /*!< r13-r14 only RC */
  BITCODE_BS DIMUNIT;
  BITCODE_BS DIMAUNIT;
  BITCODE_BS DIMDEC;
  BITCODE_BS DIMTDEC;
  BITCODE_BS DIMALTU;
  BITCODE_BS DIMALTTD;
  /* BITCODE_H DIMTXSTY; */
  BITCODE_BD DIMSCALE;
  BITCODE_BD DIMASZ;
  BITCODE_BD DIMEXO;
  BITCODE_BD DIMDLI;
  BITCODE_BD DIMEXE;
  BITCODE_BD DIMRND;
  BITCODE_BD DIMDLE;
  BITCODE_BD DIMTP;
  BITCODE_BD DIMTM;
  BITCODE_BD DIMFXL;
  BITCODE_BD DIMJOGANG;
  BITCODE_BS DIMTFILL;
  BITCODE_CMC DIMTFILLCLR;
  BITCODE_BS DIMAZIN;
  BITCODE_BS DIMARCSYM;
  BITCODE_BD DIMTXT;
  BITCODE_BD DIMCEN;
  BITCODE_BD DIMTSZ;
  BITCODE_BD DIMALTF;
  BITCODE_BD DIMLFAC;
  BITCODE_BD DIMTVP;
  BITCODE_BD DIMTFAC;
  BITCODE_BD DIMGAP;
  BITCODE_T DIMPOST;
  BITCODE_T DIMAPOST;
  BITCODE_T DIMBLK_T;
  BITCODE_T DIMBLK1_T;
  BITCODE_T DIMBLK2_T;
  BITCODE_BD DIMALTRND;
  BITCODE_RS DIMCLRD_N; /* preR13 */
  BITCODE_RS DIMCLRE_N; /* preR13 */
  BITCODE_RS DIMCLRT_N; /* preR13 */
  BITCODE_CMC DIMCLRD;
  BITCODE_CMC DIMCLRE;
  BITCODE_CMC DIMCLRT;
  BITCODE_BS DIMADEC;
  BITCODE_BS DIMFRAC;
  BITCODE_BS DIMLUNIT;
  BITCODE_BS DIMDSEP;
  BITCODE_BS DIMTMOVE;
  BITCODE_BS DIMALTZ;
  BITCODE_BS DIMALTTZ;
  BITCODE_BS DIMATFIT;
  BITCODE_B DIMFXLON;   /*!< r2007+ */
  BITCODE_B  DIMTXTDIRECTION; /*!< r2010+ */
  BITCODE_BD DIMALTMZF; /*!< r2010+ */
  BITCODE_T  DIMALTMZS; /*!< r2010+ */
  BITCODE_BD DIMMZF;    /*!< r2010+ */
  BITCODE_T  DIMMZS;    /*!< r2010+ */
  BITCODE_BSd DIMLWD;
  BITCODE_BSd DIMLWE;
  BITCODE_B flag0;

  BITCODE_H DIMTXSTY;

  BITCODE_H DIMLDRBLK;
  BITCODE_H DIMBLK;
  BITCODE_H DIMBLK1;
  BITCODE_H DIMBLK2;

  BITCODE_H DIMLTYPE;
  BITCODE_H DIMLTEX1;
  BITCODE_H DIMLTEX2;
} Dwg_Object_DIMSTYLE;

/**
 VPORT_ENTITY_CONTROL (70) table object (r11-r2000)
 The table header of all vport entities (unused in newer versions)
 Called VXTable
 */
typedef struct _dwg_object_VPORT_ENTITY_CONTROL
{
  COMMON_TABLE_CONTROL_FIELDS;
} Dwg_Object_VPORT_ENTITY_CONTROL;

/**
 VPORT_ENTITY_HEADER (71) table object (r11-r2000)
 Called VXTableRecord
 */
typedef struct _dwg_object_VPORT_ENTITY_HEADER
{
  COMMON_TABLE_FIELDS(RC);
  BITCODE_B is_on;
  BITCODE_H viewport;
  BITCODE_H prev_entry;
} Dwg_Object_VPORT_ENTITY_HEADER;

/**
 GROUP (72) object
 */
typedef struct _dwg_object_GROUP
{
  struct _dwg_object_object *parent;
  BITCODE_TV name;
  BITCODE_BS unnamed;
  BITCODE_BS selectable;
  BITCODE_BL num_groups;
  BITCODE_H* groups;
} Dwg_Object_GROUP;

/**
 MLINESTYLE (73) object
 */
typedef struct _dwg_MLINESTYLE_line
{
  struct _dwg_object_MLINESTYLE *parent;
  BITCODE_BD  offset;
  BITCODE_CMC color;
  BITCODE_BSd lt_index;   /* until 2018 */
  BITCODE_H   lt_ltype;   /* since 2018 */
} Dwg_MLINESTYLE_line;

typedef struct _dwg_object_MLINESTYLE
{
  struct _dwg_object_object *parent;
  BITCODE_TV name;
  BITCODE_TV description;
  BITCODE_BS flag;
  BITCODE_CMC fill_color;
  BITCODE_BD start_angle;
  BITCODE_BD end_angle;
  BITCODE_RC num_lines;
  Dwg_MLINESTYLE_line* lines;
} Dwg_Object_MLINESTYLE;

/**
 OLE2FRAME (74 + varies) object
 */
typedef struct _dwg_entity_OLE2FRAME
{
  struct _dwg_object_entity *parent;

  BITCODE_BS type;         /*!< DXF 71, 1: Link, 2: Embedded, 3: Static */
  BITCODE_BS mode;         /*!< r2000+ DXF 72, tile_mode, 0: mspace, 1: pspace */
  BITCODE_RC lock_aspect;  /*!< r2000+ DXF 73, 0 or 1 (locked) */
  BITCODE_BL data_size;    /*!< DXF 90 */
  BITCODE_TF data;         /*!< DXF 310, the binary object data */
  // embedded into data, not yet decoded:
  // the MS-CFB (ole2 stream) starts at 0x80 in data
  // before is probably:
  BITCODE_BS oleversion;   /*!< DXF 70, always 2 */
  BITCODE_TF oleclient;    /*!< DXF 3, e.g. OLE or Paintbrush Picture */
  BITCODE_3BD pt1;         /*!< DXF 10, upper left corner */
  BITCODE_3BD pt2;         /*!< DXF 11, lower right corner */
} Dwg_Entity_OLE2FRAME;

/**
 DUMMY (75) object, placeholder for unsupported types on encode.
 */
typedef struct _dwg_object_DUMMY
{
  struct _dwg_object_object *parent;
} Dwg_Object_DUMMY;

/**
 LONG_TRANSACTION (76) object
 */
typedef struct _dwg_object_LONG_TRANSACTION
{
  struct _dwg_object_object *parent;
  /* ??? not seen */
} Dwg_Object_LONG_TRANSACTION;

/* NOT SURE ABOUT THIS ONE (IS IT OBJECT OR ENTITY?): */
/**
 subtype PROXY_LWPOLYLINE (33) in a PROXY object
 Not a LWPOLYLINE (77? + varies)
 */
typedef struct _dwg_LWPOLYLINE_width
{
  BITCODE_BD start; /* 40 */
  BITCODE_BD end;   /* 41 */
} Dwg_LWPOLYLINE_width;

typedef struct _dwg_entity_PROXY_LWPOLYLINE
{
  struct _dwg_object_entity *parent;

  BITCODE_RL size; /* from flags to *widths */
  BITCODE_BS flags;
  BITCODE_BD const_width;
  BITCODE_BD elevation;
  BITCODE_BD thickness;
  BITCODE_BE extrusion;
  BITCODE_BL num_points;
  BITCODE_2RD* points;
  BITCODE_BL num_bulges;
  BITCODE_BD* bulges;
  BITCODE_BL num_widths;
  Dwg_LWPOLYLINE_width* widths;
  BITCODE_RC unknown_1;
  BITCODE_RC unknown_2;
  BITCODE_RC unknown_3;
} Dwg_Entity_PROXY_LWPOLYLINE;

/**
 PROXY_ENTITY (498, 0x1f2) object
 */
typedef struct _dwg_entity_PROXY_ENTITY
{
  struct _dwg_object_entity *parent;

  BITCODE_BL class_id;      /*!< DXF 91, always 498, same as obj->type */
  BITCODE_BL version;       /*!< DXF 95 <r2018, 71 r2018+ */
  BITCODE_BL maint_version; /*!< DXF 97 r2018+ */
  BITCODE_B from_dxf;       /*!< DXF 70 */
  BITCODE_BL data_numbits;
  BITCODE_BL data_size;     /*!< DXF 93 */
  BITCODE_RC *data;         /*!< DXF 310 */
  BITCODE_BL num_objids;
  BITCODE_H* objids;        /*!< DXF 340 */
} Dwg_Entity_PROXY_ENTITY;

/**
 PROXY OBJECT (499, 0x1f3) object
 */
typedef struct _dwg_object_PROXY_OBJECT
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_id;      /*!< DXF 91, always 499, same as obj->type */
  BITCODE_BL version;       /*!< DXF 95 <r2018, 71 r2018+ */
  BITCODE_BL maint_version; /*!< DXF 97 r2018+ */
  BITCODE_B from_dxf;       /*!< DXF 70 */
  BITCODE_BL data_numbits;
  BITCODE_BL data_size;     /*!< DXF 93 */
  BITCODE_RC *data;         /*!< DXF 310 */
  BITCODE_BL num_objids;
  BITCODE_H* objids;        /*!< DXF 340 */
} Dwg_Object_PROXY_OBJECT;

/**
 * types which are fixed and non-fixed:
 * also OLE2FRAME above
 */

/**
 Structs for HATCH (78 + varies)
 */
typedef struct _dwg_HATCH_Color
{
  struct _dwg_entity_HATCH *parent;
  BITCODE_BD shift_value; //0.0 non-shifted, 1.0 shifted
  BITCODE_CMC color;
} Dwg_HATCH_Color;

typedef struct _dwg_HATCH_ControlPoint
{
  struct _dwg_HATCH_PathSeg *parent;
  BITCODE_2RD point;
  BITCODE_BD weight;
} Dwg_HATCH_ControlPoint;

typedef struct _dwg_HATCH_PathSeg
{
  struct _dwg_HATCH_Path *parent;
  BITCODE_RC curve_type; // i.e. curve_type: 1-4
  // could be a union
  /* LINE */
  BITCODE_2RD first_endpoint;
  BITCODE_2RD second_endpoint;
  /* CIRCULAR ARC */
  BITCODE_2RD center;
  BITCODE_BD radius;
  BITCODE_BD start_angle;
  BITCODE_BD end_angle;
  BITCODE_B is_ccw;
  /* ELLIPTICAL ARC */
  /* BITCODE_2RD center */
  BITCODE_2RD endpoint;
  BITCODE_BD minor_major_ratio;
  /* BITCODE_BD start_angle; */
  /* BITCODE_BD end_angle; */
  /* BITCODE_B is_ccw; */
  /* SPLINE */
  BITCODE_BL degree;
  BITCODE_B is_rational;
  BITCODE_B is_periodic;
  BITCODE_BL num_knots;
  BITCODE_BL num_control_points;
  BITCODE_BD* knots;
  Dwg_HATCH_ControlPoint* control_points;
  BITCODE_BL num_fitpts;
  BITCODE_2RD *fitpts;
  BITCODE_2RD start_tangent;
  BITCODE_2RD end_tangent;
} Dwg_HATCH_PathSeg;

typedef struct _dwg_HATCH_PolylinePath
{
  struct _dwg_HATCH_Path *parent;
  BITCODE_2RD point;
  BITCODE_BD bulge;
} Dwg_HATCH_PolylinePath;

typedef struct _dwg_HATCH_Path
{
  struct _dwg_entity_HATCH *parent;
  /* Segment path */
  BITCODE_BL flag; /* 2: is_polyline, 4: is_derived, 8: is_textbox,
                      0x20: is_open, 0x80: is_textisland, 0x100: is_duplicate, 0x200: is_annotative */
  BITCODE_BL num_segs_or_paths;
  Dwg_HATCH_PathSeg* segs;

  /* Polyline path */
  BITCODE_B bulges_present;
  BITCODE_B closed;
  Dwg_HATCH_PolylinePath* polyline_paths;

  BITCODE_BL num_boundary_handles;
} Dwg_HATCH_Path;

typedef struct _dwg_HATCH_DefLine
{
  struct _dwg_entity_HATCH *parent;
  BITCODE_BD  angle;
  BITCODE_2BD pt0;
  BITCODE_2BD offset;
  BITCODE_BS  num_dashes;
  BITCODE_BD* dashes;
} Dwg_HATCH_DefLine;

typedef struct _dwg_entity_HATCH
{
  struct _dwg_object_entity *parent;

  BITCODE_BL is_gradient_fill;
  BITCODE_BL reserved;
  BITCODE_BD gradient_angle;
  BITCODE_BD gradient_shift;
  BITCODE_BL single_color_gradient;
  BITCODE_BD gradient_tint;
  BITCODE_BL num_colors;
  Dwg_HATCH_Color* colors;
  BITCODE_T gradient_name; /* 1: SPHERICAL, 2: HEMISPHERICAL, 3: CURVED, 4: LINEAR, 5: CYLINDER */
  BITCODE_BD elevation;
  BITCODE_BE extrusion;
  BITCODE_TV name;
  BITCODE_B is_solid_fill;
  BITCODE_B is_associative;
  BITCODE_BL num_paths;
  Dwg_HATCH_Path* paths; // also named loop
  BITCODE_BS style;
  BITCODE_BS pattern_type;
  BITCODE_BD angle;
  BITCODE_BD scale_spacing;
  BITCODE_B double_flag;
  BITCODE_BS num_deflines;
  Dwg_HATCH_DefLine * deflines;
  BITCODE_B has_derived;
  BITCODE_BD pixel_size;
  BITCODE_BL num_seeds;
  BITCODE_2RD * seeds;
  BITCODE_BL num_boundary_handles;
  BITCODE_H* boundary_handles;
} Dwg_Entity_HATCH;

/**
 XRECORD (79 + varies) object
 */
typedef struct _dwg_object_XRECORD
{
  struct _dwg_object_object *parent;

  BITCODE_BS cloning_flags;
  BITCODE_BL xdata_size;
  BITCODE_BL num_xdata; /* computed */
  Dwg_Resbuf* xdata;
  BITCODE_BL num_objid_handles;
  BITCODE_H* objid_handles;
} Dwg_Object_XRECORD;

/**
 PLACEHOLDER (80 + varies) object
 ACDBPLACEHOLDER
 */
typedef struct _dwg_object_PLACEHOLDER
{
  struct _dwg_object_object *parent;
} Dwg_Object_PLACEHOLDER;

/**
 * Entity MULTILEADER (varies)
 * R2000+ in work
 */

typedef struct _dwg_LEADER_Break
{
  struct _dwg_LEADER_Line *parent;
  BITCODE_3BD start;         /*!< DXF 12 */
  BITCODE_3BD end;           /*!< DXF 13 */
} Dwg_LEADER_Break;

typedef struct _dwg_LEADER_Line // as documented by DXF
{
  struct _dwg_LEADER_Node *parent;
  BITCODE_BL num_points;
  BITCODE_3DPOINT* points;         /*!< DXF 10 */
  BITCODE_BL num_breaks;
  Dwg_LEADER_Break * breaks;       /*!< DXF 12, 13 */
  BITCODE_BL  line_index;          /*!< DXF 91 */

  /*!< r2010+: */
  BITCODE_BS type; // 0 = invisible leader, 1 = straight leader, 2 = spline leader
  BITCODE_CMC color; // of the line
  BITCODE_H ltype; // 5 340
  BITCODE_BLd linewt;
  BITCODE_BD arrow_size;
  BITCODE_H  arrow_handle; // 5 341
  BITCODE_BL flags; // 1 = leader type, 2 = line color, 4 = line type, 8 = line weight,
                    // 16 = arrow size, 32 = arrow symbol (handle)
} Dwg_LEADER_Line;

typedef struct _dwg_LEADER_ArrowHead
{
  struct _dwg_entity_MULTILEADER *parent;
  BITCODE_B is_default;
  BITCODE_H arrowhead;
} Dwg_LEADER_ArrowHead;

typedef struct _dwg_LEADER_BlockLabel
{
  struct _dwg_entity_MULTILEADER *parent;
  BITCODE_H attdef;
  BITCODE_TV label_text;
  BITCODE_BS ui_index;
  BITCODE_BD width;
} Dwg_LEADER_BlockLabel;

typedef struct _dwg_LEADER_Node
{
  struct _dwg_entity_MULTILEADER *parent;
  BITCODE_B has_lastleaderlinepoint;    /*!< DXF 290 */
  BITCODE_B has_dogleg;                 /*!< DXF 291 */
  BITCODE_3BD lastleaderlinepoint;      /*!< DXF 10 */
  BITCODE_3BD dogleg_vector;            /*!< DXF 11 */
  BITCODE_BL branch_index;              /*!< DXF 90 */
  BITCODE_BD dogleg_length;             /*!< DXF 40 */
  BITCODE_BL num_lines;
  Dwg_LEADER_Line *lines;               /*!< DXF 10 */
  BITCODE_BL num_breaks;
  Dwg_LEADER_Break * breaks;            /*!< DXF 12, 13 */

  BITCODE_BS attach_dir; //2010+ 271
} Dwg_LEADER_Node;

// common to text and block
#define CMLContent_fields                                                     \
  BITCODE_RC type; /* 1 for blk, 2 for text */                                \
  BITCODE_3BD normal;                                                         \
  BITCODE_3BD location;                                                       \
  BITCODE_BD rotation

typedef struct _dwg_MLEADER_Content_MText
{
  CMLContent_fields;
  BITCODE_T default_text;
  BITCODE_H style;
  BITCODE_3BD direction;
  BITCODE_BD width;
  BITCODE_BD height;
  BITCODE_BD line_spacing_factor;
  BITCODE_BS line_spacing_style;
  BITCODE_CMC color;
  BITCODE_BS alignment;
  BITCODE_BS flow;
  BITCODE_CMC bg_color;
  BITCODE_BD bg_scale;
  BITCODE_BL bg_transparency;
  BITCODE_B is_bg_fill;
  BITCODE_B is_bg_mask_fill;
  BITCODE_BS col_type;
  BITCODE_B is_height_auto;
  BITCODE_BD col_width;
  BITCODE_BD col_gutter;
  BITCODE_B is_col_flow_reversed;
  BITCODE_BL num_col_sizes;
  BITCODE_BD *col_sizes;
  BITCODE_B word_break;
  BITCODE_B unknown;
} Dwg_MLEADER_Content_MText;

typedef struct _dwg_MLEADER_Content_Block
{
  CMLContent_fields;
  BITCODE_H block_table;
  BITCODE_3BD scale;
  BITCODE_CMC color;
  BITCODE_BD *transform;
} Dwg_MLEADER_Content_Block;

typedef union _dwg_MLEADER_Content
{
  Dwg_MLEADER_Content_MText txt;
  Dwg_MLEADER_Content_Block blk;
} Dwg_MLEADER_Content;

/* The MLeaderAnnotContext object (par 20.4.86), embedded into an MLEADER */
typedef struct _dwg_MLEADER_AnnotContext
{
  // AcDbObjectContextData:
  // BITCODE_BS class_version;  /*!< r2010+ DXF 70 */
  // BITCODE_B has_xdic_file;   /*!< r2010+ default true */
  // BITCODE_B is_default;      /*!< r2010+ DXF 290 */
  // AcDbAnnotScaleObjectContextData:
  // BITCODE_H scale;           /*!< DXF 340 hard ptr to AcDbScale */

  BITCODE_BL num_leaders;
  Dwg_LEADER_Node *leaders;

  BITCODE_BS attach_dir;

  BITCODE_BD scale_factor;
  BITCODE_3BD content_base;
  BITCODE_BD text_height;
  BITCODE_BD arrow_size;
  BITCODE_BD landing_gap;
  BITCODE_BS text_left;
  BITCODE_BS text_right;
  BITCODE_BS text_angletype;
  BITCODE_BS text_alignment;

  BITCODE_B has_content_txt;
  BITCODE_B has_content_blk;
  Dwg_MLEADER_Content content; // union txt/blk

  BITCODE_3BD base;
  BITCODE_3BD base_dir;
  BITCODE_3BD base_vert;
  BITCODE_B is_normal_reversed;

  BITCODE_BS text_top;
  BITCODE_BS text_bottom;

} Dwg_MLEADER_AnnotContext;

// dbmleader.h
typedef struct _dwg_entity_MULTILEADER
{
  struct _dwg_object_entity *parent;

  BITCODE_BS class_version; /*!< r2010+ =2 */
  Dwg_MLEADER_AnnotContext ctx;
  BITCODE_H mleaderstyle; /* DXF  340 */
  BITCODE_BL flags;       /* override. DXF 90 */
  BITCODE_BS type;
  BITCODE_CMC color;
  BITCODE_H ltype;
  BITCODE_BLd linewt;
  BITCODE_B has_landing;
  BITCODE_B has_dogleg;
  BITCODE_BD landing_dist;
  BITCODE_H arrow_handle;
  BITCODE_BD arrow_size; /* the default */
  BITCODE_BS style_content;
  BITCODE_H text_style;
  BITCODE_BS text_left;
  BITCODE_BS text_right;
  BITCODE_BS text_angletype;
  BITCODE_BS text_alignment;
  BITCODE_CMC text_color;
  BITCODE_B has_text_frame;
  BITCODE_H block_style; // internal blocks mostly, _TagSlot, _TagHexagon,
                         // _DetailCallout, ...
  BITCODE_CMC block_color;
  BITCODE_3BD block_scale;
  BITCODE_BD block_rotation;
  BITCODE_BS style_attachment; // 0 = center extents, 1 = insertion point
  BITCODE_B is_annotative;

  /* until r2007: */
  BITCODE_BL num_arrowheads;
  Dwg_LEADER_ArrowHead *arrowheads;
  BITCODE_BL num_blocklabels;
  Dwg_LEADER_BlockLabel *blocklabels;
  BITCODE_B is_neg_textdir;
  BITCODE_BS ipe_alignment;
  BITCODE_BS justification;
  BITCODE_BD scale_factor;

  BITCODE_BS attach_dir;    /*!< r2010+ (0 = horizontal, 1 = vertical) */
  BITCODE_BS attach_top;    /*!< r2010+ */
  BITCODE_BS attach_bottom; /*!< r2010+ */

  BITCODE_B is_text_extended; /*!< r2013+ */
} Dwg_Entity_MULTILEADER;

/**
 * Object MLEADERSTYLE (varies)
 * R2000+
 */
typedef struct _dwg_object_MLEADERSTYLE
{
  struct _dwg_object_object *parent;

  BITCODE_BS class_version; /*!< DXF 179, r2010+ =2 */
  BITCODE_BS content_type;
  BITCODE_BS mleader_order;
  BITCODE_BS leader_order;
  BITCODE_BL max_points;
  BITCODE_BD first_seg_angle;
  BITCODE_BD second_seg_angle;
  BITCODE_BS type;
  BITCODE_CMC line_color;
  BITCODE_H line_type;
  BITCODE_BLd linewt;
  BITCODE_B has_landing;
  BITCODE_B has_dogleg;
  BITCODE_BD landing_gap;
  BITCODE_BD landing_dist;
  BITCODE_TV description;
  BITCODE_H arrow_head;
  BITCODE_BD arrow_head_size;
  BITCODE_TV text_default;
  BITCODE_H text_style;
  BITCODE_BS attach_left;
  BITCODE_BS attach_right;
  BITCODE_BS text_angle_type;
  BITCODE_BS text_align_type;
  BITCODE_CMC text_color;
  BITCODE_BD text_height;
  BITCODE_B has_text_frame;
  BITCODE_B text_always_left;
  BITCODE_BD align_space;
  BITCODE_H block;
  BITCODE_CMC block_color;
  BITCODE_3BD block_scale;
  BITCODE_B use_block_scale;
  BITCODE_BD block_rotation;
  BITCODE_B use_block_rotation;
  BITCODE_BS block_connection;
  BITCODE_BD scale;
  BITCODE_B is_changed;
  BITCODE_B is_annotative;
  BITCODE_BD break_size;

  BITCODE_BS attach_dir;    /*!< r2010+ (0 = horizontal, 1 = vertical) */
  BITCODE_BS attach_top;    /*!< r2010+ */
  BITCODE_BS attach_bottom; /*!< r2010+ */

  BITCODE_B text_extended; /*!< r2013+ */
} Dwg_Object_MLEADERSTYLE;

/**
 VBA_PROJECT (81 + varies) object
 Has its own optional section? section[5]?
 */
typedef struct _dwg_object_VBA_PROJECT
{
  struct _dwg_object_object *parent;

  BITCODE_BL data_size;
  BITCODE_TF data;
} Dwg_Object_VBA_PROJECT;

/**
 Object PLOTSETTINGS (varies)
 See also LAYOUT.
 */
typedef struct _dwg_object_PLOTSETTINGS
{
  struct _dwg_object_object *parent;

  BITCODE_T printer_cfg_file;     /*!< DXF 1 */
  BITCODE_T paper_size;           /*!< DXF 2 */
  BITCODE_T canonical_media_name; /*!< DXF 4 */
  BITCODE_BS plot_flags;          /*!< DXF 70
                                 1 = PlotViewportBorders
                                 2 = ShowPlotStyles
                                 4 = PlotCentered
                                 8 = PlotHidden
                                 16 = UseStandardScale
                                 32 = PlotPlotStyles
                                 64 = ScaleLineweights
                                 128 = PrintLineweights
                                 512 = DrawViewportsFirst
                                 1024 = ModelType
                                 2048 = UpdatePaper
                                 4096 = ZoomToPaperOnUpdate
                                 8192 = Initializing
                                 16384 = PrevPlotInit */
  BITCODE_H plotview;             /*!< DXF 6, r2004+ */
  BITCODE_T plotview_name;        /*!< DXF 6, until r2000 */
  BITCODE_BD left_margin;         /*!< DXF 40, margins in mm */
  BITCODE_BD bottom_margin;       /*!< DXF 42 */
  BITCODE_BD right_margin;        /*!< DXF 43 */
  BITCODE_BD top_margin;          /*!< DXF 44 */
  BITCODE_BD paper_width;         /*!< DXF 44, in mm */
  BITCODE_BD paper_height;        /*!< DXF 45, in mm */
  BITCODE_2BD_1 plot_origin;      /*!< DXF 46,47 */
  BITCODE_2BD_1 plot_window_ll;   /*!< DXF 48,49 */
  BITCODE_2BD_1 plot_window_ur;   /*!< DXF 140,141 */
  BITCODE_BS plot_paper_unit;     /*!< DXF 72,  0 inches, 1 mm, 2 pixel */
  BITCODE_BS
      plot_rotation_mode; /*!< DXF 73,  0 normal, 1 90, 2 180, 3 270 deg */
  BITCODE_BS plot_type; /*!< DXF 74,  0 display, 1 extents, 2 limits, 3 view
                           (see DXF 6), 4 window (see 48-140), 5 layout */
  BITCODE_BD paper_units;   /*!< DXF 142 */
  BITCODE_BD drawing_units; /*!< DXF 143 */
  BITCODE_T stylesheet;     /*!< DXF 7 */
  BITCODE_BS
      std_scale_type;               /*!< DXF 75, 0 = scaled to fit,
                                      1 = 1/128"=1', 2 = 1/64"=1', 3 = 1/32"=1'
                                      4 = 1/16"=1', 5 = 3/32"=1', 6 = 1/8"=1'
                                      7 = 3/16"=1', 8 = 1/4"=1', 9 = 3/8"=1'
                                      10 = 1/2"=1', 11 = 3/4"=1', 12 = 1"=1'
                                      13 = 3"=1', 14 = 6"=1', 15 = 1'=1'
                                      16 = 1:1, 17= 1:2, 18 = 1:4 19 = 1:8, 20 = 1:10, 21=
                                      1:16               22 = 1:20, 23 = 1:30, 24 = 1:40, 25 = 1:50, 26 =
                                      1:100               27 = 2:1, 28 = 4:1, 29 = 8:1, 30 = 10:1, 31 =
                                      100:1, 32 = 1000:1
                                    */
  BITCODE_BD std_scale_factor;      /*!< DXF 147, value of 75 */
  BITCODE_2BD_1 paper_image_origin; /*!< DXF 148 + 149 */
  BITCODE_BS shadeplot_type; /*!< DXF 76, 0 display, 1 wireframe, 2 hidden, 3
                                rendered, 4 visualstyle, 5 renderPreset */
  BITCODE_BS
      shadeplot_reslevel;         /*!< DXF 77, 0 draft, 1 preview, 2 nomal,
                                               3 presentation, 4 maximum, 5 custom */
  BITCODE_BS shadeplot_customdpi; /*!< DXF 78, 100-32767 */
  BITCODE_H shadeplot;            /*!< DXF 333 optional. As in VIEWPORT */
} Dwg_Object_PLOTSETTINGS;

/**
 LAYOUT (82 + varies) object
 */
typedef struct _dwg_object_LAYOUT
{
  struct _dwg_object_object *parent;
  // AcDbPlotSettings:
  Dwg_Object_PLOTSETTINGS plotsettings;

  // AcDbLayout:
  BITCODE_T layout_name;
  BITCODE_BS tab_order;
  BITCODE_BS layout_flags; /* 1: PSLTSCALE, 2: LIMCHECK */
  BITCODE_3DPOINT INSBASE;
  BITCODE_2DPOINT LIMMIN;
  BITCODE_2DPOINT LIMMAX;
  BITCODE_3DPOINT UCSORG;
  BITCODE_3DPOINT UCSXDIR;
  BITCODE_3DPOINT UCSYDIR;
  BITCODE_BD ucs_elevation;
  BITCODE_BS UCSORTHOVIEW;
  BITCODE_3DPOINT EXTMIN;
  BITCODE_3DPOINT EXTMAX;
  BITCODE_H block_header;
  BITCODE_H active_viewport;
  BITCODE_H base_ucs;
  BITCODE_H named_ucs;
  BITCODE_BL num_viewports; // r2004+
  BITCODE_H *viewports;     // r2004+
} Dwg_Object_LAYOUT;

/**
 * And the non-fixed types, classes, only
 */

/**
 Class DICTIONARYVAR (varies)
 */
typedef struct _dwg_object_DICTIONARYVAR
{
  struct _dwg_object_object *parent;

  BITCODE_RC intval;
  BITCODE_TV str;
} Dwg_Object_DICTIONARYVAR;

/**
 Class DICTIONARYWDFLT (varies)
 */
typedef struct _dwg_object_DICTIONARYWDFLT
{
  struct _dwg_object_object *parent;

  BITCODE_BL numitems;    /*!< no DXF */
  BITCODE_BS cloning;     /*!< DXF 281 */
  BITCODE_RC hard_owner;  /*!< DXF 330 */
  BITCODE_TV *texts;      /*!< DXF 3 */
  BITCODE_H *itemhandles; /*!< DXF 350/360, pairwise with texts */

  BITCODE_RL cloning_r14; /*!< r14 only */
  BITCODE_H defaultid;
} Dwg_Object_DICTIONARYWDFLT;

/**
 Class TABLE (varies)
 */

// 20.4.99. also for FIELD
typedef struct _dwg_TABLE_value
{
  BITCODE_BL flags;        /* DXF 90 */
  BITCODE_BL format_flags; /* DXF 93, r2007+ */
  BITCODE_BL data_type;
  BITCODE_BL data_size;
  BITCODE_BL data_long;
  BITCODE_BD data_double;
  BITCODE_TV data_string;
  BITCODE_TF data_date;
  BITCODE_2RD data_point;
  BITCODE_3RD data_3dpoint;
  BITCODE_H data_handle;
  BITCODE_BL unit_type;
  BITCODE_TV format_string;
  BITCODE_TV value_string;
} Dwg_TABLE_value;

// 20.4.100 Custom data collection for table cells, cols, rows
typedef struct _dwg_TABLE_CustomDataItem
{
  BITCODE_TV name;
  Dwg_TABLE_value value;

  struct _dwg_TableCell *cell_parent;
  struct _dwg_TableRow *row_parent;
} Dwg_TABLE_CustomDataItem;

typedef struct _dwg_TABLE_AttrDef
{
  BITCODE_H attdef;
  BITCODE_BS index;
  BITCODE_T text;
} Dwg_TABLE_AttrDef;

typedef struct _dwg_TABLE_Cell
{
  BITCODE_BS type;
  BITCODE_RC flags;
  BITCODE_B is_merged_value;
  BITCODE_B is_autofit_flag;
  BITCODE_BL merged_width_flag;
  BITCODE_BL merged_height_flag;
  BITCODE_BD rotation;
  BITCODE_T text_value;
  BITCODE_H text_style;
  BITCODE_H block_handle;
  BITCODE_BD block_scale;
  BITCODE_B additional_data_flag;
  BITCODE_BL cell_flag_override;
  BITCODE_RC virtual_edge_flag;
  BITCODE_RS cell_alignment;
  BITCODE_B bg_fill_none;
  BITCODE_CMC bg_color;
  BITCODE_CMC content_color;
  BITCODE_BD text_height;
  BITCODE_CMC top_grid_color;
  BITCODE_BS top_grid_linewt;
  BITCODE_BS top_visibility;
  BITCODE_CMC right_grid_color;
  BITCODE_BS right_grid_linewt;
  BITCODE_BS right_visibility;
  BITCODE_CMC bottom_grid_color;
  BITCODE_BS bottom_grid_linewt;
  BITCODE_BS bottom_visibility;
  BITCODE_CMC left_grid_color;
  BITCODE_BS left_grid_linewt;
  BITCODE_BS left_visibility;
  BITCODE_BL unknown;
  Dwg_TABLE_value value;
  BITCODE_BL num_attr_defs;
  Dwg_TABLE_AttrDef *attr_defs;
  // BITCODE_H text_style_override;

  struct _dwg_entity_TABLE *parent;
} Dwg_TABLE_Cell;

typedef struct _dwg_TABLE_BreakHeight
{
  BITCODE_3BD position;
  BITCODE_BD height;
  BITCODE_BL flag;

  struct _dwg_entity_TABLE *parent;
} Dwg_TABLE_BreakHeight;

typedef struct _dwg_TABLE_BreakRow
{
  BITCODE_3BD position;
  BITCODE_BL start;
  BITCODE_BL end;

  struct _dwg_entity_TABLE *parent;
} Dwg_TABLE_BreakRow;

typedef struct _dwg_LinkedData
{
  BITCODE_TV name;        // max 16, dxf 1
  BITCODE_TV description; // max 24, dxf 300
} Dwg_LinkedData;

typedef struct _dwg_TableCellContent_Attr
{
  BITCODE_H attdef;
  BITCODE_TV value;
  BITCODE_BL index;

  struct _dwg_TableCellContent *parent;
} Dwg_TableCellContent_Attr;

// Content format 20.4.101.3
typedef struct _dwg_ContentFormat
{
  BITCODE_BL property_override_flags;
  BITCODE_BL property_flags;
  BITCODE_BL value_data_type; /* see 20.4.98 */
  BITCODE_BL value_unit_type; /* see 20.4.98 */
  BITCODE_TV value_format_string;
  BITCODE_BD rotation;
  BITCODE_BD block_scale;
  BITCODE_BL cell_alignment;
  BITCODE_CMC content_color;
  BITCODE_H text_style;
  BITCODE_BD text_height;
} Dwg_ContentFormat;

typedef struct _dwg_TableCellContent
{
  BITCODE_BL type;
  Dwg_TABLE_value value; // 20.4.99 Value
  BITCODE_H handle;
  BITCODE_BL num_attrs;
  Dwg_TableCellContent_Attr *attrs;
  BITCODE_BS has_content_format_overrides;
  Dwg_ContentFormat content_format;

  struct _dwg_TableCell *parent;
} Dwg_TableCellContent;

// 20.4.98
typedef struct _dwg_CellContentGeometry
{
  BITCODE_3BD dist_top_left;
  BITCODE_3BD dist_center;
  BITCODE_BD content_width;
  BITCODE_BD content_height;
  BITCODE_BD width;
  BITCODE_BD height;
  BITCODE_BL unknown; /* ODA bug, BD there. DXF 95 */

  struct _dwg_TableCell *cell_parent;
  struct _dwg_TABLEGEOMETRY_Cell *geom_parent;
} Dwg_CellContentGeometry;

typedef struct _dwg_TableCell
{
  BITCODE_BL flag;
  BITCODE_TV tooltip;
  BITCODE_BL customdata;
  BITCODE_BL num_customdata_items;
  Dwg_TABLE_CustomDataItem *customdata_items;
  BITCODE_BL has_linked_data;
  BITCODE_H data_link;
  BITCODE_BL num_rows;
  BITCODE_BL num_cols;
  BITCODE_BL unknown;
  BITCODE_BL num_cell_contents;
  Dwg_TableCellContent *cell_contents;
  BITCODE_BL style_id;
  BITCODE_BL has_geom_data;
  BITCODE_BL geom_data_flag;
  BITCODE_BD width_w_gap;
  BITCODE_BD height_w_gap;
  BITCODE_H tablegeometry;
  BITCODE_BL num_geometry;
  Dwg_CellContentGeometry *geometry;

  struct _dwg_CellStyle *style_parent;
  struct _dwg_TableRow *row_parent;
} Dwg_TableCell;

// almost like GridLine/TABLESTYLE_border
// in ODA named OdTableGridLine, was BorderStyle
typedef struct _dwg_GridFormat
{
  BITCODE_BL index_mask; /* 95. ie: 1,2,4,8,16,32 */
  BITCODE_BL border_overrides;
  BITCODE_BL border_type;
  BITCODE_CMC color;
  BITCODE_BLd linewt;
  BITCODE_H ltype;
  BITCODE_B visible;
  BITCODE_BD double_line_spacing;

  struct _dwg_CellStyle *parent;
} Dwg_GridFormat;

/**
  Cell style 20.4.101.4
  for TABLE, TABLECONTENT, CELLSTYLEMAP
*/
typedef struct _dwg_CellStyle
{
  BITCODE_BL type; /* 1 cell, 2 row, 3 col, 4 fmt data, 5 table */
  BITCODE_BS data_flags;
  BITCODE_BL property_override_flags;
  BITCODE_BL merge_flags;
  BITCODE_CMC bg_color;
  BITCODE_BL content_layout;
  Dwg_ContentFormat content_format;
  BITCODE_BS margin_override_flags;
  BITCODE_BD vert_margin;
  BITCODE_BD horiz_margin;
  BITCODE_BD bottom_margin;
  BITCODE_BD right_margin;
  BITCODE_BD margin_horiz_spacing;
  BITCODE_BD margin_vert_spacing;
  BITCODE_BL num_borders; /* 0-6, number of edge_flags set */
  Dwg_GridFormat *borders;

  struct _dwg_TableRow *tablerow_parent;
  struct _dwg_TableDataColumn *tabledatacolumn_parent;
} Dwg_CellStyle;

typedef struct _dwg_TableRow
{
  BITCODE_BL num_cells;
  Dwg_TableCell *cells;
  BITCODE_BL custom_data;
  BITCODE_BL num_customdata_items;
  Dwg_TABLE_CustomDataItem *customdata_items;
  Dwg_CellStyle cellstyle;
  BITCODE_BL style_id;
  BITCODE_BL height;

  struct _dwg_LinkedTableData *parent;
} Dwg_TableRow;

typedef struct _dwg_TableDataColumn
{
  BITCODE_T name;
  BITCODE_BL custom_data;
  // BITCODE_TV data;
  Dwg_CellStyle cellstyle;
  BITCODE_BL cellstyle_id;
  BITCODE_BL width;

  struct _dwg_LinkedTableData *parent;
} Dwg_TableDataColumn;

typedef struct _dwg_LinkedTableData
{
  BITCODE_BL num_cols;
  Dwg_TableDataColumn *cols;
  BITCODE_BL num_rows;
  Dwg_TableRow *rows;
  BITCODE_BL num_field_refs;
  BITCODE_H *field_refs;
} Dwg_LinkedTableData;

typedef struct _dwg_FormattedTableMerged
{
  BITCODE_BL top_row;
  BITCODE_BL left_col;
  BITCODE_BL bottom_row;
  BITCODE_BL right_col;

  struct _dwg_FormattedTableData *parent;
} Dwg_FormattedTableMerged;

typedef struct _dwg_FormattedTableData
{
  Dwg_CellStyle cellstyle;
  BITCODE_BL num_merged_cells;
  Dwg_FormattedTableMerged *merged_cells;

  struct _dwg_object_TABLECONTENT *parent;
} Dwg_FormattedTableData;

#define TABLECONTENT_fields                                                   \
  Dwg_LinkedData ldata;                                                       \
  Dwg_LinkedTableData tdata;                                                  \
  Dwg_FormattedTableData fdata;                                               \
  BITCODE_H tablestyle

typedef struct _dwg_object_TABLECONTENT
{
  struct _dwg_object_object *parent;
  TABLECONTENT_fields;
} Dwg_Object_TABLECONTENT;

typedef struct _dwg_entity_TABLE
{
  struct _dwg_object_entity *parent;
  //r2010+ TABLECONTENT:
  TABLECONTENT_fields;

  BITCODE_RC unknown_rc;
  BITCODE_H unknown_h;
  BITCODE_BL unknown_bl;
  BITCODE_B unknown_b;
  BITCODE_BL unknown_bl1;
  BITCODE_3BD insertion_pt; /*!< DXF 10 */
  BITCODE_3BD scale;        /*!< DXF 41 */
  BITCODE_BB data_flags;
  BITCODE_BD rotation;      /*!< DXF 50 */
  BITCODE_BE extrusion;    /*!< DXF 210 */
  BITCODE_B has_attribs;    /*!< DXF 66 */
  BITCODE_BL num_owned;
  BITCODE_BS flag_for_table_value; /*!< DXF 90.
                                     Bit flags, 0x06 (0x02 + 0x04): has block,
                                     0x10: table direction, 0 = up, 1 = down,
                                     0x20: title suppressed.
                                     Normally 0x06 is always set. */
  BITCODE_3BD horiz_direction; /*!< DXF 11 */
  BITCODE_BL num_cols;     /*!< DXF 90 */
  BITCODE_BL num_rows;     /*!< DXF 91 */
  unsigned long num_cells; /*!< computed */
  BITCODE_BD* col_widths;  /*!< DXF 142 */
  BITCODE_BD* row_heights; /*!< DXF 141 */
  Dwg_TABLE_Cell* cells;
  BITCODE_B has_table_overrides;
  BITCODE_BL table_flag_override; /*!< DXF 93 */
  BITCODE_B title_suppressed;     /*!< DXF 280 */
  BITCODE_B header_suppressed;    /*!< DXF 281 */
  BITCODE_BS flow_direction;      /*!< DXF 70 */
  BITCODE_BD horiz_cell_margin;   /*!< DXF 40 */
  BITCODE_BD vert_cell_margin;    /*!< DXF 41 */
  BITCODE_CMC title_row_color;    /*!< DXF 64 */
  BITCODE_CMC header_row_color;   /*!< DXF 64 */
  BITCODE_CMC data_row_color;     /*!< DXF 64 */
  BITCODE_B title_row_fill_none;  /*!< DXF 283 */
  BITCODE_B header_row_fill_none; /*!< DXF 283 */
  BITCODE_B data_row_fill_none;   /*!< DXF 283 */
  BITCODE_CMC title_row_fill_color;  /*!< DXF 63 */
  BITCODE_CMC header_row_fill_color; /*!< DXF 63 */
  BITCODE_CMC data_row_fill_color;   /*!< DXF 63 */
  BITCODE_BS title_row_alignment;   /*!< DXF 170 */
  BITCODE_BS header_row_alignment;  /*!< DXF 170 */
  BITCODE_BS data_row_alignment;    /*!< DXF 170 */
  BITCODE_H title_text_style;   /*!< DXF 7 */
  BITCODE_H header_text_style;  /*!< DXF 7 */
  BITCODE_H data_text_style;    /*!< DXF 7 */
  BITCODE_BD title_row_height;  /*!< DXF 140 */
  BITCODE_BD header_row_height; /*!< DXF 140 */
  BITCODE_BD data_row_height;   /*!< DXF 140 */

  BITCODE_B has_border_color_overrides;   /*!< if DXF 94 > 0 */
  BITCODE_BL border_color_overrides_flag; /*!< DXF 94 */
  BITCODE_CMC title_horiz_top_color;      /*!< DXF 64 if DXF 94 & 0x1 */
  BITCODE_CMC title_horiz_ins_color;      /*!< DXF 65 if DXF 94 & 0x2 */
  BITCODE_CMC title_horiz_bottom_color;   /*!< DXF 66 if DXF 94 & 0x4 */
  BITCODE_CMC title_vert_left_color;      /*!< DXF 63 if DXF 94 & 0x8 */
  BITCODE_CMC title_vert_ins_color;       /*!< DXF 68 if DXF 94 & 0x10 */
  BITCODE_CMC title_vert_right_color;     /*!< DXF 69 if DXF 94 & 0x20 */
  BITCODE_CMC header_horiz_top_color;     /*!< DXF 64 if DXF 94 & 0x40 */
  BITCODE_CMC header_horiz_ins_color;     /*!< DXF 65 */
  BITCODE_CMC header_horiz_bottom_color;  /*!< DXF 66 */
  BITCODE_CMC header_vert_left_color;     /*!< DXF 63 */
  BITCODE_CMC header_vert_ins_color;      /*!< DXF 68 */
  BITCODE_CMC header_vert_right_color;    /*!< DXF 69 */
  BITCODE_CMC data_horiz_top_color;       /*!< DXF 64 */
  BITCODE_CMC data_horiz_ins_color;       /*!< DXF 65 */
  BITCODE_CMC data_horiz_bottom_color;    /*!< DXF 66 */
  BITCODE_CMC data_vert_left_color;       /*!< DXF 63 */
  BITCODE_CMC data_vert_ins_color;        /*!< DXF 68 */
  BITCODE_CMC data_vert_right_color;      /*!< DXF 69 */

  BITCODE_B has_border_lineweight_overrides;   /*!< if DXF 95 > 0 */
  BITCODE_BL border_lineweight_overrides_flag; /*!< DXF 95 */
  BITCODE_BS title_horiz_top_linewt;
  BITCODE_BS title_horiz_ins_linewt;
  BITCODE_BS title_horiz_bottom_linewt;
  BITCODE_BS title_vert_left_linewt;
  BITCODE_BS title_vert_ins_linewt;
  BITCODE_BS title_vert_right_linewt;
  BITCODE_BS header_horiz_top_linewt;
  BITCODE_BS header_horiz_ins_linewt;
  BITCODE_BS header_horiz_bottom_linewt;
  BITCODE_BS header_vert_left_linewt;
  BITCODE_BS header_vert_ins_linewt;
  BITCODE_BS header_vert_right_linewt;
  BITCODE_BS data_horiz_top_linewt;
  BITCODE_BS data_horiz_ins_linewt;
  BITCODE_BS data_horiz_bottom_linewt;
  BITCODE_BS data_vert_left_linewt;
  BITCODE_BS data_vert_ins_linewt;
  BITCODE_BS data_vert_right_linewt;

  BITCODE_B has_border_visibility_overrides;
  BITCODE_BL border_visibility_overrides_flag; /*!< DXF 96 */
  BITCODE_BS title_horiz_top_visibility;
  BITCODE_BS title_horiz_ins_visibility;
  BITCODE_BS title_horiz_bottom_visibility;
  BITCODE_BS title_vert_left_visibility;
  BITCODE_BS title_vert_ins_visibility;
  BITCODE_BS title_vert_right_visibility;
  BITCODE_BS header_horiz_top_visibility;
  BITCODE_BS header_horiz_ins_visibility;
  BITCODE_BS header_horiz_bottom_visibility;
  BITCODE_BS header_vert_left_visibility;
  BITCODE_BS header_vert_ins_visibility;
  BITCODE_BS header_vert_right_visibility;
  BITCODE_BS data_horiz_top_visibility;
  BITCODE_BS data_horiz_ins_visibility;
  BITCODE_BS data_horiz_bottom_visibility;
  BITCODE_BS data_vert_left_visibility;
  BITCODE_BS data_vert_ins_visibility;
  BITCODE_BS data_vert_right_visibility;

  BITCODE_H block_header;
  BITCODE_H first_attrib;
  BITCODE_H last_attrib;
  BITCODE_H* attrib_handles;
  BITCODE_H seqend;
  BITCODE_H title_row_style_override;
  BITCODE_H header_row_style_override;
  BITCODE_H data_row_style_override;

  BITCODE_BS unknown_bs;
  BITCODE_3BD hor_dir;
  BITCODE_BL has_break_data;
  BITCODE_BL break_flag;
  BITCODE_BL break_flow_direction;
  BITCODE_BD break_spacing;
  BITCODE_BL break_unknown1;
  BITCODE_BL break_unknown2;
  BITCODE_BL num_break_heights;
  Dwg_TABLE_BreakHeight *break_heights;
  BITCODE_BL num_break_rows;
  Dwg_TABLE_BreakRow *break_rows;

} Dwg_Entity_TABLE;

#undef TABLECONTENT_fields

/**
 Class TABLESTYLE (varies)
 */

typedef struct _dwg_TABLESTYLE_CellStyle
{
  struct _dwg_object_TABLESTYLE *parent;
  BITCODE_BL id;   /* 1=title, 2=header, 3=data, 4=table.
                      ref TABLESTYLE. custom IDs > 100 */
  BITCODE_BL type; /* 1=data, 2=label */
  BITCODE_T  name;
  struct _dwg_CellStyle cellstyle;
} Dwg_TABLESTYLE_CellStyle;

// very similar to GridLine, or GridFormat. but no overrides, type, ltype, ...
typedef struct _dwg_TABLESTYLE_border
{
  BITCODE_BSd linewt;
  BITCODE_B visible;
  BITCODE_CMC color;
  //TODO
  // BITCODE_H ltype;
  // BITCODE_BD double_line_spacing;
} Dwg_TABLESTYLE_border; // child of TABLE/TABLESTYLE/...

typedef struct _dwg_TABLESTYLE_rowstyles
{
  struct _dwg_object_TABLESTYLE *parent;
  BITCODE_H text_style;
  BITCODE_BD text_height;
  BITCODE_BS text_alignment;
  BITCODE_CMC text_color;
  BITCODE_CMC fill_color;
  BITCODE_B has_bgcolor;

  // 6: top, horizontal inside, bottom, left, vertical inside, right
  BITCODE_BL num_borders; // always 6
  Dwg_TABLESTYLE_border *borders;

  BITCODE_BL data_type;  // r2007+
  BITCODE_BL unit_type;
  BITCODE_TU format_string;
} Dwg_TABLESTYLE_rowstyles;

typedef struct _dwg_object_TABLESTYLE
{
  struct _dwg_object_object *parent;

  BITCODE_BS class_version;
  BITCODE_T name;
  BITCODE_BS flags;
  BITCODE_BS flow_direction;
  BITCODE_BD horiz_cell_margin;
  BITCODE_BD vert_cell_margin;
  BITCODE_B is_title_suppressed;
  BITCODE_B is_header_suppressed;
  BITCODE_RC unknown_rc;         //r2007+ signed
  BITCODE_BL unknown_bl1;
  BITCODE_BL unknown_bl2;
  BITCODE_H cellstyle;           //r2007+. was called template
  Dwg_TABLESTYLE_CellStyle sty;  //r2007+. Note: embedded struct
  BITCODE_BL numoverrides;      // ??
  BITCODE_BL unknown_bl3;
  Dwg_TABLESTYLE_CellStyle ovr;  // ??

  // 0: data, 1: title, 2: header
  BITCODE_BL num_rowstyles; // always 3
  Dwg_TABLESTYLE_rowstyles *rowstyles;
} Dwg_Object_TABLESTYLE;

/**
 Class CELLSTYLEMAP (varies)
 R2008+ TABLESTYLE extension class
 */
typedef struct _dwg_object_CELLSTYLEMAP
{
  struct _dwg_object_object *parent;
  BITCODE_BL num_cells;
  Dwg_TABLESTYLE_CellStyle *cells;
} Dwg_Object_CELLSTYLEMAP;

/* 20.4.103 TABLEGEOMETRY
 r2008+ optional, == 20.4.98
 */

typedef struct _dwg_TABLEGEOMETRY_Cell
{
  struct _dwg_object_TABLEGEOMETRY *parent;
  BITCODE_BL geom_data_flag;
  BITCODE_BD width_w_gap;
  BITCODE_BD height_w_gap;
  BITCODE_H tablegeometry;
  BITCODE_BL num_geometry;
  Dwg_CellContentGeometry *geometry;
} Dwg_TABLEGEOMETRY_Cell;

typedef struct _dwg_object_TABLEGEOMETRY
{
  struct _dwg_object_object *parent;
  BITCODE_BL num_rows;
  BITCODE_BL num_cols;
  BITCODE_BL num_cells; /* = num_rows * num_cols */
  Dwg_TABLEGEOMETRY_Cell *cells;
} Dwg_Object_TABLEGEOMETRY;


/**
 Class UNDERLAYDEFINITION (varies)
 in DXF as {PDF,DGN,DWF}DEFINITION
 */
typedef struct _dwg_object_UNDERLAYDEFINITION
{
  struct _dwg_object_object *parent;

  BITCODE_TV filename; /*!< DXF 1, relative or absolute path to the image file */
  BITCODE_TV name;     /*!< DXF 2, pdf: page number, dgn: default, dwf: ? */
} Dwg_Object_UNDERLAYDEFINITION;

typedef struct _dwg_object_UNDERLAYDEFINITION Dwg_Object_PDFDEFINITION;
typedef struct _dwg_object_UNDERLAYDEFINITION Dwg_Object_DGNDEFINITION;
typedef struct _dwg_object_UNDERLAYDEFINITION Dwg_Object_DWFDEFINITION;

/**
 Entity UNDERLAY, the reference (varies)
 As IMAGE but snappable.
 in DXF as{PDF,DGN,DWF}UNDERLAY
 */
typedef struct _dwg_entity_UNDERLAY
{
  struct _dwg_object_entity *parent;

  BITCODE_BE extrusion; /*!< DXF 210 normal */
  BITCODE_3BD insertion_pt; /*!< DXF 10 */
  BITCODE_3BD scale;   /*!< DXF 41 */
  BITCODE_BD angle;    /*!< DXF 50 */
  BITCODE_RC flag;     /*!< DXF 280: 1 is_clipped, 2 is_on, 4 is_monochrome,
                            8 is_adjusted_for_background, 16 is_clip_inverted,
                            ? is_frame_visible, ? is_frame_plottable */
  BITCODE_RC contrast; /*!< DXF 281 20-100, def: 100 */
  BITCODE_RC fade;     /*!< DXF 282 0-80, def: 0*/
  BITCODE_BL num_clip_verts;
  BITCODE_2RD *clip_verts; /*!< DXF 11: if 2 rectangle, > polygon */

  BITCODE_H underlay_layer;
  BITCODE_H definition_id; /*!< DXF 340 */

} Dwg_Entity_UNDERLAY;

typedef struct _dwg_entity_UNDERLAY Dwg_Entity_PDFUNDERLAY;
typedef struct _dwg_entity_UNDERLAY Dwg_Entity_DGNUNDERLAY;
typedef struct _dwg_entity_UNDERLAY Dwg_Entity_DWFUNDERLAY;

/**
 Class DBCOLOR (varies)
 */
typedef struct _dwg_object_DBCOLOR
{
  struct _dwg_object_object *parent;
  BITCODE_CMC color;   //62,420,430
} Dwg_Object_DBCOLOR;

/**
 Class FIELDLIST AcDbField (varies)
 R2018+
 */
typedef struct _dwg_FIELD_ChildValue
{
  struct _dwg_object_FIELD *parent;
  BITCODE_TV key;   /*!< DXF 6 */
  Dwg_TABLE_value value;
} Dwg_FIELD_ChildValue;

typedef struct _dwg_object_FIELD
{
  struct _dwg_object_object *parent;
                    /* dxf group code */
  BITCODE_TV id;           /* 1 */
  BITCODE_TV code;         /* 2,3 */
  BITCODE_BL num_childs;   /* 90 */
  BITCODE_H *childs;       /* code:3, 360 */
  BITCODE_BL num_objects;  /* 97 */
  BITCODE_H *objects;      /* code:5, 331 */
  BITCODE_TV format;       /* 4, until r2004 only */
  BITCODE_BL evaluation_option; /* 91 */
  BITCODE_BL filing_option;     /* 92 */
  BITCODE_BL field_state;       /* 94 */
  BITCODE_BL evaluation_status; /* 95 */
  BITCODE_BL evaluation_error_code; /* 96 */
  BITCODE_TV evaluation_error_msg;  /* 300 */
  Dwg_TABLE_value value;
  BITCODE_TV value_string;        /* 301,9 */
  BITCODE_BL value_string_length; /* 98 ODA bug: TV */
  BITCODE_BL num_childval;      /* 93 */
  Dwg_FIELD_ChildValue *childval;
} Dwg_Object_FIELD;

/**
 * Object FIELDLIST (varies)
 */
typedef struct _dwg_object_FIELDLIST
{
  struct _dwg_object_object *parent;

  BITCODE_BL num_fields;
  BITCODE_B unknown;
  BITCODE_H *fields;
} Dwg_Object_FIELDLIST;

/**
 Class GEODATA (varies)
 R2009+
 */
typedef struct _dwg_GEODATA_meshpt
{
  BITCODE_2RD source_pt;
  BITCODE_2RD dest_pt;
} Dwg_GEODATA_meshpt;

typedef struct _dwg_GEODATA_meshface
{
  BITCODE_BL face1;
  BITCODE_BL face2;
  BITCODE_BL face3;
} Dwg_GEODATA_meshface;

typedef struct _dwg_object_GEODATA
{                   /* dxf group code */
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;
  BITCODE_H host_block;
  BITCODE_BS coord_type; /* 0 unknown, 1 local grid, 2 projected grid,
                            3 geographic defined by latitude/longitude) */
  BITCODE_3BD design_pt;
  BITCODE_3BD ref_pt;
  BITCODE_3BD obs_pt;
  BITCODE_3BD scale_vec; // always 1.0,1.0,1.0
  BITCODE_BD unit_scale_horiz;
  BITCODE_BL units_value_horiz; // enum 0-20
  BITCODE_BD unit_scale_vert;
  BITCODE_BL units_value_vert; // enum 0-20
  BITCODE_3BD up_dir;
  BITCODE_3BD north_dir;
  BITCODE_BL scale_est; /* None = 1, User specified scale factor = 2,
                           Grid scale at reference point = 3, Prismodial = 4 */
  BITCODE_BD user_scale_factor;
  BITCODE_B do_sea_level_corr;
  BITCODE_BD sea_level_elev;
  BITCODE_BD coord_proj_radius;
  BITCODE_T coord_system_def;
  BITCODE_T geo_rss_tag;
  BITCODE_T coord_system_datum; /* obsolete */
  BITCODE_T coord_system_wkt; /* obsolete */

  BITCODE_T observation_from_tag;
  BITCODE_T observation_to_tag;
  BITCODE_T observation_coverage_tag;
  BITCODE_BL num_geomesh_pts;
  Dwg_GEODATA_meshpt *geomesh_pts;
  BITCODE_BL num_geomesh_faces;
  Dwg_GEODATA_meshface *geomesh_faces;

  BITCODE_B has_civil_data;
  BITCODE_B obsolete_false;
  BITCODE_2RD ref_pt2d; // (y, x) of ref_pt reversed
  BITCODE_3BD zero1, zero2;
  BITCODE_BL unknown1;
  BITCODE_BL unknown2;
  BITCODE_B unknown_b;
  BITCODE_BD north_dir_angle_deg;
  BITCODE_BD north_dir_angle_rad;
} Dwg_Object_GEODATA;

/**
 Class IDBUFFER (varies)
 */
typedef struct _dwg_object_IDBUFFER
{
  struct _dwg_object_object *parent;

  BITCODE_RC unknown;
  BITCODE_BL num_obj_ids;
  BITCODE_H* obj_ids;
} Dwg_Object_IDBUFFER;

/**
 Classes for IMAGE (varies)
 */

typedef struct _dwg_entity_IMAGE
{
  struct _dwg_object_entity *parent;

  BITCODE_BL class_version;
  BITCODE_3BD pt0;
  BITCODE_3BD uvec;
  BITCODE_3BD vvec;
  BITCODE_2RD size; /*!< DXF 13/23; width, height in pixel */
  BITCODE_BS display_props;
  BITCODE_B clipping;
  BITCODE_RC brightness;
  BITCODE_RC contrast;
  BITCODE_RC fade;
  BITCODE_B clip_mode;
  BITCODE_BS clip_boundary_type;
  BITCODE_BL num_clip_verts;
  BITCODE_2RD* clip_verts;
  BITCODE_H imagedef;
  BITCODE_H imagedefreactor;
} Dwg_Entity_IMAGE;

/**
 Class IMAGEDEF (varies)
 */
typedef struct _dwg_object_IMAGEDEF
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;
  BITCODE_2RD image_size;
  BITCODE_TV file_path;
  BITCODE_B is_loaded;
  BITCODE_RC resunits;
  BITCODE_2RD pixel_size;
  //BITCODE_H xrefctrl;    /*!< r2010+ */
} Dwg_Object_IMAGEDEF;

/**
 Class IMAGEDEF_REACTOR (varies)
 */
typedef struct _dwg_object_IMAGEDEF_REACTOR
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;
} Dwg_Object_IMAGEDEF_REACTOR;

/**
 Class LAYER_INDEX (varies)
 */
typedef struct _dwg_LAYER_entry
{
  struct _dwg_object_LAYER_INDEX *parent;
  BITCODE_BL numlayers;
  BITCODE_T name;
  BITCODE_H handle;
} Dwg_LAYER_entry;

typedef struct _dwg_object_LAYER_INDEX
{
  struct _dwg_object_object *parent;
  BITCODE_TIMEBLL last_updated;
  BITCODE_BL num_entries;
  Dwg_LAYER_entry* entries;
} Dwg_Object_LAYER_INDEX;

/**
 Class LWPOLYLINE (77 + varies)
 */
typedef struct _dwg_entity_LWPOLYLINE
{
  struct _dwg_object_entity *parent;

  BITCODE_BS flag;              /*!< DXF 70 */
  BITCODE_BD const_width;       /*!< DXF 43 */
  BITCODE_BD elevation;         /*!< DXF 38 */
  BITCODE_BD thickness;         /*!< DXF 39 */
  BITCODE_BE extrusion;        /*!< DXF 210 */
  BITCODE_BL num_points;        /*!< DXF 90 */
  BITCODE_2RD* points;          /*!< DXF 10,20 */
  BITCODE_BL num_bulges;
  BITCODE_BD* bulges;           /*!< DXF 42 */
  BITCODE_BL num_vertexids;     /*!< r2010+, same as num_points */
  BITCODE_BL* vertexids;        /*!< r2010+ DXF 91 */
  BITCODE_BL num_widths;
  Dwg_LWPOLYLINE_width* widths; /*!< DXF 40,41 */
} Dwg_Entity_LWPOLYLINE;

/**
 Class RASTERVARIABLES (varies)
 (used in conjunction with IMAGE entities)
 */
typedef struct _dwg_object_RASTERVARIABLES
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;
  BITCODE_BS display_frame;
  BITCODE_BS display_quality;
  BITCODE_BS units;
} Dwg_Object_RASTERVARIABLES;

/**
 Object SCALE (varies)
 */
typedef struct _dwg_object_SCALE
{
  struct _dwg_object_object *parent;

  BITCODE_BS flag; /* 1: is_temporary */
  BITCODE_TV name;
  BITCODE_BD paper_units;
  BITCODE_BD drawing_units;
  BITCODE_B is_unit_scale;
} Dwg_Object_SCALE;

/**
 Class SORTENTSTABLE (varies)
 */
typedef struct _dwg_object_SORTENTSTABLE
{
  struct _dwg_object_object *parent;

  BITCODE_BL num_ents;
  BITCODE_H* sort_ents;
  BITCODE_H block_owner; // mspace or pspace
  BITCODE_H* ents;
} Dwg_Object_SORTENTSTABLE;

/**
 Class SPATIAL_FILTER (varies)
 */
typedef struct _dwg_object_SPATIAL_FILTER
{
  struct _dwg_object_object *parent;

  BITCODE_BS num_clip_verts;
  BITCODE_2RD* clip_verts;
  BITCODE_BE extrusion;
  BITCODE_3BD origin;
  BITCODE_BS display_boundary_on;
  BITCODE_BS front_clip_on;
  BITCODE_BD front_clip_z;
  BITCODE_BS back_clip_on;
  BITCODE_BD back_clip_z;
  BITCODE_BD* inverse_transform;
  BITCODE_BD* transform;
} Dwg_Object_SPATIAL_FILTER;

/**
 Class SPATIAL_INDEX (varies)
 ODA only covers the AcDbFilter class, but misses the rest.
 */
typedef struct _dwg_object_SPATIAL_INDEX
{
  struct _dwg_object_object *parent;

  BITCODE_TIMEBLL last_updated;
  BITCODE_BD num1, num2, num3, num4, num5, num6;
  BITCODE_BL num_hdls;
  BITCODE_H *hdls;
  BITCODE_BL bindata_size;
  BITCODE_TF bindata;
} Dwg_Object_SPATIAL_INDEX;

/**
 WIPEOUT (varies, 504)
 R2000+, undocumented = IMAGE layover
 */
typedef struct _dwg_entity_WIPEOUT
{
  struct _dwg_object_entity *parent;

  BITCODE_BL class_version;
  BITCODE_3BD pt0;
  BITCODE_3BD uvec;
  BITCODE_3BD vvec;
  BITCODE_2RD size;
  BITCODE_BS display_props;
  BITCODE_B clipping;
  BITCODE_RC brightness;
  BITCODE_RC contrast;
  BITCODE_RC fade;
  BITCODE_B clip_mode;
  BITCODE_BS clip_boundary_type;
  BITCODE_BL num_clip_verts;
  BITCODE_2RD* clip_verts;
  BITCODE_H imagedef;
  BITCODE_H imagedefreactor;
} Dwg_Entity_WIPEOUT;

/**
 Class WIPEOUTVARIABLES (varies, 505)
 R2000+, Object bitsize: 96
 */
typedef struct _dwg_object_WIPEOUTVARIABLES
{
  struct _dwg_object_object *parent;
  //BITCODE_BL class_version;  /*!< DXF 90 NY */
  BITCODE_BS display_frame;    /*!< DXF 70  */
} Dwg_Object_WIPEOUTVARIABLES;

/* SECTIONPLANE, r2007+
 * Looks like the livesection ptr from VIEW
 */
typedef struct _dwg_entity_SECTIONOBJECT
{
  struct _dwg_object_entity *parent;
  BITCODE_BL state;		/*!< DXF 90. Plane=1, Boundary=2, Volume=4 */
  BITCODE_BL flags;		/*!< DXF 91. hitflags: sectionline=1, sectionlinetop=2, sectionlinebottom=4,
                                  backline=8, backlinetop=16, backlinebottom=32, verticallinetop=64,
                                  verticallinebottom=128.
                                  heightflags: HeightAboveSectionLine=1, HeightBelowSectionLine=2
                                 */
  BITCODE_T name;		/*!< DXF 1 */
  //BITCODE_3BD viewing_dir;	/*!< normal of the 1st segment plane */
  BITCODE_3BD vert_dir;	        /*!< DXF 10. normal to the segment line, on the plane */
  BITCODE_BD top_height;	/*!< DXF 40 */
  BITCODE_BD bottom_height;	/*!< DXF 41 */
  BITCODE_BS indicator_alpha;	/*!< DXF 70 */
  BITCODE_CMC indicator_color;	/*!< DXF 62/420 (but documented as 63/411) */
  BITCODE_BL num_verts;		/*!< DXF 92 */
  BITCODE_3BD *verts;		/*!< DXF 11 */
  BITCODE_BL num_blverts;	/*!< DXF 93 */
  BITCODE_3BD *blverts;		/*!< DXF 12 */
  BITCODE_H section_settings;	/*!< DXF 360 */

} Dwg_Entity_SECTIONOBJECT;

/**
 Unstable
 Class VISUALSTYLE (varies)
 R2007+

 32 types, with 3 categories: Face, Edge, Display, plus 58 props r2013+
 */
typedef struct _dwg_object_VISUALSTYLE
{
  struct _dwg_object_object *parent;
  BITCODE_T description;          /*!< DXF 2  */
  BITCODE_BL style_type;          /*!< DXF 70 enum 0-32: (kFlat-kEmptyStyle acgivisualstyle.h) */
  BITCODE_BS ext_lighting_model;  /*!< DXF 177, r2010+ ? required on has_xdata */
  BITCODE_B internal_only;        /*!< DXF 291, has internal_use_only flags */
  BITCODE_BL face_lighting_model; /*!< DXF 71 0:Invisible 1:Visible 2:Phong 3:Gooch */
  BITCODE_BS face_lighting_model_int;   /*!< DXF 176 r2010+ */
  BITCODE_BL face_lighting_quality;     /*!< DXF 72 0:No lighting 1:Per face 2:Per vertex */
  BITCODE_BS face_lighting_quality_int; /*!< DXF 176 r2010+ */
  BITCODE_BL face_color_mode;   /*!< DXF 73 0 = No color
                                            1 = Object color
                                            2 = Background color
                                            3 = Custom color
                                            4 = Mono color
                                            5 = Tinted
                                            6 = Desaturated */
  BITCODE_BS face_color_mode_int; /*!< DXF 176 r2010+ */
  BITCODE_BD face_opacity;      /*!< DXF 40  */
  BITCODE_BS face_opacity_int;  /*!< DXF 176 r2010+ */
  BITCODE_BD face_specular;     /*!< DXF 41  */
  BITCODE_BS face_specular_int; /*!< DXF 176 r2010+ */
  BITCODE_BL face_modifier;     /*!< DXF 90 0:No modifiers 1:Opacity 2:Specular */
  BITCODE_BS face_modifier_int; /*!< DXF 176 r2010+ */
  BITCODE_CMC face_mono_color;  /*!< DXF 63 + 421 */
  BITCODE_BS face_mono_color_int; /*!< DXF 176 r2010+ */
  BITCODE_BS edge_model;        /*!< DXF 74 0:No edges 1:Isolines 2:Facet edges */
  BITCODE_BS edge_model_int;    /*!< DXF 176 r2010+ */
  BITCODE_BL edge_style;        /*!< DXF 91  */
  BITCODE_BS edge_style_int;    /*!< DXF 176 r2010+ */
  BITCODE_CMC edge_intersection_color;  /*!< DXF 64  */
  BITCODE_BS edge_intersection_color_int; /*!< DXF 176 r2010+ */
  BITCODE_CMC edge_obscured_color;      /*!< DXF 65  */
  BITCODE_BS edge_obscured_color_int;   /*!< DXF 176 r2010+ */
  BITCODE_BL edge_obscured_ltype;      /*!< DXF 75   */
  BITCODE_BS edge_obscured_ltype_int;  /*!< DXF 176 r2010+ */
  BITCODE_BL edge_intersection_ltype;  /*!< DXF 175  */
  BITCODE_BS edge_intersection_ltype_int; /*!< DXF 176 r2010+ */
  BITCODE_BD edge_crease_angle;         /*!< DXF 42  */
  BITCODE_BS edge_crease_angle_int;     /*!< DXF 176 r2010+ */
  BITCODE_BL edge_modifier;             /*!< DXF 92  */
  BITCODE_BS edge_modifier_int;         /*!< DXF 176 r2010+ */
  BITCODE_CMC edge_color;               /*!< DXF 66  */
  BITCODE_BS edge_color_int;            /*!< DXF 176 r2010+ */
  BITCODE_BD edge_opacity;              /*!< DXF 43  */
  BITCODE_BS edge_opacity_int;          /*!< DXF 176 r2010+ */
  BITCODE_BL edge_width;                /*!< DXF 76  */
  BITCODE_BS edge_width_int;            /*!< DXF 176 r2010+ */
  BITCODE_BL edge_overhang;             /*!< DXF 77  */
  BITCODE_BS edge_overhang_int;         /*!< DXF 176 r2010+ */
  BITCODE_BL edge_jitter;               /*!< DXF 78  */
  BITCODE_BS edge_jitter_int;           /*!< DXF 176 r2010+ */
  BITCODE_CMC edge_silhouette_color;    /*!< DXF 67  */
  BITCODE_BS edge_silhouette_color_int; /*!< DXF 176 r2010+ */
  BITCODE_BL edge_silhouette_width;     /*!< DXF 79  */
  BITCODE_BS edge_silhouette_width_int; /*!< DXF 176 r2010+ */
  BITCODE_BL edge_halo_gap;             /*!< DXF 170  */
  BITCODE_BS edge_halo_gap_int;         /*!< DXF 176 r2010+ */
  BITCODE_BL edge_isolines;             /*!< DXF 171  */
  BITCODE_BS edge_isolines_int;         /*!< DXF 176 r2010+ */
  BITCODE_B  edge_do_hide_precision;    /*!< DXF 290  */
  BITCODE_BS edge_do_hide_precision_int;/*!< DXF 176 r2010+ */
  BITCODE_BL edge_style_apply;     	/*!< DXF 174  */
  BITCODE_BS edge_style_apply_int; 	/*!< DXF 176 r2010+  */
  BITCODE_BL display_settings;          /*!< DXF 93 flags  */
  BITCODE_BS display_settings_int;      /*!< DXF 176 r2010+ */
  BITCODE_BLd display_brightness_bl;    /*!< DXF 44 <=r2007 */
  BITCODE_BD display_brightness;        /*!< DXF 44  r2010+ */
  BITCODE_BS display_brightness_int;    /*!< DXF 176 r2010+ */
  BITCODE_BL display_shadow_type;       /*!< DXF 173  */
  BITCODE_BS display_shadow_type_int;   /*!< DXF 176 r2010+ */
  BITCODE_BD bd2007_45;                 /*!< DXF 45 r2007-only 0.0 */

  BITCODE_BS num_props; 		/*!< r2013+ version3 58x */
  /* the rest of the props:
     all bool are 290, all BS/BL are 90, all BD are 40, colors 62, text 1 */
  BITCODE_B b_prop1c;   BITCODE_BS b_prop1c_int;
  BITCODE_B b_prop1d;   BITCODE_BS b_prop1d_int;
  BITCODE_B b_prop1e;   BITCODE_BS b_prop1e_int;
  BITCODE_B b_prop1f;   BITCODE_BS b_prop1f_int;
  BITCODE_B b_prop20;   BITCODE_BS b_prop20_int;
  BITCODE_B b_prop21;   BITCODE_BS b_prop21_int;
  BITCODE_B b_prop22;   BITCODE_BS b_prop22_int;
  BITCODE_B b_prop23;   BITCODE_BS b_prop23_int;
  BITCODE_B b_prop24;   BITCODE_BS b_prop24_int;
  BITCODE_BL bl_prop25; BITCODE_BS bl_prop25_int;
  BITCODE_BD bd_prop26; BITCODE_BS bd_prop26_int;
  BITCODE_BD bd_prop27; BITCODE_BS bd_prop27_int;
  BITCODE_BL bl_prop28; BITCODE_BS bl_prop28_int;
  BITCODE_CMC c_prop29; BITCODE_BS c_prop29_int;
  BITCODE_BL bl_prop2a; BITCODE_BS bl_prop2a_int;
  BITCODE_BL bl_prop2b; BITCODE_BS bl_prop2b_int;
  BITCODE_CMC c_prop2c; BITCODE_BS c_prop2c_int;
  BITCODE_B b_prop2d;   BITCODE_BS b_prop2d_int;
  BITCODE_BL bl_prop2e; BITCODE_BS bl_prop2e_int;
  BITCODE_BL bl_prop2f; BITCODE_BS bl_prop2f_int;
  BITCODE_BL bl_prop30; BITCODE_BS bl_prop30_int;
  BITCODE_B b_prop31;   BITCODE_BS b_prop31_int;
  BITCODE_BL bl_prop32; BITCODE_BS bl_prop32_int;
  BITCODE_CMC c_prop33; BITCODE_BS c_prop33_int;
  BITCODE_BD bd_prop34; BITCODE_BS bd_prop34_int;
  BITCODE_BL edge_wiggle;BITCODE_BS edge_wiggle_int;
  BITCODE_T strokes;    BITCODE_BS strokes_int;
  BITCODE_B b_prop37;   BITCODE_BS b_prop37_int;
  BITCODE_BD bd_prop38; BITCODE_BS bd_prop38_int;
  BITCODE_BD bd_prop39; BITCODE_BS bd_prop39_int;

} Dwg_Object_VISUALSTYLE;

/**
 Object LIGHTLIST (varies)
 R2010+
 */

typedef struct _dwg_LIGHTLIST_light
{
  struct _dwg_object_LIGHTLIST *parent;
  BITCODE_T name;
  BITCODE_H handle;
} Dwg_LIGHTLIST_light;

/* 2010+ */
typedef struct _dwg_object_LIGHTLIST
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version;
  BITCODE_BL num_lights;
  Dwg_LIGHTLIST_light *lights;
} Dwg_Object_LIGHTLIST;


typedef struct _dwg_MATERIAL_color
{
  struct _dwg_object_object *parent;
  BITCODE_RC flag;    /*!< 0 Use current color, 1 Override */
  BITCODE_BD factor;  /*!< 0.0 - 1.0 */
  BITCODE_BL rgb;
} Dwg_MATERIAL_color;

typedef struct _dwg_MATERIAL_mapper
{
  struct _dwg_object_object *parent;
  BITCODE_BD blendfactor;   /*!< DXF 42  def: 1.0 */
  BITCODE_RC source;        /*!< DXF 72  0 current, 1 image file (def), 2 2nd map? */
  BITCODE_T filename;       /*!< DXF 3   if NULL no diffuse map */
  BITCODE_RC projection;    /*!< DXF 73  1 Planar (def), 2 Box, 3 Cylinder, 4 Sphere */
  BITCODE_RC tiling;        /*!< DXF 74  1 = Tile (def), 2 = Crop, 3 = Clamp */
  BITCODE_RC autotransform; /*!< DXF 75  1 no, 2: scale to curr ent,
                                         4: w/ current block transform */
  BITCODE_BD* transmatrix;  /*!< DXF 43: 16x BD */
  /* marble, wood and procedural modes */
  BITCODE_BS texturemode;
  Dwg_MATERIAL_color color1;
  Dwg_MATERIAL_color color2;
} Dwg_MATERIAL_mapper;

typedef struct _dwg_MATERIAL_gentexture
{
  struct _dwg_object_MATERIAL *parent;
  BITCODE_T genprocname;
  struct _dwg_object_MATERIAL *material;
} Dwg_MATERIAL_gentexture;

/**
 Object MATERIAL (varies)
 Acad Naming: e.g. Materials/assetlibrary_base.fbm/shaders/AdskShaders.mi
                  Materials/assetlibrary_base.fbm/Mats/SolidGlass/Generic.xml
 */
typedef struct _dwg_object_MATERIAL
{
  struct _dwg_object_object *parent;

  BITCODE_T name; 			/*!< DXF 1 */
  BITCODE_T description; 		/*!< DXF 2 optional */

  Dwg_MATERIAL_color ambient_color;    /*!< DXF 70, 40, 90 */
  Dwg_MATERIAL_color diffuse_color;    /*!< DXF 71, 41, 91 */
  Dwg_MATERIAL_mapper diffusemap;      /*!< DXF 42, 72, 3, 73, 74, 75, 43 */

  BITCODE_BD specular_gloss_factor;    /*!< DXF 44 def: 0.5 */
  Dwg_MATERIAL_color specular_color;   /*!< DXF 76, 45, 92 */
  Dwg_MATERIAL_mapper specularmap;     /*!< DXF 46, 77, 4, 78, 79, 170, 47 */

  //?? BD reflection_depth
  //reflection_glossy_samples
  Dwg_MATERIAL_mapper reflectionmap;   /*!< DXF 48, 171, 6, 172, 173, 174, 49 */

  BITCODE_BD opacity_percent;          /*!< DXF 140 def: 1.0 */
  Dwg_MATERIAL_mapper opacitymap;      /*!< DXF 141, 175, 7, 176, 177, 178, 142 */

  //BITCODE_B bump_enable
  //?BD bump_amount
  Dwg_MATERIAL_mapper bumpmap;         /*!< DXF 143, 179, 8, 270, 271, 272, 144 */

  BITCODE_BD refraction_index;         /*!< DXF 145 def: 1.0 */
  //?? BD refraction_depth
  //?? BD refraction_translucency_weight
  //?? refraction_glossy_samples
  Dwg_MATERIAL_mapper refractionmap;   /*!< DXF 146, 273, 9, 274, 275, 276, 147 */

  BITCODE_BD color_bleed_scale;    /*!< DXF 460 */
  BITCODE_BD indirect_bump_scale;  /*!< DXF 461 */
  BITCODE_BD reflectance_scale;    /*!< DXF 462 */
  BITCODE_BD transmittance_scale;  /*!< DXF 463 */
  BITCODE_B two_sided_material;    /*!< DXF 290 */
  BITCODE_BD luminance;            /*!< DXF 464 */
  BITCODE_BS luminance_mode;       /*!< DXF 270 */
  BITCODE_BD translucence;         /*!< DXF 148 */
  BITCODE_BD self_illumination;    /*!< DXF 149 */
  BITCODE_BD reflectivity;         /*!< DXF 468 */
  BITCODE_BL illumination_model;   /*!< DXF 93 */
  BITCODE_BL channel_flags;        /*!< DXF 94 */
  BITCODE_BL mode;                 /*!< DXF 282 */

  BITCODE_T genprocname;           /*!< DXF 300 */
  BITCODE_BS genproctype;
  BITCODE_B genprocvalbool;        /*!< DXF 291 */
  BITCODE_BS genprocvalint;        /*!< DXF 271 */
  BITCODE_BD genprocvalreal;       /*!< DXF 469 */
  BITCODE_T genprocvaltext;        /*!< DXF 301 */
  BITCODE_CMC genprocvalcolor;     /*!< DXF 62 */
  BITCODE_B genproctableend;       /*!< DXF 292 */
  BITCODE_BS num_gentextures;
  Dwg_MATERIAL_gentexture* gentextures;

#if 0
  BITCODE_BS normalmap_method;     /*!< DXF 271 */
  BITCODE_BD normalmap_strength;   /*!< DXF 465 def: 1.0 */
  Dwg_MATERIAL_mapper normalmap;   /*!< DXF 42, 72, 3, 73, 74, 75, 43 */
  BITCODE_B is_anonymous;          /*!< DXF 293 */
  BITCODE_BS global_illumination;  /*!< DXF 272 */
  BITCODE_BS final_gather;         /*!< DXF 273 */
#endif
  //? BD backface_cull
  //? BD self_illum_luminance
  //? BD self_illum_color_temperature
} Dwg_Object_MATERIAL;

/**
 Object OBJECT_PTR (varies) UNKNOWN FIELDS
 yet unsorted, and unused.
 */
typedef struct _dwg_object_OBJECT_PTR
{
  struct _dwg_object_object *parent;
} Dwg_Object_OBJECT_PTR;

/**
 Entity LIGHT (varies)
 UNSTABLE, now complete
 */
typedef struct _dwg_entity_LIGHT
{
  struct _dwg_object_entity *parent;

  BITCODE_BL class_version; /*!< DXF 90 */
  BITCODE_T name;       /*!< DXF 1 */
  BITCODE_BL type;      /*!< DXF 70, distant = 1; point = 2; spot = 3 */
  BITCODE_B status;     /*!< DXF 290, on or off */
  BITCODE_CMC color;    /*!< DXF 63 + 421. r2000: 90 for the rgb value */
  BITCODE_B plot_glyph; /*!< DXF 291 */
  BITCODE_BD intensity; /*!< DXF 40 */
  BITCODE_3BD position; /*!< DXF 10 */
  BITCODE_3BD target;   /*!< DXF 11 */
  BITCODE_BL attenuation_type;        /*!< DXF 72. None=0, Inverse Linear=1,
                                                   Inverse Square=2 */
  BITCODE_B use_attenuation_limits;   /*!< DXF 292 */
  BITCODE_BD attenuation_start_limit; /*!< DXF 41 */
  BITCODE_BD attenuation_end_limit;   /*!< DXF 42 */
  BITCODE_BD hotspot_angle; 	  /*!< DXF 50 */
  BITCODE_BD falloff_angle; 	  /*!< DXF 51, with type=spot */
  BITCODE_B cast_shadows;   	  /*!< DXF 293 */
  BITCODE_BL shadow_type;   	  /*!< DXF 73, ray_traced=0, shadow_maps=1 */
  BITCODE_BS shadow_map_size;     /*!< DXF 91 in pixel: 64,128,256,...4096 */
  BITCODE_RC shadow_map_softness; /*!< DXF 280 1-10 (num pixels blend into) */

  BITCODE_B is_photometric;       /* if LIGHTINGUNITS == "2" */
  BITCODE_B has_photometric_data;
  BITCODE_B has_webfile;          /*!< DXF 290 */
  BITCODE_T webfile;              /*!< DXF 300 IES file */
  BITCODE_BS physical_intensity_method; /*!< DXF 70 */
  BITCODE_BD physical_intensity;  /*!< DXF 40 */
  BITCODE_BD illuminance_dist;    /*!< DXF 41 */
  BITCODE_BS lamp_color_type;     /*!< DXF 71 0: in kelvin, 1: as preset */
  BITCODE_BD lamp_color_temp;     /*!< DXF 42 Temperature in Kelvin */
  BITCODE_BS lamp_color_preset;   /*!< DXF 72 */
  BITCODE_BL lamp_color_rgb;      /*!< if lamp_color_preset is Custom */
  BITCODE_3BD web_rotation;       /*!< DXF 43-45 rotation offset in XYZ Euler angles */
  BITCODE_BS extlight_shape;      /*!< DXF 73: 0 linear, 1 rect, 2 disk, 3 cylinder, 4 sphere */
  BITCODE_BD extlight_length;     /*!< DXF 46 */
  BITCODE_BD extlight_width;      /*!< DXF 47 */
  BITCODE_BD extlight_radius;     /*!< DXF 48 */
  BITCODE_BS webfile_type;        /*!< DXF 74 */
  BITCODE_BS web_symetry;         /*!< DXF 75 */
  BITCODE_BS has_target_grip;     /*!< DXF 76
                                       if the light displays a target grip for orienting
                                       the light */
  BITCODE_BD web_flux;        /*!< DXF 49 */
  BITCODE_BD web_angle1;      /*!< DXF 50 */
  BITCODE_BD web_angle2;      /*!< DXF 51 */
  BITCODE_BD web_angle3;      /*!< DXF 52 */
  BITCODE_BD web_angle4;      /*!< DXF 53 */
  BITCODE_BD web_angle5;      /*!< DXF 54 */
  BITCODE_BS glyph_display_type;  /*!< DXF 77 0:auto, 1:on, 2:off */
} Dwg_Entity_LIGHT;

/**
 Entity CAMERA (varies) UNKNOWN FIELDS
 not DWG persistent. yet unsorted, and unused.
 */
typedef struct _dwg_entity_CAMERA
{
  struct _dwg_object_entity *parent;
  BITCODE_H view;
} Dwg_Entity_CAMERA;

/**
 Entity GEOPOSITIONMARKER (varies)
*/
typedef struct _dwg_entity_GEOPOSITIONMARKER
{
  struct _dwg_object_entity *parent;
  BITCODE_BS type;        /*!< DXF 90 point, lat_lon, mylocation */
  BITCODE_3BD position;   /*!< DXF 10 */
  BITCODE_BD radius;      /*!< DXF 40 */
  BITCODE_BD landing_gap; /*!< DXF 40 */
  BITCODE_T notes;         /*!< DXF 1 */
  BITCODE_RC text_alignment;   /*!< DXF 70  0 left, 1 center, 2 right */
  BITCODE_B mtext_visible;     /*!< DXF 290 */
  BITCODE_B enable_frame_text; /*!< DXF 290 */
  struct _dwg_object *mtext;
} Dwg_Entity_GEOPOSITIONMARKER;

/**
 Object GEOMAPIMAGE (varies), LiveMap image overlay.
 yet unsorted, and unused.
*/
typedef struct _dwg_object_GEOMAPIMAGE
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version; // 90
  BITCODE_3BD pt0; // 10
  BITCODE_2RD size; // 13
  BITCODE_BS display_props; // 70
  BITCODE_B clipping; // 280 i.e. clipping_enabled
  BITCODE_RC brightness; // 281
  BITCODE_RC contrast; // 282
  BITCODE_RC fade; // 283
  BITCODE_BD rotation;
  //?
  //BITCODE_3BD origin;
  BITCODE_BD image_width;
  BITCODE_BD image_height;
  BITCODE_T name;
  BITCODE_BD image_file;
  BITCODE_BD image_visibility;
  BITCODE_BS transparency;
  BITCODE_BD height;
  BITCODE_BD width;
  BITCODE_B show_rotation;
  BITCODE_BD scale_factor;
  BITCODE_BS geoimage_brightness;
  BITCODE_BS geoimage_contrast;
  BITCODE_BS geoimage_fade;
  BITCODE_BS geoimage_position;
  BITCODE_BS geoimage_width;
  BITCODE_BS geoimage_height;
} Dwg_Object_GEOMAPIMAGE;

/**
 Entity HELIX (varies) UNSTABLE
 subclass of SPLINE
*/
typedef struct _dwg_entity_HELIX
{
  struct _dwg_object_entity *parent;

  BITCODE_BS flag; /* computed */
  BITCODE_BS scenario; /* 1 spline, 2 bezier */
  BITCODE_BS degree;
  BITCODE_BL splineflags1; /* 2013+: method fit points = 1, CV frame show = 2, closed = 4 */
  BITCODE_BL knotparam;    /* 2013+: Chord = 0, Square root = 1, Uniform = 2, Custom = 15 */
  BITCODE_BD fit_tol;
  BITCODE_3BD beg_tan_vec;
  BITCODE_3BD end_tan_vec;
  BITCODE_B rational;
  BITCODE_B closed_b;
  BITCODE_B periodic;
  BITCODE_B weighted; /* bit 4 of 70 */
  BITCODE_BD knot_tol;
  BITCODE_BD ctrl_tol;
  BITCODE_BS num_fit_pts;
  BITCODE_3DPOINT* fit_pts;
  BITCODE_BL num_knots;
  BITCODE_BD* knots;
  BITCODE_BL num_ctrl_pts;
  Dwg_SPLINE_control_point* ctrl_pts;

  BITCODE_BS major_version; //90
  BITCODE_BS maint_version; //91
  BITCODE_3BD axis_base_pt; //10
  BITCODE_3BD start_pt;     //11
  BITCODE_3BD axis_vector;  //12
  BITCODE_BD radius;        //40
  BITCODE_BD num_turns;     //41
  BITCODE_BD turn_height;   //42
  BITCODE_B handedness;     //290
  BITCODE_BS constraint_type; //280: 0=turn_height, 1=turns, 2=height

} Dwg_Entity_HELIX;

#define SweepOptions_FIELDS  \
  BITCODE_BD draft_angle;   	   /*!< DXF 42 */ \
  BITCODE_BD draft_start_distance; /*!< DXF 43 */ \
  BITCODE_BD draft_end_distance;   /*!< DXF 44 */ \
  BITCODE_BD twist_angle;   	   /*!< DXF 45 */ \
  BITCODE_BD scale_factor;  /*!< DXF 48 */ \
  BITCODE_BD align_angle;   /*!< DXF 49 */ \
  BITCODE_BD* sweep_entity_transmatrix; /*!< DXF 46: 16x BD */ \
  BITCODE_BD* path_entity_transmatrix;  /*!< DXF 47: 16x BD */ \
  BITCODE_B is_solid;          /*!< DXF 290 */ \
  BITCODE_BS sweep_alignment_flags; /*!< DXF 70. \
                                      0=No alignment, 1=Align sweep entity to path, \
                                      2=Translate sweep entity to path, \
                                      3=Translate path to sweep entity */ \
  BITCODE_BS path_flags; /*!< DXF 71 */                                 \
  BITCODE_B align_start;                        /*!< DXF 292 */ \
  BITCODE_B bank;                               /*!< DXF 293 */ \
  BITCODE_B base_point_set;                     /*!< DXF 294 */ \
  BITCODE_B sweep_entity_transform_computed;    /*!< DXF 295 */ \
  BITCODE_B path_entity_transform_computed;     /*!< DXF 296 */ \
  BITCODE_3BD reference_vector_for_controlling_twist; /*!< DXF 11 */ \
  BITCODE_H sweep_entity; \
  BITCODE_H path_entity

/**
 Entity EXTRUDEDSURFACE (varies)
 in DXF encrypted.
*/
typedef struct _dwg_entity_EXTRUDEDSURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  //? sweep_profile, taper_angle
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BL bindata_size; // 90
  BITCODE_TF bindata; // 310|1
  BITCODE_BS u_isolines;        /*!< DXF 71 */
  BITCODE_BS v_isolines;        /*!< DXF 72 */
  BITCODE_BL class_version; 	/*!< DXF 90 */
  SweepOptions_FIELDS;
  //BITCODE_BD height;
  BITCODE_3BD sweep_vector; 	 /*!< DXF 10 */
  BITCODE_BD* sweep_transmatrix; /*!< DXF 40: 16x BD */
} Dwg_Entity_EXTRUDEDSURFACE;

/**
 Entity SWEPTSURFACE (varies)
*/
typedef struct _dwg_entity_SWEPTSURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BS u_isolines;         /*!< DXF 71 */
  BITCODE_BS v_isolines;         /*!< DXF 72 */
  BITCODE_BL class_version; /*!< DXF 90 */

  BITCODE_BL sweep_entity_id; // 90
  BITCODE_BL sweepdata_size;
  BITCODE_TF sweepdata;
  BITCODE_BL path_entity_id;
  BITCODE_BL pathdata_size;
  BITCODE_TF pathdata;
  SweepOptions_FIELDS;
} Dwg_Entity_SWEPTSURFACE;

/**
 Entity LOFTEDSURFACE (varies)
*/
typedef struct _dwg_entity_LOFTEDSURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BS u_isolines;         /*!< DXF 71 */
  BITCODE_BS v_isolines;         /*!< DXF 72 */
  //BITCODE_BL class_version;      /*!< DXF 90 */
  BITCODE_BD* loft_entity_transmatrix; /*!< DXF 40: 16x BD */
  BITCODE_BL plane_normal_lofting_type; /*!< DXF 70 */
  BITCODE_BD start_draft_angle;     /*!< DXF 41 */
  BITCODE_BD end_draft_angle;       /*!< DXF 42 */
  BITCODE_BD start_draft_magnitude; /*!< DXF 43 */
  BITCODE_BD end_draft_magnitude;   /*!< DXF 44 */
  BITCODE_B arc_length_parameterization; // 290
  BITCODE_B no_twist; // 291
  BITCODE_B align_direction; // 292
  BITCODE_B simple_surfaces; // 293
  BITCODE_B closed_surfaces; // 294
  BITCODE_B solid; // 295
  BITCODE_B ruled_surface; // 296
  BITCODE_B virtual_guide; // 297

  BITCODE_BS num_cross_sections;
  BITCODE_BS num_guide_curves;
  BITCODE_H *cross_sections;
  BITCODE_H *guide_curves;
  BITCODE_H path_curve;
} Dwg_Entity_LOFTEDSURFACE;

/**
 Entity NURBSURFACE (varies)
 no coverage yet
*/
typedef struct _dwg_entity_NURBSURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BS u_isolines;         /*!< DXF 71 */
  BITCODE_BS v_isolines;         /*!< DXF 72 */
  BITCODE_BL class_version; /*!< DXF 90 */
  // ...
} Dwg_Entity_NURBSURFACE;

/**
 Entity PLANESURFACE (varies)
*/
typedef struct _dwg_entity_PLANESURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BS u_isolines;         /*!< DXF 71 */
  BITCODE_BS v_isolines;         /*!< DXF 72 */
  BITCODE_BL class_version;      /*!< DXF 90 */

} Dwg_Entity_PLANESURFACE;

/**
 Entity REVOLVEDSURFACE (varies)
*/
typedef struct _dwg_entity_REVOLVEDSURFACE
{
  struct _dwg_object_entity *parent;
  _3DSOLID_FIELDS;
  BITCODE_BS modeler_format_version; /*!< DXF 70 */
  BITCODE_BS u_isolines;         /*!< DXF 71 */
  BITCODE_BS v_isolines;         /*!< DXF 72 */
  BITCODE_BL class_version; /*!< DXF 90 */

  BITCODE_BL id; // 90
  BITCODE_3BD axis_point; // 10
  BITCODE_3BD axis_vector; // 11
  BITCODE_BD revolve_angle; // 40
  BITCODE_BD start_angle; // 41
  BITCODE_BD* revolved_entity_transmatrix; // 42
  BITCODE_BD draft_angle; // 43
  BITCODE_BD draft_start_distance; // 44
  BITCODE_BD draft_end_distance; // 45
  BITCODE_BD twist_angle; // 46
  BITCODE_B solid; // 290
  BITCODE_B close_to_axis; // 291

} Dwg_Entity_REVOLVEDSURFACE;

/**
 Entity MESH (varies)
 Types: Sphere|Cylinder|Cone|Torus|Box|Wedge|Pyramid
*/
typedef struct _dwg_MESH_edge
{
  struct _dwg_entity_MESH *parent;
  BITCODE_BL idxfrom; // index from
  BITCODE_BL idxto; // index to
} Dwg_MESH_edge;

typedef struct _dwg_entity_MESH
{
  struct _dwg_object_entity *parent;
  BITCODE_BS dlevel; 		/*!< DXF 71 (2) */
  BITCODE_B is_watertight; 	/*!< DXF 72 (0) */
  BITCODE_BL num_subdiv_vertex; /*!< DXF 91 (0) */
  BITCODE_3DPOINT* subdiv_vertex;/*!< DXF 10 ?? */
  BITCODE_BL num_vertex;  	/*!< DXF 92 (14) */
  BITCODE_3DPOINT* vertex; 	/*!< DXF 10 */
  BITCODE_BL num_faces;  	/*!< DXF 93 (30) */
  BITCODE_BL* faces;  	        /*!< DXF 90 */
  BITCODE_BL num_edges;  	/*!< DXF 94 (19) */
  Dwg_MESH_edge* edges;   	/*!< DXF 90 */
  BITCODE_BL num_crease;  	/*!< DXF 95 (19) */
  BITCODE_BD* crease;   	/*!< DXF 140 */
} Dwg_Entity_MESH;

/**
 Object SUN (varies), unstable
 wrongly documented by ACAD DXF as entity
 */
typedef struct _dwg_object_SUN
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version; /*!< DXF 90 */
  BITCODE_B is_on;          /*!< DXF 290 */
  BITCODE_CMC color;        /*!< DXF 60, 421 */
  BITCODE_BD intensity;     /*!< DXF 40 */
  BITCODE_B  has_shadow;    /*!< DXF 291 */
  BITCODE_BL julian_day;    /*!< DXF 91 */
  BITCODE_BL msecs;         /*!< DXF 92 */
  BITCODE_B  is_dst;        /*!< DXF 292 */
  BITCODE_BL shadow_type;   /*!< DXF 70 */
  BITCODE_BS shadow_mapsize;  /*!< DXF 71 */
  BITCODE_RC shadow_softness; /*!< DXF 280 */
} Dwg_Object_SUN;

typedef struct _dwg_SUNSTUDY_Dates
{
  BITCODE_BL julian_day;
  BITCODE_BL msecs;           //seconds past midnight
} Dwg_SUNSTUDY_Dates;

/**
 Object SUNSTUDY (varies)
 --enable-debug only
 */
typedef struct _dwg_object_SUNSTUDY
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;     /*!< DXF 90 */
  BITCODE_T setup_name;         /*!< DXF 1 */
  BITCODE_T description;        /*!< DXF 2 */
  BITCODE_BL output_type;       /*!< DXF 70 */
  BITCODE_T sheet_set_name;     /*!< DXF 3 */
  BITCODE_B use_subset;         /*!< DXF 290 */
  BITCODE_T sheet_subset_name;  /*!< DXF 3 */
  BITCODE_B select_dates_from_calendar; /*!< DXF 291 */
  BITCODE_BL num_dates;         /*!< DXF 91 */
  Dwg_SUNSTUDY_Dates* dates;    /*!< DXF 90[] */
  BITCODE_B select_range_of_dates; /*!< DXF 292 */
  BITCODE_BL start_time;        /*!< DXF 93 */
  BITCODE_BL end_time;          /*!< DXF 94 */
  BITCODE_BL interval;          /*!< DXF 95 */
  BITCODE_BL num_hours;         /*!< DXF 73 */
  BITCODE_B* hours;             /*!< DXF 290 */
  BITCODE_BL shade_plot_type;   /*!< DXF 74 */
  BITCODE_BL numvports;         /*!< DXF 75 */
  BITCODE_BL numrows;           /*!< DXF 76 */
  BITCODE_BL numcols;           /*!< DXF 77 */
  BITCODE_BD spacing;           /*!< DXF 40 */
  BITCODE_B  lock_viewports;    /*!< DXF 293 */
  BITCODE_B  label_viewports;   /*!< DXF 294 */

  BITCODE_H  page_setup_wizard; /*!< 5 DXF 340 */
  BITCODE_H  view;              /*!< DXF 341 */
  BITCODE_H  visualstyle;       /*!< DXF 342 */
  BITCODE_H  text_style;        /*!< DXF 343 */
} Dwg_Object_SUNSTUDY;

typedef struct _dwg_DATATABLE_row
{
  struct _dwg_object_DATATABLE *parent;
  Dwg_TABLE_value value;
} Dwg_DATATABLE_row;

typedef struct _dwg_DATATABLE_column
{
  struct _dwg_object_DATATABLE *parent;
  BITCODE_BL type;          /* DXF 92 */
  BITCODE_T  text;          /* DXF 2 */
  Dwg_DATATABLE_row *rows;
} Dwg_DATATABLE_column;

/**
 Object DATATABLE (varies)
 --enable-debug only
 */
typedef struct _dwg_object_DATATABLE
{
  struct _dwg_object_object *parent;
  BITCODE_BS flags;	/* DXF 70 */
  BITCODE_BL num_cols;	/* DXF 90 */
  BITCODE_BL num_rows;	/* DXF 91 */
  BITCODE_T table_name;	/* DXF 1 */
  Dwg_DATATABLE_column *cols;
} Dwg_Object_DATATABLE;

/**
 Object DATALINK (varies)
 */
typedef struct _dwg_DATALINK_customdata
{
  struct _dwg_object_DATALINK *parent;
  BITCODE_H target; // 330
  BITCODE_T text;   // 304
} Dwg_DATALINK_customdata;

typedef struct _dwg_object_DATALINK
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version; /*<! DXF 70 1 */
  BITCODE_T data_adapter;/*<! DXF 1  */
  BITCODE_T description;/*<! DXF 300  */
  BITCODE_T tooltip;	/*<! DXF 301  */
  BITCODE_T connection_string;	/*<! DXF 302  */
  BITCODE_BL option;	/*<! DXF 90  2 */
  BITCODE_BL update_option;/*<! DXF 91  1179649 */
  BITCODE_BL bl92;	/*<! DXF 92  1 */
  BITCODE_BS year;	/*<! DXF 170  */
  BITCODE_BS month;	/*<! DXF 171  */
  BITCODE_BS day;	/*<! DXF 172  */
  BITCODE_BS hour;	/*<! DXF 173  */
  BITCODE_BS minute;	/*<! DXF 174  */
  BITCODE_BS seconds;	/*<! DXF 175  */
  BITCODE_BS msec;	/*<! DXF 176  */
  BITCODE_BS path_option; /*<! DXF 177  1 */
  BITCODE_BL bl93;	  /*<! DXF 93   0 */
  BITCODE_T update_status;/*<! DXF 304  */
  BITCODE_BL num_customdata; // 94
  Dwg_DATALINK_customdata *customdata; // 330 + 304
  BITCODE_H hardowner;	/*<! DXF 360  */
} Dwg_Object_DATALINK;

/**
 Object DIMASSOC (varies) DEBUGGING
 --enable-debug only
 */
typedef struct _dwg_DIMASSOC_Ref
{
  struct _dwg_object_DIMASSOC *parent;
  BITCODE_T classname;         /*!< DXF 1 constant */
  BITCODE_RC osnap_type;       /*!< DXF 72 */
  BITCODE_BD osnap_dist;       /*!< DXF 40 */
  BITCODE_3BD osnap_pt;        /*!< DXF 10-30 */
  BITCODE_BS num_xrefs;
  BITCODE_H *xrefs;            /*!< DXF 331 the geometry objects, 1 or 2 */ 
  BITCODE_BS main_subent_type; /*!< DXF 73 */
  BITCODE_BL main_gsmarker;    /*!< DXF 91 */
  BITCODE_BS num_xrefpaths;
  BITCODE_T *xrefpaths;        /*!< DXF 301 */
  BITCODE_B  has_lastpt_ref;   /*!< DXF 75 */
  BITCODE_3BD lastpt_ref;      /*!< DXF ?? */
  BITCODE_BL num_intsectobj;   /*!< DXF 74 */
  BITCODE_H* intsectobj;       /*!< DXF 332 the intersection objects, 1 or 2 */
} Dwg_DIMASSOC_Ref;

typedef struct _dwg_object_DIMASSOC
{
  struct _dwg_object_object *parent;
  BITCODE_H dimensionobj;
  BITCODE_BL associativity;   /*!< DXF 90, bitmask 0-15*/
  BITCODE_B trans_space_flag; /*!< DXF 70 boolean */
  BITCODE_RC rotated_type;      /*!< DXF 71 */
  Dwg_DIMASSOC_Ref *ref;       /* 1-4x, with possible holes,
                                  depend. on associativity bitmask */
} Dwg_Object_DIMASSOC;

typedef struct _dwg_ACTIONBODY
{
  struct _dwg_object_ASSOCNETWORK *parent;
  BITCODE_T  evaluatorid;
  BITCODE_T  expression;
  BITCODE_BL value; //resbuf
} Dwg_ACTIONBODY;


typedef struct _dwg_ASSOCACTION_Deps
{
  struct _dwg_object_ASSOCACTION *parent;
  BITCODE_B is_soft;
  BITCODE_H dep;
} Dwg_ASSOCACTION_Deps;

#define ASSOCACTION_fields                                  \
  /* until r2010: 1, 2013+: 2 */                            \
  BITCODE_BS class_version;   /* 90 */                      \
  /* 0 WellDefined, 1 UnderConstrained, 2 OverConstrained,  \
     3 Inconsistent, 4 NotEvaluated, 5 NotAvailable,        \
     6 RejectedByClient */                                  \
  BITCODE_BL geometry_status;         /* 90 */              \
  BITCODE_H owningnetwork;            /* 330 */             \
  BITCODE_H actionbody;               /* 360 */             \
  BITCODE_BL action_index;            /* 90 */              \
  BITCODE_BL max_assoc_dep_index;     /* 90 */              \
  BITCODE_BL num_deps;                /* 90 */              \
  Dwg_ASSOCACTION_Deps *deps;         /* 330 or 360 */      \
  BITCODE_BL num_owned_params;        /* 90 */              \
  BITCODE_H *owned_params;            /* 360 */             \
  BITCODE_BL num_owned_value_param_names;        /* 90 */   \
  BITCODE_H *owned_value_param_names             /* ? */

typedef struct _dwg_object_ASSOCACTION
{
  struct _dwg_object_object *parent;
  ASSOCACTION_fields;
  //BITCODE_B is_actionevaluation_in_progress; // 90
  //Dwg_ACTIONBODY body;
  //BITCODE_BL status;
  //BITCODE_H  actionbody;
  //BITCODE_H  callback;
  //BITCODE_H  owningnetwork;
} Dwg_Object_ASSOCACTION;

typedef struct _dwg_object_ASSOCDEPENDENCY
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version; // 90
  BITCODE_BL status; // 90
  BITCODE_B isread_dep; // 290
  BITCODE_B iswrite_dep; // 290
  BITCODE_B isobjectstate_dep; // 290
  BITCODE_B unknown_b4; // 290
  BITCODE_BL order; // 90 -2147483648
  BITCODE_B unknown_b5; // 290
  BITCODE_BL depbodyid; // 90

  BITCODE_H  owner; // 330
  BITCODE_H  readdep; // 330
  BITCODE_H  writedep; // 360
  BITCODE_H  node; // 330
} Dwg_Object_ASSOCDEPENDENCY;

typedef struct _dwg_object_ASSOCALIGNEDDIMACTIONBODY
{
  struct _dwg_object_object *parent;
  BITCODE_BL aab_version; // 90: until 2010: 1, 2013+: 2
  BITCODE_BL pab_status; // 90:0
  BITCODE_BL pab_l2; // 90:0
  BITCODE_BL pab_l3; // 90:1
  BITCODE_H  writedep; // 360
  BITCODE_BL pab_l4; // 90:0
  BITCODE_BL pab_l5; // 90:0
  BITCODE_BL pab_l6; // 90:0
  BITCODE_H  readdep; // 330
  BITCODE_BL dcm_status; // 90:0
  BITCODE_H  d_node; // 330
  BITCODE_H  r_node; // 330
} Dwg_Object_ASSOCALIGNEDDIMACTIONBODY;

/**
 Object ASSOCNETWORK (varies) UNKNOWN FIELDS
 subclass of AcDbAssocAction
 Object1 --ReadDep--> Action1 --WriteDep1--> Object2 --ReadDep--> Action2 ...
 */
typedef struct _dwg_object_ASSOCNETWORK
{
  struct _dwg_object_object *parent;
  ASSOCACTION_fields;
  //BITCODE_H assocaction;
  //or inlined:
  //90:2 90:0 330:0 360:0 7x90:0
  //BITCODE_BL num_deps; // 90

  BITCODE_BL unknown_assoc; // 90
  //90, 90, [90, 330], 90
  BITCODE_BL unknown_n1; // 90 0
  BITCODE_BL unknown_n2; // 90 1
  BITCODE_BL num_actions;// 90 1
  BITCODE_H* actions;    // 360
  //BITCODE_BL unknown_n3; // 90 0
} Dwg_Object_ASSOCNETWORK;

/**
 Object ASSOCOSNAPPOINTREFACTIONPARAM (varies) UNKNOWN FIELDS
 Action parameter that owns other AcDbAssocActionParameters,
 allowing the representation of hierarchical structures of action parameters.
 */
typedef struct _dwg_object_ASSOCOSNAPPOINTREFACTIONPARAM
{
  struct _dwg_object_object *parent;
  // AcDbAssocActionParam
  BITCODE_RC unknown;  // 01010101
  BITCODE_B unknown1;  //
  BITCODE_BS status;   // 90: 0 uptodate, 1 changed_directly, 2 changed_transitive,
                       // 3 ChangedNoDifference, 4 FailedToEvaluate, 5 Erased, 6 Suppressed
                       // 7 Unresolved
  BITCODE_T  name;     // 1 ""
  BITCODE_RS flags;    // 90 0
  // AcDbAssocCompoundActionParam
  BITCODE_BD unknown3; // 40 -1.0
  BITCODE_BS num_actions; // 90 1
  BITCODE_H *actions;  // 330
  BITCODE_H writedep;  // 360
} Dwg_Object_ASSOCOSNAPPOINTREFACTIONPARAM;

typedef struct _dwg_object_ASSOCVERTEXACTIONPARAM
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version;
  //?
  // AcDbAssocActionParam
  BITCODE_RC unknown;  // 01010101
  BITCODE_B unknown1;  //
  BITCODE_BS status;   // 90: 0 uptodate, 1 changed_directly, 2 changed_transitive,
                       // 3 ChangedNoDifference, 4 FailedToEvaluate, 5 Erased, 6 Suppressed
                       // 7 Unresolved
  BITCODE_T  name;     // 1 ""
  BITCODE_RS flags;    // 90 0
  // AcDbAssocCompoundActionParam
  BITCODE_BD unknown3; // 40 -1.0
  BITCODE_BS num_actions; // 90 1
  BITCODE_H *actions;  // 330
  BITCODE_H writedep;  // 360

} Dwg_Object_ASSOCVERTEXACTIONPARAM;

typedef struct _dwg_object_ASSOC2DCONSTRAINTGROUP
{
  struct _dwg_object_object *parent;
  ASSOCACTION_fields;

  BITCODE_BL l5; //90 1
  BITCODE_B  b1; //70 0
  BITCODE_3BD workplane[3]; //3x10 workplane
  BITCODE_H h1; // 360
  BITCODE_BL num_actions;// 90
  BITCODE_H* actions;    // 360
  BITCODE_BL l7; //90 9
  BITCODE_BL l8; //90 9

  BITCODE_T t1; // AcConstrainedCircle
  BITCODE_H h2; // 330
  BITCODE_BL cl1; //90 1
  BITCODE_RC cs1; //70 1
  BITCODE_BL cl2; //90 1
  BITCODE_BL cl3; //90 3
  BITCODE_H h3; // 330
  BITCODE_BL cl4; //90 0
  BITCODE_3BD c1; //10 @134
  BITCODE_3BD c2; //10
  BITCODE_3BD c3; //10
  BITCODE_BD w1; //40
  BITCODE_BD w2; //40
  BITCODE_BD w3; //40
  BITCODE_T t2; // AcConstrainedImplicitPoint
} Dwg_Object_ASSOC2DCONSTRAINTGROUP;

/* or maybe the nodes are laid out like this */
typedef struct _dwg_EVAL_Node
{
  struct _dwg_object_EVALUATION_GRAPH *parent;
  BITCODE_BL  edge[4];   // 4x 92, def: 4x -1
  //BITCODE_H   evalexpr;   // 360
} Dwg_EVAL_Node;

typedef struct _dwg_object_EVALUATION_GRAPH
{
  struct _dwg_object_object *parent;
  BITCODE_BL has_graph;   // 96
  BITCODE_BL unknown1;    // 97
  BITCODE_BL unknown2;
  BITCODE_BL nodeid;      // 91
  BITCODE_BL edge_flags;  // 93
  BITCODE_BL num_evalexpr;// 95
  BITCODE_BL node_edge1;  // 92
  BITCODE_BL node_edge2;  // 92
  BITCODE_BL node_edge3;  // 92
  BITCODE_BL node_edge4;  // 92
  BITCODE_H  *evalexpr;    //360
} Dwg_Object_EVALUATION_GRAPH;

// stable
typedef struct _dwg_object_DYNAMICBLOCKPURGEPREVENTER
{
  struct _dwg_object_object *parent;
  BITCODE_BS flag;         /*!< DXF 70 0 */
  BITCODE_H  block;
} Dwg_Object_DYNAMICBLOCKPURGEPREVENTER;

typedef struct _dwg_object_PERSUBENTMGR
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version;   /*!< DXF 90 2 */
  BITCODE_BL unknown_0;       /*!< DXF 90 0 */
  BITCODE_BL unknown_2;       /*!< DXF 90 2 */
  BITCODE_BL numassocsteps;   /*!< DXF 90 3 from ASSOCPERSSUBENTMANAGER */
  BITCODE_BL numassocsubents; /*!< DXF 90 0 from ASSOCPERSSUBENTMANAGER */
  BITCODE_BL num_steps;       /*!< DXF 90 1 */
  BITCODE_BL *steps;          /*!< DXF 90 */
  BITCODE_BL num_subents;     /*!< DXF 90 */
  BITCODE_BL *subents;        /*!< DXF 90 types/handles? */
} Dwg_Object_PERSUBENTMGR;

// The dynamic variant of above. May be frozen as static PERSUBENTMGR
// TODO subentities
typedef struct _dwg_object_ASSOCPERSSUBENTMANAGER
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version; /*!< DXF 90 1 or r2013+ 2 */
  BITCODE_BL unknown_3;     /*!< DXF 90 always 3 */
  BITCODE_BL unknown_0;     /*!< DXF 90 always 0 */
  BITCODE_BL unknown_2;     /*!< DXF 90 always 2 */
  BITCODE_BL numassocsteps;   /*!< DXF 90 3 */
  BITCODE_BL numassocsubents; /*!< DXF 90 5 */
  BITCODE_BL *assocsteps;     /*!< DXF 90 */
  BITCODE_BL *assocsubents;   /*!< DXF 90 */
  BITCODE_BL unknown_bl6;   /*!< DXF 90 5 */
  BITCODE_BL unknown_bl6a;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl7a;  /*!< DXF 90 3 */
  BITCODE_BL unknown_bl7;   /*!< DXF 90 2 */
  BITCODE_BL unknown_bl8;   /*!< DXF 90 2 */
  BITCODE_BL unknown_bl9;   /*!< DXF 90 2 */
  BITCODE_BL unknown_bl10;  /*!< DXF 90 21 */
  BITCODE_BL unknown_bl11;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl12;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl13;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl14;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl15;  /*!< DXF 90 1 */
  BITCODE_BL unknown_bl16;  /*!< DXF 90 3 */
  BITCODE_BL unknown_bl17;  /*!< DXF 90 1 */
  BITCODE_BL unknown_bl18;  /*!< DXF 90 1000000000 */
  BITCODE_BL unknown_bl19;  /*!< DXF 90 1001 */
  BITCODE_BL unknown_bl20;  /*!< DXF 90 1 */
  BITCODE_BL unknown_bl21;  /*!< DXF 90 1000000000 */
  BITCODE_BL unknown_bl22;  /*!< DXF 90 51001 */
  BITCODE_BL unknown_bl23;  /*!< DXF 90 1 */
  BITCODE_BL unknown_bl24;  /*!< DXF 90 1000000000 */
  BITCODE_BL unknown_bl25;  /*!< DXF 90 351001 */
  BITCODE_BL unknown_bl26;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl27;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl28;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl29;  /*!< DXF 90 900 */
  BITCODE_BL unknown_bl30;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl31;  /*!< DXF 90 900 */
  BITCODE_BL unknown_bl32;  /*!< DXF 90 0 */
  BITCODE_BL unknown_bl33;  /*!< DXF 90 2 */
  BITCODE_BL unknown_bl34;  /*!< DXF 90 2 */
  BITCODE_BL unknown_bl35;  /*!< DXF 90 3 0100000011 */
  BITCODE_BL unknown_bl36;  /*!< DXF 90 0 */
  BITCODE_B  unknown_b37;   /*!< DXF 290 0 */
} Dwg_Object_ASSOCPERSSUBENTMANAGER;

#define ASSOCPARAMBASEDACTIONBODY_fields \
  /* AcDbAssocActionBody */ \
  BITCODE_BL aab_version; /* 90 */ \
  /* AcDbAssocParamBasedActionBody */ \
  BITCODE_BL pab_status; /* 90:0 */ \
  BITCODE_BL pab_l2; /* 90:0*/ \
  BITCODE_BL num_deps; /* 90:1*/ \
  BITCODE_H  *writedeps; /* 360*/ \
  BITCODE_BL pab_l4; /* 90:0*/ \
  BITCODE_BL pab_l5; /* 90:0*/ \
  BITCODE_H  *readdeps; /* 330*/ \
  BITCODE_T  *descriptions; /*1*/ \

#define ASSOCPATHBASEDSURFACEACTIONBODY_fields \
  ASSOCPARAMBASEDACTIONBODY_fields \
  /* AcDbAssocSurfaceActionBody */ \
  BITCODE_BL sab_status;/*!< DXF 90 */ \
  BITCODE_B sab_b1;     /*!< DXF 290 */ \
  BITCODE_BL sab_l2;    /*!< DXF 90 */ \
  BITCODE_B sab_b2;     /*!< DXF 290 */ \
  BITCODE_BS sab_s1;    /*!< DXF 70 */ \
  /* AcDbAssocPathBasedSurfaceActionBody */ \
  BITCODE_BL pbsab_status; /*!< DXF 90 */

typedef struct _dwg_object_ASSOCEXTRUDEDSURFACEACTIONBODY
{
  struct _dwg_object_object *parent;
  ASSOCPATHBASEDSURFACEACTIONBODY_fields
  // AcDbAssocExtrudedSurfaceActionBody
  BITCODE_BL esab_status;       /*!< DXF 90  */
} Dwg_Object_ASSOCEXTRUDEDSURFACEACTIONBODY;

typedef struct _dwg_object_ASSOCPLANESURFACEACTIONBODY
{
  struct _dwg_object_object *parent;
  ASSOCPATHBASEDSURFACEACTIONBODY_fields
  // AcDbAssocPlaneSurfaceActionBody
  BITCODE_BL psab_status;       /*!< DXF 90  */

} Dwg_Object_ASSOCPLANESURFACEACTIONBODY;

typedef struct _dwg_object_ASSOCLOFTEDSURFACEACTIONBODY
{
  struct _dwg_object_object *parent;
  ASSOCPATHBASEDSURFACEACTIONBODY_fields
  // AcDbAssocLoftedSurfaceActionBody
  BITCODE_BL lsab_status;       /*!< DXF 90  */
} Dwg_Object_ASSOCLOFTEDSURFACEACTIONBODY;

typedef struct _dwg_object_ASSOCREVOLVEDSURFACEACTIONBODY
{
  struct _dwg_object_object *parent;
  ASSOCPATHBASEDSURFACEACTIONBODY_fields
  // AcDbAssocRevolvedSurfaceActionBody
  BITCODE_BL rsab_status;       /*!< DXF 90  */
} Dwg_Object_ASSOCREVOLVEDSURFACEACTIONBODY;

typedef struct _dwg_object_ASSOCSWEPTSURFACEACTIONBODY
{
  struct _dwg_object_object *parent;
  ASSOCPATHBASEDSURFACEACTIONBODY_fields
  // AcDbAssocSweptSurfaceActionBody
  BITCODE_BL ssab_status;       /*!< DXF 90  */
} Dwg_Object_ASSOCSWEPTSURFACEACTIONBODY;

#define ACDBEVALEXPR_fields                                                   \
  BITCODE_BL ee_class_version;                                                \
  BITCODE_BL ee_major;                                                        \
  BITCODE_BL ee_minor;                                                        \
  BITCODE_BL nodeid;                                                          \
  BITCODE_BSd eval_type;                                                      \
  BITCODE_BD ee_bd40;                                                         \
  BITCODE_2RD ee_2dpt;                                                        \
  BITCODE_3BD ee_3dpt;                                                        \
  BITCODE_T ee_text;                                                          \
  BITCODE_BL ee_bl90;                                                         \
  BITCODE_H ee_h91;                                                           \
  BITCODE_BS ee_bs70

typedef struct _dwg_ACSH_HistoryNode
{
  BITCODE_BL major;    //33
  BITCODE_BL minor;    //29
  BITCODE_BD* trans;   //last 16x nums 40-55
  BITCODE_CMC color;   /*!< DXF 62 */
  BITCODE_BL step_id;  /*!< DXF 92 */
  BITCODE_H  material; /*!< DXF 347 */
} Dwg_ACSH_HistoryNode;

typedef struct _dwg_object_ACSH_HISTORY_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
} Dwg_Object_ACSH_HISTORY_CLASS;

// i.e. planesurf?
typedef struct _dwg_object_ACSH_BOX_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShBox
  BITCODE_BL bl90;       /*!< DXF 90 (33) */
  BITCODE_BL bl91;       /*!< DXF 91 (29) */
  BITCODE_BD length;     /*!< DXF 40 1300.0 (length?) */
  BITCODE_BD width;      /*!< DXF 41 20.0 (width?) */
  BITCODE_BD height;     /*!< DXF 42 420.0 (height?) */

} Dwg_Object_ACSH_BOX_CLASS;

typedef struct _dwg_object_ACSH_WEDGE_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShWedge
  BITCODE_BL bl90;       /*!< DXF 90 (33) */
  BITCODE_BL bl91;       /*!< DXF 91 (29) */
  BITCODE_BD length;     /*!< DXF 40 1300.0 (length?) */
  BITCODE_BD width;      /*!< DXF 41 20.0 (width?) */
  BITCODE_BD height;     /*!< DXF 42 420.0 (height?) */

} Dwg_Object_ACSH_WEDGE_CLASS;

typedef struct _dwg_object_ACSH_BREP_CLASS
{
  struct _dwg_object_object *parent;
  _3DSOLID_FIELDS;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShBrep
  BITCODE_BL bl90;            /*!< DXF 90 */
  BITCODE_BL bl91;            /*!< DXF 91 */

} Dwg_Object_ACSH_BREP_CLASS;

typedef struct _dwg_object_ACSH_SWEEP_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShSweepBase
  BITCODE_BL bl90;            /*!< DXF 90 */
  BITCODE_BL bl91;            /*!< DXF 91 */
  BITCODE_3BD direction;      /*!< DXF 10 */
  BITCODE_BL bl92;            /*!< DXF 92 */
  BITCODE_BL shsw_text_size;  /*!< DXF 90 */
  BITCODE_TF shsw_text;       /*!< DXF 310 */
  BITCODE_BL shsw_bl93;       /*!< DXF 93 */
  BITCODE_BL shsw_text2_size; /*!< DXF 90 */
  BITCODE_TF shsw_text2;      /*!< DXF 310 */
  BITCODE_BD draft_angle;       /*!< DXF 42 0.0 */
  BITCODE_BD start_draft_dist;  /*!< DXF 43 0.0 */
  BITCODE_BD end_draft_dist;    /*!< DXF 44 0.0 */
  BITCODE_BD scale_factor;      /*!< DXF 45 1.0 */
  BITCODE_BD twist_angle;       /*!< DXF 48 0.0 */
  BITCODE_BD align_angle;       /*!< DXF 49 0.0 */
  BITCODE_BD* sweepentity_transform; /*!< DXF 46 16x */
  BITCODE_BD* pathentity_transform;  /*!< DXF 47 16x */
  BITCODE_RC align_option;      /*!< DXF 70 2 */
  BITCODE_RC miter_option;      /*!< DXF 71 2 */
  BITCODE_B has_align_start;    /*!< DXF 290 1 */
  BITCODE_B bank;       /*!< DXF 292 1 */
  BITCODE_B check_intersections; /*!< DXF 293 0 */
  BITCODE_B shsw_b294;  /*!< DXF 294  1 */
  BITCODE_B shsw_b295;  /*!< DXF 295  1 */
  BITCODE_B shsw_b296;  /*!< DXF 296  1 */
  BITCODE_3BD pt2;      /*!< DXF 11 0,0,0 */

  // AcDbShSweep

} Dwg_Object_ACSH_SWEEP_CLASS;

typedef struct _dwg_object_ACSH_EXTRUSION_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShSweepBase
  BITCODE_BL bl90;        /*!< DXF 90 */
  BITCODE_BL bl91;        /*!< DXF 91 */
  BITCODE_3BD direction;  /*!< DXF 10 */
  BITCODE_BL bl92;        /*!< DXF 92 */
  BITCODE_BL shsw_text_size;  /*!< DXF 90 */
  BITCODE_TF shsw_text;       /*!< DXF 310 */
  BITCODE_BL shsw_bl93;       /*!< DXF 93 */
  BITCODE_BL shsw_text2_size; /*!< DXF 90 */
  BITCODE_TF shsw_text2;      /*!< DXF 310 */
  BITCODE_BD draft_angle;       /*!< DXF 42 0.0 */
  BITCODE_BD start_draft_dist;  /*!< DXF 43 0.0 */
  BITCODE_BD end_draft_dist;    /*!< DXF 44 0.0 */
  BITCODE_BD scale_factor;      /*!< DXF 45 1.0 */
  BITCODE_BD twist_angle;       /*!< DXF 48 0.0 */
  BITCODE_BD align_angle;       /*!< DXF 49 0.0 */
  BITCODE_BD* sweepentity_transform; /*!< DXF 46 16x */
  BITCODE_BD* pathentity_transform;  /*!< DXF 47 16x */
  BITCODE_RC align_option;      /*!< DXF 70 2 */
  BITCODE_RC miter_option;      /*!< DXF 71 2 */
  BITCODE_B has_align_start;    /*!< DXF 290 1 */
  BITCODE_B bank;       /*!< DXF 292 1 */
  BITCODE_B check_intersections; /*!< DXF 293 0 */
  BITCODE_B shsw_b294;  /*!< DXF 294  1 */
  BITCODE_B shsw_b295;  /*!< DXF 295  1 */
  BITCODE_B shsw_b296;  /*!< DXF 296  1 */
  BITCODE_3BD pt2;      /*!< DXF 11 0,0,0 */

  // AcDbShExtrusion

} Dwg_Object_ACSH_EXTRUSION_CLASS;

typedef struct _dwg_object_ACSH_LOFT_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShLoft
  BITCODE_BL bl90;       /*!< DXF 90 */
  BITCODE_BL bl91;       /*!< DXF 91 */
  BITCODE_BL num_crosssects; /*!< DXF 92 */
  BITCODE_H *crosssects;
  BITCODE_BL num_guides; /*!< DXF 95 */
  BITCODE_H *guides;

} Dwg_Object_ACSH_LOFT_CLASS;

typedef struct _dwg_object_ACSH_FILLET_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShFillet
  BITCODE_BL bl90;       /*!< DXF 90 */
  BITCODE_BL bl91;       /*!< DXF 91 */
  BITCODE_BL bl92;	 /*!< DXF 92 */
  BITCODE_BL num_edges;	 /*!< DXF 93 */
  BITCODE_BL *edges;     /*!< DXF 94 */
  BITCODE_BL num_radiuses;	/*!< DXF 95 */
  BITCODE_BL num_startsetbacks;	/*!< DXF 96 */
  BITCODE_BL num_endsetbacks;	/*!< DXF 97 */
  BITCODE_BD *radiuses;	        /*!< DXF 41 */
  BITCODE_BD *startsetbacks;	/*!< DXF 42 */
  BITCODE_BD *endsetbacks;	/*!< DXF 43 */

} Dwg_Object_ACSH_FILLET_CLASS;

typedef struct _dwg_object_ACSH_CHAMFER_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShChamfer
  BITCODE_BL bl90;	/*!< DXF 90 */
  BITCODE_BL bl91;	/*!< DXF 91 */
  BITCODE_BL bl92;	/*!< DXF 92 */
  BITCODE_BD base_dist;	/*!< DXF 41 */
  BITCODE_BD other_dist;/*!< DXF 42 */
  BITCODE_BL num_edges;	/*!< DXF 93 */
  BITCODE_BL *edges;    /*!< DXF 94 */
  BITCODE_BL bl95;	/*!< DXF 95 */

} Dwg_Object_ACSH_CHAMFER_CLASS;

typedef struct _dwg_object_ACSH_PYRAMID_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShPyramid
  BITCODE_BL bl90;       /*!< DXF 90 */
  BITCODE_BL bl91;       /*!< DXF 91 */
  BITCODE_BD height;     /*!< DXF 40 */
  BITCODE_BL sides;      /*!< DXF 92 */
  BITCODE_BD radius;     /*!< DXF 41 */
  BITCODE_BD topradius;  /*!< DXF 42 */
} Dwg_Object_ACSH_PYRAMID_CLASS;

typedef struct _dwg_object_ACSH_SPHERE_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShTorus
  BITCODE_BL bl90;	/*!< DXF 90 */
  BITCODE_BL bl91;	/*!< DXF 91 */
  BITCODE_BD radius;	/*!< DXF 40 */

} Dwg_Object_ACSH_SPHERE_CLASS;

typedef struct _dwg_object_ACSH_TORUS_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShTorus
  BITCODE_BL bl90;	/*!< DXF 90 */
  BITCODE_BL bl91;	/*!< DXF 91 */
  BITCODE_BD major_radius;	/*!< DXF 40 */
  BITCODE_BD minor_radius;	/*!< DXF 41 */

} Dwg_Object_ACSH_TORUS_CLASS;

typedef struct _dwg_object_ACSH_REVOLVE_CLASS
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  Dwg_ACSH_HistoryNode history_node;
  // AcDbShPrimitive
  // AcDbShRevolve?
  BITCODE_BL bl90;	/*!< DXF 90 */
  BITCODE_BL bl91;	/*!< DXF 91 */
  BITCODE_3BD axis_pt;	/*!< DXF 10 */
  BITCODE_2RD direction;	/*!< DXF 11 */
  BITCODE_BD revolve_angle;	/*!< DXF 40 */
  BITCODE_BD start_angle;	/*!< DXF 41 */
  BITCODE_BD draft_angle;	/*!< DXF 43 */
  BITCODE_BD bd44;		/*!< DXF 44 */
  BITCODE_BD bd45;		/*!< DXF 45 */
  BITCODE_BD twist_angle;	/*!< DXF 46 */
  BITCODE_B b290;		/*!< DXF 290 */
  BITCODE_B is_close_to_axis;	/*!< DXF 291 */
  BITCODE_H sweep_entity;

} Dwg_Object_ACSH_REVOLVE_CLASS;

// called COORDINATION_MODEL in the DXF docs
typedef struct _dwg_entity_NAVISWORKSMODEL
{
  struct _dwg_object_entity *parent;

  // AcDbNavisworksModel
  BITCODE_H defhandle;		/*!< DXF 340 */
  BITCODE_BD *transmatrix;	/*!< DXF 40 */
  BITCODE_BD unitfactor;	/*!< DXF 40 */

} Dwg_Entity_NAVISWORKSMODEL;

typedef struct _dwg_object_NAVISWORKSMODELDEF
{
  struct _dwg_object_object *parent;

  // AcDbNavisworksModelDef
  BITCODE_T path;       /*!< DXF 1 */
  BITCODE_B status;     /*!< DXF 290 */
  BITCODE_3BD min_extent; /*!< DXF 10 */
  BITCODE_3BD max_extent; /*!< DXF 11 */
  BITCODE_B host_drawing_visibility; /*!< DXF 290 */

} Dwg_Object_NAVISWORKSMODELDEF;

#define RENDERSETTINGS_fields                                                 \
  /* AcDbRenderSettings */                                                    \
  BITCODE_BL class_version;         /*!< DXF 90, default: 1 */                \
  BITCODE_T name;                   /*!< DXF 1 */                             \
  BITCODE_B fog_enabled;            /*!< DXF 290 */                           \
  BITCODE_B fog_background_enabled; /*!< DXF 290 */                           \
  BITCODE_B backfaces_enabled;      /*!< DXF 290 */                           \
  BITCODE_B environ_image_enabled;  /*!< DXF 290 */                           \
  BITCODE_T environ_image_filename; /*!< DXF 1 */                             \
  BITCODE_T description;            /*!< DXF 1 */                             \
  BITCODE_BL display_index;         /*!< DXF 290 */                           \
  BITCODE_B has_predefined          /*!< DXF 290, r2013 only */

/**
 Class RENDERSETTINGS (varies)
 */
typedef struct _dwg_object_RENDERSETTINGS
{
  struct _dwg_object_object *parent;
  RENDERSETTINGS_fields;
} Dwg_Object_RENDERSETTINGS;

/**
 Class MENTALRAYRENDERSETTINGS (varies)
 Unstable
 */
typedef struct _dwg_object_MENTALRAYRENDERSETTINGS
{
  struct _dwg_object_object *parent;
  RENDERSETTINGS_fields;
  // AcDbMentalRayRenderSettings
  BITCODE_BL mr_version;		/*!< DXF 90, always 2 */
  BITCODE_BL sampling1;			/*!< DXF 90 */
  BITCODE_BL sampling2;			/*!< DXF 90 */
  BITCODE_BS sampling_mr_filter;	/*!< DXF 70 */
  BITCODE_BD sampling_filter1;		/*!< DXF 40 */
  BITCODE_BD sampling_filter2;		/*!< DXF 40 */
  BITCODE_BD sampling_contrast_color1;	/*!< DXF 40 */
  BITCODE_BD sampling_contrast_color2;	/*!< DXF 40 */
  BITCODE_BD sampling_contrast_color3;	/*!< DXF 40 */
  BITCODE_BD sampling_contrast_color4;	/*!< DXF 40 */
  BITCODE_BS shadow_mode;		/*!< DXF 70 */
  BITCODE_B  shadow_maps_enabled;	/*!< DXF 290 */
  BITCODE_B  ray_tracing_enabled;	/*!< DXF 290 */
  BITCODE_BL ray_trace_depth1;		/*!< DXF 90 */
  BITCODE_BL ray_trace_depth2;		/*!< DXF 90 */
  BITCODE_BL ray_trace_depth3;		/*!< DXF 90 */
  BITCODE_B  global_illumination_enabled;/*!< DXF 290 */
  BITCODE_BL gi_sample_count;		/*!< DXF 90 */
  BITCODE_B  gi_sample_radius_enabled;	/*!< DXF 290 */
  BITCODE_BD gi_sample_radius;		/*!< DXF 40 */
  BITCODE_BL gi_photons_per_light;	/*!< DXF 90 */
  BITCODE_BL photon_trace_depth1;	/*!< DXF 90 */
  BITCODE_BL photon_trace_depth2;	/*!< DXF 90 */
  BITCODE_BL photon_trace_depth3;	/*!< DXF 90 */
  BITCODE_B  final_gathering_enabled;	/*!< DXF 290 */
  BITCODE_BL fg_ray_count;		/*!< DXF 90 */
  BITCODE_B  fg_sample_radius_state1;	/*!< DXF 290 */
  BITCODE_B  fg_sample_radius_state2;	/*!< DXF 290 */
  BITCODE_B  fg_sample_radius_state3;	/*!< DXF 290 */
  BITCODE_BD fg_sample_radius1;		/*!< DXF 40 */
  BITCODE_BD fg_sample_radius2;		/*!< DXF 40 */
  BITCODE_BD light_luminance_scale;		/*!< DXF 40 */
  BITCODE_BS diagnostics_mode;		/*!< DXF 70 */
  BITCODE_BS diagnostics_grid_mode;	/*!< DXF 70 */
  BITCODE_BD diagnostics_grid_float;	/*!< DXF 40 */
  BITCODE_BS diagnostics_photon_mode;	/*!< DXF 70 */
  BITCODE_BS diagnostics_bsp_mode;	/*!< DXF 70 */
  BITCODE_B  export_mi_enabled;		/*!< DXF 290 */
  BITCODE_T  mr_description;		/*!< DXF 1 */
  BITCODE_BL tile_size;			/*!< DXF 90 */
  BITCODE_BS tile_order;		/*!< DXF 70 */
  BITCODE_BL memory_limit;		/*!< DXF 90 */
  BITCODE_B  diagnostics_samples_mode;	/*!< DXF 290 */
  BITCODE_BD energy_multiplier;		/*!< DXF 40 */
} Dwg_Object_MENTALRAYRENDERSETTINGS;

/**
 Class RAPIDRTRENDERSETTINGS (varies)
 */
typedef struct _dwg_object_RAPIDRTRENDERSETTINGS
{
  struct _dwg_object_object *parent;
  RENDERSETTINGS_fields;
  // AcDbRapidRTRenderSettings
  BITCODE_BL rapidrt_version; /*!< DXF 90 */
  BITCODE_BL render_target;	/*!< DXF 70 */
  BITCODE_BL render_level;	/*!< DXF 90 */
  BITCODE_BL render_time;	/*!< DXF 90 */
  BITCODE_BL lighting_model;	/*!< DXF 70 */
  BITCODE_BL filter_type;	/*!< DXF 70 */
  BITCODE_BD filter_width;	/*!< DXF 40 */
  BITCODE_BD filter_height;	/*!< DXF 40 */
} Dwg_Object_RAPIDRTRENDERSETTINGS;

/**
 Class RENDERENVIRONMENT (varies)
 */
typedef struct _dwg_object_RENDERENVIRONMENT
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;     	/*!< DXF 90, default: 1 */
  BITCODE_B fog_enabled;        	/*!< DXF 290 */
  BITCODE_B fog_background_enabled;  	/*!< DXF 290 */
  BITCODE_CMC fog_color;        	/*!< DXF 280 */
  BITCODE_BD fog_density_near;  	/*!< DXF 40 */
  BITCODE_BD fog_density_far;   	/*!< DXF 40 */
  BITCODE_BD fog_distance_near;     	/*!< DXF 40 */
  BITCODE_BD fog_distance_far;      	/*!< DXF 40 */
  BITCODE_B environ_image_enabled;  	/*!< DXF 290 */
  BITCODE_T environ_image_filename; 	/*!< DXF 1 */
} Dwg_Object_RENDERENVIRONMENT;

/**
 Class RENDERGLOBAL (varies)
 */
typedef struct _dwg_object_RENDERGLOBAL
{
  struct _dwg_object_object *parent;

  BITCODE_BL class_version;    /*!< DXF 90 */
  BITCODE_BL procedure;        /*!< DXF 90 */
  BITCODE_BL destination;      /*!< DXF 90 */
  BITCODE_B save_enabled;      /*!< DXF 290 */
  BITCODE_T save_filename;     /*!< DXF 1 */
  BITCODE_BL image_width;      /*!< DXF 90 */
  BITCODE_BL image_height;     /*!< DXF 90 */
  BITCODE_B predef_presets_first; /*!< DXF 290 */
  BITCODE_B highlevel_info;    /*!< DXF 290 */
} Dwg_Object_RENDERGLOBAL;

/**
 Class RENDERENTRY (varies)
 */
typedef struct _dwg_object_RENDERENTRY
{
  struct _dwg_object_object *parent;
  BITCODE_BL class_version;	/*!< DXF 90 */
  BITCODE_T image_file_name;	/*!< DXF 1 */
  BITCODE_T preset_name;	/*!< DXF 1 */
  BITCODE_T view_name;		/*!< DXF 1 */
  BITCODE_BL dimension_x;	/*!< DXF 90 */
  BITCODE_BL dimension_y;	/*!< DXF 90 */
  BITCODE_BS start_year;	/*!< DXF 70 */
  BITCODE_BS start_month;	/*!< DXF 70 */
  BITCODE_BS start_day;		/*!< DXF 70 */
  BITCODE_BS start_minute;	/*!< DXF 70 */
  BITCODE_BS start_second;	/*!< DXF 70 */
  BITCODE_BS start_msec;	/*!< DXF 70 */
  BITCODE_BD render_time;	/*!< DXF 40 */
  BITCODE_BL memory_amount;	/*!< DXF 90 */
  BITCODE_BL material_count;	/*!< DXF 90 */
  BITCODE_BL light_count;	/*!< DXF 90 */
  BITCODE_BL triangle_count;	/*!< DXF 90 */
  BITCODE_BL display_index;	/*!< DXF 90 */
} Dwg_Object_RENDERENTRY;

/**
 Class MOTIONPATH (varies)
 Maybe all the Camera paths are under ACAD_NAMEDPATH, but there's also ACAD_MOTION
 */
typedef struct _dwg_object_MOTIONPATH
{
  struct _dwg_object_object *parent;
  // AcDbMotionPath
  BITCODE_BS class_version;     /*!< DXF 90, default: 1 */
  BITCODE_H camera_path;        /*!< DXF 340 */
  BITCODE_H target_path;        /*!< DXF 340 */
  BITCODE_H viewtable;          /*!< DXF 340 */
  BITCODE_BS frames;            /*!< DXF 90  number of frames? default 30 */
  BITCODE_BS frame_rate;        /*!< DXF 90  per second, default 30 */
  BITCODE_B corner_decel;       /*!< DXF 290 */
} Dwg_Object_MOTIONPATH;

/**
 Class ACDBCURVEPATH (varies)
 */
typedef struct _dwg_object_CURVEPATH
{
  struct _dwg_object_object *parent;
  // AcDbCurvePath, child of AcDbNamedPath
  BITCODE_BS class_version;     /*!< DXF 90, default: 1 */
  BITCODE_H entity;             /*!< DXF 340 */
} Dwg_Object_CURVEPATH;

/**
 Class ACDBPOINTPATH (varies)
 */
typedef struct _dwg_object_POINTPATH
{
  struct _dwg_object_object *parent;
  // AcDbPointPath, child of AcDbNamedPath
  BITCODE_BS class_version;     /*!< DXF 90, default: 1 */
  BITCODE_3BD point;            /*!< DXF 10 */
} Dwg_Object_POINTPATH;

// not in DXF
typedef struct _dwg_object_TVDEVICEPROPERTIES
{
  struct _dwg_object_object *parent;
  BITCODE_BL flags; /* 1: double_buffer, 2: blocks_cache, 4: multithreaded, 8: sw_hlr
                       16: discard_backfaces, 32: ttf_cache, 64: dyn_subenthlt, 128: force_partial_update
                       256: clear_screen, 512: use_visual_styles (bit 9) 1024: use_overlay_buffers,
                       2048: scene_graph, 4096: composite_meta_files, ??: create_gl_context (bit 13)
                       delay_scenegraphproc (bit 14),
                    */
  BITCODE_BS max_regen_threads;
  BITCODE_BL use_lut_palette;
  BITCODE_BLL alt_hlt;
  BITCODE_BLL alt_hltcolor;
  BITCODE_BLL geom_shader_usage;
  // ver > 3
  BITCODE_BL blending_mode;
  //ver 2 or >4:
  BITCODE_BD antialiasing_level;
  BITCODE_BD bd2;
} Dwg_Object_TVDEVICEPROPERTIES;

// Unhandled, ACAD_BACKGROUND
// one of IBLBACKGROUND, SKY..., IMAGE..., SOLID..., GRADIENT..., GROUNDPLANE...
typedef struct _dwg_object_BACKGROUND
{
  struct _dwg_object_object *parent;
  BITCODE_BL type;     		/*!< DXF 90 */
  // Sky 1:
  BITCODE_H sunid;		/*!< DXF 340 */
  // Solid 1:
  BITCODE_BLx rgb;		/*!< DXF 90 */
  // Image 1:
  BITCODE_T image_filename;	/*!< DXF 300 */
  BITCODE_B fit_to_screen;	/*!< DXF 290 */
  BITCODE_B maintain_aspect_ratio;	/*!< DXF 291 */
  BITCODE_B use_tiling;		/*!< DXF 292 */
  BITCODE_2BD offset;		/*!< DXF 140,141 */
  BITCODE_2BD scale;		/*!< DXF 142,143 */
  // IBL 2:
  BITCODE_B enable;             /*!< DXF 290 */
  BITCODE_T ibl_image_name;     /*!< DXF 1 */
  BITCODE_BD rotation;          /*!< DXF 40, normalized, in degrees */
  BITCODE_B display_image;      /*!< DXF 290 */
  BITCODE_H secondary_background;/*!< DXF 340 */
  // GroundPlane 1:
  BITCODE_BL color_sky_zenith;		/*!< DXF 90 */
  BITCODE_BL color_sky_horizon;		/*!< DXF 91 */
  BITCODE_BL color_underground_horizon;	/*!< DXF 92 */
  BITCODE_BL color_underground_azimuth;	/*!< DXF 93 */
  BITCODE_BL color_groundplane_near;	/*!< DXF 94 */
  BITCODE_BL color_groundplane_far;	/*!< DXF 95 */
} Dwg_Object_BACKGROUND;

/**
 * Class AcDbAnnotScaleObjectContextData (varies)
 * for MTEXT, TEXT, MLEADER, LEADER, BLKREF, ALDIM (AlignedDimension), MTEXTATTRIBUTE, ...
 * R2010+
 * 20.4.89 SubClass AcDbObjectContextData (varies)
 */
#define OBJECTCONTEXTDATA_fields                                              \
  struct _dwg_object_object *parent;                                          \
  BITCODE_BS class_version; /*!< r2010+ =4 */                                 \
  BITCODE_B is_default;     /* no dxf */                                      \
  BITCODE_B in_dwg          /* 290, always 1 */
#define ANNOTSCALEOBJECTCONTEXTDATA_fields                                    \
  OBJECTCONTEXTDATA_fields;                                                   \
  BITCODE_H scale	/*!< DXF 340 */

/**
 * R2010+
 */
typedef struct _dwg_object_OBJECTCONTEXTDATA
{
  OBJECTCONTEXTDATA_fields;
} Dwg_Object_OBJECTCONTEXTDATA;

typedef struct _dwg_CONTEXTDATA_dict
{
  BITCODE_T text;
  BITCODE_H itemhandle;
} Dwg_CONTEXTDATA_dict;

typedef struct _dwg_CONTEXTDATA_submgr
{
  struct _dwg_object_CONTEXTDATAMANAGER *parent;
  BITCODE_H handle;
  BITCODE_BL num_entries;
  Dwg_CONTEXTDATA_dict *entries;
} Dwg_CONTEXTDATA_submgr;

/**
 * R2010+
 * A special DICTIONARY
 */
typedef struct _dwg_object_CONTEXTDATAMANAGER
{
  struct _dwg_object_object *parent;
  BITCODE_H objectcontext;
  BITCODE_BL num_submgrs;
  Dwg_CONTEXTDATA_submgr *submgrs;
} Dwg_Object_CONTEXTDATAMANAGER;

/**
 * R2010+
 */
typedef struct _dwg_object_TEXTOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  BITCODE_BS flag;	/*<! DXF 70 */ // 0
  BITCODE_BD rotation;	/*!< DXF 50 */ // 0.0 or 90.0
  BITCODE_2RD insertion_pt; 	/*!< DXF 10-20 */
  BITCODE_2RD alignment_pt; 	/*!< DXF 11-21 */
} Dwg_Object_TEXTOBJECTCONTEXTDATA;

/**
 * R2010+
 */
typedef struct _dwg_object_MTEXTOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  BITCODE_BS flag;      	/*<! DXF 70 */
  BITCODE_3BD insertion_pt; 	/*!< DXF 11-31 */
  BITCODE_3BD x_axis_dir; 	/*!< DXF 10-30 */
  BITCODE_BD text_height;	/*!< DXF 40 */
  BITCODE_BD rect_width;	/*!< DXF 41 */
  BITCODE_BD rect_height;	/*!< DXF 46 */
  BITCODE_BD extents_height;	/*!< DXF 42 */
  BITCODE_BD extents_width;	/*!< DXF 43 */
  BITCODE_BS attachment;	/*<! DXF 71 */
  BITCODE_BS drawing_dir;  /*!< DXF 72.
                            1 = Left to right, 3 = Top to bottom,
                            5 = By style (the flow direction is inherited
                            from the associated text style) */
  BITCODE_BS linespace_style; /*!< DXF 73. r2000+ */
  BITCODE_BD linespace_factor;/*!< DXF 44. r2000+. Mtext line spacing factor (optional):
                               Percentage of default (3-on-5) line spacing to
                               be applied. Valid values range from 0.25 to 4.00 */
  BITCODE_BD bd45;
  BITCODE_BS bs74;
  BITCODE_BD bd46;
} Dwg_Object_MTEXTOBJECTCONTEXTDATA;

/**
 * for ALDIM (AlignedDimension)
 * R2010+
 */
typedef struct _dwg_object_ALDIMOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  // AcDbDimensionObjectContextData
  BITCODE_T name;	/*!< DXF 2 */
  BITCODE_2RD def_pt; 	/*!< DXF 10-20 */
  BITCODE_B b293;	/*<! DXF 293 */ // 0
  BITCODE_B b294;	/*!< DXF 294 */ // 1
  BITCODE_BD bd140;	/*!< DXF 140 */ // 0.0
  BITCODE_B b298;	/*!< DXF 298 */ // 0
  BITCODE_B b291;	/*!< DXF 291 */ // 0
  BITCODE_BS flag;	/*!< DXF 70 */ // 0
  BITCODE_B b292;	/*!< DXF 292 */ // 0
  BITCODE_BS bs71;	/*!< DXF 71 */ // 0
  BITCODE_B b280;	/*!< DXF 280 */ // 0
  BITCODE_B b295;	/*!< DXF 295 */ // 0
  BITCODE_B b296;	/*!< DXF 296 */ // 0
  BITCODE_B b297;	/*!< DXF 297 */ // 0
  // AcDbAlignedDimensionObjectContextData
  BITCODE_3BD _11pt;    /*!< DXF 11-31 */
} Dwg_Object_ALDIMOBJECTCONTEXTDATA;

typedef struct _dwg_object_MTEXTATTRIBUTEOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  // ??
} Dwg_Object_MTEXTATTRIBUTEOBJECTCONTEXTDATA;

typedef struct _dwg_object_MLEADEROBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  // ...??
} Dwg_Object_MLEADEROBJECTCONTEXTDATA;

typedef struct _dwg_object_LEADEROBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  BITCODE_BL num_points;	/*< DXF 70 */
  BITCODE_3DPOINT* points;	/*!< DXF 10 */
  BITCODE_B b290;		/*!< DXF 290 */
  BITCODE_3DPOINT x_direction;	/*!< DXF 11 */
  BITCODE_3DPOINT inspt_offset;	/*!< DXF 12 */
  BITCODE_3DPOINT endptproj;	/*!< DXF 13 */
} Dwg_Object_LEADEROBJECTCONTEXTDATA;

typedef struct _dwg_object_BLKREFOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  BITCODE_BD rotation;           /* 50 */
  BITCODE_3BD insertion_pt;      /* 10 */
  BITCODE_3BD scale_factor;      /* 42-44 */
} Dwg_Object_BLKREFOBJECTCONTEXTDATA;

typedef struct _dwg_object_FCFOBJECTCONTEXTDATA
{
  ANNOTSCALEOBJECTCONTEXTDATA_fields;
  BITCODE_3BD location;   /*!< DXF 10-30 */
  BITCODE_3BD horiz_dir;  /*!< DXF 11-31 */
} Dwg_Object_FCFOBJECTCONTEXTDATA;

typedef struct _dwg_object_DETAILVIEWSTYLE
{
  struct _dwg_object_object *parent;

  BITCODE_BS class_version; /*!< DXF 70 0 */
  BITCODE_T desc;
  BITCODE_B is_modified_for_recompute;
  BITCODE_T display_name;
  BITCODE_BL viewstyle_flags; /* DXF 90. 1: cannot_rename */

  BITCODE_BL flags;
  BITCODE_H identifier_style;
  BITCODE_CMC identifier_color;
  BITCODE_BD identifier_height;
  BITCODE_T identifier_exclude_characters;
  BITCODE_BD identifier_offset;
  BITCODE_RC identifier_placement;
  BITCODE_H arrow_symbol;
  BITCODE_CMC arrow_symbol_color;
  BITCODE_BD arrow_symbol_size;
  BITCODE_H boundary_ltype;
  BITCODE_BLd boundary_linewt;
  BITCODE_CMC boundary_line_color;
  BITCODE_H viewlabel_text_style;
  BITCODE_CMC viewlabel_text_color;
  BITCODE_BD viewlabel_text_height;
  BITCODE_BL viewlabel_attachment;
  BITCODE_BD viewlabel_offset;
  BITCODE_BL viewlabel_alignment;
  BITCODE_T viewlabel_pattern;
  BITCODE_H connection_ltype;
  BITCODE_BLd connection_linewt;
  BITCODE_CMC connection_line_color;
  BITCODE_H borderline_ltype;
  BITCODE_BLd borderline_linewt;
  BITCODE_CMC borderline_color;
  BITCODE_RC model_edge;
} Dwg_Object_DETAILVIEWSTYLE;

typedef struct _dwg_object_SECTIONVIEWSTYLE
{
  struct _dwg_object_object *parent;

  BITCODE_BS class_version; /*!< DXF 70 0 */
  BITCODE_T desc;
  BITCODE_B is_modified_for_recompute;
  BITCODE_T display_name;
  BITCODE_BL viewstyle_flags; /* DXF 90. 1: cannot_rename */

  BITCODE_BL flags; /* DXF 90. 1: cont_labeling, 2: show_arrowheads, 4: show_viewlabel, 
                       8: show_allplanelines, 0x10: show_allbendids, 0x20 show_end+bendlines
                       0x40: show_hatch ... */
  BITCODE_H identifier_style;
  BITCODE_CMC identifier_color;
  BITCODE_BD identifier_height;
  BITCODE_H arrow_start_symbol;
  BITCODE_H arrow_end_symbol;
  BITCODE_CMC arrow_symbol_color;
  BITCODE_BD arrow_symbol_size;
  BITCODE_T identifier_exclude_characters;
  BITCODE_BLd identifier_position;
  BITCODE_BD identifier_offset;
  BITCODE_BLd arrow_position;
  BITCODE_BD arrow_symbol_extension_length;
  BITCODE_H plane_ltype;
  BITCODE_BLd plane_linewt;
  BITCODE_CMC plane_line_color;
  BITCODE_H bend_ltype;
  BITCODE_BLd bend_linewt;
  BITCODE_CMC bend_line_color;
  BITCODE_BD bend_line_length;
  BITCODE_BD end_line_overshoot;
  BITCODE_BD end_line_length;
  BITCODE_H viewlabel_text_style;
  BITCODE_CMC viewlabel_text_color;
  BITCODE_BD viewlabel_text_height;
  BITCODE_BL viewlabel_attachment;
  BITCODE_BD viewlabel_offset;
  BITCODE_BL viewlabel_alignment;
  BITCODE_T viewlabel_pattern;
  BITCODE_CMC hatch_color;
  BITCODE_CMC hatch_bg_color;
  BITCODE_T hatch_pattern;
  BITCODE_BD hatch_scale;
  BITCODE_BLd hatch_transparency;
  // see flags:
  //BITCODE_B is_continuous_labeling;
  //BITCODE_B show_arrowheads;
  //BITCODE_B show_viewlabel;
  //BITCODE_B show_end_and_bend_lines;
  //BITCODE_B show_hatching;
  BITCODE_B unknown_b1;
  BITCODE_B unknown_b2;
  BITCODE_BL num_hatch_angles;
  BITCODE_BD *hatch_angles;
} Dwg_Object_SECTIONVIEWSTYLE;

typedef struct _dwg_object_SECTION_MANAGER
{
  struct _dwg_object_object *parent;
  BITCODE_B is_live; 		/*!< DXF 70 */
  BITCODE_BS num_sections; 	/*!< DXF 90 */
  BITCODE_H *sections; 		/*!< DXF 330 */
} Dwg_Object_SECTION_MANAGER;

typedef struct _dwg_SECTION_geometrysettings
{
  struct _dwg_SECTION_typesettings *parent;
  BITCODE_BL num_geoms;         /* DXF 90 */
  BITCODE_BL hexindex;          /* DXF 91 */
  BITCODE_BL flags; 		/* DXF 92. 2: hatchvisible, 4: is_hiddenline, 8: has_division_lines */
  BITCODE_CMC color;		/* DXF 62 */
  BITCODE_T layer;		/* DXF 8 Default: 0 */
  BITCODE_T ltype;		/* DXF 6 Default: Continuous */
  BITCODE_BD ltype_scale;	/* DXF 40 */
  BITCODE_T plotstyle;          /* DXF 1 Default: ByColor */
  BITCODE_BLd linewt;		/* DXF 370 */
  BITCODE_BS face_transparency;	/* DXF 70 */
  BITCODE_BS edge_transparency;	/* DXF 71 */
  BITCODE_BS hatch_type;	/* DXF 72 */
  BITCODE_T hatch_pattern;	/* DXF 2 */
  BITCODE_BD hatch_angle;	/* DXF 41 */
  BITCODE_BD hatch_spacing;	/* DXF 42 */
  BITCODE_BD hatch_scale;	/* DXF 43 */
} Dwg_SECTION_geometrysettings;

typedef struct _dwg_SECTION_typesettings
{
  struct _dwg_object_SECTION_SETTINGS *parent;
  BITCODE_BS type;      	/*!< DXF 90: type: live=1, 2d=2, 3d=4 */
  BITCODE_BS generation;  	/*!< DXF 91: source and destination flags.
                                     sourceall=1, sourceselected=2.
                                     destnewblock=16, destreplaceblock=32, destfile=64
                                 */
  /* or geometry: intersectionboundary=1, intersectionfill=2, fg_geom=4, bg_geom=8
                  curvetangencylines=16 */
  BITCODE_BL num_sources;
  BITCODE_H *sources;
  BITCODE_H destblock;
  BITCODE_T destfile;
  BITCODE_BL num_geom;
  Dwg_SECTION_geometrysettings *geom;
} Dwg_SECTION_typesettings;

// Unstable
typedef struct _dwg_object_SECTION_SETTINGS
{
  struct _dwg_object_object *parent;
  BITCODE_BS curr_type;       /* DXF 90 */
  BITCODE_BL num_types;       /* DXF 91 */
  Dwg_SECTION_typesettings *types;
} Dwg_Object_SECTION_SETTINGS;

typedef struct _dwg_object_LAYERFILTER
{
  struct _dwg_object_object *parent;
  BITCODE_BL num_names;
  BITCODE_T *names;
} Dwg_Object_LAYERFILTER;

typedef struct _dwg_entity_ATEXT
{
  struct _dwg_object_entity *parent;
  BITCODE_D2T text_size;	/*!< DXF 42 */
  BITCODE_D2T xscale;		/*!< DXF 41 */
  BITCODE_D2T char_spacing;	/*!< DXF 43 */
  BITCODE_T style;		/*!< DXF 7 */
  BITCODE_T t2;			/*!< DXF 2 */
  BITCODE_T t3;			/*!< DXF 3 */
  BITCODE_T text_value;		/*!< DXF 1 */
  BITCODE_D2T offset_from_arc;	/*!< DXF 44 */
  BITCODE_D2T right_offset;	/*!< DXF 45 */
  BITCODE_D2T left_offset;	/*!< DXF 46 */
  BITCODE_3BD center;		/*!< DXF 10 */
  BITCODE_BD radius;		/*!< DXF 40 */
  BITCODE_BD start_angle;	/*!< DXF 50 */
  BITCODE_BD end_angle;		/*!< DXF 51 */
  BITCODE_3BD extrusion;        /*!< DXF 210 */
  BITCODE_BL color;             /*!< DXF 90 */
  BITCODE_BS is_reverse;	/*!< DXF 70 */
  BITCODE_BS text_direction;	/*!< DXF 71 */
  BITCODE_BS alignment;		/*!< DXF 72 */
  BITCODE_BS text_position;	/*!< DXF 73 */
  BITCODE_BS font_19;		/*!< DXF 74 */
  BITCODE_BS bs2;		/*!< DXF 75 */
  BITCODE_BS is_underlined;	/*!< DXF 76 */
  BITCODE_BS bs1;		/*!< DXF 77 */
  BITCODE_BS font;		/*!< DXF 78 */
  BITCODE_BS is_shx;		/*!< DXF 79 */
  BITCODE_BS wizard_flag;	/*!< DXF 280 */
  BITCODE_H arc_handle;		/*!< DXF 330 */
} Dwg_Entity_ATEXT;

typedef struct _dwg_entity_RTEXT
{
  struct _dwg_object_entity *parent;
  BITCODE_3BD pt;	/*!< DXF 10 */
  BITCODE_BE extrusion;	/*!< DXF 210 */
  BITCODE_BD rotation;	/*!< DXF 50 */
  BITCODE_BD height;	/*!< DXF 50 */
  BITCODE_BS flags;	/*!< DXF 70 */
  BITCODE_T text_value;	/*!< DXF 1 */
  BITCODE_H style;	/*!< DXF 7 */
} Dwg_Entity_RTEXT;

typedef struct _dwg_object_LAYOUTPRINTCONFIG
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version; /* 2 */
  // ...
  BITCODE_BS flag; /*!< DXF 93 0 */
} Dwg_Object_LAYOUTPRINTCONFIG;

typedef struct _dwg_object_ACMECOMMANDHISTORY
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version;
  //?
} Dwg_Object_ACMECOMMANDHISTORY;

typedef struct _dwg_object_ACMESCOPE
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version;
  //?
} Dwg_Object_ACMESCOPE;

typedef struct _dwg_object_ACMESTATEMGR
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version;
  //?
} Dwg_Object_ACMESTATEMGR;

typedef struct _dwg_object_ASSOCGEOMDEPENDENCY
{
  struct _dwg_object_object *parent;
  // AcDbAssocDependency
  BITCODE_BS class_version;			/*<! DXF 90 */
  BITCODE_BS dependent_on_object_status;	/*<! DXF 90 */
  BITCODE_B has_cached_value;			/*<! DXF 290 */
  BITCODE_B is_actionevaluation_in_progress;  	/*<! DXF 290 */
  BITCODE_B is_attached_to_object;		/*<! DXF 290 */
  BITCODE_B is_delegating_to_owning_action;	/*<! DXF 290 */
  BITCODE_BS bs90_2;	/*<! DXF 90 */
  BITCODE_H h330_1;	/*<! DXF 330 */
  BITCODE_B b290_5;	/*<! DXF 290 */
  BITCODE_H h330_2;	/*<! DXF 330 */
  BITCODE_H h330_3;	/*<! DXF 330 */
  BITCODE_H h360;	/*<! DXF 360 */
  BITCODE_BS bs90_3;	/*<! DXF 90 */
  // AcDbAssocGeomDependency
  BITCODE_BS bs90_4;	/*<! DXF 90 */
  BITCODE_B b290_6;	/*<! DXF 290 */
  BITCODE_T t;	/*<! DXF 1 */
  BITCODE_B dependent_on_compound_object;   /*<! DXF 290 */
} Dwg_Object_ASSOCGEOMDEPENDENCY;

typedef struct _dwg_object_CSACDOCUMENTOPTIONS
{
  struct _dwg_object_object *parent;
  BITCODE_BS class_version;
  //?
} Dwg_Object_CSACDOCUMENTOPTIONS;


// dynamic blocks:

typedef struct _dwg_BLOCKVISIBILITYPARAMETER_state
{
  struct _dwg_object_BLOCKVISIBILITYPARAMETER *parent;
  BITCODE_H block;
  BITCODE_BL bl1;
  BITCODE_BL bl2;
} Dwg_BLOCKVISIBILITYPARAMETER_state;

typedef struct _dwg_object_BLOCKVISIBILITYPARAMETER
{
  struct _dwg_object_object *parent;
  BITCODE_B is_initialized;
  BITCODE_B b2;
  BITCODE_T name;
  BITCODE_T desc;
  BITCODE_BL num_states;
  Dwg_BLOCKVISIBILITYPARAMETER_state *states;
} Dwg_Object_BLOCKVISIBILITYPARAMETER;

#define ACDBBLOCKELEMENT_fields \
  BITCODE_T be_t;    \
  BITCODE_BL be_bl1; \
  BITCODE_BL be_bl2; \
  BITCODE_BL be_bl3

typedef struct _dwg_object_BLOCKVISIBILITYGRIP
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  ACDBBLOCKELEMENT_fields;
  // AcDbBlockGrip
  BITCODE_BL bg_bl1;
  BITCODE_BL bg_bl2;
  BITCODE_3BD bg_pt;
  BITCODE_B bg_insert_cycling;
  BITCODE_BL bg_insert_cycling_weight;
  //BITCODE_3BD bg_location; //?
  //BITCODE_3BD bg_display_location; // ?
  // AcDbBlockVisibilityGrip
} Dwg_Object_BLOCKVISIBILITYGRIP;

typedef struct _dwg_object_BLOCKGRIPLOCATIONCOMPONENT
{
  struct _dwg_object_object *parent;
  ACDBEVALEXPR_fields;
  // AcDbBlockGripExpr
  //BITCODE_BL eval_type;
  BITCODE_T evalexpr; // one of: X Y UpdatedX UpdatedY DisplacementX DisplacementY
} Dwg_Object_BLOCKGRIPLOCATIONCOMPONENT;

/**
 -----------------------------------
 */

/**
 Unknown Class entity, a blob
 */
typedef struct _dwg_entity_UNKNOWN_ENT
{
  struct _dwg_object_entity *parent;
} Dwg_Entity_UNKNOWN_ENT;

/**
 Unknown Class object, a blob
 */
typedef struct _dwg_object_UNKNOWN_OBJ
{
  struct _dwg_object_object *parent;
} Dwg_Object_UNKNOWN_OBJ;

/* OBJECTS - END ************************************************************/

/**
 Extended entity data: dxf group - value pairs, similar to xdata
 */
#pragma pack(1)
typedef struct _dwg_entity_eed_data
{
  BITCODE_RC code;
  union eed_data_t {
    struct { /* 0 (1000) string */
      BITCODE_RC length;
      BITCODE_RS codepage;
      char string[1];      /* inlined */
    } eed_0;
    struct { /* R2007+ 0 (1000) string */
      BITCODE_RS length;
      DWGCHAR string[1]; /* inlined */
    } eed_0_r2007;
    struct { /* 1 (1001) invalid */
      char invalid[1]; // set the eed[0].handle to the used APPID instead
    } eed_1;
    struct { /* 2 (1002) { or } */
      BITCODE_RC byte;
    } eed_2;
    struct { /* 3 (1003) layer */
      BITCODE_RL layer;
    } eed_3;
    struct { /* 4 (1004) binary */
      BITCODE_RC length;
      unsigned char data[1]; // inlined
    } eed_4;
    struct { /* 5 (1005) entity */
      BITCODE_RLL entity;
    } eed_5;
    struct { /* 10-13 point */
      BITCODE_3RD point;
    } eed_10;
    struct { /* 40-42 real */
      BITCODE_RD real;
    } eed_40;
    struct { /* 70 short int */
      BITCODE_RS rs;
    } eed_70;
    struct { /* 71 long int */
      BITCODE_RL rl;
    } eed_71;
  } u;
} Dwg_Eed_Data;
#pragma pack()

/**
 Extended entity data
 */
typedef struct _dwg_entity_eed
{
  BITCODE_BS size;
  Dwg_Handle handle;
  Dwg_Eed_Data *data;
  BITCODE_TF raw; /* a binary copy of the data */
} Dwg_Eed;

/**
 Common entity attributes
 */
typedef struct _dwg_object_entity
{
  BITCODE_BL objid; /*!< link to the parent */
  union
  {
    Dwg_Entity_UNUSED *UNUSED;
    Dwg_Entity_TEXT *TEXT;
    Dwg_Entity_ATTRIB *ATTRIB;
    Dwg_Entity_ATTDEF *ATTDEF;
    Dwg_Entity_BLOCK *BLOCK;
    Dwg_Entity_ENDBLK *ENDBLK;
    Dwg_Entity_SEQEND *SEQEND;
    Dwg_Entity_INSERT *INSERT;
    Dwg_Entity_MINSERT *MINSERT;
    Dwg_Entity_VERTEX_2D *VERTEX_2D;
    Dwg_Entity_VERTEX_3D *VERTEX_3D;
    Dwg_Entity_VERTEX_MESH *VERTEX_MESH;
    Dwg_Entity_VERTEX_PFACE *VERTEX_PFACE;
    Dwg_Entity_VERTEX_PFACE_FACE *VERTEX_PFACE_FACE;
    Dwg_Entity_POLYLINE_2D *POLYLINE_2D;
    Dwg_Entity_POLYLINE_3D *POLYLINE_3D;
    Dwg_Entity_ARC *ARC;
    Dwg_Entity_ATEXT *ATEXT;
    Dwg_Entity_CIRCLE *CIRCLE;
    Dwg_Entity_LINE *LINE;
    Dwg_DIMENSION_common *DIMENSION_common;
    Dwg_Entity_DIMENSION_ORDINATE *DIMENSION_ORDINATE;
    Dwg_Entity_DIMENSION_LINEAR *DIMENSION_LINEAR;
    Dwg_Entity_DIMENSION_ALIGNED *DIMENSION_ALIGNED;
    Dwg_Entity_DIMENSION_ANG3PT *DIMENSION_ANG3PT;
    Dwg_Entity_DIMENSION_ANG2LN *DIMENSION_ANG2LN;
    Dwg_Entity_DIMENSION_RADIUS *DIMENSION_RADIUS;
    Dwg_Entity_DIMENSION_DIAMETER *DIMENSION_DIAMETER;
    Dwg_Entity_POINT *POINT;
    Dwg_Entity__3DFACE *_3DFACE;
    Dwg_Entity_POLYLINE_PFACE *POLYLINE_PFACE;
    Dwg_Entity_POLYLINE_MESH *POLYLINE_MESH;
    Dwg_Entity_SOLID *SOLID;
    Dwg_Entity_TRACE *TRACE;
    Dwg_Entity_SHAPE *SHAPE;
    Dwg_Entity_VIEWPORT *VIEWPORT;
    Dwg_Entity_ELLIPSE *ELLIPSE;
    Dwg_Entity_SPLINE *SPLINE;
    Dwg_Entity_3DSOLID *_3DSOLID;
    Dwg_Entity_REGION *REGION;
    Dwg_Entity_BODY *BODY;
    Dwg_Entity_RAY *RAY;
    Dwg_Entity_XLINE *XLINE;
    Dwg_Entity_OLEFRAME *OLEFRAME;
    Dwg_Entity_MTEXT *MTEXT;
    Dwg_Entity_LEADER *LEADER;
    Dwg_Entity_TOLERANCE *TOLERANCE;
    Dwg_Entity_MLINE *MLINE;
    Dwg_Entity_OLE2FRAME *OLE2FRAME;
    Dwg_Entity_HATCH *HATCH;

    Dwg_Entity_CAMERA *CAMERA;
    Dwg_Entity_GEOPOSITIONMARKER *GEOPOSITIONMARKER;
    Dwg_Entity_HELIX *HELIX;
    Dwg_Entity_IMAGE *IMAGE;
    Dwg_Entity_LIGHT *LIGHT;
    Dwg_Entity_LWPOLYLINE *LWPOLYLINE;
    Dwg_Entity_MULTILEADER *MULTILEADER;
    Dwg_Entity_SECTIONOBJECT *SECTIONOBJECT;
    Dwg_Entity_PROXY_ENTITY *PROXY_ENTITY;
    Dwg_Entity_PROXY_LWPOLYLINE *PROXY_LWPOLYLINE;
    Dwg_Entity_NURBSURFACE *NURBSURFACE;
    Dwg_Entity_PLANESURFACE *PLANESURFACE;
    Dwg_Entity_EXTRUDEDSURFACE *EXTRUDEDSURFACE;
    Dwg_Entity_LOFTEDSURFACE *LOFTEDSURFACE;
    Dwg_Entity_REVOLVEDSURFACE *REVOLVEDSURFACE;
    Dwg_Entity_SWEPTSURFACE *SWEPTSURFACE;
    Dwg_Entity_TABLE *TABLE;
    Dwg_Entity_UNDERLAY *UNDERLAY;
    Dwg_Entity_WIPEOUT *WIPEOUT;
    Dwg_Entity_ARC_DIMENSION *ARC_DIMENSION;
    Dwg_Entity_MESH *MESH;
    Dwg_Entity_NAVISWORKSMODEL *NAVISWORKSMODEL;
    Dwg_Entity_RTEXT *RTEXT;

    Dwg_Entity_UNKNOWN_ENT *UNKNOWN_ENT;
  } tio;

  struct _dwg_struct *dwg;
  BITCODE_BL num_eed;
  Dwg_Eed *eed; /* see also Dwg_Resbuf* xdata */

  /* Common Entity Data */
  BITCODE_B   preview_exists;
  BITCODE_B   preview_is_proxy; /* calculated */
  BITCODE_BLL preview_size;     /*!< DXF 160 for bitmaps, DXF 92 for PROXY vector data.
                                  e.g. INSERT, MULTILEADER */
  BITCODE_TF preview;           /*!< DXF 310 */
  BITCODE_BB entmode;           /*!< has no owner handle:
                                  0 has no ownerhandle, 1 is PSPACE, 2 is MSPACE
                                  3 has ownerhandle. */
  BITCODE_BL num_reactors;
  BITCODE_B is_xdic_missing;  /*!< r2004+ */
  BITCODE_B isbylayerlt;        /*!< r13-r14 */
  BITCODE_B nolinks;            /*!< r13-r2000 */
  BITCODE_B has_ds_data;        /*!< r2013+ AcDs datastore */
  BITCODE_CMC color;
  BITCODE_BD ltype_scale;
  BITCODE_BB ltype_flags;       /*!< r2000+ */
  BITCODE_BB plotstyle_flags;   /*!< r2000+ */
  BITCODE_BB material_flags;    /*!< r2007+ */
  BITCODE_RC shadow_flags;      /*!< r2007+: 0 both, 1 casts, 2, receives,
                                  3 has handle. DXF 284 */
  BITCODE_B has_full_visualstyle; /*!< r2010+ */
  BITCODE_B has_face_visualstyle; /*!< r2010+ */
  BITCODE_B has_edge_visualstyle; /*!< r2010+ */
  BITCODE_BS invisible;
  BITCODE_RC linewt;              /*!< r2000+, see dxf_cvt_lweight() */

  /* preR13 entity fields. TODO a union */
  BITCODE_RC flag_r11;
  BITCODE_RS kind_r11;
  BITCODE_RS opts_r11;
  BITCODE_RC extra_r11;
  BITCODE_RS layer_r11;
  BITCODE_RC color_r11;
  BITCODE_RS ltype_r11;
  BITCODE_RD elevation_r11;
  BITCODE_RD thickness_r11;
  BITCODE_RS paper_r11;
  /* preR13 in the obj: eed, elevation/pt.z, thickness, paper */

  /* Common Entity Handle Data */
  BITCODE_BL __iterator;
  BITCODE_H ownerhandle; /*!< mspace, pspace or owner of subentity */
  BITCODE_H* reactors;
  BITCODE_H xdicobjhandle;
  BITCODE_H prev_entity;  /*!< r13-r2000 */
  BITCODE_H next_entity;  /*!< r13-r2000 */
  BITCODE_H layer;
  BITCODE_H ltype;
  BITCODE_H material;     /*!< r2007+ */
  BITCODE_H shadow;       /*!< r2007+ */
  BITCODE_H plotstyle;    /*!< r2000+ */
  BITCODE_H full_visualstyle; /*!< r2010+ */
  BITCODE_H face_visualstyle;
  BITCODE_H edge_visualstyle;
} Dwg_Object_Entity;

/**
 Ordinary object attributes
 */
typedef struct _dwg_object_object
{
  BITCODE_BL objid; /*!< link to the parent */
  union
  {
    Dwg_Object_BLOCK_CONTROL *BLOCK_CONTROL;
    Dwg_Object_BLOCK_HEADER *BLOCK_HEADER;
    Dwg_Object_LAYER_CONTROL *LAYER_CONTROL;
    Dwg_Object_LAYER *LAYER;
    Dwg_Object_STYLE_CONTROL *STYLE_CONTROL;
    Dwg_Object_STYLE *STYLE;
    Dwg_Object_LTYPE_CONTROL *LTYPE_CONTROL;
    Dwg_Object_LTYPE *LTYPE;
    Dwg_Object_VIEW_CONTROL *VIEW_CONTROL;
    Dwg_Object_VIEW *VIEW;
    Dwg_Object_UCS_CONTROL *UCS_CONTROL;
    Dwg_Object_UCS *UCS;
    Dwg_Object_VPORT_CONTROL *VPORT_CONTROL;
    Dwg_Object_VPORT *VPORT;
    Dwg_Object_APPID_CONTROL *APPID_CONTROL;
    Dwg_Object_APPID *APPID;
    Dwg_Object_DIMSTYLE_CONTROL *DIMSTYLE_CONTROL;
    Dwg_Object_DIMSTYLE *DIMSTYLE;
    Dwg_Object_VPORT_ENTITY_CONTROL *VPORT_ENTITY_CONTROL;
    Dwg_Object_VPORT_ENTITY_HEADER *VPORT_ENTITY_HEADER;

    //TODO Dwg_Object_ACDSRECORD *ACDSRECORD;
    //TODO Dwg_Object_ACDSSCHEMA *ACDSSCHEMA;
    Dwg_Object_ACMECOMMANDHISTORY *ACMECOMMANDHISTORY;
    Dwg_Object_ACMESCOPE *ACMESCOPE;
    Dwg_Object_ACMESTATEMGR *ACMESTATEMGR;
    Dwg_Object_ACSH_BOX_CLASS *ACSH_BOX_CLASS;
    Dwg_Object_ACSH_BREP_CLASS *ACSH_BREP_CLASS;
    Dwg_Object_ACSH_CHAMFER_CLASS *ACSH_CHAMFER_CLASS;
    Dwg_Object_ACSH_EXTRUSION_CLASS *ACSH_EXTRUSION_CLASS;
    Dwg_Object_ACSH_FILLET_CLASS *ACSH_FILLET_CLASS;
    Dwg_Object_ACSH_HISTORY_CLASS *ACSH_HISTORY_CLASS;
    Dwg_Object_ACSH_LOFT_CLASS *ACSH_LOFT_CLASS;
    Dwg_Object_ACSH_PYRAMID_CLASS *ACSH_PYRAMID_CLASS;
    Dwg_Object_ACSH_REVOLVE_CLASS *ACSH_REVOLVE_CLASS;
    Dwg_Object_ACSH_SPHERE_CLASS *ACSH_SPHERE_CLASS;
    Dwg_Object_ACSH_SWEEP_CLASS *ACSH_SWEEP_CLASS;
    Dwg_Object_ACSH_TORUS_CLASS *ACSH_TORUS_CLASS;
    Dwg_Object_ACSH_WEDGE_CLASS *ACSH_WEDGE_CLASS;
    Dwg_Object_ASSOC2DCONSTRAINTGROUP *ASSOC2DCONSTRAINTGROUP;
    Dwg_Object_ASSOCACTION *ASSOCACTION;
    Dwg_Object_ASSOCALIGNEDDIMACTIONBODY *ASSOCALIGNEDDIMACTIONBODY;
    Dwg_Object_ASSOCDEPENDENCY *ASSOCDEPENDENCY;
    Dwg_Object_ASSOCGEOMDEPENDENCY *ASSOCGEOMDEPENDENCY;
    Dwg_Object_ASSOCNETWORK *ASSOCNETWORK;
    Dwg_Object_ASSOCOSNAPPOINTREFACTIONPARAM *ASSOCOSNAPPOINTREFACTIONPARAM;
    Dwg_Object_ASSOCVERTEXACTIONPARAM *ASSOCVERTEXACTIONPARAM;
    Dwg_Object_ASSOCPERSSUBENTMANAGER *ASSOCPERSSUBENTMANAGER;
    Dwg_Object_ASSOCEXTRUDEDSURFACEACTIONBODY *ASSOCEXTRUDEDSURFACEACTIONBODY;
    Dwg_Object_ASSOCLOFTEDSURFACEACTIONBODY *ASSOCLOFTEDSURFACEACTIONBODY;
    Dwg_Object_ASSOCPLANESURFACEACTIONBODY *ASSOCPLANESURFACEACTIONBODY;
    Dwg_Object_ASSOCREVOLVEDSURFACEACTIONBODY *ASSOCREVOLVEDSURFACEACTIONBODY;
    Dwg_Object_ASSOCSWEPTSURFACEACTIONBODY *ASSOCSWEPTSURFACEACTIONBODY;
    Dwg_Object_BACKGROUND *BACKGROUND;
    Dwg_Object_BLOCKVISIBILITYPARAMETER *BLOCKVISIBILITYPARAMETER;
    Dwg_Object_BLOCKVISIBILITYGRIP *BLOCKVISIBILITYGRIP;
    Dwg_Object_BLOCKGRIPLOCATIONCOMPONENT *BLOCKGRIPLOCATIONCOMPONENT;
    Dwg_Object_CELLSTYLEMAP *CELLSTYLEMAP;
    Dwg_Object_CONTEXTDATAMANAGER *CONTEXTDATAMANAGER;
    Dwg_Object_CSACDOCUMENTOPTIONS *CSACDOCUMENTOPTIONS;
    Dwg_Object_DATALINK *DATALINK;
    Dwg_Object_DATATABLE *DATATABLE;
    Dwg_Object_DBCOLOR *DBCOLOR;
    Dwg_Object_DETAILVIEWSTYLE *DETAILVIEWSTYLE;
    Dwg_Object_DICTIONARY *DICTIONARY;
    Dwg_Object_DICTIONARYVAR *DICTIONARYVAR;
    Dwg_Object_DICTIONARYWDFLT *DICTIONARYWDFLT;
    Dwg_Object_DIMASSOC *DIMASSOC;
    Dwg_Object_DYNAMICBLOCKPURGEPREVENTER *DYNAMICBLOCKPURGEPREVENTER;
    Dwg_Object_DUMMY *DUMMY;
    Dwg_Object_EVALUATION_GRAPH *EVALUATION_GRAPH;
    Dwg_Object_FIELD *FIELD;
    Dwg_Object_FIELDLIST *FIELDLIST;
    Dwg_Object_GEODATA *GEODATA;
    Dwg_Object_GEOMAPIMAGE *GEOMAPIMAGE;
    Dwg_Object_GROUP *GROUP;
    Dwg_Object_IDBUFFER *IDBUFFER;
    Dwg_Object_IMAGEDEF *IMAGEDEF;
    Dwg_Object_IMAGEDEF_REACTOR *IMAGEDEF_REACTOR;
    Dwg_Object_LAYER_INDEX *LAYER_INDEX;
    Dwg_Object_LAYERFILTER *LAYERFILTER;
    Dwg_Object_LAYOUT *LAYOUT;
    Dwg_Object_LAYOUTPRINTCONFIG *LAYOUTPRINTCONFIG;
    Dwg_Object_LIGHTLIST *LIGHTLIST;
    Dwg_Object_LONG_TRANSACTION *LONG_TRANSACTION;
    Dwg_Object_MATERIAL *MATERIAL;
    Dwg_Object_MLEADERSTYLE *MLEADERSTYLE;
    Dwg_Object_MLINESTYLE *MLINESTYLE;
    Dwg_Object_NAVISWORKSMODELDEF *NAVISWORKSMODELDEF;
    //Dwg_Object_NPOCOLLECTION *NPOCOLLECTION;
    Dwg_Object_ALDIMOBJECTCONTEXTDATA *ALDIMOBJECTCONTEXTDATA;
    Dwg_Object_BLKREFOBJECTCONTEXTDATA *BLKREFOBJECTCONTEXTDATA;
    Dwg_Object_FCFOBJECTCONTEXTDATA *FCFOBJECTCONTEXTDATA;
    Dwg_Object_LEADEROBJECTCONTEXTDATA *LEADEROBJECTCONTEXTDATA;
    Dwg_Object_MENTALRAYRENDERSETTINGS *MENTALRAYRENDERSETTINGS;
    Dwg_Object_MLEADEROBJECTCONTEXTDATA *MLEADEROBJECTCONTEXTDATA;
    Dwg_Object_CURVEPATH *CURVEPATH;
    Dwg_Object_MOTIONPATH *MOTIONPATH;
    Dwg_Object_POINTPATH *POINTPATH;
    Dwg_Object_OBJECTCONTEXTDATA *OBJECTCONTEXTDATA;
    Dwg_Object_MTEXTATTRIBUTEOBJECTCONTEXTDATA *MTEXTATTRIBUTEOBJECTCONTEXTDATA;
    Dwg_Object_MTEXTOBJECTCONTEXTDATA *MTEXTOBJECTCONTEXTDATA;
    Dwg_Object_OBJECT_PTR *OBJECT_PTR;
    Dwg_Object_PERSUBENTMGR *PERSUBENTMGR;
    Dwg_Object_PLACEHOLDER *PLACEHOLDER;
    Dwg_Object_PLOTSETTINGS *PLOTSETTINGS;
    Dwg_Object_PROXY_OBJECT *PROXY_OBJECT;
    Dwg_Object_RASTERVARIABLES *RASTERVARIABLES;
    Dwg_Object_RENDERENVIRONMENT *RENDERENVIRONMENT;
    Dwg_Object_RENDERENTRY *RENDERENTRY;
    Dwg_Object_RENDERGLOBAL *RENDERGLOBAL;
    //Dwg_Object_RAPIDRTRENDERENVIRONMENT *RAPIDRTRENDERENVIRONMENT;
    Dwg_Object_RENDERSETTINGS *RENDERSETTINGS;
    Dwg_Object_RAPIDRTRENDERSETTINGS *RAPIDRTRENDERSETTINGS;
    Dwg_Object_SCALE *SCALE;
    Dwg_Object_SECTION_MANAGER *SECTION_MANAGER;
    Dwg_Object_SECTION_SETTINGS *SECTION_SETTINGS;
    Dwg_Object_SECTIONVIEWSTYLE *SECTIONVIEWSTYLE;
    Dwg_Object_SORTENTSTABLE *SORTENTSTABLE;
    Dwg_Object_SPATIAL_FILTER *SPATIAL_FILTER;
    Dwg_Object_SPATIAL_INDEX *SPATIAL_INDEX;
    Dwg_Object_SUN *SUN;
    Dwg_Object_SUNSTUDY *SUNSTUDY;
    Dwg_Object_TABLECONTENT *TABLECONTENT;
    Dwg_Object_TABLEGEOMETRY *TABLEGEOMETRY;
    Dwg_Object_TABLESTYLE *TABLESTYLE;
    Dwg_Object_TEXTOBJECTCONTEXTDATA *TEXTOBJECTCONTEXTDATA;
    Dwg_Object_TVDEVICEPROPERTIES *TVDEVICEPROPERTIES;
    Dwg_Object_VBA_PROJECT *VBA_PROJECT;
    Dwg_Object_UNDERLAYDEFINITION *UNDERLAYDEFINITION;
    //Dwg_Object_VISIBILITYGRIPENTITY *VISIBILITYGRIPENTITY;
    //Dwg_Object_VISIBILITYPARAMETERENTITY *VISIBILITYPARAMETERENTITY;
    Dwg_Object_VISUALSTYLE *VISUALSTYLE;
    Dwg_Object_WIPEOUTVARIABLES *WIPEOUTVARIABLES;
    Dwg_Object_XRECORD *XRECORD;
    //TODO Dwg_Object_XREFPANELOBJECT *XREFPANELOBJECT;
    Dwg_Object_UNKNOWN_OBJ *UNKNOWN_OBJ;
  } tio;

  struct _dwg_struct *dwg;
  BITCODE_BL num_eed;
  Dwg_Eed *eed;

  BITCODE_H ownerhandle;        /*!< DXF 330 */
  BITCODE_BL num_reactors;
  BITCODE_H* reactors;
  BITCODE_H xdicobjhandle;
  BITCODE_B is_xdic_missing;  /*!< r2004+ */
  BITCODE_B has_ds_data;        /*!< r2013+  AcDs datastore */

  /*unsigned int num_handles;*/
  Dwg_Handle *handleref; //??
} Dwg_Object_Object;

/**
 Classes
 */
typedef struct _dwg_class
{
  BITCODE_BS number; /*!< starting with 500 */
  /* see http://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf */
  BITCODE_BS proxyflag; /*!<
      erase allowed = 1,
      transform allowed = 2,
      color change allowed = 4,
      layer change allowed = 8,
      LTYPE change allowed = 16,
      LTYPE.scale change allowed = 32,
      visibility change allowed = 64,
      cloning allowed = 128,
      Lineweight change allowed = 256,
      PLOTSTYLE Name change allowed = 512,
      Disables proxy warning dialog = 1024,
      is R13 format proxy = 32768 */
  char *appname;
  char *cppname;
  char *dxfname; /*!< ASCII or UTF-8 */
  BITCODE_TU dxfname_u; /*!< r2007+, always transformed to dxfname as UTF-8 */
  BITCODE_B  is_zombie; /*!< i.e. was_proxy, not loaded class */
  BITCODE_BS item_class_id; /*!< really is_entity. 1f2 for entities, 1f3 for objects */
  BITCODE_BL num_instances; /*!< 91 instance count for a custom class */
  BITCODE_BL dwg_version;
  BITCODE_BL maint_version;
  BITCODE_BL unknown_1; /*!< def: 0L */
  BITCODE_BL unknown_2; /*!< def: 0L */
} Dwg_Class;

/**
 General DWG object with link to either entity or object, and as parent the DWG
 */
typedef struct _dwg_object
{
  BITCODE_RL size;       /*!< in bytes */
  unsigned long address; /*!< byte offset in the file */
  unsigned int type;     /*!< fixed or variable (class - 500) */
  BITCODE_RL index;      /*!< into dwg->object[] */
  enum DWG_OBJECT_TYPE fixedtype; /*!< into a global list */
  char *name;            /*!< our public entity/object name */
  char *dxfname;         /*!< the internal dxf classname, often with a ACDB prefix */

  Dwg_Object_Supertype supertype;
  union
  {
    Dwg_Object_Entity *entity;
    Dwg_Object_Object *object;
  } tio;

  Dwg_Handle handle;
  struct _dwg_struct *parent;
  Dwg_Class *klass;          /* the optional class of a variable object */

  BITCODE_RL bitsize;        /* common + object fields, but no handles */
  unsigned long bitsize_pos; /* bitsize offset in bits: r13-2007 */
  unsigned long hdlpos;      /* relative offset, in bits */
  BITCODE_B  was_bitsize_set;    /* internally for encode only */
  BITCODE_B  has_strings;        /*!< r2007+ */
  BITCODE_RL stringstream_size;  /*!< r2007+ in bits, unused */
  BITCODE_UMC handlestream_size; /*!< r2010+ in bits */
  unsigned long common_size; /* relative offset from type ... end common_entity_data */

  BITCODE_RL num_unknown_bits;
  BITCODE_TF unknown_bits;

} Dwg_Object;

/**
 Dwg_Chain similar to Bit_Chain in "bits.h". Used only for the Thumbnail thumbnail
 */
typedef struct _dwg_chain
{
  unsigned char *chain;
  long unsigned int size;
  long unsigned int byte;
  unsigned char bit;
  /* NOT:
  unsigned char opts;
  FILE *fh;
  Dwg_Version_Type version;
  Dwg_Version_Type from_version;
  */
} Dwg_Chain;

typedef enum DWG_SECTION_TYPE /* since r2004+ */
{
  SECTION_UNKNOWN = 0,                  /* The very first 160 byte */
  SECTION_HEADER = 1,                   /* AcDb:Header */
  SECTION_AUXHEADER = 2,                /* AcDb:AuxHeader */
  SECTION_CLASSES = 3,                  /* AcDb:Classes */
  SECTION_HANDLES = 4,                  /* AcDb:Handles */
  SECTION_TEMPLATE = 5,                 /* AcDb:Template */
  SECTION_OBJFREESPACE = 6,             /* AcDb:ObjFreeSpace */
  SECTION_OBJECTS = 7,                  /* AcDb:AcDbObjects */
  SECTION_REVHISTORY = 8,               /* AcDb:RevHistory */
  SECTION_SUMMARYINFO = 9,              /* AcDb:SummaryInfo */
  SECTION_PREVIEW = 10,                 /* AcDb:Preview */
  SECTION_APPINFO = 11,                 /* AcDb:AppInfo */
  SECTION_APPINFOHISTORY = 12,          /* AcDb:AppInfoHistory */
  SECTION_FILEDEPLIST = 13,             /* AcDb:FileDepList */
  SECTION_SECURITY,                     /* AcDb:Security, if stored with a password */
  SECTION_VBAPROJECT,                   /* AcDb:VBAProject */
  SECTION_SIGNATURE,                    /* AcDb:Signature */
  SECTION_ACDS,                         /* AcDb:AcDsPrototype_1b = 12 (ACIS datastorage) */
  SECTION_INFO,                         /* also called Data Section, or Section Page Map (ODA) */
  SECTION_SYSTEM_MAP,
} Dwg_Section_Type;

typedef enum DWG_SECTION_TYPE_R13
{
  SECTION_HEADER_R13 = 0,
  SECTION_CLASSES_R13 = 1,
  SECTION_HANDLES_R13 = 2,
  SECTION_2NDHEADER_R13 = 3,
  SECTION_MEASUREMENT_R13 = 4,
  SECTION_AUXHEADER_R2000 = 5,
} Dwg_Section_Type_R13;

typedef enum DWG_SECTION_TYPE_R11 /* tables */
{
  SECTION_HEADER_R11 = 0,
  SECTION_BLOCK = 1,
  SECTION_LAYER = 2,
  SECTION_STYLE = 3,
  SECTION_LTYPE = 5,
  SECTION_VIEW  = 6,
  SECTION_UCS   = 7,
  SECTION_VPORT = 8,
  SECTION_APPID = 9,
  SECTION_DIMSTYLE = 10,
  SECTION_VPORT_ENTITY = 11,
} Dwg_Section_Type_r11;

typedef struct _dwg_section
{
  int32_t    number; /* preR13: count of entries, r2007: id */
  BITCODE_RL size;   /* now unsigned */
  uint64_t   address;
  BITCODE_RL parent;
  BITCODE_RL left;
  BITCODE_RL right;
  BITCODE_RL x00;
  Dwg_Section_Type type; /* to be casted to Dwg_Section_Type_r11 preR13 */
  /* => section_info? */
  char name[64];
  /*!< r2004 section fields: */
  BITCODE_RL section_type;
  BITCODE_RL decomp_data_size;
  BITCODE_RL comp_data_size;
  BITCODE_RL compression_type;
  BITCODE_RL checksum;
} Dwg_Section;

/* Dwg_R2007_Section:
  int64_t  data_size;    // max size of page
  int64_t  max_size;
  int64_t  encrypted;
  int64_t  hashcode;
  int64_t  name_length;  // 0x22
  int64_t  unknown;      // 0x00
  int64_t  encoded;
  int64_t  num_pages;
  DWGCHAR *name;
  r2007_section_page **pages;
  struct _r2007_section *nextsec;
 */

// ODA 4.5
typedef struct
{
  BITCODE_RL num_desc;
  BITCODE_RL compressed; /* Compressed (1 = no, 2 = yes, normally 2) */
  BITCODE_RL max_size;
  BITCODE_RL encrypted; /* (0 = no, 1 = yes, 2 = unknown) */
  BITCODE_RL num_desc2;
} Dwg_Section_InfoHdr;

typedef struct
{
  int64_t    size;
  BITCODE_RL num_sections;
  BITCODE_RL max_decomp_size;
  BITCODE_RL unknown;
  BITCODE_RL compressed; /* Compressed (1 = no, 2 = yes, normally 2) */
  BITCODE_RL type;       /* The dynamic index as read/written */
  BITCODE_RL encrypted;  /* (0 = no, 1 = yes, 2 = unknown) */
  char name[64];
  Dwg_Section_Type fixedtype;  /* to search for */
  Dwg_Section **sections;
} Dwg_Section_Info;


typedef struct _dwg_SummaryInfo_Property
{
  BITCODE_T key;
  BITCODE_T value;
} Dwg_SummaryInfo_Property;

typedef struct _dwg_FileDepList_Files
{
  BITCODE_T32 filename;
  BITCODE_T32 filepath;
  BITCODE_T32 fingerprint;
  BITCODE_T32 version;
  BITCODE_RL feature_index;
  BITCODE_RL timestamp;
  BITCODE_RL filesize;
  BITCODE_RS affects_graphics;
  BITCODE_RL refcount;
} Dwg_FileDepList_Files;

typedef struct _dwg_AcDs_SegmentIndex
{
  BITCODE_RLL offset;
  BITCODE_RL size;
} Dwg_AcDs_SegmentIndex;

typedef struct _dwg_AcDs_DataIndex_Entry
{
  BITCODE_RL segidx;
  BITCODE_RL offset;
  BITCODE_RL schidx;
} Dwg_AcDs_DataIndex_Entry;

typedef struct _dwg_AcDs_DataIndex
{
  BITCODE_RL num_entries;
  BITCODE_RL di_unknown; // always 0, probably RLL above
  Dwg_AcDs_DataIndex_Entry *entries;
} Dwg_AcDs_DataIndex;

typedef struct _dwg_AcDs_Data_RecordHdr
{
  BITCODE_RL entry_size;
  BITCODE_RL unknown; // mostly 1
  BITCODE_RLL handle;
  BITCODE_RL offset;
} Dwg_AcDs_Data_RecordHdr;

typedef struct _dwg_AcDs_Data_Record
{
  BITCODE_RL data_size;
  BITCODE_RC *blob;
} Dwg_AcDs_Data_Record;

typedef struct _dwg_AcDs_Data
{
  Dwg_AcDs_Data_RecordHdr *record_hdrs;
  Dwg_AcDs_Data_Record *records;
} Dwg_AcDs_Data;

typedef struct _dwg_AcDs_DataBlobRef_Page
{
  BITCODE_RL segidx;
  BITCODE_RL size;
} Dwg_AcDs_DataBlobRef_Page;

typedef struct _dwg_AcDs_DataBlobRef
{
  BITCODE_RLL total_data_size;
  BITCODE_RL num_pages;
  BITCODE_RL record_size;
  BITCODE_RL page_size;
  BITCODE_RL unknown_1; // ODA writes 1
  BITCODE_RL unknown_2; // ODA writes 0
  Dwg_AcDs_DataBlobRef_Page *pages;
} Dwg_AcDs_DataBlobRef;

typedef struct _dwg_AcDs_DataBlob
{
  BITCODE_RLL data_size;
  BITCODE_RL page_count;
  BITCODE_RL record_size;
  BITCODE_RL page_size;
  BITCODE_RL unknown_1; // ODA writes 1
  BITCODE_RL unknown_2; // ODA writes 0
  Dwg_AcDs_DataBlobRef *ref; // only one, optional
} Dwg_AcDs_DataBlob;

typedef struct _dwg_AcDs_DataBlob01
{
  BITCODE_RLL total_data_size;
  BITCODE_RLL page_start_offset;
  int32_t page_index;
  int32_t page_count;
  BITCODE_RLL page_data_size;
  BITCODE_RC *page_data;
} Dwg_AcDs_DataBlob01;

// 24.2.2.5
typedef struct _dwg_AcDs_SchemaIndex_Prop
{
  BITCODE_RL index;
  BITCODE_RL segidx;
  BITCODE_RL offset;
} Dwg_AcDs_SchemaIndex_Prop;

// 24.2.2.5
typedef struct _dwg_AcDs_SchemaIndex
{
  BITCODE_RL num_props; // or uint64
  BITCODE_RL si_unknown_1;
  Dwg_AcDs_SchemaIndex_Prop *props;
  BITCODE_RLL si_tag; /* 0x0af10c */
  BITCODE_RL num_prop_entries;
  BITCODE_RL si_unknown_2; /* 0 */
  Dwg_AcDs_SchemaIndex_Prop *prop_entries;
} Dwg_AcDs_SchemaIndex;

// 24.2.2.6.1.1
typedef struct _dwg_AcDs_Schema_Prop
{
  BITCODE_RL flags;  /*<! DXF 91 */
  BITCODE_RL namidx; /*<! DXF 2 */
  BITCODE_RL type;   /*<! DXF 280, 0-15 */
  BITCODE_RL type_size;
  BITCODE_RL unknown_1;
  BITCODE_RL unknown_2;
  BITCODE_RS num_values;
  BITCODE_RC *values;
} Dwg_AcDs_Schema_Prop;

// 24.2.2.6.1
typedef struct _dwg_AcDs_Schema
{
  BITCODE_RS num_index;
  BITCODE_RLL *index;
  BITCODE_RS num_props;
  Dwg_AcDs_Schema_Prop *props;
} Dwg_AcDs_Schema;

// 24.2.2.6
typedef struct _dwg_AcDs_SchemaData_UProp
{
  BITCODE_RL size;
  BITCODE_RL flags;
} Dwg_AcDs_SchemaData_UProp;

typedef struct _dwg_AcDs_SchemaData
{
  BITCODE_RL num_uprops; // computed, see schidx
  Dwg_AcDs_SchemaData_UProp *uprops;
  BITCODE_RL num_schemas; // computed, see schidx
  Dwg_AcDs_Schema *schemas;
  BITCODE_RL num_propnames;
  BITCODE_TV *propnames;
} Dwg_AcDs_SchemaData;

typedef struct _dwg_AcDs_Search_IdIdx
{
  BITCODE_RLL handle;
  BITCODE_RL num_ididx;
  BITCODE_RLL *ididx;
} Dwg_AcDs_Search_IdIdx;

typedef struct _dwg_AcDs_Search_IdIdxs
{
  BITCODE_RL num_ididx;
  Dwg_AcDs_Search_IdIdx *ididx;
} Dwg_AcDs_Search_IdIdxs;

// 24.2.2.7.1
typedef struct _dwg_AcDs_Search_Data
{
  BITCODE_RL schema_namidx;
  BITCODE_RL num_sortedidx;
  BITCODE_RLL *sortedidx;
  BITCODE_RL num_ididxs;
  BITCODE_RL unknown;
  Dwg_AcDs_Search_IdIdxs *ididxs;
} Dwg_AcDs_Search_Data;

typedef struct _dwg_AcDs_Search
{
  BITCODE_RL num_search;
  Dwg_AcDs_Search_Data *search;
} Dwg_AcDs_Search;

typedef struct _dwg_AcDs_Segment
{
  BITCODE_RL signature; /* always 0xd5ac */
  BITCODE_RC name[7]; /* segidx, datidx, _data_, schidx, schdat, search, blob01 */
  BITCODE_RCd type; /* computed 0-6 or -1 */
  BITCODE_RL segment_idx;
  BITCODE_RL is_blob01;
  BITCODE_RL segsize;
  BITCODE_RL unknown_2;
  BITCODE_RL ds_version; // datastorage revision
  BITCODE_RL unknown_3;
  BITCODE_RL data_algn_offset;
  BITCODE_RL objdata_algn_offset;
  BITCODE_RC padding[9]; // always 8x 0x55
} Dwg_AcDs_Segment;

typedef struct _dwg_AcDs
{
  // header
  BITCODE_RL file_signature;
  BITCODE_RL file_header_size;
  BITCODE_RL unknown_1;  /* acis version? always 2 */
  BITCODE_RL version;    /* always 2 */
  BITCODE_RL unknown_2;  /* always 0 */
  BITCODE_RL ds_version; /* datastorage revision */
  BITCODE_RL segidx_offset;
  BITCODE_RL segidx_unknown;
  BITCODE_RL num_segidx;
  BITCODE_RL schidx_segidx;
  BITCODE_RL datidx_segidx;
  BITCODE_RL search_segidx;
  BITCODE_RL prvsav_segidx;
  BITCODE_RL file_size;
  BITCODE_BL total_segments; // computed
  Dwg_AcDs_SegmentIndex *segidx;
  Dwg_AcDs_DataIndex datidx;
  Dwg_AcDs_Data *data;
  Dwg_AcDs_DataBlob blob01;
  Dwg_AcDs_SchemaIndex schidx;
  Dwg_AcDs_SchemaData schdat;
  Dwg_AcDs_Search search;
  Dwg_AcDs_Segment *segments;
} Dwg_AcDs;

typedef struct _dwg_header
{
  Dwg_Version_Type version;      /* calculated from the header magic */
  Dwg_Version_Type from_version; /* option. set by --as (convert from) */
  BITCODE_RC zero_5[5];
  BITCODE_RC is_maint;
  BITCODE_RC zero_one_or_three;
  BITCODE_RS unknown_s[3];      /* <R13 */
  BITCODE_RL thumbnail_address; /* THUMBNAIL or AdDb:Preview */
  BITCODE_RC dwg_version;
  BITCODE_RC maint_version;
  BITCODE_RS codepage;
  BITCODE_RC unknown_0;           /* R2004+ */
  BITCODE_RC app_dwg_version;     /* R2004+ */
  BITCODE_RC app_maint_version;   /* R2004+ */
  BITCODE_RL security_type;       /* R2004+ */
  BITCODE_RL rl_1c_address;       /* R2004+ mostly 0 */
  BITCODE_RL summaryinfo_address; /* R2004+ */
  BITCODE_RL vbaproj_address;     /* R2004+ */
  BITCODE_RL r2004_header_address; /* R2004+ */
  BITCODE_RL num_sections;
  Dwg_Section *section;
  Dwg_Section_InfoHdr section_infohdr; /* R2004+ */
  Dwg_Section_Info *section_info;
} Dwg_Header;

#pragma pack(1)
typedef struct _dwg_R2004_Header /* encrypted */
{
  BITCODE_RC file_ID_string[12];
  BITCODE_RLx header_address;
  BITCODE_RL header_size;
  BITCODE_RL x04;
  BITCODE_RLd root_tree_node_gap;
  BITCODE_RLd lowermost_left_tree_node_gap;
  BITCODE_RLd lowermost_right_tree_node_gap;
  BITCODE_RL unknown_long;
  BITCODE_RL last_section_id;
  BITCODE_RLL last_section_address;
  BITCODE_RLL second_header_address;
  BITCODE_RL numgaps;
  BITCODE_RL numsections;
  BITCODE_RL x20;
  BITCODE_RL x80;
  BITCODE_RL x40;
  BITCODE_RL section_map_id;
  BITCODE_RLL section_map_address;
  BITCODE_RLd  section_info_id;
  BITCODE_RL section_array_size;
  BITCODE_RL gap_array_size;
  BITCODE_RLx crc32; /* p 2.14.2 32bit CRC 2004+ */
  BITCODE_RC padding[12];
  /* System Section: Section Page Map */
  BITCODE_RL section_type; /* 0x4163043b */
  BITCODE_RL decomp_data_size;
  BITCODE_RL comp_data_size;
  BITCODE_RL compression_type;
  BITCODE_RLx checksum;
} Dwg_R2004_Header;
#pragma pack()

typedef struct _dwg_auxheader
{
  BITCODE_RC aux_intro[3]; /* ff 77 01 */
  BITCODE_RS dwg_version;
  BITCODE_RS maint_version;
  BITCODE_RL numsaves;
  BITCODE_RL minus_1;
  BITCODE_RS numsaves_1;
  BITCODE_RS numsaves_2;
  BITCODE_RL zero;
  BITCODE_RS dwg_version_1;
  BITCODE_RS maint_version_1;
  BITCODE_RS dwg_version_2;
  BITCODE_RS maint_version_2;
  BITCODE_RS unknown_6rs[6];
  BITCODE_RL unknown_5rl[5];
  BITCODE_RD TDCREATE; /* ?? format TD */
  BITCODE_RD TDUPDATE;
  BITCODE_RL HANDSEED;
  BITCODE_RL plot_stamp;
  BITCODE_RS zero_1;
  BITCODE_RS numsaves_3;
  BITCODE_RL zero_2;
  BITCODE_RL zero_3;
  BITCODE_RL zero_4;
  BITCODE_RL numsaves_4;
  BITCODE_RL zero_5;
  BITCODE_RL zero_6;
  BITCODE_RL zero_7;
  BITCODE_RL zero_8;     /* ?? */
  BITCODE_RS zero_18[3]; /* R2018+ */
} Dwg_AuxHeader;

typedef struct _dwg_summaryinfo
{
  BITCODE_T TITLE;
  BITCODE_T SUBJECT;
  BITCODE_T AUTHOR;
  BITCODE_T KEYWORDS;
  BITCODE_T COMMENTS;
  BITCODE_T LASTSAVEDBY;
  BITCODE_T REVISIONNUMBER;
  BITCODE_T HYPERLINKBASE;
  BITCODE_TIMERLL TDINDWG; /* days + ms, fixed size! */
  BITCODE_TIMERLL TDCREATE;
  BITCODE_TIMERLL TDUPDATE;
  BITCODE_RS num_props;
  Dwg_SummaryInfo_Property *props;
  BITCODE_RL unknown1;
  BITCODE_RL unknown2;
} Dwg_SummaryInfo;

/* Contains information about the application that wrote
   the .dwg file (encrypted = 2). */
typedef struct _dwg_appinfo
{
  BITCODE_RL class_version; // 3
  BITCODE_RL num_strings;   // 2-3
  BITCODE_TU appinfo_name;  // AppInfoDataList
  BITCODE_RC version_checksum[16];
  BITCODE_RC comment_checksum[16];
  BITCODE_RC product_checksum[16];
  BITCODE_TU version;      // "19.0.55.0.0", "Teigha(R) 4.3.2.0"
  BITCODE_TU comment;      // "Autodesk DWG.  This file is a Trusted DWG "...
  BITCODE_TU product_info; // XML ProductInformation
} Dwg_AppInfo;

/* File Dependencies, IMAGE files, fonts, xrefs, plotconfigs */
typedef struct _dwg_filedeplist
{
  BITCODE_RL num_features;
  BITCODE_TU32 *features; // Acad:XRef, Acad:Image, Acad:PlotConfig, Acad:Text
  BITCODE_RL num_files;
  Dwg_FileDepList_Files *files;
} Dwg_FileDepList;

/* password info */
typedef struct _dwg_security
{
  BITCODE_RL unknown_1;   // 0xc
  BITCODE_RL unknown_2;   // 0
  BITCODE_RL unknown_3;   // 0xabcdabcd
  BITCODE_RL crypto_id;   //
  BITCODE_TV crypto_name; // "Microsoft Base DSS and Diffie-Hellman
                          // Cryptographic Provider"
  BITCODE_RL algo_id;     // RC4
  BITCODE_RL key_len;     // 40
  BITCODE_RL encr_size;   //
  BITCODE_TF encr_buffer;
} Dwg_Security;

typedef struct _dwg_vbaproject
{
  int size;
  BITCODE_TF unknown_bits;
} Dwg_VBAProject;

typedef struct _dwg_appinfohistory
{
  int size;
  BITCODE_TF unknown_bits;
} Dwg_AppInfoHistory;

typedef struct _dwg_revhistory
{
  BITCODE_RL class_version;
  BITCODE_RL class_minor;
  BITCODE_RL num_histories;
  BITCODE_RL *histories;
} Dwg_RevHistory;

typedef struct _dwg_objfreespace
{
  BITCODE_RLL zero;
  BITCODE_RLL num_handles;
  BITCODE_TIMERLL TDUPDATE;
  BITCODE_RL objects_address;
  BITCODE_RC num_nums; // RLL (uint64_t) or uint128_t
  BITCODE_RLL max32;   // 0x32
  BITCODE_RLL max64;   // 0x64
  BITCODE_RLL maxtbl;  // 0x200
  BITCODE_RLL maxrl;
  BITCODE_RLL max32_hi;
  BITCODE_RLL max64_hi;
  BITCODE_RLL maxtbl_hi;
  BITCODE_RLL maxrl_hi;
} Dwg_ObjFreeSpace;

typedef struct _dwg_template
{
  BITCODE_T16 description;
  BITCODE_RS MEASUREMENT;
} Dwg_Template;

typedef struct _dwg_second_header
{
  BITCODE_RL size;
  BITCODE_RL address;
  BITCODE_RC version[12];
  BITCODE_B null_b[4];
  BITCODE_RC unknown_10;
  BITCODE_RC unknown_rc4[4];
  BITCODE_RC num_sections;
  struct _sections
  {
    BITCODE_RC nr;
    BITCODE_BL address;
    BITCODE_BL size;
  } section[6];
  BITCODE_BS num_handlers;
  struct _handler
  {
    BITCODE_RC size;
    BITCODE_RC nr;
    BITCODE_RC *data;
  } handlers[16];
  BITCODE_RL junk_r14_1; /*!< r14 only */
  BITCODE_RL junk_r14_2; /*!< r14 only */
} Dwg_Second_Header;

/**
 Main DWG struct
 */

typedef struct _dwg_struct
{
  Dwg_Header header;

  BITCODE_BS num_classes;        /*!< number of classes */
  Dwg_Class * dwg_class;         /*!< array of classes */
  BITCODE_BL num_objects;        /*!< number of objects */
  Dwg_Object * object;           /*!< list of all objects and entities */
  BITCODE_BL num_entities;       /*!< number of entities in object */
  BITCODE_BL num_object_refs;    /*!< number of object_ref's (resolved handles) */
  Dwg_Object_Ref **object_ref;   /*!< array of most handles */
  struct _inthash *object_map;   /*!< map of all handles */
  int dirty_refs;                /* 1 if we added an entity, and invalidated all
                                    the internal ref->obj's */
  unsigned int opts;             /* See DWG_OPTS_* below */

  Dwg_Header_Variables header_vars;
  Dwg_Chain thumbnail;

  Dwg_R2004_Header r2004_header; /* encrypted, packed */

  Dwg_Object *mspace_block;
  Dwg_Object *pspace_block;
  /* Those TABLES might be empty with num_entries=0 */
  Dwg_Object_BLOCK_CONTROL      block_control;
  Dwg_Object_LAYER_CONTROL      layer_control;
  Dwg_Object_STYLE_CONTROL      style_control;
  Dwg_Object_LTYPE_CONTROL      ltype_control;
  Dwg_Object_VIEW_CONTROL       view_control;
  Dwg_Object_UCS_CONTROL        ucs_control;
  Dwg_Object_VPORT_CONTROL      vport_control;
  Dwg_Object_APPID_CONTROL      appid_control;
  Dwg_Object_DIMSTYLE_CONTROL   dimstyle_control;
  Dwg_Object_VPORT_ENTITY_CONTROL  vport_entity_control;

  /* #define DWG_AUXHEADER_SIZE 123 */
  Dwg_AuxHeader auxheader;
  Dwg_SummaryInfo summaryinfo;
  /* Contains information about the application that wrote
     the .dwg file (encrypted = 2). */
  Dwg_AppInfo appinfo;
  /* File Dependencies, IMAGE files, fonts, xrefs, plotconfigs */
  Dwg_FileDepList filedeplist;
  Dwg_Security security; /* password info */
  Dwg_VBAProject vbaproject;
  Dwg_AppInfoHistory appinfohistory;
  Dwg_RevHistory revhistory;
  Dwg_ObjFreeSpace objfreespace;
  Dwg_Template Template;
  Dwg_AcDs acds;
  Dwg_Second_Header second_header;

  unsigned int layout_type;
  unsigned int num_acis_sab_hdl;  // temporary, until we can parse acds for SAB data, r2013+
  BITCODE_H *acis_sab_hdl;
} Dwg_Data;

#define DWG_OPTS_LOGLEVEL 0xf
#define DWG_OPTS_MINIMAL  0x10
#define DWG_OPTS_DXFB     0x20
/* can be safely shared */
#define DWG_OPTS_JSONFIRST 0x20
#define DWG_OPTS_INDXF    0x40
#define DWG_OPTS_INJSON   0x80
#define DWG_OPTS_IN       (DWG_OPTS_INDXF | DWG_OPTS_INJSON)

/*--------------------------------------------------
 * Exported Functions
 */

EXPORT int dwg_read_file (const char *restrict filename,
                          Dwg_Data *restrict dwg);
EXPORT int dxf_read_file (const char *restrict filename,
                          Dwg_Data *restrict dwg);

#ifdef USE_WRITE
EXPORT int dwg_write_file (const char *restrict filename,
                           const Dwg_Data *restrict dwg);
#endif

EXPORT unsigned char *dwg_bmp (const Dwg_Data *restrict, BITCODE_RL *restrict);

/** Converts the internal enum RC into 100th mm lineweight, with
 *  -1 BYLAYER, -2 BYBLOCK, -3 BYLWDEFAULT.
 */
EXPORT int dxf_cvt_lweight (const BITCODE_BSd value);

/** Converts the 100th mm lineweight, with -1 BYLAYER, -2 BYBLOCK, -3 BYLWDEFAULT,
    into the internal enum RC.
 */
EXPORT BITCODE_BSd dxf_revcvt_lweight (const int lw);

/* Return the matching _CONTROL table, or NULL
 */
EXPORT BITCODE_H
dwg_ctrl_table (Dwg_Data *restrict dwg, const char *restrict table);

/* Search for the name in the associated table, and return its handle. Search
 * is case-insensitive.
 * Both name and table are ascii.
 */
EXPORT BITCODE_H dwg_find_tablehandle (Dwg_Data *restrict dwg,
                                       const char *restrict name,
                                       const char *restrict table);


/* Search for handle in associated table, and return its name. */
EXPORT char*
dwg_handle_name (Dwg_Data *restrict dwg, const char *restrict table,
                 const BITCODE_H restrict handle);

/** Not checking the header_vars entry, only searching the objects
 *  Returning a hardowner or hardpointer (DICTIONARY) ref (code 3 or 5)
 *  to it, as stored in header_vars. table must contain the "_CONTROL" suffix.
 *  table is ascii.
 */
EXPORT BITCODE_H dwg_find_table_control (Dwg_Data *restrict dwg,
                                         const char *restrict table);

/** Search for a dictionary ref.
 *  Returning a hardpointer ref (5) to it, as stored in header_vars.
 *  Name is ascii.
 */
EXPORT BITCODE_H dwg_find_dictionary (Dwg_Data *restrict dwg,
                                      const char *restrict name);
/** Search for a named dictionary entry in the given dict.
 *  Search is case-sensitive. name is ASCII. */
EXPORT BITCODE_H dwg_find_dicthandle (Dwg_Data *restrict dwg, BITCODE_H dict,
                                      const char *restrict name);
/** Search all dictionary entries in the given dict.
 *  Check for the matching name of the handle object. (Control lists).
 *  Search is case-insensitive */
EXPORT BITCODE_H dwg_find_dicthandle_objname (Dwg_Data *restrict dwg, BITCODE_H dict,
                                              const char *restrict name);
/* Search for a table EXTNAME */
EXPORT char *dwg_find_table_extname (Dwg_Data *restrict dwg,
                                     Dwg_Object *restrict obj);
/* Returns the string value of the member of the AcDbVariableDictionary.
   The name is ascii. E.g. LIGHTINGUNITS => "0" */
EXPORT char *dwg_variable_dict (Dwg_Data *restrict dwg,
                                const char *restrict name);

EXPORT double dwg_model_x_min (const Dwg_Data *restrict);
EXPORT double dwg_model_x_max (const Dwg_Data *restrict);
EXPORT double dwg_model_y_min (const Dwg_Data *restrict);
EXPORT double dwg_model_y_max (const Dwg_Data *restrict);
EXPORT double dwg_model_z_min (const Dwg_Data *restrict);
EXPORT double dwg_model_z_max (const Dwg_Data *restrict);
EXPORT double dwg_page_x_min (const Dwg_Data *restrict);
EXPORT double dwg_page_x_max (const Dwg_Data *restrict);
EXPORT double dwg_page_y_min (const Dwg_Data *restrict);
EXPORT double dwg_page_y_max (const Dwg_Data *restrict);

EXPORT Dwg_Object_BLOCK_CONTROL * dwg_block_control (Dwg_Data *restrict dwg);

EXPORT Dwg_Object_Ref * dwg_model_space_ref (Dwg_Data *restrict dwg);
EXPORT Dwg_Object_Ref * dwg_paper_space_ref (Dwg_Data *restrict dwg);
EXPORT Dwg_Object * dwg_model_space_object (Dwg_Data *restrict dwg);

EXPORT unsigned int dwg_get_layer_count (const Dwg_Data *restrict dwg);

EXPORT Dwg_Object_LAYER ** dwg_get_layers (const Dwg_Data *restrict dwg);

EXPORT BITCODE_BL dwg_get_num_objects (const Dwg_Data *restrict dwg);

EXPORT BITCODE_BL dwg_get_object_num_objects (const Dwg_Data *restrict dwg);

EXPORT int dwg_class_is_entity (const Dwg_Class *restrict klass);

EXPORT int dwg_obj_is_control (const Dwg_Object *restrict obj);

EXPORT int dwg_obj_is_table (const Dwg_Object *restrict obj);

EXPORT int dwg_obj_is_subentity (const Dwg_Object *restrict obj);

EXPORT int dwg_obj_has_subentity (const Dwg_Object *restrict obj);

EXPORT int dwg_obj_is_3dsolid (const Dwg_Object *restrict obj);

EXPORT BITCODE_BL dwg_get_num_entities (const Dwg_Data *restrict);

EXPORT Dwg_Object_Entity **dwg_get_entities (const Dwg_Data *restrict);

EXPORT Dwg_Object_LAYER *
dwg_get_entity_layer (const Dwg_Object_Entity *restrict);

EXPORT Dwg_Object *dwg_next_object (const Dwg_Object *obj);
EXPORT Dwg_Object *dwg_next_entity (const Dwg_Object *obj);

EXPORT Dwg_Object *dwg_ref_object (const Dwg_Data *restrict dwg,
                                   Dwg_Object_Ref *restrict ref);

EXPORT Dwg_Object *dwg_ref_object_relative (const Dwg_Data *restrict dwg,
                                            Dwg_Object_Ref *restrict ref,
                                            const Dwg_Object *restrict obj);
EXPORT Dwg_Object *dwg_ref_object_silent (const Dwg_Data *restrict dwg,
                                          Dwg_Object_Ref *restrict ref);

EXPORT Dwg_Object *get_first_owned_entity (const Dwg_Object *restrict hdr);
EXPORT Dwg_Object *get_next_owned_entity (const Dwg_Object *restrict hdr,
                                          const Dwg_Object *restrict current);
EXPORT Dwg_Object *get_first_owned_subentity (const Dwg_Object *restrict owner);
EXPORT Dwg_Object *get_next_owned_subentity (const Dwg_Object *restrict owner,
                                             const Dwg_Object *restrict current);
EXPORT Dwg_Object *get_first_owned_block (const Dwg_Object *hdr);
EXPORT Dwg_Object *get_last_owned_block (const Dwg_Object *hdr);
EXPORT Dwg_Object *get_next_owned_block (const Dwg_Object *restrict hdr,
                                         const Dwg_Object *restrict current);
EXPORT Dwg_Object *get_next_owned_block_entity (const Dwg_Object *restrict hdr,
                                                const Dwg_Object *restrict current);

EXPORT Dwg_Object *dwg_resolve_handle (const Dwg_Data *restrict dwg,
                                       const unsigned long absref);
EXPORT Dwg_Object *dwg_resolve_handle_silent (const Dwg_Data *restrict dwg,
                                              const BITCODE_BL absref);
EXPORT int dwg_resolve_handleref (Dwg_Object_Ref *restrict ref,
                                  const Dwg_Object *restrict obj);

EXPORT Dwg_Section_Type dwg_section_type (const char *restrict name);
EXPORT Dwg_Section_Type dwg_section_wtype (const DWGCHAR *restrict wname);
EXPORT const char *dwg_section_name (const Dwg_Data *dwg, const unsigned int sec_id);

/** Free the whole DWG. all tables, sections, objects, ...
*/
EXPORT void dwg_free (Dwg_Data *restrict dwg);

/** Free the object (all three structs and its fields)
*/
EXPORT void dwg_free_object (Dwg_Object *restrict obj);

/** Add the empty ref to the DWG (freshly malloc'ed), or NULL.
*/
EXPORT Dwg_Object_Ref * dwg_new_ref (Dwg_Data *restrict dwg);

/** For encode:
 *  May need obj to shorten the code to a relative offset, but not in header_vars.
 *  There obj is NULL.
 */
EXPORT int dwg_add_handle (Dwg_Handle *restrict hdl, const BITCODE_RC code,
                           const unsigned long value,
                           const Dwg_Object *restrict obj);

/** Returns an existing ref with the same ownership (hard/soft, owner/pointer)
    or creates it. With obj non-NULL it may return a relative offset, otherwise
    always absolute.
*/
EXPORT Dwg_Object_Ref *dwg_add_handleref (Dwg_Data *restrict dwg,
                                          const BITCODE_RC code,
                                          const unsigned long value,
                                          const Dwg_Object *restrict obj);
/* Creates a non-global, free'able handle ref. Never relative */
EXPORT Dwg_Object_Ref *
dwg_add_handleref_free (const BITCODE_RC code, const unsigned long absref);

EXPORT const char *dwg_version_type (const Dwg_Version_Type version);
EXPORT Dwg_Version_Type dwg_version_as (const char *version);
EXPORT void dwg_errstrings (int error);

EXPORT char *dwg_encrypt_SAT1 (BITCODE_BL blocksize,
                               BITCODE_RC *restrict acis_data,
                               int *restrict acis_data_offset);
/* Converts v2 SAB acis_data in-place to SAT v1 encr_sat_data[].
   Sets _obj->_dxf_sab_converted to 1, denoting that encr_sat_data is NOT the
   encrypted acis_data anymore, rather the converted from SAB for DXF */
EXPORT int dwg_convert_SAB_to_SAT1 (Dwg_Entity_3DSOLID *restrict _obj);


/* The old color.index 0-256 */
typedef struct rgbpalette {
  unsigned char r,g,b;
} Dwg_RGB_Palette;
EXPORT const Dwg_RGB_Palette *dwg_rgb_palette (void);
/* find a matching color index (0-255) for a truecolor rgb value.
   returns 256 if not found, i.e. the default ByLayer.
 */
EXPORT BITCODE_BS dwg_find_color_index (BITCODE_BL rgb);

/** Add the empty object to the DWG.
    Returns DWG_ERR_OUTOFMEM, -1 for realloced or 0 if not.
    objects are allocated in bulk, and all old obj pointers may become invalid.
    The new object is at &dwg->object[dwg->num_objects - 1].
*/
EXPORT int dwg_add_object (Dwg_Data *restrict dwg);

/** Initialize the empty entity or object with its three structs.
    All fields are zero'd, some are initialized with default values, as
    defined in dwg.spec. obj->fixedtype is set, obj->type only for static types.
    Use dwg_encode_get_class for the variable types.
    Returns 0 or DWG_ERR_OUTOFMEM.
*/
EXPORT int dwg_setup_TEXT (Dwg_Object *obj);
EXPORT int dwg_setup_ATTRIB (Dwg_Object *obj);
EXPORT int dwg_setup_ATTDEF (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCK (Dwg_Object *obj);
EXPORT int dwg_setup_ENDBLK (Dwg_Object *obj);
EXPORT int dwg_setup_SEQEND (Dwg_Object *obj);
EXPORT int dwg_setup_INSERT (Dwg_Object *obj);
EXPORT int dwg_setup_MINSERT (Dwg_Object *obj);
EXPORT int dwg_setup_VERTEX_2D (Dwg_Object *obj);
EXPORT int dwg_setup_VERTEX_3D (Dwg_Object *obj);
EXPORT int dwg_setup_VERTEX_MESH (Dwg_Object *obj);
EXPORT int dwg_setup_VERTEX_PFACE (Dwg_Object *obj);
EXPORT int dwg_setup_VERTEX_PFACE_FACE (Dwg_Object *obj);
EXPORT int dwg_setup_POLYLINE_2D (Dwg_Object *obj);
EXPORT int dwg_setup_POLYLINE_3D (Dwg_Object *obj);
EXPORT int dwg_setup_ARC (Dwg_Object *obj);
EXPORT int dwg_setup_CIRCLE (Dwg_Object *obj);
EXPORT int dwg_setup_LINE (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_ORDINATE (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_LINEAR (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_ALIGNED (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_ANG3PT (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_ANG2LN (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_RADIUS (Dwg_Object *obj);
EXPORT int dwg_setup_DIMENSION_DIAMETER (Dwg_Object *obj);
EXPORT int dwg_setup_POINT (Dwg_Object *obj);
EXPORT int dwg_setup__3DFACE (Dwg_Object *obj);
EXPORT int dwg_setup__3DSOLID (Dwg_Object *obj);
EXPORT int dwg_setup_POLYLINE_PFACE (Dwg_Object *obj);
EXPORT int dwg_setup_POLYLINE_MESH (Dwg_Object *obj);
EXPORT int dwg_setup_SOLID (Dwg_Object *obj);
EXPORT int dwg_setup_TRACE (Dwg_Object *obj);
EXPORT int dwg_setup_SHAPE (Dwg_Object *obj);
EXPORT int dwg_setup_VIEWPORT (Dwg_Object *obj);
EXPORT int dwg_setup_ELLIPSE (Dwg_Object *obj);
EXPORT int dwg_setup_SPLINE (Dwg_Object *obj);
EXPORT int dwg_setup_REGION (Dwg_Object *obj);
EXPORT int dwg_setup_BODY (Dwg_Object *obj);
EXPORT int dwg_setup_RAY (Dwg_Object *obj);
EXPORT int dwg_setup_XLINE (Dwg_Object *obj);
EXPORT int dwg_setup_DICTIONARY (Dwg_Object *obj);
EXPORT int dwg_setup_OLEFRAME (Dwg_Object *obj);
EXPORT int dwg_setup_MTEXT (Dwg_Object *obj);
EXPORT int dwg_setup_LEADER (Dwg_Object *obj);
EXPORT int dwg_setup_TOLERANCE (Dwg_Object *obj);
EXPORT int dwg_setup_MLINE (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCK_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCK_HEADER (Dwg_Object *obj);
EXPORT int dwg_setup_LAYER_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_LAYER (Dwg_Object *obj);
EXPORT int dwg_setup_STYLE_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_STYLE (Dwg_Object *obj);
EXPORT int dwg_setup_LTYPE_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_LTYPE (Dwg_Object *obj);
EXPORT int dwg_setup_VIEW_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_VIEW (Dwg_Object *obj);
EXPORT int dwg_setup_UCS_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_UCS (Dwg_Object *obj);
EXPORT int dwg_setup_VPORT_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_VPORT (Dwg_Object *obj);
EXPORT int dwg_setup_APPID_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_APPID (Dwg_Object *obj);
EXPORT int dwg_setup_DIMSTYLE_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_DIMSTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_VPORT_ENTITY_CONTROL (Dwg_Object *obj);
EXPORT int dwg_setup_VPORT_ENTITY_HEADER (Dwg_Object *obj);
EXPORT int dwg_setup_GROUP (Dwg_Object *obj);
EXPORT int dwg_setup_MLINESTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_OLE2FRAME (Dwg_Object *obj);
EXPORT int dwg_setup_DUMMY (Dwg_Object *obj);
EXPORT int dwg_setup_LONG_TRANSACTION (Dwg_Object *obj);
EXPORT int dwg_setup_LWPOLYLINE (Dwg_Object *obj);
EXPORT int dwg_setup_GEODATA (Dwg_Object *obj);
EXPORT int dwg_setup_HATCH (Dwg_Object *obj);
EXPORT int dwg_setup_XRECORD (Dwg_Object *obj);
EXPORT int dwg_setup_PLACEHOLDER (Dwg_Object *obj);
EXPORT int dwg_setup_LAYOUT (Dwg_Object *obj);
EXPORT int dwg_setup_PROXY_ENTITY (Dwg_Object *obj);
EXPORT int dwg_setup_PROXY_OBJECT (Dwg_Object *obj);
EXPORT int dwg_setup_UNKNOWN_ENT (Dwg_Object *obj);
EXPORT int dwg_setup_UNKNOWN_OBJ (Dwg_Object *obj);

/* STABLE: */
EXPORT int dwg_setup_CELLSTYLEMAP (Dwg_Object *obj);
EXPORT int dwg_setup_DICTIONARYVAR (Dwg_Object *obj);
EXPORT int dwg_setup_DICTIONARYWDFLT (Dwg_Object *obj);
EXPORT int dwg_setup_DYNAMICBLOCKPURGEPREVENTER (Dwg_Object *obj);
EXPORT int dwg_setup_FIELD (Dwg_Object *obj);
EXPORT int dwg_setup_FIELDLIST (Dwg_Object *obj);
EXPORT int dwg_setup_IDBUFFER (Dwg_Object *obj);
EXPORT int dwg_setup_IMAGE (Dwg_Object *obj);
EXPORT int dwg_setup_IMAGEDEF (Dwg_Object *obj);
EXPORT int dwg_setup_IMAGEDEF_REACTOR (Dwg_Object *obj);
EXPORT int dwg_setup_LAYER_INDEX (Dwg_Object *obj);
EXPORT int dwg_setup_MLEADERSTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_RASTERVARIABLES (Dwg_Object *obj);
EXPORT int dwg_setup_SCALE (Dwg_Object *obj);
EXPORT int dwg_setup_SECTION_MANAGER (Dwg_Object *obj);
EXPORT int dwg_setup_SECTIONOBJECT (Dwg_Object *obj);
EXPORT int dwg_setup_SORTENTSTABLE (Dwg_Object *obj);
EXPORT int dwg_setup_SPATIAL_FILTER (Dwg_Object *obj);
EXPORT int dwg_setup_SPATIAL_INDEX (Dwg_Object *obj);
EXPORT int dwg_setup_VBA_PROJECT (Dwg_Object *obj);
EXPORT int dwg_setup_WIPEOUTVARIABLES (Dwg_Object *obj);
EXPORT int dwg_setup_WIPEOUT (Dwg_Object *obj);

/* UNSTABLE: */
EXPORT int dwg_setup_ARC_DIMENSION (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCDEPENDENCY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCALIGNEDDIMACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCPLANESURFACEACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_CAMERA (Dwg_Object *obj);
EXPORT int dwg_setup_DETAILVIEWSTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_DIMASSOC (Dwg_Object *obj);
EXPORT int dwg_setup_DBCOLOR (Dwg_Object *obj);
EXPORT int dwg_setup_HELIX (Dwg_Object *obj);
EXPORT int dwg_setup_LAYERFILTER (Dwg_Object *obj);
EXPORT int dwg_setup_LIGHT (Dwg_Object *obj);
EXPORT int dwg_setup_LIGHTLIST (Dwg_Object *obj);
EXPORT int dwg_setup_MATERIAL (Dwg_Object *obj);
EXPORT int dwg_setup_MENTALRAYRENDERSETTINGS (Dwg_Object *obj);
EXPORT int dwg_setup_MESH (Dwg_Object *obj);
EXPORT int dwg_setup_MULTILEADER (Dwg_Object *obj);
EXPORT int dwg_setup_OBJECT_PTR (Dwg_Object *obj);
EXPORT int dwg_setup_PERSUBENTMGR (Dwg_Object *obj);
EXPORT int dwg_setup_PLOTSETTINGS (Dwg_Object *obj);
EXPORT int dwg_setup_RENDERSETTINGS (Dwg_Object *obj);
EXPORT int dwg_setup_RAPIDRTRENDERSETTINGS (Dwg_Object *obj);
EXPORT int dwg_setup_SECTION_SETTINGS (Dwg_Object *obj);
EXPORT int dwg_setup_SECTIONVIEWSTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_SUN (Dwg_Object *obj);
EXPORT int dwg_setup_TABLEGEOMETRY (Dwg_Object *obj);
EXPORT int dwg_setup_TABLESTYLE (Dwg_Object *obj);
EXPORT int dwg_setup_UNDERLAY (Dwg_Object *obj);
EXPORT int dwg_setup_UNDERLAYDEFINITION (Dwg_Object *obj);
EXPORT int dwg_setup_VISUALSTYLE (Dwg_Object *obj);

#ifdef DEBUG_CLASSES

/* DEBUGGING and UNHANDLED: */
EXPORT int dwg_setup_ASSOC2DCONSTRAINTGROUP (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCACTION (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCNETWORK (Dwg_Object *obj);
//EXPORT int dwg_setup_ACDSRECORD (Dwg_Object *obj);
//EXPORT int dwg_setup_ACDSSCHEMA (Dwg_Object *obj);
int dwg_setup_ACMECOMMANDHISTORY (Dwg_Object *obj);
int dwg_setup_ACMESCOPE (Dwg_Object *obj);
int dwg_setup_ACMESTATEMGR (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_BOX_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_BREP_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_EXTRUSION_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_HISTORY_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_SWEEP_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_CHAMFER_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_FILLET_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_LOFT_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_PYRAMID_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_REVOLVE_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_SPHERE_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_TORUS_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ACSH_WEDGE_CLASS (Dwg_Object *obj);
EXPORT int dwg_setup_ATEXT (Dwg_Object *obj);
EXPORT int dwg_setup_CONTEXTDATAMANAGER (Dwg_Object *obj);
EXPORT int dwg_setup_OBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_ALDIMOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_BLKREFOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_FCFOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_LEADEROBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_MLEADEROBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_MTEXTATTRIBUTEOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_MTEXTOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_TEXTOBJECTCONTEXTDATA (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCGEOMDEPENDENCY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCEXTRUDEDSURFACEACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCLOFTEDSURFACEACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCREVOLVEDSURFACEACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCSWEPTSURFACEACTIONBODY (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCOSNAPPOINTREFACTIONPARAM (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCPERSSUBENTMANAGER (Dwg_Object *obj);
EXPORT int dwg_setup_ASSOCVERTEXACTIONPARAM (Dwg_Object *obj);
EXPORT int dwg_setup_DATALINK (Dwg_Object *obj);
EXPORT int dwg_setup_DATATABLE (Dwg_Object *obj);
EXPORT int dwg_setup_EVALUATION_GRAPH (Dwg_Object *obj);
EXPORT int dwg_setup_GEOMAPIMAGE (Dwg_Object *obj);
EXPORT int dwg_setup_GEOPOSITIONMARKER (Dwg_Object *obj);
EXPORT int dwg_setup_LAYOUTPRINTCONFIG (Dwg_Object *obj);
EXPORT int dwg_setup_NAVISWORKSMODEL (Dwg_Object *obj);
EXPORT int dwg_setup_NAVISWORKSMODELDEF (Dwg_Object *obj);
EXPORT int dwg_setup_NPOCOLLECTION (Dwg_Object *obj);
//EXPORT int dwg_setup_POINTCLOUD (Dwg_Object *obj);
EXPORT int dwg_setup_CSACDOCUMENTOPTIONS (Dwg_Object *obj);
EXPORT int dwg_setup_RENDERENVIRONMENT (Dwg_Object *obj);
EXPORT int dwg_setup_RENDERENTRY (Dwg_Object *obj);
EXPORT int dwg_setup_RENDERGLOBAL (Dwg_Object *obj);
EXPORT int dwg_setup_CURVEPATH (Dwg_Object *obj);
EXPORT int dwg_setup_MOTIONPATH (Dwg_Object *obj);
EXPORT int dwg_setup_POINTPATH (Dwg_Object *obj);
//EXPORT int dwg_setup_RAPIDRTRENDERENVIRONMENT (Dwg_Object *obj);
EXPORT int dwg_setup_BACKGROUND (Dwg_Object *obj);
EXPORT int dwg_setup_TVDEVICEPROPERTIES (Dwg_Object *obj);
EXPORT int dwg_setup_RTEXT (Dwg_Object *obj);
EXPORT int dwg_setup_NURBSURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_PLANESURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_EXTRUDEDSURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_LOFTEDSURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_REVOLVEDSURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_SWEPTSURFACE (Dwg_Object *obj);
EXPORT int dwg_setup_SUNSTUDY (Dwg_Object *obj);
EXPORT int dwg_setup_TABLE (Dwg_Object *obj);
EXPORT int dwg_setup_TABLECONTENT (Dwg_Object *obj);
//EXPORT int dwg_setup_XREFPANELOBJECT (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCKGRIPLOCATIONCOMPONENT (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCKVISIBILITYGRIP (Dwg_Object *obj);
EXPORT int dwg_setup_BLOCKVISIBILITYPARAMETER (Dwg_Object *obj);
//EXPORT int dwg_setup_VISIBILITYGRIPENTITY (Dwg_Object *obj);
//EXPORT int dwg_setup_VISIBILITYPARAMETERENTITY (Dwg_Object *obj);


#endif /* DEBUG_CLASSES */

#ifdef __cplusplus
}
#endif

#endif
