
SymlixStoreps.dll: dlldata.obj SymlixStore_p.obj SymlixStore_i.obj
	link /dll /out:SymlixStoreps.dll /def:SymlixStoreps.def /entry:DllMain dlldata.obj SymlixStore_p.obj SymlixStore_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SymlixStoreps.dll
	@del SymlixStoreps.lib
	@del SymlixStoreps.exp
	@del dlldata.obj
	@del SymlixStore_p.obj
	@del SymlixStore_i.obj
