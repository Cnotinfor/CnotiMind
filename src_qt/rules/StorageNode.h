#if !defined(_STORAGENODE_H)
#define _STORAGENODE_H

#include <QtCore/QString>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{
	class StorageNode : public RuleNode
	{
		Q_OBJECT

	public:
		StorageNode(const QString& key, const QString& value, MemoryType memory, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth = 0 ) const;

	protected:
		MemoryType _memory;
	};

}
#endif  //_STORAGENODE_H
