set chip=%1

set hdr_path=..\..\h\leonino\lion
set src_root_path=..\..\src\leonino
set src_path=%src_root_path%\lion
set leop_path=..\..\lib\lion

set dst_hdr_path=..\..\h\lion\leonino

copy "%src_path%\*.h" "%dst_hdr_path%\"
copy "%src_path%\usb\*.h" "%dst_hdr_path%\usb\"
copy %src_root_path%\leonino.h %hdr_path%\

xc8 --chip=%chip% --runtime=default,+clear,+init,-keep,-no_startup,+download,-config,+clib,+plib ^
-I%src_path% --OUTDIR=%leop_path% --OUTPUT=lpp --OBJDIR=./trash -Oleonino --CODEOFFSET=2000h ^
%src_path%\usb\ep0.c %src_path%\usb\ep1.c %src_path%\usb\ep2.c %src_path%\usb\usb.c ^
%src_path%\delay.c %src_path%\mem_flash.c

