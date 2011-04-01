#if !defined(_RULENODE_H)
#define _RULENODE_H

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QHash>

#include "../Node.h"

namespace CnotiMind
{

	class Brain;

	class RuleNode : public QObject, public Node
	{
		Q_OBJECT


	public:

		enum RuleNodeType
		{
//			Condition,
//			Action,
//			Storage,
//			Emotion,
//			Root,
//			DataMining,
//			Event
		};
		Q_DECLARE_FLAGS( RuleNodeTypes, RuleNodeType )

		RuleNode( const QString& key, const QString& value, Brain* brain, QObject* parent );

		virtual void exec() = 0;
		virtual void exec( QHash<QString, QString>& variables ) = 0;
		virtual bool isRoot() const;

	protected:
		void execChildren();
		void execChildren( QHash<QString, QString>& variables );

	protected:
		Brain* _brain;
	};

}
#endif  //_RULENODE_H
