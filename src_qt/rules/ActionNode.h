#if !defined(_ACTIONNODE_H)
#define _ACTIONNODE_H

#include <QtCore/QString>
#include "RuleNode.h"

namespace CnotiMind
{
	class Brain;

	class ActionNode : public RuleNode
	{
		Q_OBJECT

	public:
		ActionNode( const QString& key, const QString& value, Brain* brain, QObject* parent );

		void exec();
		void exec( QHash<QString, QString>& variables );

		QString info( int depth ) const;

	protected:
		QString _name;
		QString _value;

	};

}

#endif  //_ACTIONNODE_H
