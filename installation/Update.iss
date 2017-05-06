; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！
[Code]

function InitializeSetup(): boolean;
  begin

    result:= true;
    if not RegKeyExists(HKEY_LOCAL_MACHINE,'SOFTWARE\Samwoo\AA\PBXSoftPhone')then
      begin
      result:= false;
      MsgBox('原文件未安装，请先安装原文件',mbInformation, MB_OK);
    end;

end;


[Setup]
; 注意: AppId 值用于唯一识别该应用程序。
; 禁止对其他应用程序的安装器使用相同的 AppId 值！
; (若要生成一个新的 GUID，请选择“工具 | 生成 GUID”。)
AppId={{DA2D7FC2-E751-44CA-A6E5-909CB8937F79}}
AppName=AgentUpdate
AppVerName=AgentUpdate 1.1.5
AppPublisher=AOC
AppPublisherURL=http://www.quanxun.com/
AppSupportURL=http://www.quanxun.com/
AppUpdatesURL=http://www.quanxun.com/
OutputDir=.\
OutputBaseFilename=AgentUpdate
CreateAppDir = yes
DisableDirPage=yes
Compression=lzma/max
SolidCompression=yes
DefaultDirName={reg:HKLM\SOFTWARE\Samwoo\AA\PBXSoftPhone,BinPath|C:\Program Files\CTI\AgentOCX\bin}
Uninstallable=no
PrivilegesRequired=none
AppMutex = AgentUpdate

[Languages]
Name: "chinese"; MessagesFile: "ChineseUpdate.isl"


[Dirs]
Name: "{app}\..\data"
Name: "{app}\..\bin"


[Files]
;Source: ".\..\AgentRun.1.0.4.abs"; DestDir: "{app}";DestName:"AgentRun.abs"; Flags: ignoreversion
Source: ".\..\Prj_Uniland_AgentOCX.ocx"; DestDir: "{app}\..\Dll\"; DestName:"Prj_Uniland_AgentOCX.ocx";Flags: ignoreversion regserver
;Source: ".\..\AgentOCX.dll"; DestDir: "{app}\..\Dll\"; DestName:"AgentOCX.dll";Flags: ignoreversion regserver
Source: ".\..\State.1.1.1.bas"; DestDir: "{app}";DestName:"State.bas"; Flags: ignoreversion

[Registry]
Root: HKLM; Subkey: "SOFTWARE\Samwoo\AA\PBXSoftPhone"; ValueType: string; ValueName: "BinPath"; ValueData:C:\Program Files\CTI\AgentOCX\bin; Flags:createvalueifdoesntexist

