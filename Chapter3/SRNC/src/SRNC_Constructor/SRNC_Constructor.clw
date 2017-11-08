; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSRNC_ConstructorDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SRNC_Constructor.h"

ClassCount=3
Class1=CSRNC_ConstructorApp
Class2=CSRNC_ConstructorDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SRNC_CONSTRUCTOR_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_DIALOG1
Resource6=IDD_SRNC_CONSTRUCTOR_DIALOG (English (U.S.))

[CLS:CSRNC_ConstructorApp]
Type=0
HeaderFile=SRNC_Constructor.h
ImplementationFile=SRNC_Constructor.cpp
Filter=N

[CLS:CSRNC_ConstructorDlg]
Type=0
HeaderFile=SRNC_ConstructorDlg.h
ImplementationFile=SRNC_ConstructorDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_CHECK_LinkNum

[CLS:CAboutDlg]
Type=0
HeaderFile=SRNC_ConstructorDlg.h
ImplementationFile=SRNC_ConstructorDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_SRNC_CONSTRUCTOR_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CSRNC_ConstructorDlg

[DLG:IDD_SRNC_CONSTRUCTOR_DIALOG (English (U.S.))]
Type=1
Class=CSRNC_ConstructorDlg
ControlCount=13
Control1=IDC_CHECK_NodeNum,button,1342242819
Control2=IDC_BUTTON_Maxflow,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO_algorithm,button,1342308361
Control5=IDC_RADIO_Dalgorithm,button,1342177289
Control6=IDC_BUTTON_ImportTopo,button,1342242816
Control7=IDC_CHECK_LinkNum,button,1342242819
Control8=IDC_STATIC1,static,1342308352
Control9=IDC_EDIT1,edit,1353777348
Control10=IDC_BUTTON_AssignCode,button,1342242816
Control11=IDC_STATIC_GCV,static,1342308352
Control12=IDC_BUTTON_Check,button,1342242816
Control13=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

