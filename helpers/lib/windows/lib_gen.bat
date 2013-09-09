CALL variables.bat
set chip=%1



xc8 --chip=%chip% --runtime=default,+clear,+init,-keep,-no_startup,+download,-config,+clib,+plib ^
-I%src_path% --OUTDIR=%leop_path% --OUTPUT=lpp --OBJDIR=./trash -Oleonino --CODEOFFSET=2000h ^
%src_path%\usb\ep0.c %src_path%\usb\ep1.c %src_path%\usb\ep2.c %src_path%\usb\usb.c ^
%src_path%\delay.c %src_path%\mem_flash.c

