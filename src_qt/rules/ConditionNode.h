#if !defined(_CONDITIONNODE_H)
#define _CONDITIONNODE_H

#include <QtCore/QString>
#include <QtCore/QHash>

#include "RuleNode.h"
#include "../CnotiMind.h"

namespace CnotiMind
{
	class Brain;

	class ConditionNode : public RuleNode
	{
		Q_OBJECT

	public:

		ConditionNode( ConditionOperator op, Brain* brain, QObject* parent);

		void exec();
		void exec( QHash<QString,QString>& variables );

		QString info( int depth = 0 ) const;



	protected:
		ConditionOperator _operator;
		virtual bool isTrue() = 0;


	};

}

#endif  //_CONDITIONNODE_H
