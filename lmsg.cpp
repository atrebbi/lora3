
// LoraBBS Version 2.99 Free Edition
// Copyright (C) 1987-98 Marco Maccaferri
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "_ldefs.h"
#include "lora_api.h"
#include "msgbase.h"

class TConfig *Cfg;

VOID UpdateLastread (PSZ Area, ULONG TotalMsgs, ULONG *Active)
{
   int fd, i, Count, Changed, m;
   ULONG Position, LastRead;
   MSGTAGS *Buffer;

   if ((fd = sopen ("msgtags.dat", O_RDWR|O_BINARY|O_CREAT, SH_DENYNO, S_IREAD|S_IWRITE)) != -1) {
      if ((Buffer = (MSGTAGS *)malloc (sizeof (MSGTAGS) * MSGTAGS_INDEX)) != NULL) {
         do {
            Changed = FALSE;

            Position = tell (fd);
            Count = read (fd, Buffer, sizeof (MSGTAGS) * MSGTAGS_INDEX) / sizeof (MSGTAGS);
            for (i = 0; i < Count; i++) {
               if (Buffer[i].Free == FALSE && !strcmp (Buffer[i].Area, Area)) {
                  LastRead = 0L;
                  for (m = 0; m < TotalMsgs; m++) {
                     if (Active[m] != 0L && Active[m] <= Buffer[i].LastRead)
                        LastRead = Active[m];
                  }
                  if (Buffer[i].LastRead != LastRead) {
                     Buffer[i].LastRead = LastRead;
                     Changed = TRUE;
                  }
               }
            }
            if (Changed == TRUE) {
               lseek (fd, Position, SEEK_SET);
               write (fd, Buffer, sizeof (MSGTAGS) * Count);
            }
         } while (Count == MSGTAGS_INDEX);
         free (Buffer);
      }

      close (fd);
   }
}

VOID PurgeMessages (CHAR *Area, USHORT WriteDate)
{
   int i;
   USHORT Deleted, Done;
   ULONG Number, Highest, TotalMsgs, *Active, Counter;
   time_t Today, MsgDate;
   struct tm ltm;
   class TMsgData *Data;
   class TMsgBase *Msg;

   cprintf (" * Purging Messages\r\n");
   Today = time (NULL) / 86400L;

   if ((Data = new TMsgData (Cfg->SystemPath)) != NULL) {
      if (Data->First () == TRUE)
         do {
            if (Area != NULL) {
               if (Data->Read (Area) == FALSE)
                  break;
            }

            Msg = NULL;
            if (Data->Storage == ST_JAM)
               Msg = new JAM (Data->Path);
            else if (Data->Storage == ST_SQUISH)
               Msg = new SQUISH (Data->Path);
            else if (Data->Storage == ST_FIDO)
               Msg = new FIDOSDM (Data->Path);
            else if (Data->Storage == ST_ADEPT)
               Msg = new ADEPT (Data->Path);

            if (Msg != NULL) {
               cprintf (" +-- %-15.15s %-29.29s ", Data->Key, Data->Display);
               Msg->Lock (0L);

               Counter = 0;
               Deleted = 0;
               TotalMsgs = Msg->Number ();
               if (TotalMsgs > 0L) {
                  if ((Active = (ULONG *)malloc ((size_t)((TotalMsgs + 100L) * sizeof (ULONG)))) != NULL) {
                     i = 0;
                     Number = Msg->Lowest ();
                     do {
                        Active[i++] = Number;
                     } while (Msg->Next (Number) == TRUE);
                  }
               }
               else
                  Active = NULL;

               if (Data->DaysOld != 0 || Data->MaxMessages != 0) {
                  Number = Msg->Lowest ();
                  Highest = Msg->Highest ();

                  do {
                     if ((Counter % 10L) == 0L)
                        cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", Counter, TotalMsgs);
                     Counter++;

                     if (Msg->ReadHeader (Number) == TRUE) {
                        Done = FALSE;
                        if (Data->DaysOld != 0) {
                           if (WriteDate == TRUE) {
                              ltm.tm_mday = Msg->Written.Day;
                              ltm.tm_mon = Msg->Written.Month - 1;
                              ltm.tm_year = Msg->Written.Year - 1900;
                              ltm.tm_hour = Msg->Written.Hour;
                              ltm.tm_min = Msg->Written.Minute;
                              ltm.tm_sec = Msg->Written.Second;
                           }
                           else {
                              ltm.tm_mday = Msg->Arrived.Day;
                              ltm.tm_mon = Msg->Arrived.Month - 1;
                              ltm.tm_year = Msg->Arrived.Year - 1900;
                              ltm.tm_hour = Msg->Arrived.Hour;
                              ltm.tm_min = Msg->Arrived.Minute;
                              ltm.tm_sec = Msg->Arrived.Second;
                           }
                           MsgDate = mktime (&ltm) / 86400L;

                           if ((Today - MsgDate) > Data->DaysOld) {
                              Msg->Delete (Number);
                              Done = TRUE;
                              Deleted++;
                              if (Active != NULL) {
                                 for (i = 0; i < TotalMsgs; i++) {
                                    if (Active[i] == Number)
                                       Active[i] = 0L;
                                 }
                              }
                           }
                        }
                        if (Done == FALSE && Data->MaxMessages != 0 && Msg->Number () > Data->MaxMessages) {
                           Msg->Delete (Number);
                           Deleted++;
                           if (Active != NULL) {
                              for (i = 0; i < TotalMsgs; i++) {
                                 if (Active[i] == Number)
                                    Active[i] = 0L;
                              }
                           }
                        }
                     }
                  } while (Msg->Next (Number) == TRUE);
                  cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", Counter, TotalMsgs);
               }

               cprintf ("Total: %5lu, Deleted: %5u\r\n", TotalMsgs, Deleted);
               Msg->UnLock ();

               if (Deleted > 0) {
                  Data->ActiveMsgs = Msg->Number ();
                  Data->FirstMessage = Msg->Lowest ();
                  Data->LastMessage = Msg->Highest ();
                  Data->Update ();
                  if (Active != NULL)
                     UpdateLastread (Data->Key, TotalMsgs, Active);
               }
               if (Active != NULL)
                  free (Active);
            }
            if (Msg != NULL)
               delete Msg;

            if (Area != NULL)
               break;
         } while (Data->Next () == TRUE);
      delete Data;
   }
}

VOID PackMessages (CHAR *Area)
{
   USHORT Skip;
   PSZ p;
   class TMsgData *Data;
   class TMsgBase *Msg;
   class TCollection Done;

   printf (" * Pack (Compressing) Messages\n");

   if ((Data = new TMsgData (Cfg->SystemPath)) != NULL) {
      if (Data->First () == TRUE)
         do {
            if (Area != NULL) {
               if (Data->Read (Area) == FALSE)
                  break;
            }

            Msg = NULL;
            if (Data->Storage == ST_JAM)
               Msg = new JAM (Data->Path);
            else if (Data->Storage == ST_SQUISH)
               Msg = new SQUISH (Data->Path);
            else if (Data->Storage == ST_FIDO)
               Msg = new FIDOSDM (Data->Path);
            else if (Data->Storage == ST_ADEPT)
               Msg = new ADEPT (Data->Path);
            else if (Data->Storage == ST_HUDSON) {
               Skip = FALSE;
               if ((p = (PSZ)Done.First ()) != NULL)
                  do {
                     if (!stricmp (p, Data->Path)) {
                        Skip = TRUE;
                        break;
                     }
                  } while ((p = (PSZ)Done.Next ()) != NULL);
               if (Skip == FALSE) {
                  Done.Add (Data->Path);
                  Msg = new HUDSON (Data->Path, (UCHAR)Data->Board);
               }
            }
            if (Msg != NULL) {
               cprintf (" +-- %-15.15s %-49.49s ", Data->Key, Data->Display);
               fflush (stdout);
               Msg->Pack ();
               if (Data->Storage != ST_HUDSON) {
                  Data->ActiveMsgs = Msg->Number ();
                  Data->FirstMessage = Msg->Lowest ();
                  Data->LastMessage = Msg->Highest ();
                  Data->Update ();
               }
               cprintf ("\r\n");
            }
            if (Msg != NULL)
               delete Msg;

            if (Area != NULL)
               break;
         } while (Data->Next () == TRUE);
      delete Data;
   }
}

typedef struct {
   ULONG Subject;
   ULONG Number;
} MSGLINK;

VOID LinkMessages (CHAR *Area)
{
   int i, m;
   ULONG Number, Prev, Next, Crc, Total;
   CHAR Temp[128], *p;
   MSGLINK *Link;
   class TMsgData *Data;
   class TMsgBase *Msg;

   printf (" * Reply-linking Messages\n");

   if ((Data = new TMsgData (Cfg->SystemPath)) != NULL) {
      if (Data->First () == TRUE)
         do {
            if (Area != NULL) {
               if (Data->Read (Area) == FALSE)
                  break;
            }

            Msg = NULL;
            if (Data->Storage == ST_JAM)
               Msg = new JAM (Data->Path);
            else if (Data->Storage == ST_SQUISH)
               Msg = new SQUISH (Data->Path);
            else if (Data->Storage == ST_FIDO)
               Msg = new FIDOSDM (Data->Path);
            else if (Data->Storage == ST_ADEPT)
               Msg = new ADEPT (Data->Path);
            if (Msg != NULL) {
               cprintf (" +-- %-15.15s %-40.40s ", Data->Key, Data->Display);
               fflush (stdout);
               if ((Total = Msg->Number ()) != 0L) {
                  Msg->Lock (0L);
                  if ((Link = (MSGLINK *)malloc (Total * sizeof (MSGLINK))) != NULL) {
                     memset (Link, 0, Total * sizeof (MSGLINK));
                     Number = Msg->Lowest ();
                     i = 0;
                     do {
                        Msg->ReadHeader (Number);
                        strcpy (Temp, Msg->Subject);
                        p = strupr (Temp);
                        if (!strncmp (p, "RE:", 3)) {
                           p += 3;
                           if (*p == ' ')
                              p++;
                        }
                        Link[i].Subject = StringCrc32 (p, 0xFFFFFFFFL);
                        Link[i].Number = Number;
                        i++;

                        if ((i % 10) == 0)
                           cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", i, Total);
                     } while (Msg->Next (Number) == TRUE);

                     cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", i, Total);

                     Number = Msg->Lowest ();
                     i = 0;
                     do {
                        Msg->ReadHeader (Number);

                        Prev = Next = 0;
                        Crc = Link[i].Subject;

                        for (m = 0; m < Total; m++) {
                           if (m == i)
                              continue;
                           if (Link[m].Subject == Crc) {
                              if (m < i)
                                 Prev = Link[m].Number;
                              else if (m > i) {
                                 Next = Link[m].Number;
                                 break;
                              }
                           }
                        }

                        if ((i % 10) == 0)
                           cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", i, Total);

                        if (Msg->Original != Prev || Msg->Reply != Next) {
                           Msg->Original = Prev;
                           Msg->Reply = Next;
                           Msg->WriteHeader (Number);
                        }

                        i++;
                     } while (Msg->Next (Number) == TRUE);

                     cprintf ("%6lu / %6lu\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", i, Total);
                     free (Link);
                  }
                  Msg->UnLock ();
               }
               cprintf ("\r\n");
               delete Msg;
            }

            if (Area != NULL)
               break;
         } while (Data->Next () == TRUE);
      delete Data;
   }
}

VOID ReindexMessages (VOID)
{
   class TMsgData *Data;
   class TMsgBase *Msg;

   printf (" * Indexing Messages\n");

   if ((Data = new TMsgData (Cfg->SystemPath)) != NULL) {
      if (Data->First () == TRUE)
         do {
            Msg = NULL;
            if (Data->Storage == ST_JAM)
               Msg = new JAM (Data->Path);
            else if (Data->Storage == ST_SQUISH)
               Msg = new SQUISH (Data->Path);
            else if (Data->Storage == ST_FIDO)
               Msg = new FIDOSDM (Data->Path);
            else if (Data->Storage == ST_ADEPT)
               Msg = new ADEPT (Data->Path);
            if (Msg != NULL) {
               printf (" +-- %-15.15s %-29.29s ", Data->Key, Data->Display);
               Data->ActiveMsgs = Msg->Number ();
               Data->FirstMessage = Msg->Lowest ();
               Data->LastMessage = Msg->Highest ();
               Data->Update ();
               printf ("Total: %5lu, First: %5u\n", Data->ActiveMsgs, Data->FirstMessage);
            }
            if (Msg != NULL)
               delete Msg;
         } while (Data->Next () == TRUE);
      delete Data;
   }
}

VOID ImportDescriptions (PSZ pszFile)
{
   #define MAX_LINECHAR 2048
   int counter, existing;
   FILE *fp = fopen (pszFile, "rt");
   CHAR *lpTemp = (CHAR *)malloc (MAX_LINECHAR + 1);
   CHAR *lpTag, *lpDescription;
   class TMsgData *MsgData = new TMsgData (Cfg->SystemPath);

   counter = 0;
   existing = 0;
   printf (" * Import descriptions from %s\n", pszFile);

   if (fp != NULL && lpTemp != NULL && MsgData != NULL) {
      while (fgets (lpTemp, MAX_LINECHAR, fp) != NULL) {
         lpTemp[strlen (lpTemp) - 1] = '\0';
         if (lpTemp[0] == ';' || lpTemp[0] == '\0')
            continue;
         if ((lpTag = strtok (lpTemp, " ")) != NULL) {
            if ((lpDescription = strtok (NULL, "")) != NULL) {
               while (*lpDescription == ' ' || *lpDescription == 0x09)
                  lpDescription++;
               if (MsgData->ReadEcho (lpTag) == TRUE) {
                  strcpy (MsgData->Display, lpDescription);
                  MsgData->Update ();
                  existing++;
               }

               counter++;
            }
         }
      }
   }

   printf ("   %d area(s) readed, %d updated\n", counter, existing);

   if (MsgData != NULL)
      delete MsgData;
   if (lpTemp != NULL)
      free (lpTemp);
   if (fp != NULL)
      fclose (fp);
}

VOID ExportDescriptions (PSZ pszFile)
{
   FILE *fp;
   int counter = 0;
   class TMsgData *MsgData;

   printf (" * Updating %s\n", pszFile);

   if ((fp = fopen (pszFile, "wt")) != NULL) {
      if ((MsgData = new TMsgData (Cfg->SystemPath)) != NULL) {
         if (MsgData->First () == TRUE)
            do {
               if (MsgData->EchoMail == TRUE && MsgData->EchoTag[0] != '\0') {
                  fprintf (fp, "%-24s %s\n", MsgData->EchoTag, MsgData->Display);
                  counter++;
               }
            } while (MsgData->Next () == TRUE);
         delete MsgData;
      }
      fclose (fp);
   }

   printf ("   %d description(s) exported\n", counter);
}

void main (int argc, char *argv[])
{
   int i;
   USHORT Purge, Pack, Reindex, Link, WriteDate;
   USHORT Import, Export;
   CHAR *Area = NULL, *Config = NULL, *File = NULL;

   Import = Export = 0;
   Purge = Pack = FALSE;
   Reindex = Link = FALSE;
   WriteDate = FALSE;

   printf ("\nLMSG; %s v%s - Message maintenance utility\n", NAME, VERSION);
   printf ("      Copyright (c) 1991-96 by Marco Maccaferri. All Rights Reserved.\n\n");

/*
   if (ValidateKey ("bbs", NULL, NULL) == KEY_UNREGISTERED) {
      printf ("* * *     WARNING: No license key found    * * *\n");
      if ((i = CheckExpiration ()) == 0) {
         printf ("* * *   This evaluation copy has expired   * * *\n\a\n");
          exit (0);
      }
      else
         printf ("* * * You have %2d days left for evaluation * * * \n\a\n", i);
   }
*/

   if (argc <= 1) {
      printf (" * Command-line parameters:\n\n");

      printf ("        -A<key>     Process the area <key> only\n");
      printf ("        -I          Recreate index files\n");
      printf ("        -P[K]       Pack (compress) message base\n");
      printf ("                    K=Purge\n");
      printf ("        -K[W]       Purge messages from info in MSG.DAT\n");
      printf ("                    W=Use write date\n");
      printf ("        -L          Link messages by subject\n");
      printf ("        -E[D]<file> Export data from MSG.DAT\n");
      printf ("                    D=Echomail descriptions\n");
      printf ("        -R[D]<file> Import data to MSG.DAT\n");
      printf ("                    D=Echomail descriptions\n");

      printf ("\n * Please refer to the documentation for a more complete command summary\n\n");
   }
   else {
      for (i = 1; i < argc; i++) {
         if (argv[i][0] == '-' || argv[i][0] == '/') {
            switch (toupper (argv[i][1])) {
               case 'A':
                  Area = &argv[i][2];
                  break;
               case 'K':
                  Purge = TRUE;
                  if (toupper (argv[i][2]) == 'W')
                     WriteDate = TRUE;
                  break;
               case 'P':
                  Pack = TRUE;
                  if (toupper (argv[i][2]) == 'K')
                     Purge = TRUE;
                  break;
               case 'I':
                  Reindex = TRUE;
                  break;
               case 'L':
                  Link = TRUE;
                  break;
               case 'R':
                  if (toupper (argv[i][2]) == 'D') {
                     Import = 1;
                     File = &argv[i][3];
                  }
                  break;
               case 'E':
                  if (toupper (argv[i][2]) == 'D') {
                     Export = 1;
                     File = &argv[i][3];
                  }
                  break;
            }
         }
         else if (Config == NULL)
            Config = argv[i];
      }

      if ((Cfg = new TConfig) != NULL) {
         if (Cfg->Load (Config, NULL) == FALSE)
            Cfg->Default ();
      }

      if (Export == 1)
         ExportDescriptions (File);
      if (Import == 1)
         ImportDescriptions (File);
      if (Reindex == TRUE)
         ReindexMessages ();
      if (Purge == TRUE)
         PurgeMessages (Area, WriteDate);
      if (Pack == TRUE)
         PackMessages (Area);
      if (Link == TRUE)
         LinkMessages (Area);

      if (Purge == TRUE || Pack == TRUE || Reindex == TRUE || Link == TRUE || Import != 0 || Export != 0)
         printf (" * Done\n\n");
      else
         printf (" * Nothing to do\n\n");

      if (Cfg != NULL)
         delete Cfg;
   }
}


