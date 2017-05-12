#include "webenginepage.h"

WebEnginePage::WebEnginePage(QObject *parent = Q_NULLPTR) :
	QWebEnginePage(parent)
{}

WebEnginePage::WebEnginePage(QWebEngineProfile *profile, QObject *parent) :
	QWebEnginePage(profile, parent)
{}

bool WebEnginePage::certificateError(const QWebEngineCertificateError &certificateError)
{
	Q_UNUSED(certificateError);

	// Unconditionally ignore error
	return true;
}
