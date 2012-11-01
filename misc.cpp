
// ----------------------------------------------------------------------
// Lora BBS Professional Edition - Version 3.00.11
// Copyright (c) 1996 by Marco Maccaferri. All rights reserved.
//
// History:
//    05/20/95 - Initial coding.
// ----------------------------------------------------------------------

#include "_ldefs.h"
#if defined(__DOS__)
#include "cxl.h"
#elif defined(__LINUX__)
#include <curses.h>
#endif

ULONG cr3tab[] = {
   0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
   0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
   0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
   0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
   0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
   0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
   0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
   0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
   0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
   0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
   0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
   0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
   0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
   0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
   0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
   0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
   0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
   0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L, 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
   0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
   0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
   0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
   0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
   0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
   0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
   0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
   0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
   0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
   0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
   0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
   0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
   0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
   0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

USHORT crctab[256] = {
   0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
   0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
   0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
   0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
   0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
   0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
   0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
   0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
   0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
   0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
   0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
   0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
   0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
   0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
   0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
   0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
   0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
   0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
   0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
   0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
   0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
   0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
   0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
   0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
   0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
   0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
   0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
   0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
   0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
   0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
   0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
   0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

USHORT Crc16 (UCHAR Byte, USHORT Crc)
{
   return ((USHORT)(crctab[((Crc >> 8) & 255) ^ Byte] ^ (Crc << 8)));
}

ULONG Crc32 (UCHAR Byte, ULONG Crc)
{
   return (cr3tab[((int) Crc ^ Byte) & 0xff] ^ ((Crc >> 8) & 0x00FFFFFFL));
//   return ((ULONG)(cr3tab[((ULONG)Crc ^ Byte) & 0xFF] ^ ((Crc >> 8) & 0x00FFFFFFL)));
}

USHORT StringCrc16 (CHAR *String, USHORT Crc)
{
   while (*String)
      Crc = Crc16 ((UCHAR)*String++, Crc);

   return (Crc);
}

ULONG StringCrc32 (CHAR *String, ULONG Crc)
{
   while (*String)
      Crc = Crc32 ((UCHAR)*String++, Crc);

   return (Crc);
}

// ----------------------------------------------------------------------

#define PER_WEEK    60480000L
#define PER_DAY      8640000L
#define PER_HOUR      360000L
#define PER_MINUTE      6000L
#define PER_SECOND       100L

LONG TimerSet (LONG lHund)
{
   LONG l;
   struct dostime_t dt;

   _dos_gettime (&dt);
   l = (dt.minute % 60) * PER_MINUTE + (dt.second % 60) * PER_SECOND + dt.hsecond;
   l += lHund;

   return (l);
}

USHORT TimeUp (LONG lEndtime)
{
   LONG l;
   struct dostime_t dt;

   _dos_gettime (&dt);
   l = (dt.minute % 60) * PER_MINUTE + (dt.second % 60) * PER_SECOND + dt.hsecond;
   if (l < (lEndtime - 65536L))
      l += PER_HOUR;

   return ((USHORT)(((l - lEndtime) >= 0L) ? TRUE : FALSE));
}

VOID Pause (LONG lHund)
{
   LONG Endtime;

   Endtime = TimerSet (lHund);
   while (TimeUp (Endtime) == FALSE) {
#if defined(__OS2__)
      DosSleep (1L);
#elif defined(__NT__)
      Sleep (1L);
#endif
   }
}

// ----------------------------------------------------------------------

PSZ AdjustPath (PSZ pszPath)
{
#if defined(__LINUX__)
   PSZ p;

   p = pszPath;
   while ((p = strchr (p, '\\')) != NULL)
      *p++ = '/';
#endif

   return (pszPath);
}

USHORT BuildPath (PSZ pszPath)
{
   USHORT RetVal = TRUE;
   CHAR Dir[128], *p, Final[128];

   AdjustPath (pszPath);

   strcpy (Final, "");
#if defined(__LINUX__)
   if (pszPath[0] == '/')
      strcat (Final, "/");
#else
   if (pszPath[0] == '\\')
      strcat (Final, "\\");
#endif
   strcpy (Dir, pszPath);

// ----------------------------------------------------------------------
// Build a complete directory tree by extracting the single directory
// names from the pathname.
// ----------------------------------------------------------------------
   if ((p = strtok (Dir, "\\/")) != NULL)
      do {
         strcat (Final, p);
         if (p[1] != ':' && p[0] != '.') {
// ----------------------------------------------------------------------
// If the directory cannot be created, stops the process immediately.
// The global variable errno is set to zero after an error only if the
// directory already exists.
// ----------------------------------------------------------------------
#if defined(__LINUX__)
            mkdir (Final, 0666);
#else
            mkdir (Final);
#endif
         }
#if defined(__LINUX__)
         strcat (Final, "/");
#else
         strcat (Final, "\\");
#endif
      } while (RetVal == TRUE && (p = strtok (NULL, "\\/")) != NULL);

   return (RetVal);
}

USHORT BuildEmptyPath (PSZ pszPath)
{
   DIR *dir;
   USHORT RetVal = TRUE;
   CHAR Dir[128], *p, Final[128];
   struct dirent *ent;

   strcpy (Final, "");
#if defined(__LINUX__)
   if (pszPath[0] == '/')
      strcat (Final, "/");
#else
   if (pszPath[0] == '\\')
      strcat (Final, "\\");
#endif
   strcpy (Dir, pszPath);

// ----------------------------------------------------------------------
// Build a complete directory tree by extracting the single directory
// names from the pathname.
// ----------------------------------------------------------------------
   if ((p = strtok (Dir, "\\/")) != NULL)
      do {
         strcat (Final, p);
         if (p[1] != ':' && p[0] != '.') {
// ----------------------------------------------------------------------
// If the directory cannot be created, stops the process immediately.
// The global variable errno is set to zero after an error only if the
// directory already exists.
// ----------------------------------------------------------------------
#if defined(__LINUX__)
            mkdir (Final, 0666);
#else
            mkdir (Final);
#endif
         }
#if defined(__LINUX__)
         strcat (Final, "/");
#else
         strcat (Final, "\\");
#endif
      } while (RetVal == TRUE && (p = strtok (NULL, "\\/")) != NULL);

   if (RetVal == TRUE) {
// ----------------------------------------------------------------------
// The directory was successfully created, now we clean the directory
// just in case it was already here with some trash in it.
// ----------------------------------------------------------------------
      strcpy (Dir, pszPath);
      if (Dir[strlen (Dir) - 1] == '\\' || Dir[strlen (Dir) - 1] == '/')
         Dir[strlen (Dir) - 1] = '\0';
      if ((dir = opendir (Dir)) != NULL) {
         while ((ent = readdir (dir)) != NULL) {
            sprintf (Final, "%s%s", pszPath, ent->d_name);
            unlink (Final);
         }
         closedir (dir);
      }
   }

   return (RetVal);
}

// ----------------------------------------------------------------------

#define KEY_UNREGISTERED      0
#define KEY_BASIC             1
#define KEY_ADVANCED          2
#define KEY_PROFESSIONAL      3
#define KEY_POINT             4

USHORT DLL_EXPORT ValidateKey (PSZ product, PSZ name, PSZ number)
{
   FILE *fp;
   USHORT RetVal = KEY_UNREGISTERED;
   CHAR Temp[64], Name[64], Serial[16], Check[32], *p;
   ULONG Crc, Validation;

#if defined(__OS2__)
   sprintf (Check, "[%s-os/2]", product);
#elif defined(__NT__)
   sprintf (Check, "[%s-windows]", product);
#elif defined(__LINUX__)
   sprintf (Check, "[%s-linux]", product);
#else
   sprintf (Check, "[%s-dos]", product);
#endif

   if ((fp = fopen ("lora.key", "rt")) != NULL) {
      while (fgets (Temp, sizeof (Temp) - 1, fp) != NULL) {
         if ((p = strchr (Temp, '\r')) != NULL)
            *p = '\0';
         if ((p = strchr (Temp, '\n')) != NULL)
            *p = '\0';

         if (!stricmp (Temp, Check)) {
            fgets (Temp, sizeof (Temp) - 1, fp);
            if ((p = strchr (Temp, '\r')) != NULL)
               *p = '\0';
            if ((p = strchr (Temp, '\n')) != NULL)
               *p = '\0';

            if (!strncmp (Temp, "name=", 5)) {
               strcpy (Name, &Temp[5]);
               fgets (Temp, sizeof (Temp) - 1, fp);
               if ((p = strchr (Temp, '\r')) != NULL)
                  *p = '\0';
               if ((p = strchr (Temp, '\n')) != NULL)
                  *p = '\0';

               if (!strncmp (Temp, "serial=", 7)) {
                  strcpy (Serial, &Temp[7]);
                  fgets (Temp, sizeof (Temp) - 1, fp);
                  if ((p = strchr (Temp, '\r')) != NULL)
                     *p = '\0';
                  if ((p = strchr (Temp, '\n')) != NULL)
                     *p = '\0';

                  if (!strncmp (Temp, "validation=", 11)) {
                     Validation = atol (&Temp[11]);

#if !defined(__POINT__)
                     Crc = StringCrc32 ("30BASIC", 0xFFFFFFFFL);
                     Crc = StringCrc32 (Check, Crc);
                     Crc = StringCrc32 (Name, Crc);
                     Crc = StringCrc32 (Serial, Crc);
                     if (Validation == Crc)
                        RetVal = KEY_BASIC;

                     Crc = StringCrc32 ("30ADVANCED", 0xFFFFFFFFL);
                     Crc = StringCrc32 (Check, Crc);
                     Crc = StringCrc32 (Name, Crc);
                     Crc = StringCrc32 (Serial, Crc);
                     if (Validation == Crc)
                        RetVal = KEY_ADVANCED;

                     Crc = StringCrc32 ("30PROFESSIONAL", 0xFFFFFFFFL);
                     Crc = StringCrc32 (Check, Crc);
                     Crc = StringCrc32 (Name, Crc);
                     Crc = StringCrc32 (Serial, Crc);
                     if (Validation == Crc)
                        RetVal = KEY_PROFESSIONAL;
#else
                     Crc = StringCrc32 ("30POINT", 0xFFFFFFFFL);
                     Crc = StringCrc32 (Check, Crc);
                     Crc = StringCrc32 (Name, Crc);
                     Crc = StringCrc32 (Serial, Crc);
                     if (Validation == Crc)
                        RetVal = KEY_POINT;
#endif
                  }
               }
            }
         }
      }
      fclose (fp);
   }

   if (RetVal != KEY_UNREGISTERED) {
      if (name != NULL)
         strcpy (name, Name);
      if (number != NULL)
         strcpy (number, Serial);
   }

   return (RetVal);
}

USHORT DLL_EXPORT CheckExpiration (VOID)
{
   #define EXPIRE_DAY        15
   #define EXPIRE_MONTH       3
   #define EXPIRE_YEAR     1997
   USHORT RetVal = 0;
   time_t today, expire;
   struct tm xtm;

   memset (&xtm, 0, sizeof (struct tm));
   xtm.tm_mday = EXPIRE_DAY;
   xtm.tm_mon = EXPIRE_MONTH - 1;
   xtm.tm_year = EXPIRE_YEAR - 1900;
   expire = mktime (&xtm);

   today = time (NULL);
   if (expire > today)
      RetVal = (USHORT)((expire - today) / 86400L);

   return (RetVal);
}

char *strinc (char *str1, char *str2)
{
   int max;
   char *p;

   max = strlen (str1);

   for (p = str2; *p; p++) {
      if (!strncmp (str1, p, max))
         return (p);
   }

   return (NULL);
}

char *strdel (char *substr, char *str)
{
   char *src, *dest;

   dest = strinc (substr, str);
   if (!dest)
      return (NULL);

   src = dest + strlen (substr);
   strcpy (dest, src);

   return (str);
}

char *strins (char *instr, char *str, int st_pos)
{
   int i, leninstr;

   /* get length of string to insert */
   leninstr = strlen (instr);

   /* shift affected portion of str text to the right */
   for (i = strlen (str); i >= st_pos; i--)
      *(str + leninstr + i) = *(str + i);

   /* insert instr text */
   for (i = 0; i < leninstr; i++)
      *(str + st_pos + i) = *(instr + i);

   /* return address of modified string */
   return (str);
}

char * DLL_EXPORT strsrep (char *str, char *search, char *replace)
{
   char *p;

   if ((p = strinc (search, str)) != NULL) {
      strdel (search, str);
      strins (replace, str, (int)((unsigned long)p - (unsigned long)str));
      p=str;
   }

   return (p);
}

VOID DLL_EXPORT RunExternal (PSZ Command, USHORT TimeLimit)
{
#if defined(__OS2__)
   int rc;
   CHAR Args[256], Pathname[_MAX_PATH], Name[128], *p;
   CHAR ObjBuf[64], Terminated, isCmd;
   ULONG id;
   STARTDATA StartData;
   PID Pid;
   STATUSDATA sd;
#elif defined(__NT__)
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   DWORD exitcode;
#endif
   ULONG timeout;

#if defined(__OS2__)
   if (Command[0] != '\0') {
      isCmd = FALSE;

      strcpy (Args, Command);
      strcpy (Name, strtok (Args, " "));
      if ((p = strtok (NULL, "")) != NULL) {
         while (*p == ' ')
            p++;
         strcpy (Args, p);
      }
      else
         Args[0] = '\0';

      strlwr (Name);
      if (strstr (Name, ".cmd") != NULL || strstr (Name, ".bat") != NULL) {
         strcpy (Args, "/C ");
         strcat (Args, Command);
         if ((p = getenv ("COMSPEC")) == NULL)
            p = "CMD.EXE";
         strcpy (Pathname, p);
         isCmd = TRUE;
      }
      else if (strchr (Name, '\\') == NULL && strchr (Name, ':') == NULL) {
         _searchenv (Name, "PATH", Pathname);
         if (Pathname[0] == '\0' && strchr (Name, '.') == NULL) {
            strcat (Name, ".com");
            _searchenv (Name, "PATH", Pathname);
            if (Pathname[0] == '\0') {
               strcpy (&Name[strlen (Name) - 4], ".exe");
               _searchenv (Name, "PATH", Pathname);
               if (Pathname[0] == '\0') {
                  strcpy (Args, "/C ");
                  strcat (Args, Command);
                  if ((p = getenv ("COMSPEC")) == NULL)
                     p = "CMD.EXE";
                  strcpy (Pathname, p);
                  isCmd = TRUE;
               }
            }
         }
      }
      else
         strcpy (Pathname, Name);

      memset (&StartData, 0, sizeof (STARTDATA));
      StartData.Length = sizeof (STARTDATA);
      StartData.Related = SSF_RELATED_CHILD;
      StartData.FgBg = SSF_FGBG_BACK;
      StartData.TraceOpt = SSF_TRACEOPT_NONE;
      StartData.PgmName = Pathname;
      StartData.PgmInputs = Args;
      StartData.TermQ = NULL;
      StartData.Environment = 0;
      StartData.InheritOpt = SSF_INHERTOPT_PARENT;
      StartData.SessionType = SSF_TYPE_FULLSCREEN;
      StartData.IconFile = 0;
      StartData.PgmHandle = 0;
      StartData.PgmControl = SSF_CONTROL_VISIBLE;
      StartData.InitXPos = 30;
      StartData.InitYPos = 40;
      StartData.InitXSize = 200;
      StartData.InitYSize = 140;
      StartData.Reserved = 0;
      StartData.ObjectBuffer = ObjBuf;
      StartData.ObjectBuffLen = sizeof (ObjBuf);
      if ((rc = DosStartSession (&StartData, &id, &Pid)) != 0 && isCmd == FALSE) {
         strcpy (Args, "/C ");
         strcat (Args, Command);
         if ((p = getenv ("COMSPEC")) == NULL)
            p = "CMD.EXE";
         strcpy (Pathname, p);
         rc = DosStartSession (&StartData, &id, &Pid);
      }

      if (rc == 0) {
         Terminated = FALSE;
         if (TimeLimit != 0)
            timeout = TimerSet (TimeLimit * 6000L);
         while (Terminated == FALSE) {
            sd.Length = sizeof (STATUSDATA);
            sd.SelectInd = SET_SESSION_UNCHANGED;
            sd.BondInd = SET_SESSION_UNCHANGED;
            if (DosSetSession (id, &sd) != 0 || (TimeLimit != 0 && TimeUp (timeout)))
               Terminated = TRUE;
            DosSleep (1L);
         }

         DosStopSession (STOP_SESSION_SPECIFIED, id);
      }
   }
/*
#elif defined(__NT__)
   if (Command[0] != '\0') {
      memset (&si, 0, sizeof (STARTUPINFO));
      si.cb = sizeof (STARTUPINFO);

      if (CreateProcess (NULL, Command, NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE|NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi) == TRUE) {
         do {
            GetExitCodeProcess (pi.hProcess, &exitcode);
         } while (exitcode == STILL_ACTIVE);
      }
   }
*/
#else
#if defined(__DOS__)
   wopen (0, 0, 24, 79, 5, LGREY|_BLACK, LGREY|_BLACK);
#endif
   system (Command);
#if defined(__DOS__)
   wclose ();
#endif
#endif
}

VOID DLL_EXPORT SpawnExternal (PSZ Command)
{
#if defined(__OS2__)
   CHAR Args[256], Pathname[_MAX_PATH], Name[128], *p;
   CHAR ObjBuf[64], isCmd;
   ULONG id;
   STARTDATA StartData;
   PID Pid;
#elif defined(__NT__)
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   DWORD exitcode;
#endif

#if defined(__OS2__)
   if (Command[0] != '\0') {
      isCmd = FALSE;

      strcpy (Args, Command);
      strcpy (Name, strtok (Args, " "));
      if ((p = strtok (NULL, "")) != NULL) {
         while (*p == ' ')
            p++;
         strcpy (Args, p);
      }
      else
         Args[0] = '\0';

      strlwr (Name);
      if (strstr (Name, ".cmd") != NULL || strstr (Name, ".bat") != NULL) {
         strcpy (Args, "/C ");
         strcat (Args, Command);
         if ((p = getenv ("COMSPEC")) == NULL)
            p = "CMD.EXE";
         strcpy (Pathname, p);
         isCmd = TRUE;
      }
      else if (strchr (Name, '\\') == NULL && strchr (Name, ':') == NULL) {
         _searchenv (Name, "PATH", Pathname);
         if (Pathname[0] == '\0' && strchr (Name, '.') == NULL) {
            strcat (Name, ".com");
            _searchenv (Name, "PATH", Pathname);
            if (Pathname[0] == '\0') {
               strcpy (&Name[strlen (Name) - 4], ".exe");
               _searchenv (Name, "PATH", Pathname);
               if (Pathname[0] == '\0') {
                  strcpy (Args, "/C ");
                  strcat (Args, Command);
                  if ((p = getenv ("COMSPEC")) == NULL)
                     p = "CMD.EXE";
                  strcpy (Pathname, p);
                  isCmd = TRUE;
               }
            }
         }
      }
      else
         strcpy (Pathname, Name);

      memset (&StartData, 0, sizeof (STARTDATA));
      StartData.Length = sizeof (STARTDATA);
      StartData.Related = SSF_RELATED_CHILD;
      StartData.FgBg = SSF_FGBG_BACK;
      StartData.TraceOpt = SSF_TRACEOPT_NONE;
      StartData.PgmName = Pathname;
      StartData.PgmInputs = Args;
      StartData.TermQ = NULL;
      StartData.Environment = 0;
      StartData.InheritOpt = SSF_INHERTOPT_PARENT;
      StartData.SessionType = SSF_TYPE_FULLSCREEN;
      StartData.IconFile = 0;
      StartData.PgmHandle = 0;
      StartData.PgmControl = SSF_CONTROL_VISIBLE;
      StartData.InitXPos = 30;
      StartData.InitYPos = 40;
      StartData.InitXSize = 200;
      StartData.InitYSize = 140;
      StartData.Reserved = 0;
      StartData.ObjectBuffer = ObjBuf;
      StartData.ObjectBuffLen = sizeof (ObjBuf);
      if (DosStartSession (&StartData, &id, &Pid) != 0 && isCmd == FALSE) {
         strcpy (Args, "/C ");
         strcat (Args, Command);
         if ((p = getenv ("COMSPEC")) == NULL)
            p = "CMD.EXE";
         strcpy (Pathname, p);
         DosStartSession (&StartData, &id, &Pid);
      }
   }
#elif defined(__NT__)
   if (Command[0] != '\0') {
      memset (&si, 0, sizeof (STARTUPINFO));
      si.cb = sizeof (STARTUPINFO);
      CreateProcess (NULL, Command, NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE|NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
   }
#else
#if defined(__DOS__)
   wopen (0, 0, 24, 79, 5, LGREY|_BLACK, LGREY|_BLACK);
#endif
   system (Command);
#if defined(__DOS__)
   wclose ();
#endif
#endif
}

ULONG DLL_EXPORT AvailableMemory (VOID)
{
   ULONG Value = 0L;

#if defined(__OS2__)
   DosQuerySysInfo (20, 20, (UCHAR *)&Value, sizeof (Value));
#elif defined(__NT__)
#elif defined(__LINUX__)
#else
#endif

   return (Value);
}

