#if !defined(_RULENODE_H)
#define _RULENODE_H

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QHash>

#include "../Node.h"

namespace CnotiMind
{

	class Brain;

	class RuleNode : public QObject
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

		RuleNode( Brain* brain, QObject* parent );

		virtual void exec() = 0;
		virtual void exec( QHash<QString, QString>& variables ) = 0;
		virtual bool isRoot() const;

		virtual QString info( int depth = 0 ) const = 0;

	protected:
		virtual void execChildren();
		virtual void execChildren( QHash<QString, QString>& variables );

		void tagsToValue( QString& value, QHash<QString, QString>& variables );

		QString space( int depth ) const;

	protected:
		Brain* _brain;
	};

}
#endif  //_RULENODE_H
