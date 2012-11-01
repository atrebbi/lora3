
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
#include "combase.h"

TScreen::TScreen (void)
{
   wh = 0;
   Ansi = FALSE;
   Prec = 0;
   Attr = BLACK|_LGREY;
   RxBytes = 0;
   RxPosition = 0;
   Counter = 0;
}

TScreen::~TScreen (void)
{
   if (wh != -1) {
      wactiv (wh);
      wclose ();
      wclose ();
   }

   hidecur ();

#if defined(__NT__)
   FreeConsole ();
#endif
}

USHORT TScreen::BytesReady (VOID)
{
   int c;
   USHORT RetVal = FALSE;

   while (kbmhit ()) {
      c = (USHORT)getxch ();
      if (c == 0x4800) {
         memcpy (&RxBuffer[RxBytes], "\x1B[A", 3);
         RxBytes += 3;
      }
      else if (c == 0x5000) {
         memcpy (&RxBuffer[RxBytes], "\x1B[B", 3);
         RxBytes += 3;
      }
      else if (c == 0x4D00) {
         memcpy (&RxBuffer[RxBytes], "\x1B[C", 3);
         RxBytes += 3;
      }
      else if (c == 0x4B00) {
         memcpy (&RxBuffer[RxBytes], "\x1B[D", 3);
         RxBytes += 3;
      }
      else if (c == 0x4700) {
         memcpy (&RxBuffer[RxBytes], "\x1B[H", 3);
         RxBytes += 3;
      }
      else if (c == 0x4F00) {
         memcpy (&RxBuffer[RxBytes], "\x1B[K", 3);
         RxBytes += 3;
      }
      else if (c == 0x5300) {
         memcpy (&RxBuffer[RxBytes], "\x7F", 1);
         RxBytes += 1;
      }
      else if (c == 0x2300)      // Alt-H = Hangup
         Running = FALSE;
      else
         RxBuffer[RxBytes++] = (UCHAR)c;
   }
   if (RxBytes > 0)
      RetVal = TRUE;

#if defined(__OS2__)
   if (RetVal == FALSE)
      DosSleep (1L);
#elif defined(__NT__)
   if (RetVal == FALSE)
      Sleep (1L);
#endif

   return (RetVal);
}

VOID TScreen::BufferByte (UCHAR byte)
{
   short x, y;
   USHORT i;

   if (byte == '[' && Prec == ESC) {
      Ansi = TRUE;
      Count = 0;
      Params[Count] = 0;
   }
   else {
      if (Ansi == TRUE) {
         if (isalpha (byte)) {
            if (byte == 'm') {
               for (i = 0; i <= Count; i++) {
                  if (Params[i] >= 30 && Params[i] <= 39)
                     Attr &= 0xF8;
                  else if (Params[i] >= 40 && Params[i] <= 49)
                     Attr &= 0x8F;

                  switch (Params[i]) {
                     case 0:
                        Attr = 7;
                        break;
                     case 1:
                        Attr |= 0x08;
                        break;
                     case 5:
                        Attr |= BLINK;
                        break;
                     case 30:
                        Attr |= BLACK;
                        break;
                     case 34:
                        Attr |= BLUE;
                        break;
                     case 32:
                        Attr |= GREEN;
                        break;
                     case 36:
                        Attr |= CYAN;
                        break;
                     case 31:
                        Attr |= RED;
                        break;
                     case 35:
                        Attr |= MAGENTA;
                        break;
                     case 39:
                        Attr |= BROWN;
                        break;
                     case 37:
                        Attr |= LGREY;
                        break;
                     case 33:
                        Attr |= YELLOW;
                        break;
                     case 40:
                        Attr |= _BLACK;
                        break;
                     case 44:
                        Attr |= _BLUE;
                        break;
                     case 42:
                        Attr |= _GREEN;
                        break;
                     case 46:
                        Attr |= _CYAN;
                        break;
                     case 41:
                        Attr |= _RED;
                        break;
                     case 45:
                        Attr |= _MAGENTA;
                        break;
                     case 49:
                        Attr |= _BROWN;
                        break;
                     case 47:
                        Attr |= _LGREY;
                        break;
                  }
               }
               wtextattr (Attr);
            }
            else if (byte == 'A') {
               wreadcur (&y, &x);
               if (Params[0] == 0)
                  Params[0] = 1;
               wgotoxy ((SHORT)(y - Params[0]), x);
            }
            else if (byte == 'B') {
               wreadcur (&y, &x);
               if (Params[0] == 0)
                  Params[0] = 1;
               wgotoxy ((SHORT)(y + Params[0]), x);
            }
            else if (byte == 'C') {
               wreadcur (&y, &x);
               if (Params[0] == 0)
                  Params[0] = 1;
               wgotoxy (y, (SHORT)(x + Params[0]));
            }
            else if (byte == 'D') {
               wreadcur (&y, &x);
               if (Params[0] == 0)
                  Params[0] = 1;
               wgotoxy (y, (SHORT)(x - Params[0]));
            }
            else if (byte == 'n') {
               if (Params[0] == 6) {
                  memcpy (RxBuffer, "\x1B[0;0h", 6);
                  RxBytes = 6;
                  RxPosition = 0;
               }
            }
            else if (byte == 'f' || byte == 'H')
               wgotoxy ((SHORT)(Params[0] - 1), (SHORT)(Params[1] - 1));
            else if (byte == 'J' && Params[0] == 2)
               wclear ();
            else if (byte == 'K')
               wclreol ();
            Ansi = FALSE;
         }
         else if (byte == ';') {
            Count++;
            Params[Count] = 0;
         }
         else if (isdigit (byte)) {
            Params[Count] *= 10;
            Params[Count] += (USHORT)(byte - '0');
         }
         else
            Ansi = FALSE;
      }
      else if (byte == CTRLL) {
         wclear ();
         videoupdate ();
      }
      else if (byte != ESC)
         wputc (byte);
   }

   Prec = byte;

   if ((++Counter % 64) == 0) {
      videoupdate ();
      Counter = 0;
   }
}

VOID TScreen::BufferBytes (UCHAR *bytes, USHORT len)
{
   while (len-- > 0)
      BufferByte (*bytes++);
}

USHORT TScreen::Carrier (VOID)
{
   return (Running);
}

VOID TScreen::ClearOutbound (VOID)
{
   TxBytes = 0;
}

VOID TScreen::ClearInbound (VOID)
{
   RxBytes = 0;
}

USHORT TScreen::Initialize (VOID)
{
   USHORT RetVal = FALSE;

   RxBytes = 0;
   RxPosition = 0;
   Running = TRUE;

#if defined(__NT__)
   AllocConsole ();
#endif

#if defined(__OS2__) || defined(__NT__)
   videoinit ();
#endif
   if ((wh = wopen (0, 0, (short)(24 - 1), 79, 5, LGREY|_BLACK, LGREY|_BLACK)) != -1) {
      wopen (24, 0, 24, 79, 5, WHITE|_BLUE, WHITE|_BLUE);
      wprintc (0, 22, WHITE|_BLUE, '�');
      wprintc (0, 43, WHITE|_BLUE, '�');
      wprintc (0, 58, WHITE|_BLUE, '�');
      wprintc (0, 69, WHITE|_BLUE, '�');
      wactiv (wh);
      showcur ();
      RetVal = TRUE;
   }
   videoupdate ();

   return (RetVal);
}

UCHAR TScreen::ReadByte (VOID)
{
   UCHAR c;

   if (RxBytes == 0)
      return ((UCHAR)getxch ());
   else {
      c = RxBuffer[RxPosition++];
      if (--RxBytes == 0)
         RxPosition = 0;
      return (c);
   }
}

USHORT TScreen::ReadBytes (UCHAR *bytes, USHORT len)
{
   USHORT Max = 0;
   USHORT c;

   if ((Max = len) > RxBytes)
      Max = RxBytes;
   if (Max > 0)
      memcpy (bytes, &RxBuffer[RxPosition], Max);
   RxPosition += Max;
   if ((RxBytes -= Max) == 0)
      RxPosition = 0;
   while (kbhit ()) {
      c = (USHORT)getxch ();
      if (c == 0x4800) {
         memcpy (&bytes[Max], "\x1B[A", 3);
         Max += 3;
      }
      else if (c == 0x5000) {
         memcpy (&bytes[Max], "\x1B[B", 3);
         Max += 3;
      }
      else if (c == 0x4D00) {
         memcpy (&bytes[Max], "\x1B[C", 3);
         Max += 3;
      }
      else if (c == 0x4B00) {
         memcpy (&bytes[Max], "\x1B[D", 3);
         Max += 3;
      }
      else if (c == 0x4700) {
         memcpy (&bytes[Max], "\x1B[H", 3);
         Max += 3;
      }
      else if (c == 0x4F00) {
         memcpy (&bytes[Max], "\x1B[K", 3);
         Max += 3;
      }
      else if (c == 0x2300)      // Alt-H = Hangup
         Running = FALSE;
      else
         bytes[Max++] = (UCHAR)c;
   }

   return (Max);
}

VOID TScreen::SendByte (UCHAR byte)
{
   BufferByte (byte);
   videoupdate ();
}

VOID TScreen::SendBytes (UCHAR *bytes, USHORT len)
{
   BufferBytes (bytes, len);
   videoupdate ();
}

VOID TScreen::UnbufferBytes (VOID)
{
   videoupdate ();
}

VOID TScreen::SetName (PSZ name)
{
   CHAR Temp[48];

   sprintf (Temp, "%-20.20s", name);
   prints (24, 1, WHITE|_BLUE, Temp);
   videoupdate ();
}

VOID TScreen::SetCity (PSZ name)
{
   CHAR Temp[48];

   sprintf (Temp, "%-18.18s", name);
   prints (24, 24, WHITE|_BLUE, Temp);
   videoupdate ();
}

VOID TScreen::SetLevel (PSZ level)
{
   CHAR Temp[48];

   sprintf (Temp, "%-12.12s", level);
   prints (24, 45, WHITE|_BLUE, Temp);
   videoupdate ();
}

VOID TScreen::SetTimeLeft (ULONG seconds)
{
   CHAR Temp[48];

   if (seconds >= 3600L)
      sprintf (Temp, "%2d:%02d:%02d", seconds / 3600L, (seconds % 3600L) / 60L, (seconds % 3600L) % 60L);
   else
      sprintf (Temp, "  %2d:%02d", seconds / 60L, seconds % 60L);
   prints (24, 60, WHITE|_BLUE, Temp);
   videoupdate ();
}

VOID TScreen::SetTime (ULONG seconds)
{
   CHAR Temp[48];
   struct tm *ltm;

   ltm = localtime ((time_t *)&seconds);
   sprintf (Temp, "%2d:%02d:%02d", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
   prints (24, 71, WHITE|_BLUE, Temp);
   videoupdate ();
}


