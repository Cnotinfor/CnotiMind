#ifndef MEMORYXMLHANDLER_H
#define MEMORYXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QList>

#include "CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class MemoryXmlHandler : public QXmlDefaultHandler
	{
	public:
		MemoryXmlHandler( Brain* brain );

		bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
		bool endElement( const QString & namespaceURI, const QString & localName, const QString & qName );

	private:
		Brain* _brain;
		MemoryType _type;
	};

}

#endif // MEMORYXMLHANDLER_H
