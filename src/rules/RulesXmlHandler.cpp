#include "RulesXmlHandler.h"
#include "RuleNode.h"

namespace CnotiMind
{

	RulesXmlHandler::RulesXmlHandler() :
		QXmlDefaultHandler()
	{
	}


	bool RulesXmlHandler::startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts )
	{

		return true;
	}

	bool RulesXmlHandler::endElement( const QString & namespaceURI, const QString & localName, const QString & qName )
	{
		return false;
	}

}
