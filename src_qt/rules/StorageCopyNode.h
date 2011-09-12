#ifndef STORAGECOPYNODE_H
#define STORAGECOPYNODE_H

#include <QDateTime>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class StorageCopyNode : public RuleNode
	{
	public:
		StorageCopyNode(MemoryType memory, Brain* brain, QObject* parent);
		StorageCopyNode(MemoryType memory, QDateTime before, QDateTime after, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

		static StorageCopyNode *fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent );

	protected:
		MemoryType _memory;
		QDateTime _after;
		QDateTime _before;
	};

}
#endif // STORAGECOPYNODE_H
