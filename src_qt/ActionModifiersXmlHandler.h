#ifndef ACTIONMODIFIERSXMLHANDLER_H
#define ACTIONMODIFIERSXMLHANDLER_H

// Qt
#include <QtXml/QXmlDefaultHandler>
#include <QtCore/QHash>

namespace CnotiMind
{
	class Emotion;
	class ActionModifier;

	class ActionModifiersXmlHandler : public QXmlDefaultHandler
	{
	public:
		ActionModifiersXmlHandler();

		bool startElement(const QString& namespaceURI, const QString& localName,
						  const QString &qName, const QXmlAttributes& atts );
		bool endElement(const QString &namespaceURI, const QString& localName,
						const QString &qName );

		QList<ActionModifier*> reinforceStatements();
	private:
		QString  _action;
		Emotion* _emotion;
		bool     _isCurrentEmotionUsed;
		int      _order;
		QHash<QString, QString> _properties;

		QList<ActionModifier*> _reinforceStatements;

		// Methods
		bool elementAction(const QXmlAttributes& atts);
		bool elementEmotion(const QXmlAttributes& atts);
		bool elementProperty(const QXmlAttributes& atts);
		bool elementOrder(const QXmlAttributes& atts);
		bool elementModifier(const QXmlAttributes& atts);
	};

} // namespace CnotiMind

#endif // ACTIONMODIFIERSXMLHANDLER_H
