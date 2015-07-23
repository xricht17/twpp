/*

The MIT License (MIT)

Copyright (c) 2015 Martin Richter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef TWPP_DETAIL_FILE_ENUMS_HPP
#define TWPP_DETAIL_FILE_ENUMS_HPP

#include "../twpp.hpp"

namespace Twpp {

enum class Alarm : UInt16 {
    General = 0, // aka TWAL_ALARM
    FeederError = 1,
    FeederWarning = 2,
    BarCode = 3,
    DoubleFeed = 4,
    Jam = 5,
    PatchCode = 6,
    Power = 7,
    Skew = 8
};

/// Argument types.
enum class Dat : UInt16 {
    Null = 0x0000,
    Capability = 0x0001,
    Event = 0x0002,
    Identity = 0x0003,
    Parent = 0x0004,
    PendingXfers = 0x0005,
    SetupMemXfer = 0x0006,
    SetupFileXfer = 0x0007,
    Status = 0x0008,
    UserInterface = 0x0009,
    XferGroup = 0x000a,
    CustomData = 0x000c,
    DeviceEvent = 0x000d,
    FileSystem = 0x000e,
    PassThrough = 0x000f,
    Callback = 0x0010,
    StatusUtf8 = 0x0011,
    Callback2 = 0x0012,
    ImageInfo = 0x0101,
    ImageLayout = 0x0102,
    ImageMemXfer = 0x0103,
    ImageNativeXfer = 0x0104,
    ImageFileXfer = 0x0105,
    CieColor = 0x0106,
    GrayResponse = 0x0107,
    RgbResponse = 0x0108,
    JpegCompression = 0x0109,
    Palette8 = 0x010a,
    ExtImageInfo = 0x010b,
    Filter = 0x010c,
    AudioFileXfer = 0x0201,
    AudioInfo = 0x0202,
    AudioNativeXfer = 0x0203,
    IccProfile = 0x0401,
    ImageMemFileXfer = 0x0402,
    EntryPoint = 0x0403,

    CustomBase = 0x8000
};

/// Values of CapType::IAutoSize.
enum class AutoSize : UInt16 {
    None = 0,
    Auto = 1,
    Current = 2
};

/// Values of CapType::ISupportedBarcodeTypes.
enum class BarCodeType : UInt16 {
    ThreeOfNine = 0,
    ThreeOfFiveInterleaved = 1,
    ThreeOfFiveNonInterleaved = 2,
    Code93 = 3,
    Code128 = 4,
    Ucc128 = 5,
    CodaBar = 6,
    Upca = 7,
    Upce = 8,
    Ean8 = 9,
    Ean13 = 10,
    Postnet = 11,
    Pdf417 = 12,
    TwoOfFiveIndustrial = 13,
    TwoOfFiveMatrix = 14,
    TwoOfFiveDatalogic = 15,
    TwoOfFiveIata = 16,
    ThreeOfNineFullAscii = 17,
    CodaBarWithStartStop = 18,
    MaxiCode = 19,
    QrCode = 20
};

/// Values of CapType::IBitDepthReduction.
enum class BitDepthReduction : UInt16 {
    Threshold = 0,
    HalfTone = 1,
    CustHalfTone = 2,
    Diffusion = 3,
    DynamicThreshold = 4
};

/// Values of CapType::IBitOrder.
enum class BitOrder : UInt16 {
    LsbFirst = 0,
    MsbFirst = 1
};

/// Values of CapType::CameraSide.
enum class CameraSide : UInt16 {
    Both = 0,
    Top = 1,
    Bottom = 2
};

enum class ConditionCode : UInt16 {
    Success = 0,
    Bummer = 1,
    LowMemory = 2,
    NoDs = 3,
    MaxConnections = 4,
    OperationError = 5,
    BadCap = 6,
    BadProtocol = 9,
    BadValue = 10,
    SeqError = 11,
    BadDest = 12,
    CapUnsupported = 13,
    CapBadOperation = 14,
    CapSeqError = 15,
    Denied = 16,
    FileExists = 17,
    FileNotFound = 18,
    NotEmpty = 19,
    PaperJam = 20,
    PaperDoubleFeed = 21,
    FileWriteError = 22,
    CheckDeviceOnline = 23,
    InterLock = 24,
    DamagedCorner = 25,
    FocusError = 26,
    DocTooLight = 27,
    DocTooDark = 28,
    NoMedia = 29,

    CustomBase = 0x8000
};

typedef ConditionCode CC;

static inline constexpr bool success(CC cc) noexcept{
    return cc == CC::Success;
}

/// Capability container type.
enum class ConType : UInt16 {
    Array = 3,
    Enumeration = 4,
    OneValue = 5,
    Range = 6,
    DontCare = 0xFFFF
};

/// Capability type.
enum class CapType : UInt16 {
    XferCount = 0x0001,
    ICompression = 0x0100,
    IPixelType = 0x0101,
    IUnits = 0x0102,
    IXferMech = 0x0103,
    Author = 0x1000,
    Caption = 0x1001,
    FeederEnabled = 0x1002,
    FeederLoaded = 0x1003,
    TimeDate = 0x1004,
    SupportedCaps = 0x1005,
    ExtendedCaps = 0x1006,
    AutoFeed = 0x1007,
    ClearPage = 0x1008,
    FeedPage = 0x1009,
    RewindPage = 0x100a,
    Indicators = 0x100b,
    PaperDetectable = 0x100d,
    UiControllable = 0x100e,
    DeviceOnline = 0x100f,
    AutoScan = 0x1010,
    ThumbnailsEnabled = 0x1011,
    Duplex = 0x1012,
    DuplexEnabled = 0x1013,
    EnableDsUiOnly = 0x1014,
    CustomDsData = 0x1015,
    Endorser = 0x1016,
    JobControl = 0x1017,
    Alarms = 0x1018,
    AlarmVolume = 0x1019,
    AutomaticCapture = 0x101a,
    TimeBeforeFirstCapture = 0x101b,
    TimeBetweenCaptures = 0x101c,
    ClearBuffers = 0x101d,
    MaxBatchBuffers = 0x101e,
    DeviceTimeDate = 0x101f,
    PowerSupply = 0x1020,
    CameraPreviewUi = 0x1021,
    DeviceEvent = 0x1022,
    SerialNumber = 0x1024,
    Printer = 0x1026,
    PrinterEnabled = 0x1027,
    PrinterIndex = 0x1028,
    PrinterMode = 0x1029,
    PrinterString = 0x102a,
    PrinterSuffix = 0x102b,
    Language = 0x102c,
    FeederAlignment = 0x102d,
    FeederOrder = 0x102e,
    ReacquireAllowed = 0x1030,
    BatteryMinutes = 0x1032,
    BatteryPercentage = 0x1033,
    CameraSide = 0x1034,
    Segmented = 0x1035,
    CameraEnabled = 0x1036,
    CameraOrder = 0x1037,
    MicrEnabled = 0x1038,
    FeederPrep = 0x1039,
    FeederPocket = 0x103a,
    AutomaticSenseMedium = 0x103b,
    CustomInterfaceGuid = 0x103c,
    SupportedCapsSegmentUnique = 0x103d,
    SupportedDats = 0x103e,
    DoubleFeedDetection = 0x103f,
    DoubleFeedDetectionLength = 0x1040,
    DoubleFeedDetectionSensitivity = 0x1041,
    DoubleFeedDetectionResponse = 0x1042,
    PaperHandling = 0x1043,
    IndicatorsMode = 0x1044,
    PrinterVerticalOffset = 0x1045,
    PowerSaveTime = 0x1046,
    PrinterCharRotation = 0x1047,
    PrinterFontStyle = 0x1048,
    PrinterIndexLeadChar = 0x1049,
    PrinterIndexMaxValue = 0x104A,
    PrinterIndexNumDigits = 0x104B,
    PrinterIndexStep = 0x104C,
    PrinterIndexTrigger = 0x104D,
    PrinterStringPreview = 0x104E,
    IAutoBright = 0x1100,
    IBrightness = 0x1101,
    IContrast = 0x1103,
    ICustHalfTone = 0x1104,
    IExposureTime = 0x1105,
    IFilter = 0x1106,
    IFlashUsed = 0x1107,
    IGamma = 0x1108,
    IHalfTones = 0x1109,
    IHighLight = 0x110a,
    IImageFileFormat = 0x110c,
    ILampState = 0x110d,
    ILightSource = 0x110e,
    IOrientation = 0x1110,
    IPhysicalWidth = 0x1111,
    IPhysicalHeight = 0x1112,
    IShadow = 0x1113,
    IFrames = 0x1114,
    IXNativeResolution = 0x1116,
    IYNativeResolution = 0x1117,
    IXResolution = 0x1118,
    IYResolution = 0x1119,
    IMaxFrames = 0x111a,
    ITiles = 0x111b,
    IBitOrder = 0x111c,
    ICcittKFactor = 0x111d,
    ILightPath = 0x111e,
    IPixelFlavor = 0x111f,
    IPlanarChunky = 0x1120,
    IRotation = 0x1121,
    ISupportedSizes = 0x1122,
    IThreshold = 0x1123,
    IXScaling = 0x1124,
    IYScaling = 0x1125,
    IBitOrderCodes = 0x1126,
    IPixelFlavorCodes = 0x1127,
    IJpegPixelType = 0x1128,
    ITimeFill = 0x112a,
    IBitDepth = 0x112b,
    IBitDepthReduction = 0x112c,
    IUndefinedImageSize = 0x112d,
    IImageDataSet = 0x112e,
    IExtImageInfo = 0x112f,
    IMinimumHeight = 0x1130,
    IMinimumWidth = 0x1131,
    IAutoDiscardBlankPages = 0x1134,
    IFlipRotation = 0x1136,
    IBarCodeDetectionEnabled = 0x1137,
    ISupportedBarCodeTypes = 0x1138,
    IBarCodeMaxSearchPriorities = 0x1139,
    IBarCodeSearchPriorities = 0x113a,
    IBarCodeSearchMode = 0x113b,
    IBarCodeMaxRetries = 0x113c,
    IBarCodeTimeOut = 0x113d,
    IZoomFactor = 0x113e,
    IPatchCodeDetectionEnabled = 0x113f,
    ISupportedPatchCodeTypes = 0x1140,
    IPatchCodeMaxSearchPriorities = 0x1141,
    IPatchCodeSearchPriorities = 0x1142,
    IPatchCodeSearchMode = 0x1143,
    IPatchCodeMaxRetries = 0x1144,
    IPatchCodeTimeOut = 0x1145,
    IFlashUsed2 = 0x1146,
    IImageFilter = 0x1147,
    INoiseFilter = 0x1148,
    IOverScan = 0x1149,
    IAutomaticBorderDetection = 0x1150,
    IAutomaticDeskew = 0x1151,
    IAutomaticRotate = 0x1152,
    IJpegQuality = 0x1153,
    IFeederType = 0x1154,
    IIccProfile = 0x1155,
    IAutoSize = 0x1156,
    IAutomaticCropUsesFrame = 0x1157,
    IAutomaticLengthDetection = 0x1158,
    IAutomaticColorEnabled = 0x1159,
    IAutomaticColorNonColorPixelType = 0x115a,
    IColorManagementEnabled = 0x115b,
    IImageMerge = 0x115c,
    IImageMergeHeightThreshold = 0x115d,
    ISupportedExtImageInfo = 0x115e,
    IFilmType = 0x115f,
    IMirror = 0x1160,
    IJpegSubSampling = 0x1161,
    AXferMech = 0x1202,
    CustomBase = 0x8000
};

/// Values of CapType::ClearBuffers.
enum class ClearBuffers : UInt16 {
    Auto = 0,
    Clear = 1,
    NoClear = 2
};

/// Values of CapType::IPlanarChunky.
enum class ColorFormat : UInt16 {
    Chunky = 0,
    Planar = 1
};

typedef ColorFormat PlanarChunky;

/// Values of CapType::ICompression.
/// Also used in ImageInfo and ImageMemXfer.
enum class Compression : UInt16 {
    None = 0,
    PackBits = 1,
    Group31D = 2,
    Group31DEol = 3,
    Group32D = 4,
    Group4 = 5,
    Jpeg = 6,
    Lzw = 7,
    JBig = 8,
    Png = 9,
    Rle4 = 10,
    Rle8 = 11,
    BitFields = 12,
    Ziz = 13,
    Jpeg2000 = 14,
    DontCare = 0xFFFF
};

/// Countries for Version.
enum class Country : UInt16 {
    Afghanistan = 1001,
    Algeria = 213,
    AmericanSamoa = 684,
    Andorra = 033,
    Angola = 1002,
    Anguilla = 8090,
    Antigua = 8091,
    Argentina = 54,
    Aruba = 297,
    Ascensioni = 247,
    Australia = 61,
    Austria = 43,
    Bahamas = 8092,
    Bahrain = 973,
    Bangladesh = 880,
    Barbados = 8093,
    Belgium = 32,
    Belize = 501,
    Benin = 229,
    Bermuda = 8094,
    Bhutan = 1003,
    Bolivia = 591,
    Botswana = 267,
    Britain = 6,
    BritVirginIs = 8095,
    Brazil = 55,
    Brunei = 673,
    Bulgaria = 359,
    BurkinaFaso = 1004,
    Burma = 1005,
    Burundi = 1006,
    Camaroon = 237,
    Canada = 2,
    CapeVerdeIs = 238,
    CaymanIs = 8096,
    CentralAfRep = 1007,
    Chad = 1008,
    Chile = 56,
    China = 86,
    ChristmasIs = 1009,
    CocosIs = 1009,
    Colombia = 57,
    Comoros = 1010,
    Congo = 1011,
    CookIs = 1012,
    Costarica = 506,
    Cuba = 005,
    Cyprus = 357,
    Czechoslovakia = 42,
    Denmark = 45,
    Djibouti = 1013,
    Dominica = 8097,
    DomincanRep = 8098,
    EasterIs = 1014,
    Ecuador = 593,
    Egypt = 20,
    ElSalvador = 503,
    EqGuinea = 1015,
    Ethiopia = 251,
    FalklandIs = 1016,
    FaeroeIs = 298,
    FijiIslands = 679,
    Finland = 358,
    France = 33,
    FrAntilles = 596,
    FrGuiana = 594,
    FrPolyneisa = 689,
    FutanaIs = 1043,
    Gabon = 241,
    Gambia = 220,
    Germany = 49,
    Ghana = 233,
    Gibralter = 350,
    Greece = 30,
    Greenland = 299,
    Grenada = 8099,
    Grenedines = 8015,
    Guadeloupe = 590,
    Guam = 671,
    GuantanamoBay = 5399,
    Guatemala = 502,
    Guinea = 224,
    GuineaBissau = 1017,
    Guyana = 592,
    Haiti = 509,
    Honduras = 504,
    HongKong = 852,
    Hungary = 36,
    Iceland = 354,
    India = 91,
    Indonesia = 62,
    Iran = 98,
    Iraq = 964,
    Ireland = 353,
    Israel = 972,
    Italy = 39,
    IvoryCoast = 225,
    Jamaica = 8010,
    Japan = 81,
    Jordan = 962,
    Kenya = 254,
    Kiribati = 1018,
    Korea = 82,
    Kuwait = 965,
    Laos = 1019,
    Lebanon = 1020,
    Liberia = 231,
    Libya = 218,
    Liechtenstein = 41,
    Luxenbourg = 352,
    Macao = 853,
    Madagascar = 1021,
    Malawi = 265,
    Malaysia = 60,
    Maldives = 960,
    Mali = 1022,
    Malta = 356,
    MarshallIs = 692,
    Mauritania = 1023,
    Mauritius = 230,
    Mexico = 3,
    Micronesia = 691,
    Miquelon = 508,
    Monaco = 33,
    Mongolia = 1024,
    Montserrat = 8011,
    Morocco = 212,
    Mozambique = 1025,
    Namibia = 264,
    Nauru = 1026,
    Nepal = 977,
    Netherlands = 31,
    NethAntilles = 599,
    Nevis = 8012,
    NewCaledonia = 687,
    NewZealand = 64,
    Nicaragua = 505,
    Niger = 227,
    Nigeria = 234,
    Niue = 1027,
    Norfolki = 1028,
    Norway = 47,
    Oman = 968,
    Pakistan = 92,
    Palau = 1029,
    Panama = 507,
    Paraguay = 595,
    Peru = 51,
    Phillippines = 63,
    PitcairnIs = 1030,
    PNewGuinea = 675,
    Poland = 48,
    Portugal = 351,
    Qatar = 974,
    Reunioni = 1031,
    Romania = 40,
    Rwanda = 250,
    Saipan = 670,
    SanMarino = 39,
    SaoTome = 1033,
    SaudiArabia = 966,
    Senegal = 221,
    Seychellesis = 1034,
    SierraLeone = 1035,
    Singapore = 65,
    SolomonIs = 1036,
    Somali = 1037,
    SouthAfrica = 27,
    Spain = 34,
    SriLanka = 94,
    StHelena = 1032,
    StKitts = 8013,
    StLucia = 8014,
    StPierre = 508,
    StVincent = 8015,
    Sudan = 1038,
    Suriname = 597,
    Swaziland = 268,
    Sweden = 46,
    Switzerland = 41,
    Syria = 1039,
    Taiwan = 886,
    Tanzania = 255,
    Thailand = 66,
    Tobago = 8016,
    Togo = 228,
    Tongais = 676,
    Trinidad = 8016,
    Tunisia = 216,
    Turkey = 90,
    TurksCaicos = 8017,
    Tuvalu = 1040,
    Uganda = 256,
    Ussr = 7,
    UaEmirates = 971,
    UnitedKingdom = 44,
    Usa = 1,
    Uruguay = 598,
    Vanuatu = 1041,
    VaticanCity = 39,
    Venezuela = 58,
    Wake = 1042,
    WallisIs = 1043,
    WesternSahara = 1044,
    WesternSamoa = 1045,
    Yemen = 1046,
    Yugoslavia = 38,
    Zaire = 243,
    Zambia = 260,
    Zimbabwe = 263,
    Albania = 355,
    Armenia = 374,
    Azerbaijan = 994,
    Belarus = 375,
    BosniaHerzgo = 387,
    Cambodia = 855,
    Croatia = 385,
    CzechRepublic = 420,
    DiegoGarcia = 246,
    Eritrea = 291,
    Estonia = 372,
    Georgia = 995,
    Latvia = 371,
    Lesotho = 266,
    Lithuania = 370,
    Macedonia = 389,
    MayotteIs = 269,
    Moldova = 373,
    Myanmar = 95,
    NorthKorea = 850,
    Puertorico = 787,
    Russia = 7,
    Serbia = 381,
    Slovakia = 421,
    Slovenia = 386,
    SouthKorea = 82,
    Ukraine = 380,
    UsVirginIs = 340,
    Vietnam = 84
};

/// Data group for distinguishing different categories of TWAIN operations.
enum class DataGroup : UInt32 {
    Control = 0x0001L,
    Image = 0x0002L,
    Audio = 0x0004L
};

typedef DataGroup DG;

static constexpr inline UInt32 operator~(DataGroup g) noexcept{
    return ~static_cast<UInt32>(g);
}

static constexpr inline UInt32 operator|(DataGroup a, DataGroup b) noexcept{
    return static_cast<UInt32>(a) | static_cast<UInt32>(b);
}

static constexpr inline UInt32 operator|(DataGroup a, UInt32 b) noexcept{
    return static_cast<UInt32>(a) | b;
}

static constexpr inline UInt32 operator&(DataGroup a, DataGroup b) noexcept{
    return static_cast<UInt32>(a) & static_cast<UInt32>(b);
}

static constexpr inline UInt32 operator&(UInt32 a, DataGroup b) noexcept{
    return static_cast<DataGroup>(a) & b;
}


/// Values of CapType::IAutoDiscardBlankPages.
enum class DiscardBlankPages : Int32 {
    Disabled = -2,
    Auto = -1
};

static constexpr inline DiscardBlankPages discardBytes(Int32 value) noexcept{
    return static_cast<DiscardBlankPages>(value);
}

/// Values of CapType::DoubleFeedDetection.
enum class DoubleFeedDetection : UInt16 {
    Ultrasonic = 0,
    ByLength = 1,
    Infrared = 2,
};

/// Values of CapType::DoubleFeedDetectionResponse.
enum class DoubleFeedResponse : UInt16 {
    Stop = 0,
    StopAndWait = 1,
    Sound = 2,
    DoNotImprint = 3
};

/// Values of CapType::DoubleFeedDetectionSensitivity.
enum class DoubleFeedSensitivity : UInt16 {
    Low = 0,
    Medium = 1,
    High = 2
};

/// Values of CapType::Duplex.
enum class Duplex : UInt16 {
    None = 0,
    OnePass = 1,
    TwoPass = 2
};

/// Values for CapType::FeederAlignment.
enum class FeederAlignment : UInt16 {
    None = 0,
    Left = 1,
    Center = 2,
    Right = 3
};

/// Values for CapType::FeederOrder.
enum class FeederOrder : UInt16 {
    FirstPageFirst = 0,
    LastPageFirst = 1
};


/// Values for CapType::FeederPocket.
enum class FeederPocket : UInt16 {
    PError = 0,
    P1 = 1,
    P2 = 2,
    P3 = 3,
    P4 = 4,
    P5 = 5,
    P6 = 6,
    P7 = 7,
    P8 = 8,
    P9 = 9,
    P10 = 10,
    P11 = 11,
    P12 = 12,
    P13 = 13,
    P14 = 14,
    P15 = 15,
    P16 = 16
};

/// Values for CapType::IFeederType.
enum class FeederType : UInt16 {
    General = 0,
    Photo = 1,
};

/// Values for CapType::IFilmType.
enum class FilmType : UInt16 {
    Positive = 0,
    Negative = 1
};

/// Values for CapType::IFilter.
enum class Filter : UInt16 {
    Red = 0,
    Green = 1,
    Blue = 2,
    None = 3,
    White = 4,
    Cyan = 5,
    Magenta = 6,
    Yellow = 7,
    Black = 8
};

/// Values for CapType::IFlashUsed2 and DeviceEvent.flash.
enum class Flash : UInt16 { // Capability->UInt16, DeviceEvent->UInt32
    None = 0,
    Off = 1,
    On = 2,
    Auto = 3,
    RedEye = 4
};

/// Values for CapType::IFlipRotation.
enum class FlipRotation : UInt16 {
    Book = 0,
    Fanfold = 1
};

/// Values for CapType::PrinterFontStyle
enum class FontStyle : UInt16 {
    Normal = 0,
    Bold = 1,
    Italic = 2,
    LargeSize = 3,
    SmallSize = 4
};

/// Values for CapType::IIccProfile.
enum class IccProfile : UInt16 {
    None = 0,
    Link = 1,
    Embed = 2
};

/// Values for CapType::IImageFileFormat.
enum class ImageFileFormat : UInt16 {
    Tiff = 0,
    Pict = 1,
    Bmp = 2,
    Xbm = 3,
    Jfif = 4,
    Fpx = 5,
    TiffMulti = 6,
    Png = 7,
    Spiff = 8,
    Exif = 9,
    Pdf = 10,
    Jp2 = 11,
    Jpx = 13,
    Dejavu = 14,
    PdfA = 15,
    PdfA2 = 16
};

/// Values for CapType::IImageFilter.
enum class ImageFilter : UInt16 {
    None = 0,
    Auto = 1,
    LowPass = 2,
    BandPass = 3,
    HighPass = 4,
    Text = 3,
    FineLine = 4
};

/// Values of CapType::IImageMerge.
enum class ImageMerge : UInt16 {
    None = 0,
    FrontOnTop = 1,
    FrontOnBottom = 2,
    FrontOnLeft = 3,
    FrontOnRight = 4
};

/// Values of CapType::PrinterIndexTrigger.
enum class IndexTrigger : UInt16 {
    Page = 0,
    Patch1 = 1,
    Patch2 = 2,
    Patch3 = 3,
    Patch4 = 4,
    PatchT = 5,
    Patch6 = 6
};

/// Values of CapType::IndicatorsMode.
enum class IndicatorsMode : UInt16 {
    Info = 0,
    Warning = 1,
    Error = 2,
    Warmup = 3
};

/// Values of CapType::JobControl.
enum class JobControl : UInt16 {
    None = 0,
    InclSepContScan = 1,
    InclSepStopScan = 2,
    ExclSepContScan = 3,
    ExclSepStopScap = 4
};

/// Values of CapType::IJpegQuality.
enum class JpegQuality : Int16 {
    Unknown = -4,
    Low = -3,
    Medium = -2,
    High = -1
};

static constexpr inline JpegQuality jpegQuality(Int16 value) noexcept{
    return static_cast<JpegQuality>(value);
}


/// Values of CapType::IJpegSubSampling.
enum class JpegSubSampling : UInt16 {
    Jp444Ycbcr = 0,
    Jp444Rgb = 1,
    Jp422 = 2,
    Jp421 = 3,
    Jp411 = 4,
    Jp420 = 5,
    Jp410 = 6,
    Jp311 = 7
};

/// Values of CapType::Language and Version structure.
enum class Language : UInt16 {
    UserLocale = 0xFFFF,
    Afrikaans = 14,
    Albania = 15,
    Arabic = 16,
    ArabicAlgeria = 17,
    ArabicBahrain = 18,
    ArabicEgypt = 19,
    ArabicIraq = 20,
    ArabicJordan = 21,
    ArabicKuwait = 22,
    ArabicLebanon = 23,
    ArabicLibya = 24,
    ArabicMorocco = 25,
    ArabicOman = 26,
    ArabicQatar = 27,
    ArabicSaudiArabia = 28,
    ArabicSyria = 29,
    ArabicTunisia = 30,
    ArabicUae = 31,
    ArabicYemen = 32,
    Basque = 33,
    ByeloRussian = 34,
    Bulgarian = 35,
    Catalan = 36,
    Chinese = 37,
    ChineseHongKong = 38,
    ChinesePrc = 39,
    ChineseSingapore = 40,
    ChineseSimplified = 41,
    ChineseTaiwan = 42,
    ChineseTraditional = 43,
    Croatia = 44,
    Czech = 45,
    Danish = 0,
    Dutch = 1,
    DutchBelgian = 46,
    English = 2,
    EnglishAustralian = 47,
    EnglishCanadian = 48,
    EnglishIreland = 49,
    EnglishNewZealand = 50,
    EnglishSouthAfrica = 51,
    EnglishUk = 52,
    EnglishUsa = 13,
    Estonian = 53,
    Faeroese = 54,
    Farsi = 55,
    Finnish = 4,
    French = 5,
    FrenchBelgian = 56,
    FrenchCanadian = 3,
    FrenchLuxembourg = 57,
    FrenchSwiss = 58,
    German = 6,
    GermanAustrian = 59,
    GermanLuxembourg = 60,
    GermanLiechtenstein = 61,
    GermanSwiss = 62,
    Greek = 63,
    Hebrew = 64,
    Hungarian = 65,
    Icelandic = 7,
    Indonesian = 66,
    Italian = 8,
    ItalianSwiss = 67,
    Japanese = 68,
    Korean = 69,
    KoreanJohab = 70,
    Latvian = 71,
    Lithuanian = 72,
    Norwegian = 9,
    NorwegianBokmal = 73,
    NorwegianNynorsk = 74,
    Polish = 75,
    Portuguese = 10,
    PortugueseBrazil = 76,
    Romanian = 77,
    Russian = 78,
    SerbianLatin = 79,
    Slovak = 80,
    Slovenian = 81,
    Spanish = 11,
    SpanishMexican = 82,
    SpanishModern = 83,
    Swedish = 12,
    Thai = 84,
    Turkish = 85,
    Ukranian = 86,
    Assamese = 87,
    Bengali = 88,
    Bihari = 89,
    Bodo = 90,
    Dogri = 91,
    Gujarati = 92,
    Haryanvi = 93,
    Hindi = 94,
    Kannada = 95,
    Kashmiri = 96,
    Malayalam = 97,
    Marathi = 98,
    Marwari = 99,
    Meghalayan = 100,
    Mizo = 101,
    Naga = 102,
    Orissi = 103,
    Punjabi = 104,
    Pushtu = 105,
    SerbianCyrillic = 106,
    Sikkimi = 107,
    SwedishFinland = 108,
    Tamil = 109,
    Telugu = 110,
    Tripuri = 111,
    Urdu = 112,
    Vietnamese = 113
};

/// Values of CapType::ILightPath.
enum class LightPath : UInt16 {
    Reflective = 0,
    Transmissive = 1
};

/// Values of CapType::ILightSource.
enum class LightSource : UInt16 {
    Red = 0,
    Green = 1,
    Blue = 2,
    None = 3,
    White = 4,
    Uv = 5,
    Ir = 6
};

/// Values for CapType::IMirror.
enum class Mirror : UInt16 {
    None = 0,
    Vertical = 1,
    Horizontal = 2
};

/// Values of possible actions of TWAIN operations.
enum class Msg : UInt16 {
    Null = 0x0000,
    Get = 0x0001,
    GetCurrent = 0x0002,
    GetDefault = 0x0003,
    GetFirst = 0x0004,
    GetNext = 0x0005,
    Set = 0x0006,
    Reset = 0x0007,
    QuerySupport = 0x0008,
    GetHelp = 0x0009,
    GetLabel = 0x000a,
    GetLabelEnum = 0x000b,
    SetConstraint = 0x000c,
    XferReady = 0x0101,
    CloseDsReq = 0x0102,
    CloseDsOk = 0x0103,
    DeviceEvent = 0x0104,
    OpenDsm = 0x0301,
    CloseDsm = 0x0302,
    OpenDs = 0x0401,
    CloseDs = 0x0402,
    UserSelect = 0x0403,
    DisableDs = 0x0501,
    EnableDs = 0x0502,
    EnableDsUiOnly = 0x0503,
    ProcessEvent = 0x0601,
    EndXfer = 0x0701,
    StopFeeder = 0x0702,
    ChangeDirectory = 0x0801,
    CreateDirectory = 0x0802,
    Delete = 0x0803,
    FormatMedia = 0x0804,
    GetClose = 0x0805,
    GetFirstFile = 0x0806,
    GetInfo = 0x0807,
    GetNextFile = 0x0808,
    Rename = 0x0809,
    Copy = 0x080A,
    AutomaticCaptureDirectory = 0x080B,
    PassThru = 0x0901,
    RegisterCallback = 0x0902,
    ResetAll = 0x0A01,
    CustomBase = 0x8000
};

/// Capability action support flags.
enum class MsgSupport : Int32 {
    Get = 0x0001,
    Set = 0x0002,
    GetDefault = 0x0004,
    GetCurrent = 0x0008,
    Reset = 0x0010,
    SetConstraint = 0x0020,
    GetHelp = 0x0100,
    GetLabel = 0x0200,
    GetLabelEnum = 0x0400
};

static inline constexpr MsgSupport operator|(MsgSupport a, MsgSupport b){
    return static_cast<MsgSupport>(static_cast<UInt32>(a) | static_cast<UInt32>(b));
}

static inline constexpr MsgSupport operator&(MsgSupport a, MsgSupport b){
    return static_cast<MsgSupport>(static_cast<UInt32>(a) & static_cast<UInt32>(b));
}

static inline constexpr MsgSupport operator^(MsgSupport a, MsgSupport b){
    return static_cast<MsgSupport>(static_cast<UInt32>(a) ^ static_cast<UInt32>(b));
}

/// Action support flags, all `get` actions.
static constexpr const MsgSupport msgSupportGetAll = MsgSupport::Get | MsgSupport::GetDefault | MsgSupport::GetCurrent;

/// Action support flags, all `get` actions, `set` and `reset`.
static constexpr const MsgSupport msgSupportGetAllSetReset = msgSupportGetAll | MsgSupport::Set | MsgSupport::Reset;

/// Values for CapType::INoiseFilter.
enum class NoiseFilter : UInt16 {
    None = 0,
    Auto = 1,
    LonePixel = 2,
    MajorityRule = 3
};

/// Values for CapType::IOrientation.
enum class Orientation : UInt16 {
    Rot0 = 0,
    Rot90 = 1,
    Rot180 = 2,
    Rot270 = 3,
    Portrait = 0,
    Landscape = 3,
    Auto = 4,
    AutoText = 5,
    AutoPicture = 6
};

/// Values for CapType::IOverscan.
enum class OverScan : UInt16 {
    None = 0,
    Auto = 1,
    TopBottom = 2,
    LeftRight = 3,
    All = 4
};

/// Values for CapType::PaperHandling.
enum class PaperHandling : UInt16 {
    Normal = 0,
    Fragile = 1,
    Thick = 2,
    TriFold = 3,
    Photograph = 4
};

/// Values for CapType::ISupportedSizes.
enum class PaperSize : UInt16 {
    None = 0,
    A4 = 1,
    JisB5 = 2,
    UsLetter = 3,
    UsLegal = 4,
    A5 = 5,
    IsoB4 = 6,
    IsoB6 = 7,
    UsLedger = 9,
    UsExecutive = 10,
    A3 = 11,
    IsoB3 = 12,
    A6 = 13,
    C4 = 14,
    C5 = 15,
    C6 = 16,
    Ps4A0 = 17, // 4A0
    Ps2A0 = 18, // 2A0
    A0 = 19,
    A1 = 20,
    A2 = 21,
    A7 = 22,
    A8 = 23,
    A9 = 24,
    A10 = 25,
    IsoB0 = 26,
    IsoB1 = 27,
    IsoB2 = 28,
    IsoB5 = 29,
    IsoB7 = 30,
    IsoB8 = 31,
    IsoB9 = 32,
    IsoB10 = 33,
    JisB0 = 34,
    JisB1 = 35,
    JisB2 = 36,
    JisB3 = 37,
    JisB4 = 38,
    JisB6 = 39,
    JisB7 = 40,
    JisB8 = 41,
    JisB9 = 42,
    JisB10 = 43,
    C0 = 44,
    C1 = 45,
    C2 = 46,
    C3 = 47,
    C7 = 48,
    C8 = 49,
    C9 = 50,
    C10 = 51,
    UsStatement = 52,
    BusinessCard = 53,
    MaxSize = 54
};

/// Values for CapType::IPixelFlavor, CapType::IPixelFlavorCodes, InfoId::PixelFlavor.
/// Chocolate - pixel represents darkest data.
/// Vanilla - pixel represents lightest data.
enum class PixelFlavor : UInt16 {
    Chocolate = 0,
    Vanilla = 1
};

/// Values for CapType::IPixelType, ImageInfo.
enum class PixelType : UInt16 {
    BlackWhite = 0,
    Gray = 1,
    Rgb = 2,
    Palette = 3,
    Cmy = 4,
    Cmyk = 5,
    Yuv = 6,
    Yuvk = 7,
    CieXyz = 8,
    Lab = 9,
    SRgb = 10,
    ScRgb = 11,
    Infrared = 16
};

/// Values for CapType::PowerSupply.
enum class PowerSupply : UInt16 { // Capability->UInt16, DeviceEvent->Int32
    External = 0,
    Battery = 1,
};

/// Values for CapType::Printer.
enum class Printer : UInt16 {
    ImprinterTopBefore = 0,
    ImprinterTopAfter = 1,
    ImprinterBottomBefore = 2,
    ImprinterBottomAfter = 3,
    EndorserTopBefore = 4,
    EndorserTopAfter = 5,
    EndorserBottomBefore = 6,
    EndorserBottomAfter = 7
};

/// Values for CapType::PrinterMode.
enum class PrinterMode : UInt16 {
    SingleString = 0,
    MultiString = 1,
    CompoundString = 2
};

enum class ReturnCode : UInt16 {
    Success = 0,
    Failure = 1,
    CheckStatus = 2,
    Cancel = 3,
    DsEvent = 4,
    NotDsEvent = 5,
    XferDone = 6,
    EndOfList = 7,
    InfoNotSupported = 8,
    DataNotAvailable = 9,
    Busy = 10,
    ScannerLocked = 11,

    CustomBase = 0x8000
};

typedef ReturnCode RC;

static inline constexpr bool success(ReturnCode rc) noexcept{
    return rc == RC::Success;
}


/// Values for CapType::IBarCodeSearchMode.
enum class SearchMode : UInt16 {
    Horizontal = 0,
    Vertical = 1,
    HorizVert = 2,
    VertHoriz = 3
};

/// Values for CapType::Segmented.
enum class Segmented : UInt16 {
    None = 0,
    Auto = 1,
    Manual = 2
};

/// TWAIN manager states.
enum class DsmState : UInt16 {
    PreSession = 1,
    Loaded = 2,
    Open = 3
};

/// TWAIN source states.
enum class DsState : UInt16 {
    Closed = 3,
    Open = 4,
    Enabled = 5,
    XferReady = 6,
    Xferring = 7
};

/// Values for CapType::IUnits.
enum class Unit : UInt16 {
    Inches = 0,
    CentiMetres = 1,
    Picas = 2,
    Points = 3,
    Twips = 4,
    Pixels = 5,
    MilliMetres = 6
};

/// Values for CapType::IXferMech, CapType::AXferMech.
enum class XferMech : UInt16 {
    Native = 0,
    File = 1,
    Memory = 2,
    MemFile = 4,
};


/// Type of the extended information.
enum class InfoId : UInt16 {
    BarCodeX = 0x1200,
    BarCodeY = 0x1201,
    BarCodeText = 0x1202,
    BarCodeType = 0x1203,
    DeShadeTop = 0x1204,
    DeShadeLeft = 0x1205,
    DeShadeHeight = 0x1206,
    DeShadeWidth = 0x1207,
    DeShadeSize = 0x1208,
    SpecklesRemoved = 0x1209,
    HorzLineXCoord = 0x120A,
    HorzLineYCoord = 0x120B,
    HorzLineLength = 0x120C,
    HorzLineThickness = 0x120D,
    VertLineXCoord = 0x120E,
    VertLineYCoord = 0x120F,
    VertLineLength = 0x1210,
    VertLineThickness = 0x1211,
    PatchCode = 0x1212,
    EndorsedText = 0x1213,
    FormConfidence = 0x1214,
    FormTemplateMatch = 0x1215,
    FormTemplatePageMatch = 0x1216,
    FormHorzDocOffset = 0x1217,
    FormVertDocOffset = 0x1218,
    BarCodeCount = 0x1219,
    BarCodeConfidence = 0x121A,
    BarCodeRotation = 0x121B,
    BarCodeTextLength = 0x121C,
    DeShadeCount = 0x121D,
    DeShadeBlackCountOld = 0x121E,
    DeShadeBlackCountNew = 0x121F,
    DeShadeBlackRlMin = 0x1220,
    DeShadeBlackRlMax = 0x1221,
    DeShadeWhiteCountOld = 0x1222,
    DeShadeWhiteCountNew = 0x1223,
    DeShadeWhiteRlMin = 0x1224,
    DeShadEWhiteRlAve = 0x1225,
    DeShadeWhiteRlMax = 0x1226,
    BlackSpecklesRemoved = 0x1227,
    WhiteSpecklesRemoved = 0x1228,
    HorzLineCount = 0x1229,
    VertLineCount = 0x122A,
    DeskewStatus = 0x122B,
    SkewOriginalAngle = 0x122C,
    SkewFinalAngle = 0x122D,
    SkewConfidence = 0x122E,
    SkewWindowX1 = 0x122F,
    SkewWindowY1 = 0x1230,
    SkewWindowX2 = 0x1231,
    SkewWindowY2 = 0x1232,
    SkewWindowX3 = 0x1233,
    SkewWindowY3 = 0x1234,
    SkewWindowX4 = 0x1235,
    SkewWindowY4 = 0x1236,
    BookName = 0x1238,
    ChapterNumber = 0x1239,
    DocumentNumber = 0x123A,
    PageNumber = 0x123B,
    Camera = 0x123C,
    FrameNumber = 0x123D,
    Frame = 0x123E,
    PixelFlavor = 0x123F,
    IccProfile = 0x1240,
    LastSegment = 0x1241,
    SegmentNumber = 0x1242,
    MagData = 0x1243,
    MagType = 0x1244,
    PageSide = 0x1245,
    FileSystemSource = 0x1246,
    ImageMerged = 0x1247,
    MagDataLength = 0x1248,
    PaperCount = 0x1249,
    PrinterText = 0x124A
};

/// Values for InfoId::BarCodeRotation.
enum class BarCodeRotation : UInt16 {
    Rot0 = 0,
    Rot90 = 1,
    Rot180 = 2,
    Rot270 = 3,
    RotUnknown = 4
};

/// Values for InfoId::PageSide.
enum class PageSide : UInt16 {
    Top = 1,
    Bottom = 2
};

/// Values for InfoId::DeskewStatus.
enum class DeskewStatus : UInt16 {
    Success = 0,
    ReportOnly = 1,
    Fail = 2,
    Disabled = 3
};

/// Values for InfoId::MagType.
enum class MagType : UInt16 {
    Micr = 0,
    Raw = 1,
    Invalid = 2
};

/// Values for InfoId::PatchCode.
enum class PatchCode : UInt16 {
    P1 = 0,
    P2 = 1,
    P3 = 2,
    P4 = 3,
    P6 = 4,
    PT = 5
};

}

#endif // TWPP_DETAIL_FILE_ENUMS_HPP

