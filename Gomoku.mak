<?xml version='1.0' encoding='utf-8' ?>
<!-- C++Builder XML Project -->
<PROJECT>
  <MACROS>
    <VERSION value="BCB.05.03"/>
    <PROJECT value="Gomoku.exe"/>
    <OBJFILES value="Gomoku.obj UnitMain.obj UnitConnect.obj UnitConnecting.obj UnitSelect.obj 
      UnitAbout.obj"/>
    <RESFILES value="Gomoku.res"/>
    <IDLFILES value=""/>
    <IDLGENFILES value=""/>
    <DEFFILE value=""/>
    <RESDEPEN value="$(RESFILES) UnitMain.dfm UnitConnect.dfm UnitConnecting.dfm UnitSelect.dfm 
      UnitAbout.dfm"/>
    <LIBFILES value=""/>
    <LIBRARIES value="VCLX50.lib NMFast50.lib Vcl50.lib"/>
    <SPARELIBS value="Vcl50.lib NMFast50.lib VCLX50.lib"/>
    <PACKAGES value="Vcl50.bpi Vclx50.bpi bcbsmp50.bpi Vcldb50.bpi vclie50.bpi Inetdb50.bpi 
      Inet50.bpi webmid50.bpi"/>
    <PATHCPP value=".;"/>
    <PATHPAS value=".;"/>
    <PATHRC value=".;"/>
    <PATHASM value=".;"/>
    <DEBUGLIBPATH value="$(BCB)\lib\debug"/>
    <RELEASELIBPATH value="$(BCB)\lib\release"/>
    <LINKER value="ilink32"/>
    <USERDEFINES value=""/>
    <SYSDEFINES value="NO_STRICT"/>
    <MAINSOURCE value="Gomoku.cpp"/>
    <INCLUDEPATH value="&quot;C:\Program Files\Borland\CBuilder5\Projects\&quot;;$(BCB)\include;$(BCB)\include\vcl"/>
    <LIBPATH value="&quot;C:\Program Files\Borland\CBuilder5\Projects\&quot;;$(BCB)\lib\obj;$(BCB)\lib"/>
    <WARNINGS value="-w-par"/>
    <WARNOPTSTR value=""/>
  </MACROS>
  <OPTIONS>
    <IDLCFLAGS value="-I&quot;C:\Program Files\Borland\CBuilder5\Projects\.&quot; -I$(BCB)\include 
      -I$(BCB)\include\vcl -src_suffix cpp -boa"/>
    <CFLAG1 value="-O2 -H=$(BCB)\lib\vcl50.csm -Hc -Vx -Ve -X- -a8 -5 -b- -k- -vi -c -tW -tWM"/>
    <PFLAGS value="-$Y- -$L- -$D- -v -JPHNE -M"/>
    <RFLAGS value=""/>
    <AFLAGS value="/mx /w2 /zn"/>
    <LFLAGS value="-D&quot;&quot; -aa -Tpe -x -Gn"/>
  </OPTIONS>
  <LINKER>
    <ALLOBJ value="c0w32.obj sysinit.obj $(OBJFILES)"/>
    <ALLRES value="$(RESFILES)"/>
    <ALLLIB value="$(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib"/>
  </LINKER>
  <IDEOPTIONS>
[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0
Locale=1049
CodePage=1251

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[HistoryLists\hlIncludePath]
Count=1
Item0=C:\Program Files\Borland\CBuilder5\Projects\;$(BCB)\include;$(BCB)\include\vcl

[HistoryLists\hlLibraryPath]
Count=1
Item0=C:\Program Files\Borland\CBuilder5\Projects\;$(BCB)\lib\obj;$(BCB)\lib

[HistoryLists\hlDebugSourcePath]
Count=1
Item0=$(BCB)\source\vcl

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

[Parameters]
RunParams=
HostApplication=
RemoteHost=
RemotePath=
RemoteDebug=0

[Compiler]
ShowInfoMsgs=0
LinkDebugVcl=0
LinkCGLIB=0

[CORBA]
AddServerUnit=1
AddClientUnit=1
PrecompiledHeaders=1
  </IDEOPTIONS>
</PROJECT>