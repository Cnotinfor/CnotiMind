#ifndef STORAGECOPYNODE_H
#define STORAGECOPYNODE_H

#include <QDateTime>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	/*!
		Node to copy the content from a memory (Long Term or Working Memory) to another memory.
		If the origin of memory is Long Term, it get copied to the Working Memory.

		It is possible to define a time frame from where the events get copied.

		It also possible to define which events get copied giving the name of the before and after event.
	*/
	class StorageCopyNode : public RuleNode
	{
	public:
		StorageCopyNode(MemoryType memory, Brain* brain, QObject* parent);
		StorageCopyNode(MemoryType memory, const QString &afterDate, const QString &beforeDate, Brain* brain, QObject* parent);
		StorageCopyNode(MemoryType memory, const QString &afterEvent, EventPosition afterEventPosition,
						const QString &beforeEvent, EventPosition beforeEventPosition, Brain* brain, QObject* parent);


		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static StorageCopyNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		MemoryType _memoryFrom;
		MemoryType _memoryTo;

		QDateTime _after;
		QString _afterDateString;

		QString _afterEventName;
		EventPosition _afterPosition;

		QDateTime _before;
		QString _beforeDateString;

		QString _beforeEventName;
		EventPosition _beforePosition;
	};

}
#endif // STORAGECOPYNODE_H
