#ifndef SETTINGSXMLHANDLER_H
#define SETTINGSXMLHANDLER_H

#include <QtXml/QXmlDefaultHandler>

namespace CnotiMind
{
	class Brain;

	class SettingsXmlHandler : public QXmlDefaultHandler
	{
	public:
		SettingsXmlHandler( Brain* brain );

		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement( const QString & namespaceURI, const QString & localName, const QString & qName );
		bool characters( const QString & ch );

	protected:
		bool elementPerception( const QXmlAttributes & atts );
		bool elementAction( const QXmlAttributes & atts );
		bool elementEmotion( const QXmlAttributes & atts );

		bool endElementPerception();
		bool endElementAction();
		bool endElementEmotion();

	private:
		Brain* _brain;

		bool _insidePerception;
		bool _insideAction;
		bool _insideEmotion;
		bool _insideValue;
		QString _elementType;
		QString _elementName;
		bool _needValues;

		QStringList _possibleValues;
		QList<int> _emotionAttributes;

		// Constants
		const QString TYPE;
		const QString TYPE_INT;
		const QString TYPE_STRING;
		const QString TYPE_VALUES;

		const QString NAME;


	};

}

#endif // SETTINGSXMLHANDLER_H
