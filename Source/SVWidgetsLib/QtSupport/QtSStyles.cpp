/* ============================================================================
* Copyright (c) 2009-2016 BlueQuartz Software, LLC
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this
* list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* Neither the name of BlueQuartz Software, the US Air Force, nor the names of its
* contributors may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The code contained herein was partially funded by the followig contracts:
*    United States Air Force Prime Contract FA8650-07-D-5800
*    United States Air Force Prime Contract FA8650-10-D-5210
*    United States Prime Contract Navy N00173-07-C-2068
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "QtSStyles.h"

#include <QtCore/QTextStream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

#include "moc_QtSStyles.cpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QtSStyles::QtSStyles()
{}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QtSStyles::~QtSStyles()
{}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString QtSStyles::GetUIFont()
{
#if defined (Q_OS_MAC)
  //return QString::fromUtf8("Helvetica");
  QFont font;
  return font.defaultFamily();
#elif defined (Q_OS_WIN)
  return QString::fromUtf8("Trebuchet MS");
#else
  QFont font("DejaVu Sans");
  if (font.fromString("DejaVu Sans") )
  {
    return font.toString();
  } else {
    QFont font;
    return font.defaultFamily();
  }
#endif
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFont QtSStyles::GetHumanLabelFont()
{
  QFont humanLabelFont;
  humanLabelFont.setBold(true);
  humanLabelFont.setItalic(false);
  humanLabelFont.setWeight(75);
  humanLabelFont.setStyleStrategy(QFont::PreferAntialias);
  humanLabelFont.setFamily(GetUIFont());

#if defined (Q_OS_MAC)
  humanLabelFont.setPointSize(16);
#elif defined (Q_OS_WIN)
  humanLabelFont.setPointSize(12);
#endif
  return humanLabelFont;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFont QtSStyles::GetBrandingLabelFont()
{
  QFont brandingFont;
  brandingFont.setBold(true);
  brandingFont.setItalic(true);
  brandingFont.setWeight(75);
  brandingFont.setStyleStrategy(QFont::PreferAntialias);
  brandingFont.setFamily(GetUIFont());

#if defined (Q_OS_MAC)
  brandingFont.setPointSize(11);
#elif defined (Q_OS_WIN)
  brandingFont.setPointSize(8);
#else
  brandingFont.setPointSize(9);
#endif
  return brandingFont;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFont QtSStyles::GetCategoryFont()
{
  QFont categoryFont;
  categoryFont.setBold(true);
  categoryFont.setWeight(75);
  categoryFont.setStyleStrategy(QFont::PreferAntialias);
  categoryFont.setFamily(GetUIFont());

#if defined (Q_OS_MAC)
  categoryFont.setPointSize(14);
#elif defined (Q_OS_WIN)
  categoryFont.setPointSize(10);
#endif

  return categoryFont;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QFont QtSStyles::GetTitleFont()
{
  QFont categoryFont;
  categoryFont.setBold(true);
  categoryFont.setWeight(99);
  categoryFont.setStyleStrategy(QFont::PreferAntialias);
  categoryFont.setFamily(GetUIFont());

#if defined (Q_OS_MAC)
  categoryFont.setPointSize(16);
#elif defined (Q_OS_WIN)
  categoryFont.setPointSize(12);
#endif

  return categoryFont;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QtSStyles::LineEditErrorStyle(QLineEdit* lineEdit)
{
    QString str;
    QTextStream ss(&str);
    ss << "QLineEdit#" << lineEdit->objectName() << "{";
    //  ss << "border: 1px solid rgb(180, 0, 0);";
    ss << "background-color: rgb(255, 246, 179);"; // Yellow background
    ss << "}";
    lineEdit->setStyleSheet(str);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QtSStyles::LineEditClearStyle(QLineEdit* lineEdit)
{
  lineEdit->setStyleSheet("");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void QtSStyles::LineEditRedErrorStyle(QLineEdit* lineEdit)
{
  QString str;
  QTextStream ss(&str);
  ss << "QLineEdit#" << lineEdit->objectName() << "{";
  //  ss << "border: 1px solid rgb(180, 0, 0);";
  ss << "background-color: rgb(208, 128, 139);"; // Yellow background
  ss << "}";
  lineEdit->setStyleSheet(str);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QString QtSStyles::DAPSelectionButtonStyle()
{
  QString str;
  QTextStream ss(&str);

  ss << "QPushButton {\n";
  ss << "border: 1px solid #8f8f91;\n";
  ss << "border-radius: 4px;\n";
  ss << "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\nstop: 0 #DDDDDD, stop: 1 #FFFFFF);\n";
  ss << "font-size: 12pt;\n";
  ss << "padding-left: 16px;\n";
  ss << "padding-right: 4px;\n";
  ss << "padding-top: 2px;\n";
  ss << "padding-bottom: 2px;\n";
  ss << "}\n";

  ss << "QPushButton::menu-indicator {\n";
  ss << "subcontrol-origin: padding;\n";
  ss << "subcontrol-position:  left; /* */\n";
  ss << "}\n";

  ss << "QPushButton::menu-indicator:pressed, QPushButton::menu-indicator:open {\n";
  ss << "position: relative;\n";
  ss << "}\n";

  ss << "QPushButton:pressed {\n";
  ss << "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\nstop: 0 " << QApplication::palette().highlight().color().name() << ", stop: 1 #FFFFFF);\n";
  ss << "}\n";

  ss << "QPushButton:flat {\n";
  ss << "border: none;\n";
  ss << "}\n";

  ss << "QPushButton:hover {\n";
  ss << "border: 1px solid #8f8f91;\n";
  ss << "border-radius: 4px;\n";
  ss << "}\n";

  return str;
}
