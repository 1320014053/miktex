/* PackageInfoDialog.cpp:

   Copyright (C) 2017-2021 Christian Schenk

   This file is part of the MiKTeX UI Library.

   The MiKTeX UI Library is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2, or
   (at your option) any later version.

   The MiKTeX UI Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the MiKTeX UI Library; if not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA. */

#include <QDateTime>
#include <QLocale>
#include <QSortFilterProxyModel>
#include <QtWidgets>

#include "internal.h"

#include "miktex/UI/Qt/PackageInfoDialog.h"

#include "FileTableModel.h"
#include "PackageInfoDialog.h"
#include "ui_PackageInfoDialog.h"

using namespace MiKTeX::Packages;
using namespace MiKTeX::UI::Qt;

QDateTime ToDateTime(time_t t)
{
  return QDateTime::fromTime_t(t);
}

PackageInfoDialogImpl::PackageInfoDialogImpl(QWidget* parent, const PackageInfo& packageInfo) :
  QDialog(parent),
  ui(new Ui::PackageInfoDialog)
{
  ui->setupUi(this);
  ui->leName->setText(QString::fromUtf8(packageInfo.id.c_str()));
  ui->leDate->setText(ToDateTime(packageInfo.timePackaged).toString());
  ui->leVersion->setText(QString::fromUtf8(packageInfo.version.c_str()));
  ui->leMaintainer->setText(QString::fromUtf8(packageInfo.copyrightOwner.c_str()));
  ui->pteTitle->setPlainText(QString::fromUtf8(packageInfo.title.c_str()));
  ui->pteDescription->setPlainText(QString::fromUtf8(packageInfo.description.c_str()));
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
  ui->leSize->setText(QLocale::system().formattedDataSize(packageInfo.GetSize()));
#else
  ui->leSize->setText(QString("%1 bytes").arg(packageInfo.GetSize()));
#endif

  FileTableModel* runFiles = new FileTableModel(parent, packageInfo.runFiles);
  QSortFilterProxyModel* runProxyModel = new QSortFilterProxyModel(this);
  runProxyModel->setSourceModel(runFiles);
  ui->tvRunFiles->setModel(runProxyModel);
  ui->tvRunFiles->sortByColumn(0, Qt::AscendingOrder);
  if (packageInfo.runFiles.empty())
  {
    ui->lbRunFiles->hide();
    ui->tvRunFiles->hide();
  }
  FileTableModel* docFiles = new FileTableModel(parent, packageInfo.docFiles);
  QSortFilterProxyModel* docProxyModel = new QSortFilterProxyModel(this);
  docProxyModel->setSourceModel(docFiles);
  ui->tvDocFiles->setModel(docProxyModel);
  ui->tvDocFiles->sortByColumn(0, Qt::AscendingOrder);
  if (packageInfo.docFiles.empty())
  {
    ui->lbDocFiles->hide();
    ui->tvDocFiles->hide();
  }

  if (packageInfo.runFiles.empty() && packageInfo.docFiles.empty())
  {
    ui->tabWidget->removeTab(1);
  }
}

PackageInfoDialogImpl::~PackageInfoDialogImpl()
{
  delete ui;
}

int PackageInfoDialog::DoModal(QWidget* parent, const PackageInfo& packageInfo)
{
  PackageInfoDialogImpl dlg(parent, packageInfo);
  return dlg.exec();
}
