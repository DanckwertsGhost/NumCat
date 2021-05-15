
ARExcelFuncsps.dll: dlldata.obj ARExcelFuncs_p.obj ARExcelFuncs_i.obj
	link /dll /out:ARExcelFuncsps.dll /def:ARExcelFuncsps.def /entry:DllMain dlldata.obj ARExcelFuncs_p.obj ARExcelFuncs_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ARExcelFuncsps.dll
	@del ARExcelFuncsps.lib
	@del ARExcelFuncsps.exp
	@del dlldata.obj
	@del ARExcelFuncs_p.obj
	@del ARExcelFuncs_i.obj
