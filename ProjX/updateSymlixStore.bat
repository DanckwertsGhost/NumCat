@echo off
echo +
echo ***Update TraceRecorder header files for Symlix***
echo ***Update SymlixStore header and interface description files***
echo +


if exist Symlix\TraceRecorder_i.c echo removing existing Symlix\TraceRecorder_i.c
if exist Symlix\TraceRecorder_i.c del Symlix\TraceRecorder_i.c
if exist Symlix\TraceRecorder.h echo removing existing Symlix\TraceRecorder.h
if exist Symlix\TraceRecorder.h del Symlix\TraceRecorder.h
copy ..\TraceRecorder\TraceRecorder_i.c Symlix\*.*
copy ..\TraceRecorder\TraceRecorder.h Symlix\*.*

if exist SymlixStore_i.c echo removing existing SymlixStore_i.c
if exist SymlixStore_i.c del SymlixStore_i.c
if exist SymlixStore.h echo removing existing SymlixStore.h
if exist SymlixStore.h del SymlixStore.h
if exist Symlix\symlixstore.h echo removing existing symlix\symlixstore.h
if exist Symlix\symlixstore.h del symlix\symlixstore.h
copy ..\SymlixStore\SymlixStore_i.c *.*
copy ..\SymlixStore\SymlixStore.h *.*
copy symlixStore.h Symlix\*.*
dir SymlixStor*.*
dir symlix\symlixStor*.*
dir symlix\TraceRecorder*.*
pause

@echo on

