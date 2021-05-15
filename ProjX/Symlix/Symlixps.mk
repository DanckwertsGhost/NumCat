
Symlixps.dll: dlldata.obj Symlix_p.obj Symlix_i.obj
	link /dll /out:Symlixps.dll /def:Symlixps.def /entry:DllMain dlldata.obj Symlix_p.obj Symlix_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Symlixps.dll
	@del Symlixps.lib
	@del Symlixps.exp
	@del dlldata.obj
	@del Symlix_p.obj
	@del Symlix_i.obj
