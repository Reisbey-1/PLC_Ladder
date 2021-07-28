
Ladderps.dll: dlldata.obj Ladder_p.obj Ladder_i.obj
	link /dll /out:Ladderps.dll /def:Ladderps.def /entry:DllMain dlldata.obj Ladder_p.obj Ladder_i.obj \
		kernel32.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Ladderps.dll
	@del Ladderps.lib
	@del Ladderps.exp
	@del dlldata.obj
	@del Ladder_p.obj
	@del Ladder_i.obj
