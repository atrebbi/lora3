
// ----------------------------------------------------------------------
// LoraBBS Professional Edition - Version 3.00.32
// Copyright (c) 1996 by Marco Maccaferri. All rights reserved.
//
// History:
//    02/27/96 - Initial coding.
// ----------------------------------------------------------------------

#ifndef _LORA_API_H
#define _LORA_API_H

#include "collect.h"
#include "struc299.h"

#define KEY_UNREGISTERED      0
#define KEY_BASIC             1
#define KEY_ADVANCED          2
#define KEY_PROFESSIONAL      3
#define KEY_POINT             4

USHORT DLL_EXPORT ValidateKey (PSZ product, PSZ name, PSZ number);
USHORT DLL_EXPORT CheckExpiration (VOID);

#if defined(__POINT__)
#define NAME               "LoraPOINT"
#else
#define NAME               "LoraBBS"
#endif

#if defined(__POINT__)
#if defined(__OS2__)
#define NAME_OS            "LoraPOINT/OS2"
#elif defined(__NT__)
#define NAME_OS            "LoraPOINT/NT"
#elif defined(__LINUX__)
#define NAME_OS            "LoraPOINT/LINUX"
#elif defined(__DOS__)
#define NAME_OS            "LoraPOINT/DOS"
#else
#define NAME_OS            "LoraPOINT/???"
#endif
#else
#if defined(__OS2__)
#define NAME_OS            "LoraBBS/OS2"
#elif defined(__NT__)
#define NAME_OS            "LoraBBS/NT"
#elif defined(__LINUX__)
#define NAME_OS            "LoraBBS/LINUX"
#elif defined(__DOS__)
#define NAME_OS            "LoraBBS/DOS"
#else
#define NAME_OS            "LoraBBS/???"
#endif
#endif

#define VERSION            "2.99.34"
#define VER_MAJOR          2
#define VER_MINOR          99
#define PRODUCT_ID         0x4E

typedef struct {
   USHORT Zone;
   USHORT Net;
   USHORT Node;
   USHORT Point;
   CHAR   Domain[32];
   USHORT FakeNet;
} MAILADDRESS;

class DLL_EXPORT TAddress
{
public:
   TAddress (void);
   ~TAddress (void);

   USHORT Zone, Net, Node, Point;
   CHAR   Domain[32];
   CHAR   String[64];

   SHORT  Add (VOID);
   SHORT  Add (PSZ pszAddress);
   SHORT  Add (USHORT usZone, USHORT usNet, USHORT usNode, USHORT usPoint = 0, PSZ pszDomain = "");
   VOID   Clear (VOID);
   VOID   Delete (VOID);
   SHORT  First (VOID);
   USHORT Load (PSZ pszFile);
   USHORT Merge (PSZ pszFile);
   SHORT  Next (VOID);
   VOID   Parse (PSZ pszAddress);
   USHORT Save (PSZ pszFile);

private:
   class  TCollection List;
};

#define CONFIG_VERSION     2932

#define NO                 0
#define YES                1
#define REQUIRED           2
#define AUTO               2

typedef struct {
   USHORT Size;
   USHORT Version;

   CHAR   Device[32];            // Communication Device (COM2, COM3, etc.)
   ULONG  Speed;                 // DTE Maximum Speed
   USHORT LockSpeed;
   CHAR   Initialize[3][48];     // Initialization Strings
   CHAR   Answer[48];            // Command to Answer an Incoming Call
   CHAR   Dial[48];              // Command to Dial to Another Modem
   CHAR   Hangup[48];            // Command to Hangup the Line
   CHAR   OffHook[48];           // Command to Bring the Modem OffHook
   USHORT DialTimeout;
   USHORT CarrierDropTimeout;
   USHORT StripDashes;
   CHAR   FaxMessage[48];
   CHAR   FaxCommand[64];

   CHAR   SystemName[64];
   CHAR   SysopName[48];
   CHAR   Location[48];
   CHAR   Phone[32];
   CHAR   NodelistFlags[64];

   USHORT NewUserLevel;
   ULONG  NewUserFlags;
   ULONG  NewUserDenyFlags;
   CHAR   NewUserLimits[16];
   UCHAR  LoginType;
   UCHAR  CheckAnsi;
   UCHAR  RealName;
   UCHAR  CompanyName;
   UCHAR  Address;
   UCHAR  City;
   UCHAR  PhoneNumber;
   UCHAR  Gender;

   CHAR   LogFile[64];

   CHAR   SystemPath[64];
   CHAR   UserFile[64];
   CHAR   NormalInbound[64];
   CHAR   KnownInbound[64];
   CHAR   ProtectedInbound[64];
   CHAR   Outbound[64];
   CHAR   NodelistPath[64];
   CHAR   UsersHomePath[64];
   CHAR   MenuPath[64];
   CHAR   LanguageFile[64];
   CHAR   TextFiles[64];
   CHAR   SchedulerFile[64];

   CHAR   MainMenu[32];

   CHAR   HostName[48];
   CHAR   NewsServer[48];
   CHAR   MailServer[48];
   CHAR   PopServer[48];

   USHORT FakeNet;

   USHORT MailStorage;
   CHAR   MailPath[64];
   USHORT NetMailStorage;
   CHAR   NetMailPath[64];
   USHORT BadStorage;
   CHAR   BadPath[64];
   USHORT DupeStorage;
   CHAR   DupePath[64];

   USHORT TelnetServer;
   USHORT TelnetPort;
   USHORT FtpServer;
   USHORT FtpPort;
   USHORT WebServer;
   USHORT WebPort;
   USHORT SMTPServer;
   USHORT SMTPPort;
   USHORT POP3Server;
   USHORT POP3Port;
   USHORT NNTPServer;
   USHORT NNTPPort;

   USHORT WaZoo;
   USHORT EMSI;
   USHORT Janus;

   USHORT NewAreasStorage;
   CHAR   NewAreasPath[64];
   USHORT NewAreasLevel;
   ULONG  NewAreasFlags;
   ULONG  NewAreasDenyFlags;
   USHORT NewAreasWriteLevel;
   ULONG  NewAreasWriteFlags;
   ULONG  NewAreasDenyWriteFlags;

   UCHAR  Ansi;
   UCHAR  IEMSI;

   UCHAR  ImportEmpty;
   UCHAR  ReplaceTear;
   CHAR   TearLine[32];
   UCHAR  ForceIntl;
   UCHAR  Secure;
   UCHAR  KeepNetMail;
   UCHAR  TrackNetMail;

   CHAR   MailOnly[64];
   CHAR   EnterBBS[64];

   CHAR   ImportCmd[64];
   CHAR   ExportCmd[64];
   CHAR   SinglePassCmd[64];
   CHAR   PackCmd[64];
   CHAR   NewsgroupCmd[64];

   UCHAR  UseSinglePass;
   UCHAR  SeparateNetMail;

   CHAR   AreasBBS[64];
   UCHAR  UseAreasBBS;
   UCHAR  UpdateAreasBBS;

   CHAR   AfterCallerCmd[64];
   CHAR   AfterMailCmd[64];

   CHAR   Ring[32];
   UCHAR  ZModemTelnet;
   UCHAR  EnablePPP;
   USHORT PPPTimeLimit;
   CHAR   PPPCmd[64];

   CHAR   TempPath[64];
   CHAR   OLRPacketName[16];
   USHORT OLRMaxMessages;

   UCHAR  ExternalFax;
   UCHAR  FaxFormat;
   CHAR   FaxPath[64];
   CHAR   AfterFaxCmd[64];
   CHAR   FaxAlertNodes[64];
   CHAR   FaxAlertUser[64];

   UCHAR  ReloadLog;
   UCHAR  MakeProcessLog;
   USHORT RetriveMaxMessages;

   UCHAR  CheckAvatar;
   UCHAR  CheckColor;
   UCHAR  CheckFullScreen;
   UCHAR  CheckHotKey;
   UCHAR  CheckIBMChars;
   UCHAR  AskLines;
   UCHAR  AskPause;
   UCHAR  AskScreenClear;
   UCHAR  AskBirthDate;
   UCHAR  AskMailCheck;
   UCHAR  AskFileCheck;

   UCHAR  ExternalEditor;
   CHAR   EditorCmd[64];

   CHAR   HudsonPath[64];
   CHAR   GoldPath[64];
   USHORT BadBoard;
   USHORT DupeBoard;
   USHORT MailBoard;
   USHORT NetMailBoard;
} CONFIG;


typedef struct {
   USHORT TaskNumber;
   CHAR   Device[32];            // Communication Device (COM2, COM3, etc.)
   ULONG  Speed;                 // DTE Maximum Speed
   USHORT LockSpeed;
   CHAR   Initialize[3][48];     // Initialization Strings
   CHAR   Answer[48];            // Command to Answer an Incoming Call
   CHAR   Dial[48];              // Command to Dial to Another Modem
   CHAR   Hangup[48];            // Command to Hangup the Line
   CHAR   OffHook[48];           // Command to Bring the Modem OffHook
   USHORT DialTimeout;
   USHORT CarrierDropTimeout;
   USHORT StripDashes;
   CHAR   FaxMessage[48];
   CHAR   FaxCommand[64];
   CHAR   SchedulerFile[64];
   CHAR   MainMenu[32];
   CHAR   Ring[32];
   UCHAR  ManualAnswer;
   UCHAR  LimitedHours;
   USHORT StartTime;
   USHORT EndTime;
} CHANNEL;

class DLL_EXPORT TConfig
{
public:
   TConfig (void);
   ~TConfig (void);

   CHAR   Device[32];
   ULONG  Speed;
   CHAR   Initialize[3][48];
   CHAR   Answer[48], Dial[48], Hangup[48], OffHook[48];
   USHORT DialTimeout, LockSpeed, CarrierDropTimeout;
   USHORT StripDashes;
   CHAR   Ring[32];
   UCHAR  ManualAnswer, LimitedHours;
   USHORT StartTime, EndTime;
   CHAR   FaxMessage[48], FaxCommand[64];
   CHAR   SystemName[64], SysopName[48], Location[48];
   CHAR   Phone[32], NodelistFlags[64];
   UCHAR  LoginType, CheckAnsi, RealName, CompanyName;
   UCHAR  Address, City, PhoneNumber, Gender;
   USHORT TaskNumber;
   USHORT NewUserLevel;
   ULONG  NewUserFlags, NewUserDenyFlags;
   CHAR   NewUserLimits[16], SystemPath[64], LogFile[64];
   CHAR   UserFile[64], Outbound[64], SchedulerFile[64];
   CHAR   NormalInbound[64], KnownInbound[64], ProtectedInbound[64];
   CHAR   NodelistPath[64], UsersHomePath[64], MenuPath[64];
   CHAR   LanguageFile[64], TextFiles[64], TempPath[64];
   CHAR   MainMenu[32], HostName[48];
   CHAR   NewsServer[48], MailServer[48], PopServer[48];
   USHORT FakeNet;
   USHORT NetMailStorage, MailStorage, BadStorage, DupeStorage;
   CHAR   NetMailPath[64], MailPath[64], BadPath[64], DupePath[64];
   USHORT TelnetServer, TelnetPort;
   USHORT FtpServer, FtpPort;
   USHORT WebServer, WebPort;
   USHORT SMTPServer, SMTPPort;
   USHORT POP3Server, POP3Port;
   USHORT NNTPServer, NNTPPort;
   USHORT WaZoo, EMSI, Janus;
   USHORT NewAreasStorage;
   CHAR   NewAreasPath[64];
   USHORT NewAreasLevel, NewAreasWriteLevel;
   ULONG  NewAreasFlags, NewAreasDenyFlags, NewAreasWriteFlags, NewAreasDenyWriteFlags;
   UCHAR  Ansi, IEMSI, ImportEmpty, ReplaceTear, ForceIntl;
   CHAR   TearLine[32];
   UCHAR  Secure, KeepNetMail, TrackNetMail;
   CHAR   MailOnly[64], EnterBBS[64];
   CHAR   ImportCmd[64], ExportCmd[64], SinglePassCmd[64];
   CHAR   PackCmd[64], NewsgroupCmd[64], AfterCallerCmd[64], AfterMailCmd[64];
   UCHAR  UseSinglePass, SeparateNetMail, UseAreasBBS, UpdateAreasBBS;
   CHAR   AreasBBS[64], PPPCmd[64];
   UCHAR  ZModemTelnet, EnablePPP;
   USHORT PPPTimeLimit;
   CHAR   OLRPacketName[16];
   USHORT OLRMaxMessages;
   UCHAR  ExternalFax, FaxFormat;
   CHAR   FaxPath[64], AfterFaxCmd[64], FaxAlertNodes[64], FaxAlertUser[64];
   UCHAR  ReloadLog, MakeProcessLog;
   USHORT RetriveMaxMessages;
   UCHAR  CheckAvatar, CheckColor;
   UCHAR  CheckFullScreen;
   UCHAR  CheckHotKey;
   UCHAR  CheckIBMChars;
   UCHAR  AskLines;
   UCHAR  AskPause;
   UCHAR  AskScreenClear;
   UCHAR  AskBirthDate;
   UCHAR  AskMailCheck;
   UCHAR  AskFileCheck;
   UCHAR  ExternalEditor;
   CHAR   EditorCmd[64];
   CHAR   HudsonPath[64], GoldPath[64];
   USHORT BadBoard, DupeBoard, MailBoard, NetMailBoard;
   class  TAddress MailAddress;

   PSZ    AdjustPath (PSZ path);
   VOID   Default (VOID);
   PSZ    FixPath (PSZ path);
   USHORT Load (PSZ pszConfig = NULL, PSZ pszChannel = NULL);
   VOID   New (VOID);
   VOID   NewChannel (VOID);
   USHORT Reload (VOID);
   USHORT Save (PSZ pszConfig = NULL, PSZ pszChannel = NULL);

private:
   VOID   Struct2Class (CONFIG *Cfg);

   CHAR   ConfigFile[128];
   CHAR   ChannelFile[128];
};

class DLL_EXPORT TLog
{
public:
   TLog (void);
   virtual ~TLog (void);

   USHORT Display;

   virtual USHORT Open (PSZ pszName);
   virtual VOID   Resume (VOID);
   virtual VOID   Suspend (VOID);
   virtual VOID   Write (PSZ pszFormat, ...);
   virtual VOID   WriteBlank (VOID);

protected:
   FILE   *fp;
   PSZ    Months[12];
   CHAR   FileName[128];
   CHAR   Buffer[512], Temp[512];
};

// ---------------------------------------------------------------------------

typedef struct {
   CHAR   LastCaller[48];
   ULONG  TodayCalls;
   ULONG  Calls;
   ULONG  MailCalls;
} SYSSTAT;

#define STAT_OFFLINE       0
#define STAT_WAITING       1
#define STAT_USER          2
#define STAT_MAILER        3
#define STAT_FAXRECEIVE    4

typedef struct {
   USHORT Number;
   USHORT Status;
   CHAR   User[48];
   CHAR   From[48];
   CHAR   Action[48];
   CHAR   LastCaller[48];
   ULONG  TodayCalls;
   ULONG  Calls;
   ULONG  MailCalls;
} LINESTAT;

class DLL_EXPORT TStatistics
{
public:
   TStatistics (void);
   TStatistics (PSZ pszDataPath);
   ~TStatistics (void);

   USHORT LineNumber;
   USHORT Status;
   CHAR   User[48], From[48], Action[48];
   CHAR   LastCaller[48], LineLastCaller[48];
   ULONG  TotalCalls, Calls;
   ULONG  TotalMailCalls, MailCalls;
   ULONG  TotalTodayCalls, TodayCalls;

   USHORT First (VOID);
   USHORT Next (VOID);
   VOID   Read (USHORT usLine);
   VOID   Update (VOID);

private:
   USHORT LastTask;
   CHAR   DataFile[128];
   SYSSTAT Sys;
   LINESTAT Line;
};

// ---------------------------------------------------------------------------

class DLL_EXPORT TMsgData
{
public:
   TMsgData (void);
   TMsgData (PSZ pszDataPath);
   ~TMsgData (void);

   CHAR   Key[16];
   CHAR   Display[128];
   USHORT Level, WriteLevel;
   ULONG  AccessFlags, DenyFlags, WriteFlags, DenyWriteFlags;
   UCHAR  Age;
   USHORT Storage;
   CHAR   Path[128];
   USHORT Board;
   USHORT Flags, Group;
   CHAR   EchoMail, ShowGlobal, UpdateNews, Offline;
   CHAR   MenuName[32], Moderator[64];
   ULONG  Cost;
   USHORT DaysOld, RecvDaysOld, MaxMessages;
   ULONG  ActiveMsgs, HighWaterMark;
   CHAR   NewsGroup[128], EchoTag[64], Origin[80];
   CHAR   Address[48];
   ULONG  Highest, FirstMessage, LastMessage;
   SHORT  OriginIndex;
   ULONG  LastReaded;

   USHORT Add (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   USHORT Insert (VOID);
   USHORT Last (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   VOID   Pack (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ pszName, USHORT fCloseFile = TRUE);
   USHORT ReadEcho (PSZ pszEchoTag);
   USHORT ReRead (VOID);
   USHORT Update (VOID);

private:
   int    fdDat, fdIdx;
   CHAR   DataFile[128], IdxFile[128];
   CHAR   LastKey[16];

   VOID   Class2Struct (MESSAGE *Msg);
   VOID   Struct2Class (MESSAGE *Msg);
};

class DLL_EXPORT TEchoLink
{
public:
   TEchoLink (void);
   TEchoLink (PSZ pszDataPath);
   ~TEchoLink (void);

   USHORT Skip4D;
   ULONG  EchoTag;
   USHORT Zone, Net, Node, Point;
   CHAR   Domain[32];
   CHAR   Address[64], ShortAddress[64];
   UCHAR  SendOnly, ReceiveOnly;
   UCHAR  PersonalOnly;
   UCHAR  Passive, Skip;

   USHORT Add (VOID);
   USHORT AddString (PSZ pszString);
   VOID   Change (PSZ pszFrom, PSZ pszTo);
   USHORT Check (PSZ pszName);
   VOID   Clear (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   VOID   Load (PSZ pszEchoTag);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   VOID   Save (VOID);
   VOID   Update (VOID);

private:
   CHAR   DataFile[64];
   class  TCollection Data;
};

// ---------------------------------------------------------------------------

class DLL_EXPORT TFileData
{
public:
   TFileData (void);
   TFileData (PSZ pszDataPath);
   ~TFileData (void);

   CHAR   Display[128], Key[16];
   USHORT Level;
   ULONG  AccessFlags, DenyFlags;
   USHORT UploadLevel;
   ULONG  UploadFlags, UploadDenyFlags;
   USHORT DownloadLevel;
   ULONG  DownloadFlags, DownloadDenyFlags;
   UCHAR  Age;
   CHAR   Download[128];
   CHAR   Upload[128];
   CHAR   CdRom, FreeDownload, ShowGlobal;
   CHAR   MenuName[32];
   CHAR   Moderator[64];
   ULONG  Cost;
   ULONG  ActiveFiles, UnapprovedFiles;
   CHAR   EchoTag[64];
   UCHAR  UseFilesBBS;
   UCHAR  DlCost;
   CHAR   FileList[128];

   USHORT Add (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   USHORT Insert (VOID);
   USHORT Last (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   VOID   Pack (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ pszName, USHORT fCloseFile = TRUE);
   USHORT ReadEcho (PSZ pszEchoTag);
   USHORT ReRead (VOID);
   USHORT Update (VOID);

private:
   int    fdDat, fdIdx;
   CHAR   DataFile[128], IdxFile[128];
   CHAR   LastKey[16];

   VOID   Class2Struct (FILES *File);
   VOID   Struct2Class (FILES *File);
};

class DLL_EXPORT TFilechoLink
{
public:
   TFilechoLink (void);
   TFilechoLink (PSZ pszDataPath);
   ~TFilechoLink (void);

   USHORT Skip4D;
   ULONG  EchoTag;
   USHORT Zone, Net, Node, Point;
   CHAR   Domain[32];
   CHAR   Address[64], ShortAddress[64];
   UCHAR  SendOnly, ReceiveOnly;
   UCHAR  PersonalOnly;
   UCHAR  Passive, Skip;

   USHORT Add (VOID);
   USHORT AddString (PSZ pszString);
   VOID   Change (PSZ pszFrom, PSZ pszTo);
   USHORT Check (PSZ pszName);
   VOID   Clear (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   VOID   Load (PSZ pszEchoTag);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   VOID   Save (VOID);
   VOID   Update (VOID);

private:
   CHAR   DataFile[64];
   class  TCollection Data;
};

// ---------------------------------------------------------------------------

#define MSGTAGS_INDEX      32

typedef struct {
   UCHAR  Free;            // TRUE=Record is free
   UCHAR  Tagged;          // TRUE=Tagged for offline mail packing
   ULONG  UserId;          // CRC32 of user's name
   CHAR   Area[16];        // Area name
   ULONG  LastRead;        // Number of last message read
   ULONG  OlderMsg;        // Timestamp of the older message to pack
} MSGTAGS;

class DLL_EXPORT TMsgTag
{
public:
   TMsgTag (void);
   TMsgTag (PSZ pszUserFile);
   ~TMsgTag (void);

   UCHAR  Tagged;
   ULONG  UserId;          // CRC32 of user's name
   CHAR   Area[16];        // Area name
   ULONG  LastRead;        // Number of last message read
   ULONG  OlderMsg;        // Timestamp of the older message to pack

   VOID   Add (VOID);
   VOID   Change (PSZ pszOldName, PSZ pszNewName);
   VOID   Clear (VOID);
   USHORT First (VOID);
   VOID   Load (VOID);
   USHORT Next (VOID);
   VOID   New (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ pszArea);
   VOID   Save (VOID);
   VOID   Update (VOID);

private:
   CHAR   DatFile[64];
   class  TCollection Data;
};

#define FILETAGS_INDEX     32

typedef struct {
   UCHAR  Free;            // TRUE=Record is free
   ULONG  UserId;          // CRC32 of user's name
   USHORT Index;
   CHAR   Area[16];        // Area name
   CHAR   Name[32];        // Name of tagged file
   ULONG  Size;            // Size in bytes
   CHAR   Complete[128];   // Complete path and file name
   USHORT DeleteAfter;     // Delete file after transfer
   USHORT CdRom;           // The file is on a CD-ROM drive
} FILETAGS;

class DLL_EXPORT TFileTag
{
public:
   TFileTag (void);
   TFileTag (PSZ pszUserFile);
   ~TFileTag (void);

   ULONG  UserId;
   USHORT Index;
   CHAR   Area[16], Name[32], Complete[128];
   ULONG  Size;
   USHORT DeleteAfter;
   USHORT CdRom;
   USHORT TotalFiles;
   ULONG  TotalBytes;

   USHORT Add (VOID);
   USHORT Check (PSZ pszName);
   VOID   Clear (VOID);
   USHORT First (VOID);
   VOID   Load (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   VOID   Reindex (VOID);
   VOID   Remove (PSZ pszName = NULL);
   USHORT Select (USHORT usIndex);
   VOID   Save (VOID);
   VOID   Update (VOID);

private:
   CHAR   DatFile[64];
   class  TCollection Data;
};

typedef struct {
   CHAR   Key[16];             // Nome di riferimento
   CHAR   Description[32];     // Descrizione del livello
   USHORT Level;
   ULONG  Flags;
   ULONG  DenyFlags;
   ULONG  ExpireDays;          // Numero di giorni di validita'
   CHAR   ExpireClass[16];     // Classe di limitazione dopo la scadenza
   USHORT ExpireLevel;         // Livello da selezionare dopo la scadenza
   ULONG  ExpireFlags;
   ULONG  ExpireDenyFlags;
   USHORT CallTimeLimit;       // Tempo limite per chiamata
   USHORT DayTimeLimit;        // Tempo limite giornaliero
   USHORT WeekTimeLimit;       // Tempo limite settimanale
   USHORT MonthTimeLimit;      // Tempo limite mensile
   ULONG  YearTimeLimit;       // Tempo limite annuale
   ULONG  CallDownloadLimit;   // Limite di download per chiamata
   ULONG  DayDownloadLimit;    // Limite di download giornaliero
   ULONG  WeekDownloadLimit;   // Limite di download settimanale
   ULONG  MonthDownloadLimit;  // Limite di download mensile
   ULONG  YearDownloadLimit;   // Limite di download annuale
   USHORT InactivityTime;
   USHORT ShowLevel;           // Livello per vedere questo livello nella lista
   ULONG  ShowFlags;
   ULONG  ShowDenyFlags;
} LIMITS;

class DLL_EXPORT TLimits
{
public:
   TLimits (void);
   TLimits (PSZ pszUserFile);
   ~TLimits (void);

   CHAR   Key[16];             // Nome di riferimento
   CHAR   Description[32];     // Descrizione del livello
   USHORT Level;
   ULONG  Flags, DenyFlags;
   ULONG  ExpireDays;          // Numero di giorni di validita'
   CHAR   ExpireClass[16];     // Classe di limitazione dopo la scadenza
   USHORT ExpireLevel;         // Livello da selezionare dopo la scadenza
   ULONG  ExpireFlags;
   ULONG  ExpireDenyFlags;
   USHORT CallTimeLimit;       // Tempo limite per chiamata
   USHORT DayTimeLimit;        // Tempo limite giornaliero
   USHORT WeekTimeLimit;       // Tempo limite settimanale
   USHORT MonthTimeLimit;      // Tempo limite mensile
   ULONG  YearTimeLimit;       // Tempo limite annuale
   ULONG  CallDownloadLimit;   // Limite di download per chiamata
   ULONG  DayDownloadLimit;    // Limite di download giornaliero
   ULONG  WeekDownloadLimit;   // Limite di download settimanale
   ULONG  MonthDownloadLimit;  // Limite di download mensile
   ULONG  YearDownloadLimit;   // Limite di download annuale
   USHORT InactivityTime;
   USHORT ShowLevel;           // Livello per vedere questo livello nella lista
   ULONG  ShowFlags;
   ULONG  ShowDenyFlags;

   USHORT Add (VOID);
   VOID   New (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ pszName, USHORT fCloseFile = TRUE);
   USHORT Update (VOID);

private:
   int    fdDat;
   CHAR   DatFile[64];
};

class DLL_EXPORT TUser
{
public:
   TUser (void);
   TUser (PSZ pszUserFile);
   ~TUser (void);

   CHAR   Name[48];            // Name or nickname
   ULONG  Password;            // Password as a 32bit CRC
   CHAR   RealName[48];        // Real name
   CHAR   Company[36];         // Company name (if allowed)
   CHAR   Address[48];         // First line of the address
   CHAR   City[48];            // Second line of the address
   CHAR   DayPhone[26];        // Daytime phone number
   CHAR   Ansi;                // TRUE=User can display ANSI
   CHAR   Avatar;              // TRUE=User can display AVATAR
   CHAR   Color;               // TRUE=User can display color informations
   CHAR   HotKey;              // TRUE=User can use hot keyed menus
   CHAR   Sex;                 // M=Male, F=Female (no other sex allowed at this writing)
   UCHAR  FullEd;              // TRUE=Use fullscreen editor
   UCHAR  FullReader;          // TRUE=Use fullscreen reader
   UCHAR  NoDisturb;           // TRUE=Do not disturb
   UCHAR  AccessFailed;        // TRUE=Last access attempt failed
   USHORT ScreenHeight;        // User's screen width
   USHORT ScreenWidth;         // User's screen height
   USHORT Level;               // Level
   ULONG  AccessFlags;         // Access flags
   ULONG  DenyFlags;           // Deny access flags
   ULONG  CreationDate;        // Record's creation date as a Unix-style timestamp
   ULONG  LastCall;            // User's last call date/time as a Unix-style timestamp
   CHAR   MailBox[32];         // User's mailbox name
   CHAR   LimitClass[16];      // Class of limits
   ULONG  TotalCalls;          // Number of calls to the system
   ULONG  TodayTime;           // Number of minutes on-line today
   ULONG  WeekTime;            // Number of minutes on-line this week
   ULONG  MonthTime;           // Number of minutes on-line this month
   ULONG  YearTime;            // Number of minutes on-line this year
   CHAR   Language[16];        // Currently selected language (if any)
   CHAR   FtpHost[48];         // Host name for FTP transfers
   CHAR   FtpName[32];         // User name for FTP transfers
   CHAR   FtpPwd[32];          // Password for FTP transfers
   CHAR   LastMsgArea[16];     // Last message area visited
   CHAR   LastFileArea[16];    // Last file area visited
   USHORT UploadFiles;
   ULONG  UploadBytes;
   USHORT DownloadFiles;
   ULONG  DownloadBytes;
   USHORT FilesToday;
   ULONG  BytesToday;
   UCHAR  ImportPOP3Mail;           // TRUE=Import e-mail from POP3 server
   UCHAR  UseInetAddress;           // TRUE=Use the personal Inet address
   CHAR   InetAddress[64];          // Personal E-Mail address
   CHAR   Pop3Pwd[32];              // Password for POP3 mail server
   CHAR   Archiver[16];             // Default archiver
   CHAR   Protocol[16];             // Default protocol
   CHAR   Signature[64];            // Personal signature
   CHAR   FullScreen;               // TRUE=Full screen enhancements
   CHAR   IBMChars;                 // TRUE=Can display IBM characters
   CHAR   MorePrompt;               // TRUE=Display More? prompt at each page
   CHAR   ScreenClear;              // TRUE=Send screen clear codes
   CHAR   InUserList;               // TRUE=Display in user list
   CHAR   Kludges;                  // TRUE=Display message's kludge lines
   CHAR   MailCheck;                // TRUE=Mail check at logon
   CHAR   NewFileCheck;             // TRUE=Check for new files at logon
   UCHAR  BirthDay;
   UCHAR  BirthMonth;
   USHORT BirthYear;
   ULONG  LastPwdChange;            // Time of last password change
   class  TMsgTag  *MsgTag;
   class  TFileTag *FileTag;

   USHORT Add (VOID);
   USHORT Age (VOID);
   USHORT CheckPassword (PSZ pszPassword);
   VOID   Clear (VOID);
   USHORT Delete (VOID);
   USHORT First (VOID);
   USHORT GetData (PSZ pszName, USHORT fCheckRealName = TRUE);
   USHORT Next (VOID);
   VOID   Pack (VOID);
   VOID   SetPassword (PSZ pszPassword);
   USHORT Previous (VOID);
   VOID   Reindex (VOID);
   USHORT Update (VOID);

private:
   int    fdDat, fdIdx;
   CHAR   TempMailBox[32], DatFile[64], IdxFile[64];
   UINDEX Idx;
   USER   Usr;

   VOID   Struct2Class (VOID);
   VOID   Class2Struct (VOID);
};

// ---------------------------------------------------------------------------

typedef struct {
   CHAR   Address[64];           // Node's address
   CHAR   SystemName[64];        // System name
   CHAR   SysopName[48];         // Sysop name
   CHAR   Location[48];          // Location of this node (city/state)
   ULONG  Speed;                 // Maximum connection speed
   ULONG  MinSpeed;              // Minimum connection speed allowed
   CHAR   Phone[48];             // Phone number
   CHAR   Flags[48];             // Nodelist-type flags
   CHAR   DialCmd[32];           // Special dialing command for this node
   CHAR   SessionPwd[32];        // Mail session password
   CHAR   AreaMgrPwd[32];        // AreaManager (Echomail and Tic) password
   CHAR   OutPktPwd[9];          // Outbound packet password
   CHAR   InPktPwd[9];           // Inbound packet password
   CHAR   TicPwd[32];
   UCHAR  RemapMail;             // TRUE=Remap mail directed to SysopName
   UCHAR  UsePkt22;              // TRUE=Use mail packet type 2.2
   UCHAR  CreateNewAreas;        // TRUE=Can create new echomail areas
   CHAR   NewAreasFilter[128];   // Filter for new echomail areas
   CHAR   Packer[16];
   UCHAR  ImportPOP3Mail;        // TRUE=Import e-mail from POP3 server
   UCHAR  UseInetAddress;        // TRUE=Use the personal Inet address
   CHAR   InetAddress[64];       // Personal E-Mail address
   CHAR   Pop3Pwd[32];           // Password for POP3 mail server
} NODES;

typedef struct {
   CHAR   Name[14];
   ULONG  Entry;
} IDXHEADER;

typedef struct {
   USHORT Zone;
   USHORT Net;
   USHORT Node;
   ULONG  Position;
} NODEIDX;

typedef struct {
   USHORT Size;
   USHORT Zone;
   CHAR   Name[64];
   CHAR   Diff[64];
} NODELIST;

class DLL_EXPORT TNodes
{
public:
   TNodes (void);
   TNodes (PSZ pszDataPath);
   ~TNodes (void);

   CHAR   DataFile[64];
   CHAR   Address[64];
   USHORT Zone, Net, Node, Point;
   CHAR   SystemName[64], SysopName[48], Location[48];
   ULONG  Speed, MinSpeed;
   CHAR   Phone[48], Flags[48], DialCmd[32];
   UCHAR  RemapMail;
   CHAR   SessionPwd[32], AreaMgrPwd[32];
   CHAR   OutPktPwd[9], InPktPwd[9], TicPwd[32];
   UCHAR  UsePkt22, CreateNewAreas;
   CHAR   NewAreasFilter[128];
   CHAR   Packer[16];
   UCHAR  ImportPOP3Mail;        // TRUE=Import e-mail from POP3 server
   UCHAR  UseInetAddress;        // TRUE=Use the personal Inet address
   CHAR   InetAddress[64];       // Personal E-Mail address
   CHAR   Pop3Pwd[32];           // Password for POP3 mail server
   USHORT DefaultZone;
   CHAR   Nodelist[64], Nodediff[64];

   VOID   Add (VOID);
   VOID   AddNodelist (PSZ name, PSZ diff, USHORT zone = 0);
   VOID   Delete (VOID);
   VOID   DeleteNodelist (VOID);
   USHORT First (VOID);
   USHORT FirstNodelist (VOID);
   VOID   LoadNodelist (VOID);
   USHORT Next (VOID);
   USHORT NextNodelist (VOID);
   VOID   New (VOID);
   USHORT Previous (VOID);
   USHORT Read (USHORT usZone, USHORT usNet, USHORT usNode, USHORT usPoint, PSZ pszDomain = NULL);
   USHORT Read (class TAddress *Address, USHORT flAddNodelist = TRUE);
   USHORT Read (class TAddress &Address, USHORT flAddNodelist = TRUE);
   USHORT Read (PSZ pszAddress, USHORT flAddNodelist = TRUE);
   USHORT ReadNodelist (class TAddress *Address);
   USHORT ReadNodelist (class TAddress &Address);
   VOID   SaveNodelist (VOID);
   VOID   Update (VOID);

private:
   int    fd;
   class  TAddress Addr1, Addr2;
   class  TCollection ListData;

   VOID   Class2Struct (NODES &Nodes);
   VOID   Struct2Class (NODES &Nodes);
};

// ---------------------------------------------------------------------------

typedef struct {
   UCHAR  Day;
   UCHAR  Month;
   USHORT Year;
   UCHAR  Hour;
   UCHAR  Minute;
} FBDATE;

class DLL_EXPORT TFileBase
{
public:
   TFileBase (void);
   TFileBase (PSZ pszPath, PSZ pszArea);
   ~TFileBase (void);

   CHAR   Area[32], Name[32], Complete[128];
   FBDATE UplDate, Date;
   USHORT Level;
   PSZ    Uploader;
   CHAR   Keyword[32], Unapproved;
   ULONG  Size, DlTimes;
   ULONG  Cost, Password, AccessFlags, DenyFlags;
   ULONG  UploadDate, FileDate;
   USHORT CdRom;
   class  TCollection *Description;

   USHORT Add (VOID);
   ULONG  ChangeLibrary (PSZ pszFrom, PSZ pszTo);
   VOID   Clear (VOID);
   VOID   Close (VOID);
   VOID   Delete (VOID);
   USHORT First (PSZ pszSearch = NULL);
   USHORT Next (PSZ pszSearch = NULL);
   USHORT Open (PSZ pszPath, PSZ pszArea);
   VOID   Pack (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ pszFile);
   VOID   ReadFileList (PSZ list, PSZ dl_path);
   USHORT Replace (VOID);
   USHORT ReplaceHeader (VOID);
   VOID   SearchFile (PSZ pszFile);
   VOID   SearchKeyword (PSZ pszKeyword);
   VOID   SearchText (PSZ pszText);
   VOID   SortByDate (ULONG ulDate = 0L);
   VOID   SortByDownload (VOID);
   VOID   SortByName (VOID);

private:
   int    fdIdx;
   int    fdDat;
   CHAR   szArea[32], DataPath[128];
   CHAR   fUploader;
   PSZ    pszMemUploader;
   ULONG  LastPos;
   ULONG  LastDate;
   class  TCollection *List;

   USHORT MatchName (PSZ pszName, PSZ pszSearch);
};

// ---------------------------------------------------------------------------

#define OS_DOS          0x0001
#define OS_OS2          0x0002
#define OS_WINDOWS      0x0004
#define OS_LINUX        0x0008

typedef struct {
   CHAR   Key[16];
   CHAR   Display[32];
   CHAR   PackCmd[128];
   CHAR   UnpackCmd[128];
   CHAR   Id[32];
   LONG   Position;
   USHORT OS;
} PACKER;

class DLL_EXPORT TPacker
{
public:
   TPacker (void);
   TPacker (PSZ pszDataPath);
   ~TPacker (void);

   CHAR   Key[16], Display[32];
   CHAR   PackCmd[128], UnpackCmd[128];
   CHAR   Error[32];
   CHAR   Id[32];
   LONG   Position;
   UCHAR  Dos, OS2, Windows, Linux;

   USHORT Add (VOID);
   USHORT CheckArc (PSZ pszArcName);
   USHORT Delete (VOID);
   USHORT DoPack (PSZ pszArcName, PSZ pszFiles);
   USHORT DoUnpack (PSZ pszArcName, PSZ pszPath, PSZ pszFiles = NULL);
   USHORT First (USHORT checkOS = TRUE);
   VOID   New (VOID);
   USHORT Next (USHORT checkOS = TRUE);
   USHORT Previous (USHORT checkOS = TRUE);
   USHORT Read (PSZ pszKey, USHORT checkOS = TRUE);
   USHORT Update (VOID);

private:
   int  fd;
   CHAR Command[256];
   CHAR DataPath[48];
};

// ---------------------------------------------------------------------------

#define DAY_SUNDAY       0x01
#define DAY_MONDAY       0x02
#define DAY_TUESDAY      0x04
#define DAY_WEDNESDAY    0x08
#define DAY_THURSDAY     0x10
#define DAY_FRIDAY       0x20
#define DAY_SATURDAY     0x40

typedef struct {
   CHAR   Label[32];          // Reference label
   UCHAR  Hour;
   UCHAR  Minute;
   USHORT WeekDays;
   USHORT Length;             // Duration of this event (if applicable)
   USHORT LastDay;
   UCHAR  Dynamic;
   UCHAR  Force;              // Force execution of this event
   UCHAR  MailOnly;
   UCHAR  ForceCall;          // TRUE=Force a call to the node specified
   CHAR   Address[32];        // Fidonet address to call
   UCHAR  SendNormal;
   UCHAR  SendCrash;
   UCHAR  SendDirect;
   UCHAR  SendImmediate;
   USHORT CallDelay;
   UCHAR  StartImport;
   UCHAR  StartExport;
   UCHAR  ExportMail;
   UCHAR  ImportNormal;
   UCHAR  ImportKnown;
   UCHAR  ImportProtected;
   CHAR   RouteCmd[64];
   CHAR   Command[128];
   USHORT MaxCalls;
   USHORT MaxConnects;
   UCHAR  AllowRequests;
   UCHAR  MakeRequests;
   UCHAR  ProcessTIC;
   UCHAR  ClockAdjustment;
   UCHAR  Dummy[128];
} EVENT;

class DLL_EXPORT TEvents
{
public:
   TEvents (void);
   TEvents (PSZ pszDataFile);
   ~TEvents (void);

   USHORT Number, NextNumber;
   CHAR   NextLabel[32];
   USHORT Started, TimeRemain;

   CHAR   Label[32];
   UCHAR  Hour, Minute;
   UCHAR  Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday;
   USHORT Length, LastDay;
   UCHAR  Dynamic, Force, MailOnly, ForceCall;
   CHAR   Address[32];
   UCHAR  SendNormal, SendCrash, SendDirect, SendImmediate;
   USHORT CallDelay;
   UCHAR  StartImport, StartExport, ExportMail;
   UCHAR  ImportNormal, ImportKnown, ImportProtected;
   CHAR   RouteCmd[64], Command[128];
   USHORT MaxCalls, MaxConnects;
   UCHAR  AllowRequests, MakeRequests, ProcessTIC, ClockAdjustment;

   VOID   Add (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   USHORT SetCurrent (VOID);
   USHORT Load (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   USHORT Read (USHORT evtNum);
   VOID   Save (VOID);
   VOID   TimeToNext (VOID);
   VOID   Update (VOID);

private:
   CHAR   DataFile[128];
   EVENT  Event;
   class  TCollection Data;

   VOID   Class2Struct (EVENT *Event);
   VOID   Struct2Class (EVENT *Event);
};

// ----------------------------------------------------------------------

typedef struct {
   USHORT Zone;
   USHORT Net;
   USHORT Node;
   USHORT Point;
   CHAR   Domain[32];
   CHAR   Name[32];           // File name
   CHAR   Complete[128];
   ULONG  Size;               // File size in bytes
   UCHAR  ArcMail;            // TRUE=File is a compressed mail packet
   UCHAR  MailPKT;            // TRUE=File is an uncompressed mail packet
   UCHAR  Request;            // TRUE=File is a files request
   UCHAR  Poll;               // TRUE=Only the poll flag is present
   UCHAR  DeleteAfter;        // TRUE=Should be deleted after sent
   UCHAR  TruncateAfter;      // TRUE=Should be truncated to 0 bytes after sent
   CHAR   Status;             // 'H'=Hold, 'C'=Crash, 'D'=Direct, 'F'=Normal
} OUTFILE;

typedef struct {
   USHORT Zone;
   USHORT Net;
   USHORT Node;
   USHORT Point;
   CHAR   Domain[32];
   ULONG  Size;               // Total files size in bytes
   USHORT Files;              // Total number of files
   UCHAR  ArcMail;            // TRUE=Node has compressed mail files
   UCHAR  MailPKT;            // TRUE=Node has uncompressed mail files
   UCHAR  Request;            // TRUE=Node has file requests pending
   UCHAR  Crash;              // TRUE=Node has priority flags CRASH
   UCHAR  Direct;             // TRUE=Node has priority flags DIRECT
   UCHAR  Hold;               // TRUE=Node has priority flags HOLD
   UCHAR  Immediate;          // TRUE=Node has priority flags IMMEDIATE
   UCHAR  Normal;             // TRUE=Node has priority flags NORMAL
   USHORT Attempts;           // Number of dialing attempts
   USHORT Failed;             // Number of calls failed (connection but no handshake)
   CHAR   LastCall[32];
} QUEUE;

class DLL_EXPORT TOutbound
{
public:
   TOutbound (PSZ pszPath);
   TOutbound (PSZ pszPath, USHORT usZone, USHORT usNet, USHORT usNode, USHORT usPoint = 0, PSZ pszDomain = "");
   ~TOutbound (void);

   USHORT Zone, Net, Node, Point;
   CHAR   Domain[32];
   CHAR   Name[32], Complete[128];
   ULONG  Size;
   UCHAR  ArcMail, MailPKT, Request, Poll;
   UCHAR  DeleteAfter, TruncateAfter;
   CHAR   Status;

   USHORT Number;
   CHAR   Address[64];
   UCHAR  Crash, Direct, Hold, Immediate, Normal;
   USHORT Attempts, Failed;
   CHAR   LastCall[32];

   USHORT DefaultZone;
   USHORT TotalFiles, TotalNodes;
   ULONG  TotalSize;

   USHORT Add (VOID);
   USHORT Add (USHORT usZone, USHORT usNet, USHORT usNode, USHORT usPoint = 0, PSZ pszDomain = "");
   USHORT AddQueue (OUTFILE &Out);
   VOID   BuildQueue (PSZ pszPath);
   VOID   Clear (VOID);
   USHORT First (VOID);
   USHORT FirstNode (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT NextNode (VOID);
   VOID   PollNode (PSZ address, CHAR flag);
   VOID   Remove (VOID);
   VOID   Update (VOID);

   VOID   AddAttempt (PSZ address, USHORT failed, PSZ status = "");
   VOID   ClearAttempt (PSZ address);

private:
   CHAR   Path[48], Outbound[48];
   class  TCollection Files;
   class  TCollection Nodes;
};

// ---------------------------------------------------------------------------

#define MAX_LINE        4096

enum {
   LNG_LANGUAGE_NAME = 1,
   LNG_YES,
   LNG_NO,
   LNG_NONE,
   LNG_MALE,
   LNG_FEMALE,
   LNG_YESKEY,
   LNG_NOKEY,
   LNG_HELPKEY,
   LNG_MALEKEY,
   LNG_FEMALEKEY,
   LNG_JANUARY,
   LNG_FEBRUARY,
   LNG_MARCH,
   LNG_APRIL,
   LNG_MAY,
   LNG_JUNI,
   LNG_JULY,
   LNG_AUGUST,
   LNG_SEPTEMBER,
   LNG_OCTOBER,
   LNG_NOVEMBER,
   LNG_DECEMBER,
   LNG_PRESSENTER,
   LNG_DEFYESNO,
   LNG_YESDEFNO,
   LNG_DEFYESNOHELP,
   LNG_YESDEFNOHELP,
   LNG_ASKADDRESS,
   LNG_ASKANSI,
   LNG_ASKCITY,
   LNG_ASKCOMPANYNAME,
   LNG_ASKDAYPHONE,
   LNG_ASKPASSWORD,
   LNG_ASKALIAS,
   LNG_ASKSEX,
   LNG_ENTERNAME,
   LNG_ENTERNAMEORNEW,
   LNG_ENTERPASSWORD,
   LNG_INVALIDPASSWORD,
   LNG_HAVETAGGED,
   LNG_DISCONNECT,
   LNG_YOUSURE,
   LNG_USERFROMCITY,
   LNG_MENUERROR,
   LNG_MESSAGEHDR,
   LNG_MESSAGENUMBER,
   LNG_MESSAGENUMBER1,
   LNG_MESSAGENUMBER2,
   LNG_MESSAGENUMBER3,
   LNG_MESSAGEDATE,
   LNG_MESSAGEISREPLY,
   LNG_MESSAGESEEALSO,
   LNG_MESSAGEISBOTH,
   LNG_MESSAGEFLAGS,
   LNG_MESSAGEFROM,
   LNG_MESSAGETO,
   LNG_MESSAGESUBJECT,
   LNG_MESSAGEFILE,
   LNG_MESSAGETEXT,
   LNG_MESSAGEQUOTE,
   LNG_MESSAGEKLUDGE,
   LNG_MESSAGEORIGIN,
   LNG_MESSAGEAREAHEADER,
   LNG_MESSAGEAREASEPARATOR,
   LNG_MESSAGEAREADESCRIPTION1,
   LNG_MESSAGEAREADESCRIPTION2,
   LNG_MESSAGEAREACURSOR,
   LNG_MESSAGEAREAKEY,
   LNG_MESSAGEAREALIST,
   LNG_MESSAGEAREAREQUEST,
   LNG_MSGFLAG_RCV,
   LNG_MSGFLAG_SNT,
   LNG_MSGFLAG_PVT,
   LNG_MSGFLAG_CRA,
   LNG_MSGFLAG_KS,
   LNG_MSGFLAG_LOC,
   LNG_MSGFLAG_HLD,
   LNG_MSGFLAG_ATT,
   LNG_MSGFLAG_FRQ,
   LNG_MSGFLAG_TRS,
   LNG_ENDOFMESSAGES,
   LNG_READMENU,
   LNG_ENDREADMENU,
   LNG_NEXTMESSAGE,
   LNG_EXITREADMESSAGE,
   LNG_REREADMESSAGE,
   LNG_PREVIOUSMESSAGE,
   LNG_REPLYMESSAGE,
   LNG_EMAILREPLYMESSAGE,
   LNG_MENUNAME,
   LNG_CONFERENCENOTAVAILABLE,
   LNG_STARTWITHMESSAGE,
   LNG_NEWMESSAGES,
   LNG_TEXTFILES,
   LNG_FORUMNAME,
   LNG_FORUMOPERATOR,
   LNG_FORUMTOPIC,
   LNG_MENUPATH,
   LNG_MOREQUESTION,
   LNG_DELETEMOREQUESTION,
   LNG_NONSTOP,
   LNG_QUIT,
   LNG_CONTINUE,
   LNG_NAMENOTFOUND,
   LNG_FILEAREAREQUEST,
   LNG_FILEAREAHEADER,
   LNG_FILEAREALIST,
   LNG_FILEAREANOTAVAILABLE,
   LNG_FILEAREACURSOR,
   LNG_FILEAREASEPARATOR,
   LNG_FILEAREADESCRIPTION1,
   LNG_FILEAREADESCRIPTION2,
   LNG_FILEAREAKEY,
   LNG_FILENOTFOUNDINAREA,
   LNG_FILEDESCRIPTION,
   LNG_FILEDOWNLOADNAME,
   LNG_DOWNLOADFILENAME,
   LNG_NOFILEHERE,
   LNG_DISPLAYWHICHFILE,
   LNG_FILELISTHEADER,
   LNG_FILELISTSEPARATOR,
   LNG_FILELISTDESCRIPTION1,
   LNG_FILELISTDESCRIPTION2,
   LNG_FILELISTTAGGED,
   LNG_FILELISTNORMAL,
   LNG_READERFROM,
   LNG_READERTO,
   LNG_READERSUBJECT,
   LNG_READERFILE,
   LNG_CONTINUEASNEW,
   LNG_REENTERPASSWORD,
   LNG_PASSWORDNOMATCH,
   LNG_ASKAVATAR,
   LNG_ASKCOLOR,
   LNG_ASKFULLSCREEN,
   LNG_ASKHOTKEY,
   LNG_ASKIBMCHARS,
   LNG_ASKLINES,
   LNG_ASKPAUSE,
   LNG_ASKSCREENCLEAR,
   LNG_ASKBIRTHDATE,
   LNG_ASKMAILCHECK,
   LNG_ASKFILECHECK,
   LNG_CURRENTPASSWORD,
   LNG_WHYPASSWORD,
   LNG_WRONGPASSWORD,
   LNG_FILEPROTOCOLLIST,
   LNG_FILETAGGEDWARNING,
   LNG_FILENOBYTESWARNING,
   LNG_FILENOTIMEWARNING,
   LNG_FILEBEGINDOWNLOAD,
   LNG_FILEBEGINDOWNLOAD2,
   LNG_FILETAGGEDHEADER,
   LNG_FILETAGGEDLIST,
   LNG_FILETAGGEDTOTAL,
   LNG_FILEDOWNLOADERROR,
   LNG_FILEDOWNLOADCOMPLETE,
   LNG_FILEBUILDLIST,
   LNG_FILENOTAGGED,
   LNG_FILETAGLISTED,
   LNG_FILELISTTAGCONFIRM,
   LNG_FILELISTMOREQUESTION,
   LNG_FILELISTDELETEMOREQUESTION,
   LNG_FILELISTTAGKEY,
   LNG_FILELISTNOFILESFOUND,
   LNG_FILELISTCOMMENT,
   LNG_FILELISTNOTFOUND,
   LNG_FILENAMETODELETE,
   LNG_FILEDELETED,
   LNG_FILETODETAG,
   LNG_FILEDETAGGED,
   LNG_FILETAGEMPTY,
   LNG_FILETOTAG,
   LNG_FILETAGCONFIRM,
   LNG_FILENOTFOUND,
   LNG_MAX_ENTRIES
};

class DLL_EXPORT TLanguage
{
public:
   TLanguage (void);
   ~TLanguage (void);

   CHAR   File[32], Comment[64], MenuName[32];
   CHAR   TextFiles[64], MenuPath[64];

   PSZ    Months[12];
   CHAR   Yes, No, Help;
   CHAR   Male, Female;

   VOID   Default (VOID);
   USHORT Load (PSZ pszFile);
   PSZ    Text (USHORT Id);

private:
   PSZ    TextMemory;
   PSZ    Pointer[LNG_MAX_ENTRIES];

   USHORT CheckKeyword (PSZ pszKey);
   PSZ    CopyString (USHORT Key, PSZ Arg, PSZ Pointer);
};

// ---------------------------------------------------------------------------

class DLL_EXPORT TEchotoss
{
public:
   TEchotoss (PSZ path);
   ~TEchotoss (void);

   CHAR   Tag[64];

   VOID   Add (PSZ tag);
   VOID   Clear (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   USHORT Load (VOID);
   USHORT Next (VOID);
   VOID   Save (VOID);

private:
   CHAR   DataFile[128];
   class  TCollection Data;
};

// ---------------------------------------------------------------------------

typedef struct {
   USHORT Size;
   CHAR   Key[16];
   CHAR   Description[64];
   UCHAR  Active;
   UCHAR  Batch;
   UCHAR  DisablePort;
   UCHAR  ChangeToUploadPath;
   CHAR   DownloadCmd[64];
   CHAR   UploadCmd[64];
   CHAR   LogFileName[64];
   CHAR   CtlFileName[64];
   CHAR   DownloadCtlString[32];
   CHAR   UploadCtlString[32];
   CHAR   DownloadKeyword[32];
   CHAR   UploadKeyword[32];
   USHORT FileNamePos;
   USHORT SizePos;
   USHORT CpsPos;
} PROTOCOL;

class DLL_EXPORT TProtocol
{
public:
   TProtocol (void);
   TProtocol (PSZ path);
   ~TProtocol (void);

   CHAR   Key[16];
   CHAR   Description[64];
   UCHAR  Active, Batch, DisablePort, ChangeToUploadPath;
   CHAR   DownloadCmd[64], UploadCmd[64];
   CHAR   LogFileName[64], CtlFileName[64];
   CHAR   DownloadCtlString[32], UploadCtlString[32];
   CHAR   DownloadKeyword[32], UploadKeyword[32];
   USHORT FileNamePos, SizePos, CpsPos;

   VOID   Add (VOID);
   VOID   Delete (VOID);
   USHORT First (VOID);
   VOID   New (VOID);
   USHORT Next (VOID);
   USHORT Previous (VOID);
   USHORT Read (PSZ key);
   VOID   Update (VOID);

private:
   int    fdDat;
   CHAR   DataFile[128];
   PROTOCOL prot;

   VOID   Class2Struct (PROTOCOL *proto);
   VOID   Struct2Class (PROTOCOL *proto);
};

#endif

