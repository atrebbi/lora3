
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

VOID PurgeUsers (USHORT Days, USHORT Level)
{
   USHORT i;
   CHAR Temp[64];
   ULONG Today;
   struct tm *ltm;
   class TUser *User;

   printf (" * Purging Users\n");
   Today = time (NULL);

   if ((User = new TUser ("users")) != NULL) {
      if (User->First () == TRUE)
         do {
            if (Level == 0 || User->Level < Level) {
               i = (USHORT)((Today - User->LastCall) / 86400L);
               if (i >= Days) {
                  ltm = localtime ((time_t *)&User->LastCall);
                  strcpy (Temp, asctime (ltm));
                  Temp[strlen (Temp) - 1] = '\0';
                  printf (" +-- %-30.30s Last: %s (%u days)\n", User->Name, Temp, i);
                  User->Delete ();
               }
            }
         } while (User->Next () == TRUE);
      delete User;
   }
}

VOID PackUsers ()
{
   class TUser *User;

   printf (" * Pack (Compressing) Users\n");

   if ((User = new TUser ("users")) != NULL) {
      User->Pack ();
      delete User;
   }
}

int main (int argc, char *argv[])
{
   int i;
   USHORT Pack, Purge, Level;

   Pack = FALSE;
   Purge = Level = 0;

   printf ("\nLUSER; %s v%s - User maintenance utility\n", NAME, VERSION);
   printf ("       Copyright (c) 1991-96 by Marco Maccaferri. All Rights Reserved.\n\n");

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

      printf ("        -P        Pack (compress) user file\n");
      printf ("        -D[n]     Delete users who haven't called in [n] days\n");
      printf ("        -M[s]     Only purge users with security level less than [s]\n");

      printf ("\n * Please refer to the documentation for a more complete command summary\n\n");
   }
   else {
      for (i = 1; i < argc; i++) {
         if (argv[i][0] == '-' || argv[i][0] == '/') {
            switch (toupper (argv[i][1])) {
               case 'D':
                  Purge = (USHORT)atoi (&argv[i][2]);
                  break;
               case 'M':
                  Level = (USHORT)atoi (&argv[i][2]);
                  break;
               case 'P':
                  Pack = TRUE;
                  break;
            }
         }
      }

      if (Purge != 0)
         PurgeUsers (Purge, Level);
      if (Pack == TRUE)
         PackUsers ();

      if (Purge != 0 || Pack == TRUE)
         printf (" * Done\n\n");
      else
         printf (" * Nothing to do\n\n");
   }

   return 0;
}

