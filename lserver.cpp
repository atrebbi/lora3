
// ----------------------------------------------------------------------
// LoraBBS Professional Edition - Version 3.00.6
// Copyright (c) 1996 by Marco Maccaferri. All rights reserved.
//
// History:
//    13/06/96 - Initial coding.
// ----------------------------------------------------------------------

#include "_ldefs.h"
#include "lserver.h"
#include "lora.h"

#if defined(__OS2__)
#define IDOK            1
#define IDCANCEL        2
#endif

#define WMU_ADDITEM        1
#define WMU_CLEAR          2

#if defined(__OS2__)
HAB  hab;
HWND hwndMainFrame, hwndMainClient;
HWND hwndBBS, hwndFTP, hwndMail, hwndNews, hwndWeb;
#elif defined(__NT__)
HINSTANCE hinst;
HWND hwndMainClient, hwndMainList;
#endif

// ---------------------------------------------------------------------------

USHORT BM_QueryCheck (HWND m_hWnd, int id)
{
   return ((USHORT)WinSendDlgItemMsg (m_hWnd, id, BM_QUERYCHECK, 0L, 0L));
}

VOID BM_SetCheck (HWND m_hWnd, int id, USHORT value)
{
   WinSendDlgItemMsg (m_hWnd, id, BM_SETCHECK, MPFROMSHORT (value), 0L);
}

VOID SetDlgItemText (HWND m_hWnd, int id, PSZ text)
{
   WinSetDlgItemText (m_hWnd, id, text);
}

// ---------------------------------------------------------------------------

class TPMLog : public TLog
{
public:
   TPMLog (HWND hwnd);
   ~TPMLog (void);

   VOID   Write (PSZ pszFormat, ...);
   VOID   WriteSend (PSZ pszFormat, ...);

private:
   HWND   hwndList;
#if defined(__OS2__)
   HMTX   hmtx;
#endif
};

TPMLog::TPMLog (HWND hwnd)
{
   hwndList = hwnd;
#if defined(__OS2__)
   DosCreateMutexSem ("\\SEM32\\INETLOG", &hmtx, 0L, FALSE);
#endif
}

TPMLog::~TPMLog (void)
{
#if defined(__OS2__)
   DosCloseMutexSem (hmtx);
#endif
}

VOID TPMLog::Write (PSZ pszFormat, ...)
{
   va_list arglist;
   PSZ MsgTemp;
   time_t t;
   struct tm *timep;

#if defined(__OS2__)
   DosRequestMutexSem (hmtx, -1);
#endif

   va_start (arglist, pszFormat);
   vsprintf (Buffer, pszFormat, arglist);
   va_end (arglist);

   t = time (NULL);
   timep = localtime (&t);
   sprintf (Temp, "%c %02d %3s %02d:%02d:%02d %s %s", Buffer[0], timep->tm_mday, Months[timep->tm_mon], timep->tm_hour, timep->tm_min, timep->tm_sec, "LORA", &Buffer[1]);

   if (fp != NULL) {
      fprintf (fp, "%s\n", Temp);
      fflush (fp);
   }

   if (hwndList != NULL) {
      sprintf (Temp, "%c %02d:%02d %s", Buffer[0], timep->tm_hour, timep->tm_min, &Buffer[1]);
      if ((MsgTemp = (PSZ)malloc (strlen (Temp) + 1)) != NULL) {
         strcpy (MsgTemp, Temp);
#if defined(__OS2__)
         WinPostMsg (hwndList, WM_USER, MPFROMSHORT (WMU_ADDITEM), MPFROMP (MsgTemp));
#elif defined(__NT__)
         PostMessage (hwndList, WM_USER, WMU_ADDITEM, (LPARAM)MsgTemp);
#endif
      }
   }

#if defined(__OS2__)
   DosReleaseMutexSem (hmtx);
#endif
}

VOID TPMLog::WriteSend (PSZ pszFormat, ...)
{
   va_list arglist;
   PSZ MsgTemp;
   time_t t;
   struct tm *timep;

#if defined(__OS2__)
   DosRequestMutexSem (hmtx, -1);
#endif

   va_start (arglist, pszFormat);
   vsprintf (Buffer, pszFormat, arglist);
   va_end (arglist);

   t = time (NULL);
   timep = localtime (&t);
   sprintf (Temp, "%c %02d %3s %02d:%02d:%02d %s %s", Buffer[0], timep->tm_mday, Months[timep->tm_mon], timep->tm_hour, timep->tm_min, timep->tm_sec, "LORA", &Buffer[1]);

   if (fp != NULL) {
      fprintf (fp, "%s\n", Temp);
      fflush (fp);
   }

   if (hwndList != NULL) {
      sprintf (Temp, "%c %02d:%02d %s", Buffer[0], timep->tm_hour, timep->tm_min, &Buffer[1]);
      if ((MsgTemp = (PSZ)malloc (strlen (Temp) + 1)) != NULL) {
         strcpy (MsgTemp, Temp);
#if defined(__OS2__)
         WinSendMsg (hwndList, WM_USER, MPFROMSHORT (WMU_ADDITEM), MPFROMP (MsgTemp));
#elif defined(__NT__)
         SendMessage (hwndList, WM_USER, WMU_ADDITEM, (LPARAM)MsgTemp);
#endif
      }
   }

#if defined(__OS2__)
   DosReleaseMutexSem (hmtx);
#endif
}

// ----------------------------------------------------------------------------

#define MAX_TELNET_SLOTS      16

USHORT TelnetSlots[MAX_TELNET_SLOTS];
USHORT WebInit, MailInit, PopInit, FtpInit, TelnetInit, NewsInit;
class  TConfig *Cfg;
class  TPMLog *Log;
class  TTcpip *Web, *Mail, *Pop, *Ftp, *Telnet, *News;

// ----------------------------------------------------------------------------

VOID WebThread (PVOID Args)
{
   class TTcpip *Data;
   class TWeb *Server;

#if defined(__OS2__)
//   DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0);
#endif

   if ((Data = (class TTcpip *)Args) != NULL) {
      if ((Server = new TWeb) != NULL) {
         Server->Tcp = Data;
         Server->Cfg = Cfg;
         Server->Log = Log;
         Server->Run ();
      }
      Data->ClosePort ();
      delete Data;
   }

   _endthread ();
}

VOID FtpThread (PVOID Args)
{
   class TTcpip *Data;
   class TFTP *Server;

#if defined(__OS2__)
//   DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0);
#elif defined(__NT__)
//   SetPriorityClass (NULL, IDLE_PRIORITY_CLASS);
#endif

   if ((Data = (class TTcpip *)Args) != NULL) {
      if ((Server = new TFTP) != NULL) {
         Server->Tcp = Data;
         Server->Cfg = Cfg;
         Server->Log = Log;
         strcpy (Server->ClientIP, Data->ClientIP);
         if (Server->Login () == TRUE)
            Server->Run ();
      }
      Data->ClosePort ();
      delete Data;
   }

   _endthread ();
}

VOID PopThread (PVOID Args)
{
   class TTcpip *Data;
   class TPOP3 *Server;

#if defined(__OS2__)
//   DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0);
#endif

   if ((Data = (class TTcpip *)Args) != NULL) {
      if ((Server = new TPOP3) != NULL) {
         Server->Tcp = Data;
         Server->Cfg = Cfg;
         Server->Log = Log;
         Server->Run ();
      }
      Data->ClosePort ();
      delete Data;
   }

   _endthread ();
}

VOID NewsThread (PVOID Args)
{
   class TTcpip *Data;
   class TNNTP *Server;

#if defined(__OS2__)
//   DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0);
#endif

   if ((Data = (class TTcpip *)Args) != NULL) {
      if ((Server = new TNNTP) != NULL) {
         Server->Tcp = Data;
         Server->Cfg = Cfg;
         Server->Log = Log;
         Server->Run ();
      }
      Data->ClosePort ();
      delete Data;
   }

   _endthread ();
}

VOID BbsThread (PVOID Args)
{
   USHORT i, Mailer, Task = 1;
   CHAR Temp[128], Title[64], CtlName[64];
#if defined(__OS2__)
   CHAR ObjBuf[64];
   ULONG id;
   STARTDATA StartData;
   PID Pid;
#endif
   class TTcpip *Data;
   class TBbs *Bbs;
   class TLog *BBSLog;
   class TPipe *Pipe;

#if defined(__OS2__)
//   DosSetPriority (PRTYS_THREAD, PRTYC_IDLETIME, PRTYD_MAXIMUM, 0);
#endif

   if ((Data = (class TTcpip *)Args) != NULL) {
      Mailer = FALSE;
      for (i = 0; i < MAX_TELNET_SLOTS; i++) {
         if (TelnetSlots[i] == FALSE) {
            TelnetSlots[i] = TRUE;
            Task = (USHORT)(Cfg->TaskNumber + i);
            break;
         }
      }
      if (i < MAX_TELNET_SLOTS) {
         if ((BBSLog = new TLog) != NULL) {
            sprintf (Temp, Cfg->LogFile, Task);
            BBSLog->Open (Temp);
         }
         if ((Bbs = new TBbs) != NULL) {
            if ((Pipe = new TPipe) != NULL) {
               sprintf (Title, "Snoop - Line %u", Cfg->TaskNumber);
               sprintf (Temp, "\\PIPE\\SNOOP%u", Cfg->TaskNumber);
               sprintf (CtlName, "\\PIPE\\CTL%u", Cfg->TaskNumber);

#if defined(__OS2__)
               memset (&StartData, 0, sizeof (STARTDATA));
               StartData.Length = sizeof (STARTDATA);
               StartData.Related = SSF_RELATED_CHILD;
               StartData.FgBg = SSF_FGBG_BACK;
               StartData.TraceOpt = SSF_TRACEOPT_NONE;
               StartData.PgmTitle = Title;
               StartData.PgmName = "SNOOP.EXE";
               StartData.PgmInputs = Temp;
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
               DosStartSession (&StartData, &id, &Pid);

               if (Pipe->Initialize (Temp, CtlName, 1) == TRUE)
                  Bbs->Snoop = Pipe;
#endif
            }

            Bbs->Log = BBSLog;
            Bbs->Cfg = Cfg;
            Bbs->Com = Data;
            Bbs->Task = Task;
            Bbs->Speed = 57600L;

            Log->Write ("+BBS started on task #%d", Task);
            Data->SendBytes ((UCHAR *)"\xFF\xFD\x01\xFF\xFD\x00\xFF\xFB\x01\xFF\xFB\x00", 12);

            Bbs->Run ();
            Mailer = Bbs->Remote;

            if (Pipe != NULL) {
#if defined(__OS2__)
               DosStopSession (STOP_SESSION_SPECIFIED, id);
#endif
               delete Pipe;
            }

            delete Bbs;
         }

         if (BBSLog != NULL)
            delete BBSLog;

         Log->Write (":Task #%d terminated", Task);
         TelnetSlots[i] = FALSE;
      }
      Data->ClosePort ();
      delete Data;
   }
}

// ----------------------------------------------------------------------------

#if defined(__OS2__)
MRESULT EXPENTRY MainWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
#elif defined(__NT__)
LRESULT CALLBACK MainWinProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#endif
{
   switch (msg) {
      case WM_CREATE: {
#if defined(__OS2__)
         HWND hwndMainList;

         if ((hwndMainList = WinCreateWindow (hwnd, WC_LISTBOX, NULL, LS_NOADJUSTPOS|LS_HORZSCROLL|WS_GROUP|WS_TABSTOP|WS_VISIBLE, 0, 0, 0, 0, hwnd, HWND_TOP, 101, NULL, NULL)) != NULLHANDLE)
            WinSetPresParam (hwndMainList, PP_FONTNAMESIZE, 14, "11.System VIO");
#elif defined(__NT__)
         LOGFONT logFont;
         HFONT hFont;

         if ((hwndMainList = CreateWindow ("LISTBOX", "", LBS_NOINTEGRALHEIGHT|LBS_MULTIPLESEL|WS_CHILD, 0, 0, 100, 50, hwnd, NULL, hinst, NULL)) != NULL) {
            logFont.lfHeight = 12;
            logFont.lfWidth = 8;
            logFont.lfEscapement = 0;
            logFont.lfOrientation = 0;
            logFont.lfWeight = FW_NORMAL;
            logFont.lfItalic = FALSE;
            logFont.lfUnderline = FALSE;
            logFont.lfStrikeOut = FALSE;
            logFont.lfCharSet = OEM_CHARSET;
            logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
            logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
            logFont.lfQuality = DEFAULT_QUALITY;
            logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
            strcpy (logFont.lfFaceName, "Fixedsys");
            if ((hFont = CreateFontIndirect (&logFont)) != NULL)
               SendMessage (hwndMainList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM (FALSE, 0));
            ShowWindow (hwndMainList, SW_SHOW);
         }
#endif
         if (hwndMainList != NULL) {
            if ((Log = new TPMLog (hwnd)) != NULL) {
               Log->Open ("server.log");
#if defined(__OS2__)
               Log->Write ("+Begin, v%s (OS/2)", VERSION);
#elif defined(__NT__)
               Log->Write ("+Begin, v%s (Win32)", VERSION);
#endif
            }
         }

         Web = Mail = Pop = Ftp = Telnet = News = NULL;
         WebInit = MailInit = PopInit = FALSE;
         FtpInit = TelnetInit = NewsInit = FALSE;

         Telnet = new TTcpip;
         Ftp = new TTcpip;
         Web = new TTcpip;
         Pop = new TTcpip;
         News = new TTcpip;
         break;
      }

#if defined(__NT__)
      case WM_CTLCOLORLISTBOX: {
         LOGBRUSH logBrush;

         SetBkColor ((HDC)wParam, GetSysColor (COLOR_WINDOW));

         logBrush.lbStyle = BS_SOLID;
         logBrush.lbColor = GetSysColor (COLOR_WINDOW);
         logBrush.lbHatch = 0;

         return ((BOOL)CreateBrushIndirect (&logBrush));
      }
#endif

      case WM_USER:
#if defined(__OS2__)
         switch (SHORT1FROMMP (mp1)) {
#elif defined(__NT__)
         switch (wParam) {
#endif
            case WMU_ADDITEM: {
               USHORT Item;

#if defined(__OS2__)
               if ((USHORT)WinSendMsg (WinWindowFromID (hwnd, 101), LM_QUERYITEMCOUNT, 0L, 0L) > 200)
                  WinSendMsg (WinWindowFromID (hwnd, 101), LM_DELETEITEM, MPFROMSHORT (0), 0L);

               Item = (USHORT)WinSendMsg (WinWindowFromID (hwnd, 101), LM_INSERTITEM, MPFROMSHORT (LIT_END), mp2);
               WinSendMsg (WinWindowFromID (hwnd, 101), LM_SELECTITEM, MPFROMSHORT (Item), MPFROMSHORT (TRUE));
               free ((PSZ)mp2);
#elif defined(__NT__)
               SendMessage (hwndMainList, LB_SETSEL, FALSE, (LPARAM)-1);
               Item = (USHORT)SendMessage (hwndMainList, LB_ADDSTRING, 0, lParam);
               SendMessage (hwndMainList, LB_SETSEL, TRUE, (LPARAM)Item);
               free ((PSZ)lParam);
#endif
               break;
            }

            case WMU_CLEAR:
#if defined(__OS2__)
               WinSendMsg (WinWindowFromID (hwnd, 101), LM_DELETEALL, 0L, 0L);
#elif defined(__NT__)
#endif
               break;
         }
         break;

      case WM_TIMER: {
         USHORT Socket;
         class TTcpip *Data;

#if defined(__OS2__)
         if (SHORT1FROMMP (mp1) == 2) {
            ULONG Value[3];

            Value[0] = 0L;
            DosQuerySysInfo (20, 20, (UCHAR *)Value, sizeof (Value));
            Log->Write ("+%lu bytes remain in heap", Value[0]);
         }
#endif

         if (Web != NULL && WebInit == TRUE) {
            if ((Socket = Web->WaitClient ()) != 0) {
               Log->Write (":From %s (%s)", Web->ClientName, Web->ClientIP);
               if ((Data = new TTcpip) != NULL) {
                  Data->Initialize (0, Socket);
#if defined(__BORLANDC__)
                  _beginthread (WebThread, 8192, (PVOID)Data);
#elif defined(_MSC_VER)
                  DWORD ThreadId;

                  CreateThread (NULL, 8192, (LPTHREAD_START_ROUTINE)WebThread, (PVOID)Data, 0L, &ThreadId);
#else
                  _beginthread (WebThread, NULL, 8192U, (PVOID)Data);
#endif
               }
            }
         }
         if (Ftp != NULL && FtpInit == TRUE) {
            if ((Socket = Ftp->WaitClient ()) != 0) {
               Log->Write (":FTP: Incoming from %s (%s)", Ftp->ClientName, Ftp->ClientIP);
               if ((Data = new TTcpip) != NULL) {
                  Data->Initialize (0, Socket);
                  strcpy (Data->ClientIP, Ftp->ClientIP);
#if defined(__BORLANDC__)
                  _beginthread (FtpThread, 8192, (PVOID)Data);
#elif defined(_MSC_VER)
                  DWORD ThreadId;

                  CreateThread (NULL, 8192, (LPTHREAD_START_ROUTINE)FtpThread, (PVOID)Data, 0L, &ThreadId);
#else
                  _beginthread (FtpThread, NULL, 32768U, (PVOID)Data);
#endif
               }
            }
         }
         if (Telnet != NULL && TelnetInit == TRUE) {
            if ((Socket = Telnet->WaitClient ()) != 0) {
               Log->Write ("+Telnet: Incoming from %s (%s)", Telnet->ClientName, Telnet->ClientIP);
               if ((Data = new TTcpip) != NULL) {
                  Log->Write (":Telnet socket #%d", Socket);
                  Data->Initialize (0, Socket);
#if defined(__BORLANDC__)
                  _beginthread (BbsThread, 8192, (PVOID)Data);
#elif defined(_MSC_VER)
                  DWORD ThreadId;

                  CreateThread (NULL, 8192, (LPTHREAD_START_ROUTINE)BbsThread, (PVOID)Data, 0L, &ThreadId);
#else
                  _beginthread (BbsThread, NULL, 32768U, (PVOID)Data);
#endif
               }
            }
         }
         if (Pop != NULL && PopInit == TRUE) {
            if ((Socket = Pop->WaitClient ()) != 0) {
               Log->Write (":POP3: Incoming from %s (%s)", Pop->ClientName, Pop->ClientIP);
               if ((Data = new TTcpip) != NULL) {
                  Data->Initialize (0, Socket);
#if defined(__BORLANDC__)
                  _beginthread (PopThread, 8192, (PVOID)Data);
#elif defined(_MSC_VER)
                  DWORD ThreadId;

                  CreateThread (NULL, 8192, (LPTHREAD_START_ROUTINE)PopThread, (PVOID)Data, 0L, &ThreadId);
#else
                  _beginthread (PopThread, NULL, 8192, (PVOID)Data);
#endif
               }
            }
         }
         if (News != NULL && NewsInit == TRUE) {
            if ((Socket = News->WaitClient ()) != 0) {
               Log->Write (":NNTP: Incoming from %s (%s)", News->ClientName, News->ClientIP);
               if ((Data = new TTcpip) != NULL) {
                  Data->Initialize (0, Socket);
#if defined(__BORLANDC__)
                  _beginthread (NewsThread, 8192, (PVOID)Data);
#elif defined(_MSC_VER)
                  DWORD ThreadId;

                  CreateThread (NULL, 8192, (LPTHREAD_START_ROUTINE)NewsThread, (PVOID)Data, 0L, &ThreadId);
#else
                  _beginthread (NewsThread, NULL, 8192, (PVOID)Data);
#endif
               }
            }
         }

         // Socket initialisation for servers
         if (Telnet != NULL && TelnetInit == FALSE) {
            if (Telnet->Initialize (23) == TRUE) {
               Log->Write ("+Telnet Server started on port 23");
               TelnetInit = TRUE;
            }
         }
         if (Ftp != NULL && FtpInit == FALSE) {
            if (Ftp->Initialize (121) == TRUE) {
               Log->Write ("+FTP Server started on port 121");
               FtpInit = TRUE;
            }
         }
         if (Web != NULL && WebInit == FALSE) {
            if (Web->Initialize (80) == TRUE) {
               Log->Write ("+HTTP Server started on port 80");
               WebInit = TRUE;
            }
         }
         if (Pop != NULL && PopInit == FALSE) {
            if (Pop->Initialize (110) == TRUE) {
               Log->Write ("+POP3 Server started on port 110");
               PopInit = TRUE;
            }
         }
         if (News != NULL && NewsInit == FALSE) {
            if (News->Initialize (119) == TRUE) {
               Log->Write ("+NNTP Server started on port 119");
               NewsInit = TRUE;
            }
         }
         break;
      }

      case WM_SIZE:
#if defined(__OS2__)
         WinSetWindowPos (WinWindowFromID (hwnd, 101), NULLHANDLE, 0, 0, SHORT1FROMMP (mp2), SHORT2FROMMP (mp2), SWP_SIZE|SWP_SHOW);
#elif defined(__NT__)
         MoveWindow (hwndMainList, 0, 0, LOWORD (lParam), HIWORD (lParam), TRUE);
#endif
         break;

#if defined(__OS2__)
      case WM_ERASEBACKGROUND:
         return ((MRESULT)TRUE);
#endif

      case WM_COMMAND:
#if defined(__OS2__)
         switch (SHORT1FROMMP (mp1)) {
#elif defined(__NT__)
         switch (wParam) {
#endif
            case 206:      // Global / Internet Options
#if defined(__OS2__)
//               if ((USHORT)WinDlgBox (HWND_DESKTOP, hwnd, InternetDlgProc, NULLHANDLE, 23, NULL) == TRUE)
#elif defined(__NT__)
//               if (Win95DialogBox (hinst, "INTERNET", hwnd, (DLGPROC)InternetDlgProc) == TRUE)
#endif
                  Cfg->Save ();
               break;
         }
         break;

#if defined(__OS2__)
      case WM_CONTROL:
         break;
#endif

#if defined(__OS2__)
      case WM_CLOSE:
#elif defined(__NT__)
      case WM_DESTROY:
#endif
         if (Telnet != NULL) {
            Telnet->ClosePort ();
            delete Telnet;
         }
         if (Ftp != NULL) {
            Ftp->ClosePort ();
            delete Ftp;
         }
         if (Web != NULL) {
            Web->ClosePort ();
            delete Web;
         }
         if (Pop != NULL) {
            Pop->ClosePort ();
            delete Pop;
         }
         if (News != NULL) {
            News->ClosePort ();
            delete News;
         }
         if (Log != NULL) {
            Log->Write (":End");
            Log->WriteBlank ();
            delete Log;
         }
#if defined(__NT__)
         PostQuitMessage (0);
#endif
         break;
   }

#if defined(__OS2__)
   return (WinDefWindowProc (hwnd, msg, mp1, mp2));
#elif defined(__NT__)
   return (DefWindowProc (hwnd, msg, wParam, lParam));
#endif
}

#if defined(__OS2__)
MRESULT EXPENTRY DummyDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
#elif defined(__NT__)
LRESULT CALLBACK DummyDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#endif
{
   switch (msg) {
#if defined(__OS2__)
      case WM_INITDLG:
#elif defined(__NT__)
      case WM_CREATE:
#endif
         break;

#if defined(__OS2__)
      case WM_CONTROL:
         return (0);
#endif

      case WM_COMMAND:
         return (0);
   }

#if defined(__OS2__)
   return (WinDefDlgProc (hwnd, msg, mp1, mp2));
#elif defined(__NT__)
   return (0);
#endif
}

#if defined(__OS2__)
MRESULT EXPENTRY FtpDlgProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
#elif defined(__NT__)
LRESULT CALLBACK FtpDlgProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#endif
{
   CHAR Temp[64];

   switch (msg) {
      case WM_INITDLG:
         BM_SetCheck (hwnd, 101, Cfg->FtpServer);
         sprintf (Temp, "%u", Cfg->FtpPort);
         SetDlgItemText (hwnd, 103, Temp);
         break;

      case WM_CONTROL:
         return (0);

      case WM_COMMAND:
         return (0);
   }

   return (WinDefDlgProc (hwnd, msg, mp1, mp2));
}

#if defined(__OS2__)
MRESULT EXPENTRY ServerWinProc (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
#elif defined(__NT__)
LRESULT CALLBACK ServerWinProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
#endif
{
   switch (msg) {
      case WM_CREATE: {
#if defined(__OS2__)
         ULONG style, page;
         HWND hwndCtl;

         style = BKS_SOLIDBIND|BKS_BACKPAGESTR|BKS_MAJORTABTOP|BKS_SQUARETABS|BKS_TABTEXTCENTER|BKS_STATUSTEXTLEFT;
         if ((hwndCtl = WinCreateWindow (hwnd, WC_NOTEBOOK, NULL, style|WS_VISIBLE, 0, 0, 0, 0, hwnd, HWND_TOP, 101, NULL, NULL)) != NULL) {
            WinSendMsg (hwndCtl, BKM_SETDIMENSIONS, MPFROM2SHORT (80, 24), MPFROMSHORT (BKA_MAJORTAB));
            WinSendMsg (hwndCtl, BKM_SETDIMENSIONS, MPFROM2SHORT (0, 0), MPFROMSHORT (BKA_MINORTAB));
            WinSendMsg (hwndCtl, BKM_SETNOTEBOOKCOLORS, MPFROMLONG (SYSCLR_DIALOGBACKGROUND), MPFROMLONG (BKA_BACKGROUNDPAGECOLORINDEX));
            WinSendMsg (hwndCtl, BKM_SETNOTEBOOKCOLORS, MPFROMLONG (SYSCLR_DIALOGBACKGROUND), MPFROMLONG (BKA_BACKGROUNDMAJORCOLORINDEX));

            page = (ULONG)WinSendMsg (hwndCtl, BKM_INSERTPAGE, 0L, MPFROM2SHORT (BKA_MAJOR, BKA_LAST));
            WinSendMsg (hwndCtl, BKM_SETTABTEXT, (MPARAM)page, MPFROMP ("BBS"));
            hwndBBS = WinLoadDlg (hwndCtl, hwndCtl, DummyDlgProc, NULLHANDLE, 301, NULL);
            WinSendMsg (hwndCtl, BKM_SETPAGEWINDOWHWND, MPFROMLONG (page), MPFROMHWND (hwndBBS));

            page = (ULONG)WinSendMsg (hwndCtl, BKM_INSERTPAGE, 0L, MPFROM2SHORT (BKA_MAJOR, BKA_LAST));
            WinSendMsg (hwndCtl, BKM_SETTABTEXT, (MPARAM)page, MPFROMP ("FTP"));
            hwndFTP = WinLoadDlg (hwndCtl, hwndCtl, DummyDlgProc, NULLHANDLE, 302, NULL);
            WinSendMsg (hwndCtl, BKM_SETPAGEWINDOWHWND, MPFROMLONG (page), MPFROMHWND (hwndFTP));

            page = (ULONG)WinSendMsg (hwndCtl, BKM_INSERTPAGE, 0L, MPFROM2SHORT (BKA_MAJOR, BKA_LAST));
            WinSendMsg (hwndCtl, BKM_SETTABTEXT, (MPARAM)page, MPFROMP ("Mail"));
            hwndMail = WinLoadDlg (hwndCtl, hwndCtl, DummyDlgProc, NULLHANDLE, 303, NULL);
            WinSendMsg (hwndCtl, BKM_SETPAGEWINDOWHWND, MPFROMLONG (page), MPFROMHWND (hwndMail));

            page = (ULONG)WinSendMsg (hwndCtl, BKM_INSERTPAGE, 0L, MPFROM2SHORT (BKA_MAJOR, BKA_LAST));
            WinSendMsg (hwndCtl, BKM_SETTABTEXT, (MPARAM)page, MPFROMP ("News"));
            hwndNews = WinLoadDlg (hwndCtl, hwndCtl, DummyDlgProc, NULLHANDLE, 304, NULL);
            WinSendMsg (hwndCtl, BKM_SETPAGEWINDOWHWND, MPFROMLONG (page), MPFROMHWND (hwndNews));

            page = (ULONG)WinSendMsg (hwndCtl, BKM_INSERTPAGE, 0L, MPFROM2SHORT (BKA_MAJOR, BKA_LAST));
            WinSendMsg (hwndCtl, BKM_SETTABTEXT, (MPARAM)page, MPFROMP ("Web"));
            hwndWeb = WinLoadDlg (hwndCtl, hwndCtl, DummyDlgProc, NULLHANDLE, 305, NULL);
            WinSendMsg (hwndCtl, BKM_SETPAGEWINDOWHWND, MPFROMLONG (page), MPFROMHWND (hwndWeb));
         }

         WinPostMsg (hwnd, WM_USER, 0L, 0L);
#elif defined(__NT__)
         PROPSHEETPAGE psp[1];
         PROPSHEETHEADER psh;

         psp[0].dwSize = sizeof (PROPSHEETPAGE);
         psp[0].dwFlags = PSP_USETITLE;
         psp[0].hInstance = hinst;
         psp[0].pszTemplate = MAKEINTRESOURCE (0);
         psp[0].pszIcon = NULL;
         psp[0].pfnDlgProc = NULL;
         psp[0].pszTitle = "BBS";
         psp[0].lParam = 0;

         psh.dwSize = sizeof (PROPSHEETHEADER);
         psh.dwFlags = PSH_PROPSHEETPAGE;
         psh.hwndParent = hwnd;
         psh.hInstance = hinst;
         psh.pszIcon = NULL;
         psh.pszCaption = (LPSTR)"Trackbar Properties";
         psh.nPages = sizeof (psp) / sizeof (PROPSHEETPAGE);
         psh.ppsp = (LPCPROPSHEETPAGE)psp;

         PropertySheet (&psh);
#endif
         break;
      }

      case WM_SIZE:
#if defined(__OS2__)
         WinSetWindowPos (WinWindowFromID (hwnd, 101), NULLHANDLE, 0, 0, SHORT1FROMMP (mp2), SHORT2FROMMP (mp2), SWP_SIZE|SWP_SHOW);
#elif defined(__NT__)
#endif
         break;

#if defined(__OS2__)
      case WM_ERASEBACKGROUND:
         return ((MRESULT)TRUE);
#endif

#if defined(__OS2__)
      case WM_CONTROL:
         break;
#endif

#if defined(__OS2__)
      case WM_CLOSE:
#elif defined(__NT__)
      case WM_DESTROY:
#endif
#if defined(__NT__)
         PostQuitMessage (0);
#endif
         break;
   }

#if defined(__OS2__)
   return (WinDefWindowProc (hwnd, msg, mp1, mp2));
#elif defined(__NT__)
   return (DefWindowProc (hwnd, msg, wParam, lParam));
#endif
}

#if defined(__OS2__)
void main (int argc, char *argv[])
{
   int i, x, y, dx, dy;
   HMQ hmq;
   QMSG qmsg;
   CHAR Title[64], *Config = NULL, *Channel = NULL;
   ULONG flFrame;
   RECTL rc;

   for (i = 1; i < argc; i++) {
      if (Config == NULL)
         Config = argv[i];
      else if (Channel == NULL)
         Channel = argv[i];
   }

   if ((Cfg = new TConfig) != NULL) {
      Cfg->TaskNumber = 1;
      if (Cfg->Load (Config, Channel) == FALSE)
         Cfg->Default ();
   }

   if ((hab = WinInitialize (0)) != 0) {
      if ((hmq = WinCreateMsgQueue (hab, 0)) != 0) {
         WinRegisterClass (hab, "SERVER_WINDOW", ServerWinProc, CS_CLIPCHILDREN|CS_SIZEREDRAW|CS_MOVENOTIFY, 0);

         flFrame = (FCF_TASKLIST|FCF_TITLEBAR|FCF_SYSMENU|FCF_MINMAX|FCF_SIZEBORDER|FCF_NOBYTEALIGN);
         if ((hwndMainFrame = WinCreateStdWindow (HWND_DESKTOP, 0, &flFrame, "SERVER_WINDOW", NULL, 0, NULLHANDLE, 256, &hwndMainClient)) != NULLHANDLE) {
            sprintf (Title, "%s Internet Server %s", NAME, VERSION);
            WinSetWindowText (hwndMainFrame, Title);

            WinQueryWindowRect (HWND_DESKTOP, &rc);
            dx = 480;
            if ((rc.xRight - rc.xLeft) < dx)
               dx = rc.xRight - rc.xLeft;
            dy = 374;
            if ((rc.yTop - rc.yBottom) < dy)
               dy = rc.yTop - rc.yBottom;

            x = ((rc.xRight - rc.xLeft) - dx) / 2;
            y = ((rc.yTop - rc.yBottom) - dy) / 2;

            WinSetWindowPos (hwndMainFrame, NULLHANDLE, x, y, dx, dy, SWP_SIZE|SWP_MOVE|SWP_SHOW|SWP_ACTIVATE);

            while (WinGetMsg (hab, &qmsg, NULLHANDLE, 0, 0))
               WinDispatchMsg (hab, &qmsg);

            WinDestroyWindow (hwndMainFrame);
         }

         WinDestroyMsgQueue (hmq);
      }

      WinTerminate (hab);
   }
}
#elif defined(__NT__)
int PASCAL WinMain (HINSTANCE hinstCurrent, HINSTANCE hinstPrevious, LPSTR lpszCmdLine, int nCmdShow)
{
   CHAR Title[64];
   MSG msg;
   WNDCLASS wc;

   lpszCmdLine = lpszCmdLine;

   if (hinstPrevious == NULL) {
      wc.style         = 0;
      wc.lpfnWndProc   = ServerWinProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hInstance     = hinstCurrent;
      wc.hIcon         = NULL;
      wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
      wc.lpszMenuName  = NULL;
      wc.lpszClassName = "SERVER_WINDOW";

      if (!RegisterClass (&wc))
         return (FALSE);
   }

   hinst = hinstCurrent;
   msg.wParam = FALSE;

   sprintf (Title, "%s Internet Server v%s%s", NAME, VERSION, "");
   if ((hwndMainClient = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, "SERVER_WINDOW", Title, WS_OVERLAPPEDWINDOW, 170, 240, 400, 200, NULL, NULL, hinstCurrent, NULL)) != NULL) {
      ShowWindow (hwndMainClient, nCmdShow);

      while (GetMessage (&msg, NULL, 0, 0)) {
         TranslateMessage (&msg);
         DispatchMessage (&msg);
      }
   }

   return ((int)msg.wParam);
}
#endif

/*
#if defined(__OS2__)
void main (int argc, char *argv[])
{
   int i;
   USHORT Task = 1;
   CHAR Title[128], *Config = NULL, *Channel = NULL;
   HMQ hmq;
   QMSG qmsg;
   ULONG flFrame;
   POINTL aptl[2];

   Log = NULL;

   for (i = 1; i < argc; i++) {
      if (!stricmp (argv[i], "/LINE")) {
         i++;
         Task = (USHORT)atoi (argv[i]);
      }
      else if (Config == NULL)
         Config = argv[i];
      else if (Channel == NULL)
         Channel = argv[i];
   }

   if ((Cfg = new TConfig) != NULL) {
      Cfg->TaskNumber = Task;
      if (Cfg->Load (Config, Channel) == FALSE)
         Cfg->Default ();
   }

   if ((hab = WinInitialize (0)) != 0) {
      if ((hmq = WinCreateMsgQueue (hab, 0)) != 0) {
         WinRegisterClass (hab, "MAIN_WINDOW", MainWinProc, CS_CLIPCHILDREN|CS_SIZEREDRAW|CS_MOVENOTIFY, 0);

         flFrame = (FCF_TASKLIST|FCF_TITLEBAR|FCF_SYSMENU|FCF_MINMAX|FCF_SIZEBORDER|FCF_NOBYTEALIGN|FCF_MENU);
         if ((hwndMainFrame = WinCreateStdWindow (HWND_DESKTOP, 0, &flFrame, "MAIN_WINDOW", NULL, 0, NULLHANDLE, 257, &hwndMainClient)) != NULLHANDLE) {
            sprintf (Title, "%s Internet Server v%s%s", NAME, VERSION, "");
            WinSetWindowText (hwndMainFrame, Title);

            aptl[ 0 ].x = 60;
            aptl[ 0 ].y = 100;
            aptl[ 1 ].x = 250;
            aptl[ 1 ].y = 100;
            WinMapDlgPoints (HWND_DESKTOP, aptl, 2, TRUE);
            WinSetWindowPos (hwndMainFrame, NULLHANDLE, aptl[0].x, aptl[0].y, aptl[1].x, aptl[1].y, SWP_SIZE|SWP_MOVE|SWP_SHOW|SWP_ACTIVATE);

            WinStartTimer (hab, hwndMainClient, 1, 50);

            while (WinGetMsg (hab, &qmsg, NULLHANDLE, 0, 0)) {
               WinDispatchMsg (hab, &qmsg);
            }

            WinStopTimer (hab, hwndMainClient, 1);
            WinDestroyWindow (hwndMainFrame);
         }

         WinDestroyMsgQueue (hmq);
      }
      WinTerminate (hab);
   }

   if (Cfg != NULL)
      delete Cfg;
}
#elif defined(__NT__)
int PASCAL WinMain (HINSTANCE hinstCurrent, HINSTANCE hinstPrevious, LPSTR lpszCmdLine, int nCmdShow)
{
   USHORT Task = 1;
   CHAR Title[128], *Config = NULL, *Channel = NULL;
   MSG msg;
   WNDCLASS wc;

   Log = NULL;
   lpszCmdLine = lpszCmdLine;

   if ((Cfg = new TConfig) != NULL) {
      Cfg->TaskNumber = Task;
      if (Cfg->Load (Config, Channel) == FALSE)
         Cfg->Default ();
   }

   if (hinstPrevious == NULL) {
      wc.style         = 0;
      wc.lpfnWndProc   = MainWinProc;
      wc.cbClsExtra    = 0;
      wc.cbWndExtra    = 0;
      wc.hInstance     = hinstCurrent;
      wc.hIcon         = NULL;
      wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
      wc.lpszMenuName  = "MENU_1";
      wc.lpszClassName = "MAIN_WINDOW";

      if (!RegisterClass (&wc))
         return (FALSE);
   }

   hinst = hinstCurrent;
   msg.wParam = FALSE;

   sprintf (Title, "%s Internet Server v%s%s", NAME, VERSION, "");
   if ((hwndMainClient = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, "MAIN_WINDOW", Title, WS_OVERLAPPEDWINDOW, 170, 240, 400, 200, NULL, NULL, hinstCurrent, NULL)) != NULL) {
      ShowWindow (hwndMainClient, nCmdShow);

      SetTimer (hwndMainClient, 1, 50, NULL);

      while (GetMessage (&msg, NULL, 0, 0)) {
         TranslateMessage (&msg);
         DispatchMessage (&msg);
      }

      KillTimer (hwndMainClient, 1);
   }

   if (Cfg != NULL)
      delete Cfg;

   return ((int)msg.wParam);
}
#endif
*/

