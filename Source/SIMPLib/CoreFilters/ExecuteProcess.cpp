/*
 * Your License or Copyright can go here
 */

#include "ExecuteProcess.h"

#include <QtCore/QFileInfo>
#include <QtCore/QCoreApplication>

#include "SIMPLib/Common/Constants.h"
#include "SIMPLib/SIMPLibVersion.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersReader.h"
#include "SIMPLib/FilterParameters/AbstractFilterParametersWriter.h"
#include "SIMPLib/FilterParameters/InputFileFilterParameter.h"
#include "SIMPLib/FilterParameters/StringFilterParameter.h"

// Include the MOC generated file for this class
#include "moc_ExecuteProcess.cpp"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ExecuteProcess::ExecuteProcess() :
  AbstractFilter()
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
ExecuteProcess::~ExecuteProcess()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::setupFilterParameters()
{
  FilterParameterVector parameters;

  parameters.push_back(StringFilterParameter::New("Command Line Arguments", "Arguments", getArguments(), FilterParameter::Parameter));

  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);

  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int ExecuteProcess::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);

  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::dataCheck()
{
  setErrorCondition(0);

  QStringList arguments = splitArgumentsString(m_Arguments);
  if (arguments.size() <= 0)
  {
    QString ss = QObject::tr("No command line arguments have been specified.");
    setErrorCondition(-4001);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
    return;
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::preflight()
{
  // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
  setInPreflight(true); // Set the fact that we are preflighting.
  emit preflightAboutToExecute(); // Emit this signal so that other widgets can do one file update
  emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
  dataCheck(); // Run our DataCheck to make sure everthing is setup correctly
  emit preflightExecuted(); // We are done preflighting this filter
  setInPreflight(false); // Inform the system this filter is NOT in preflight mode anymore.
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::execute()
{
  setErrorCondition(0);
  dataCheck();
  if(getErrorCondition() < 0) { return; }

  QStringList arguments = splitArgumentsString(m_Arguments);
  QString command = arguments[0];
  arguments.removeAt(0);

  QProcess* process = new QProcess(NULL);
  qRegisterMetaType<QProcess::ExitStatus>("QProcess::ExitStatus");
  qRegisterMetaType<QProcess::ProcessError>("QProcess::ProcessError");
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
          this, SLOT(processHasFinished(int, QProcess::ExitStatus)), Qt::QueuedConnection);
  connect(process, SIGNAL(error(QProcess::ProcessError)),
          this, SLOT(processHasErroredOut(QProcess::ProcessError)), Qt::QueuedConnection);
  process->start(command, arguments);

  m_Mutex.lock();
  m_Pause = true;
  while (m_Pause == true)
  {
    m_WaitCondition.wait(&m_Mutex, 2000);
    QCoreApplication::processEvents();
  }
  m_Mutex.unlock();

  delete process;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
QStringList ExecuteProcess::splitArgumentsString(QString arguments)
{
  QStringList argumentList;
  for(int i=0; i<m_Arguments.size(); i++)
  {
    if (m_Arguments[i] == '\"')
    {
      i++;
      int start = i;
      int index = m_Arguments.indexOf("\"", start);
      if (index == -1)
      {
        index = m_Arguments.size();
      }
      int end = index - 1;
      argumentList.push_back(m_Arguments.mid(start, end-start+1));
      i = index;
    }
    else
    {
      int start = i;
      int index = m_Arguments.indexOf(" ", start + 1);
      if (index == -1)
      {
        index = m_Arguments.size();
      }
      int end = index - 1;
      argumentList.push_back(m_Arguments.mid(start, end-start+1));
      i = index;
    }
  }

  return argumentList;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::processHasFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  if (exitStatus == QProcess::CrashExit)
  {
    QString ss = QObject::tr("The process crashed during its exit.");
    setErrorCondition(-4003);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (exitCode < 0)
  {
    QString ss = QObject::tr("The process finished with exit code %1.").arg(QString::number(exitCode));
    setErrorCondition(-4004);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else
  {
    notifyStatusMessage(getHumanLabel(), "Complete");
  }

  m_Pause = false;
  m_WaitCondition.wakeAll();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void ExecuteProcess::processHasErroredOut(QProcess::ProcessError error)
{
  if (error == QProcess::FailedToStart)
  {
    QString ss = QObject::tr("The process failed to start.  Either the invoked program is missing, or you may have insufficient permissions to invoke the program.");
    setErrorCondition(-4005);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (error == QProcess::Crashed)
  {
    QString ss = QObject::tr("The process crashed some time after starting successfully.");
    setErrorCondition(-4006);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (error == QProcess::Timedout)
  {
    QString ss = QObject::tr("The process timed out.");
    setErrorCondition(-4007);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (error == QProcess::WriteError)
  {
    QString ss = QObject::tr("An error occurred when attempting to write to the process.");
    setErrorCondition(-4008);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else if (error == QProcess::ReadError)
  {
    QString ss = QObject::tr("An error occurred when attempting to read from the process.");
    setErrorCondition(-4009);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }
  else
  {
    QString ss = QObject::tr("An unknown error occurred.");
    setErrorCondition(-4009);
    notifyErrorMessage(getHumanLabel(), ss, getErrorCondition());
  }

  m_Pause = false;
  m_WaitCondition.wakeAll();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
AbstractFilter::Pointer ExecuteProcess::newFilterInstance(bool copyFilterParameters)
{
  ExecuteProcess::Pointer filter = ExecuteProcess::New();
  if(true == copyFilterParameters)
  {
    copyFilterParameterInstanceVariables(filter.get());
  }
  return filter;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getCompiledLibraryName()
{ return Core::CoreBaseName; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getBrandingString()
{
  return "SIMPLib Core Filter";
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getFilterVersion()
{
  QString version;
  QTextStream vStream(&version);
  vStream <<  SIMPLib::Version::Major() << "." << SIMPLib::Version::Minor() << "." << SIMPLib::Version::Patch();
  return version;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getGroupName()
{ return SIMPL::FilterGroups::CoreFilters; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getSubGroupName()
{ return SIMPL::FilterSubGroups::MiscFilters; }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
const QString ExecuteProcess::getHumanLabel()
{ return "Execute Process"; }

