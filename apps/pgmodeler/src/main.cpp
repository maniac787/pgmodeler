/*
# PostgreSQL Database Modeler (pgModeler)
#
# (c) Copyright 2006-2026 - Raphael Araújo e Silva <raphael@pgmodeler.io>
#
# DEVELOPMENT, MAINTENANCE AND COMMERCIAL DISTRIBUTION BY:
# Nullptr Labs Software e Tecnologia LTDA <contact@nullptrlabs.io>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

#include "pgmodelerapp.h"
#include "mainwindow.h"
#include "utilsns.h"
#include <signal.h>
#include <QSplashScreen>

#ifdef PRIV_CODE_SYMBOLS
	#include "privcoreinit.h"
	#include "privcoreclasses.h"
#endif

namespace {
	void startCrashHandler(int signal)
	{
		try
		{
			QString chandler_cmd = QString("\"%1\"").arg(GlobalAttributes::getPgModelerCHandlerPath()) + " -style " + GlobalAttributes::DefaultQtStyle;
			QFile output;
			UtilsNs::saveFile(GlobalAttributes::getTemporaryFilePath(GlobalAttributes::StacktraceFile),
												UtilsNs::generateStackTrace(signal).toUtf8());

			/* Changing the working dir to the main executable in order to call the crash handler
			 * if the PGMODELER_CHANDLER_PATH isn't set */
			QDir dir;
			dir.cd(QApplication::applicationDirPath());
			exit(1 + system(chandler_cmd.toStdString().c_str()));
		}
		catch(Exception &e)
		{
			qFatal() << "** Failed to save stacktrace file! Crash handler aborted.";
			qFatal() << e.getExceptionsText();
		}
	}
}

int main(int argc, char **argv)
{
	try
	{		
		//Install a signal handler to start crashhandler when SIGSEGV or SIGABRT is emitted
		signal(SIGSEGV, startCrashHandler);
		signal(SIGABRT, startCrashHandler);

		GlobalAttributes::init(argv[0], true);
		PgModelerApp app(argc,argv);
		int res=0;

		// Loading the application splash screen
		QSplashScreen splash;
		QPixmap pix(":images/images/pgmodeler_splash.png");

		if(qApp->primaryScreen()->devicePixelRatio() > 1)
			pix.setDevicePixelRatio(qApp->primaryScreen()->devicePixelRatio());
		else
			pix = pix.scaledToWidth(320, Qt::SmoothTransformation);

		splash.setPixmap(pix);
		splash.show();
		splash.raise();
		app.processEvents();

		//Creates the main form
		MainWindow fmain;

		#ifdef PRIV_CODE_SYMBOLS
			__pgm_plus_gui_init
		#endif

		// Displaying the splash for one and a half second after displaying the main window
		QTimer::singleShot(1500, &splash, [&splash, &fmain]() {
			fmain.show();
			splash.finish(&fmain);
		 });

		//Loading models via command line on MacOSX are disabled until the file association work correclty on that system
		#ifndef Q_OS_MACOS
			QStringList params = app.arguments();
			params.pop_front();

			//If the user specifies a list of files to be loaded
			if(!params.isEmpty())
				fmain.loadModels(params);
		#endif

		res = app.exec();
		app.closeAllWindows();

		return res;
	}
	catch(Exception &e)
	{
		QTextStream ts(stdout);
		ts << e.getExceptionsText();
		return enum_t(e.getErrorCode());
	}
}
