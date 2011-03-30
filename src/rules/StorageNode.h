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
		StorageNode(const QString& key, const QString& value, Brain::MemoryType memory, Brain* brain, QObject* parent);

		void exec();
		RuleNodeTypes type() const;

	protected:
		Brain::MemoryType _memory;
	};

}
#endif  //_STORAGENODE_H
