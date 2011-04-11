#if !defined(_CONDITIONPERCEPTIONNODE_H)
#define _CONDITIONPERCEPTIONNODE_H

#include <QtCore/QString>

#include "ConditionNode.h"

namespace CnotiMind
{
	class Brain;

	class ConditionPerceptionNode : public ConditionNode
	{
		Q_OBJECT

	public:
		ConditionPerceptionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;

	protected:
		bool isTrue();
	};

}
#endif  //_CONDITIONPERCEPTIONNODE_H
