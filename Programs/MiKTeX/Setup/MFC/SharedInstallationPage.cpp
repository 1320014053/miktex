/* SharedInstallationPage.cpp:

   Copyright (C) 1999-2021 Christian Schenk

   This file is part of the MiKTeX Setup Wizard.

   The MiKTeX Setup Wizard is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX Setup Wizard is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX Setup Wizard; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#include "StdAfx.h"

#include "Setup.h"

#include "SetupWizard.h"
#include "SharedInstallationPage.h"

BEGIN_MESSAGE_MAP(SharedInstallationPage, CPropertyPage)
  ON_BN_CLICKED(IDC_SHARED, OnCommonUserSetup)
END_MESSAGE_MAP();

SharedInstallationPage::SharedInstallationPage() :
  CPropertyPage(IDD, 0, IDS_HEADER_SHARED, IDS_SUBHEADER_SHARED)
{
}

BOOL SharedInstallationPage::OnInitDialog()
{
  sheet = reinterpret_cast<SetupWizard*>(GetParent());

  commonUserSetup = (SetupApp::Instance->IsCommonSetup() ? 0 : 1);

  BOOL ret = CPropertyPage::OnInitDialog();

  try
  {
    if (!session->IsUserAnAdministrator())
    {
      CWnd* wnd = GetDlgItem(IDC_SHARED);
      if (wnd == nullptr)
      {
        MIKTEX_UNEXPECTED();
      }
      wnd->EnableWindow(FALSE);
    }
    CWnd* wnd = GetDlgItem(IDC_JUST_FOR_ME);
    if (wnd == nullptr)
    {
      MIKTEX_UNEXPECTED();
    }
    wchar_t logonName[30];
    DWORD sizeLogonName = sizeof(logonName) / sizeof(logonName[0]);
    if (!GetUserNameW(logonName, &sizeLogonName))
    {
      if (GetLastError() == ERROR_NOT_LOGGED_ON)
      {
        StringUtil::CopyCeeString(logonName, 30, L"unknown user");
      }
      else
      {
        MIKTEX_FATAL_WINDOWS_ERROR("GetUserNameW");
      }
    }
    CString str;
    wnd->GetWindowText(str);
    str += _T(" (");
    str += logonName;
    wchar_t displayName[30];
    ULONG sizeDisplayName = sizeof(displayName) / sizeof(displayName[0]);
    if (GetUserNameExW(NameDisplay, displayName, &sizeDisplayName))
    {
      str += _T(", ");
      str += displayName;
    }
    str += _T(')');
    wnd->SetWindowText(str);
  }
  catch (const MiKTeXException& e)
  {
    ReportError(e);
  }
  catch (const exception& e)
  {
    ReportError(e);
  }

  return ret;
}

BOOL SharedInstallationPage::OnSetActive()
{
  sheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
  return CPropertyPage::OnSetActive();
}

void SharedInstallationPage::DoDataExchange(CDataExchange* dx)
{
  CPropertyPage::DoDataExchange(dx);
  DDX_Radio(dx, IDC_SHARED, commonUserSetup);
}

LRESULT SharedInstallationPage::OnWizardNext()
{
  sheet->PushPage(IDD);
  UINT next;
  if (SetupApp::Instance->Service->GetOptions().IsPrefabricated)
  {
    next = IDD_INSTALLDIR;
  }
  else
  {
    switch (SetupApp::Instance->GetTask())
    {
    case SetupTask::InstallFromCD:
      next = IDD_INSTALLDIR;
      break;
    case SetupTask::InstallFromLocalRepository:
      next = IDD_LOCAL_REPOSITORY;
      break;
    case SetupTask::InstallFromRemoteRepository:
      next = IDD_REMOTE_REPOSITORY;
      break;
    case SetupTask::PrepareMiKTeXDirect:
      next = IDD_SETTINGS;
      break;
    default:
      ASSERT(false);
      __assume(false);
      break;
    }
  }
  return reinterpret_cast<LRESULT>(MAKEINTRESOURCE(next));
}

LRESULT SharedInstallationPage::OnWizardBack()
{
  return reinterpret_cast<LRESULT>(MAKEINTRESOURCE(sheet->PopPage()));
}

BOOL SharedInstallationPage::OnKillActive()
{
  BOOL ret = CPropertyPage::OnKillActive();
  if (ret)
  {
    SetupOptions options = SetupApp::Instance->Service->GetOptions();
    options.IsCommonSetup = (commonUserSetup == 0);
    SetupApp::Instance->Service->SetOptions(options);
  }
  return ret;
}

void SharedInstallationPage::OnCommonUserSetup()
{
  if (showMessageBox)
  {
    showMessageBox = false;
    AfxMessageBox(T_(_T("Choosing this option is rarely a good decision. You have been warned...")), MB_ICONEXCLAMATION | MB_OK);
  }
}
