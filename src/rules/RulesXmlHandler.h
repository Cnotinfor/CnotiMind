#ifndef RULESXMLHANDLER_H
#define RULESXMLHANDLER_H

#include <QXmlDefaultHandler>

namespace CnotiMind
{
	class RuleNode;

	class RulesXmlHandler : public QXmlDefaultHandler
	{

	public:
		explicit RulesXmlHandler();

		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement( const QString & namespaceURI, const QString & localName, const QString & qName );

	signals:

	public slots:

	private:
		RuleNode* _rootNode;
		RuleNode* _currentNode;

	};

}
#endif // RULESXMLHANDLER_H
