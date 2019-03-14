#include <QCoreApplication>
#include <QStringList>
#include "runpy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    /** NOTE:
     *  Test a simple python script, absolute path should be provided, and it
     *  may be accommodated with QProcess.setWorkdingDirectory().
     */
//    QString fName = "/home/yzy/Desktop/qtTest/QProcessPython/runtest.py";
    QString fName = "/home/yzy/Desktop/qtTest/QProcessPython/runComplex.py";
//    QString fName = "/home/yzy/myStudy/PythonTest/VideoSuperResolution/Train/run.py";
    RunPy *runPy = new RunPy();
    runPy->processPy(fName);

    return a.exec();
}
